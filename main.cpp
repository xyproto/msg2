#include <iostream>
#include <sstream>

using namespace std::string_literals;

auto main(int argv, char** args) -> int
{
    std::stringstream ss;

    // Prepare a blue arrow followed by white text
    ss << "  \033[1;34m->\033[1;37m"s;

    // Gather all commandline arguments
    for (auto i = 1; i < argv; ++i) {
        ss << " "s << args[i];
    }

    // Reset colors
    ss << "\033[0m"s;

    std::cout << ss.str() << std::endl;
    return 0;
}
