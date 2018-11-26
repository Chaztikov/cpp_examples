https://en.cppreference.com/w/cpp/language/parameter_pack

template<typename ...Ts, typename U, typename=void>
void valid(U, Ts...);     // OK: can deduce U
// void valid(Ts..., U);  // Can't be used: Ts... is a non-deduced context in this position
 
valid(1.0, 1, 2, 3);      // OK: deduces U as double, Ts as {int,int,int}


template<class ...Us> void f(Us... pargs) {}
template<class ...Ts> void g(Ts... args) {
    f(&args...); // “&args...” is a pack expansion
                 // “&args” is its pattern
}
g(1, 0.2, "a"); // Ts... args expand to int E1, double E2, const char* E3
                // &args... expands to &E1, &E2, &E3
                // Us... pargs expand to int* E1, double* E2, const char** E3


If the names of two parameter packs appear in the same pattern, they are expanded simultaneously, and they must have the same length:

template<typename...> struct Tuple {};
template<typename T1, typename T2> struct Pair {};
 
template<class ...Args1> struct zip {
    template<class ...Args2> struct with {
        typedef Tuple<Pair<Args1, Args2>...> type;
//        Pair<Args1, Args2>... is the pack expansion
//        Pair<Args1, Args2> is the pattern
    };
};
 
typedef zip<short, int>::with<unsigned short, unsigned>::type T1;
// Pair<Args1, Args2>... expands to
// Pair<short, unsigned short>, Pair<int, unsigned int> 
// T1 is Tuple<Pair<short, unsigned short>, Pair<int, unsigned>>
 
typedef zip<short>::with<unsigned short, unsigned>::type T2;
// // error: pack expansion contains parameter packs of different lengths
// If a pack expansion is nested within another pack expansion, the parameter packs that appear inside the innermost pack expansion are expanded by it, and there must be another pack mentioned in the enclosing pack expansion, but not in the innermost one:

template<class ...Args>
    void g(Args... args) {
        f(const_cast<const Args*>(&args)...); 
 // const_cast<const Args*>(&args) is the pattern, it expands two packs
 // (Args and args) simultaneously
 
        f(h(args...) + args...); // Nested pack expansion:
   // inner pack expansion is "args...", it is expanded first
   // outer pack expansion is h(E1, E2, E3) + args..., it is expanded
   // second (as h(E1,E2,E3) + E1, h(E1,E2,E3) + E2, h(E1,E2,E3) + E3)
}

// Expansion loci
// Depending on where the expansion takes place, the resulting comma-separated list is a different kind of list: function parameter list, member initializer list, attribute list, etc. The following is the list of all allowed contexts


// Function argument lists
// A pack expansion may appear inside the parentheses of a function call operator, in which case the largest expression or braced-init-list to the left of the ellipsis is the pattern that is expanded.

f(&args...); // expands to f(&E1, &E2, &E3)
f(n, ++args...); // expands to f(n, ++E1, ++E2, ++E3);
f(++args..., n); // expands to f(++E1, ++E2, ++E3, n);
f(const_cast<const Args*>(&args)...);
// f(const_cast<const E1*>(&X1), const_cast<const E2*>(&X2), const_cast<const E3*>(&X3))
f(h(args...) + args...); // expands to 
// f(h(E1,E2,E3) + E1, h(E1,E2,E3) + E2, h(E1,E2,E3) + E3)