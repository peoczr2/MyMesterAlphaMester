/*
Megoldás lényege:
A DNS-szekvenciát implicit treap tárolja: a sorrend a részfa-méretekből adódik, minden csúcsban a részfa A, C, G, T betűnkénti darabszáma is el van tárolva.
Minden művelet a [i, j] szakaszt split-tel leválasztja, a középső részen végzi el a változtatást vagy a számlálást, majd merge-gel visszafűzi, így mindegyik O(log n) várható időben fut.
A Szamlal a középső részfa betűszámlálójából azonnal adódik, az Eredmeny pedig egyszer bejárja a fát (legfeljebb 100 hívás).
A főprogram (main) csak helyi próbafuttatásra szolgál: a minta grader protokollját végrehajtja, az eredményeket és az eltéréseket a hibacsatornára (cerr) írja.
*/
/*
Hint 1: || Egy tömbön a beszúrás és a törlés O(n), ami 100 000 művelet mellett túl lassú. Olyan fát használj, amelynek csúcsai a részfa méretét és a betűnkénti darabszámot tárolják. ||
Hint 2: || Minden művelet a [i, j] szakaszra vonatkozik: két split után a középső részfán végezd el a változtatást vagy a számlálást, majd merge-gel fűzd vissza. A Szamlal válaszát a középső részfa számlálójából kapod. ||
Hint 3: || A treap véletlen prioritása tartja a fa magasságát logaritmikus közelben, így a rekurzív split és merge is gyors. A Kezd() kezdő szövegét egy-egy csúcs merge-elésével építsd fel. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Implicit treap: a sorrend a részfa-méretekből adódik. Minden csúcsban a részfa
// betűnkénti darabszáma van (A, C, G, T = 0..3).
struct Node {
    int l = 0, r = 0;       // gyerekek indexe (0 = nincs)
    unsigned pri = 0;       // véletlen prioritás
    int sz = 0;             // részfa mérete
    int cnt[4] = {0, 0, 0, 0};
    int ch = 0;             // a csúcs betűje
};

vector<Node> t(1);          // t[0] az üres csúcs
int root = 0;
mt19937 rng(20210101);
const char LETTERS[4] = {'A', 'C', 'G', 'T'};

int letterIdx(char c) {
    switch (c) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        default: return 3;
    }
}

int newNode(char c) {
    t.push_back(Node());
    int id = (int)t.size() - 1;
    t[id].pri = rng();
    t[id].ch = letterIdx(c);
    t[id].sz = 1;
    t[id].cnt[t[id].ch] = 1;
    return id;
}

void upd(int v) {
    Node& x = t[v];
    x.sz = 1 + t[x.l].sz + t[x.r].sz;
    for (int k = 0; k < 4; k++) x.cnt[k] = t[x.l].cnt[k] + t[x.r].cnt[k] + (k == x.ch ? 1 : 0);
}

// Az első k csúcsot a és a többit b kapja.
void split(int v, int k, int& a, int& b) {
    if (!v) {
        a = b = 0;
        return;
    }
    if (t[t[v].l].sz >= k) {
        split(t[v].l, k, a, t[v].l);
        upd(v);
        b = v;
    } else {
        split(t[v].r, k - t[t[v].l].sz - 1, t[v].r, b);
        upd(v);
        a = v;
    }
}

int merge(int a, int b) {
    if (!a) return b;
    if (!b) return a;
    if (t[a].pri > t[b].pri) {
        t[a].r = merge(t[a].r, b);
        upd(a);
        return a;
    }
    t[b].l = merge(a, t[b].l);
    upd(b);
    return b;
}

void Kezd(const string& s) {
    root = 0;
    for (char c : s) root = merge(root, newNode(c));
}

// Az x karaktert az i. pozíció után szúrja be (0 <= i <= n).
void Beszur(int i, char x) {
    int a, b;
    split(root, i, a, b);
    root = merge(merge(a, newNode(x)), b);
}

// Az i. (1-indexelt) pozíció karakterét x-re cseréli.
void Mutal(int i, char x) {
    int a, b, m, c;
    split(root, i - 1, a, b);
    split(b, 1, m, c);
    t[m].ch = letterIdx(x);
    upd(m);
    root = merge(merge(a, m), c);
}

// Az i..j (1-indexelt, inkluzív) pozíciókat törli.
void Kivag(int i, int j) {
    int a, b, m, c;
    split(root, i - 1, a, b);
    split(b, j - i + 1, m, c);
    root = merge(a, c);
}

// Az i..j részsorozatban az x betűk számát adja.
int Szamlal(int i, int j, char x) {
    int a, b, m, c;
    split(root, i - 1, a, b);
    split(b, j - i + 1, m, c);
    int res = t[m].cnt[letterIdx(x)];
    root = merge(merge(a, m), c);
    return res;
}

void inorder(int v, string& out) {
    if (!v) return;
    inorder(t[v].l, out);
    out.push_back(LETTERS[t[v].ch]);
    inorder(t[v].r, out);
}

// Az aktuális DNS-szekvencia.
string Eredmeny() {
    string out;
    out.reserve(t[root].sz);
    inorder(root, out);
    return out;
}

// Helyi próbafuttatás: a minta grader protokollját hajtja végre.
// Sor: művelet-szám és paraméterek; 0 a befejezés. A 4-es és 5-ös műveletek
// eredményét és a fájlban lévő ellenőrző értéket a hibacsatornára írja.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    t.reserve(200005);

    string s;
    cin >> s;
    Kezd(s);

    int op;
    while (cin >> op && op != 0) {
        if (op == 1) {
            int i;
            char x;
            cin >> i >> x;
            Beszur(i, x);
        } else if (op == 2) {
            int i;
            char x;
            cin >> i >> x;
            Mutal(i, x);
        } else if (op == 3) {
            int i, j;
            cin >> i >> j;
            Kivag(i, j);
        } else if (op == 4) {
            int i, j;
            char x;
            cin >> i >> j >> x;
            string expected;
            cin >> expected;
            int got = Szamlal(i, j, x);
            cerr << "Szamlal " << i << ' ' << j << ' ' << x << " = " << got;
            if (expected != to_string(got)) cerr << "  (a fajlban: " << expected << ")";
            cerr << '\n';
        } else if (op == 5) {
            string expected;
            cin >> expected;
            string res = Eredmeny();
            cerr << "Eredmeny = " << res;
            if (expected != res + "#") cerr << "  (a fajlban: " << expected << ")";
            cerr << '\n';
        }
    }
    return 0;
}
