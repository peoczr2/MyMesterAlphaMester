/*
Megoldás lényege:
A menetrendet Á×V-es táblázatban tároljuk, minden cella egy (érkezés, indulás) pár. Megállás akkor van, ha a két idő valós és különböző; az egyenlő pár áthaladást jelent, a -1 pedig végállomást: (-1, indulás) a kezdő, (érkezés, -1) a záró végállomás. Az 1. részfeladatban a Budapestről induló és Székesfehérvárra érkező vonatokat számoljuk. A 2. részfeladatban a legrövidebb megállást keressük, egyenlőségnél a legkisebb állomássorszámot tartva meg. A 3. részfeladatban a két közbülső végállomású vonat menetideje a záró érkezés mínusz a kezdő indulás. A 4. részfeladatban vonatonként megszámoljuk a megállásokat. Az 5. részfeladatban a Székesfehérvárról induló vonatokat gyűjtjük ki, és azokat az állomásokat keressük, ahol ezek egyike sem áll meg és nem végállomás; ezek darabszámát és sorszámát írjuk ki növekvő sorrendben.
Az időigény O(Á·V), ami a legfeljebb 20·50-es táblázat miatt elhanyagolható.
*/
/*
Hint 1: || Minden cellánál döntsd el, hogy valós megállás-e (mindkét idő nem -1, és a kettő nem egyenlő), vagy végállomás. Ezek a mezők adják a többi részfeladat alapját. ||
Hint 2: || A kezdő végállomás az a mező, ahol az érkezés -1, a záró végállomásé ahol az indulás -1. Így az 1. részfeladat a vonatok kezdő- és záróállomásából adódik, a 3. részfeladatban pedig a menetidő a záró érkezés mínusz a kezdő indulás. ||
Hint 3: || Az 5. részfeladatban először gyűjtsd ki a Székesfehérvárról induló vonatokat, majd jelöld meg azokat az állomásokat, ahol ezek megállnak vagy véget érnek. A meg nem jelölt állomások sorszámait és darabszámát kell kiírni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A, V;
    cin >> A >> V;

    // t[i][j]: a j. vonat i. állomáson mért (érkezés, indulás) párja; i = 0 Budapest, i = A-1 Székesfehérvár
    vector<vector<pair<int, int>>> t(A, vector<pair<int, int>>(V));
    for (int i = 0; i < A; ++i)
        for (int j = 0; j < V; ++j)
            cin >> t[i][j].first >> t[i][j].second;

    // valós megállás: mindkét idő ismert, és nem egyenlők (az egyenlő pár áthaladás)
    auto isStop = [&](int i, int j) {
        return t[i][j].first != -1 && t[i][j].second != -1 && t[i][j].first != t[i][j].second;
    };
    // induló végállomás: nincs érkezés, van indulás
    auto isStart = [&](int i, int j) {
        return t[i][j].first == -1 && t[i][j].second != -1;
    };
    // érkező végállomás: van érkezés, nincs indulás
    auto isEnd = [&](int i, int j) {
        return t[i][j].first != -1 && t[i][j].second == -1;
    };

    // 1. részfeladat: Budapestről induló, Székesfehérvárra érkező vonatok
    int cnt1 = 0;
    for (int j = 0; j < V; ++j)
        if (isStart(0, j) && isEnd(A - 1, j)) ++cnt1;
    cout << "#\n" << cnt1 << "\n";

    // 2. részfeladat: legrövidebb megállás (egyenlőségnél a legkisebb állomássorszám)
    int bestDur = INT_MAX, bestSt = 0;
    for (int i = 0; i < A; ++i)
        for (int j = 0; j < V; ++j)
            if (isStop(i, j) && t[i][j].second - t[i][j].first < bestDur) {
                bestDur = t[i][j].second - t[i][j].first;
                bestSt = i;
            }
    cout << "#\n" << bestSt + 1 << "\n";

    // 3. részfeladat: mindkét végállomás közbülső (nem Budapest, nem Székesfehérvár)
    vector<pair<int, int>> pairs;  // (vonat sorszáma, menetidő)
    for (int j = 0; j < V; ++j) {
        int s = -1, e = -1;
        for (int i = 0; i < A; ++i) {
            if (isStart(i, j)) s = i;
            if (isEnd(i, j)) e = i;
        }
        if (s > 0 && s < A - 1 && e > 0 && e < A - 1)
            pairs.push_back({j + 1, t[e][j].first - t[s][j].second});
    }
    cout << "#\n" << pairs.size();
    for (auto [train, time] : pairs) cout << ' ' << train << ' ' << time;
    cout << "\n";

    // 4. részfeladat: a legtöbb közbülső megállású vonat (egyenlőségnél a legkisebb sorszám)
    int bestTrain = 0, bestStops = -1;
    for (int j = 0; j < V; ++j) {
        int stops = 0;
        for (int i = 0; i < A; ++i)
            if (isStop(i, j)) ++stops;
        if (stops > bestStops) {
            bestStops = stops;
            bestTrain = j;
        }
    }
    cout << "#\n" << bestTrain + 1 << "\n";

    // 5. részfeladat: a Székesfehérvárról induló vonatok, és az ezekkel el nem érhető állomások
    vector<int> fromSf;
    for (int j = 0; j < V; ++j)
        if (isStart(A - 1, j) || isStop(A - 1, j)) fromSf.push_back(j);
    vector<bool> reach(A, false);
    for (int j : fromSf)
        for (int i = 0; i < A - 1; ++i)
            if (isStop(i, j) || isEnd(i, j)) reach[i] = true;
    vector<int> unreachable;
    for (int i = 0; i < A - 1; ++i)
        if (!reach[i]) unreachable.push_back(i + 1);
    cout << "#\n" << unreachable.size();
    for (int s : unreachable) cout << ' ' << s;
    cout << "\n";

    return 0;
}
