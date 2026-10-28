/*
    A ritka számok bináris alakjában nincs két egymás melletti 1-es. Az adott
    bitszámú ritka számok darabszáma Fibonacci-sorozatot követ, ezért a keresett
    szám legfeljebb kb. 30 bites lehet. Először a bitszámot határozzuk meg: a
    rövidebb hosszúságú ritka számok darabszámát sorban levonjuk N-ből. Ezután a
    biteket balról jobbra döntjük el: 1-es után csak 0 állhat; egyébként
    megszámoljuk, hány ritka szám kezdődik 0-val az adott hosszban, és ha N ennél
    nagyobb, a bit 1 lesz, N-ből pedig levonjuk ezt a darabszámot.
    Időigény: O(log N).
*/
/*
Hint 1: || Egy adott bitszámú ritka számok darabszámát lehet összeadni a rövidebb hosszúságok darabszámaiból. Ha N-ből sorban levonod a rövidebb hosszúságok darabszámát, megtalálod a keresett szám bitszámát. ||
Hint 2: || Balról jobbra haladva, ha az előző bit 1, a következő csak 0 lehet. Különben számold meg, hány ritka szám kezdődik 0-val: ha N ennél kisebb vagy egyenlő, a bit 0, különben a bit 1, és N-ből levonod ezt a darabszámot. ||
Hint 3: || Előre számold ki egy tömbben: a 0-val kezdődő n bites ritka számok száma megegyezik az (n-1) bites összes ritka sorozat számával, az 1-essel kezdődőké pedig az (n-2) bites összes sorozatéval. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;
    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }
    --n;

    vector<long long> lenCnt(50, 0);
    vector<long long> suf0(50, 0), suf1(50, 0);
    suf0[0] = suf1[0] = 1;
    for (int i = 1; i < 50; ++i) {
        suf0[i] = suf0[i - 1] + suf1[i - 1];
        suf1[i] = suf0[i - 1];
    }
    for (int len = 1; len < 50; ++len) lenCnt[len] = suf1[len - 1];

    int len = 1;
    while (n > lenCnt[len]) {
        n -= lenCnt[len];
        ++len;
    }

    string bits;
    bits.push_back('1');
    int prev = 1;
    for (int pos = 2; pos <= len; ++pos) {
        int rem = len - pos;
        if (prev == 1) {
            bits.push_back('0');
            prev = 0;
        } else {
            long long zeroCnt = suf0[rem];
            if (n <= zeroCnt) {
                bits.push_back('0');
                prev = 0;
            } else {
                bits.push_back('1');
                n -= zeroCnt;
                prev = 1;
            }
        }
    }

    long long ans = 0;
    for (char c : bits) ans = ans * 2 + (c - '0');
    cout << ans << '\n';
    return 0;
}