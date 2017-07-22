#ifndef _route_hpp_
#define _route_hpp_

#include <array>
#include <stdexcept>
#include <string>

namespace disccord
{
    namespace rest
    {
        struct route_info
        {
            const std::string method;
            const std::string bucket_url;
            const std::string full_url;
        };

        template<int N>
        const route_info build_route(const std::string method,
            const std::string route, const std::array<std::string, N> params)
        {
            std::string bucket{route};
            std::string url{route};

            std::string::size_type start{std::string::npos};

            for (auto i = params.rbegin(); i != params.rend(); i++)
            {
                auto param = *i;

                auto end = route.rfind('}', start - 1);
                start = route.rfind('{', start - 1);

                if (start == std::string::npos || end == std::string::npos)
                    throw new std::range_error{"invalid route"};

                auto length = end - start + 1;

                std::string segment = url.substr(start, length);

                if (segment == "{guild.id}" ||
                    segment == "{channel.id}")
                {
                    bucket.replace(start, length, param);
                }

                url.replace(start, length, param);
            }

            return route_info{method, bucket, url};
        }
    }
}
#endif /* _route_hpp_ */
