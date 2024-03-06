# Conclusion

You can use aliase for templates to make it easy to use them e.g.
```cpp
using Point = Pair<int>; // this aliase can be used into block
```

In another case you can use alias template e.g.
```cpp
template<typename T>
using Point = Pair<T>;

Point<int> p1 {1, 1}; // prior to cxx20 you have to explicitly specify all type template argumets
Point p2 {2, 2}; // here CTAD works
```

> [!warning]
> Don't forget that the CTAD doesn't work with function parameters.

