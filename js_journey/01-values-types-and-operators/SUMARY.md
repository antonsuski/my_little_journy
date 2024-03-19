# Conclusion

## Nmbers
In JS numers are numeric type.

## Arithmetic
Noting new.

## Special numbers
There are a few special numbers in JS:
- `Infinity`
- `-Infinity`
- `NaN` (not a number)

## Strings
There are three types of strings in JS:
- \`template literal\`
- "format ${string}" You can make some operations like concatination with `+` operation.
- 'non-modifiable string'

## Unary operators
`typeof` ofperator can ouput the type of operator. E.g.
```js
// → number
console.log(typeof 4)
// → string
console.log(typeof "x")

console.log(typeof 3.14)
console.log(typeof true)
```
oput:
```
number
string
number
boolean
```

## Boolean values
Nothing new. They are presist.

## Comparison
There only one value can't be equal be it self: `NaN`

## Logical operators
Nothing new

## Empty values
There are two empty values in JS: `null` and `undefined`

## Automatic type conversion

JS will automaticaly convert types.
> [!warning]
> You should remember that the `null` isn't equal to `0`. But the `null` is equal to `undefined`.
> `0` are also not equal to `false` nither `""` not equal to `false`. Because of automatic conversion.

> [!note] b.p.
> Prefere using `===` while comparing because it will comare type also

## Short circuiting of ligical operators

Opearators `&&` and `||` will can do some magic e.g.
```js
console.log(null || "user")
// user
console.log("Agnes" || "user")
// Agnes
```
Operator `||` convert both operands into boolean, but after that it will return original right or left value depends on results of comparing. The operator will return left operator if it can be converted into `bool` and right otherwise.

Operator `??` return right value if left operand equal to `null` or `undefined`.

Operator `&&` return left value  if can be converted into `false` otherwice it will return right value.

