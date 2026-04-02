/*
Megoldás:
Először kibontjuk a nagy képet a futamhossz-kódolásból, mert N legfeljebb 1000, tehát az egész
N x N mátrix még kényelmesen elfér. Ezután a kis K x K mintát és a nagy képet is kétdimenziós
gördülő hash-sel vizsgáljuk.

Minden sorra kiszámítjuk a K széles részszakaszok hash-ét, majd ezekből oszloponként újabb gördülő
hash-sel kapjuk meg az összes K x K ablak hash-ét. Az első olyan pozíció lesz a válasz, ahol a hash
egyezik, és egy biztonsági közvetlen ellenőrzés is igazolja az egyezést.

Az algoritmus O(N^2) idejű és O(N^2) memóriájú.
*/
/*
Hint 1: || A futamhossz-kódolt nagy kép maximális mérete csak 1000 x 1000, ezért bátran ki lehet bontani. ||
Hint 2: || Először soronként keress K hosszú egyezéseket, és ezekből építs fel függőleges gördülő hash-t. ||
Hint 3: || Hash-egyezés után érdemes egy közvetlen K x K összehasonlítással kizárni az ütközéseket. ||
*/

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;

    vector<vector<int>> small(k, vector<int>(k));
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            cin >> small[i][j];
        }
    }

    int n;
    cin >> n;
    string line;
    getline(cin, line);

    if (k > n) {
        for (int i = 0; i < n; ++i) {
            getline(cin, line);
        }
        cout << 0 << '\n';
        return 0;
    }

    vector<vector<int>> large(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        getline(cin, line);
        while (line.empty()) {
            getline(cin, line);
        }
        stringstream input(line);
        int position = 0;
        int length, color;
        while (input >> length >> color) {
            for (int cnt = 0; cnt < length; ++cnt) {
                large[i][position++] = color;
            }
        }
    }

    const uint64_t BASE_ROW = 911382323ULL;
    const uint64_t BASE_COL = 972663749ULL;

    uint64_t powerRow = 1;
    for (int i = 1; i < k; ++i) {
        powerRow *= BASE_ROW;
    }
    uint64_t powerCol = 1;
    for (int i = 1; i < k; ++i) {
        powerCol *= BASE_COL;
    }

    vector<uint64_t> smallRowHash(k, 0);
    for (int i = 0; i < k; ++i) {
        uint64_t hash = 0;
        for (int j = 0; j < k; ++j) {
            hash = hash * BASE_ROW + static_cast<uint64_t>(small[i][j] + 1);
        }
        smallRowHash[i] = hash;
    }

    uint64_t patternHash = 0;
    for (int i = 0; i < k; ++i) {
        patternHash = patternHash * BASE_COL + smallRowHash[i];
    }

    int widthCount = n - k + 1;
    vector<vector<uint64_t>> rowHashes(n, vector<uint64_t>(widthCount));
    for (int i = 0; i < n; ++i) {
        uint64_t hash = 0;
        for (int j = 0; j < k; ++j) {
            hash = hash * BASE_ROW + static_cast<uint64_t>(large[i][j] + 1);
        }
        rowHashes[i][0] = hash;
        for (int j = k; j < n; ++j) {
            hash -= static_cast<uint64_t>(large[i][j - k] + 1) * powerRow;
            hash = hash * BASE_ROW + static_cast<uint64_t>(large[i][j] + 1);
            rowHashes[i][j - k + 1] = hash;
        }
    }

    vector<uint64_t> windowHash(widthCount, 0);
    for (int c = 0; c < widthCount; ++c) {
        uint64_t hash = 0;
        for (int r = 0; r < k; ++r) {
            hash = hash * BASE_COL + rowHashes[r][c];
        }
        windowHash[c] = hash;
    }

    auto matches = [&](int top, int left) {
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) {
                if (large[top + i][left + j] != small[i][j]) {
                    return false;
                }
            }
        }
        return true;
    };

    for (int top = 0; top <= n - k; ++top) {
        for (int left = 0; left < widthCount; ++left) {
            if (windowHash[left] == patternHash && matches(top, left)) {
                cout << (top + 1) << ' ' << (left + 1) << '\n';
                return 0;
            }
        }
        if (top == n - k) {
            break;
        }
        for (int left = 0; left < widthCount; ++left) {
            windowHash[left] -= rowHashes[top][left] * powerCol;
            windowHash[left] = windowHash[left] * BASE_COL + rowHashes[top + k][left];
        }
    }

    cout << 0 << '\n';
    return 0;
}