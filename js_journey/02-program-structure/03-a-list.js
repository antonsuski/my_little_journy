// This file is results of exercises
// A list.

function arrayToList(arr){
  let list = {value: arr[0], rest: null};
  let tail = list;
  //console.log("tail:", tail);
  for(let i = 1; i < arr.length; i++){
    tail.rest = {};
    Object.assign(tail.rest,{value: arr[i], rest: null});
    tail = tail.rest;
  }
  return list;
}

function listToArray(list){
  let arr = [];
  let head = list;
  while(list?.value){
    arr.push(list.value);
    list = list.rest;
  }
  //list = head;
  return arr;
}

function prepend(value, list){
  return {value: value, rest: list};
}

function nth(list, index){
  if(index < 0) return undefined;
  let it = list;
  Object.assign(it, list);
  let result = undefined;
  while(index >= 0){
    result = it;
    it = it.rest;
    index--;
  }
  return result.value;
}

console.log(arrayToList([10, 20,77,88]));
// → {value: 10, rest: {value: 20, rest: null}}
let list = arrayToList([10, 20, 30]);
console.log(listToArray(list));
//console.log("list after:", list);
// → [10, 20, 30]
console.log(prepend(10, prepend(20, null)));
// → {value: 10, rest: {value: 20, rest: null}}
console.log(nth(arrayToList([10, 20, 30]), 1));
// → 20

