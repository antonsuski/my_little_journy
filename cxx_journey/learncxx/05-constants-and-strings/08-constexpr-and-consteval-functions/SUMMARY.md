# Conclustion

> [!note]
> All *constexpr* function are implicitly *inline*.

## Constexpr function and variables

Good way to define constatn it use the *constexpr* keyword which will implement your constatn value
directly in code. If compiler occure *constexpr* in compiletime it will be replaced with actual value.
For make it possible you have to use next syntax:

> [!example]
> constexpr float pi = 3.14f;

The *constexpr* function is more usefull cause *constexper* functions can be evaluated at compile-time.
From one hand that get us grate perfomance at run-time and from other hand it increase compile-time
due to fucntion evaluation.

> [!note]
> The *constexpr* functions not always are evaluating at compile-time.
> There are a few cases:
>  1. Espesialy if this one used with run-time function as its arguments.
>  2. If *constexpr* function call run-time function inside.
>  3. With usual call ther is no guaranty that the *constexpr* functino will evaluate at compile-time.
>  4. If *constexpr* function gets non-constexpr values.

If you want to make it you have to devine *constepr* variable and initialize it with *constexr*
function.

There is a good way to find out where is the fucntion are evaluated at compile-time or runtime:
***std::is_constatn_evaluated()*** - tell us if funciton evaluated at compile-time. It usefull for
use if you want to call runtime funciton insede *constexpr* function ar runtime or not in compile-time.

## Consteval

*consteval* says to compiler evaluate expresssion in run-time. Be aware that the *consteval* variables
have to be *constexpr*.
