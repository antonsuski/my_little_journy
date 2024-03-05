# Conclusion

Struct can be nested. While using structures prefere to use safe structures. Be aware of dangle members.

Size of srtuctures can be optimized and padding by copiler. e.g.
```cpp
struct foo {
    int a{};
    short b{};
    double c{};
}
foo strct{};
std::cout << "int:" << sizeof(int) << "\n";
std::cout << "shrot:" << sizeof(short) << "\n";
std::cout << "double:" << sizeof(double) << "\n";

std::cout << "foo:" << sizeof(foo) << "\n";
```
Output:
```
int:4
short:2
double:8
foo:16
```
The compiler make padding after memeber `b` for optimization.

> [!note]
> You can minimize padding by defining your memebers in decreaseing order of size. It has to be done manualy

