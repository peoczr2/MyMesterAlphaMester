/*
Megoldás lényege:
A nyelveket a bemenetbeli első előfordulásuk sorrendjében azonosítjuk egy unordered_map segítségével. A (hallgató, nyelv) párokat rendezzük és egyedivé tesszük, mert egy hallgató ugyanazt a nyelvet többször is megadhatja. Az egyedi párokból nyelvenként megszámolható, hányan beszélik, hallgatónként pedig, hány nyelven beszél. Az egyetlen hallgató által beszélt nyelv az első olyan nyelv, amelyet egyetlen hallgató beszél, különben NINCS. A legtöbb nyelven beszélő hallgató a maximális nyelvszámú hallgató közül a legkisebb sorszámú. A csoportban bárki bárkivel bármely általa beszélt nyelven beszélhet, ezért a csoport minden tagjának ugyanazokat a nyelveket kell beszélnie: az azonos nyelvkészletű hallgatók alkotnak egy csoportot. A csoportok száma a különböző (rendezett) nyelvlisták száma, csak a legalább egy nyelven beszélő hallgatók számítanak. Az időigény O(M log M + N); a legnagyobb méretű saját teszten (N = 100 000, M = 200 000) a futás kb. 60 ms, az időlimit 0,1 mp.
*/
/*
Hint 1: || Minden nyelvhez rendelj azonosítót, és a (hallgató, nyelv) párokat egyedi párokként kezeld: egy hallgató ugyanazt a nyelvet többször is megadhatja, de csak egyszer számít. ||
Hint 2: || Nyelvenként számold meg, hány hallgató beszéli: az egyetlen hallgató által beszélt nyelv ebből adódik. A csoportokhoz a hallgatók nyelvkészletét rendezett listaként használd: két hallgató akkor kerülhet egy csoportba, ha a nyelvkészletük teljesen azonos. ||
Hint 3: || Rendezd a párokat (hallgató, nyelvazonosító) szerint, így egy hallgató nyelvei egymás után következnek. Hallgatónként számold a nyelveket, és a maximumot keresd a bejárással, döntetlennél a kisebb sorszámút tartsd meg. A listákat gyűjtsd egy vektorba, rendezd, és a különböző elemek száma adja a csoportok számát. ||
*/
#include <bits/stdc++.h>
using namespace std;

static char ibuf[1 << 16];
static size_t ipos = 0, ilen = 0;

static inline int gc() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return (unsigned char)ibuf[ipos++];
}

static inline void readToken(string& s) {
    s.clear();
    int c = gc();
    while (c != -1 && isspace(c)) c = gc();
    while (c != -1 && !isspace(c)) {
        s.push_back((char)c);
        c = gc();
    }
}

static inline int readInt() {
    int c = gc();
    while (c != -1 && !(c >= '0' && c <= '9')) c = gc();
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

int main() {
    int n = readInt();  // hallgatók száma
    int m = readInt();  // nyelvmegadások száma

    unordered_map<string, int> langId;
    langId.reserve(1 << 14);
    vector<string> names;            // a nyelvek az első előfordulás sorrendjében
    vector<pair<int, int>> pairs;    // (hallgató, nyelv azonosító)
    pairs.reserve(m);
    string tok;
    for (int k = 0; k < m; k++) {
        readToken(tok);
        int student = readInt();
        int f;
        auto it = langId.find(tok);
        if (it == langId.end()) {
            f = (int)names.size();
            langId.emplace(tok, f);
            names.push_back(tok);
        } else {
            f = it->second;
        }
        pairs.push_back({student, f});
    }
    sort(pairs.begin(), pairs.end());
    pairs.erase(unique(pairs.begin(), pairs.end()), pairs.end());

    int kinds = (int)names.size();
    vector<int> speakerCnt(kinds, 0);  // nyelvenként a beszélők száma
    vector<int> langCnt(n + 1, 0);     // hallgatónként a nyelvek száma
    vector<vector<int>> items(n + 1);  // hallgatónként a nyelvazonosítók (rendezve)
    for (const auto& p : pairs) {
        speakerCnt[p.second]++;
        langCnt[p.first]++;
        items[p.first].push_back(p.second);
    }

    // 1. részfeladat: a beszélt nyelvek száma
    printf("#\n%d\n", kinds);

    // 2. részfeladat: egy nyelv, amelyet csak egy hallgató beszél (különben NINCS)
    printf("#\n");
    int single = -1;
    for (int f = 0; f < kinds; f++)
        if (speakerCnt[f] == 1) {
            single = f;
            break;
        }
    printf("%s\n", single >= 0 ? names[single].c_str() : "NINCS");

    // 3. részfeladat: nyelvenként a beszélők száma
    printf("#\n");
    for (int f = 0; f < kinds; f++)
        printf("%s %d\n", names[f].c_str(), speakerCnt[f]);

    // 4. részfeladat: a legtöbb nyelven beszélő hallgató (döntetlennél a legkisebb sorszám)
    int best = 1;
    for (int i = 2; i <= n; i++)
        if (langCnt[i] > langCnt[best]) best = i;
    printf("#\n%d\n", best);

    // 5. részfeladat: csoportok száma (az azonos nyelvkészletű hallgatók egy csoportba tartoznak)
    vector<vector<int>> groups;
    for (int i = 1; i <= n; i++)
        if (!items[i].empty()) groups.push_back(items[i]);
    sort(groups.begin(), groups.end());
    groups.erase(unique(groups.begin(), groups.end()), groups.end());
    printf("#\n%d\n", (int)groups.size());
    return 0;
}
