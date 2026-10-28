/*
Megoldás lényege:
Minden helységről a sorában lévő madárszámokat nézzük. Egy helység akkor üres, ha a sorának minden
száma 0, ezért soronként elég egy logikai jelzővel megjegyezni, volt-e nullától különböző érték.
Az első üres helység sorszámát írjuk ki; ha nincs ilyen, a kimenet 0. Az M·N ≤ 10 000 beolvasás
gyorsan lefut, így az időkorlát bőven teljesül.
*/
/*
Hint 1: || Egy helység üres voltát csak a saját sorának számai döntik el, a többi helység nem számít. ||
Hint 2: || Sorról sorra haladva olvasd be a sor N számát, és közben jelöld, volt-e köztük nem nulla. Az első csupa nulla sor sorszámát tárold el, a többit már nem kell figyelni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    int valasz = 0;
    for (int i = 1; i <= M; ++i) {
        bool ures = true;
        for (int j = 0; j < N; ++j) {
            int e;
            cin >> e;
            if (e != 0) ures = false;
        }
        if (ures && valasz == 0) valasz = i;
    }

    cout << valasz << '\n';
    return 0;
}
