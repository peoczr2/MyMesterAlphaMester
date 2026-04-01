/*
Hungarian megoldás: a szavakat sorban helyezzük el a táblán, és minden lépésben
csak a maximális átfedést adó elhelyezéseket engedjük tovább.

Hint 1: || Az első szó helye adott, a többi szóhoz minden lehetséges pozíciót meg kell nézni. ||
Hint 2: || Minden lépésben a most elérhető legnagyobb átfedésű helyezések közül választunk. ||
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
        return a.d < b.d;
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