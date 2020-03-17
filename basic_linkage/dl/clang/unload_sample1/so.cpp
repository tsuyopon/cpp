
inline
int b()
{
    static int x = 0;
    return x;
}

int a()
{
    return b();
}
