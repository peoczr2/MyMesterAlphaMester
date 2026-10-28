/*
Megoldás lényege:
Minden embernek összegyűjtjük a gyermekeit a szülő–gyerek párokból. Egy ember gyermekeinek száma
közvetlenül adódik, unokáinak száma pedig a gyermekei gyermekszámainak összege, ezért előbb a
gyermekszámokat, utána az unokaszámokat számoljuk ki. A három kérdésre ezután egy-egy lineáris
bejárás adja a választ. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Minden ember gyerekeinek számát a szülő–gyerek párokból egyetlen beolvasással megkapod: a szülő listájához hozzáfűzöd a gyereket. ||
Hint 2: || Egy ember unokáinak száma az összes gyereke gyermekszámának összege, tehát a gyermekszámok ismeretében egy második bejárás elég. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> gyerek(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int szulo, gyermek;
        cin >> szulo >> gyermek;
        gyerek[szulo].push_back(gyermek);
    }

    vector<int> gyerekSzam(n + 1, 0), unokaSzam(n + 1, 0);
    for (int v = 1; v <= n; v++) gyerekSzam[v] = gyerek[v].size();
    for (int v = 1; v <= n; v++)
        for (int c : gyerek[v]) unokaSzam[v] += gyerekSzam[c];

    int legtobbGyerek = 1, legtobbUnoka = 1, unokatlan = 0;
    for (int v = 1; v <= n; v++) {
        if (gyerekSzam[v] > gyerekSzam[legtobbGyerek]) legtobbGyerek = v;
        if (unokaSzam[v] > unokaSzam[legtobbUnoka]) legtobbUnoka = v;
        if (unokaSzam[v] == 0) unokatlan++;
    }

    cout << legtobbGyerek << '\n' << legtobbUnoka << '\n' << unokatlan << '\n';
    return 0;
}
