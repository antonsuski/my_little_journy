# Conclusion

The good way to implement PRNG is to use one-header file with `namecpese` where we will define global variable PRNG and intialize it with expression. In this way global non-constant variable is exclusion from rule.

> [!note]
> Also for my opinon here if we want to use oop methodology we can use single tone for avoiding multiple reseeding of PRNG.

