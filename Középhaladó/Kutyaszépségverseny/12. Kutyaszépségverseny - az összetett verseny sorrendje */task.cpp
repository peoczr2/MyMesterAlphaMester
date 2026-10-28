/*
Megoldás lényege:
Egy kutya az összetett versenyből akkor esik ki, ha valamelyik szempontban nem éri el az alsó határt. A bennmaradók összpontszáma az összes szempontban kapott pontok összege.
A bennmaradókat az összpontszám szerint csökkenő sorrendbe rendezzük, a holtversenyes kutyák sorszám szerint növekvő sorrendben kerülnek a sorba.
Ha senki sem marad bent, a kimenet egyetlen -1.
Az idő O(N · M + N log N), a memóriaigény O(N · M).
*/
/*
Hint 1: || Egy kutya akkor esik ki, ha bármelyik szempontban a pontszáma kisebb az alsó határnál. Az összpontszámot csak a bennmaradó kutyákra számold ki. ||
Hint 2: || A bennmaradók sorszámát rendezd úgy, hogy az összehasonlító függvény először az összpontszám szerint csökkenőben, azonos összpontszámnál sorszám szerint növekvően rendezzen. Ha nincs bennmaradó, a -1-et írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> maxPont(m), minPont(m);
    for (int &x : maxPont) cin >> x;
    for (int &x : minPont) cin >> x;

    vector<vector<int>> p(n, vector<int>(m));
    for (auto &sor : p)
        for (int &x : sor) cin >> x;

    vector<int> ossz(n, 0);
    vector<int> bent;
    for (int j = 0; j < n; j++) {
        bool kiesett = false;
        for (int i = 0; i < m; i++) {
            if (p[j][i] < minPont[i]) kiesett = true;
            ossz[j] += p[j][i];
        }
        if (!kiesett) bent.push_back(j);
    }

    if (bent.empty()) {
        cout << -1 << '\n';
        return 0;
    }

    sort(bent.begin(), bent.end(), [&](int a, int b) {
        if (ossz[a] != ossz[b]) return ossz[a] > ossz[b];
        return a < b;
    });

    for (size_t k = 0; k < bent.size(); k++) {
        if (k) cout << ' ';
        cout << bent[k] + 1;
    }
    cout << '\n';
    return 0;
}
