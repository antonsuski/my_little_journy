function print_type( variable ) {
    console.log(`\'${variable}\' is a ${typeof variable}`)
}

a = 100
pi = 3.14
str = "Hello, world"
bool = true

console.log('####################################################print_types')
print_type(a)
print_type(pi)
print_type(str)
print_type(bool)

console.log('########################################################strings')
literal_template = `hello.\nliteral temlate. Pi = ${pi}`
single_quotes = 'hello.\nsingle quote string. Pi = ${pi}'
double_quotes = "hello.\ndouble quote string. Pi = ${pi}"

console.log(literal_template)
console.log(single_quotes)
console.log(single_quotes)

console.log('####################################################print_types')
print_type(literal_template)
print_type(single_quotes)
print_type(double_quotes)

console.log('####################################conversions with comparison')
console.log('1' == 1)
console.log('1' === 1)

console.log('##########################shrot-circuiting of logical operators')
console.log(null || "rhs")
console.log("lhs" || "rhs")

console.log(undefined && "rhs")
console.log("lhs" && "rhs")

console.log(null ?? "rhs")
console.log("lhs" ?? undefined)
console.log("lhs" ?? "rhs")
