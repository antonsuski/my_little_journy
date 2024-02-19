# Conclusion

When function are overloaded the compiler will make funciton resolution:

 1. Compiler will try to make type deduction:
    2. Firstly compiler try to find out convinient delcaration of fucntion. If not, go next step.
    2. Then it try to make numeric promotion and try to findo out convient fuction.
    2. If it still not suitable it will try to make numeric conversion.
    2. Then if it steel no declarion it will try to find out user-defined conversion or type contructor (to make conversion with it).
    2. If it stell no matches compiler will try to find out ellipsis.
 1. If founded fucntion is the best match compiler will take it. Otherwise if no accurencec don't find or it has more than one suitable fucntion compiler will throw an error.

> [!note]
> If ambiguoutse match occure you can use explicit conversion for avoiding it.

