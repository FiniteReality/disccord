-- Generates C++ models given a data descriptions

--[=[Example model DSL:
model {"user",
    property {"name", "std::string"},
    property {"id", "snowflake"},

    method {"derp", "int", [[return 0;]]}
}
]=]

local generate do -- Code generation
    function generate(data, model_name)
        local header = {}
        local code = {}

        if data.type == "model" then
            header[#header+1] = ("class %s {"):format(data.name)
            header[#header+1] = ("public: %s(); virtual ~%s();"):format(data.name, data.name)

            local ctor_params = {}

            for i = 1, #data.members do
                local member_header, member_code = generate(data.members[i], data.name)
                header[#header+1] = member_header
                code[#code+1] = member_code
                ctor_params[#ctor_params+1] = ("%s(%s)"):format(data.members[i].name, data.members[i].default or "")
            end

            header[#header+1] = "};"

            code[#code+1] = ("%s::%s() : %s { }"):format(data.name, data.name, table.concat(ctor_params, ","))
            code[#code+1] = ("%s::~%s() { }"):format(data.name, data.name)

        elseif data.type == "property" then
            header[#header+1] = ("private: %s %s;"):format(data.prop_type, data.name)
            header[#header+1] = ("public: %s get_%s();"):format(data.prop_type, data.name)

            code[#code+1] = ("%s %s::%s() { return %s; }"):format(data.prop_type, model_name, data.name, data.name)

        elseif data.type == "method" then
            error("not supported yet")
        end

        return table.concat(header, "\n"), table.concat(code, "\n")
    end
end

do -- DSL definitions
    function model(data)
        if type(data) ~= "table" then
            error("argument 1 to model() is not a table", 2)
        end

        __MODELS__[#__MODELS__ + 1] = {type = "model", name = data[1], members = {unpack(data, 2)}}
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

        return {type = "method", name = data[1], type = data[2], body = data[3]}
    end
end

local read_file, write_file do -- Helpers
    function read_file(file)
        local f = assert(io.open(file, "r"))
        local data = assert(f:read("*a"))
        assert(f:close())
        return data
    end
    function write_file(file, contents)
        local f = assert(io.open(file, "w"))
        assert(f:write(contents))
        assert(f:close())
    end
end

local args = {...}
local nargs = select('#', ...)

if nargs < 3 then
    error("expected at least 3 arguments on command line")
end

local templates = {header = read_file(args[1]), code = read_file(args[2])}

for i = 3, nargs do
    __MODELS__ = {}

    local env = {
        __FILE__ = args[i],
    }

    local header_template = templates.header:gsub("%$%$(.-)%$%$", function(code)
        local f = loadstring("return "..code) or assert(loadstring(code))
        return tostring(setfenv(f, env)() or "")
    end)
    local code_template = templates.code:gsub("%$%$(.-)%$%$", function(code)
        local f = loadstring("return "..code) or assert(loadstring(code))
        return tostring(setfenv(f, env)() or "")
    end)

    dofile(args[i])

    for j = 1, #__MODELS__ do
        local header, code = generate(__MODELS__[j])
        header = header_template:format(header)
        code = code_template:format(code)

        write_file(args[i]:gsub("%.lua$", ".hpp"), header)
        write_file(args[i]:gsub("%.lua$", ".cpp"), code)
    end
end
