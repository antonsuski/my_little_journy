# Conclusion

Unscoped enumartion are implicilty convert into integer and implicitly assigned from 0,1,2 etc. Enums could be explicitly assigned from value what you need inclusing negative values.

When you try to ouput enum it will convert into ingegral type and ouptut some number instead of name. For making this possible you need to teach `operator<<` or make some function for converting from enum to sertain name.

Whith input the same. You can't just do next:
```cpp
som_enum e;
std::cin >> e;
```
You should do next:
```cpp
some_enum e;
int a;
std::cin >> a;
e = staic_cast<some_enum>(a); // use static cast for input enums or overaload input operaotr >>
```

You can't assing integral type directly into enum. For making this possible you should declare **base type** for your enumeration. e.g.
```cpp
enum clor: int
{
    red,
    green,
    blue,
};
```
After that you can explicit initialize enumes with brace initializer with integral type.

