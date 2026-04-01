/*
Megoldas lenyege:
Vegigolvassuk a meresi pontokat, es a 800 cm alatti vagy egyenlo ertekekbol allo maximalis
folytonos szakaszokat gyujtjuk ki. Ezek adjak az arvizmentes folyosszakaszokat. A hosszukat
kulon eltesszuk, hogy a szakaszok szama, hatarai, hossza es az atlag is egyszerre kiirhato
legyen.
*/
/*
Hint 1: || Csak azokat a pontokat kell egy szakaszba tenni, ahol az érték legfeljebb 800. ||
Hint 2: || Egy új árvízmentes szakasz mindig akkor kezdődik, amikor egy korábbi magas pont után ismét alacsony értéket látunk. ||
Hint 3: || Az átlaghoz elég a szakaszhosszak összegét és a darabszámot eltárolni. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct FastScanner {
    static const int BUFSIZE = 1 << 20;
    int idx = 0, size = 0;
    char buf[BUFSIZE];

    inline char getChar() {
        if (idx >= size) {
            size = (int)fread(buf, 1, BUFSIZE, stdin);
            idx = 0;
            if (size == 0) return 0;
        }
        return buf[idx++];
    }

    template <typename T>
    bool readInt(T &out) {
        char c;
        T sign = 1;
        T val = 0;
        c = getChar();
        if (!c) return false;
        while (c != '-' && (c < '0' || c > '9')) {
            c = getChar();
            if (!c) return false;
        }
        if (c == '-') {
            sign = -1;
            c = getChar();
        }
        for (; c >= '0' && c <= '9'; c = getChar()) val = val * 10 + (c - '0');
        out = val * sign;
        return true;
    }
};

static string formatAverage(long long sum, int count) {
    long long integerPart = sum / count;
    int exponent = 0;
    while (integerPart >= 10) {
        integerPart /= 10;
        ++exponent;
    }

    __int128 scale = 1;
    for (int i = 0; i < 16; ++i) scale *= 10;
    for (int i = 0; i < exponent; ++i) scale /= 10;

    __int128 numerator = (__int128)sum * scale;
    __int128 rounded = (numerator * 2 + count) / (2 * count);

    __int128 limit = 1;
    for (int i = 0; i < 16; ++i) limit *= 10;
    while (rounded >= 10 * limit) {
        rounded /= 10;
        ++exponent;
    }

    __int128 whole = rounded / limit;
    __int128 frac = rounded % limit;

    ostringstream out;
    out << ' ' << (long long)whole << '.';
    string digits = to_string((long long)frac);
    if ((int)digits.size() < 16) digits = string(16 - (int)digits.size(), '0') + digits;
    out << digits << 'E' << '+';
    string exp = to_string(exponent);
    if ((int)exp.size() < 4) exp = string(4 - (int)exp.size(), '0') + exp;
    out << exp;
    return out.str();
}

int main() {
    FastScanner fs;
    int n;
    if (!fs.readInt(n)) return 0;

    vector<int> starts;
    vector<int> ends;
    vector<int> lengths;
    starts.reserve(n);
    ends.reserve(n);
    lengths.reserve(n);

    int currentStart = -1;
    int currentLength = 0;

    for (int i = 1; i <= n; ++i) {
        int a;
        fs.readInt(a);
        bool safe = a <= 800;
        if (safe) {
            if (currentStart == -1) currentStart = i;
            ++currentLength;
        } else {
            if (currentStart != -1) {
                starts.push_back(currentStart);
                ends.push_back(i - 1);
                lengths.push_back(currentLength);
                currentStart = -1;
                currentLength = 0;
            }
        }
    }

    if (currentStart != -1) {
        starts.push_back(currentStart);
        ends.push_back(n);
        lengths.push_back(currentLength);
    }

    int k = (int)starts.size();
    cout << k << '\n';
    if (k == 0) return 0;

    for (int i = 0; i < k; ++i) {
        if (i) cout << ' ';
        cout << starts[i] << ' ' << ends[i];
    }
    cout << ' ' << '\n';

    for (int i = 0; i < k; ++i) {
        if (i) cout << ' ';
        cout << lengths[i];
    }
    cout << ' ' << '\n';

    long long sum = 0;
    for (int len : lengths) sum += len;
    cout << formatAverage(sum, k) << '\n';

    return 0;
}
