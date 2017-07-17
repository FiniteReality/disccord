$$NAME = __FILE__:match("/?(.-)$"):gsub("%.", "_")$$
#ifndef _$$NAME$$_
#define _$$NAME$$_

namespace disccord
{
namespace models
{
%s
}
}

#endif /* _$$NAME$$_ */
