/*
Megoldas lenyege:
A szoveg hossza legfeljebb 300, ezert minden legalabb 2 hosszú reszsztringet elo tudunk
allitani es megszamolni. Azokat a reszleteket gyujtjuk ossze, amelyek legalabb ketszer
elofordulnak, majd ezeket lexikografikus sorrendben kiirjuk.
*/
/*
Hint 1: || A szöveg rövid, ezért a teljes részsztring-összeszámlálás belefér. ||
Hint 2: || Minden előfordulást külön számolni kell, de a kimenetben minden részlet csak egyszer szerepelhet. ||
Hint 3: || A végén elég az ismétlődő részleteket rendezni és kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    unordered_map<string, int> cnt;
    cnt.reserve(50000);

    for (int i = 0; i < (int)s.size(); ++i) {
        string cur;
        cur.reserve(s.size() - i);
        for (int j = i; j < (int)s.size(); ++j) {
            cur.push_back(s[j]);
            if ((int)cur.size() >= 2) ++cnt[cur];
        }
    }

    vector<string> ans;
    for (const auto &entry : cnt) {
        if (entry.second >= 2) ans.push_back(entry.first);
    }
    sort(ans.begin(), ans.end());

    for (size_t i = 0; i < ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
