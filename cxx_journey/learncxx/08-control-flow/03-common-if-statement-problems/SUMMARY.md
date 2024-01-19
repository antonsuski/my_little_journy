# Conclusion

There is a few common problems.
- dangling else (when we use sigle-line `if-else` statements)
    > [!note]
    > `else statemets` will be paired with the last unmached `if statement`
- null statements `;` e.g.
    ```cpp
    if(is_true);
    {
        doSomething(); //this stateement will be ignored due to null statement above
    }
    ```
- assigne `operator=` istead of `operator==`
