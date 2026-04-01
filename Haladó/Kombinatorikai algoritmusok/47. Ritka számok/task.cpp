/*
   Ritka számok: bináris számok, amelyekben nincs két egymás melletti 1-es.
   A számot egy fix hosszra feltöltve lexikografikusan kezeljük, így a
   következő/előző sparse szám egyszerűen módosítható.
*/
#include <bits/stdc++.h>
using namespace std;

static string trimLeadingZeros(const vector<int>& bits) {
    int i = 0;
    while (i < (int)bits.size() && bits[i] == 0) ++i;
    if (i == (int)bits.size()) return "";
    string s;
    for (; i < (int)bits.size(); ++i) s.push_back(char('0' + bits[i]));
    return s;
}

static vector<int> nextSparse(vector<int> bits) {
    int L = (int)bits.size();
    for (int i = L - 1; i >= 0; --i) {
        if (bits[i] == 0 && (i == 0 || bits[i - 1] == 0)) {
            bits[i] = 1;
            for (int j = i + 1; j < L; ++j) bits[j] = 0;
            return bits;
        }
    }
    return bits;
}

static bool prevSparse(vector<int>& bits) {
    int L = (int)bits.size();
    for (int i = L - 1; i >= 0; --i) {
        if (bits[i] == 1) {
            bits[i] = 0;
            for (int j = i + 1; j < L; ++j) bits[j] = ((j - i) % 2 == 1 ? 1 : 0);
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    string s;
    cin >> N >> s;

    vector<int> bits(N + 1, 0);
    for (int i = 0; i < N; ++i) bits[i + 1] = s[i] - '0';

    auto nxt = nextSparse(bits);
    string nextAns = trimLeadingZeros(nxt);
    if (nextAns.empty()) nextAns = "-1";

    auto prv = bits;
    bool ok = prevSparse(prv);
    string prevAns = ok ? trimLeadingZeros(prv) : "";
    if (prevAns.empty()) prevAns = "-1";

    cout << nextAns << '\n' << prevAns << '\n';
    return 0;
}