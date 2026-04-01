/*
 * Átváltás 10-es és -10-es számrendszer között __int128 használatával.
 
Hint 1: || A `-10` alapú átváltásnál ugyanúgy ismételt osztás működik, csak a negatív maradékot korrigálni kell. ||
Hint 2: || Ha az osztás maradéka negatív lenne, adj hozzá 10-et, és növeld az új hányadost 1-gyel, hogy a számjegy 0 és 9 közé essen. ||
*/

#include "../common.hpp"

static __int128 parse_int128(const string& s) {
    __int128 value = 0;
    int sign = 1;
    size_t i = 0;
    if (!s.empty() && s[0] == '-') {
        sign = -1;
        i = 1;
    }
    for (; i < s.size(); ++i) value = value * 10 + (s[i] - '0');
    return sign * value;
}

static string to_string_int128(__int128 x) {
    if (x == 0) return "0";
    bool neg = x < 0;
    if (neg) x = -x;
    string s;
    while (x > 0) {
        int digit = (int)(x % 10);
        s.push_back(char('0' + digit));
        x /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}

static string to_neg10(__int128 x) {
    if (x == 0) return "0";
    string s;
    while (x != 0) {
        __int128 r = x % -10;
        x /= -10;
        if (r < 0) {
            r += 10;
            ++x;
        }
        s.push_back(char('0' + (int)r));
    }
    reverse(s.begin(), s.end());
    return s;
}

static __int128 from_neg10(const string& s) {
    __int128 value = 0;
    for (char c : s) value = value * (-10) + (c - '0');
    return value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string x_str, y_str;
    cin >> x_str >> y_str;
    __int128 x = parse_int128(x_str);
    cout << to_neg10(x) << '\n';
    cout << to_string_int128(from_neg10(y_str)) << '\n';
    return 0;
}
