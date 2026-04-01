/*
Megoldas lenyege:
A kimenetnek mindig 1,2,...,M sorrendben kell elkészülnie, ezért minden pillanatban
csak a következő még hiányzó számot várjuk. A verem tetején lévő elemet amint az
éppen szükséges következő szám, azonnal ki is vesszük. Az aktuális bemeneti számot
akkor tehetjük a verembe, ha azzal továbbra is csökkenő marad a verem tetejétől
lefelé a sorrend; különben már nem tudunk további folyamatos prefixet előállítani.
*/
/*
Hint 1: || Mindig a következő hiányzó számra figyelj, nem az egész permutációra. ||
Hint 2: || A veremből azonnal vedd ki a tetejét, ha pont az kell következőnek. ||
Hint 3: || Új számot csak akkor tehetsz a verembe, ha nem rontja el a csökkenő veremsorrendet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];

    vector<int> st;
    int need = 1;
    for (int x : p) {
        while (!st.empty() && st.back() == need) {
            st.pop_back();
            ++need;
        }
        if (x == need) {
            ++need;
            continue;
        }
        st.push_back(x);
    }

    while (!st.empty() && st.back() == need) {
        st.pop_back();
        ++need;
    }

    cout << need - 1 << '\n';
    return 0;
}
