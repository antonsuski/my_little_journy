# Conclusion

When ther is no some interapt statements like `break` or `return` there some **fallthrough** will occure.
> [!note] B.P.
> If you wanna to make **fallthroug** intentionaly use the [[fallthroug]] attribute e.g.
> ```
> swithc(num)
> {
>   case 1:
>     std::cout << "1" << std::endl;
>   [[fallthrough]];
>   case 2:
>     std::cout << "2" << std::endl;
> }

Be aware that the switch case and case lables wich was declared with out block will have common **scope**

Also you can declare and define variables but you can't initialize them. You can do this only after cale lable into the block.

