/*
Megoldási ötlet:
A kifejezés teljesen zárójelezett, ezért bináris fa: a levelek számjegyek, a belső csúcsok
+ vagy - műveletek. Minden részkifejezésre három értéket tárolunk: a normál értéket, valamint
a legnagyobb és a legkisebb értéket, amit a részkifejezésben pontosan egy műveleti jel
megváltoztatásával kaphatunk. A legkisebb érték azért kell, mert egy kivonás jobb oldalán
a jobb tag fordítva hat: ott a jobb oldal legkisebb értéke adja a legnagyobb eredményt.

Egy belső csúcsnál három lehetőség van: a saját jelet változtatjuk meg, vagy a bal, vagy a jobb
részkifejezésben változtatunk egy jelet. A fát egy veremmel építjük fel balról jobbra haladva:
a ')' jelnél a verem két legfelső értékét az utolsó műveleti jellel összevonjuk.
*/
/*
Hint 1: || Minden ')' jel egy részkifejezés végét jelzi, ott mindig a verem két legfelső értékét és az utolsó műveleti jelet kell összevonni. ||
Hint 2: || Ha egy kivonás jobb oldalán levő részkifejezést változtatjuk meg, akkor annak a legkisebb értéke a kedvező, ezért a legkisebb értéket is nyilván kell tartani. ||
Hint 3: || Egy csúcs legnagyobb értéke a három lehetőség (saját jel, bal oldal, jobb oldal) legnagyobbika, a legkisebb érték a legkisebbik. Hiányzó (levél) részre a határértéket használd. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct NodeValue {
    long long value;  // a részkifejezés normál értéke
    long long mx;     // legnagyobb érték pontosan egy jel átalakításával (levélnél -INF)
    long long mn;     // legkisebb érték pontosan egy jel átalakításával (levélnél +INF)
};

static const long long INF = 1LL << 60;

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
            // a saját jel átalakítása: L - R
            cur.mx = max({left.value - right.value, left.mx + right.value, left.value + right.mx});
            cur.mn = min({left.value - right.value, left.mn + right.value, left.value + right.mn});
        } else {
            cur.value = left.value - right.value;
            // a saját jel átalakítása: L + R
            cur.mx = max({left.value + right.value, left.mx - right.value, left.value - right.mn});
            cur.mn = min({left.value + right.value, left.mn - right.value, left.value - right.mx});
        }
        values.push_back(cur);
    };

    for (char c : expr) {
        if (isdigit(static_cast<unsigned char>(c))) {
            long long x = c - '0';
            values.push_back({x, -INF, INF});
        } else if (c == '+' || c == '-') {
            ops.push_back(c);
        } else if (c == ')') {
            apply();
        }
    }

    cout << values.back().mx << '\n';
    return 0;
}
