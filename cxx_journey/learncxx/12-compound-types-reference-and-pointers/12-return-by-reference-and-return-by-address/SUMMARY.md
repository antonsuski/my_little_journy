# Conclustion

Return by reference it is an interesting tool. But you should remeber that the function which retutrn reference should renternt reference to variable that will be alive beyond the function call. Otherwicse it will return **dangling reference** and you will get ub when try to get access.

The **lifetime extension** doesn't work with retunr value from function.

Caller can modify result of function if it makes return by non-const reference.

> [!note]
> Avoid return non-const static variable. It can cause of some logic issues.

Return by addres works simmilar. Prefere retnrun by reference.

