#include "password_generator.h"

#include <algorithm>

PasswordGenerator::PasswordGenerator() = default;

void PasswordGenerator::Fill(std::vector<char> &password,
                             const std::vector<char> &pool,
                             unsigned int count) {
  for (unsigned int i = 0; i < count; ++i) {
    std::uniform_int_distribution<unsigned long> udist(0, pool.size() - 1);
    password.push_back(pool[udist(rd)]);
  }
}

std::string PasswordGenerator::GeneratePassword(const GenerationOptions &opts) {
  std::vector<char> password;

  // In the initial case we will handle any cases where the MAXIMUM digits of
  // characters have been specified
  if (opts.symbols && opts.max_symbols > 0) {
    Fill(password, SPECIAL, opts.max_symbols);
  }

  if (opts.digits && opts.max_digits > 0) {
    Fill(password, DIGITS, opts.max_digits);
  }

  if (opts.lowercase && opts.max_lowercase > 0) {
    Fill(password, LOWER, opts.max_lowercase);
  }

  if (opts.uppercase && opts.max_uppercase > 0) {
    Fill(password, UPPER, opts.max_uppercase);
  }

  // Create a pool of all remaining character sets (those that did not have a
  // maximum specified) to fill the remaining length of the requested password
  std::vector<char> pool;
  if (opts.symbols && opts.max_symbols == 0) {
    pool.insert(pool.end(), SPECIAL.begin(), SPECIAL.end());
  }
  if (opts.digits && opts.max_digits == 0) {
    pool.insert(pool.end(), DIGITS.begin(), DIGITS.end());
  }
  if (opts.lowercase && opts.max_lowercase == 0) {
    pool.insert(pool.end(), LOWER.begin(), LOWER.end());
  }
  if (opts.uppercase && opts.max_uppercase == 0) {
    pool.insert(pool.end(), UPPER.begin(), UPPER.end());
  }
  if (password.size() < opts.length && !pool.empty()) {
    Fill(password, pool, opts.length - password.size());
  }

  std::shuffle(password.begin(), password.end(), rd);

  // Since our options dictate the MAX limit of each character class, we can
  // end up with a password greater than the desired length. In this case trim
  // the end of the password, producing the correct size.
  //
  // Note: The "MAX" options are just that -- the maximum digits that may be
  // in the password. The only guarantee is the generated password will not
  // have more than the specified value. It is valid for a generated password
  // to have fewer than the specified MAX characters (e.g. symbols, digits).
  if (password.size() > opts.length) {
    password.erase(password.begin() + (opts.length - 1), password.end());
  }

  return std::accumulate(password.begin(), password.end(), std::string(""));
}