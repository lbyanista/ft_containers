#include "vector.hpp"
#include <iostream>

int main(){

    // int a = 1;
    std::vector<int> v2(45, 33);
    ft::vector<int> v(v2.begin(), v2.end());
    // ft::vector<int> v(10, a);
    // ft::vector<int> v(10, int(a));
    // delete a;

    return 0;
}