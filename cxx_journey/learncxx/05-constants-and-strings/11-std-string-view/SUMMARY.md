# Conclusion

Be aware while manipulation with `std::string`. Remmeber that `std::string_view` is only viewer of
refered string. Also `std::string_view` may be or not null-terminated. It occure when you get some
substring with removing some part of `std::string_view` because it refere at actual string with
null-terminator and next symbol of substring may be not a null-terminator.

> [!note]
> Remmeber this rule while working with `std::string`
> - Don't change refered variable. It make view invalid.
>   If you try to get access after that you'll get undefind behaviour.
> - If you change refered variable make revalidation (reasign) of `std::string_view`.
> - Be careful while returning `std::string_view`. Remmeber local variable are destroyed
>   in the end of expression.

