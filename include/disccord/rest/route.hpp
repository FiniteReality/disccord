#ifndef _route_hpp_
#define _route_hpp_

#include <string>

namespace disccord
{
    namespace rest
    {
        struct route_info
        {
            std::string method;
            std::string full_url;
            std::string bucket_url;
        };

        namespace internal
        {
            std::string get_route_string(std::string url);

            template<class TFirst, class... TArgs>
            std::string get_route_string(
                std::string base,
                TFirst first,
                TArgs... args)
            {
                size_t start = base.find('{');
                size_t end = base.find('}', start);

                return get_route_string(base.replace(start, end, first),
                                        args...);
            }
        }

        route_info get_route(std::string method, std::string url);

        template<class TFirst, class... TArgs>
        route_info get_route(
            std::string method,
            std::string base,
            TFirst first,
            TArgs... args)
        {

            size_t start = base.find('{');
            size_t end = base.find('}', start) - start + 1;

            std::string paramName = base.substr(start, end);

            if (paramName == "{channel.id}" || paramName == "{guild.id}")
            {
                return get_route(method, base.replace(start, end, first),
                                 args...);
            }
            else
            {
                route_info info;
                info.method = method;
                info.bucket_url = base;
                info.full_url =
                    internal::get_route_string(base.replace(start, end, first),
                                               args...);

                return info;
            }
        }
    }
}
#endif /* _route_hpp_ */
