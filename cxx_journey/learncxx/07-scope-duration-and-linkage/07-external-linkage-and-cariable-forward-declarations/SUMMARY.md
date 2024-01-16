# Conclusion

All function by default have an external linkage. It provided by **forward declaration**.
Variables can also be forward declared. It achive with `extern` key word. Function don't need
`extern` key word for forward declaration.

> [!warning]
> Constexpr variables can't be forward declared. Because it must be initialized at compile-time.

Be aware that the `extern` depend on context.

    // math.hxx
    extern int g_x {1}; // global variable with external linkage

    // main.cxx
    extern int g_x; // forward declarion of global variable wich is defined somewhere else

