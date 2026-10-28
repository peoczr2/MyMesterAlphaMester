/*
Megoldás lényege:
A kérdés csak arra vonatkozik, hogy ki indult legalább egy versenyen, ezért a minimális pontszámok és a versenyzők pontszámai nem számítanak. Az összetett versenyről szóló mondat csak háttérinformáció. A minimumokat és a pontszámokat azonban be kell olvasni, hogy a beolvasás a megfelelő helyen maradjon. Egy logikai tömbben (1-től N-ig indexelve) minden versenynél a kiolvasott induló sorszámát igazra állítjuk. A végén a tömböt sorszám szerint, növekvő sorrendben bejárjuk, és kiírjuk az igaz értékű sorszámok számát, majd magukat a sorszámokat. Az időigény O(N + M·N), ami legfeljebb 10^4 bejegyzés, így bőven belefér a 0,1 mp-es időlimitbe.
*/
/*
Hint 1: || A minimális pontszámok és a pontok az összetett versenyre vonatkoznak, itt nincs rájuk szükség. Elég tudni, hogy egy tanuló szerepel-e valamelyik verseny indulói között. ||
Hint 2: || Használj N+1 méretű logikai tömböt. Minden versenynél a beolvasott sorszámokhoz állíts igazat, a pontot pedig olvasd be és dobd el. A végén a sorszámokat 1-től N-ig bejárva írd ki az igaz értékűeket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // A minimális pontszámokra nincs szükség, de be kell olvasni őket.
    for (int i = 0; i < m; i++) {
        int mini;
        cin >> mini;
    }

    vector<bool> indult(n + 1, false);
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int s, p;
            cin >> s >> p;
            indult[s] = true;
        }
    }

    vector<int> lista;
    for (int i = 1; i <= n; i++) {
        if (indult[i]) {
            lista.push_back(i);
        }
    }

    cout << lista.size();
    for (int x : lista) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
