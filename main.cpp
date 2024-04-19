#include <iostream>

int power(int x, int n) {
    int result = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            result *= x;
        }
        x *= x;
        n /= 2;
    }
    return result;
}

int main() {
    int x = 2; // podstawa potęgi
    int n = 10; // wykładnik potęgi
    int wynik = power(x, n);
    std::cout << wynik << std::endl;
    return 0;
}
