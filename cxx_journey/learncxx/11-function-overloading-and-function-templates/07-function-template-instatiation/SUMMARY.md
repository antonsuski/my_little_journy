# Conclusion

When compiler occure call of template function it make generic function each time. This proces is called **tmeplate instantiation**.
During instantiation compiler it will do **template argumet deduction**. If there are exists overloaded non-template function bisided overloaded template function the complier will choose non-template overloaded function.

Also the function template can be defined with out any template argumets. E.g.
```cpp
template<typename T>
int sum(T a, double b)
```
> [!warning]
> Remember that the not all template function can be compiled. Some times funciton can do som rediculus work like adding 1 to std::string. At this cases the compel can throw an error.

For prevening from this type of logic and compile errors you can forbid this type of function template instance with keyword `delete` e.g.
```cpp
template<typename T>
T incr(T a);

template<>
std::string incr(std::string a) = delete;
```
Template don affected by ODR because the are implicity inlined.

> [!note]
> Prefer regular fucntion and overloading. But if you need to make repitedly actions with different data use `templates`

