/*
   Előző és következő közeli elrendezés: a permutációk az egymást nem fedő
   szomszédos cserék sorozatai. Ez egy olyan 0/1 sorozatra felel meg, amelyben
   egymás mellett nem állhat két 1-es. A lexikografikus előző/következő ehhez
   a sorozathoz egyszerűen átalakítható.
*/
#include <bits/stdc++.h>
using namespace std;

static vector<int> buildPermutation(int n, const vector<int>& bits) {
    vector<int> ans;
    for (int i = 0; i < n - 1; ) {
        if (bits[i]) {
            ans.push_back(i + 2);
            ans.push_back(i + 1);
            i += 2;
        } else {
            ans.push_back(i + 1);
            ++i;
        }
    }
    if ((int)ans.size() < n) ans.push_back(n);
    return ans;
}

static vector<int> nextBits(vector<int> bits) {
    int L = (int)bits.size();
    for (int i = L - 1; i >= 0; --i) {
        if (bits[i] == 0 && (i == 0 || bits[i - 1] == 0)) {
            bits[i] = 1;
            for (int j = i + 1; j < L; ++j) bits[j] = 0;
            return bits;
        }
    }
    fill(bits.begin(), bits.end(), 0);
    return bits;
}

static vector<int> prevBits(vector<int> bits) {
    int L = (int)bits.size();
    for (int i = L - 1; i >= 0; --i) {
        if (bits[i] == 1) {
            bits[i] = 0;
            for (int j = i + 1; j < L; ++j) bits[j] = ((j - i) % 2 == 1 ? 1 : 0);
            return bits;
        }
    }
    for (int i = 0; i < L; ++i) bits[i] = (i % 2 == 0 ? 1 : 0);
    return bits;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];

    vector<int> bits(max(0, n - 1), 0);
    for (int i = 0; i + 1 < n; ) {
        if (p[i] == i + 1) {
            bits[i] = 0;
            ++i;
        } else {
            bits[i] = 1;
            i += 2;
        }
    }

    auto prevP = buildPermutation(n, prevBits(bits));
    auto nextP = buildPermutation(n, nextBits(bits));

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << prevP[i];
    }
    cout << '\n';
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << nextP[i];
    }
    cout << '\n';
    return 0;
}