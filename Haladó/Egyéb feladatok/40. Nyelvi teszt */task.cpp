/*
Megoldás lényege:
A megoldási kulcsot egy egyszerű elemzővel fa-szerkezetre bontjuk: karakterekből, szóközökből és zárójeles csoportokból áll, a csoportok ágakra, az ágak pedig további elemekre bomlanak. Az illeszkedést pozíciók halmazával követjük: minden elemnél azt tároljuk, hová juthat a megoldás (hány karaktert fogyasztott), és hogy az utolsó fogyasztott karakter szóköz volt-e. Csoportnál minden ágra külön lefuttatjuk az illeszkedést, az eredményeket uniózzuk, és az üres ág nem fogyaszt karaktert. A szóközöket úgy kezeljük, hogy a megoldásban a szavak közti szóközök száma nem számít, így az üres ág miatt egymás után kerülő szóközök egynek számítanak. Egy megoldás ellenőrzése a kulcs hosszával és a megoldás hosszával arányos.
*/
/*
Hint 1: || A kulcs zárójeles részei egymásba ágyazhatók, ezért rekurzív feldolgozással a legegyszerűbb: egy sorozat elemeit sorban olvasd, és csoportnál külön kezeld az ágakat. ||
Hint 2: || Az illeszkedés során ne egyetlen pozíciót, hanem az összes lehetséges pozíciót tartsd nyilván. Ezért egy csoport minden ágát ugyanabból a halmazból indítsd, és az eredményeket egyesítsd. ||
Hint 3: || Az üres ág nem fogyaszt karaktert, a szóközöket pedig úgy kezeld, hogy két egymás utáni kulcs-szóköz közül egy is elég legyen a megoldás egyetlen szóköze mellé. Ezt egy kiegészítő jelzővel követheted nyilván. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int type;                   // 0: karakter, 1: szóköz, 2: csoport
    char c;
    vector<vector<Node>> alts;  // csoport ágai
};

// Kulcs-sorozatot olvas az i-edik pozíciótól; ')' vagy '|' előtt, illetve a sor végén áll meg.
static void parseSeq(const string& s, size_t& i, vector<Node>& out) {
    while (i < s.size() && s[i] != '|' && s[i] != ')') {
        if (s[i] == '(') {
            ++i;
            Node g;
            g.type = 2;
            g.c = 0;
            while (true) {
                vector<Node> alt;
                parseSeq(s, i, alt);
                g.alts.push_back(move(alt));
                if (i < s.size() && s[i] == '|') {
                    ++i;
                    continue;
                }
                break;
            }
            if (i < s.size() && s[i] == ')') ++i;
            out.push_back(move(g));
        } else if (s[i] == ' ') {
            out.push_back(Node{1, ' ', {}});
            ++i;
        } else {
            out.push_back(Node{0, s[i], {}});
            ++i;
        }
    }
}

// Állapot: index = 2*p + f, ahol p a megoldás aktuális pozíciója, f = 1, ha az utolsó fogyasztott karakter szóköz volt.
using States = vector<char>;

static States matchSeq(const vector<Node>& seq, const States& st, const string& t) {
    const size_t L = t.size();
    States cur = st;
    for (const Node& nd : seq) {
        States nxt(2 * (L + 1), 0);
        if (nd.type == 0) {
            for (size_t p = 0; p < L; ++p)
                for (int f = 0; f < 2; ++f)
                    if (cur[2 * p + f] && t[p] == nd.c) nxt[2 * (p + 1)] = 1;
        } else if (nd.type == 1) {
            for (size_t p = 0; p <= L; ++p)
                for (int f = 0; f < 2; ++f) {
                    if (!cur[2 * p + f]) continue;
                    if (p < L && t[p] == ' ') nxt[2 * (p + 1) + 1] = 1;
                    if (f == 1 || p == L) nxt[2 * p + 1] = 1;
                }
        } else {
            for (const auto& alt : nd.alts) {
                States r = matchSeq(alt, cur, t);
                for (size_t k = 0; k < nxt.size(); ++k) nxt[k] |= r[k];
            }
        }
        cur = move(nxt);
    }
    return cur;
}

// A szavakat egyetlen szóközzel választja el, a kezdő és záró szóközöket elhagyja.
static string canonical(const string& s) {
    string out, word;
    istringstream iss(s);
    while (iss >> word) {
        if (!out.empty()) out += ' ';
        out += word;
    }
    return out;
}

static void stripCR(string& s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == '\n')) s.pop_back();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string key, line;
    getline(cin, key);
    stripCR(key);

    getline(cin, line);
    stripCR(line);
    int n = stoi(line);

    vector<Node> top;
    size_t pos = 0;
    parseSeq(key, pos, top);

    for (int k = 0; k < n; ++k) {
        getline(cin, line);
        stripCR(line);
        string t = canonical(line);
        const size_t L = t.size();

        States st(2 * (L + 1), 0);
        st[1] = 1;  // p = 0, f = 1: a kezdő kulcs-szóköz elnyelhető
        States fin = matchSeq(top, st, t);
        bool ok = fin[2 * L] || fin[2 * L + 1];
        cout << (ok ? "IGEN" : "NEM") << '\n';
    }
    return 0;
}
