# Conclusion

Remeber when you passing by addres you pass just a copy of your addres. There fore all operation under pointer will no affect to argument. If you want to affect to pointer it slfe use reference to pointer e.g.
```cpp
void nullify(int*& ptr)
{
    ptr = nullptr;
}

`nullptr` has his own type `std::nullptr_t`. It can be used in fucntion overlaoding to define function that works with only `nullptr` argumenrs. Be aware that if you have `int*` to some value with assigned `nullptr` inside the compiler will call best match function like function with `int*` parameter instead fucntion with `std::nullptr_t` parameter. Because compiler will compare types while type deduction.

> [!note]
> Use `nullptr` isntead `0` or `NULL` macro. Cause this can lead some ambiguous.

