/*
Megoldas lenyege:
A ket kereskedo aru-nevsora rendezetten adott. A keresett valasz a ket nevhalmaz
szimmetrikus differenciaja, de minden nevet csak egyszer szabad kiirni, akkor is,
ha valamelyik listaban tobbszor szerepel.

Ket mutatoval osszefesuljuk a ket rendezett listat. Mindig az aktualis legkisebb nevet
vizsgaljuk, megszamoljuk, hogy melyik listaban szerepel, majd atugorjuk az osszes azonos
elojfordulast. Ha pontosan az egyik listaban volt jelen, bekerul a valaszba.
*/
/*
Hint 1: || A duplikatumok miatt egy nevet mindig blokkonkent erdemes kezelni. ||
Hint 2: || A rendezettség miatt eleg ket mutatoval vegigmenni a ket listan. ||
Hint 3: || Akkor kell kiirni a nevet, ha csak az egyik listaban fordult elo. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    int m;
    cin >> m;
    vector<string> b(m);
    for (int i = 0; i < m; ++i) cin >> b[i];

    vector<string> answer;
    int i = 0, j = 0;
    while (i < n || j < m) {
        string current;
        if (j == m || (i < n && a[i] < b[j])) current = a[i];
        else if (i == n || b[j] < a[i]) current = b[j];
        else current = a[i];

        bool inA = false, inB = false;
        while (i < n && a[i] == current) {
            inA = true;
            ++i;
        }
        while (j < m && b[j] == current) {
            inB = true;
            ++j;
        }

        if (inA != inB) answer.push_back(current);
    }

    cout << answer.size() << '\n';
    for (const string& name : answer) cout << name << '\n';
    return 0;
}