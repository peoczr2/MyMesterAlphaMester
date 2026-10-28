/*
Megoldás lényege:
A fő vágányon átmenő kocsi azonnal kimegy, a kitérő kocsijai pedig FIFO-sorként,
tetszőleges időpontban engedhetők ki. A kimenetnek növekvőnek kell lennie, ezért
a fő vágányra csak az a kocsi kerülhet, amelynél a később érkezők között nincs
nála kisebb (jobbról balra minimum). A többi kocsi a kitérőre kerül, és a kitérőre
került kocsiknak érkezési sorrendben növekvőnek kell lenniük. A jó prefixek halmaza
lefelé zárt, így a legnagyobb jó m bináris kereséssel megtalálható. Egy m-re az
ellenőrzés egy O(m) bejárás, az összidő tehát O(K log K).
*/
/*
Hint 1: || Gondold végig, mi történik egy kocsival, ha a fő vágányon halad át: azonnal kimegy balra. Ezért ha egy kocsi a fő vágányon megy, minden nála kisebb sorszámú kocsinak már korábban meg kellett érkeznie. ||
Hint 2: || Ebből következik, hogy a fő vágányra csak az a kocsi kerülhet, amelynél a később érkező kocsik között nincs kisebb. A többi kocsi a kitérőre kerül, és mivel a kitérő FIFO sor, ezeknek érkezési sorrendben növekvőknek kell lenniük. ||
Hint 3: || Az első m kocsira tehát a jobbról balra minimumok mennek a fő vágányon, a többi kocsi érkezési sorrendjét kell ellenőrizni. Ha egy m hosszú prefix jó, akkor minden rövidebb is jó, ezért a legnagyobb jó m bináris kereséssel megtalálható; minden próbánál egy O(m) bejárás elég. ||
*/

#include <bits/stdc++.h>
using namespace std;

// Igaz, ha az első m kocsi sorba rendezhető.
bool rendezheto(const vector<int>& s, int m) {
    vector<int> kitero;
    int jobbMin = INT_MAX;
    for (int j = m - 1; j >= 0; --j) {
        if (s[j] < jobbMin) {
            jobbMin = s[j];
        } else {
            kitero.push_back(s[j]);
        }
    }
    reverse(kitero.begin(), kitero.end());
    for (size_t j = 1; j < kitero.size(); ++j) {
        if (kitero[j] < kitero[j - 1]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    vector<int> s(k);
    for (int i = 0; i < k; ++i) cin >> s[i];

    int lo = 0, hi = k;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (rendezheto(s, mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << '\n';
    return 0;
}
