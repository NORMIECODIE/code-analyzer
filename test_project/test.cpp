#include <iostream>

void sayHello() {
    std::cout << "Hello";
}

int add(int a, int b) {
    return a + b;
}

int main() {

    // TODO: Improve error handling
    // FIXME: Refactor this function

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

    std::cout << result;

    return 0;
}

void complexTest() {

    if (true) {
        std::cout << "Condition 1";
    }

    if (true) {
        std::cout << "Condition 2";
    }

    for (int i = 0; i < 5; i++) {
        std::cout << i;
    }

    while (false) {
        std::cout << "Loop";
    }

    switch (1) {

        case 1:
            std::cout << "Switch";
            break;

        default:
            break;
    }
}