#ifndef _optional_hpp_
#define _optional_hpp_

// Tri-state optional object
// Has states for when a value is present, when a value is null and when a
// value is not present.

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
                typedef T value_type;

                constexpr optional() : _specified(false) { }
                constexpr optional(const T& value) : _value(value), _specified(true) { }

                constexpr bool has_value() const { return _specified && !_null; }
                constexpr bool is_specified() const { return _specified; }
                constexpr T get_value() const { return _value; }

                constexpr operator T&() { return _value; }
                constexpr operator T() const { return _value; }

                constexpr static optional no_value()
                {
                    // TODO: move this into the ctor
                    auto val = optional();
                    val._specified = true;
                    val._null = true;

                    return val;
                }

                bool operator==(const optional<T>& rhs) const
                {
                    return _null == rhs._null &&
                           _specified = rhs._specified &&
                           _value == rhs._value;
                }

                bool operator==(const T& rhs) const
                {
                    return _specified == true &&
                           _value == rhs;
                }
        };
    }
}

#endif /* _optional_hpp_ */
