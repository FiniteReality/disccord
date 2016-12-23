/***
DISCCORD LIB - UNIT TEST
***/

#include <string>
#include <iostream>

#include <REST/route.hpp>

using namespace disccord::REST;

std::ostream& operator<< (std::ostream& stream, const RouteInfo& info)
{
	return stream << "[bucket " << info.method << " " << info.bucket_url << "] " << info.full_url;
}

int main(){
	
	std::cout << "Test endpoint: " << Route("GET", "/gateway") << std::endl;
	std::cout << "Test endpoint with params: " << 
		Route("GET", "/channels/{channel.id}/messages/{message.id}", "1234", "5678") <<
		std::endl;
	
	return 0;
}