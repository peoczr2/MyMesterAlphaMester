/*
Megoldás lényege:
A fordítás két menetben történik. Az első menetben minden utasítás hosszát kiszámoljuk (szám és karakter esetén a DB,
karakterlánc esetén a hossza, cím esetén 2, tárhivatkozás esetén 1 rekesz), így minden címke címe, azaz a rekesz sorszáma
az utasítás előtt, már ismert lesz, még az előre hivatkozott címkéké is. A második menetben az utasításokat sorrendben
hajtjuk végre: a tár egy tömb, a következő szabad rekesz sorszámát egy számláló adja. A <X> utasítás a cím alacsonyabb,
majd magasabb helyi értékű bájtját írja. A [X] utasítás a címen a program végén álló értéket másolja, mert az X rekesz
is lehet később írt, vagy egy másik [Y] utasítás által kitöltött rekesz; ilyenkor a láncot a végéig követjük. A végén
a tár 1-től kezdődő, írt részét egy sorba kiírjuk. Az időigény a program hosszával (legfeljebb 200 000 rekesz) arányos.
*/
/*
Hint 1: || Egy címke hivatkozhat olyan rekeszre is, amit később írsz, ezért előbb érdemes kiszámolni, hogy minden utasítás hány rekeszt foglal, és így megkapni a címkék címeit. ||
Hint 2: || Az utasítás típusa az első nem szóköz karakterből dönthető el: szám, aposztróf, idézőjel, '<' vagy '['. A címke csak betűkből áll, és kettőspont követi; a sor elején lehet, de elmaradhat. ||
Hint 3: || A tárat egy tömbként tárold, a következő szabad rekesz sorszámát pedig egy számláló adja. A [X] utasításnál ne a pillanatnyi értéket másold, hanem az X rekesz végső értékét: a rekeszt jelöld meg hivatkozásként, és a tár teljes feltöltése után oldd fel. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Instr {
    char type = 0; // 'n' szám, 'c' karakter, 's' karakterlánc, 'a' cím, 'v' tárérték
    int num = 0;   // szám vagy karakterkód
    int db = 0;    // ismétlésszám
    string s;      // karakterlánc, vagy a hivatkozott címke neve
};

struct Item {
    bool hasLabel = false;
    string label;
    bool hasIns = false;
    Instr ins;
};

static bool isLetterCh(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

static bool isDigitCh(char ch) {
    return ch >= '0' && ch <= '9';
}

static Item parseLine(const string &line) {
    Item it;
    size_t i = 0, n = line.size();
    auto skip = [&]() {
        while (i < n && (line[i] == ' ' || line[i] == '\t'))
            ++i;
    };
    auto readLetters = [&]() {
        string r;
        while (i < n && isLetterCh(line[i]))
            r.push_back(line[i++]);
        return r;
    };
    auto readNumber = [&]() {
        int v = 0;
        while (i < n && isDigitCh(line[i]))
            v = v * 10 + (line[i++] - '0');
        return v;
    };

    skip();
    if (i < n && isLetterCh(line[i])) {
        it.hasLabel = true;
        it.label = readLetters();
        skip();
        if (i < n && line[i] == ':')
            ++i;
        skip();
    }
    if (i >= n)
        return it;

    it.hasIns = true;
    char c = line[i];
    if (isDigitCh(c)) {
        it.ins.type = 'n';
        it.ins.num = readNumber();
        skip();
        ++i; // '('
        skip();
        it.ins.db = readNumber();
        skip();
        ++i; // ')'
    } else if (c == '\'') {
        it.ins.type = 'c';
        it.ins.num = (unsigned char)line[i + 1];
        i += 3; // 'x'
        skip();
        ++i; // '('
        skip();
        it.ins.db = readNumber();
        skip();
        ++i; // ')'
    } else if (c == '"') {
        it.ins.type = 's';
        size_t j = line.find('"', i + 1);
        if (j == string::npos)
            j = n;
        it.ins.s = line.substr(i + 1, j - i - 1);
        i = j + 1;
    } else if (c == '<') {
        it.ins.type = 'a';
        ++i;
        skip();
        it.ins.s = readLetters();
        skip();
        ++i; // '>'
    } else if (c == '[') {
        it.ins.type = 'v';
        ++i;
        skip();
        it.ins.s = readLetters();
        skip();
        ++i; // ']'
    } else {
        it.hasIns = false;
    }
    return it;
}

static long long insLen(const Instr &in) {
    switch (in.type) {
    case 'n':
    case 'c':
        return in.db;
    case 's':
        return (long long)in.s.size();
    case 'a':
        return 2;
    case 'v':
        return 1;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Item> prog;
    string line;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        Item it = parseLine(line);
        if (it.hasLabel || it.hasIns)
            prog.push_back(it);
    }

    // 1. menet: címkék címei (a rekesz sorszáma az utasítás előtt)
    unordered_map<string, long long> addr;
    long long pos = 0;
    for (const Item &it : prog) {
        if (it.hasLabel)
            addr[it.label] = pos + 1;
        if (it.hasIns)
            pos += insLen(it.ins);
    }

    // 2. menet: a tár feltöltése; a [X] rekeszek forrása később, a teljes tár ismeretében oldódik fel
    const long long L = pos;
    vector<int> val(L + 2, 0);
    vector<char> isRef(L + 2, 0), done(L + 2, 0);
    vector<long long> target(L + 2, 0);
    long long w = 0; // az utolsó írt rekesz sorszáma
    auto put = [&](int v) {
        ++w;
        val[w] = v & 255;
        done[w] = 1;
    };
    for (const Item &it : prog) {
        if (!it.hasIns)
            continue;
        const Instr &in = it.ins;
        if (in.type == 'n' || in.type == 'c') {
            for (int k = 0; k < in.db; ++k)
                put(in.num);
        } else if (in.type == 's') {
            for (unsigned char ch : in.s)
                put(ch);
        } else if (in.type == 'a') {
            long long a = addr.count(in.s) ? addr[in.s] : 0;
            put((int)(a & 255));
            put((int)((a >> 8) & 255));
        } else if (in.type == 'v') {
            ++w;
            isRef[w] = 1;
            target[w] = addr.count(in.s) ? addr[in.s] : 0;
        }
    }

    // A [X] rekeszek értéke a cél rekesz végső értéke; ha az is [Y], a láncot követjük a végéig.
    for (long long k = 1; k <= L; ++k) {
        if (!isRef[k] || done[k])
            continue;
        vector<long long> path;
        long long cur = k;
        while (cur >= 1 && cur <= L && isRef[cur] && !done[cur] && (long long)path.size() <= L) {
            path.push_back(cur);
            cur = target[cur];
        }
        int v = 0;
        if (cur >= 1 && cur <= L && (!isRef[cur] || done[cur]))
            v = val[cur];
        for (long long p : path) {
            val[p] = v;
            done[p] = 1;
        }
    }

    string out;
    for (long long k = 1; k <= L; ++k) {
        if (k > 1)
            out.push_back(' ');
        out += to_string(val[k]);
    }
    cout << out << '\n';
    return 0;
}
