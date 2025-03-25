#include <bits/stdc++.h>
using namespace std;

string to_base_62(unsigned long long num) {
    const string base62 = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    string result = "";
    if (num == 0) return "0";

    while (num > 0) {
        int rem = num % 62;
        result = base62[rem] + result;
        num /= 62;
    }

    return result;
}

int main() {
    unsigned long long num = 64;
    string encoded = to_base_62(num);  
    cout << "Base62 encoding of " << num << " is: " << encoded << endl;
    return 0;
}
