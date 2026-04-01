/*
Megoldas lenyege:
Az i. versenyzo altal legyozott, legkozelebb korabban indulo versenyzo pontosan a bal oldali
legkozelebbi nala kisebb pontszamu elem. Az ot legyozo, legkozelebb kesobb indulo versenyzo
pedig a jobb oldali legkozelebbi nala nagyobb pontszamu elem.

Mindketto klasszikus monoton verem: balrol jobbra egy novekvo veremmel megkapjuk az elozo
kisebb elemet, jobrol balra pedig egy csokkeno veremmel a kovetkezo nagyobbat.
*/
/*
Hint 1: || A „hozza legkozelebb indult” feltetel a legkozelebbi indexet jelenti, nem a minimum vagy maximum pontszamot. ||
Hint 2: || Az altala legyozott elozo versenyzo a bal oldali legkozelebbi kisebb elem. ||
Hint 3: || Az ot legyozo kovetkezo versenyzo a jobb oldali legkozelebbi nagyobb elem. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i) cin >> p[i];

    vector<int> prevSmaller(n + 1, -1), nextGreater(n + 1, -1);
    vector<int> st;

    for (int i = 1; i <= n; ++i) {
        while (!st.empty() && p[st.back()] >= p[i]) st.pop_back();
        if (!st.empty()) prevSmaller[i] = st.back();
        st.push_back(i);
    }

    st.clear();
    for (int i = n; i >= 1; --i) {
        while (!st.empty() && p[st.back()] <= p[i]) st.pop_back();
        if (!st.empty()) nextGreater[i] = st.back();
        st.push_back(i);
    }

    for (int i = 1; i <= n; ++i) {
        cout << prevSmaller[i] << ' ' << nextGreater[i] << '\n';
    }
    return 0;
}