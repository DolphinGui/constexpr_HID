#pragma once
#include "constexpr_HID/internal.hpp"
#include <tuplet/tuple.hpp>

namespace HID {
#pragma pack(push, 1)
namespace IOF {
enum struct p1 { data = false, constant = true };
enum struct p2 { array = false, variable = true };
enum struct p3 { absolute = false, relative = true };
enum struct p4 { no_wrap = false, wrap = true };
enum struct p5 { linear = false, nonlinear = true };
enum struct p6 { preferred_state = false, no_preferred = true };
enum struct p7 { no_null_state = false, null_state = true };
enum struct p8 { not_volatile = false, out_volatile = true };
enum struct p9 { bitfield = false, buffered_byte = true };
} // namespace IOF
enum struct collection_type : unsigned char {
  physical = 0x00,
  application = 0x01,
  logical = 0x02,
  report = 0x03,
  named_array = 0x04,
  usage_switch = 0x05,
  usage_modifier = 0x06
};
struct io8 {
  IOF::p1 data_or_constant : 1;
  IOF::p2 array_or_variable : 1;
  IOF::p3 absolute_or_relative : 1;
  IOF::p4 no_wrap_or_wrap : 1;
  IOF::p5 linear_or_nonlinear : 1;
  IOF::p6 preferred_or_not : 1;
  IOF::p7 no_null_or_null : 1;
  IOF::p8 not_volatile_or_not : 1;
};
struct io16 {
  IOF::p1 data_or_constant : 1;
  IOF::p2 array_or_variable : 1;
  IOF::p3 absolute_or_relative : 1;
  IOF::p4 no_wrap_or_wrap : 1;
  IOF::p5 linear_or_nonlinear : 1;
  IOF::p6 preferred_or_not : 1;
  IOF::p7 no_null_or_null : 1;
  IOF::p8 not_volatile_or_not : 1;
  IOF::p9 bitfield_or_buffered_byte : 1;
};

namespace internal {
using collection_start = small_item<collection_type, prefix_type::main, 0b1010>;
struct collection_end {
  prefix itself;
  constexpr collection_end() : itself{bSize::e0, prefix_type::main, 0b1100} {}
};
} // namespace internal
template <typename... T> struct collection {
  internal::collection_start start;
  tuplet::tuple<T...> members;
  internal::collection_end end;
  constexpr collection(collection_type t, T... members)
      : start(t), members(tuplet::make_tuple(members...)) {}
};
template<uint8_t tag>
using iosmall = small_item<io8, prefix_type::main, tag>;
template<uint8_t tag>
using iobig = small_item<io16, prefix_type::main, tag>;

template <typename io> struct input;

template <> struct input<io8> : iosmall<0b1000> {
  constexpr input(io8 data): iosmall<0b1000>(data){}
};
template <> struct input<io16> : iobig<0b1000> {
  constexpr input(io16 data): iobig<0b1000>(data){}
};

template <typename io> struct output;

template <> struct output<io8> : iosmall<0b1001> {
  constexpr output(io8 data): iosmall<0b1001>(data){}
};
template <> struct output<io16> : iobig<0b1001> {
  constexpr output(io16 data): iobig<0b1001>(data){}
};
template <typename io> struct feature;

template <> struct feature<io8> : iosmall<0b1011> {
  constexpr feature(io8 data): iosmall<0b1011>(data){}
};
template <> struct feature<io16> : iobig<0b1011> {
  constexpr feature(io16 data): iobig<0b1011>(data){}
};
#pragma pack(pop)
} // namespace HID