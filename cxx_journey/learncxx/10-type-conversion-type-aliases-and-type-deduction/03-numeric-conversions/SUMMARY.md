# Conclusion

There are five basic types of conversions:
 - from integaral to types who have lower types
 - floating point types to any other floating point types (excluding floating point promotion)
 - signed types to unsigned
 - converting integral type to any floating point types
 - converting integral and floating point types to boolan.

Converting integral types to lower types woks ok till integral can fit into range of another type.
In another way it will cut off value.

Converting floagint point types to any other floating point types e.g. from double to float. In this case value can lost his pricision.

Converting signed types to unsigned same types can overflows destination value. In vice versa case convertin from unsigned to signed have undefined bihaviour (it was prior to cxx20).

In some way ther is nothing to convert integral type into float type. By the way it will works ok till your integral type have lower size then the floating point. In the case when integral type have the same size with floating type here you will occure lost in presision if try to convert from 8 byte `int` to 8 byte `double` and back again. Converting from floating point to integral leads to lossing precision.

> [!warning]
> All of this conversions are safe and undsafe potentialy. Be carefull when using it.

