# Conclusion

The `namespace` allow us to hide out some declaraiont of variable or function.
It protect from name collision.

Scope resolution operator `::` can be used with out namespace e.g.:

    // In this case copiler will try to find function in global scope
    ::print();

For resolving proble with long and nested namespaces you may use aliases e.g.

    namespace foo
    {
        namespace bar
        {
            void print();
        }
    }
   
    int main(){
        // Aliases are definded by keyword `using`
        using Alias = foo::bar;     
        Alias::print();
    }

Also aliases could be reassigned and refer to anotheer nested or not `namespace`
What can be wary useful if the namspeces of used library are changed.

