#ifndef _endpoint_hpp_
#define _endpoint_hpp_

#include <string>

namespace disccord
{
    namespace REST
    {
        struct RouteInfo
        {
            std::string method;
            std::string full_url;
            std::string bucket_url;
        };

        namespace internal
        {
            std::string RouteString(std::string url)
            {
                return url;
            }

            template<class TFirst, class... TArgs>
            std::string RouteString(std::string base, TFirst first, TArgs... args)
            {
                size_t start = base.find('{');
                size_t end = base.find('}', start);

                return RouteString(base.replace(start, end, first), args...);
            }
        }

        RouteInfo Route(std::string method, std::string url)
        {
            RouteInfo info;
            info.method = method;
            info.full_url = url;
            info.bucket_url = url;

            return info;
        }

        template<class TFirst, class... TArgs>
        RouteInfo Route(std::string method, std::string base, TFirst first, TArgs... args)
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
                RouteInfo info;
                info.method = method;
                info.bucket_url = base;
                info.full_url = internal::RouteString(base.replace(start, end, first), args...);

                return info;
            }
        }
    }
}
#endif /* _endpoint_hpp_ */