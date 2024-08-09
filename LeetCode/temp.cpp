#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int minLength(string s) {
    bitset<100> bm;
    int size = s.size();
    bm.reset();
    for(int i = 1; i < size; i++) {
        if(s[i] == 'B') {
            for(int j = i - 1; j >= 0; j--) {
                if(bm.test(j)) {
                   continue;
                }
                if(s[j] == 'A') {
                    bm.set(i, true);
                    bm.set(j, true);
                }
                break;
            }
        }
        else if(s[i] == 'D') {
            for(int j = i - 1; j >= 0; j--) {
                if(bm.test(j)) {
                   continue;
                }
                if(s[j] == 'C') {
                    bm.set(i, true);
                    bm.set(j, true);
                }
                break;
            }
        }
    }
    int res = 0;
    for(int i = 0; i < size; i++) {
        if(!bm.test(i)) {
            res++;
        }
    }
    return res;
}
int main() {
    string s{ "ABFCACDB" };
    cout << minLength(s) << std::endl;

    return 0;
}