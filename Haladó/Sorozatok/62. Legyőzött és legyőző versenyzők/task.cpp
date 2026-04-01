/*
Megoldas lenyege:
Az elso N sorban a bal oldali legkozelebbi kisebb es bal oldali legkozelebbi nagyobb elemet kell
megadni, a kovetkezo N sorban pedig a jobb oldali legkozelebbi kisebb es jobb oldali legkozelebbi
nagyobb elemet.

Ez negy klasszikus monotonvermes lekerdezes: elozo kisebb, elozo nagyobb, kovetkezo kisebb,
kovetkezo nagyobb. Mindegyik egyetlen linearis bejarassal kiszamithato.
*/
/*
Hint 1: || Az elozo es kovetkezo legkozelebbi elemeket kulon erdemes kiszamolni. ||
Hint 2: || A kisebb elemekhez novekvo, a nagyobb elemekhez csokkeno monotón verem kell. ||
Hint 3: || Az elso N sor a bal oldalrol, a masodik N sor a jobb oldalrol szol. ||
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

    vector<int> prevSmaller(n + 1, -1), prevGreater(n + 1, -1);
    vector<int> nextSmaller(n + 1, -1), nextGreater(n + 1, -1);
    vector<int> st;

    for (int i = 1; i <= n; ++i) {
        while (!st.empty() && p[st.back()] >= p[i]) st.pop_back();
        if (!st.empty()) prevSmaller[i] = st.back();
        st.push_back(i);
    }

    st.clear();
    for (int i = 1; i <= n; ++i) {
        while (!st.empty() && p[st.back()] <= p[i]) st.pop_back();
        if (!st.empty()) prevGreater[i] = st.back();
        st.push_back(i);
    }

    st.clear();
    for (int i = n; i >= 1; --i) {
        while (!st.empty() && p[st.back()] >= p[i]) st.pop_back();
        if (!st.empty()) nextSmaller[i] = st.back();
        st.push_back(i);
    }

    st.clear();
    for (int i = n; i >= 1; --i) {
        while (!st.empty() && p[st.back()] <= p[i]) st.pop_back();
        if (!st.empty()) nextGreater[i] = st.back();
        st.push_back(i);
    }

    for (int i = 1; i <= n; ++i) {
        cout << prevSmaller[i] << ' ' << prevGreater[i] << '\n';
    }
    for (int i = 1; i <= n; ++i) {
        cout << nextSmaller[i] << ' ' << nextGreater[i] << '\n';
    }
    return 0;
}