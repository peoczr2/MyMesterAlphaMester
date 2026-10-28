/*
Megoldás lényege:
Egy madárfaj akkor fordult elő csak 1 helyen, ha az oszlopában pontosan egy nullától különböző darabszám van. Fajonként egy számlálót tartunk, amely azt számolja, hány helységben láttak belőle legalább egy egyedet. A bemenetet soronként olvassuk, és minden pozitív elemnél növeljük a megfelelő faj számlálóját. A végén akkor 1 a válasz, ha van olyan faj, amelynek számlálója pontosan 1, különben 0. Az idő O(M·N), a memóriaigény O(N).
*/
/*
Hint 1: || Egy faj helyeinek számát a saját oszlopa adja: meg kell számolnod, hány helységben volt a darabszám nullától különböző. ||
Hint 2: || Tarts N elemű számlálót a fajokhoz, és minden pozitív szám után növeld a hozzá tartozó számlálót. A végén nézd meg, van-e olyan faj, amelynek számlálója pontosan 1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    vector<int> helyekSzama(N, 0);
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            int e;
            cin >> e;
            if (e > 0) ++helyekSzama[j];
        }
    }

    bool van = false;
    for (int j = 0; j < N; ++j)
        if (helyekSzama[j] == 1) van = true;

    cout << (van ? 1 : 0) << '\n';
    return 0;
}
