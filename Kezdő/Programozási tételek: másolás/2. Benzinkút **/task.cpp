/*
Megoldás lényege:
Az autók érkezési sorrendben állnak sorba, ezért nem kell a kút állapotát végigkövetni: elég tudni, melyik töltőhely szabadul fel legkorábban. Egy autó a legkorábban szabaduló helyen kezd tankolni, a kezdés az érkezési idő és ez a szabadulási idő közül a nagyobb, a befejezés pedig a kezdés plusz a tankolási idő. A K szabadulási időpontot prioritási sorban (min-heap) tartjuk, így a legkisebb mindig gyorsan elérhető, és minden autó után a befejezési idő visszakerül a sorba. Az időigény O(N log K), a memóriaigény O(K).
*/
/*
Hint 1: || Nem kell az egész kutat szimulálni: az autók sorrendje adott, így csak azt kell tudni, melyik töltőhely szabadul fel legkorábban. ||
Hint 2: || Tarts nyilván K darab „mikor szabadul fel” értéket, kezdetben mindegyik legyen 0. Egy autó kezdési ideje a saját érkezési ideje és a legkorábbi szabadulási idő közül a nagyobb. ||
Hint 3: || A legkisebb szabadulási idő gyors kiválasztására min-heap típusú prioritási sort használj. Az időket percben számold (60-szor az óra plusz a perc), és a kiíráskor alakítsd vissza óra és perc párra. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    priority_queue<int, vector<int>, greater<int>> freeAt;
    for (int i = 0; i < k; i++) {
        freeAt.push(0);
    }

    for (int i = 0; i < n; i++) {
        int h, m, duration;
        cin >> h >> m >> duration;
        int arrive = h * 60 + m;

        int start = max(arrive, freeAt.top());
        freeAt.pop();
        int leave = start + duration;
        freeAt.push(leave);

        cout << leave / 60 << " " << leave % 60 << "\n";
    }
    return 0;
}
