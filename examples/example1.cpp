#include "constexpr_HID/constexpr_HID.hpp"
#include "constexpr_HID/uses_types.hpp"
#include "constexpr_HID/byte.hpp"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <iostream>


template <typename T> using raw_array = std::array<HID::byte, sizeof(T)>;

using namespace HID;

constexpr std::array<HID::byte, 85> joystick_report_desc = {
    0x05, 0x01,       // Usage Page (Generic Desktop)
    0x09, 0x04,       // Usage (Joystick)
    0xA1, 0x01,       // Collection (Application)
    0x15, 0x00,       //   Logical Minimum (0)
    0x25, 0x01,       //   Logical Maximum (1)
    0x75, 0x01,       //   Report Size (1)
    0x95, 0x20,       //   Report Count (32)
    0x05, 0x09,       //   Usage Page (Button)
    0x19, 0x01,       //   Usage Minimum (Button #1)
    0x29, 0x20,       //   Usage Maximum (Button #32)
    0x81, 0x02,       //   Input (variable,absolute)
    0x15, 0x00,       //   Logical Minimum (0)
    0x25, 0x07,       //   Logical Maximum (7)
    0x35, 0x00,       //   Physical Minimum (0)
    0x46, 0x3B, 0x01, //   Physical Maximum (315)
    0x75, 0x04,       //   Report Size (4)
    0x95, 0x01,       //   Report Count (1)
    0x65, 0x14,       //   Unit (20)
    0x05, 0x01,       //   Usage Page (Generic Desktop)
    0x09, 0x39,       //   Usage (Hat switch)
    0x81, 0x42,       //   Input (variable,absolute,null_state)
    0x05, 0x01,       //   Usage Page (Generic Desktop)
    0x09, 0x01,       //   Usage (Pointer)
    0xA1, 0x00,       //   Collection ()
    0x15, 0x00,       //     Logical Minimum (0)
    0x26, 0xFF, 0x03, //     Logical Maximum (1023)
    0x75, 0x0A,       //     Report Size (10)
    0x95, 0x04,       //     Report Count (4)
    0x09, 0x30,       //     Usage (X)
    0x09, 0x31,       //     Usage (Y)
    0x09, 0x32,       //     Usage (Z)
    0x09, 0x35,       //     Usage (Rz)
    0x81, 0x02,       //     Input (variable,absolute)
    0xC0,             //   End Collection
    0x15, 0x00,       //   Logical Minimum (0)
    0x26, 0xFF, 0x03, //   Logical Maximum (1023)
    0x75, 0x0A,       //   Report Size (10)
    0x95, 0x02,       //   Report Count (2)
    0x09, 0x36,       //   Usage (Slider)
    0x09, 0x36,       //   Usage (Slider)
    0x81, 0x02,       //   Input (variable,absolute)
    0xC0              // End Collection
};

constexpr std::array<HID::byte, 99> multitouch_report_desc = {
        0x05, 0x0D,                     // Usage Page (Digitizer)
        0x09, 0x04,                     // Usage (Touch Screen)
        0xa1, 0x01,                     // Collection (Application)
        0x09, 0x22,                     //   Usage (Finger)
        0xA1, 0x02,                     //   Collection (Logical)
        0x09, 0x42,                     //     Usage (Tip Switch)
        0x15, 0x00,                     //     Logical Minimum (0)
        0x25, 0x01,                     //     Logical Maximum (1)
        0x75, 0x01,                     //     Report Size (1)
        0x95, 0x01,                     //     Report Count (1)
        0x81, 0x02,                     //     Input (variable,absolute)
        0x09, 0x51,                     //     Usage (Contact Identifier)
        0x25, 0x7F,                     //     Logical Maximum (127)
        0x75, 0x07,                     //     Report Size (7)
        0x95, 0x01,                     //     Report Count (1)
        0x81, 0x02,                     //     Input (variable,absolute)
        0x09, 0x30,                     //     Usage (Pressure)
        0x26, 0xFF, 0x00,               //     Logical Maximum (255)
        0x75, 0x08,                     //     Report Size (8)
        0x95, 0x01,                     //     Report Count (1)
        0x81, 0x02,                     //     Input (variable,absolute)
        0x05, 0x01,                     //     Usage Page (Generic Desktop)
        0x09, 0x30,                     //     Usage (X)
        0x09, 0x31,                     //     Usage (Y)
        0x26, 0xFF, 0x7F,               //     Logical Maximum (32767)
        0x65, 0x00,                     //     Unit (None)
        0x75, 0x10,                     //     Report Size (16)
        0x95, 0x02,                     //     Report Count (2)
        0x81, 0x02,                     //     Input (variable,absolute)
        0xC0,                           //   End Collection
        0x05, 0x0D,                     //   Usage Page (Digitizer)
        0x27, 0xFF, 0xFF, 0, 0,         //   Logical Maximum (65535)
        0x75, 0x10,                     //   Report Size (16)
        0x95, 0x01,                     //   Report Count (1)
        0x09, 0x56,                     //   Usage (Scan Time)
        0x81, 0x02,                     //   Input (variable,absolute)
        0x09, 0x54,                     //   USAGE (Contact count)
        0x25, 0x7f,                     //   LOGICAL_MAXIMUM (127)
        0x75, 0x08,                     //   REPORT_SIZE (8)
        0x95, 0x01,                     //   REPORT_COUNT (1)
        0x81, 0x02,                     //   INPUT (Data,Var,Abs)
        0x05, 0x0D,                     //   Usage Page (Digitizers)
        0x09, 0x55,                     //   Usage (Contact Count Maximum)
        0x25, 0x0a,        //   Logical Maximum (10)
        0x75, 0x08,                     //   Report Size (8)
        0x95, 0x01,                     //   Report Count (1)
        0xB1, 0x02,                     //   Feature (variable,absolute)
        0xC0                            // End Collection
};

auto joystick_descriptor = descriptor(
    uses::generic_desktop::joystick,
    collection(collection_type::application,
      logical_extent(0_u8, 1_u8),
      report_type(1_u8, 32_u8),
      usage_range(usage_extent(static_cast<uses::button>(1),
                                            static_cast<uses::button>(32))),
      input<io8>(io8{.array_or_variable = IOF::p2::variable}),
      logical_extent(0_u8, 7_u8),
      physical_extent(0_u8, uint16_t(315)),
      report_type(4_u8, 1_u8),
      uint8_t(0x65), uint8_t(0x00), //units, none
      usage_pair(uses::generic_desktop::hat_switch),
      input<io8>(io8{.array_or_variable = IOF::p2::variable,
                    .no_null_or_null = IOF::p7::null_state}),
      usage_pair(uses::generic_desktop::pointer),
      collection(collection_type::physical,
        logical_extent(0_u8, uint16_t(1023)),
        report_type(10_u8, 4_u8),
        usage(uses::generic_desktop::X),
        usage(uses::generic_desktop::Y),
        usage(uses::generic_desktop::Z),
        usage(uses::generic_desktop::Rz),
        input<io8>(io8{.array_or_variable = IOF::p2::variable})),
    logical_extent(0_u8, uint16_t(1023)),
    report_type(10_u8, 2_u8),
    usage(uses::generic_desktop::slider),
    usage(uses::generic_desktop::slider),
    input<io8>(io8{.array_or_variable = IOF::p2::variable})
    )
  );

auto multitouch_descriptor = descriptor(
  uses::digitizer::Touch_Screen,
  collection(collection_type::application,
    usage(uses::digitizer::Finger),
    collection(collection_type::logical,
      usage(uses::digitizer::Tip_Switch),
      logical_extent(uint8_t(0),uint8_t(1)),
      report_type(uint8_t(1),uint8_t(1)),
      input<io8>(io8{.array_or_variable=IOF::p2::variable}),
      usage(uses::digitizer::Contact_Identifier),
      logical_maximum<>(int8_t(127)),
      report_type(uint8_t(7),uint8_t(1)),
      input<io8>(io8{.array_or_variable=IOF::p2::variable}),
      usage(uses::digitizer::Tip_Pressure),
      logical_maximum<int16_t>(255),
      report_type(uint8_t(8),uint8_t(1)),
      input<io8>(io8{.array_or_variable=IOF::p2::variable}),
      usage_page(uses::page_type::generic_desktop),
      usage(uses::generic_desktop::X),
      usage(uses::generic_desktop::Y),
      logical_maximum<int16_t>(32767),
      uint8_t(0x65), uint8_t(0x00), // units, none
      report_type(uint8_t(16),uint8_t(2)),
      input<io8>(io8{.array_or_variable = IOF::p2::variable})
    ),
    usage_page(uses::page_type::digitizer),
    logical_maximum<int32_t>(65535),
    report_type(uint8_t(16),uint8_t(1)),
    usage(uses::digitizer::Scan_Time),
    input<io8>(io8{.array_or_variable=IOF::p2::variable}),
    usage(uses::digitizer::Contact_Count),
    logical_maximum<>(127),
    report_type(uint8_t(8),uint8_t(1)),
    input<io8>(io8{.array_or_variable=IOF::p2::variable}),
    usage_page(uses::page_type::digitizer),
    usage(uses::digitizer::Contact_Count_Maximum),
    logical_maximum<>(10),
    report_type(uint8_t(8),uint8_t(1)),
    feature<io8>(io8{.array_or_variable=IOF::p2::variable})
  )
);
template <typename T>
void test(const raw_array<T>& raw, T test, std::string_view error) {
  raw_array<T> data;
  std::memcpy(&data, &test, sizeof(T));
  if (data != raw) {
    std::cout << '\n' << error;
    std::cout << "\nexpected: ";
    for (auto d : raw)
      std::cout << (d) << ' ';
    std::cout << "\ngot: ";
    for (auto d : data)
      std::cout << (d) << ' ';
    std::cout << "\nSizeof T: " << sizeof(T) << '\n';
  }
}


void dump(auto t){
  raw_array<decltype(t)> data;
  std::memcpy(&data, &t, sizeof(t));
  for (auto d : data)
      std::cout << (d) << ' ';
}

int main() {
  test(joystick_report_desc, joystick_descriptor, "joystick is different");
  test(multitouch_report_desc, multitouch_descriptor, "touchscreen is different");

  return 0;
}