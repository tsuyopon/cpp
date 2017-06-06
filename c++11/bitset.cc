#include <bitset>
#include <climits>
#include <iostream>

int main()
{
    char a = 0x0a;
    char b = 0x0f;

    std::bitset<CHAR_BIT> as(a);
    std::bitset<CHAR_BIT> bs(b);
    std::bitset<CHAR_BIT> as_xor_bs(as ^ bs);
    std::cout << "a  (" << as        << "): " << as.count()        << '\n';
    std::cout << "b  (" << bs        << "): " << bs.count()        << '\n';
    std::cout << "a^b(" << as_xor_bs << "): " << as_xor_bs.count() << '\n';
}
