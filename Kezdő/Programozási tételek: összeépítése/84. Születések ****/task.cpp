/*
Megoldás lényege:
Minden születési dátumot egyetlen egész számmá kódolunk úgy, hogy a sorrend megmaradjon: a kulcs év*372 + (hónap-1)*31 + (nap-1). Egy (E,H,N) kezdő dátumú egy éves intervallum pontosan azokat a születéseket tartalmazza, amelyek kulcsa a K kulcstól kezdve 372-nél kisebb tartományba esik. Elég olyan kezdő dátumot vizsgálni, amely valakinek a születésnapja, mert ha egy optimális intervallum kezdete nem születési nap, a kezdetét az első utána következő születési napra tolva a darabszám nem csökken. Rendezés után minden különböző kulcsra két lower_bound hívással megszámoljuk a darabszámot, és a legkorábbi maximumot tartjuk meg. Az időigény O(M log M).
*/
/*
Hint 1: || Egy dátumot úgy kódolj egyetlen számmá, hogy az év, a hónap és a nap sorrendje megmaradjon, például év*372 + (hónap-1)*31 + (nap-1). ||
Hint 2: || Egy (E,H,N) kezdő dátumú intervallum pontosan azokat a kulcsokat tartalmazza, amelyek a kezdő kulcstól kezdve 372-nél kisebb távolságra vannak. Elég olyan kezdő dátumot nézni, amely valakinek a születésnapja. ||
Hint 3: || Rendezd a kulcsokat, majd minden különböző kulcsra két bináris kereséssel (lower_bound) számold meg a K és a K+372 közötti elemeket; a legnagyobb darabszámot a növekvő bejárás első előfordulásánál tartsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

const long long NAPSZAM = 372; // 12 hónap * 31 nap: a (hónap, nap) páros egy számmal kódolható

int main() {
    int m;
    cin >> m;

    vector<long long> kulcs(m);
    for (int i = 0; i < m; ++i) {
        long long ev, ho, nap;
        cin >> ev >> ho >> nap;
        kulcs[i] = ev * NAPSZAM + (ho - 1) * 31 + (nap - 1);
    }
    sort(kulcs.begin(), kulcs.end());

    long long legjobbDb = 0, legjobbK = -1;
    for (int i = 0; i < m; ++i) {
        if (i > 0 && kulcs[i] == kulcs[i - 1]) continue;
        long long k = kulcs[i];
        long long vege = lower_bound(kulcs.begin(), kulcs.end(), k + NAPSZAM) - kulcs.begin();
        long long db = vege - i;
        if (db > legjobbDb) {
            legjobbDb = db;
            legjobbK = k;
        }
    }

    long long ev = legjobbK / NAPSZAM;
    long long maradek = legjobbK % NAPSZAM;
    long long ho = maradek / 31 + 1;
    long long nap = maradek % 31 + 1;
    cout << ev << ' ' << ho << ' ' << nap << '\n';
    return 0;
}
