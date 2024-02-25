# Conclusion

Here we can use non-type template function. It mean we can use some constexpr value for template function instantiation. E.g.
```cpp
template <int N> // instead of type name in template typename argumet use the bacis type.
void print(void) {
    std::cout << N << '\n';
}
```

There no way to define function with `constexpr` paramaters, you can just add `constexpr` qualifier for funcito's parameters. Some times you want to do this and we can use **non-type template argumets** it allow us to use **template typename arguments** as `constexpr` arguments.

Next entities can be non-type template argumets:
- integral types
- an enumartion tyepes
- `std::nulptr_t`
- floating types (since cxx20)
- pointer to some object
- pointer to some fuction
- pointer or reference to a member function
- a liter class type (since cxx20)

> [!warning]
> As for other fucntion and tempaltes convetsation works too. **This conversation can be cause of ambiguaty**.
> You can find full list at cppreference.com

For avoiding ambiguaty with conversation you can use `auto` instead dedicating of certaing type.

