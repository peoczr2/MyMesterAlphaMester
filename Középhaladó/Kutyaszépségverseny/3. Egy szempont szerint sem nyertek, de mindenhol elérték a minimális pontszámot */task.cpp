/*
Megoldás lényege:
Szempontonként először megkeressük a legnagyobb pontot azok között a kutyák között, akik elérik az adott szempont alsó ponthatárát. Az ezt a pontot elérő kutyák (holtverseny esetén mindegyik) nyertek az adott szempontban. Ezután kiválogatjuk azokat a kutyákat, amelyek minden szempontban elérték az alsó határt, és egyik szempontban sem nyertek. Ezek számát és sorszámait növekvő sorrendben írjuk ki; ha nincs ilyen kutya, a 0 a válasz. Az időigény O(N·M), a memóriaigény O(N·M).
*/
/*
Hint 1: || Egy szempontban a győztes pontot csak az alsó ponthatárt elérő kutyák közül keresd. Ha ezen belül a legnagyobb pontot többen is elérik, mindannyian nyertek. ||
Hint 2: || Tarts egy logikai tömböt arról, hogy a kutya nyert-e valamelyik szempontban. Szempontonként egy második bejárással jelöld meg azokat, akiknek a pontja megegyezik a győztes ponttal. ||
Hint 3: || A végén csak azokat a kutyákat írd ki, amelyek minden szempontban elérték az alsó határt, és nincsenek megjelölve. A kiírás az indexek szerinti bejárásból adódik, így a sorszámok automatikusan növekvő sorrendben jönnek. ||
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

    vector<bool> nyert(n, false);
    for (int j = 0; j < m; j++) {
        int legjobb = -1;
        for (int i = 0; i < n; i++)
            if (p[i][j] >= minPont[j]) legjobb = max(legjobb, p[i][j]);
        if (legjobb < 0) continue;
        // az alsó határ alatti pont kisebb a legjobbnál, így nem jelölődik meg
        for (int i = 0; i < n; i++)
            if (p[i][j] == legjobb) nyert[i] = true;
    }

    vector<int> valasz;
    for (int i = 0; i < n; i++) {
        bool bent = true;
        for (int j = 0; j < m; j++)
            if (p[i][j] < minPont[j]) bent = false;
        if (bent && !nyert[i]) valasz.push_back(i + 1);
    }

    cout << valasz.size();
    for (int x : valasz) cout << ' ' << x;
    cout << '\n';
    return 0;
}
