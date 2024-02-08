# Conclustion

This is an importatn thing to handel an inalid input. Usualy deter three types of handling.
- Reading full string from stdin. And handling.
- Validation each character wich wass put by user. And preventing to input wrong values.
- Reading one value. Than handling it.

There are several cases what and how to handle with invalid input.
- If input is meaming less. You can make iternal `while` loop and ask user to enter another value while it will be valid.
- If value have some invalid symbold e.g. `5a`.
```cpp
int x;
std::cin >> x // here we try to put 5a. the 5 will be extracted into x. And a will be stay in `stdin` stream and whating moment when it can be extracted.
// In this case you shoud to ignore symbols after 5. It can be achived with std::cin.ignore() function member. Here use std::numeric_limits.
```
- If extraction fails the `std::cin` will be alwas return with fail. In this case use `std::cin.clear()`. Remember that the `std::cin` returns `boolean` and you can use it in `if` statements for checking errors. E.g.
```cpp
int x;
std::cin >> x;
if(!std::cin)
    std::cin.clear();
```
- If user overflows integer value with a bit number. The `std::cin` alway put intp fail mode if overfolw is happaning. Use `clean()`.

