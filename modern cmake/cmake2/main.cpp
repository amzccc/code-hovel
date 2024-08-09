#include <iostream>

using namespace std;

int main() {

#ifdef IS_LINUX
    cout << "hello, linux!\n";
#elif IS_WINDOWS
    cout << "hello, windows!\n";
#endif
    
    return 0;
}