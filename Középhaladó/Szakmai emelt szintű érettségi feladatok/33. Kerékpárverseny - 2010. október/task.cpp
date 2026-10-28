/*
Megoldás lényege: a bemenet minden szakaszában az i-edik szám az i-edik rajtszámú versenyző helyezését adja, így ha ott 1 áll, az i-edik versenyző nyerte az adott szakaszt. Versenyzőnként összeszámoljuk az első helyezéseket, majd megkeressük a legnagyobb számot, és kiírjuk az ezt elérő versenyzők rajtszámait növekvő sorrendben. A fődíjat a nyertesek száma szerint egész osztással osztjuk el, így a lefelé kerekítés automatikusan teljesül. A beolvasás O(N·K) időben fut, ami legfeljebb 2·10^5 szám, tehát az időlimit bőven teljesíthető.
*/
/*
Hint 1: || A sorokban az i-edik szám az i-edik versenyző helyezése, így nem a sor első eleme számít, hanem az 1-es érték helye. Elég versenyzőnként egy számlálót tartani. ||
Hint 2: || Minden szakasz után vizsgáld meg, melyik helyen áll az 1-es érték, és ott növeld a megfelelő számlálót. A számlálók maximumát a beolvasás végén keresd meg. ||
Hint 3: || A nyertesek rajtszámait a sorszám szerinti bejárásban gyűjtsd össze, így már növekvő sorrendben lesznek. A díj egyenlő részre osztásához egész osztást használj: a maradék elvész, ez pont a lefelé kerekítés. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    long long prize;
    cin >> n >> k >> prize;

    vector<int> firsts(n + 1, 0);  // firsts[i]: az i-edik versenyző első helyezéseinek száma
    for (int s = 0; s < k; s++) {
        for (int i = 1; i <= n; i++) {
            int place;
            cin >> place;
            if (place == 1) firsts[i]++;
        }
    }

    int best = *max_element(firsts.begin() + 1, firsts.end());
    vector<int> winners;
    for (int i = 1; i <= n; i++) {
        if (firsts[i] == best) winners.push_back(i);
    }

    cout << "#\n";
    for (size_t i = 0; i < winners.size(); i++) {
        if (i > 0) cout << ' ';
        cout << winners[i];
    }
    cout << '\n';

    long long each = prize / (long long)winners.size();
    cout << "#\n";
    cout << each << '\n';
    return 0;
}
