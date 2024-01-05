# Conclusion

`std::string_view` [cxx-std17] just a reference to `std::string` or C-style string or some string
literal. It provide read-only interface of string.
It usfull if you need to read-only access to string with out modifying value.

Be aware of dangling variables. If you return `std::string_view` which refer to local `std::string`
you will have a dangling view of destroyed string

`std::string_view` can not be converted in `std::string` implicitly. You must do it explicitly.
With using `static_cast` or `std::string` uniform initialization.

`std::string_view` supports `constexpr` expressions
