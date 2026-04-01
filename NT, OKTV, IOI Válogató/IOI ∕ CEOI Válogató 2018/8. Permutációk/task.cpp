/*
Megoldás lényege:
A 3-1-2 minta-mentes permutációk pontosan a stack-sortolható permutációk egy
szimmetrikus osztálya; ehhez egyértelműen hozzárendelhető egy Dyck-szó.
Az input permutációból a szokásos push/pop szimulációval kapjuk meg a Dyck-szót:
1,2,3,...,N elemeket tolunk a verembe, és amikor a következő kimenő elem a verem
tetője, kipop-pintjuk.

Ezen a Dyck-szón a lexikografikus sorrend (ahol a zárójel kisebb, mint a nyitójel)
megegyezik a permutáció lexikografikus sorrendjével. Ezért elég a következő Dyck-
szót kiszámítani: a jobb széltől visszafelé megkeressük a jobb oldalon még bővíthető
legutolsó zárójelet, azt nyitóra cseréljük, majd a maradékot a lehető legkisebb
érvényes Dyck-lexikográfiával töltjük fel. A kapott Dyck-szóból ismét stack-
szimulációval visszaáll a permutáció.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];

    vector<char> dyck;
    dyck.reserve(2 * n);
    vector<int> st;
    st.reserve(n);

    int nextVal = 1;
    for (int x : p) {
        while (nextVal <= x) {
            st.push_back(nextVal++);
            dyck.push_back('U');
        }
        st.pop_back();
        dyck.push_back('D');
    }

    int totalU = n, totalD = n;
    vector<int> prefU(2 * n + 1, 0), prefD(2 * n + 1, 0);
    for (int i = 0; i < 2 * n; ++i) {
        prefU[i + 1] = prefU[i] + (dyck[i] == 'U');
        prefD[i + 1] = prefD[i] + (dyck[i] == 'D');
    }

    int pos = -1;
    int uRight = 0;
    for (int i = 2 * n - 1; i >= 0; --i) {
        if (dyck[i] == 'U') ++uRight;
        else if (uRight > 0) {
            pos = i;
            break;
        }
    }

    vector<char> nextDyck;
    nextDyck.reserve(2 * n);
    for (int i = 0; i < pos; ++i) nextDyck.push_back(dyck[i]);
    nextDyck.push_back('U');

    int usedU = prefU[pos] + 1;
    int usedD = prefD[pos];
    int remU = totalU - usedU;
    int remD = totalD - usedD;
    int balance = usedU - usedD;

    while (remU + remD > 0) {
        if (remD > 0 && balance > 0) {
            nextDyck.push_back('D');
            --remD;
            --balance;
        } else {
            nextDyck.push_back('U');
            --remU;
            ++balance;
        }
    }

    vector<int> out;
    out.reserve(n);
    st.clear();
    nextVal = 1;
    for (char c : nextDyck) {
        if (c == 'U') {
            st.push_back(nextVal++);
        } else {
            out.push_back(st.back());
            st.pop_back();
        }
    }

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << out[i];
    }
    cout << '\n';
    return 0;
}