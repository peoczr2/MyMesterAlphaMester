/*
Megoldás lényege:
Egy versenyt akkor tekintünk eredménytelennek, ha egyetlen résztvevő pontszáma sem éri el a verseny minimális pontszámát. Versenyenként egy logikai jelzőt használunk: kezdetben hamis, és ha valamelyik résztvevő eléri a minimumot, igazra állítjuk. A bejárás végén a hamis jelzésű versenyek sorszámait gyűjtjük, majd sorrendben kiírjuk őket a darabszámukkal együtt. Minden résztvevőt egyszer olvasunk be, így az időigény O(N·M), ami a korlátok mellett gyors.
*/
/*
Hint 1: || Egy versenyt akkor kell eredménytelennek tekinteni, ha a résztvevők közül senki nem éri el a hozzá tartozó minimális pontszámot. ||
Hint 2: || Versenyenként egy logikai változóval jelezd, volt-e legalább egy minimumot elérő pont. A résztvevőket akkor is végig kell olvasni, ha már találtál ilyent. A versenyek bejárása után a hamis értékű sorszámokat írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> mini(m);
    for (int i = 0; i < m; i++) {
        cin >> mini[i];
    }

    vector<int> bad;
    for (int i = 0; i < m; i++) {
        int ind;
        cin >> ind;
        bool reached = false;
        for (int j = 0; j < ind; j++) {
            int s, p;
            cin >> s >> p;
            if (p >= mini[i]) {
                reached = true;
            }
        }
        if (!reached) {
            bad.push_back(i + 1);
        }
    }

    cout << bad.size();
    for (int x : bad) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
