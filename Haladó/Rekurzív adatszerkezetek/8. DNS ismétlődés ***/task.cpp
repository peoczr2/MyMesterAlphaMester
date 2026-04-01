#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
A megadott DNS-szekvenciából minden K hosszú részsztringet végignézünk, és
megszámoljuk, melyik fordul elő a legtöbbször. K legfeljebb 20, ezért egy egyszerű
számkódolással a részsztringek gyorsan hash-elhetők.

Az A, C, G, T betűket 0, 1, 2, 3 értékre képezzük, és a K hosszú ablakot 2 bites
kód helyett 4-es számrendszerben tartjuk nyilván. Így minden részsztring egyetlen
egész számmal azonosítható.

Hint 1: || Minden K hosszú részsztringet csak egyszer kell kiolvasni az ablakos bejárással. ||
Hint 2: || Az A/C/G/T betűk helyett használhatsz 0..3 kódot, így gyors lesz az azonosítás. ||
Hint 3: || A legtöbbször előforduló rész mellett annak egy előfordulási helyét is meg kell őrizni. ||
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    string s;
    cin >> s;

    auto code = [](char c) {
        if (c == 'A') return 0;
        if (c == 'C') return 1;
        if (c == 'G') return 2;
        return 3;
    };

    if (K > N) {
        cout << 0 << ' ' << 1 << '\n';
        return 0;
    }

    unordered_map<long long, pair<int,int>> cnt;
    long long key = 0;
    long long base = 1;
    for (int i = 0; i < K; ++i) {
        key = key * 4 + code(s[i]);
        if (i + 1 < K) base *= 4;
    }

    auto touch = [&](int pos) {
        auto &p = cnt[key];
        ++p.first;
        if (p.second == 0) p.second = pos;
    };

    touch(1);
    for (int i = K; i < N; ++i) {
        key -= code(s[i - K]) * base;
        key = key * 4 + code(s[i]);
        touch(i - K + 2);
    }

    int bestCount = 0, bestPos = 1;
    for (auto &it : cnt) {
        if (it.second.first > bestCount || (it.second.first == bestCount && it.second.second < bestPos)) {
            bestCount = it.second.first;
            bestPos = it.second.second;
        }
    }
    cout << bestCount << ' ' << bestPos << '\n';
    return 0;
}