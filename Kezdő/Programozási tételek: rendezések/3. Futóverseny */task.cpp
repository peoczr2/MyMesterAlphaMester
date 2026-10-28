/*
Megoldás lényege:
A versenyzőket rajtszám szerint, percenként indítják, így a r rajtszámú versenyző r perccel később (vagy r-1 perccel, ami ugyanazt a sorrendet adja) indul.
A valódi futási idő ezért a célidő és a rajtszám különbsége: C_i - r_i. Ez a rangsor alapja.
Az így kapott futási időket növekvő sorrendbe rendezzük (azonos időnél a rajtszám szerint), majd végigmegyünk a sorozaton.
Az azonos futási idejű versenyzők egy csoportot alkotnak, a csoport helyezési száma a csoport első elemének sorszáma (1-től számolva), így a holtverseny után a helyezés kimarad.
A célba nem érők rajtszámát növekvő sorrendben az utolsó sorba írjuk.
Az időigény O(M log M + N), ami N ≤ 1000 mellett bőven elég.
*/
/*
Hint 1: || Nem a nyers célidő számít: a r rajtszámú versenyző r perccel később indul, ezért a futási idő a célidő és a rajtszám különbsége. ||
Hint 2: || A futási idők szerint rendezd a célba érkezőket (azonos időnél a rajtszám szerint), majd a rendezett sorban csoportonként haladj: a csoport helyezési száma a csoport első elemének sorszáma. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> cel;  // (futási idő, rajtszám)
    vector<bool> celba(n + 1, false);
    for (int i = 0; i < m; i++) {
        int rajtszam, ido;
        cin >> rajtszam >> ido;
        celba[rajtszam] = true;
        cel.push_back({ido - rajtszam, rajtszam});
    }
    sort(cel.begin(), cel.end());

    // Csoportonként: azonos futási idő holtverseny, a következő helyezés kimarad
    for (int i = 0; i < m;) {
        int j = i;
        while (j < m && cel[j].first == cel[i].first) j++;
        cout << i + 1;
        for (int t = i; t < j; t++) cout << ' ' << cel[t].second;
        cout << '\n';
        i = j;
    }

    // A célba nem érők rajtszáma növekvő sorrendben
    bool elso = true;
    for (int r = 1; r <= n; r++) {
        if (!celba[r]) {
            if (!elso) cout << ' ';
            cout << r;
            elso = false;
        }
    }
    cout << '\n';
    return 0;
}
