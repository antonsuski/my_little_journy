There are 4 main numeral system in programming: decimal, octal, heximal, binary. In cxx you can define it with next speacial symbols. E.g:
```
int binary { 0b1101'0100 }; // binary integral interpretation
int octal { 0171'236 }; // octal integral interpretation
int hex { 0xa2b'3e'ff }; // hex integral interpreation
```
Also you can't just output numbers in hex, binary or octal interpretation. You have to call special fucntions for that or path flags into cout or cin object. E.g.:
> [!note]
> After you do hex outup the output interpreatio number doesn't chang. You have to do it manualy.
```
std::cout << std::hex << 9123 << std::endl;
```
