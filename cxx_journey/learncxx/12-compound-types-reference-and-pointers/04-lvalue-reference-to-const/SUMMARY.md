# Conclusion

The `l-value refenrece` can reference to `const` objects. In this case it will provide reference with read only access. There are some feature to make `const l-value reference` to r-value. This feature make lifete-time extension cause all r-values will be destroyid at the end of expression. **Life-time** extension is a mechanism for protecting agains **dangling reference**.

> [!warning]
> Be aware. Not all r-value coud be life extended. E.g. returning const reference from function.

