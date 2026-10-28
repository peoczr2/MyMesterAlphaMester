/*
Megoldás lényege:
Egyetlen bejárással végigmegyünk a vásárlásokon, és minden tételt külön vizsgálunk, nem a cégek összesített mennyiségét.
Ha egy tétel mennyisége 500 grammnál nagyobb, a cég nevét egy vektorba tesszük, így ugyanaz a cég többször is szerepelhet.
A vektor a bemenet sorrendjében épül fel, ezért a kiírás is a bemenet sorrendjét követi.
Kiírásnál előbb a vektor mérete, utána a cégnevek következnek, szóközzel elválasztva.
Az időigény N-nel arányos, ami legfeljebb 100 lépés, így az időlimit bőven teljesül.
*/
/*
Hint 1: || Ne az egyes cégek teáinak összegét számold: az „egyszerre” szó egyetlen vásárlásra vonatkozik, így minden tételt külön kell megvizsgálni. ||
Hint 2: || Egy vektorba gyűjtsd a 500-nál nagyobb tételekhez tartozó cégneveket a bemenet sorrendjében, majd kiírás előtt a vektor méretét írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> firms;
    for (int i = 0; i < n; ++i) {
        string firm;
        int amount;
        cin >> firm >> amount;
        if (amount > 500) firms.push_back(firm);
    }

    cout << firms.size();
    for (const string& f : firms) cout << ' ' << f;
    cout << '\n';
    return 0;
}
