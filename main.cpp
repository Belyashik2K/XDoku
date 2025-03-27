#include <iostream>

class XDoku {
    public:
    XDoku() {
        std::cout << "XDoku." << std::endl;
    }
    ~XDoku() {
        std::cout << "Soon." << std::endl;
    }
};

int main() {
    XDoku var;
    return 0;
}