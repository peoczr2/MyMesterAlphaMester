/*
Megoldás lényege:
Az első kérdésnél X és Y karaktereit az elejétől kezdve egyszerre hasonlítjuk össze, és az első eltérésnél megállunk; a megegyező szakasz lesz az első kimeneti sor.
A második kérdésnél Y karaktereit balról jobbra haladva keressük X-ben, mindig az előző találat utáni résztől folytatva. Az első olyan karakternél, amelyet már nem találunk meg, megállunk; Y addig beolvasott kezdőszelete lesz a második sor.
Mindkét rész egyetlen bejárás, így az időigény O(|X|+|Y|).
*/
/*
Hint 1: || Az első kérdésnél a két sorozatot egyszerre, az elejétől kezdve kell végignézni, és az első különbségnél abba kell hagyni. ||
Hint 2: || A második kérdésnél Y karaktereit sorban vedd, és X-ben egy mutatóval keresd meg őket: minden találat után a mutatót a találat utáni pozícióra léptesd. ||
Hint 3: || Ha egy karaktert már nem találsz meg X maradék részében, az eddig sikeresen párosított Y-beli kezdőszelet a válasz, és tovább nem kell menni. ||
*/
#include <bits/stdc++.h>
using namespace std;

string readLine() {
    string s;
    getline(cin, s);
    while (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
    return s;
}

int main() {
    string x = readLine();
    string y = readLine();

    size_t common = 0;
    while (common < x.size() && common < y.size() && x[common] == y[common]) {
        common++;
    }
    cout << x.substr(0, common) << endl;

    size_t pos = 0;
    size_t len = 0;
    for (char c : y) {
        while (pos < x.size() && x[pos] != c) {
            pos++;
        }
        if (pos == x.size()) {
            break;
        }
        pos++;
        len++;
    }
    cout << y.substr(0, len) << endl;

    return 0;
}
