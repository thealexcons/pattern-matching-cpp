#include <iostream>
#include "match.h"

int main() {
    using namespace pm;

    std::variant<double, int, std::string> val = "test";

    // Example usage:
    match(val).on(
          [](const std::string& str) { std::cout << "The value was a string: " << str << std::endl; },
          [](int i) { std::cout << "The value was an int: " << i << std::endl; },
          [](double d) { std::cout << "The value was a double: " << d << std::endl; }
    );

    // We can provide a default case by using the `auto` keyword, which matches all remaining types
    val = 42;
    match(val).on(
            [](const std::string& str) { std::cout << "The value was a string: " << str << std::endl; },
            [](auto d) { std::cout << "The value was not a string: " << d << std::endl; }   // Default case
    );

    // Match all types in the variant
    match(val).on(
            [](auto v) { std::cout << "Matches any type, got: " << v << std::endl; }
    );

    // This doesn't compile: we need to provide an operation for all types in the variant.
    //    match(val).on(
    //            [](int v) { std::cout << "The value was an int: " << v << std::endl; }
    //    );

    // We can even return values, however we must make sure that all lambdas return a value of the same type
    val = "25.0";
    auto res =
        match(val).on(
            [](const std::string& str)  { return std::atof(str.data()) * 2; },
            [](auto num)                        { return num * 2.0; }
    );
    std::cout << "Got value " << res << std::endl;

}
