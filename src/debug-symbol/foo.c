int foo(int a, int b) {
    int c;
    static double d = 5.0;
    c = a + b;
    return c;
}

int global_int_data;
char global_chars_data[10]={1,2,4,8};
int main() {
    global_int_data=0;
    global_int_data=global_chars_data[0];
    int r;
    r = foo(2, 3);
    return 0;
}

