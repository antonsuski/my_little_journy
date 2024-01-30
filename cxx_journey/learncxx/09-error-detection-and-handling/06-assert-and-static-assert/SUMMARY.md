# Conclustion

`assert` is pre-definded macro wich terminate program when the condition expression false. In case of termination the `assert` macro terminate program with `std::abort()`. Therefore you can easly debug your program.

> [!hint]
> // If you want to ouput some text with assert do this:
> ```cpp
> #include <cassert>
> assert((1 < 0) && "One is bigger than zero!\n") // Put on string literal
> ```

`static_assert` is the keyword therefore it don't have to include <cassert> header file. `static_assert` evaluating at compile time. So the condition expression should be constexpr. E.g.
```cpp
static_assert(g == pi, "gravity is not equal to pi number");
```

> [!warning]
> The `assret` macro are works untill `NDEBUG` are defined. Othervise if `NDEBUG` are defined `assert` woun't works and will be skiped.

