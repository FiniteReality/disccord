// Optional<T> class with support for cpprestsdk

#ifndef _optional_hpp_
#define _optional_hpp_

#include <exception>

#include <json.h>

namespace disccord
{
    namespace util
    {
        template <typename T>
        class optional
        {
            T _value;
            bool _null;
            bool _specified;

            public:
                constexpr optional() : _specified(false) { }
                //constexpr optional(T value) : _value(value), _specified(true) { }
                constexpr optional(const T& value) : _value(value), _specified(true) { }

                constexpr bool has_value() const { return _specified || !_null; }
                constexpr bool is_specified() const { return _specified; }
                constexpr T get_value() const { return _value; }

                constexpr operator T&() { return _value; }
                constexpr operator T() const { return _value; }

                constexpr operator web::json::value() const
                {
                    if (_specified)
                    {
                        if (_null) {
                            return web::json::value();
                        } else {
                            return web::json::value(_value);
                        }
                    }
                    else
                    {
                        throw std::logic_error("cannot convert to json when not specified");
                    }
                }

                constexpr static optional no_value()
                {
                    auto val = optional();
                    val._specified = true;
                    val._null = true;

                    return val;
                }
        };
    }
}

#endif /* _optional_hpp_ */
