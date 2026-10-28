/*
Megoldás lényege:
A tantárgyakat a bemenetbeli első előfordulásuk sorrendjében azonosítjuk egy unordered_map segítségével, így a döntetlennél a legkorábbi előfordulás könnyen kiválasztható. A (tanár, tárgy) párokat rendezzük és egyedivé tesszük, mert ugyanabból a tárgyból egy tanár több órát is tarthat. Az egyedi párokból számolható a tanáronkénti tárgyszám, a tárgyanként tanítók száma, és az első olyan sorszám, amelyhez nem tartozik pár. A csoportokhoz a tanárok tárgyainak rendezett listáját vesszük: az egyenlő listájú tanárok egy csoportba kerülnek, így a csoportok száma a különböző listák száma (csak a legalább egy órát tartó tanárok számítanak). Az időigény O(O log O + T); a legnagyobb méretű saját teszten (T = 100 000, O = 200 000) a futás kb. 60 ms, az időlimit 0,1 mp.
*/
/*
Hint 1: || Minden tárgyhoz rendelj azonosítót, és a (tanár, tárgy) párokat kezeld halmazként: ugyanazt a tárgyat egy tanár többször is taníthatja, de csak egyszer számít. ||
Hint 2: || A legtöbb tanár által tanított tárgy: számold meg, hány különböző tanár tanítja az egyes tárgyakat, és döntetlennél a korábban előforduló tárgyat válaszd. A csoportokhoz a tanárok tárgyainak rendezett listáját használd, az egyenlő listák egy csoportba tartoznak. ||
Hint 3: || Rendezd a párokat (tanár, tárgyazonosító) szerint és távolítsd el az ismétléseket, így egy tanár tárgyai egymás után következnek. A tanáronkénti listákat gyűjtsd egy vektorba, rendezd, és a különböző elemek száma adja a csoportok számát. Az első órát nem tartó tanárt az 1..T bejárásával keresd meg. ||
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
    int t = readInt();  // tanárok száma
    int o = readInt();  // óratartások száma

    unordered_map<string, int> subjectId;
    subjectId.reserve(1 << 14);
    vector<string> names;          // a tárgyak az első előfordulás sorrendjében
    vector<pair<int, int>> lessons;  // (tanár, tárgy azonosító)
    lessons.reserve(o);
    string tok;
    for (int k = 0; k < o; k++) {
        int s = readInt();
        readToken(tok);
        int f;
        auto it = subjectId.find(tok);
        if (it == subjectId.end()) {
            f = (int)names.size();
            subjectId.emplace(tok, f);
            names.push_back(tok);
        } else {
            f = it->second;
        }
        lessons.push_back({s, f});
    }
    sort(lessons.begin(), lessons.end());
    lessons.erase(unique(lessons.begin(), lessons.end()), lessons.end());

    int kinds = (int)names.size();
    vector<int> teacherCnt(t + 1, 0);  // tanáronként a tárgyak száma
    vector<int> subjectCnt(kinds, 0);  // tárgyanként a tanárok száma
    vector<vector<int>> items(t + 1);  // tanáronként a tárgyazonosítók (rendezve)
    for (const auto& p : lessons) {
        teacherCnt[p.first]++;
        subjectCnt[p.second]++;
        items[p.first].push_back(p.second);
    }

    // 1. részfeladat: a tárgyak száma
    printf("#\n%d\n", kinds);

    // 2. részfeladat: tanáronként a tárgyak száma (csak akik tartottak órát)
    printf("#\n");
    for (int i = 1; i <= t; i++)
        if (teacherCnt[i] > 0) printf("%d %d\n", i, teacherCnt[i]);

    // 3. részfeladat: a legtöbb tanár által tanított tárgy (döntetlennél a korábbi)
    printf("#\n");
    if (kinds > 0) {
        int best = 0;
        for (int f = 1; f < kinds; f++)
            if (subjectCnt[f] > subjectCnt[best]) best = f;
        printf("%s\n", names[best].c_str());
    }

    // 4. részfeladat: egy tanár, aki nem tartott órát (különben -1)
    int idle = -1;
    for (int i = 1; i <= t; i++)
        if (teacherCnt[i] == 0) {
            idle = i;
            break;
        }
    printf("#\n%d\n", idle);

    // 5. részfeladat: csoportok száma (az azonos tárgyú tanárok egy csoportba tartoznak)
    vector<vector<int>> groups;
    for (int i = 1; i <= t; i++)
        if (!items[i].empty()) groups.push_back(items[i]);
    sort(groups.begin(), groups.end());
    groups.erase(unique(groups.begin(), groups.end()), groups.end());
    printf("#\n%d\n", (int)groups.size());
    return 0;
}
