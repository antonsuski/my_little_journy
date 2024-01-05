# Conclusion

## Inline fucntions

The *inline* keyword allow to embed code from declared fucntion directly in
caller. It can increase performance. For making this possible you must define your function, forward declaration isn't enough.
E.g.
> [!example]
> inline int max(int a, int b)
> {
>     return a > b;
> }

This mean that the function can have a multple definition.

> [!note]
> The best way is to not use *inline*. The reason is the compilers today can
> make decision by it self use or not use function with inline

## Inline variables

Variables wich was defined as *inline* works in same way as *inline* fucntions.
*inline* variables. It can be good replacement for C-style macro.
