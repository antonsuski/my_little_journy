# Conclusion

Identifier's linkage is a property of variable or function identifier which detern whether other
declarations of that name refer to the same object or not.

Global variables defined in source code with `static` keyword are linkage internaly. `static`
key word is a **storage class specifier**. Function wich was declared as `static` have an
internal linkage too.

Constant and constexpr glabal variable have internal linkage implicitly.

> [!best practice]
> Today is a good way to make internal linkage vaiable of function is to use `unnamed namspace`

