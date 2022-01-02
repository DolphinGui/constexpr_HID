#pragma once

#include "constexpr_HID/internal.hpp"

namespace HID {
#pragma pack(push, 1)
namespace internal {

template <typename usage_type = unsigned char>
struct usage_min : small_item<usage_type, prefix_type::local, 1> {
  constexpr usage_min(usage_type data)
      : small_item<usage_type, prefix_type::local, 1>(data) {}
};
template <typename usage_type> struct range_traits<usage_min<usage_type>> {
  typedef usage_type type;
};
template <typename usage_type = unsigned char>
struct usage_max : small_item<usage_type, prefix_type::local, 2> {
  constexpr usage_max(usage_type data)
      : small_item<usage_type, prefix_type::local, 2>(data) {}
};
template <typename usage_type> struct range_traits<usage_max<usage_type>> {
  typedef usage_type type;
};
} // namespace internal
template<typename usage_type>
struct usage : small_item<usage_type, prefix_type::local, 0> {
  constexpr usage(usage_type data)
      : small_item<usage_type, prefix_type::local, 0>(data) {}
};
template <typename usage_type1, typename usage_type2>
struct usage_extent
    : internal::extent<usage_type1, usage_type2, internal::usage_min<usage_type1>,
                       internal::usage_max<usage_type2>> {
  constexpr usage_extent(usage_type1 lower, usage_type2 upper)
      : internal::extent<usage_type1,usage_type2, internal::usage_min<usage_type1>,
                         internal::usage_max<usage_type2>>(lower, upper) {}
};
/* I have not seen designators, strings, or delimiters used in any descriptors.
I honestly have no idea if anyone does anything with them, and so won't program
them in until someone asks me to.*/
#pragma pack(pop)
} // namespace HID