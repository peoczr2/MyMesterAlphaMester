/*
Megoldás lényege:
Minden mérést átalakítunk készültségi szintre: 800 cm felett 1, 900 cm felett 2, 1000 cm felett 3, különben 0.
Egy hely akkor felel meg, ha a szintje legalább 2-vel nagyobb az előző helyénél, ezért minden szomszédos párt egyszer megvizsgálunk.
Az első helynek nincs előzője, így a vizsgálatot a 2. helytől kezdjük.
A kimenet első sorába a találatok K darabszáma kerül, a második sorba pedig a helyek sorszáma növekvő sorrendben.
Az algoritmus egyetlen lineáris bejárás, O(N) időben fut.
*/
/*
Hint 1: || Nem kell külön árvizeket keresni: elég minden helyhez az előző hellyel összehasonlítani a készültségi szintet. ||
Hint 2: || A szintet a méret alapján határozd meg: 800 cm felett 1, 900 cm felett 2, 1000 cm felett 3, különben 0. Ezután a két szomszédos szint különbsége legyen legalább 2. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Készültségi szint: 0 (nincs), 1 (elsőfokú), 2 (másodfokú), 3 (harmadfokú)
int szint(int h) {
    if (h <= 800) return 0;
    if (h <= 900) return 1;
    if (h <= 1000) return 2;
    return 3;
}

int main() {
    int n;
    cin >> n;
    vector<int> s(n + 1, 0);  // 1-től indexelünk
    for (int i = 1; i <= n; i++) {
        int h;
        cin >> h;
        s[i] = szint(h);
    }

    vector<int> helyek;
    for (int i = 2; i <= n; i++) {
        if (s[i] - s[i - 1] >= 2) helyek.push_back(i);
    }

    cout << helyek.size() << "\n";
    for (size_t j = 0; j < helyek.size(); j++) {
        if (j) cout << ' ';
        cout << helyek[j];
    }
    if (!helyek.empty()) cout << "\n";
    return 0;
}
