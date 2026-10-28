/*
Megoldás lényege:
Először egy kérdéssel az egész rács kincsszámát kérdezzük le. Egy téglalapot a hosszabb oldala mentén kettéosztunk, és csak az egyik félre kérdezünk: a másik fél kincsszáma a szülő számából kivonva adódik, így arra nem kell külön kérdés. Ha egy téglalap kincsszáma 0, vagy egyenlő a területével, a cellái már egyértelműek, és a rekurzió megáll. Egy cellánál a kincsszám mindig 0 vagy a terület, így a felosztás véges. A kérdések számát a bináris felosztás adja meg, a költsége nagyjából N^4 nagyságrendű, nem optimalizált.
*/
/*
Hint 1: || Kérdezz először az egész rácsra: a kincsszám megmondja, hány kincs van összesen, és ha ez 0, vagy minden cella kincs, több kérdés nem kell. ||
Hint 2: || Egy téglalapot a hosszabb oldala mentén felezd ketté, és csak az egyik felére kérdezz. A másik fél kincsszáma a szülő számából kivonva adódik. ||
Hint 3: || A rekurzió akkor áll meg, ha a téglalap kincsszáma 0 vagy egyenlő a területével, mert ekkor minden cella értéke egyértelmű. Egy cellánál ez mindig teljesül. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A könyvtári függvények (a zsűri adja a megvalósítást).
int get_n();
int get_count(int r1, int c1, int r2, int c2);
void END();

// Helyi próbához: ha a zsűri könyvtára nincs linkelve, ezek a gyenge (weak) alapértelmezések
// a szabványos bemenet térképét (N, majd a rács) használják. A zsűri könyvtára felülírja őket.
namespace {
vector<string> helyiTerkep;
long long helyiKoltseg = 0;
}

__attribute__((weak)) int get_n() {
    int n;
    cin >> n;
    helyiTerkep.assign(n, "");
    for (auto &sor : helyiTerkep) cin >> sor;
    return n;
}

__attribute__((weak)) int get_count(int r1, int c1, int r2, int c2) {
    int n = (int)helyiTerkep.size();
    int s = 0;
    for (int r = r1 - 1; r < r2; ++r)
        for (int c = c1 - 1; c < c2; ++c)
            if (helyiTerkep[r][c] == '1') ++s;
    helyiKoltseg += 1 + (long long)n * n - s;
    return s;
}

__attribute__((weak)) void END() {
    cerr << helyiKoltseg << " <-libPrintsCost\n";
}

int N;
vector<string> ans;

// Az (r1,c1)-(r2,c2) téglalap cellái közül cnt kincs van.
void megold(int r1, int c1, int r2, int c2, int cnt) {
    int terulet = (r2 - r1 + 1) * (c2 - c1 + 1);
    if (cnt == 0) return;
    if (cnt == terulet) {
        for (int r = r1; r <= r2; ++r)
            for (int c = c1; c <= c2; ++c)
                ans[r - 1][c - 1] = '1';
        return;
    }
    if (r2 - r1 >= c2 - c1) {          // a hosszabb oldal: a sorok mentén felezünk
        int mid = (r1 + r2) / 2;
        int felso = get_count(r1, c1, mid, c2);
        megold(r1, c1, mid, c2, felso);
        megold(mid + 1, c1, r2, c2, cnt - felso);
    } else {                           // az oszlopok mentén felezünk
        int mid = (c1 + c2) / 2;
        int bal = get_count(r1, c1, r2, mid);
        megold(r1, c1, r2, mid, bal);
        megold(r1, mid + 1, r2, c2, cnt - bal);
    }
}

int main() {
    N = get_n();
    ans.assign(N, string(N, '0'));
    int osszes = get_count(1, 1, N, N);
    megold(1, 1, N, N, osszes);
    END();
    for (int i = 0; i < N; ++i) cout << ans[i] << '\n';
    return 0;
}
