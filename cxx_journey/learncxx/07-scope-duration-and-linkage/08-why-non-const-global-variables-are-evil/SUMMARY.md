# Conclusion

Generaly using of global non-constatn variable is bad idea. In small programs it's ok, but in large codebase it make problems.

> [!note]
> Try to use local variables instaed of global

At runtime the program start within not from main. Before main function it will invoke **static initialization** and then **dynamic initialization**. Global and Static variables are initialized at **static initialization**. Therefore global variable will be initialized with 0.

> [!warning]
> If you initialize your global value it can cause a problems.

> [!best practice]
> If you use global constatns it's a good way to make internal constants with constexpr and make for them some interface for access

