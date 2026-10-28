/*
Megoldás lényege: N bástya egymást nem ütő elhelyezésénél minden sorban és minden oszlopban pontosan egy bástya áll,
így a sorokhoz rendelt oszlopok sorozata az 1..N számok egy permutációja, és fordítva: minden permutáció egy érvényes elhelyezés.
Az összes permutációt a std::next_permutation adja lexikografikus sorrendben, ezért a kimenet sorrendje a mintával egyezik.
A sorokat egy karaktertömbből, fwrite-tal írjuk ki, mert a cout nagy kimenetnél lassú.
Az időigény O(N · N!), mert N! sort írunk ki N számmal; N = 10 esetén mintegy 3,6 millió sor, ami a 0,2 másodperces limiten belül marad.
*/
/*
Hint 1: || Egy bástya sem maradhat ugyanabban az oszlopban, ezért minden sorhoz
egyetlen oszlopot választunk. ||
Hint 2: || Az összes jó elhelyezés pontosan az 1..N permutációja. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    char sor[64];
    do {
        int len = 0;
        for (int i = 0; i < n; ++i) {
            if (i) sor[len++] = ' ';
            if (p[i] >= 10) sor[len++] = '1';  // N <= 10: a 10 kétjegyű
            sor[len++] = char('0' + p[i] % 10);
        }
        sor[len++] = '\n';
        fwrite(sor, 1, len, stdout);
    } while (next_permutation(p.begin(), p.end()));
    return 0;
}
