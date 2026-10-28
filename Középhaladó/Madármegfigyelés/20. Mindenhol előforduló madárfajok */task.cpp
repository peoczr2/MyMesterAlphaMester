/*
Megoldás lényege:
Egy faj pontosan akkor fordult elő az összes helységben, ha egyik helységben sem volt nulla a darabszáma. Ezért minden fajhoz egy jelzőt tárolunk, amely kezdetben igaz. A számokat soronként olvassuk be, és ha valamelyik helységben egy faj darabszáma 0, a jelzőjét hamisra állítjuk. A végén az első sorba a megmaradt igaz jelzőjű fajok számát írjuk, a másodikba a sorszámaikat növekvő sorrendben (csak ha van ilyen faj). Mivel a táblázatot nem kell tárolni, a memóriaigény O(N), az idő O(M·N).
*/
/*
Hint 1: || Egy faj kiesik, amint bármelyik helységben nulla darab egyedét látták. Nem kell összegezni, elég a nullákat keresni. ||
Hint 2: || Tarts N elemű logikai tömböt, amelynek minden eleme kezdetben igaz. Beolvasás közben minden nulla számnál állítsd hamisra az adott faj elemét. A végén az igaz elemek indexei adják a kimenetet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    vector<bool> mindenhol(N + 1, true);
    for (int i = 0; i < M; ++i) {
        for (int j = 1; j <= N; ++j) {
            int e;
            cin >> e;
            if (e == 0) mindenhol[j] = false;
        }
    }

    vector<int> fajok;
    for (int j = 1; j <= N; ++j) {
        if (mindenhol[j]) fajok.push_back(j);
    }

    cout << fajok.size() << '\n';
    for (size_t k = 0; k < fajok.size(); ++k) {
        if (k) cout << ' ';
        cout << fajok[k];
    }
    if (!fajok.empty()) cout << '\n';
    return 0;
}
