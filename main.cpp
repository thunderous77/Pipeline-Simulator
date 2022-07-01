#include "Execute.hpp"

using namespace std;

CPU mycpu;

int main() {
    mycpu.codeStore();
    mycpu.run();
}
