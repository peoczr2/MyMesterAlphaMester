/*
Megoldas lenyege:
A célba érkező országok azok, amelyek legalább egyszer szerepelnek a listában.
Mivel legfeljebb 200 különböző ország van, elég egy halmazba gyűjteni az
országkódokat, majd a végén rendezve kiírni őket.
*/
/*
Hint 1: || Nem az érkezési sorrend számít, csak az, hogy egy ország szerepelt-e. ||
Hint 2: || Tedd a kódokat halmazba vagy rendezett tömbbe, hogy ne legyen ismétlés. ||
Hint 3: || A kimenet az összes különböző ország kódja növekvő sorrendben. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    set<string> countries;
    for (int i = 0; i < n; ++i) {
        string code;
        cin >> code;
        countries.insert(code);
    }

    cout << countries.size() << '\n';
    bool first = true;
    for (const string &code : countries) {
        if (!first) cout << ' ';
        first = false;
        cout << code;
    }
    cout << '\n';
    return 0;
}
