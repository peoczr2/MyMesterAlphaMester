/*
Legyen dpA az addigi igények legyártásának minimális ideje, ha az utolsó alkatrészt az A gépen gyártottuk,
és hasonlóan dpB a B gépre. A következő darabnál vagy ugyanazon a gépen maradunk, vagy átállunk a másikra,
ezért mindkét állapot egyetlen soros dinamikus programozással frissíthető. A kezdődarab előtt bármelyik gépet
választhatjuk átállási költség nélkül.
*/
/*
Hint 1: || Csak az utolsóként használt gép számít a jövő szempontjából. ||
Hint 2: || A következő alkatrésznél két lehetőség van: maradsz ugyanazon a gépen, vagy átváltasz. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    long long ab, ba;
    cin >> k >> n >> ab >> ba;
    vector<long long> ta(k + 1), tb(k + 1), order(n + 1);
    for (int i = 1; i <= k; ++i) {
        cin >> ta[i];
    }
    for (int i = 1; i <= k; ++i) {
        cin >> tb[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> order[i];
    }

    long long dpA = ta[order[1]];
    long long dpB = tb[order[1]];
    for (int i = 2; i <= n; ++i) {
        long long nextA = min(dpA + ta[order[i]], dpB + ba + ta[order[i]]);
        long long nextB = min(dpB + tb[order[i]], dpA + ab + tb[order[i]]);
        dpA = nextA;
        dpB = nextB;
    }

    cout << min(dpA, dpB) << '\n';
    return 0;
}