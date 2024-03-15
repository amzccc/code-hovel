#include <complex>          //复数库
#include <iostream>
#include <cstdlib>
#include <limits>

using namespace std;

int main()
{
    complex<long double> c1, c2;
    while(cin.peek() != '\n') {
        cout << "complex number c1: ";
        cin >> c1;
        if(!cin) {
            cerr << "input error, input format: (Rm, Im)" << endl;
            return EXIT_FAILURE;
        }
        cout << "complex number c2: ";
        cin >> c2;
        if(!cin) {
            cerr << "input error, input format: (Rm, Im)" << endl;
            return EXIT_FAILURE;
        }
        if(c1 == c2) {
            cout << "c1 and c2 are equal !" << endl;
        }
        cout << "c1 raised to the c2: " << pow(c1, c2) << endl;
        //跳过剩余行
        cin.ignore(numeric_limits<int> ::max(), '\n');
    }
}