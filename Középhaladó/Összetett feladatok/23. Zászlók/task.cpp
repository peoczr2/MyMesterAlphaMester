/*
Megoldás lényege:
A színeket egy hash-táblával azonosítókká alakítjuk, az első előfordulás sorrendjében. Országonként a színazonosítókat rendezzük és egyedivé tesszük, így az ismétlődő megadások nem torzítanak. A színek száma az azonosítók száma, egy szín zászlóinak száma pedig az országonkénti egyedi listákban való előfordulások száma. A csoportok száma a különböző (rendezett) színlisták száma: a listákra mutató mutatókat rendezzük, és az egymást követő különböző listákat számoljuk, csak a legalább egy színnel rendelkező országok számítanak. Az időigény O(S log S), a bemenetet pufferelt olvasással dolgozzuk fel, így a 0,1 másodperces időlimit belefér.
*/
/*
Hint 1: || Minden színhez egyszer rendelj azonosítót egy unordered_map segítségével, és az országonként gyűjtött színlistát rendezés után tedd egyedivé. ||
Hint 2: || Egy szín zászlóinak száma: az országonkénti egyedi listákban számold meg a szín előfordulásait, így ugyanaz a szín egy zászlón csak egyszer számít. ||
Hint 3: || A csoportok száma a különböző színlisták száma: a listákra mutató mutatókat rendezd a listák szerint, és az egymást követő különbözőket számold meg. Csak azokat az országokat vedd figyelembe, amelyeknek van legalább egy színük. ||
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
    int o = readInt();
    int s = readInt();

    unordered_map<string, int> id;
    id.reserve(1 << 15);
    vector<string> names;  // a színek az első előfordulásuk sorrendjében
    vector<vector<int>> flags(o + 1);
    string tok;
    for (int k = 0; k < s; k++) {
        readToken(tok);
        int h = readInt();
        auto it = id.find(tok);
        int cid;
        if (it == id.end()) {
            cid = (int)names.size();
            id.emplace(tok, cid);
            names.push_back(tok);
        } else {
            cid = it->second;
        }
        flags[h].push_back(cid);
    }

    int colours = (int)names.size();
    vector<int> cnt(colours, 0);
    for (int h = 1; h <= o; h++) {
        vector<int>& v = flags[h];
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        for (int c : v) cnt[c]++;
    }

    // 1. részfeladat: a használt színek száma
    cout << "#\n" << colours << "\n";

    // 2. részfeladat: egy szín, amely csak egy zászlón szerepel
    int uniq = -1;
    for (int c = 0; c < colours; c++) {
        if (cnt[c] == 1) {
            uniq = c;
            break;
        }
    }
    cout << "#\n" << (uniq == -1 ? string("NINCS") : names[uniq]) << "\n";

    // 3. részfeladat: minden szín és a zászlók száma, amelyeken szerepel
    cout << "#\n";
    for (int c = 0; c < colours; c++) cout << names[c] << ' ' << cnt[c] << "\n";

    // 4. részfeladat: a legtöbb színt használó ország (döntetlennél a kisebb sorszám)
    int bestH = 0;
    size_t bestN = 0;
    for (int h = 1; h <= o; h++) {
        if (flags[h].size() > bestN) {
            bestN = flags[h].size();
            bestH = h;
        }
    }
    cout << "#\n" << bestH << "\n";

    // 5. részfeladat: a csoportok száma (az azonos színhalmazú zászlók egy csoportba kerülnek)
    vector<const vector<int>*> lists;
    for (int h = 1; h <= o; h++)
        if (!flags[h].empty()) lists.push_back(&flags[h]);
    sort(lists.begin(), lists.end(),
         [](const vector<int>* a, const vector<int>* b) { return *a < *b; });
    int groups = 0;
    for (size_t i = 0; i < lists.size(); i++)
        if (i == 0 || *lists[i] != *lists[i - 1]) groups++;
    cout << "#\n" << groups << "\n";
    return 0;
}
