/*
Megoldás lényege:
A szakmákat a bemenetbeli első előfordulásuk sorrendjében azonosítjuk egy unordered_map segítségével. Az (iskola, szakma) párokat rendezzük és egyedivé tesszük, mert egy iskola ugyanazt a szakmát többször is megadhatja. Az egyedi párokból szakmánként megszámolható, hány iskolában tanítják, iskolánként pedig, hány szakmát tanít. Az egyetlen iskolában tanított szakma az első olyan szakma, amelyhez egyetlen iskola tartozik, különben NINCS. A legtöbb szakmát tanító iskola a maximális szakmaszámú iskola legkisebb sorszámú tagja. Az összevonás után az iskolák száma az egyenlő szakmalistájú iskolák csoportjainak száma, ahol csak a legalább egy szakmát tanító iskolák számítanak. Az időigény O(S log S + Sz); a legnagyobb méretű saját teszten (Sz = 100 000, S = 200 000) a futás kb. 60 ms, az időlimit 0,1 mp.
*/
/*
Hint 1: || Minden szakmához rendelj azonosítót, és az (iskola, szakma) párokat egyedi párokként kezeld: egy iskola ugyanazt a szakmát többször is megadhatja, de csak egyszer számít. ||
Hint 2: || Szakmánként számold meg, hány különböző iskolában tanítják: az egyetlen iskolában tanított szakma ebből adódik. Az iskolák összevonásához az iskolánkénti szakmalistát használd, az egyenlő listájú iskolák egy csoportba tartoznak. ||
Hint 3: || Rendezd a párokat (iskola, szakmaazonosító) szerint, így egy iskola szakmái egymás után következnek. Iskolánként számold a szakmákat, és a maximumot keresd a bejárással, döntetlennél a kisebb sorszámút tartsd meg. A listákat gyűjtsd egy vektorba, rendezd, és a különböző elemek száma adja az összevonások utáni iskolák számát. ||
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
    int sz = readInt();  // szakiskolák száma
    int s = readInt();   // szakma-megadások száma

    unordered_map<string, int> jobId;
    jobId.reserve(1 << 14);
    vector<string> names;            // a szakmák az első előfordulás sorrendjében
    vector<pair<int, int>> pairs;    // (iskola, szakma azonosító)
    pairs.reserve(s);
    string tok;
    for (int k = 0; k < s; k++) {
        readToken(tok);
        int school = readInt();
        int f;
        auto it = jobId.find(tok);
        if (it == jobId.end()) {
            f = (int)names.size();
            jobId.emplace(tok, f);
            names.push_back(tok);
        } else {
            f = it->second;
        }
        pairs.push_back({school, f});
    }
    sort(pairs.begin(), pairs.end());
    pairs.erase(unique(pairs.begin(), pairs.end()), pairs.end());

    int kinds = (int)names.size();
    vector<int> schoolCnt(kinds, 0);  // szakmánként az iskolák száma
    vector<int> jobCnt(sz + 1, 0);    // iskolánként a szakmák száma
    vector<vector<int>> items(sz + 1);  // iskolánként a szakmaazonosítók (rendezve)
    for (const auto& p : pairs) {
        schoolCnt[p.second]++;
        jobCnt[p.first]++;
        items[p.first].push_back(p.second);
    }

    // 1. részfeladat: a tanított szakmák száma
    printf("#\n%d\n", kinds);

    // 2. részfeladat: egy szakma, amelyet csak egy iskolában tanítanak (különben NINCS)
    printf("#\n");
    int single = -1;
    for (int f = 0; f < kinds; f++)
        if (schoolCnt[f] == 1) {
            single = f;
            break;
        }
    printf("%s\n", single >= 0 ? names[single].c_str() : "NINCS");

    // 3. részfeladat: szakmánként az iskolák száma
    printf("#\n");
    for (int f = 0; f < kinds; f++)
        printf("%s %d\n", names[f].c_str(), schoolCnt[f]);

    // 4. részfeladat: a legtöbb szakmát tanító iskola (döntetlennél a legkisebb sorszám)
    int best = 1;
    for (int i = 2; i <= sz; i++)
        if (jobCnt[i] > jobCnt[best]) best = i;
    printf("#\n%d\n", best);

    // 5. részfeladat: az összevonások utáni iskolák száma (legalább egy szakmát tanító iskolák)
    vector<vector<int>> groups;
    for (int i = 1; i <= sz; i++)
        if (!items[i].empty()) groups.push_back(items[i]);
    sort(groups.begin(), groups.end());
    groups.erase(unique(groups.begin(), groups.end()), groups.end());
    printf("#\n%d\n", (int)groups.size());
    return 0;
}
