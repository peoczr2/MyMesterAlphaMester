/*
Megoldás lényege:
Egy egész számot tartunk nyilván, amely a bejárás közben a még le nem zárt nyitó zárójelek számát mutatja. Nyitó zárójelnél nő, záró zárójelnél csökken. Ha a számláló valaha negatívvá válik, egy záró zárójel nyitó nélkül állt, ezért a kifejezés hibás. A bejárás végén a számlálónak nullának kell lennie, különben maradt le nem zárt nyitó zárójel. Kifejezésenként az időigény a hossz, összesen O(N · hossz).
*/
/*
Hint 1: || Nem kell a zárójeleket párba rendezni: elég egy számlálót futtatni a kifejezésen, és figyelni, hogy mikor lesz negatív, illetve mennyi a végén. ||
Hint 2: || Két esetben a válasz Nem: ha a számláló a bejárás közben negatívvá válik (egy záró zárójel megelőzi a hozzá tartozó nyitót), vagy ha a végén nem nulla. Minden más esetben Igen. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int melyseg = 0;
        bool jo = true;
        for (char c : s) {
            if (c == '(') {
                melyseg++;
            } else if (c == ')') {
                melyseg--;
                if (melyseg < 0) jo = false;
            }
        }
        if (melyseg != 0) jo = false;
        cout << (jo ? "Igen" : "Nem") << "\n";
    }
    return 0;
}
