# Conclusion

Good way to share global constants is to make them constexpr. The downside of constexpr that the are have internal linkage and we must recompile each translation unit where it was included every time when we change this variable. In large project it can be increase compile time.

To avoid recopilation each time when we change constatns we can use forward declaration to make global variables external linkage. It will reduce compile time. But now constatn expantion are unavaliable.

