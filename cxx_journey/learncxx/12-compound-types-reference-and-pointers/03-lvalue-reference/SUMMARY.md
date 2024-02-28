# Conclustion

The `l-value reference` are just an aliace for some variable there are not an object from compiler side. When compiler occure `l-value reference` it just replace it with referend. In some casese `l-value reference` can be stored in memmory but it still non-object. E.g.
```cpp
int x { 5 };
int& x_ref { x }; // As like a constants l-value reference should be initialized.
```

The `l-value reference` can not be reseated. It also can not be referenced to void type or same `l-value reference`. If you'll try to reassign reference you just update value of refered variable.

The `l-value reference` have a indepenent life time. But be aware the could be destroyied before referend. In this case nothing will be affected. In vice-versa case if refered would be destroyied before `l-value reference` you will get a **dangling reference** wich will be reference to destroyied variable.

> [!note]
> If you need reference wich can be an object or reseated use `std::refernce_wrapper`.
> It will be covered later.

