# Conclusion

`enum class` allow us to make scoped enumeration. The main difference between scoped and unscoped enumeration that the scoped enumaration are creating inside some cope witch protect global space from pollution and name collision. Also scoped enumearations can't be implicet converted into integral types.

For making this possible you can use `static_cast` or `std::to_endlrlying()` functions.

In cxx17. Unlike unscoped enums scoped can be initilizaed with integral types through **brece initialization** without specifying base type and using `static_cast`.

In cxx20. You can use `using enum` for creating alices for long scope names.

