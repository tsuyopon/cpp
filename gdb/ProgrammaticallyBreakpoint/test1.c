
void main(int argc, char** argv)
{
    asm("int $3");    // 「__asm__("int $3");」としても動作する
    int a = 3;
    a++;  //  In gdb> print a;  expect result to be 3
}
