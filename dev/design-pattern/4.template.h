
struct Base
{
    virtual void A() = 0;
    virtual void B() = 0;
    virtual void C() = 0;

    void set_flags(bool b) { some_control_flag = b; }
    void template_func()
    {
        A();
        B();
        if (some_control_flag)
            C();
    }

private:
    bool some_control_flag;
};

struct A:Base{};// ...