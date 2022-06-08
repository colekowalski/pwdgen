#include <getopt.h>

#include <climits>
#include <iostream>

#include "password_generator.h"
#include "version.h"

// For any option that does not have a corresponding short option, select a
// pseudo-character starting at CHAR_MAX + 1. This is similar to how the
// situation is handled in many gnu utilities.
enum {
  MAX_SYMBOLS_OPTION = CHAR_MAX + 1,
  MAX_DIGITS_OPTION,
  MAX_LOWERCASE_OPTION,
  MAX_UPPERCASE_OPTION,
};

static struct option long_opts[] = {
    {"no-symbols", no_argument, nullptr, 'S'},
    {"no-digits", no_argument, nullptr, 'D'},
    {"no-lowercase", no_argument, nullptr, 'L'},
    {"no-uppercase", no_argument, nullptr, 'U'},

    {"max-symbols", required_argument, nullptr, MAX_SYMBOLS_OPTION},
    {"max-digits", required_argument, nullptr, MAX_DIGITS_OPTION},
    {"max-lowercase", required_argument, nullptr, MAX_LOWERCASE_OPTION},
    {"max-uppercase", required_argument, nullptr, MAX_UPPERCASE_OPTION},

    {"length", required_argument, nullptr, 'l'},
    {"count", required_argument, nullptr, 'c'},

    {"help", no_argument, nullptr, 'h'},
    {"version", no_argument, nullptr, 'v'},

    {nullptr, 0, nullptr, 0},
};

static void usage() {
  std::cerr << "Usage: pwdgen [OPTION]..." << std::endl << std::endl;
  std::cerr << "Options:" << std::endl
            << "  -l, --length\t\tpassword length to generate" << std::endl
            << "  -c, --count\t\tpasswords to generate" << std::endl
            << "  -S, --no-symbols\tdo not include symbols" << std::endl
            << "  -D, --no-digits\tdo not include digits" << std::endl
            << "  -U, --no-uppercase\tdo not include uppercase characters" << std::endl
            << "  -L, --no-lowercase\tdo not include lowercase characters" << std::endl
            << "  --max-symbols <num>\tmax symbols to include" << std::endl
            << "  --max-digits <num>\tmax digits to include" << std::endl
            << "  --max-uppercase <num>\tmax uppercase characters to include" << std::endl
            << "  --max-lowercase <num>\tmax lowercase characters to include" << std::endl
            << std::endl;
}

int main(int argc, char* argv[]) {
  GenerationOptions pwd_opts;

  // digits of passwords to generate
  unsigned int count = 1;

  int c, opt_idx;
  while ((c = getopt_long(argc, argv, "vhSDLUc:l:", long_opts, &opt_idx)) != -1) {
    switch (c) {
      case 'c': {
        try {
          int val = std::stoi(optarg);
          if (val < 0) {
            throw std::invalid_argument("");
          }
          count = (unsigned int)val;
        } catch (const std::invalid_argument& ex) {
          std::cerr << "Invalid count argument" << std::endl;
          return EXIT_FAILURE;
        }
        break;
      }

      case 'l': {
        try {
          int val = std::stoi(optarg);
          if (val < 0) {
            throw std::invalid_argument("");
          }
          pwd_opts.length = (unsigned int)val;
        } catch (const std::invalid_argument& ex) {
          std::cerr << "Invalid length argument" << std::endl;
          return EXIT_FAILURE;
        }
        break;
      }

      case 'S': {
        pwd_opts.symbols = false;
        break;
      }

      case 'D': {
        pwd_opts.digits = false;
        break;
      }

      case 'L': {
        pwd_opts.lowercase = false;
        break;
      }

      case 'U': {
        pwd_opts.uppercase = false;
        break;
      }

      case MAX_SYMBOLS_OPTION: {
        try {
          int val = std::stoi(optarg);
          if (val < 0) {
            throw std::invalid_argument("");
          }
          pwd_opts.max_symbols = (unsigned int)val;
        } catch (const std::invalid_argument& ex) {
          std::cerr << "Invalid value passed for max-symbols argument" << std::endl;
          return EXIT_FAILURE;
        }
        break;
      }

      case MAX_DIGITS_OPTION: {
        try {
          int val = std::stoi(optarg);
          if (val < 0) {
            throw std::invalid_argument("");
          }
          pwd_opts.max_digits = (unsigned int)val;
        } catch (const std::invalid_argument& ex) {
          std::cerr << "Invalid value passed for max-digits argument" << std::endl;
          return EXIT_FAILURE;
        }
        break;
      }

      case MAX_UPPERCASE_OPTION: {
        try {
          int val = std::stoi(optarg);
          if (val < 0) {
            throw std::invalid_argument("");
          }
          pwd_opts.max_uppercase = val;
        } catch (const std::invalid_argument& ex) {
          std::cerr << "Invalid value passed for max-uppercase argument" << std::endl;
          return EXIT_FAILURE;
        }
        break;
      }

      case MAX_LOWERCASE_OPTION: {
        try {
          int val = std::stoi(optarg);
          if (val < 0) {
            throw std::invalid_argument("");
          }
          pwd_opts.max_lowercase = (unsigned int)val;
        } catch (const std::invalid_argument& ex) {
          std::cerr << "Invalid value passed for max-lowercase argument" << std::endl;
          return EXIT_FAILURE;
        }
        break;
      }

      case 'h': {
        usage();
        return EXIT_SUCCESS;
      }

      case 'v': {
        std::cerr << "pwdgen " << PROJECT_VERSION << std::endl;
        return EXIT_SUCCESS;
      }

      default:
        break;
    }
  }

  if (!pwd_opts.Validate()) {
    std::cerr << "Unable to generate password with provided parameters" << std::endl;
    return EXIT_FAILURE;
  }

  auto* pwd = new PasswordGenerator();
  for (unsigned int i = 0; i < count; ++i) {
    std::cout << pwd->GeneratePassword(pwd_opts) << std::endl;
  }
  delete pwd;

  return EXIT_SUCCESS;
}
