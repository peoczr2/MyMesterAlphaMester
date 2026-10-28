/*
Megoldás lényege:
A perc értéke (0, 15, 30 vagy 45) határozza meg a kiírás szerkezetét: egész óránál "X o'clock", negyednél "a quarter past X", félnél "half past X", háromnegyednél "a quarter to X+1" alakot használunk. Az órát 12 órás beosztásban írjuk ki: a 13–23 órából levonjuk a 12-t, a 12-es órát pedig a "twelve" szó jelöli. Az a.m./p.m. jelölést az eredeti óra dönti el: 12 óra előtt a.m., 12 órától p.m., a háromnegyedes esetben is az eredeti órából. A megoldás egyetlen elágazással, állandó időben fut.
*/
/*
Hint 1: || A 13–23 órás időpontokat 12 órás formára kell hozni: vond le belőlük a 12-t. Ügyelj arra, hogy a 12-es órát is a "twelve" szóval írd ki, és hogy a 12 óra utáni időpontok p.m. jelölést kapjanak. ||
Hint 2: || A perc négy lehetséges értékéhez külön eset tartozik. A 45 perc esetén a következő órát kell kiírni, és az utolsó óra után a következő óra a 0-s, azaz a 12-es lesz. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Az óra 12 órás alakja: 1..12 között, a 0 helyett a 12.
int hour12(int h) {
    int r = h % 12;
    return r == 0 ? 12 : r;
}

string numberWord(int n) {
    static const char *words[] = {"", "one", "two", "three", "four", "five", "six",
                                  "seven", "eight", "nine", "ten", "eleven", "twelve"};
    return words[n];
}

int main() {
    int h, m;
    cin >> h >> m;

    string suffix = (h < 12) ? "a.m." : "p.m.";
    string text;

    if (m == 0) {
        text = numberWord(hour12(h)) + " o'clock";
    } else if (m == 15) {
        text = "a quarter past " + numberWord(hour12(h));
    } else if (m == 30) {
        text = "half past " + numberWord(hour12(h));
    } else {
        text = "a quarter to " + numberWord(hour12(h + 1));
    }

    cout << text << ' ' << suffix << '\n';
    return 0;
}
