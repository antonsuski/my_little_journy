# Conclusion

Aggregate has a littlle bit different meaning in `C++`.
Aggreagates could be:
- arrays
- classes which have no:
    - user-defined constructors
    - privet or protected non-staic data members
    - virtual function

The struct's members can't be initillized by default. For make it possible you should brace initilization at struct definition. E.g.
```cpp
struct Point {
    int x{};
    int y{};
};
```
Then you can use **aggregate initialization** for initializing memebers. It does **memberwise initialization** which means that the memebres will be initialized in order of declaration. It is possible with using **list initializer** e.g.
```cpp
Point a = { 0, -1 }; // copy-list initialization
Point b{ 1, -5 }; // list initialization
```
There are some issue. If you add new field between `x` and `y` your initialization will be shifted and `y` will be initialized with `0`.

The best way to protect against that it is add new field in the end of definition of structure.
Also we have another way. It is to use **designated initializers** e.g.
```cpp
// It's avaliable with cxx20
Point a { .x{ 0 }, .y{ 2 }};
// or
Point b { .x = -2, .y = 5 };
Point c { .y{ 33 }, .x{ 11 }}; // compile error becasuse the initialization ordered are broken
```
You can easy copy a structure to another with assing, direct or brace initialization or you can just make assing. Also it's possible to make assigment with desgnated initializar.

