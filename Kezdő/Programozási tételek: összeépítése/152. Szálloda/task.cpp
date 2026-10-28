/*
Megoldás lényege:
Minden lehetséges K szomszédos telekből álló csoport összegét ki kell számolni. Az összegek csúszóablakkal
kaphatók meg: az első csoport összegét egyszer kiszámoljuk, utána minden következő csoport összege az előzőből
úgy adódik, hogy hozzáadjuk az újonnan bekerülő telek árát, és levonjuk a kiesőét. Ezután megkeressük a
minimumot, majd még egyszer végigmegyünk a csoportokon, és kiírjuk az összes minimális összegű csoport
szélső telkének sorszámát balról jobbra. Az időigény O(N), ahol N a telkek száma.
*/
/*
Hint 1: || Az összes lehetséges K szomszédos telekcsoport összegét kell ismerni. Ezek száma N-K+1, és egymás összegéből könnyen származtathatók. ||
Hint 2: || Egy csoport összegét az előző csoport összegéből kapod: hozzáadod az új telek árát, és levonod a kiesőét. A minimum megkeresése után újra végigmész a csoportokon, és a minimumot adókat gyűjtöd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k; // a telkek száma, a megvásárolandó szomszédos telkek száma
    cin >> n >> k;

    vector<long long> price(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> price[i];

    int groups = n - k + 1; // a lehetséges csoportok száma, a j-edik csoport a j..j+K-1 telkeket fogja át
    vector<long long> sum(groups + 1, 0);
    long long cur = 0;
    for (int i = 1; i <= k; i++)
        cur += price[i];
    sum[1] = cur;
    for (int j = 2; j <= groups; j++) {
        cur += price[j + k - 1] - price[j - 1];
        sum[j] = cur;
    }

    long long best = *min_element(sum.begin() + 1, sum.end());

    vector<int> starts; // a minimális összegű csoportok kezdő telke
    for (int j = 1; j <= groups; j++)
        if (sum[j] == best)
            starts.push_back(j);

    cout << best << '\n';
    cout << starts.size() << '\n';
    for (int j : starts)
        cout << j << ' ' << j + k - 1 << '\n';
    return 0;
}
