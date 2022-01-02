#pragma once

#include <bitset>
#include <cstddef>
#include <ostream>
#include <sys/types.h>

namespace HID {
// This is a byte wrapper that prints out better
struct byte {
public:
  std::byte itself;

  constexpr byte(unsigned char value) : itself(static_cast<std::byte>(value)) {}
  constexpr byte() = default;

  friend std::ostream &operator<<(std::ostream &output, const byte &rhs) {
    uint big = static_cast<unsigned int>(rhs.itself) / 16;
    uint small = static_cast<unsigned int>(rhs.itself) % 16;
    output << std::hex << "0x" << big << small << std::dec;
    return output;
  }

  friend bool operator==(byte lhs, byte rhs) {
    return lhs.itself == rhs.itself;
  }

  friend byte operator&(byte lhs, byte rhs) {
    return static_cast<unsigned char>(lhs.itself) &
           static_cast<unsigned char>(rhs.itself);
  }

  operator std::bitset<8>() {
    return std::bitset<8>(static_cast<unsigned char>(itself));
  }
};
static_assert(sizeof(byte) == 1, "byte is not equal 1 byte");

inline constexpr unsigned char
operator"" _u8(unsigned long long int arg) noexcept {
  return static_cast<unsigned char>(arg);
}

inline constexpr unsigned char
operator"" _u16(unsigned long long int arg) noexcept {
  return static_cast<uint16_t>(arg);
}

} // namespace HID