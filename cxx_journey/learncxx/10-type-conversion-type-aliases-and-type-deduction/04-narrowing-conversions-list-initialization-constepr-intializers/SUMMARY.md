# Conclusion

Narrowing conversion is defenitly unsafe and are cause issues with lossing precision. By default narrowing conversion accure in next cases:

- Integral conversion to smaller integraly types;
- Floating point to integral types conversions unless the source value are constexpr and is in the range of destintion value;
- Floating point to floation point with less size unless the source value are constexpr and is in the range of destination value;
- Integral conversion to Floating type with the same size;

> [!note]
> Brace(uniform) initiliazation prevetn from narrow conversion. Unless initializer are being converted explicitly.

> [!warnig]
> The list initialization prevent narowing conversion till the initializer aren't fit in destination variable.

