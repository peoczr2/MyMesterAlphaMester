/*
Megoldás lényege:
A kifejezés csak összeadásból, kivonásból, zárójelekből és változókból áll, ezért minden
változó egy lineáris együtthatót kap. A maximumot úgy érjük el, hogy a pozitív együtthatójú
változókra B-t, a negatívakra A-t választunk.

*/

// Hint 1: || Itt nincs szorzás, ezért a teljes kifejezés lineáris a változókban. ||
// Hint 2: || A zárójelek és az előjelek csak azt döntik el, hogy egy változó + vagy - előjellel szerepel. ||
// Hint 3: || Elég a változóegyütthatókat összeszedni, majd abból az értéket és az optimális hozzárendelést is megkapod. ||

#include <bits/stdc++.h>
using namespace std;

string s;
int pos;
map<char, long long> coef;

void parseExpr(long long mult);

void parseTerm(long long mult) {
    long long sign = 1;
    while (pos < (int)s.size() && (s[pos] == '+' || s[pos] == '-')) {
        if (s[pos] == '-') sign = -sign;
        ++pos;
    }

    if (s[pos] == '(') {
        ++pos;
        parseExpr(mult * sign);
        ++pos;
        return;
    }

    coef[s[pos]] += mult * sign;
    ++pos;
}

void parseExpr(long long mult) {
    parseTerm(mult);
    while (pos < (int)s.size() && s[pos] != ')') {
        char op = s[pos++];
        parseTerm(op == '+' ? mult : -mult);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> s)) return 0;
    long long A, B;
    cin >> A >> B;

    pos = 0;
    coef.clear();
    parseExpr(1);

    long long ans = 0;
    for (auto [ch, c] : coef) {
        if (c > 0) ans += c * B;
        else ans += c * A;
    }

    cout << ans << '\n';
    for (auto [ch, c] : coef) {
        cout << ch << ' ' << (c >= 0 ? B : A) << '\n';
    }
    return 0;
}
