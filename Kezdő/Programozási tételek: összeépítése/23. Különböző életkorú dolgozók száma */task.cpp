/*
Megoldás lényege:
Az életkorokat egy halmazba (set) gyűjtjük, a fizetés a kérdés szempontjából nem számít.
A halmaz minden értéket csak egyszer tárol, így a végén a halmaz mérete megadja a különböző életkorú dolgozók számát.
Az idő O(N log N), N ≤ 100 esetén ez az időlimithez képest bőven elegendő.
*/
/*
Hint 1: || Vedd észre, hogy a fizetés a kérdésre nincs hatással: csak az életkorok különbözősége számít. ||
Hint 2: || Használj olyan adatszerkezetet, amely minden értéket csak egyszer tárol (pl. set), és a végén kérdezd le az elemszámát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    set<int> korok;
    for (int i = 0; i < n; i++) {
        int kor, fizetes;
        cin >> kor >> fizetes;
        korok.insert(kor);
    }
    cout << korok.size() << "\n";
    return 0;
}
