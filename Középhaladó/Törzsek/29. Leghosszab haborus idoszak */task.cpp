/*
Megoldás lényege:
Egy időszak akkor háborús, ha legalább egy háború zajlik benne, ezért a háborúk időintervallumait egyesítjük. Kezdő év szerint rendezzük a háborúkat, majd egy lineáris bejárással összevonjuk azokat, amelyek átfedik vagy érintik az előző összevont szakaszt (a következő kezdete nem nagyobb az aktuális végénél). Így diszjunkt, háborús szakaszok listáját kapjuk, amelyek közül a leghosszabbat választjuk, döntetlennél a korábbit. Az időigény O(K log K), a rendezés dominál.
*/
/*
Hint 1: || Az a kérdés, mikor van legalább egy háború. Ehhez a háborúk időintervallumait kell egyesíteni, és ehhez érdemes őket kezdő év szerint rendezni. ||
Hint 2: || Egy következő háború vagy az utolsó összevont szakaszba tartozik (kezdete nem későbbi annak végénél), vagy új szakaszt nyit. Az összevont szakaszok közül a legnagyobb vég - kezdet különbségű adja a választ. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> haboru(k); // (kezdés, befejezés)
    for (auto &h : haboru) {
        int a, b;
        cin >> a >> b >> h.first >> h.second;
    }
    sort(haboru.begin(), haboru.end());

    // Összevont háborús időszakok
    vector<pair<int, int>> idoszak;
    for (const auto &h : haboru) {
        if (!idoszak.empty() && h.first <= idoszak.back().second)
            idoszak.back().second = max(idoszak.back().second, h.second);
        else
            idoszak.push_back(h);
    }

    pair<int, int> legjobb = {0, 0};
    int legjobb_hossz = -1;
    for (const auto &p : idoszak) {
        if (p.second - p.first > legjobb_hossz) {
            legjobb_hossz = p.second - p.first;
            legjobb = p;
        }
    }
    cout << legjobb.first << " " << legjobb.second << "\n";
    return 0;
}
