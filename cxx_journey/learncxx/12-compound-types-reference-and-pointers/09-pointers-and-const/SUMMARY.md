# Conclusion

Pointers can be refere to const variables and can be const itself. To declare `non-const pointer` to const value` use `const` qualifier before asterik e.g.

```cpp
const int a { 1 };
const int b { 2 };
const int* ptr_a { &a };
int* ptr_b { &b }; // compile error. you can't point to const value with non-const pointer as you can derefere pointer and change value.
```

If you want to make poiner const it self use const after asterik e.g.

```cpp
int a { 56 };
int b { 123 };
int * const ptr_a { &a }; // as const variables the const pointer should be initialized.
*ptr_a = 1; // ok; you can derefer and change value;

ptr_a = &ptr_a; // compile error
```

You can also make const pointer wich would be point to const variable e.g.

```cpp
const int a { 123 };
const int * const { &a };
```

