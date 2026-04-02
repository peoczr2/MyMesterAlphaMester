/*
Megoldás:
Az állapotot egy N bites maszk írja le: az i-edik bit 1, ha az i-edik üregben van kavics.
Egy állapotból minden lehetséges 011 -> 100 és 110 -> 001 lépést kipróbálunk, és rekurzívan
meghatározzuk, hogy abból az állapotból legjobb játékkal minimum hány kavics maradhat.

Mivel N legfeljebb 20, legfeljebb 2^20 különböző állapot létezik, ezért a teljes keresés
memoizálással biztonságosan lefut. Az átmenetek száma állapotonként O(N), így a megoldás
O(N * 2^N) időben és O(2^N) memóriával működik.
*/
/*
Hint 1: || A játékállás nagyon természetesen leírható bitmaszkkal, mert minden helyen csak az számít, van-e kavics vagy nincs. ||
Hint 2: || Egy állapot értéke: a belőle elérhető végállások közül a legkisebb kavicsszám. ||
Hint 3: || Memoizálj minden maszkra, különben ugyanazokat az állapotokat sokszor újraszámolnád. ||
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int n;
vector<int> memo;

int solve(int mask) {
    int &answer = memo[mask];
    if (answer != -1) {
        return answer;
    }

    answer = __builtin_popcount(static_cast<unsigned>(mask));
    for (int i = 0; i + 2 < n; ++i) {
        int bits = (mask >> i) & 7;
        if (bits == 0b011) {
            int nextMask = mask;
            nextMask ^= (1 << i);
            nextMask ^= (1 << (i + 1));
            nextMask ^= (1 << (i + 2));
            answer = min(answer, solve(nextMask));
        }
        if (bits == 0b110) {
            int nextMask = mask;
            nextMask ^= (1 << i);
            nextMask ^= (1 << (i + 1));
            nextMask ^= (1 << (i + 2));
            answer = min(answer, solve(nextMask));
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> n >> s;

    int startMask = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            startMask |= (1 << i);
        }
    }

    memo.assign(1 << n, -1);
    cout << solve(startMask) << '\n';
    return 0;
}