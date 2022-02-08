#pragma once

#include "constexpr_HID/global_items.hpp"
#include "constexpr_HID/local_items.hpp"
#include "constexpr_HID/main_items.hpp"
#include "internal.hpp"
#include <limits>
#include <tuplet/tuple.hpp>
#include <type_traits>

namespace HID {
#pragma pack(push, 1)

template <typename usage_type> struct usage_pair {
  usage_page page;
  usage<usage_type> type;
  usage_pair(usage_type type)
      : page(internal::typeswitch(static_cast<usage_type>(0))), type(type) {}
};

template <typename usage_type> struct usage_range {
  typedef internal::extent<usage_type, usage_type,
                           typename internal::usage_min<usage_type>,
                           typename internal::usage_max<usage_type>>
      range;
  usage_page page;
  range types;
  usage_range(range type)
      : page(internal::typeswitch(static_cast<usage_type>(0))), types(type) {}
};

template <typename usage_type, typename... T> struct descriptor {
  usage_pair<usage_type> pair;
  tuplet::tuple<T...> members;

  void static iteration(auto &&part) {}

public:
  constexpr descriptor(usage_type t, T... members)
      : pair(t), members(tuplet::make_tuple(members...)) {
    prefix_type current;
    unsigned int pushs = 0;
    unsigned int min = std::numeric_limits<unsigned int>::max();
    unsigned int max = std::numeric_limits<unsigned int>::max();

    /*
    rn the constexpr support necessary to actually validate stuff
    at compile time only exists in c++23, which basically doesn't
    exist at the moment. So for now, implementing this is a long
    way off.
    */
    tuplet::apply([&](auto &&...args) { ((iteration(args)), ...); },
                  this->members);
  }
};

template <size_t size> using raw = std::array<uint8_t, size>;

#pragma pack(pop)
} // namespace HID