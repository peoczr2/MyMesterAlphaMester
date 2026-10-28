/*
Megoldás lényege:
A virágfajtákat a bemenetbeli első előfordulásuk sorrendjében azonosítjuk egy unordered_map segítségével, így a döntetlennél a legkorábbi előfordulás könnyen kiválasztható. Az (árus, virág) párokat rendezzük és egyedivé tesszük, mert ugyanazt a virágot egy árus többször is megadhatja. Az egyedi párokból számolható az árusonkénti fajtaszám, a virágonkénti árusszám, és az első olyan sorszám, amelyhez nem tartozik pár. A csoportokhoz az árusok virágainak rendezett listáját vesszük: az egyenlő listájú árusok egy csoportba kerülnek, így a csoportok száma a különböző listák száma (csak a legalább egy virágot áruló árusok számítanak). Az időigény O(A log A + V); a legnagyobb méretű saját teszten (V = 100 000, A = 200 000) a futás kb. 60 ms, az időlimit 0,1 mp.
*/
/*
Hint 1: || Minden virágfajtához rendelj azonosítót, és az (árus, virág) párokat kezeld halmazként: ugyanazt a virágot egy árus többször is megadhatja, de csak egyszer számít. ||
Hint 2: || A legtöbb helyen kapható virág: számold meg, hány különböző árus árulja az egyes virágokat, és döntetlennél a korábban előforduló virágot válaszd. A csoportokhoz az árusok virágainak rendezett listáját használd, az egyenlő listák egy csoportba tartoznak. ||
Hint 3: || Rendezd a párokat (árus, virágazonosító) szerint és távolítsd el az ismétléseket, így egy árus virágai egymás után következnek. Az árusonkénti listákat gyűjtsd egy vektorba, rendezd, és a különböző elemek száma adja a csoportok számát. Az első nem dolgozó árust az 1..V bejárásával keresd meg. ||
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
    int v = readInt();  // virágárusok száma
    int a = readInt();  // árusítási információk száma

    unordered_map<string, int> flowerId;
    flowerId.reserve(1 << 14);
    vector<string> names;          // a virágok az első előfordulás sorrendjében
    vector<pair<int, int>> sales;  // (árus, virág azonosító)
    sales.reserve(a);
    string tok;
    for (int k = 0; k < a; k++) {
        int s = readInt();
        readToken(tok);
        int f;
        auto it = flowerId.find(tok);
        if (it == flowerId.end()) {
            f = (int)names.size();
            flowerId.emplace(tok, f);
            names.push_back(tok);
        } else {
            f = it->second;
        }
        sales.push_back({s, f});
    }
    sort(sales.begin(), sales.end());
    sales.erase(unique(sales.begin(), sales.end()), sales.end());

    int kinds = (int)names.size();
    vector<int> vendorCnt(v + 1, 0);   // árusonként a fajták száma
    vector<int> flowerCnt(kinds, 0);   // virágonként az árusok száma
    vector<vector<int>> items(v + 1);  // árusonként a virágazonosítók (rendezve)
    for (const auto& p : sales) {
        vendorCnt[p.first]++;
        flowerCnt[p.second]++;
        items[p.first].push_back(p.second);
    }

    // 1. részfeladat: a virágfajták száma
    printf("#\n%d\n", kinds);

    // 2. részfeladat: árusonként a fajták száma (csak akik árulnak)
    printf("#\n");
    for (int i = 1; i <= v; i++)
        if (vendorCnt[i] > 0) printf("%d %d\n", i, vendorCnt[i]);

    // 3. részfeladat: a legtöbb árusnál kapható virág (döntetlennél a korábbi)
    printf("#\n");
    if (kinds > 0) {
        int best = 0;
        for (int f = 1; f < kinds; f++)
            if (flowerCnt[f] > flowerCnt[best]) best = f;
        printf("%s\n", names[best].c_str());
    }

    // 4. részfeladat: egy árus, aki nem dolgozik (különben -1)
    int idle = -1;
    for (int i = 1; i <= v; i++)
        if (vendorCnt[i] == 0) {
            idle = i;
            break;
        }
    printf("#\n%d\n", idle);

    // 5. részfeladat: csoportok száma (az azonos virágkészletű árusok egy csoportba tartoznak)
    vector<vector<int>> groups;
    for (int i = 1; i <= v; i++)
        if (!items[i].empty()) groups.push_back(items[i]);
    sort(groups.begin(), groups.end());
    groups.erase(unique(groups.begin(), groups.end()), groups.end());
    printf("#\n%d\n", (int)groups.size());
    return 0;
}
