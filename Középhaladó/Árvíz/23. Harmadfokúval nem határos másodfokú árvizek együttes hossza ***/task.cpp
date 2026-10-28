/*
Megoldás lényege:
Minden vízállást készültségi szintre osztunk (3: 1000 cm felett, 2: 900 cm felett, 1: 800 cm felett, egyébként 0), majd a folyószakaszokat
a maximális, egymás melletti, azonos szintű mérések adják. Egy bejárással felépítjük a szakaszok listáját (kezdet, vég, szint).
A másodfokú (szint 2) szakaszok közül azok számítanak, amelyeknek sem a bal, sem a jobb oldali közvetlen szomszédja nem harmadfokú.
Ezeknek kiírjuk a darabszámát, a kezdő- és végsorszámukat, majd a hosszuk összegét. Az időigény O(N).
*/
/*
Hint 1: || Először bontsd a vízállás-sorozatot folyószakaszokra: az azonos készültségi szintű, egymás melletti mérések egy szakaszt alkotnak. ||
Hint 2: || A szakaszokat egy vektorban tárold (kezdet, vég, szint). Egy szakasz szomszédai a listában a közvetlenül előtte és a közvetlenül utána álló elemek. ||
Hint 3: || Egy másodfokú szakaszt akkor vedd bele az összhosszba, ha sem a bal, sem a jobb oldali szomszédja nem harmadfokú. A lista szélső elemeinek csak egy szomszédjuk van. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Szakasz {
    int l, r, szint;
};

int szint(int h) {
    if (h > 1000) return 3;
    if (h > 900) return 2;
    if (h > 800) return 1;
    return 0;
}

void printPairs(const vector<pair<int, int>>& v) {
    for (size_t k = 0; k < v.size(); k++) {
        if (k > 0) cout << ' ';
        cout << v[k].first << ' ' << v[k].second;
    }
    cout << '\n';
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<Szakasz> sz;
    int i = 1;
    while (i <= n) {
        int s = szint(a[i]);
        int j = i;
        while (j + 1 <= n && szint(a[j + 1]) == s) j++;
        sz.push_back({i, j, s});
        i = j + 1;
    }

    vector<pair<int, int>> masodfokuak;
    vector<pair<int, int>> kivalasztott;
    long long osszhossz = 0;

    for (size_t k = 0; k < sz.size(); k++) {
        if (sz[k].szint != 2) continue;
        masodfokuak.push_back({sz[k].l, sz[k].r});

        bool harmadfokuSzomszed = false;
        if (k > 0 && sz[k - 1].szint == 3) harmadfokuSzomszed = true;
        if (k + 1 < sz.size() && sz[k + 1].szint == 3) harmadfokuSzomszed = true;

        if (!harmadfokuSzomszed) {
            kivalasztott.push_back({sz[k].l, sz[k].r});
            osszhossz += sz[k].r - sz[k].l + 1;
        }
    }

    cout << masodfokuak.size() << '\n';
    if (masodfokuak.empty()) return 0;
    printPairs(masodfokuak);

    cout << kivalasztott.size() << '\n';
    if (kivalasztott.empty()) return 0;
    printPairs(kivalasztott);

    cout << osszhossz << '\n';
    return 0;
}
