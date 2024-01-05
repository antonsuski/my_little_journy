# Conclusion

`std::string` is very usefull container. It is defined at `<string>` header. Syntax:
    
    std::string str {"Hello, world!"s};

Be aware of copying and passing by value. It is inefficiant cause the `std::string` will make a full
copy of passed string. The copying of C-string or another literal also accure with initialization.

This tell us that the string is dynamically allocate memmory with heap. And can change it's own size in
runtime.

Instead of passing `std:string` by value use `std::string_view` as function parameter.

`std::string` required be null-terminated. [cxx-std11]

Use `std::getline()` function for getting whole line from `stdin`.

> [!note]
> For preventing any leading before whitespaces use `std::ws` with `std::cin` e.g.
>   
>   std::string str {};
>   std::getline(std::cin >> std::ws, str);
