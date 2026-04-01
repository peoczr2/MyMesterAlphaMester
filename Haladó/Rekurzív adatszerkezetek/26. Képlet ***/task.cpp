/*
Megoldasi otlet:
A kifejezes teljesen zarojelezett, ezert rekurziv szerkezetu binaris fa. Minden
reszkifejezesre kiszamoljuk a normalis erteket, valamint azt is, hogy mennyi a
legnagyobb ertek, ha abban a reszben pontosan egy muveleti jelet atalakitunk.

Egy belso csomopontnal harom lehetoseg van: a mostani muveletet flippeled, a bal
oldalon flippelsz, vagy a jobb oldalon flippelsz. Ezek kozul a legnagyobb adja a
reszkifejezes optimalis erteket.

Hint 1: || A fa levelei szamjegyek, a belso csomopontok pedig + vagy - muveletek. ||
Hint 2: || Egy reszkifejezes valos erteke es az egyetlen flip utani legjobb erteke eleg minden tovabbi lepeshez. ||
Hint 3: || Minden csomopontnal csak a jelenlegi muvelet, a bal gyerek es a jobb gyerek flipjeit kell osszevetni. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct NodeValue {
    long long value;
    long long best;
};

static const long long NEG_INF = -(1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    string expr;
    cin >> N >> expr;

    vector<NodeValue> values;
    vector<char> ops;

    auto apply = [&]() {
        NodeValue right = values.back();
        values.pop_back();
        char op = ops.back();
        ops.pop_back();
        NodeValue left = values.back();
        values.pop_back();

        NodeValue cur;
        if (op == '+') {
            cur.value = left.value + right.value;
            cur.best = max({left.best == NEG_INF ? NEG_INF : left.best + right.value,
                            right.best == NEG_INF ? NEG_INF : left.value + right.best,
                            left.value - right.value});
        } else {
            cur.value = left.value - right.value;
            cur.best = max({left.best == NEG_INF ? NEG_INF : left.best - right.value,
                            right.best == NEG_INF ? NEG_INF : left.value - right.best,
                            left.value + right.value});
        }
        values.push_back(cur);
    };

    for (char c : expr) {
        if (isdigit(static_cast<unsigned char>(c))) {
            long long x = c - '0';
            values.push_back({x, NEG_INF});
        } else if (c == '+' || c == '-') {
            ops.push_back(c);
        } else if (c == ')') {
            apply();
        }
    }

    cout << values.back().best << '\n';
    return 0;
}