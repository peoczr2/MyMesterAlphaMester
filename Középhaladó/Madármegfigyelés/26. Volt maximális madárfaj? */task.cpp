/*
Megoldás lényege:
Helységenként meghatározzuk a leggyakoribb fajokat, ez a legnagyobb darabszámú fajok halmaza (döntetlen esetén több faj is benne lehet). A kérdés az, hogy van-e olyan faj, amely minden helységben a leggyakoribbak közé tartozik. Ezt úgy döntjük el, hogy fajonként egy jelzőt tartunk, amely kezdetben igaz, és minden helységnél hamisra állítjuk azokat a fajokat, amelyek darabszáma kisebb a helység maximumánál. A végén akkor 1 a válasz, ha van még igaz jelző. Az idő O(M·N), a memóriaigény O(N).
*/
/*
Hint 1: || Először csak azt vizsgáld, melyik faj a leggyakoribb egy adott helységben: ez a sor legnagyobb eleme. Egy faj csak akkor lehet a megoldás, ha minden helységben ilyen legnagyobb elem. ||
Hint 2: || Tarts N elemű logikai tömböt, amely kezdetben minden fajra igaz. Soronként számold ki a sor maximumát, és minden olyan fajt, amelynek darabszáma kisebb, tedd hamissá. A végén, ha van még igaz elem, a válasz 1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    vector<bool> jelolt(N, true);
    for (int i = 0; i < M; ++i) {
        vector<int> sor(N);
        for (int j = 0; j < N; ++j)
            cin >> sor[j];

        int legtobb = *max_element(sor.begin(), sor.end());
        for (int j = 0; j < N; ++j)
            if (sor[j] < legtobb) jelolt[j] = false;
    }

    bool van = false;
    for (int j = 0; j < N; ++j)
        if (jelolt[j]) van = true;

    cout << (van ? 1 : 0) << '\n';
    return 0;
}
