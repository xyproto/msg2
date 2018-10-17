#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std::string_literals;

const auto versionString = "msg2 1.2.0"s;

const auto red = "\033[1;31m"s;
const auto blue = "\033[1;34m"s;
const auto bold = "\033[;1m"s;
const auto reset = "\033[0m"s;

inline auto contains(std::string const& a, std::string const& b) -> bool
{
    return a.find(b) != std::string::npos;
}

auto main(int argv, char** args) -> int
{
    if (argv > 1 && (args[1] == "-v"s || args[1] == "--version"s)) {
        std::cout << versionString << std::endl;
        return EXIT_SUCCESS;
    }

    std::stringstream ss;

    // Prepare a blue arrow followed by bold text
    ss << "  "s << blue << "->"s << bold;

    // If the first argument is a string containing one or more "%s",
    // use it as a format string where "%s"'s are replaced by the
    // following arguments.
    if (argv > 1 && contains(args[1], "%s"s)) {
        std::string s = args[1];
        while (contains(s, "%s"s)) {
            for (auto i = 2; i < argv; ++i) {
                auto pos = s.find("%s"s);
                if (pos != std::string::npos) {
                    // Replace %s with the ith argument. 2 is the length of "%s"
                    s.replace(pos, 2, args[i]);
                } else {
                    // Create a space separated string from the following arguments
                    std::stringstream argss;
                    for (auto j = 2; j < argv; ++j) {
                        argss << " "s << args[j];
                    }
                    std::cerr << red << "error: "s << reset
                              << "too many arguments for format string \""s << args[1] << "\":"s
                              << argss.str() << std::endl;
                    std::exit(EXIT_FAILURE);
                }
            }
            // All instances of "%s" should now be replaced
            if (contains(s, "%s"s)) {
                // Create a space separated string from the following arguments
                std::stringstream argss;
                for (auto j = 2; j < argv; ++j) {
                    argss << " "s << args[j];
                }
                std::cerr << red << "error: "s << reset
                          << "too few arguments for format string \""s << args[1] << "\":"s
                          << argss.str() << std::endl;
                std::exit(EXIT_FAILURE);
            }
        }
        ss << " "s << s;
    } else {
        // Create a space separated string from all arguments
        std::stringstream argss;
        for (auto i = 1; i < argv; ++i) {
            argss << " "s << args[i];
        }
        // Just use the arguments, without any formatting
        ss << argss.str();
    }

    // Reset colors
    ss << reset;

    // Output line
    std::cout << ss.str() << std::endl;
    return EXIT_SUCCESS;
}
