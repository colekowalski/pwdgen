#pragma once

#include <random>

struct GenerationOptions {
  bool digits = true;
  bool uppercase = true;
  bool lowercase = true;
  bool symbols = true;
  unsigned int length = 32;
  unsigned int max_uppercase = 0;
  unsigned int max_lowercase = 0;
  unsigned int max_digits = 0;
  unsigned int max_symbols = 0;

  bool Validate() const {
    // If we have at least one class with a '0' max length (unlimited) we can
    // produce the requested password
    if ((symbols && max_symbols == 0) || (digits && max_digits == 0) ||
        (uppercase && max_uppercase == 0) || (lowercase && max_lowercase == 0)) {
      return true;
    }

    // validate the requested parameters are AT LEAST of the requested length
    unsigned int max_len = 0;
    if (symbols) max_len += max_symbols;
    if (digits) max_len += max_digits;
    if (uppercase) max_len += max_uppercase;
    if (lowercase) max_len += max_lowercase;
    return (max_len >= length);
  }
};

class PasswordGenerator {
 public:
  PasswordGenerator();
  std::string GeneratePassword(const GenerationOptions& opts);

 private:
  const std::vector<char> DIGITS = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  const std::vector<char> UPPER = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                   'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  const std::vector<char> LOWER = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                   'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  const std::vector<char> SPECIAL = {'!', '@', '#', '$', '%', '^', '&', '*'};

  std::random_device rd;
  void Fill(std::vector<char>& password, const std::vector<char>& pool, unsigned int count);
};