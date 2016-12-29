#ifndef _endpoint_hpp_
#define _endpoint_hpp_

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
            std::string RouteString(std::string url);

            template<class TFirst, class... TArgs>
            std::string RouteString(std::string base, TFirst first, TArgs... args)
            {
                size_t start = base.find('{');
                size_t end = base.find('}', start);

                return RouteString(base.replace(start, end, first), args...);
            }
        }

        route_info Route(std::string method, std::string url);

        template<class TFirst, class... TArgs>
        route_info Route(std::string method, std::string base, TFirst first, TArgs... args)
        {

            size_t start = base.find('{');
            size_t end = base.find('}', start) - start + 1;

            std::string paramName = base.substr(start, end);

            if (paramName == "{channel.id}" || paramName == "{guild.id}")
            {
                return Route(method, base.replace(start, end, first), args...);
            }
            else
            {
                route_info info;
                info.method = method;
                info.bucket_url = base;
                info.full_url = internal::RouteString(base.replace(start, end, first), args...);

                return info;
            }
        }
    }
}
#endif /* _endpoint_hpp_ */