# Conclusion

`constexpr if` statement with constant expression can be replased with one block of code, true or false regarding result of `if` statement. E.g.

```cpp
if constexpr(gravity == 9.8)
    std::cout << "it's ok << std::endl;
else
    std::cout << "it isn't ok" << std::endl;
```

