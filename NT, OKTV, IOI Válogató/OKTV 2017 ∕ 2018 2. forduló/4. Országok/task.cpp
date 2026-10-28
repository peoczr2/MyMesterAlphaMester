/*
Megoldás lényege:
Minden évben egyszerre dől el, mely szabad országok esnek el: egy szabad ország akkor kerül egy agresszív országhoz, ha az agresszív szomszédai mind ugyanahhoz a foglalóhoz tartoznak.
Ha a szomszédai között két különböző foglaló agresszív országa is van, az ország nem esik el, és ez később sem változik, mert az agresszív országok száma csak nő.
Az elfoglalt országok az év végén maguk is agresszívvá válnak, és a foglaló tulajdonába kerülnek.
Minden országra nyilvántartjuk az egyetlen foglalót (seen), és azt, hogy két különböző foglaló is jelentkezett-e (mixed); így egy év csak az előző évben újonnan agresszívvá vált országok szomszédait érinti.
A teljes futás O(N + E + K) időben végezhető, ahol E a szomszédsági listák összes eleme.
*/
/*
Hint 1: || Az évek sorban követik egymást, és minden évben csak az év eleji állapot számít. Egy szabad országot akkor foglal el egy agresszív szomszéd, ha az összes agresszív szomszédja ugyanahhoz a foglalóhoz tartozik. ||
Hint 2: || Minden országhoz tárolj egy foglalót (az első agresszív szomszéd tulajdonosát), és egy jelzőt arra, hogy két különböző foglaló is jelentkezett-e. Ha jelző be van állítva, az ország sosem esik el, mert az agresszív országok száma csak nő. ||
Hint 3: || Egy évben csak azoknak a szabad országoknak kell foglalót keresni, amelyek az előző évben újonnan agresszívvá vált országok szomszédai. A foglalásokat az év végén egyszerre alkalmazd, és csak utána frissítsd a foglaló- és a jelzőértékeket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, r, k;
    cin >> n >> r >> k;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        while (cin >> x && x != 0) adj[i].push_back(x);
    }

    vector<int> owner(n + 1, 0);       // 0: szabad, különben a tulajdonos (kezdő agresszív ország) sorszáma
    vector<int> seen(n + 1, 0);        // a rá eddig jelentkező agresszív szomszédok közös tulajdonosa (0: nincs)
    vector<char> mixed(n + 1, 0);      // két különböző tulajdonú agresszív szomszéd van: sosem esik el

    // Egy új agresszív ország (sorszáma a, tulajdonosa o) jelentkezik a szomszédainál
    auto registerAgg = [&](int a, int o) {
        for (int c : adj[a]) {
            if (seen[c] == 0) seen[c] = o;
            else if (seen[c] != o) mixed[c] = 1;
        }
    };

    vector<int> newly;                 // az előző évben (vagy kezdetben) agresszívvá vált országok
    for (int i = 1; i <= r; i++) {
        owner[i] = i;
        newly.push_back(i);
    }
    for (int i = 1; i <= r; i++) registerAgg(i, i);

    vector<int> mark(n + 1, -1);
    for (int year = 0; year < k && !newly.empty(); year++) {
        // Az év eleji állapot alapján: a szabad szomszédok, akiknek egyetlen foglaló a szomszédságában van
        vector<int> captured;
        for (int a : newly) {
            for (int b : adj[a]) {
                if (owner[b] != 0 || mixed[b] || mark[b] == year) continue;
                mark[b] = year;
                captured.push_back(b);
            }
        }

        // A foglalók az év elején még nem változtak, így az elfoglalt országok tulajdonosa egyértelmű
        for (int b : captured) owner[b] = seen[b];
        // Az év végén az új agresszív országok szomszédai frissülnek
        for (int b : captured) registerAgg(b, owner[b]);
        newly.swap(captured);
    }

    // Tulajdonosonként, növekvő sorrendben, az elfoglalt országok listája
    vector<vector<int>> took(r + 1);
    for (int b = r + 1; b <= n; b++) {
        if (owner[b] != 0) took[owner[b]].push_back(b);
    }
    for (int i = 1; i <= r; i++) {
        cout << took[i].size();
        for (int b : took[i]) cout << ' ' << b;
        cout << '\n';
    }
    return 0;
}
