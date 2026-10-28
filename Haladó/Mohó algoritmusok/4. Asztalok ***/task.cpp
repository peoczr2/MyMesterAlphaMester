/*
Feladat: N vendég mindegyike az [E, T] zárt időintervallumban van jelen. Asztalokhoz kell ültetni őket úgy,
hogy egy asztalnál legfeljebb K vendég üljön, és legyen olyan időpont, amikor az asztal minden vendége
egyszerre jelen van (azaz max E <= min T). Minimalizálni kell az asztalok számát, és meg kell adni egy beosztást.

Ötlet (mohó, "legkorábban távozó" horgony): Legyen v a még le nem ültetett vendégek közül a legkorábban
távozó, t = T_v. Van optimális megoldás, amelyben v asztalának közös időpontja éppen t: az asztal minden
tagja eljött t-ig (közös pont <= t) és senki sem megy el t előtt (t a legkisebb távozás). Ekkor v asztalához
a t-ben jelen lévő szabad vendégek közül a legkorábban távozó (legfeljebb K) vendéget érdemes ültetni:
ha egy ilyen x helyett egy később távozó y ül ott, x és y cseréje nem ront (y bárhol jelen van, ahol x,
mert E_y <= t és T_y >= T_x). Ezután ugyanez a feladat marad a többi vendégre.
Megvalósítás: idő szerint söprünk t = 1..100000. A t-ben érkezőket betesszük egy (távozás szerinti)
min-kupacba. Amíg a kupac tetején lévő vendég t-ben távozik, nyitunk egy asztalt, és a kupacból kivesszük
a legkorábban távozó legfeljebb K vendéget (mind jelen van t-ben).
Lépésszám: O(N log N + maxT), memória: O(N).
*/
/*
Hint 1: || Nézd a legkorábban távozó, még ültetetlen vendéget: az ő asztalának közös időpontja nyugodtan lehet az ő távozási ideje. ||
Hint 2: || Ebben az időpontban a jelen lévő szabad vendégek közül kiket ültess mellé? Azokat, akik a legkorábban távoznak, mert a később távozók a későbbi asztaloknál is felhasználhatók. ||
Hint 3: || Söpörj végig az időn, a jelen lévőket tartsd távozási idő szerinti min-kupacban, és ha a kupac tetején lévő vendég most távozik, vegyél ki legfeljebb K vendéget egy új asztalhoz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // beolvasás
    int n, k;
    cin >> n >> k;
    const int MAXT = 100000;
    vector<int> e(n + 1), t(n + 1);
    for (int i = 1; i <= n; i++) cin >> e[i] >> t[i];

    // a vendégek érkezési idő szerint rendezve (leszámláló rendezés)
    vector<int> kezd(MAXT + 2, 0);
    for (int i = 1; i <= n; i++) kezd[e[i] + 1]++;
    for (int x = 1; x <= MAXT + 1; x++) kezd[x] += kezd[x - 1];
    vector<int> sorrend(n);
    vector<int> poz(kezd.begin(), kezd.end());
    for (int i = 1; i <= n; i++) sorrend[poz[e[i]]++] = i;

    // jelen lévő, még le nem ültetett vendégek: (távozás, sorszám) min-kupac
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> jelen;

    vector<int> ultetes;     // a vendégek sorszáma asztalonként egymás után
    vector<int> asztalVege;  // asztalVege[j] = a j. asztal utáni pozíció az ultetes tömbben
    ultetes.reserve(n);

    for (int x = 1; x <= MAXT; x++) {
        // az x-ben érkezők bekerülnek
        for (int p = kezd[x]; p < kezd[x + 1]; p++) jelen.push({t[sorrend[p]], sorrend[p]});

        // amíg valaki most távozik, új asztal: a legkorábban távozó legfeljebb K jelen lévő vendég
        while (!jelen.empty() && jelen.top().first == x) {
            for (int db = 0; db < k && !jelen.empty(); db++) {
                ultetes.push_back(jelen.top().second);
                jelen.pop();
            }
            asztalVege.push_back((int)ultetes.size());
        }
    }

    // kiírás: asztalonként egy sor
    cout << asztalVege.size() << '\n';
    int p = 0;
    for (int veg : asztalVege) {
        for (; p < veg; p++) cout << ultetes[p] << (p + 1 < veg ? ' ' : '\n');
    }
    return 0;
}
