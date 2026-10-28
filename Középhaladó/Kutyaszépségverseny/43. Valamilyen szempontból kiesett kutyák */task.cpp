/*
Megoldás lényege:
Egy kutya valamilyen szempontból kiesett, ha valamelyik szempontban a pontszáma kisebb az adott szempont alsó ponthatáránál.
Minden kutyára végigmegyünk a szempontokon, és ha talál ilyet, a kutya sorszámát felvesszük a listába; így minden kiesett kutya csak egyszer szerepel.
A kutyákat sorszám szerint járjuk be, ezért a lista már növekvő sorrendben készül el.
Az idő O(N · M), a memóriaigény O(N · M).
*/
/*
Hint 1: || Egy kutya kiesése egyetlen szempont miatt is megtörténhet, ezért elég, ha egy szempontban találsz alsó határ alatti pontot. Egy kutyát így is csak egyszer írj ki. ||
Hint 2: || Minden kutya minden pontját vesd össze a szempont alsó határával. Ha kisebb, a kutya kiesett: jelöld meg egy logikai változóval, és a sor végén már nem kell tovább nézni. ||
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

    vector<int> kiesett;
    for (int i = 0; i < n; i++) {
        bool kiesik = false;
        for (int j = 0; j < m && !kiesik; j++)
            if (p[i][j] < minPont[j]) kiesik = true;
        if (kiesik) kiesett.push_back(i + 1);
    }

    cout << kiesett.size();
    for (int x : kiesett) cout << ' ' << x;
    cout << '\n';
    return 0;
}
