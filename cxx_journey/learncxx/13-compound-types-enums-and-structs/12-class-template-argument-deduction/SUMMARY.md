# Conclusion

> [!note]
> Since cxx17

Class template argument deduction allow us to initialize template variable with out specifying template arguments e.g.
```cpp
#include<utility>

int main(int , char**) {
    std::pair<int, int> p1{1, 1}; // ok, we specify template arguments
    std::pair p2 {2, 2}; // ok, CTDA will deduce type of initializer.
}
```

> [!warning]
> **Only in cxx17**. CTDA woun't work with aggregates.

For make in possible you should user **deduction guide**. E.g.
```cpp
template<typename T>
struct Point {
    T x{};
    T y{};
};

template<typename T>
Point(T) -> Point<T>
```

> [!warning]
> CTDA doesn't work with function parameters and non-static memeber initialization.

Also you can use default template argumets e.g.
```cpp
template<typename T = int>
struct Point {
    T x {};
    T y {};
};

Point a; // will instantiate with int type by default
```
