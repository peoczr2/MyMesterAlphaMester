/*
Megoldás lényege:
Egy faj akkor ritka, ha az országban pontosan egy helységben fordult elő, vagyis az oszlopában pontosan egy nullától különböző darabszám van. Fajonként megszámoljuk, hány helységben láttak belőle egyedet. Soronként olvasunk, és a nullától különböző számok után a megfelelő faj számlálóját növeljük. A végén az első olyan faj sorszámát írjuk ki, amelynek számlálója 1; ha nincs ilyen, a 0 kerül ki. Mivel fajonként egy számlálót tárolunk, a memóriaigény O(N), az idő O(M·N).
*/
/*
Hint 1: || Egy faj sorsát a saját oszlopa dönti el: meg kell számolnod, hány helységben volt a faj darabszáma nullától különböző. ||
Hint 2: || Tarts N elemű számlálót a fajokhoz, és minden nem nulla szám után növeld az adott faj számlálóját. A végén az első olyan faj sorszámát írd ki, amelynek számlálója pontosan 1; ha nincs ilyen, írj 0-t. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    vector<int> helysegek(N + 1, 0);
    for (int i = 0; i < M; ++i) {
        for (int j = 1; j <= N; ++j) {
            int e;
            cin >> e;
            if (e > 0) ++helysegek[j];
        }
    }

    int talalat = 0;
    for (int j = 1; j <= N; ++j) {
        if (helysegek[j] == 1) {
            talalat = j;
            break;
        }
    }

    cout << talalat << '\n';
    return 0;
}
