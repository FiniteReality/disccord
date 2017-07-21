#include <disccord/util/url_encode.hpp>

#include <sstream>

namespace disccord
{
    namespace util
    {
        std::string url_encode(const std::string& s)
        {
            std::string lookup = "0123456789ABCDEF";
            std::stringstream e;
             
            for (const char &c : s) // RFC 3986 section 2.3 Unreserved Characters
            {
                if (('0' <= c && c <= '9') ||
                    ('a' <= c && c <= 'z') ||
                    ('A' <= c && c <= 'Z') ||
                    (c=='-' || c=='_' || c=='.' || c=='~') 
                )
                {
                    e << c;
                }
                else
                {
                    e << '%';
                    e << lookup[(c & 0xF0) >> 4];
                    e << lookup[(c & 0x0F)];
                }
            }
            
            return e.str();
        }
    } // namespace util
} // namespace disccord
