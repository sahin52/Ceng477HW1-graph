#include <iostream>
#include <stdarg.h>
int f(int, ... );

int f(int, ... ) {
    return 0;
}

int g() {
        f(1,2,3);
        return 0;
}

void TEST(){
    throw(3);
}

int main(){
    std::cout<<"-------------------------------START--------------------\n";
    TEST();
    std::cout<<"-------------------------------END-----------------------\n";
}