## Pattern matching in C++17 with `std::variant`

A straightforward implementation of a high-level pattern matching API using C++17 features such as template deduction guides, fold expressions and `std::variant` / `std::visit`.

### Example usage

```c++
std::variant<double, int, std::string> val = "test";

// Example usage:
match(val).on(
      [](const std::string& str)    { std::cout << "The value was a string: " << str << std::endl; },
      [](int i)                     { std::cout << "The value was an int: " << i << std::endl; },
      [](double d)                  { std::cout << "The value was a double: " << d << std::endl; }
);

// We can provide a default case by using the `auto` keyword, which matches all remaining types
val = 42;
match(val).on(
        [](const std::string& str)  { std::cout << "The value was a string: " << str << std::endl; },
        [](auto d)                  { std::cout << "The value was not a string: " << d << std::endl; }   // Default case
);

// Match all types in the variant
match(val).on(
        [](auto v) { std::cout << "Matches any type, got: " << v << std::endl; }
);


// We can even return values, however we must make sure that all lambdas return a value of the same type
val = "25.0";
auto res =
    match(val).on(
        [](const std::string& str)  { return std::atof(str.data()) * 2; },
        [](auto num)                { return num * 2.0; }
);
std::cout << "Got value " << res << std::endl;
```
