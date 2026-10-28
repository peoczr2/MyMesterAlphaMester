/*
Megoldás lényege:
Minden vízállást készültségi szintre osztunk: 3, ha meghaladja az 1000 cm-t, 2, ha meghaladja a 900 cm-t, 1, ha meghaladja a 800 cm-t, egyébként 0.
A harmadfokú folyószakaszok a harmadfokú szintű mérések maximális, egymás melletti sorozatai, ezeket egy bejárással megkapjuk.
Mindegyik harmadfokú szakaszon belül megkeressük az egyforma vízállású futamok közül a leghosszabbat. Állandó résznek a legalább 2 hosszú futam számít.
A szakaszok közül azok kerülnek a harmadik és negyedik sorba, amelyekben van ilyen rész; az utolsó sorba a leghosszabb állandó részt tartalmazó szakasz kerül
(egyenlőség esetén az előbbi), a hosszával együtt. Az egész megoldás O(N) időben fut.
*/
/*
Hint 1: || Minden mérést először sorolj egy készültségi szintbe, majd az egymás melletti, azonos szintű mérések maximális sorozatai lesznek a folyószakaszok. Csak a 3-as szintűekre van szükség. ||
Hint 2: || Egy harmadfokú szakaszon belül keresd az egyforma vízállású, egymás melletti mérések futamait. Egy futam akkor állandó vízmagasságú rész, ha legalább 2 mérésből áll. ||
Hint 3: || Egy bejárással minden harmadfokú szakasz legalább 2 hosszú futamai közül számold ki a leghosszabb futamot. A kiíráshoz tárold a szakasz kezdetét és végét, és csak szigorúan hosszabb futamnál írd felül a korábbi eredményt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int szint(int h) {
    if (h > 1000) return 3;
    if (h > 900) return 2;
    if (h > 800) return 1;
    return 0;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<pair<int, int>> harmadfokuak;
    int i = 1;
    while (i <= n) {
        int s = szint(a[i]);
        int j = i;
        while (j + 1 <= n && szint(a[j + 1]) == s) j++;
        if (s == 3) harmadfokuak.push_back({i, j});
        i = j + 1;
    }

    cout << harmadfokuak.size() << '\n';
    if (harmadfokuak.empty()) return 0;

    for (size_t k = 0; k < harmadfokuak.size(); k++) {
        if (k > 0) cout << ' ';
        cout << harmadfokuak[k].first << ' ' << harmadfokuak[k].second;
    }
    cout << '\n';

    vector<pair<int, int>> allandoSzakaszok;
    int legjobbHossz = 0, legjobbKezdet = 0, legjobbVege = 0;
    for (auto [l, r] : harmadfokuak) {
        int maxHossz = 0;
        int p = l;
        while (p <= r) {
            int q = p;
            while (q + 1 <= r && a[q + 1] == a[p]) q++;
            maxHossz = max(maxHossz, q - p + 1);
            p = q + 1;
        }
        if (maxHossz >= 2) allandoSzakaszok.push_back({l, r});
        if (maxHossz > legjobbHossz) {
            legjobbHossz = maxHossz;
            legjobbKezdet = l;
            legjobbVege = r;
        }
    }

    cout << allandoSzakaszok.size() << '\n';
    if (allandoSzakaszok.empty()) return 0;

    for (size_t k = 0; k < allandoSzakaszok.size(); k++) {
        if (k > 0) cout << ' ';
        cout << allandoSzakaszok[k].first << ' ' << allandoSzakaszok[k].second;
    }
    cout << '\n';

    cout << legjobbKezdet << ' ' << legjobbVege << ' ' << legjobbHossz << '\n';

    return 0;
}
