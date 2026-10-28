/*
Megoldás lényege: a szavakat sorban rakjuk le, és minden lépésben olyan elhelyezést választunk, amelyben az új szó a legtöbb már letett betűvel fedi át a táblát.
Egy betű annyiszor számít átfedésnek, ahány szóban szerepel, mínusz egy, ezért egy új szó átfedése pontosan azt adja, hányszor esik már foglalt mezőre; így a lépésenkénti maximum a teljes átfedés növekedésének maximuma is.
Minden (sor, oszlop, irány) helyzetet végigpróbálunk, a legnagyobb átfedésűek közül rendezési sorrendben választunk, és ha egy választás zsákutcába vezet, visszalépünk.
A döntetlenek miatt több helyes megoldás is lehet, a feladat szerint bármelyik megadható.
Időigény: egy szó lerakása O(N·M·hossz) próba, így a teljes futás O(DB·N·M·hossz) nagyságrendű, ami a korlátok mellett bőven belefér.
*/
/*
Hint 1: || Az első szó helye adott; minden további szónál az összes kezdőpozíciót és irányt végig kell nézned, és csak a legnagyobb átfedésűek érdekesek. ||
Hint 2: || Tárold a táblát két mátrixban: az egyikben a mezőn lévő betűt, a másikban azt, hány szó fedi le az adott mezőt; így az átfedés és az ütközés gyorsan ellenőrizhető. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Place { int r, c; char d; int overlap; };

int n, m, w;
vector<string> words;
vector<string> board;
vector<vector<int>> cnt;
vector<Place> ans;

bool canPlace(const string &s, int r, int c, char d, int &ov) {
    int dr = d == 'V' ? 0 : 1;
    int dc = d == 'V' ? 1 : 0;
    ov = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        int nr = r + dr * i, nc = c + dc * i;
        if (nr < 0 || nr >= n || nc < 0 || nc >= m) return false;
        if (cnt[nr][nc] && board[nr][nc] != s[i]) return false;
        if (cnt[nr][nc]) ++ov;
    }
    return true;
}

void apply(const string &s, int r, int c, char d, int delta) {
    int dr = d == 'V' ? 0 : 1;
    int dc = d == 'V' ? 1 : 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        int nr = r + dr * i, nc = c + dc * i;
        if (delta > 0) {
            if (cnt[nr][nc] == 0) board[nr][nc] = s[i];
            ++cnt[nr][nc];
        } else {
            --cnt[nr][nc];
            if (cnt[nr][nc] == 0) board[nr][nc] = '.';
        }
    }
}

bool dfs(int idx) {
    if (idx == w) return true;
    vector<Place> cand;
    int best = -1;
    for (int r = 0; r < n; ++r) for (int c = 0; c < m; ++c) for (char d : {'V', 'F'}) {
        int ov;
        if (!canPlace(words[idx], r, c, d, ov)) continue;
        if (ov > best) {
            best = ov;
            cand.clear();
        }
        if (ov == best) cand.push_back({r, c, d, ov});
    }
    sort(cand.begin(), cand.end(), [](const Place &a, const Place &b) {
        if (a.overlap != b.overlap) return a.overlap > b.overlap;
        if (a.r != b.r) return a.r < b.r;
        if (a.c != b.c) return a.c < b.c;
        return a.d > b.d;
    });
    for (auto p : cand) {
        apply(words[idx], p.r, p.c, p.d, 1);
        ans.push_back(p);
        if (dfs(idx + 1)) return true;
        ans.pop_back();
        apply(words[idx], p.r, p.c, p.d, -1);
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> w >> n >> m;
    int sr, sc;
    char sd;
    cin >> sr >> sc >> sd;
    --sr; --sc;
    words.resize(w);
    for (int i = 0; i < w; ++i) cin >> words[i];
    board.assign(n, string(m, '.'));
    cnt.assign(n, vector<int>(m, 0));
    apply(words[0], sr, sc, sd, 1);
    ans.push_back({sr, sc, sd, 0});
    if (dfs(1)) {
        for (int i = 1; i < w; ++i) {
            cout << ans[i].r + 1 << ' ' << ans[i].c + 1 << ' ' << ans[i].d << '\n';
        }
    }
    return 0;
}