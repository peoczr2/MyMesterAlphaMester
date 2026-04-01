/*
   Permutációk: a 3-1-2 minta-mentes permutációk a stack-sortolható
   permutációk. Ezekhez egy Dyck-szó felel meg, és a lexikografikus sorrend
   a Dyck-szavak sorrendjére vezethető vissza.
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