# Conclusion

There are 2 types of numeric promotions:
 - floating-point promotion
 - integral promotion
 
The **floating-point promotion** is most easyer. If you try to pass or initilize etc. `double` type with `float`, the passed argumet wich is `float` will converted(promoted) to `double`.

The ****integral promotion** is a littel bit complicated. Here is the same idea as in **floating-point promotion**. The compiler will promote all smaller or simillar types into `int`. Bu it depends on your platform. If you have platform with 2 byte `int` the types like `signed char` or `char` could be promoted to `unsigned int`.

> [!note]
> The numeric promotions is value-preserved. That mean the value will be same as source.

