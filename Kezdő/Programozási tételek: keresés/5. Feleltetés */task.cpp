/*
Megoldás lényege:
Először a névsor sorrendjében keressük az első tanulót, akinek legalább két elégtelen (1-es) osztályzata van. Ha ilyen nincs, újra végigmegyünk a névsoron, és az első olyan tanulót választjuk, akinek az átlagának tizedesjegye 4 vagy 6, vagyis fél jegyre áll. Az átlag tizedesjegyét egészekkel számoljuk: az átlag tízszerese 2*összeg, ennek utolsó számjegye adja a tizedesjegyet. Ha egyik feltétel sem teljesül, az 1. sorszámú tanuló a felelő. Mivel minden tanulót és osztályzatot legfeljebb néhányszor nézünk meg, az időigény O(N).
*/
/*
Hint 1: || Két szabályt kell sorban alkalmazni: először tanulónként meg kell számolni az egyeseket, és csak ha ez nem talál senkit, nézd az átlagokat. ||
Hint 2: || Az átlag tizedesjegyét ne lebegőpontos osztással számold: az átlag tízszerese 2 * az összeg, ennek utolsó számjegye a tizedesjegy, és azt kell 4 és 6 közötti értékkel összevetni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<array<int, 5>> g(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> g[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        int bad = 0;
        for (int j = 0; j < 5; j++) {
            if (g[i][j] == 1) {
                bad++;
            }
        }
        if (bad >= 2) {
            cout << i + 1 << endl;
            return 0;
        }
    }

    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < 5; j++) {
            sum += g[i][j];
        }
        int tenth = (2 * sum) % 10;
        if (tenth >= 4 && tenth <= 6) {
            cout << i + 1 << endl;
            return 0;
        }
    }

    cout << 1 << endl;
    return 0;
}
