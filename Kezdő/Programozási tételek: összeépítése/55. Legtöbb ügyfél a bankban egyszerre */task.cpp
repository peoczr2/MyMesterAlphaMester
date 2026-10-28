/*
Megoldás lényege: az események időrendben érkeznek, ezért a bent lévő ügyfelek száma a két esemény között állandó.
Az időtengelyt szakaszokra bontjuk: minden szakasz egy esemény időpontjától a következő eseményig tart (az utolsó
szakasz 23:59-ig). Belépésnél a kártyaszámot a halmazba tesszük, kilépésnél kivesszük, pénzműveletnél nem
változik a bentlévők száma. Megkeressük a legnagyobb létszámot, majd az első olyan időszakot, ahol ez a létszám
van: az időszak kezdete az érkezési, a vége pedig az a pillanat, amikor a létszám először csökken (kilépés vagy 23:59).
Az egymás után következő, azonos maximális létszámú szakaszokat összevonjuk. Időigény O(N log N).
*/
/*
Hint 1: || Az események között a bent lévők száma nem változik, így elég a változás pillanatait vizsgálni. Minden esemény után a bentlévők száma egy szakaszon át állandó. ||
Hint 2: || Egy halmazban tárold a bent lévő kártyaszámokat: belépésnél szúrd be, kilépésnél töröld. A pénzfelvétel és a pénzbefizetés nem változtatja a létszámot. ||
Hint 3: || Készíts szakaszokat [kezdet, vég) formában, a nap végéig (23:59) tartva. A maximális létszámú szakaszok közül az elsőt keresd meg, és a szomszédos ugyanilyen szakaszokat vond össze. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    struct Seg {
        int s, e, cnt; // [s, e) időszakban cnt ügyfél volt bent (percben számolva)
    };
    vector<Seg> segs;
    set<long long> inside; // a bent lévő kártyák
    int prev = 0;          // az aktuális szakasz kezdete, a nap 0:00-ától indulunk

    for (int i = 0; i < n; i++) {
        int h, m, type;
        long long val;
        cin >> h >> m >> type >> val;
        int t = h * 60 + m;

        if (t > prev) segs.push_back({prev, t, (int)inside.size()});

        if (type == 1) inside.insert(val);      // belépés
        else if (type == -1) inside.erase(val); // kilépés
        // -2 (pénzfelvétel) és 2 (pénzbefizetés): nem változtatja a bentlévők számát
        prev = t;
    }

    const int END = 23 * 60 + 59; // 23:59-kor mindenkit kiküldenek
    if (END > prev) segs.push_back({prev, END, (int)inside.size()});

    int best = -1;
    for (const Seg &sg : segs) best = max(best, sg.cnt);

    for (size_t i = 0; i < segs.size(); i++) {
        if (segs[i].cnt != best) continue;
        int s = segs[i].s, e = segs[i].e;
        size_t j = i + 1;
        while (j < segs.size() && segs[j].cnt == best) { // összevonjuk a szomszédos azonos szakaszokat
            e = segs[j].e;
            j++;
        }
        cout << s / 60 << ' ' << s % 60 << ' ' << e / 60 << ' ' << e % 60 << '\n';
        break; // az első (legkorábbi) ilyen időszak kell
    }
    return 0;
}
