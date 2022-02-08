#pragma once

#include <array>
#include <cstdint>

namespace HID {
#pragma pack(push, 1)
enum struct prefix_type : uint8_t { main = 0, global = 1, local = 2 };
enum struct bSize : uint8_t { e0 = 0, e1 = 1, e2 = 2, e4 = 3 };
#pragma pack(push, 1)
struct prefix {
  bSize size : 2; // 0,1,2,4 bytes
  prefix_type bType : 2;
  uint8_t bTag : 4;
};

static_assert(sizeof(prefix) == sizeof(std::byte),
              "prefix does not fit in a single byte");

// no long tags are actually defined, so this is kinda useless right now.
template <uint8_t size> struct long_item {
public:
  static_assert(size > 3, "use a small item");
  prefix pre;
  uint8_t data_size;
  std::byte long_tag;
  std::array<std::byte, size> bLongItemTag;
  constexpr long_item<size>(std::byte long_tag,
                            std::array<std::byte, size> long_item_tag) noexcept
      : pre{bSize::e2, static_cast<prefix_type>(0b11), 0b1111}, data_size(size),
        long_tag(long_tag), bLongItemTag(long_item_tag) {}
};

template <typename data_type, prefix_type p, int tag> struct small_item {
public:
  prefix pre;
  data_type min;

  constexpr small_item(data_type data) {
    static_assert(sizeof(data_type) != 0,
                  "data size is 0. This really shouldn't happen.");
    static_assert(
        sizeof(data_type) != 3,
        "int size cannot be 3. I have never heard of a int of size 3.");
    static_assert(sizeof(data_type) <= 4, "int size is too big.");
    switch (sizeof(data_type)) {
    case 1:
      pre = prefix{bSize::e1, p, tag};
      break;
    case 2:
      pre = prefix{bSize::e2, p, tag};
      break;
    case 4:
      pre = prefix{bSize::e4, p, tag};
      break;
    }
    min = data;
  }
};
#pragma pack(pop)
namespace uses {
enum struct page_type : uint8_t {
  generic_desktop = 0x01,
  simulation_controls = 0x02,
  VR_controls = 0x03,
  sport_controls = 0x04,
  game_controls = 0x05,
  generic_device_controls = 0x06,
  keyboard_keypad = 0x07,
  LED = 0x08,
  button = 0x09,
  ordinal = 0x0A,
  telephony_device = 0x0B,
  consumer = 0x0C,
  digitizer = 0x0D,
  haptics = 0x0E,
  unicode = 0x10,
  eye_and_head_trackers = 0x12,
  auxiliary_display = 0x14,
  sensors = 0x20,
  medical_instrument = 0x40,
  braille_display = 0x41,
  lighting_and_illumination = 0x59,
  camera_controls = 0x90,
  gaming_device = 0x92,
};
#ifndef _CONSTEXPR_HID_USAGES_HPP_DEFINED_
enum struct generic_desktop : uint8_t;
enum struct simulation_controls : uint8_t;
enum struct VR : uint8_t;
enum struct sport : uint8_t;
enum struct game_controls : uint8_t;
enum struct generic_device_controls : uint8_t;
enum struct keyboard : uint8_t;
enum struct LED : uint8_t;
enum struct button : uint8_t;
enum struct ordinal : uint8_t;
enum struct telephony8 : uint8_t;
enum struct telephony16 : uint16_t;
enum struct consumer8 : uint8_t;
enum struct consumer16 : uint16_t;
enum struct digitizer : uint8_t;
enum struct haptic8 : uint8_t;
enum struct haptic16 : uint16_t;
enum struct eye_and_head_tracker8 : uint8_t;
enum struct eye_and_head_tracker16 : uint16_t;
enum struct auxiliary_display : uint8_t;
enum struct sensors8 : uint8_t;
enum struct sensors16 : uint16_t;
enum struct medical_instrument : uint8_t;
enum struct braille_display8 : uint8_t;
enum struct braille_display16 : uint16_t;
enum struct lighting_and_illumination : uint8_t;
enum struct camera_controls : uint8_t;
enum struct FIDO : uint8_t;
enum struct preferred_colors : uint8_t;
#endif
} // namespace uses
namespace internal {
template <class = int> inline constexpr bool always_false = false;
template <class = int> inline constexpr bool always_true = true;

template <typename T> struct range_traits {};
// this is super jank but I can't think of a better way to do this.
template <typename usage_type> constexpr auto typeswitch(usage_type usage) {
  if constexpr (std::is_same<usage_type, uses::generic_desktop>::value) {
    return uses::page_type::generic_desktop;
  } else if constexpr (std::is_same<usage_type,
                                    uses::simulation_controls>::value) {
    return uses::page_type::simulation_controls;
  } else if constexpr (std::is_same<usage_type, uses::VR>::value) {
    return uses::page_type::VR_controls;
  } else if constexpr (std::is_same<usage_type, uses::sport>::value) {
    return uses::page_type::sport_controls;
  } else if constexpr (std::is_same<usage_type, uses::game_controls>::value) {
    return uses::page_type::game_controls;
  } else if constexpr (std::is_same<usage_type,
                                    uses::generic_device_controls>::value) {
    return uses::page_type::generic_device_controls;
  } else if constexpr (std::is_same<usage_type, uses::keyboard>::value) {
    return uses::page_type::keyboard_keypad;
  } else if constexpr (std::is_same<usage_type, uses::LED>::value) {
    return uses::page_type::LED;
  } else if constexpr (std::is_same<usage_type, uses::button>::value) {
    return uses::page_type::button;
  } else if constexpr (std::is_same<usage_type, uses::ordinal>::value) {
    return uses::page_type::ordinal;
  } else if constexpr (std::is_same<usage_type, uses::telephony16>::value ||
                       std::is_same<usage_type, uses::telephony8>::value) {
    return uses::page_type::telephony_device;
  } else if constexpr (std::is_same<usage_type, uses::consumer8>::value ||
                       std::is_same<usage_type, uses::consumer16>::value) {
    return uses::page_type::consumer;
  } else if constexpr (std::is_same<usage_type, uses::digitizer>::value) {
    return uses::page_type::digitizer;
  } else if constexpr (std::is_same<usage_type, uses::haptic8>::value ||
                       std::is_same<usage_type, uses::haptic16>::value) {
    return uses::page_type::haptics;
  } else if constexpr (std::is_same<usage_type,
                                    uses::eye_and_head_tracker8>::value ||
                       std::is_same<usage_type,
                                    uses::eye_and_head_tracker16>::value) {
    return uses::page_type::eye_and_head_trackers;
  } else if constexpr (std::is_same<usage_type,
                                    uses::auxiliary_display>::value) {
    return uses::page_type::auxiliary_display;
  } else if constexpr (std::is_same<usage_type, uses::sensors8>::value ||
                       std::is_same<usage_type, uses::sensors16>::value) {
    return uses::page_type::sensors;
  } else if constexpr (std::is_same<usage_type,
                                    uses::medical_instrument>::value) {
    return uses::page_type::medical_instrument;
  } else if constexpr (std::is_same<usage_type,
                                    uses::braille_display8>::value ||
                       std::is_same<usage_type,
                                    uses::braille_display16>::value) {
    return uses::page_type::braille_display;
  } else if constexpr (std::is_same<usage_type,
                                    uses::lighting_and_illumination>::value) {
    return uses::page_type::lighting_and_illumination;
  } else if constexpr (std::is_same<usage_type, uses::camera_controls>::value) {
    return uses::page_type::camera_controls;
  }
}
template <typename data, typename data2, typename minimum, typename maximum>
struct extent {
  minimum min;
  maximum max;
  constexpr extent(data min, data2 max) : min(min), max(max) {
  }
};
} // namespace internal
#pragma pack(pop)
} // namespace HID