/*
Megoldás lényege:
A szavak száma N legfeljebb 7, ezért az összes sorrend kipróbálása (legfeljebb 7! = 5040 eset) gyorsan lefut. A szavakat először rendezzük, így a next_permutation az összes különböző sorrendet végigjárja, ismétlődő szavak esetén is. Minden sorrendből egymás mellé írással összetett szót képezünk, és ezeket egy set-be tesszük: a halmaz kiszűri az ismétlődéseket, és a kiíráskor már abc-sorrendben adja vissza az elemeket. A kimenet első sora a halmaz mérete. Az időigény O(N! * N * L), ahol L a szavak összhossza, ami N ≤ 7 esetén bőven belefér az időkorlátba.
*/
/*
Hint 1: || Mivel N legfeljebb 7, nincs szükség kombinatorikai képletre: az összes szósorrend kipróbálása gyorsan lefut. ||
Hint 2: || Rendezd a szóvektort, majd a next_permutation függvénnyel járd végig a sorrendeket, és minden sorrendből fűzd össze a szavakat. Az eredményeket set<string>-ben gyűjtsd: így az ismétlődések automatikusan kiesnek, és a sorrend is rendezett lesz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<string> w(n);
    for (auto &x : w) cin >> x;
    sort(w.begin(), w.end());
    set<string> res;
    do {
        string s;
        for (const string &x : w) s += x;
        res.insert(s);
    } while (next_permutation(w.begin(), w.end()));
    cout << res.size() << "\n";
    for (const string &s : res) cout << s << "\n";
    return 0;
}
