/*
Megoldás lényege:
Versenyzőnként a 6 dobást csökkenő sorrendbe rendezzük. Így két versenyző eredménye lexikografikusan hasonlítható össze: az első elem a legjobb dobás, egyenlőség esetén a második, és így tovább, ahogy a feladat kéri. A sikertelen (-1) dobások a rendezés után a sor végére kerülnek, ezért külön kezelésük nem kell. A győztes az a versenyző, akinek a rendezett sorozata a legnagyobb, és az összes ilyen versenyző sorszámát növekvő sorrendben írjuk ki. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Két versenyzőt nem az összesített eredmény, hanem a dobásaik sorrendje alapján kell összehasonlítani: a legjobb dobás dönt, döntetlen esetén a második legjobb, és így tovább. ||
Hint 2: || Versenyzőnként rendezd a 6 dobást csökkenő sorrendbe; így két versenyző sorozata elemenként összevethető, sőt a beépített vektor-összehasonlítás is ugyanezt adja. ||
Hint 3: || Miután megvan a legjobb sorozat, menj végig a versenyzőkön sorszám szerint, és írd ki mindazokat, akiknek a rendezett sorozata ugyanaz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> throwsDesc(n, vector<int>(6));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++) {
            cin >> throwsDesc[i][j];
        }
        sort(throwsDesc[i].begin(), throwsDesc[i].end(), greater<int>());
    }

    vector<int> best = throwsDesc[0];
    for (int i = 1; i < n; i++) {
        if (throwsDesc[i] > best) {
            best = throwsDesc[i];
        }
    }

    bool first = true;
    for (int i = 0; i < n; i++) {
        if (throwsDesc[i] == best) {
            if (!first) {
                cout << " ";
            }
            cout << i + 1;
            first = false;
        }
    }
    cout << "\n";

    return 0;
}
