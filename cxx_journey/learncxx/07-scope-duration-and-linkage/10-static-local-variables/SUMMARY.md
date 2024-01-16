# Conclusion

`static` key word makes variables are internal linkage. `static` variables are have **static duration**. Is mean that thew will be created at the start of programm and deleted in the end.

As `static` variables have internal linkage they accessible just in file scope where they were defined.

`static` variables are zero-initialized by default as global variables.

> [!warnning]
> This bad idea to make dynamic initialization for static variables. Cause ther is no strict order to make initialization for static variables. E.g.
> ```cpp
> static int a { 2 };
> static int b{ a }; // ambiguouse it can be zero-initialazed or initialized with 2
> ```
