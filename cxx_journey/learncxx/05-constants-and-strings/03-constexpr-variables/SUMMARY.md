# Conclusion

Sometimes it is hard to determ werether the expresion is **Compile Constant**
or **Runtime Constatn**. Keyword *constexpr* could help us with this. When you
try to initilaze *constexpr* value with runtime value the compiler will throw
an error e.g.
> [!example]
> // Here we don't know wherether get_value() will return value at compile
> // time or at runtime. So, if it return value at runtime, the compiler will
> // throw an error.
> constexpr int a { get_value() };

The const optimization will also works with subexpressions like:
> [!example]
> std::cout << 4+5 << std::endl;

It called **Constant Folding**

