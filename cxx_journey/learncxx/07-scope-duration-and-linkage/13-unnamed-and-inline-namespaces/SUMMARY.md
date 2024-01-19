# Conclusion

Unnamed `namespace` are adds all identifiers into parent namespace. But it has one interesting effect. All identifiers in unnamed namespace are treated as `static` and have internal linkage.

It's very usefull when you have a lot of `static` functions or variables to define them in a such way.

`inline namespace` does the same as unnamed `namespace`. But with one difference. It has no affect linkage. It's very convinient to use `inline namespace` when you need to make different version of one function.

Mixing `inline namespace` with unnmaed `namespace` (unnamed inside inline) give you same effect as `inline namespace` but with static linkage with explicit namespace that you can use.

