/*
Megoldás lényege:
Egy nap akkor „hűvösebb az előző napnál”, ha legalább egy településen a hőmérséklet kisebb, mint a megelőző napon. A településeket egyesével, a sorokat balról jobbra olvassuk be, és minden olyan j napot megjelölünk, amelyen az előző napi értéknél kisebb érték szerepel. Az első napnak nincs előző napja, ezért nem vizsgáljuk. A megjelölt napok sorszámait növekvő sorrendben írjuk ki. Az idő O(N·M), a memória O(M), mert a teljes mátrixot nem kell tárolni.
*/
/*
Hint 1: || Egy nap akkor jó, ha valamely településen a hőmérséklet kisebb, mint a közvetlenül előző napon. Elég minden település sorát egyszer, balról jobbra végigolvasni. ||
Hint 2: || Egy logikai tömbben jelöld meg a napokat: ha a j. napon egy település értéke kisebb a (j−1). napinál, a j. nap bekerül a listába. Az első napot ne hasonlítsd semmihez. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<bool> hulvosebb(m + 1, false);
    for (int i = 1; i <= n; i++) {
        int elozo;
        cin >> elozo;
        for (int j = 2; j <= m; j++) {
            int h;
            cin >> h;
            if (h < elozo) hulvosebb[j] = true;
            elozo = h;
        }
    }

    vector<int> napok;
    for (int j = 2; j <= m; j++) {
        if (hulvosebb[j]) napok.push_back(j);
    }

    cout << napok.size();
    for (int d : napok) cout << ' ' << d;
    cout << '\n';
    return 0;
}
