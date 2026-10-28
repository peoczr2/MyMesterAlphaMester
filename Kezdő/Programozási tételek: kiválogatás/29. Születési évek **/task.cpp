/*
Megoldás lényege:
A kérdés csak az évekről szól, ezért a hónap és a nap a döntéshez nem kell, csak az évszámot olvassuk ki.
Az elmúlt 100 év a mai évtől visszafelé a mai évet is beleszámítva a Y-99 és Y közötti évek.
Egyetlen bejárással minden születési évet megvizsgálunk: ha a tartományba esik, egy halmazba (set) tesszük.
A set rendezve tárolja az elemeket és az ismétléseket kiszűri, így a kiíráskor az évek már növekvő sorrendben vannak.
Először a darabszám következik, utána az évek, egy-egy szóközzel elválasztva.
Az időigény N-nel arányos, és N legfeljebb 1000, így ez bőven belefér.
*/
/*
Hint 1: || A feladat csak évekre kérdez rá, ezért a születési hónap és nap a megoldáshoz nem kell. A mai dátumból is csak az évet használd. ||
Hint 2: || Az azonos évben született emberekből csak egy év kerüljön a kimenetbe. Ehhez egy set<int>-et használhatsz, amely rendezetten tárolja és kiszűri az ismétléseket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> years(n);
    for (int i = 0; i < n; ++i) {
        int month, day;
        cin >> years[i] >> month >> day;
    }

    int today_year, today_month, today_day;
    cin >> today_year >> today_month >> today_day;

    set<int> found;
    for (int y : years) {
        if (y > today_year - 100 && y <= today_year) found.insert(y);
    }

    cout << found.size();
    for (int y : found) cout << ' ' << y;
    cout << '\n';
    return 0;
}
