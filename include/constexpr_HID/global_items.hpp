#pragma once

#include "constexpr_HID/internal.hpp"

namespace HID {
#pragma pack(push, 1)
using usage_page = small_item<uses::page_type, prefix_type::global, 0>;
namespace internal {
template <typename Int = unsigned char>
using logical_minimum = small_item<Int, prefix_type::global, 1>;
template <typename Int = unsigned char>
using logical_maximum = small_item<Int, prefix_type::global, 2>;
template <typename Int = unsigned char>
using physical_minimum = small_item<Int, prefix_type::global, 3>;
template <typename Int = unsigned char>
using physical_maximum = small_item<Int, prefix_type::global, 4>;

template <std::unsigned_integral unsigned_type>
using report_size = small_item<unsigned_type, prefix_type::global, 7>;
template <std::unsigned_integral unsigned_type>
using report_count = small_item<unsigned_type, prefix_type::global, 9>;
} // namespace internal
template <typename Int = unsigned char>
using logical_maximum = internal::logical_maximum<Int>;
template <std::unsigned_integral size_type, std::unsigned_integral count_type>
struct report_type {
  internal::report_size<size_type> size;
  internal::report_count<count_type> count;
  constexpr report_type(size_type size, count_type count)
      : size(size), count(count) {}
};

template <std::integral min_type, std::integral max_type>
struct logical_extent
    : internal::extent<min_type, max_type, internal::logical_minimum<min_type>,
                       internal::logical_maximum<max_type>> {
  constexpr logical_extent(min_type min, max_type max)
      : internal::extent<min_type, max_type,
                         internal::logical_minimum<min_type>,
                         internal::logical_maximum<max_type>>(min, max){};
};
template <std::integral min_type, std::integral max_type>
struct physical_extent
    : internal::extent<min_type, max_type, internal::physical_minimum<min_type>,
                       internal::physical_maximum<max_type>> {
  constexpr physical_extent(min_type min, max_type max)
      : internal::extent<min_type, max_type,
                         internal::physical_minimum<min_type>,
                         internal::physical_maximum<max_type>>(min, max){};
};

struct push {
  prefix itself;
  constexpr push() : itself{bSize::e0, prefix_type::global, 10} {}
};
struct pop {
  prefix itself;
  constexpr pop() : itself{bSize::e0, prefix_type::global, 11} {}
};
enum struct exponent : uint16_t {
  e1 = 0x1,
  e2 = 0x2,
  e3 = 0x3,
  e4 = 0x4,
  e5 = 0x5,
  e6 = 0x6,
  e7 = 0x7,
  neg8 = 0x8,
  neg7 = 0x9,
  neg6 = 0xA,
  neg5 = 0xB,
  neg4 = 0xC,
  neg3 = 0xD,
  neg2 = 0xE,
  neg1 = 0xF
};

using unit_exponent = small_item<exponent, prefix_type::global, 5>;

// I haven't seen anybody use this so far
using report_ID = small_item<uint8_t, prefix_type::global, 8>;
#pragma pack(pop)
} // namespace HID