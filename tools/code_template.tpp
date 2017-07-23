#include <disccord/models/$$__FILE__:gsub("%.lua$", ".hpp")$$>

$$
__SUB_NAMESPACES__ = __FILE__:match("(.+)/[^/]-$")
if __SUB_NAMESPACES__ then
    local ns = {}
    for component in __SUB_NAMESPACES__:gmatch("[^/]+") do
        ns[#ns+1] = ("namespace %s\n{"):format(component)
    end
    __SUB_NAMESPACES__ = ns
end
$$

/*
NOTE: this code is generated by a tool (generate_models.lua)
Please make changes in $$__FILE__$$ to update this file.
*/

namespace disccord
{
namespace models
{
$$__SUB_NAMESPACES__ and table.concat(__SUB_NAMESPACES__, "\n") or ""$$
%s
$$__SUB_NAMESPACES__ and ("}\n"):rep(#__SUB_NAMESPACES__) or ""$$
}
}
