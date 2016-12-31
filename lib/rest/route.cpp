#include <rest/route.hpp>

namespace disccord
{
	namespace rest
	{
		namespace internal
		{
			std::string RouteString(std::string url)
            {
                return url;
            }
		}

		route_info Route(std::string method, std::string url)
        {
            route_info info;
            info.method = method;
            info.full_url = url;
            info.bucket_url = url;

            return info;
        }
	}
}