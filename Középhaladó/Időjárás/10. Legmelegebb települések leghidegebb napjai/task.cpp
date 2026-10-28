/*
Megoldás lényege:
Legmelegebb településnek azt tekintjük, amelynél valamelyik napon előfordul az országos maximum (az összes N · M érték legnagyobbja).
Ezeknek a településeknek a sorát megvizsgáljuk, megkeressük a saját minimumukat, és azokat a napokat megjelöljük, ahol ez a minimum van.
A kimenet azok a napok, amelyeket legalább egy legmelegebb település minimumnapjaként megjelöltünk, növekvő sorrendben.
Mivel az országos maximumot csak a teljes beolvasás után lehet tudni, a táblázatot először teljesen be kell olvasni.
Az idő O(N · M).
*/
/*
Hint 1: || Először az országos maximumot kell megtalálni, és azokat a településeket, amelyeknél ez előfordul. Csak ezekkel a sorokkal kell tovább foglalkozni. ||
Hint 2: || Egy legmelegebb település sorában keresd meg a legkisebb értéket, és jegyezd meg, mely napokon fordul elő. Ehhez a táblázatot el kell tárolni, mert az országos maximum csak a beolvasás után ismert. ||
Hint 3: || A megjelölt napokat egy logikai tömbben (vector<bool>) tartsd nyilván, a végén pedig a megjelölt napok sorszámát írd ki növekvő sorrendben. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> h(n, vector<int>(m));
    int globalMax = INT_MIN;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cin >> h[i][j];
        globalMax = max(globalMax, *max_element(h[i].begin(), h[i].end()));
    }

    vector<bool> coldestDay(m, false);
    for (int i = 0; i < n; i++) {
        if (*max_element(h[i].begin(), h[i].end()) != globalMax)
            continue;
        int rowMin = *min_element(h[i].begin(), h[i].end());
        for (int j = 0; j < m; j++)
            if (h[i][j] == rowMin)
                coldestDay[j] = true;
    }

    vector<int> days;
    for (int j = 0; j < m; j++)
        if (coldestDay[j])
            days.push_back(j + 1);

    cout << days.size();
    for (int d : days)
        cout << ' ' << d;
    cout << '\n';
    return 0;
}
