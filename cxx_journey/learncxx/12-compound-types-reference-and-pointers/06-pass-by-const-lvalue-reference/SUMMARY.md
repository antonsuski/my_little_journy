# Conclusion

Passing by `const l-value reference` is a strong enough. Becaus it saves us from heavy copieng. In same time accessing by reference is slightly slower than the regural object access.

> [!note]
> In some cases compiler can optimize by it self argumets wich was passed by value.

> [!note]
> As rule of bit thumb. If copying is chap and dont requier of allocatoion of additional resources you can alwas pas by value, especialy basic typs. In other case use `const l-value reference` if you need read-only interface or `std::string_view` for strings.

