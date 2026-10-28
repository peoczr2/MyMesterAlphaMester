/*
Megoldás lényege:
A kombinációk lexikografikus sorrendjében a következő sorozat úgy kapható, hogy a legjobbra álló, még növelhető elemet eggyel megnöveljük, a tőle jobbra álló elemeket pedig a lehető legkisebb, egymás utáni értékekre állítjuk. Az előző sorozatnál ugyanez tükrösen történik: a legjobbra álló, még csökkenthető elemet csökkentjük, a jobb oldali elemek pedig az N-ig tartó legnagyobb, egymás utáni számok lesznek. Ha nincs ilyen elem, a sorrend körbeér: a következő az 1 2 … M, az előző az N−M+1 … N. A lépés csak a sorozat jobb oldali részét írja át, így egy lépés O(M) időben elvégezhető.
*/
/*
Hint 1: || Keresd meg a legjobbra álló olyan elemet, amelyet még lehet eggyel növelni úgy, hogy a sorozat szigorúan növekvő maradjon és az értéke ne haladja meg N-et. ||
Hint 2: || A talált elem jobb oldalán álló elemeket állítsd vissza a lehető legkisebb, egymás utáni számokra. Az előző sorozatnál csökkenthető elemet keress, a jobb oldalt pedig az N-ig tartó egymás utáni számokkal töltsd fel. ||
Hint 3: || Ha egyetlen elem sem léptethető, a sorrend körbeér: a következő sorozat 1 2 … M, az előző N−M+1 … N. ||
*/
#include <bits/stdc++.h>
using namespace std;

static bool nextComb(vector<int>& a, int N) {
    int M = (int)a.size();
    for (int i = M - 1; i >= 0; --i) {
        int limit = N - (M - 1 - i);
        if (a[i] < limit) {
            ++a[i];
            for (int j = i + 1; j < M; ++j) a[j] = a[j - 1] + 1;
            return true;
        }
    }
    for (int i = 0; i < M; ++i) a[i] = i + 1;
    return false;
}

static bool prevComb(vector<int>& a, int N) {
    int M = (int)a.size();
    for (int i = M - 1; i >= 0; --i) {
        int lower = (i == 0 ? 1 : a[i - 1] + 1);
        if (a[i] > lower) {
            --a[i];
            for (int j = i + 1; j < M; ++j) a[j] = N - (M - 1 - j);
            return true;
        }
    }
    for (int i = 0; i < M; ++i) a[i] = N - M + 1 + i;
    return false;
}

static void printComb(const vector<int>& a) {
    for (int i = 0; i < (int)a.size(); ++i) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<int> a(M);
    for (int i = 0; i < M; ++i) cin >> a[i];

    auto prevA = a;
    auto nextA = a;
    prevComb(prevA, N);
    nextComb(nextA, N);
    printComb(prevA);
    printComb(nextA);
    return 0;
}