#include <iostream>
#include <string_view>

int main(int argc, char** argv)
{
    // empty lambda without capture and parametres
    []() { std::cout << "Empty lambda" << std::endl; };

    // lambda with parametr
    int a{ 1 };
    std::cout << "Before println_num a: " << a << std::endl;
    auto println_num = [](int val) {
        std::cout << "Lambda with direct value pass, val: " << ++val
                  << std::endl;
    };
    println_num(a);
    std::cout << "After println_num a: " << a << std::endl;

    // lambda with parametr
    auto println = [](const std::string_view& buffer)
    {
        std::cout << "Lambda with const reference parameter, buffer:" << buffer
                  << std::endl;
    };
    std::string str = "Heloo, world!";
    println(str);

    // generic lambda
    auto printlna = [](const auto& val)
    { std::cout << "Generic lambda val: " << val << std::endl; };
    printlna(2);

    // generic lambda and static variable
    auto println_gen_static = [](auto var)
    {
        static int call_count{ 0 };
        std::cout << call_count++ << ": " << var << std::endl;
    };

    println_gen_static("hello"); // 0: hello
    println_gen_static("from");  // 1: from

    println_gen_static(1); // 0: 1
    println_gen_static(2); // 1: 2

    println_gen_static("static"); // 2: static

    // return type deduction and trailing return types
    auto divide{ [](int x, int y,
                    bool intDivision) { // note: no specified return type
        if (intDivision)
            return x / y; // return type is int
        else
            return x / y;
        // return static_cast<double>(x) /
        //        y; // ERROR: return type doesn't match previous return
        // type
    } };

    std::cout << divide(3, 2, true) << '\n';
    std::cout << divide(3, 2,
                        false) // Uncomment previouse lines of code for
                               // instance
              << '\n';

    // lambda with declared return type
    auto multiple{ [](int x, int y) -> int { return x * y; } };
    std::cout << "lambda with int return type, 5 * 7: " << multiple(5, 7)
              << std::endl;

    return 0;
}
