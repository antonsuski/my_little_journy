# Conclusion

All prety clear. There is several types of cast:
 - C-style cast
 - `static_casti`
 - `const_cast`
 - `reinterpret_cast`
 - `dynamic_cast`
 
C-style cast is a dangeorouse thing because it could use all types of cast. `static_cast` one of the harmless, because it's don't affect on `const` qualifier and can cast basic types at **compile time**.

Another three cast have some issue. So use if you realy realize what you do.

