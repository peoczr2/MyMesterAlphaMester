/*
 * Átváltás tízes számrendszer és faktoriális számrendszer között.
 
Hint 1: || Tízesből faktoriálisba úgy tudsz váltani, hogy sorban osztasz 2-vel, 3-mal, 4-gyel és a maradékokat gyűjtöd. ||
Hint 2: || Visszafelé a számjegyek súlyai 1!, 2!, 3!, ... , ezért balról jobbra egy vegyes alapú kiértékelést kell csinálni. ||
*/

#include "../common.hpp"

static string to_factorial(int64 x) {
    if (x == 0) return "0";
    string digits;
    for (int base = 2; x > 0; ++base) {
        digits.push_back(char('0' + (x % base)));
        x /= base;
    }
    while (digits.size() > 1 && digits.back() == '0') digits.pop_back();
    reverse(digits.begin(), digits.end());
    return digits;
}

static int64 from_factorial(const string& s) {
    int64 value = 0;
    int base = 1;
    for (char c : s) {
        value = value * base + (c - '0');
        ++base;
    }
    return value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 a;
    string b;
    cin >> a >> b;
    cout << to_factorial(a) << '\n';
    cout << from_factorial(b) << '\n';
    return 0;
}
