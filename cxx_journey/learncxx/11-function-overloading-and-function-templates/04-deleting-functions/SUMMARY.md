# Conclustion

The key word `delete` can be used for deletting function. `= delete` means you forbid this, not it doesn't exists" E.g.

```cpp
void foo(int a)
{
    printf("%i", a);
}

void foo(double a)
{
    printf("%d", a);
}

void foo(int) = delete;
```

It's very suitable when you whant to ban using of function.

> [!warning]
> Remember that the deleted function are still participiate in all stages of function resolution.

If you want to forbid all overloadings and make straitway using of one certain function with same function's parameters type you cat make next:

```cpp
template<typename T>
void foo(T a) = delete;
```

