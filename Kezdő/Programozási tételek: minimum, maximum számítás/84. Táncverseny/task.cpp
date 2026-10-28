/*
Megoldás lényege:
Az érkezőket sorrendben dolgozzuk fel: a fiúk a teremben várakoznak, a lányok érkezéskor azonnal párt választanak a még szabad fiúk közül, a legnagyobb tudásúét, egyenlőség esetén a korábban érkezőt. A várakozó fiúkat egy prioritási sorba (max-heap) tesszük (tudásszint, -fiú-sorszám) kulccsal, így a sor tetején mindig a helyes fiú áll, és egy lány O(log N) idő alatt párt választ. A fiúk és a lányok saját, nemenkénti sorszámát is nyilvántartjuk, és a végén a legnagyobb tudásösszegű pár adatait írjuk ki. Az összesen O(N log N) időben fut.
*/
/*
Hint 1: || Dolgozd fel az érkezőket sorrendben: a fiúk a teremben várakoznak, a lányok érkezéskor azonnal párt választanak a még szabad fiúk közül. ||
Hint 2: || A lánynak a szabad fiúk közül a legnagyobb tudásút kell választania, egyenlőség esetén a korábban érkezőt. Erre prioritási sor (max-heap) alkalmas, amelybe a fiúkat (tudásszint, -fiú-sorszám) párként tesszük be. ||
Hint 3: || Minden lány érkezésekor a sor tetejét vedd ki: ez lesz a párja, és a pár tudásösszege a két tudásszint összege. A végén azt a párt írd ki, amelynek a tudásösszege a legnagyobb, a fiú és a lány sorszámát nemenként számolva. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    // (tudásszint, -fiú-sorszám): a tetején a legnagyobb tudás, egyenlőségnél a legkorábbi fiú
    priority_queue<pair<int, int>> waiting;
    int boys = 0, girls = 0;
    long long bestSum = -1;
    int bestBoy = 0, bestGirl = 0;

    for (int k = 0; k < 2 * n; k++) {
        int e, t;
        cin >> e >> t;
        if (e == 1) {
            boys++;
            waiting.push({t, -boys});
        } else {
            girls++;
            pair<int, int> top = waiting.top();
            waiting.pop();
            int boyNo = -top.second;
            long long sum = (long long)top.first + t;
            if (sum > bestSum) {
                bestSum = sum;
                bestBoy = boyNo;
                bestGirl = girls;
            }
        }
    }

    cout << bestBoy << " " << bestGirl << " " << bestSum << "\n";
    return 0;
}
