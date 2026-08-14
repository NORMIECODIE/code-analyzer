#include <iostream>

void sayHello() {
    std::cout << "Hello";
}

int add(int a, int b) {
    return a + b;
}

int main() {

    if (true) {
        std::cout << "Inside if";
    }

    for (int i = 0; i < 5; i++) {
        std::cout << i;
    }

    while (false) {
        std::cout << "Loop";
    }
     std::cout << "Hello from the test project";

int x = 10;
int y = 20;
int result = x + y;

// your existing code...

    return 0;
}