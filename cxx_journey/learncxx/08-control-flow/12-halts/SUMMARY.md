# Conlcusion

> [!note]
> In general way all halts like std::exit(), std::abort(), std::terminate(), better isn't use.

- std::exit() terminate program in normal way with cleaninig static variables and etc...
> You can register your clean up function with std::atexit(); which will be invoked with std::exit();
> std::exit are implicitly called at return from main function. All registred fucntion will be invoked in reversed order (the last one will be called first).
> For program with threads it's more convinient to use **std::quick_exit()** and **std::at_quick_exit()** because they don't clear static variavles and you can clear them safty.
- std::abort() terminate program in abnormal way.
- std::terminate() usualy this function are called when exeption wasn't handled.

