/*
Megoldás lényege:
Egy cég nyereségét az utolsó és az első napi záróárfolyam különbsége adja, ezért a köztes napok értékeit beolvassuk, de nem tároljuk. Minden cégnél kiszámoljuk a nyereséget, és egy tömbbe tesszük. Az első részfeladatban ennek a tömbnek a maximumát írjuk ki. A második részfeladatban megszámoljuk, hány cég éri el ezt a maximumot, majd a nevüket a bemeneti sorrendben, szóközzel elválasztva kiírjuk. A két részfeladat előtt külön-külön egy # sor áll. Az időigény O(N * M), a memóriaigény O(N), ahol N a cégek és M a napok száma.
*/
/*
Hint 1: || A nyereséghez csak két árfolyamra van szükség: az első és az utolsó napira. A köztes napok értékeit beolvasni kell, de nem kell eltárolni. ||
Hint 2: || Minden cégre számold ki a nyereséget egy tömbbe, majd a maximumot és a maximumot elérő cégeket ebből a tömbből határozd meg. A kiírásnál a két részfeladat előtt a # sor kötelező, és a darabszámot külön sorba írd a nevek elé. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<string> nevek(n);
    vector<long long> nyereseg(n);
    for (int i = 0; i < n; i++) {
        cin >> nevek[i];

        long long elso;
        cin >> elso;
        long long utolso = elso;
        for (int j = 1; j < m; j++) {
            cin >> utolso;
        }
        nyereseg[i] = utolso - elso;
    }

    long long legnagyobb = nyereseg[0];
    for (long long x : nyereseg) {
        legnagyobb = max(legnagyobb, x);
    }

    cout << "#\n";
    cout << legnagyobb << "\n";

    vector<string> gyoztesek;
    for (int i = 0; i < n; i++) {
        if (nyereseg[i] == legnagyobb) {
            gyoztesek.push_back(nevek[i]);
        }
    }

    cout << "#\n";
    cout << gyoztesek.size() << "\n";
    for (size_t i = 0; i < gyoztesek.size(); i++) {
        if (i > 0) cout << " ";
        cout << gyoztesek[i];
    }
    cout << "\n";
    return 0;
}
