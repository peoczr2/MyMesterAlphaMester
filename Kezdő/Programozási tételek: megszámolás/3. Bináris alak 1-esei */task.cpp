/*
Megoldás lényege:
A bináris alak számjegyeit a 2-vel való maradékos osztással kapjuk meg: az N 2-vel osztott maradéka az utolsó számjegy, majd N-et egész osztással 2-vel elosztva a következő számjegyhez jutunk.
Ezt ismételjük, amíg a szám nullává nem válik, és közben minden 1-es maradékot megszámolunk.
Mivel N legfeljebb 10000, a bináris alak legfeljebb 14 számjegyű, így az időigény O(log N).
*/
/*
Hint 1: || A legkisebb helyiértékű bináris számjegyet megkapod, ha a számot elosztod 2-vel, és a maradékot nézed. ||
Hint 2: || Ismételd a műveletet egy ciklusban, amíg a szám nem lesz 0: a maradék 1 esetén növeld a számlálót, majd a számot oszd 2-vel egész osztással. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int db = 0;
    while (n > 0) {
        if (n % 2 == 1) {
            db++;
        }
        n /= 2;
    }
    cout << db << endl;
    return 0;
}
