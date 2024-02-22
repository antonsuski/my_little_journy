# Conclustion

If you want to make mulitple typename template parameteres add another typename argumet in temaplate definition. E.g.
```cpp
template<typename T, typename U>
T summ(T x, U y) {
    return x + y;
}
```

> [!note]
> Be aware in case wich was considered above in return value can occure narrowing version. E.g. if you pas `int` and `double` types firstly it would converted into `double` with **arthmetich conversion** and then retunr typte will be converted into `int` with **narrowing conversion**.

For avoiding this you can use keyword `auto` and get to compiler deduce return type by it self. E.g.
```cpp
template<typename T, typename U>
auto summ(T x, U y) {
    return x + y;
}
```

There are we have **abbreviated function tepmplates** with cxx20. Which get us more concise syntax.
```cpp
auto sum(auto x, auto y) { // here compiler will process it like template with multiples types
    return x + y;
}
```
Feel free to use **abbreviated function teplates**.

