# Conclustion

Arithmetic conversion accures when you use arithmetic operations like `+,-,\` etc. In some reason almost all arithmetic operation requier that the both operands should be the same type.

In the case with different types it will be converted to the next order. On top is most higher priority in the bottom is most lowest prority.

 - long double (highest rank)
 - double
 - float
 - long logn
 - long
 - int (lowest rank)

The prority list above is managed by next rules:
- If rank of the unsignd operand higher than the rank of the signed operand, the signed operand will be converted into unsigned type.
- If signed variable isn't fit into unsigned, the unsiged will be converted into signed operand.
- Otherwise both operators will be converted into unsined.

