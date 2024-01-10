# Conclusion

Variables declared at top of file after includes at global namespace are called global variable.
It a good practice to add 'g' or 'g_' prefix to variable to detern that is global.

Global variables can be defined inside of user definded namespace but it still be global variable
which are called named global variable. It will be accessible in global namespace with using
user namespace where it was define.

