/*
Megoldás lényege:
A címeket 8 darab 16 bites csoportra bontjuk, így két cím összehasonlítása csoportonként, számértékként történik,
a legalacsonyabb cím pedig egyszerű minimumkereséssel adódik. A típust a cím első karakterei (2001:0db8, 2001:0e,
fc/fd) döntik el, a nullák számát pedig a '0' karakterek összeszámlálása adja. A rövidített alak két lépésben készül:
minden csoportból elhagyjuk a bevezető nullákat, a csupa nulla csoportok közül pedig a leghosszabb, legalább két
csoportból álló szakaszt (azonos hosszúságnál a balról elsőt) '::' jelölésre cseréljük. Minden részfeladat a cím
hosszában, illetve a címek számában lineáris, így az időigény messze a 0,1 mp-es limit alatt marad.
*/
/*
Hint 1: || A típus a cím kezdetéből, a nullák száma pedig a '0' karakterek összeszámlálásából állapítható meg. A legalacsonyabb cím a csoportonkénti számértékek összehasonlításával keresendő. ||
Hint 2: || A rövidítésnél bontsd a címet 8 csoportra, majd keresd meg a csupa nullából álló, egymást követő csoportok szakaszait. Csak a legalább két csoportból álló szakaszok számítanak, és ezek közül a leghosszabbat (egyenlőségnél a balról elsőt) kell '::'-ra cserélni. ||
Hint 3: || A többi csoportból a bevezető nullákat töröld, de a csupa nulla csoport egyetlen '0' maradjon. Ha nincs legalább kétcsoportnyi nullás szakasz, a rövidítés helyett '-' jelet kell kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A cím 8 csoportra bontása (a csoportok szövegként maradnak).
vector<string> groups(const string &addr) {
    vector<string> g;
    string cur;
    for (char c : addr) {
        if (c == ':') {
            g.push_back(cur);
            cur.clear();
        } else {
            cur += c;
        }
    }
    g.push_back(cur);
    return g;
}

// Csoport bevezető nulláinak elhagyása; a csupa nulla csoport "0" lesz.
string strip(const string &grp) {
    size_t p = grp.find_first_not_of('0');
    return p == string::npos ? "0" : grp.substr(p);
}

bool allZero(const string &grp) {
    return grp.find_first_not_of('0') == string::npos;
}

// A cím számértéke csoportonként (hexadecimálisan), a rendezéshez.
array<unsigned long, 8> numeric(const string &addr) {
    array<unsigned long, 8> v{};
    vector<string> g = groups(addr);
    for (int i = 0; i < 8; i++) v[i] = stoul(g[i], nullptr, 16);
    return v;
}

// A [from, to) csoportok bevezető nullák nélkül, kettősponttal összefűzve.
string joinStripped(const vector<string> &g, int from, int to) {
    string r;
    for (int i = from; i < to; i++) {
        if (i > from) r += ':';
        r += strip(g[i]);
    }
    return r;
}

// A cím rövidítése az egymást követő nullás csoportok szabálya szerint.
string compress(const string &addr) {
    vector<string> g = groups(addr);
    int bestStart = -1, bestLen = 0;
    int i = 0;
    while (i < 8) {
        if (!allZero(g[i])) {
            i++;
            continue;
        }
        int j = i;
        while (j < 8 && allZero(g[j])) j++;
        if (j - i > bestLen) {  // szigorúan nagyobb: azonos hossznál a balról első marad
            bestLen = j - i;
            bestStart = i;
        }
        i = j;
    }
    if (bestLen < 2) return "-";
    return joinStripped(g, 0, bestStart) + "::" + joinStripped(g, bestStart + bestLen, 8);
}

int main() {
    int n, s;
    cin >> n >> s;
    vector<string> ip(n);
    for (auto &x : ip) cin >> x;

    // 1. részfeladat: a legalacsonyabb IP-cím
    int low = 0;
    for (int i = 1; i < n; i++)
        if (numeric(ip[i]) < numeric(ip[low])) low = i;

    // 2. részfeladat: darabszám típusonként (dokumentációs, globális, helyi)
    int doc = 0, glob = 0, loc = 0;
    for (const string &x : ip) {
        if (x.compare(0, 9, "2001:0db8") == 0) doc++;
        else if (x.compare(0, 7, "2001:0e") == 0) glob++;
        else if (x.compare(0, 2, "fc") == 0 || x.compare(0, 2, "fd") == 0) loc++;
    }

    // 3. részfeladat: legalább 18 nullát tartalmazó címek (sorszámmal)
    vector<int> many;
    for (int i = 0; i < n; i++)
        if (count(ip[i].begin(), ip[i].end(), '0') >= 18) many.push_back(i);

    const string &sAddr = ip[s - 1];

    cout << "#\n" << ip[low] << "\n";
    cout << "#\n" << doc << " " << glob << " " << loc << "\n";
    cout << "#\n" << many.size() << "\n";
    for (int i : many) cout << i + 1 << " " << ip[i] << "\n";
    // 4. részfeladat: az S. cím csoportonkénti bevezető nullák nélkül
    cout << "#\n" << joinStripped(groups(sAddr), 0, 8) << "\n";
    // 5. részfeladat: az S. cím rövidítése nullás csoportokkal
    cout << "#\n" << compress(sAddr) << "\n";
    return 0;
}
