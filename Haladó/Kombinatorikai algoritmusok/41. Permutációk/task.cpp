/*
Megoldás lényege:
A 3-1-2 minta-mentes permutációk pontosan azok, amelyek az 1, 2, …, N sorozat verembe tolásával és onnan kivételével előállíthatók, ezért minden ilyen permutációhoz egyértelmű Dyck-szó tartozik (betolás = U, kivétel = D). A lexikografikus sorrend a Dyck-szavak sorrendjének felel meg, ahol a D kisebb az U-nál. Így a rákövetkező Dyck-szó úgy kapható, hogy megkeressük a legutolsó olyan D betűt, amelynek jobb oldalán van U, azt U-ra cseréljük, a maradék részt pedig a lehető legkisebb módon (előbb D-vel) töltjük ki.
A kapott Dyck-szót a verem-szimulációval visszaalakítjuk permutációvá. Minden lépés O(N), ami N ≤ 10 000 mellett gyors.
*/
/*
Hint 1: || Képzeld el a permutációt verem-műveletek sorozataként: a számokat 1-től sorban betolod a verembe, és amikor a kívánt szám következik, kiveszed. Így minden 3-1-2 minta-mentes permutációhoz egy zárójelezés (Dyck-szó) tartozik. ||
Hint 2: || A lexikografikus sorrend a Dyck-szavak olyan sorrendje, ahol a kivétel (D) kisebb a betolásnál (U). Keresd meg a Dyck-szó legutolsó D betűjét, amelynek jobb oldalán van U; ezt U-ra cserélve, és a végét a lehető legkisebb módon kitöltve kapod a következőt. ||
Hint 3: || A kapott Dyck-szót a verem-szimulációval visszaalakítod permutációvá: U esetén új számot tolsz be, D esetén kiveszed a verem tetejét. Ez egy végigmenéssel O(N) időben megoldható. ||
*/
#include <bits/stdc++.h>
using namespace std;

static string permToDyck(const vector<int>& p) {
    int n = (int)p.size();
    int nextVal = 1;
    vector<int> st;
    string w;
    w.reserve(2 * n);
    for (int x : p) {
        while (nextVal <= x) {
            st.push_back(nextVal++);
            w.push_back('U');
        }
        st.pop_back();
        w.push_back('D');
    }
    return w;
}

static vector<int> dyckToPerm(const string& w) {
    int n = (int)w.size() / 2;
    vector<int> st, p;
    p.reserve(n);
    int nextVal = 1;
    for (char c : w) {
        if (c == 'U') {
            st.push_back(nextVal++);
        } else {
            p.push_back(st.back());
            st.pop_back();
        }
    }
    return p;
}

static string nextDyck(string w) {
    int n = (int)w.size() / 2;
    int openRight = 0;
    vector<int> prefBal(w.size() + 1, 0);
    for (int i = 0; i < (int)w.size(); ++i) {
        prefBal[i + 1] = prefBal[i] + (w[i] == 'U' ? 1 : -1);
    }
    for (int i = (int)w.size() - 1; i >= 0; --i) {
        if (w[i] == 'U') ++openRight;
        else if (openRight > 0) {
            string ans = w.substr(0, i);
            ans.push_back('U');
            int remU = n - (prefBal[i] + 1 + (int)(ans.size() - i - 1 + 0));
            // remU/remD are easier computed from the counts in the suffix.
            int usedU = prefBal[i] + 1 + (int)count(ans.begin(), ans.end(), 'D');
            (void)usedU;
            int prefixU = 0;
            for (int j = 0; j < i; ++j) if (w[j] == 'U') ++prefixU;
            int prefixD = i - prefixU;
            remU = n - prefixU - 1;
            int remD = n - prefixD;
            int bal = prefBal[i] + 1;
            while ((int)ans.size() < 2 * n) {
                if (remD > 0 && bal > 0) {
                    ans.push_back('D');
                    --remD;
                    --bal;
                } else {
                    ans.push_back('U');
                    --remU;
                    ++bal;
                }
            }
            return ans;
        }
    }
    return w;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> p(N);
    for (int i = 0; i < N; ++i) cin >> p[i];

    string w = permToDyck(p);
    string nxt = nextDyck(w);
    vector<int> ans = dyckToPerm(nxt);
    for (int i = 0; i < N; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
