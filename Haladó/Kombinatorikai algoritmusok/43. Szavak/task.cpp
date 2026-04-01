/*
   Szavak: az összes nem üres, a megadott betűmultihalmazon belül képezhető
   szó lexikografikus előzője és követője. A sorrend a prefixfán végzett
   bejárásnak felel meg.
*/
#include <bits/stdc++.h>
using namespace std;

static string nextWord(const string& s, const vector<int>& total) {
    vector<int> used(26, 0);
    for (char c : s) used[c - 'a']++;

    for (int c = 0; c < 26; ++c) {
        if (used[c] < total[c]) return s + char('a' + c);
    }

    for (int i = (int)s.size() - 1; i >= 0; --i) {
        used[s[i] - 'a']--;
        int cur = s[i] - 'a';
        for (int c = cur + 1; c < 26; ++c) {
            if (used[c] < total[c]) return s.substr(0, i) + char('a' + c);
        }
    }

    for (int c = 0; c < 26; ++c) {
        if (total[c] > 0) return string(1, char('a' + c));
    }
    return "";
}

static string maxWord(const vector<int>& total) {
    vector<int> rem = total;
    string ans;
    while (true) {
        int c = -1;
        for (int i = 25; i >= 0; --i) if (rem[i] > 0) { c = i; break; }
        if (c < 0) break;
        ans.push_back(char('a' + c));
        --rem[c];
    }
    return ans;
}

static string prevWord(const string& s, const vector<int>& total) {
    vector<int> used(26, 0);
    for (char c : s) used[c - 'a']++;

    for (int i = (int)s.size() - 1; i >= 0; --i) {
        used[s[i] - 'a']--;
        int cur = s[i] - 'a';
        for (int c = cur - 1; c >= 0; --c) {
            if (used[c] < total[c]) {
                string ans = s.substr(0, i) + char('a' + c);
                vector<int> rem = total;
                for (int j = 0; j < 26; ++j) rem[j] -= used[j];
                --rem[c];
                while (true) {
                    int d = -1;
                    for (int x = 25; x >= 0; --x) if (rem[x] > 0) { d = x; break; }
                    if (d < 0) break;
                    ans.push_back(char('a' + d));
                    --rem[d];
                }
                return ans;
            }
        }
    }
    return maxWord(total);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    string letters, s;
    cin >> letters >> s;

    vector<int> total(26, 0);
    for (char c : letters) total[c - 'a']++;

    cout << prevWord(s, total) << '\n' << nextWord(s, total) << '\n';
    return 0;
}