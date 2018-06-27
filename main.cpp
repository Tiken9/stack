#include <iostream>
#include "vector.h"

int main() {
    int a = 5;
    int b = 12;
    Vector<int> AS(7, a);
    Vector<int> SD(4, b);

    printf("%d", AS[400]);
    return 0;
}