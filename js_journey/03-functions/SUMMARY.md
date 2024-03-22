# Conclusino

## Defining a Functions
Ther are a few ways to defiene function:
```js
// 1. bind function to some variable
const let max = function(a, b){ return a > b ? a : b;};
// 2. define function with out binding
function sum(arr){
    let acc;
    for(i of arr){
        acc += i;
    }
    return acc;
}
// 3. make arrow fucntion
let arrow_foo = (x, y) => {return x + y};
```
The arrow function can be defined inside some calls.

## Binding and Scope
Nothing new.

## Nested Scope
Noting new.

## Function as values
You can unbind functions if it was.

## Declaration Notation
When you define function without binding like this:
```js
function sum(){}
```
The function will be accessible from whole module. The functions defineed with bindgs are accessabled from moment of declaration.

## Arrow functions
They are very suitable. And shown in [Dedfining a Function] section

## Call Stack
Nothing new

## Optional arguments
If you pass more than neeeded argumets thet will be ignored. Also you can make default arguments for function e.g.
```js
function foo(a = (x, y) => x + y;);
```

## Closure
It some mechanism to treat functions as values with their enviromnet wich recreated each call.

## Recursion
Nothing new.

## Growing functions
It's kind of paradigm. Where you need to split your function to more little functions.

## Functions and side effect
Ther are functions with side effect and pure functions in JS. Pure functions it's a function that doesn't change incommig arguments and return result. Functions with side effect it's functions which can affect on thier incomming data.
