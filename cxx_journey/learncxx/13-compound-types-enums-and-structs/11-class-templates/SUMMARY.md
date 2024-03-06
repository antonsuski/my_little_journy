# Conclusion

Class templates are simillar to function templates. First of all you should declare tepmlate with typenemes. Then just use defined typenames in your struct definition. e.g.
```cpp
template<typename T>
struct Point {
    T x{};
    T y{};
};
```
While instantiation compiler will do the same procedure as for function template - type deduction. Be aware that the `typename` aren't type ot something else, it just type argument placeholder e.g.
```cpp
template<typename Point>
constexpr int max(Point p) {
    return p.x > p.y ? p.x : p.y;
}
```
If you call it with Point it woun't throw any error, because Point have members `x` and `y`, But you can also call this function with int and it will throw an error. Here `    Point` it just a type placeholder not a distinc type. `typename` Point will shadow `struct` Point.

Therefore beter to use simple letters for `typenames` like `T`,`U`,`V` etc. e.g.
```cpp
template<typename T>
constexpr T max(Point<T> p) {
    return p.x > p.y ? p.x : p.y;
}
```

