
struct A{
    A&Instance(){
        static A _a;
        return _a;
    }
    private:
    A(){}
};
