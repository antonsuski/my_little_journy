# Conclusion

Unscoped enumeration it is enumartion wich are defined in global scope. There some problems it pollut global scope and increase name collision chance.

For decrease name collision chance use `namespace` for defning `enum` inside some scope. There are another way to make scoped enumaration it is declare them inside class. Or inside function, enumarations declared inside function are shadowing same names from outer scope.

The names inside enumeration are implicilty convert into integral type.
Enumaration works with comparing operators like `operatol==` and `operator!=`.

