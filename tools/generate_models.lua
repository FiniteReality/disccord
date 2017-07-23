-- Generates C++ models given a data descriptions

--[=[Example model DSL:
model {"user",
    property {"name", "std::string"},
    property {"id", "snowflake"},

    method {"derp", "int", [[return 0;]]},
    method {"stuff", "int",
        [[return i+1;]],
        param {"i", "int", "0"}
    }
}
]=]

local generate do -- Code generation
    function generate(data, model_name)
        local header = {}
        local code = {}

        if data.type == "model" then
            header[#header+1] = ("class %s {"):format(data.name)
            header[#header+1] = ("public: %s();"):format(data.name)

            local ctor_params = {}

            for i = 1, #data.members do
                local member_header, member_code = generate(data.members[i], data.name)
                header[#header+1] = member_header
                code[#code+1] = member_code
                if data.members[i].type == "property" then
                    ctor_params[#ctor_params+1] = ("%s(%s)"):format(data.members[i].name, data.members[i].default or "")
                end
            end

            header[#header+1] = "};"

            code[#code+1] = ("%s::%s() : %s { }"):format(data.name, data.name, table.concat(ctor_params, ","))

        elseif data.type == "property" then
            header[#header+1] = ("private: %s %s;"):format(data.prop_type, data.name)
            header[#header+1] = ("public: %s get_%s();"):format(data.prop_type, data.name)

            code[#code+1] = ("%s %s::get_%s() { return %s; }"):format(data.prop_type, model_name, data.name, data.name)

        elseif data.type == "method" then
            local params = {}
            for i = 1, #data.params do
                local param = data.params[i]
                if param.default ~= nil then
                    params[#params+1] = ("%s %s = %s"):format(param.param_type, param.name, param.default)
                else
                    params[#params+1] = ("%s %s"):format(param.param_type, param.name)
                end
            end
            header[#header+1] = ("%s %s(%s);"):format(data.return_type, data.name, table.concat(params, ","))
            code[#code+1] = ("%s %s::%s(%s){%s}"):format(data.return_type, model_name, data.name, table.concat(params, ","), data.body)
        end

        return table.concat(header, "\n"), table.concat(code, "\n")
    end
end

do -- DSL definitions
    function converter(data)
        if type(data) ~= "table" then
            error("argument 1 to converter() is not a table", 2)
        end

        local converter = {from = data.from, to = data.to, body = data[1]}
        __CONVERTERS__[#__CONVERTERS__+1] = converter
    end

    function include(file)
        __INCLUDES__[#__INCLUDES__ + 1] = file
    end

    function model(data)
        if type(data) ~= "table" then
            error("argument 1 to model() is not a table", 2)
        end

        __MODEL__ = {type = "model", name = data[1], members = {unpack(data, 2)}}
        __MODELS__[#__MODELS__ + 1] = __MODEL__
    end

    function property(data)
        if type(data) ~= "table" then
            error("argument 1 to property() is not a table", 2)
        end

        return {type = "property", name = data[1], prop_type = data[2], default = data[3]}
    end

    function method(data)
        if type(data) ~= "table" then
            error("argument 1 to method() is not a table", 2)
        end

        return {type = "method", name = data[1], return_type = data[2], body = data[3], params = {unpack(data, 4)}}
    end

    function param(data)
        if type(data) ~= "table" then
            error("argument 1 to param()) is not a table", 2)
        end

        return {name = data[1], param_type = data[2], default = data[3]}
    end
end

local read_file, write_file, read_file_safe do -- Helpers
    function read_file_safe(file)
        local f, err = io.open(file, "r")
        if f then
            local data, err = f:read("*a")
            f:close()
            return data, err
        end
        return nil, err
    end
    function read_file(file)
        local f = assert(io.open(file, "r"))
        local data = assert(f:read("*a"))
        f:close()
        return data
    end
    function write_file(file, contents)
        local f = assert(io.open(file, "w"))
        assert(f:write(contents))
        f:close()
    end
end

local generate_encode_body, generate_decode_body do
    local function get_encoder(member)
        if member.prop_type:find("std::string") or
        member.prop_type:find("disccord::discriminator") or
        member.prop_type:find("disccord::snowflake") or
        member.prop_type:find("bool") or
        member.prop_type:find("u?int%d+_t") then
            return ("web::json::value(%s)"):format(member.name)

        elseif member.prop_type:find("util::optional") then
            local sub_simple, sub_complex = get_encoder{
                prop_type = member.prop_type:match("%b<>"):sub(2,-2),
                name = ("%s.get_value()"):format(member.name)
            }

            if not sub_simple then
                error("not supported yet", 2)
            else
                return nil, ([[
if (%s.has_value())
{
    info.push_back(std::make_pair("%s", %s));
}
else if (%s.is_specified())
{
    info.push_back(std::make_pair("%s", web::json::value::null()));
}]]):format(member.name, member.name, sub_simple, member.name, member.name)
            end
        elseif member.prop_type:find("models") then
            return ("%s.encode()"):format(member.name)
        else
            -- TODO: handle multiple converters from this type
            -- TODO: handle more complex converters
            for _, converter in ipairs(__CONVERTERS__) do
                if converter.from == member.prop_type then
                    return converter.body:format(member.name)
                end
            end
        end

        error(("get_encoder: unknown type %s"):format(member.prop_type), 2)
    end
    function generate_encode_body(model)
        local result = {"std::vector<std::pair<std::string, web::json::value>> info;"}

        for _, member in ipairs(model.members) do
            if member.type == "property" then
                local simple, complex = get_encoder(member)
                if not simple then
                    result[#result+1] = complex
                else
                    result[#result+1] = ("info.push_back(std::make_pair(\"%s\", web::json::value(%s)));"):format(member.name, simple)
                end
            end
        end

        result[#result+1] = "return web::json::value::object(info);"
        return table.concat(result, "\n")
    end

    local function get_decoder(prop_type, err)
        if prop_type:find("std::string") then
            return "field.as_string()";

        elseif prop_type:find("snowflake") then
            return "field.as_number().to_uint64()"
        elseif prop_type:find("discriminator") then
            return ("static_cast<%s>(field.as_number().to_uint32())"):format(prop_type)

        elseif prop_type:find("u?int%d+_t") then
            local int_type = prop_type:match("(u?int%d+)_t")
            if int_type:find("int64") then
                return ("field.as_number().to_%s()"):format(int_type)
            elseif int_type:find("int32") then
                return ("field.as_number().to_%s()"):format(int_type)
            else
                return ("static_cast<%s>(field.as_number().to_uint64())"):format(int_type)
            end

        elseif prop_type:find("bool") then
            return "field.as_bool()"

        elseif prop_type:find("models") then
            return "model", ("%s::value_type model; model.decode(field);"):format(prop_type);

        else
            for _, converter in ipairs(__CONVERTERS__) do
                if converter.to == prop_type then
                    local value = get_decoder(converter.from, false)
                    if value then
                        return converter.body:format(value)
                    end
                end
            end

            if not err then
                error(("get_decoder: unknown type %s"):format(prop_type), 2)
            end
        end
    end
    function generate_decode_body(model)
        local result = {}

        for _, member in ipairs(model.members) do
            if member.type == "property" then
                local assigner, decoder = get_decoder(member.prop_type)
                if member.prop_type:find("util::optional") then

                    result[#result+1] = ([[
if (!json.has_field("%s"))
    %s = disccord::util::optional<%s::value_type>();
if (json.at("%s").is_null())
    %s = disccord::util::optional<%s::value_type>::no_value();
else
{
    auto field = json.at("%s");
    %s
    %s = disccord::util::optional<%s::value_type>(%s);
}]]):format(member.name, member.name, member.prop_type, member.name, member.name, member.prop_type, member.name, decoder or "", member.name, member.prop_type, assigner)

                else

                    result[#result+1] = ([[
{
    auto field = json.at("%s");
    %s
    %s = %s;
}]]):format(member.name, decoder or "", member.name, assigner)

                end
            end
        end

        return table.concat(result, "\n")
    end
end

local args = {...}
local nargs = select('#', ...)

if nargs < 3 then
    error("expected at least 3 arguments on command line")
end

local templates = {header = read_file(args[1]), code = read_file(args[2])}
local header_output = args[3].."/"
local code_output = args[4].."/"

for i = 5, nargs do
    __MODELS__ = {}
    __INCLUDES__ = {}
    __CONVERTERS__ = {}
    dofile(args[i])

    local env = {
        __FILE__ = args[i]
    }
    for i, v in pairs(getfenv()) do
        env[i] = v
    end

    local header_template = templates.header:gsub("%$%$(.-)%$%$", function(code)
        local f = loadstring("return "..code) or assert(loadstring(code))
        return tostring(setfenv(f, env)() or "")
    end)
    local code_template = templates.code:gsub("%$%$(.-)%$%$", function(code)
        local f = loadstring("return "..code) or assert(loadstring(code))
        return tostring(setfenv(f, env)() or "")
    end)

    for j = 1, #__MODELS__ do
        local model = __MODELS__[j]
        model.members[#model.members+1] = {
            type = "method",
            name = "encode",
            return_type = "web::json::value",
            body = generate_encode_body(model),
            params = {}
        }
        model.members[#model.members+1] = {
            type = "method",
            name = "decode",
            return_type = "void",
            body = generate_decode_body(model),
            params = {{name = "json", param_type = "web::json::value"}}
        }

        local header, code = generate(model)
        header = header_template:format(header)
        code = code_template:format(code)

        local header_loc = header_output..args[i]:gsub("%.lua$", ".hpp")
        local code_loc = code_output..args[i]:gsub("%.lua$", ".cpp")

        local orig_header, err = read_file_safe(header_loc)
        local orig_code, err = read_file_safe(code_loc)

        --print(err, code_loc)

        if err or orig_header ~= header or orig_code ~= code then
            write_file(header_loc, header)
            write_file(code_loc, code)
        end
    end
end
