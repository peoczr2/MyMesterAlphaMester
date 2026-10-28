/*
Megoldás lényege:
Az induló állomástól mért távolságok az előző állomástól mért távolságok folyamatos összegzésével adódnak. A végállomástól mért távolság ezért a teljes út hossza mínusz az adott állomásig megtett út, és ez a sorszámmal szigorúan csökken. Így a K méternél közelebbi állomások közül a legtávolabbit az a legkisebb sorszámú állomás adja, amelynek a végállomástól mért távolsága még kisebb K-nál. Az induló állomás is állomás, ezért ha a teljes út rövidebb K-nál, ő a válasz; a végállomás távolsága 0, így mindig van találat. Az időadatok nem befolyásolják az eredményt, az időigény O(N).
*/
/*
Hint 1: || Számold ki minden állomásra az induló állomástól mért távolságot az előző állomástól mért távolságok összegzésével, majd a végállomástól mért távolság ebből a teljes út hossza mínusz ez az érték. ||
Hint 2: || A végállomástól mért távolságok a sorszám növekedésével csökkennek, ezért a sorban elől álló első olyan állomás lesz a keresett, amelynek a végállomástól mért távolsága K-nál kisebb; ekkor a keresés leállhat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;

    vector<long long> pos(n + 1, 0);   // az induló állomástól mért távolság
    for (int i = 1; i <= n; i++) {
        long long t, arr, dep;
        cin >> t >> arr >> dep;
        pos[i] = pos[i - 1] + t;
    }

    long long total = pos[n];
    for (int i = 0; i <= n; i++) {
        long long d = total - pos[i];   // távolság a végállomástól
        if (d < k) {
            cout << i << ' ' << d << '\n';
            return 0;
        }
    }
    return 0;
}
