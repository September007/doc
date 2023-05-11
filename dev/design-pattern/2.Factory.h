
struct Interface{
    virtual int id()=0;
};

struct A:Interface{
    virtual int id(){return 'A';}
};
struct B:Interface{
    virtual int id(){return 'B';}
};
struct C:Interface{
    virtual int id(){return 'C';}
};


// 1. control by hand
Interface * Factory(char c){
    switch (c)
    {
    case 'A':
        return new A();
    case 'B':
        return new B();
    case 'C':
        return new C();
    default:
        return 0;
    }
}


// 2. compile time

#include <tuple> // record type lists
// assume there is a register process
// register manager
using MappedTypeId = int;
template<typename Type=void>
struct Id;

#define REGIS(TYPE, _id)        template<> struct Id<TYPE>{static constexpr int value = _id;}
REGIS(A,1);
REGIS(B,2);
REGIS(C,3);

template<typename Tuple,int index = 0>
Interface * RegisterFactory(MappedTypeId id){
    if(std::tuple_size<Tuple>() == index)
        return nullptr;
    using T0 = std::tuple_element_t<index,Tuple>;
    //using T1 = std::tuple_element_t<,Tuple>; 
    
    if(Id<T0>::value == id)
        return new T0{};
    else
        return RegisterFactory<Tuple,index+1>(id);
}
Interface * Factory2(MappedTypeId id) { return RegisterFactory<std::tuple<A, B, C>>(id); }

// there could be something make linking-list creation to binary-search creation
