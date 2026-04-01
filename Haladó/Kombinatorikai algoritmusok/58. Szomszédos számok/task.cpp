/*
   Szomszédos számok: az érdekes számok M+1 alapú számrendszerben, pontosan M
   összeggel. Az elemeket először hossz szerint, majd lexikografikusan rendezzük.
*/
#include <bits/stdc++.h>
using namespace std;

static vector<int> parse(const string& s) {
    vector<int> a;
    for (char c : s) a.push_back(c - '0');
    return a;
}

static string join(const vector<int>& a) {
    if (a.empty()) return "-1";
    string s;
    for (int x : a) s.push_back(char('0' + x));
    return s;
}

static vector<int> smallestFixedLen(int len, int sum, int M, bool firstPositive) {
    vector<int> a;
    int rem = sum;
    for (int i = 0; i < len; ++i) {
        int left = len - 1 - i;
        int low = max(0, rem - left * M);
        if (i == 0 && firstPositive) low = max(low, 1);
        int d = low;
        a.push_back(d);
        rem -= d;
    }
    if (rem != 0) return {};
    return a;
}

static vector<int> largestFixedLen(int len, int sum, int M, bool firstPositive) {
    vector<int> a;
    int rem = sum;
    for (int i = 0; i < len; ++i) {
        int left = len - 1 - i;
        int high = min(M, rem);
        if (i == 0 && firstPositive) high = max(1, high);
        int d = high;
        while (d >= 0 && rem - d > left * M) --d;
        if (i == 0 && firstPositive && d == 0) return {};
        a.push_back(d);
        rem -= d;
    }
    if (rem != 0) return {};
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    string s;
    cin >> s;
    vector<int> a = parse(s);
    int L = (int)a.size();

    auto nextSameLen = [&](const vector<int>& cur) -> vector<int> {
        int pref = 0;
        for (int i = 0; i < L; ++i) pref += cur[i];
        for (int i = L - 1; i >= 0; --i) {
            pref -= cur[i];
            int remPos = L - 1 - i;
            int minD = max(cur[i] + 1, M - pref - remPos * M);
            for (int d = minD; d <= M; ++d) {
                int rem = M - pref - d;
                if (rem < 0 || rem > remPos * M) continue;
                vector<int> ans(cur.begin(), cur.begin() + i);
                ans.push_back(d);
                auto tail = smallestFixedLen(remPos, rem, M, false);
                if ((int)tail.size() != remPos) continue;
                ans.insert(ans.end(), tail.begin(), tail.end());
                return ans;
            }
        }
        return {};
    };

    auto prevSameLen = [&](const vector<int>& cur) -> vector<int> {
        int pref = 0;
        for (int i = 0; i < L; ++i) pref += cur[i];
        for (int i = L - 1; i >= 0; --i) {
            pref -= cur[i];
            int remPos = L - 1 - i;
            for (int d = cur[i] - 1; d >= 0; --d) {
                if (i == 0 && d == 0) continue;
                int rem = M - pref - d;
                if (rem < 0 || rem > remPos * M) continue;
                vector<int> ans(cur.begin(), cur.begin() + i);
                ans.push_back(d);
                auto tail = largestFixedLen(remPos, rem, M, false);
                if ((int)tail.size() != remPos) continue;
                ans.insert(ans.end(), tail.begin(), tail.end());
                return ans;
            }
        }
        return {};
    };

    vector<int> nxt = nextSameLen(a);
    vector<int> prv = prevSameLen(a);

    if (prv.empty()) {
        if (L == 1) cout << -1 << '\n';
        else {
            auto prevLen = largestFixedLen(L - 1, M, M, true);
            cout << join(prevLen) << '\n';
        }
    } else {
        cout << join(prv) << '\n';
    }

    if (nxt.empty()) {
        if (L == N) cout << -1 << '\n';
        else {
            auto nextLen = smallestFixedLen(L + 1, M, M, true);
            cout << join(nextLen) << '\n';
        }
    } else {
        cout << join(nxt) << '\n';
    }
    return 0;
}