/*
Megoldási ötlet:
Az irányítás miatt minden városból pontosan egy úton lehet a központba jutni, tehát a városok a központtal
gyökerezett fát alkotnak. Egy részfában a raktárak először helyben próbálják elnyelni a termékeket, és csak
az a mennyiség megy feljebb, ami már sehol nem fér el a részfán belül.

Legyen `excess[u]` az `u` részfájában keletkező nettó többlet, amelyet a szülő felé kell továbbvinni:

`excess[u] = max(0, termelés[u] - kapacitás[u] + sum(excess[gyerek]))`.

Az `u` részfájában dolgozó kamionok a részfa gyökeréig mindenképpen el tudnak jutni. Ha valahol lerakták a
szállítmányt, attól még üresen tovább tudnak menni a központ felé, ezért a szülőnél nem csak a megrakott,
hanem az összes, részfában már használt kamion rendelkezésre áll. Emiatt ha a gyerek-részfákban összesen
`sum(trucks[gyerek])` kamion kell, akkor ezek mind felhasználhatók `u` többletének továbbszállítására is.

Az `u` részfájából legalább `ceil(excess[u] / K)` kamionnak kell tudnia kifelé menni. Ezért a részfában
szükséges minimális kamionszám:

`trucks[u] = max(sum(trucks[gyerek]), ceil(excess[u] / K))`.

A teljes minimális kamionszám `trucks[root]`, az építendő központi raktár mérete pedig `excess[root]`.
*/
/*
Hint 1: || A központ felé vezető utak egy gyökerezett fát adnak, ezért érdemes alulról felfelé számolni. ||
Hint 2: || Egy részfa felől csak az a mennyiség megy tovább, ami a részfa saját raktáraiban már nem fér el. ||
Hint 3: || A részfában már használt kamionok üresen is tovább tudnak menni a szülő felé, ezért a szülőnél ezek újra felhasználhatók. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, truckCapacity;
    cin >> n >> truckCapacity;

    vector<long long> production(n + 1);
    vector<long long> storage(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> production[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> storage[i];
    }

    vector<int> parent(n + 1);
    int root = 1;
    for (int i = 1; i <= n; ++i) {
        cin >> parent[i];
        if (parent[i] == 0) {
            root = i;
        }
    }

    vector<vector<int>> children(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (parent[i] != 0) {
            children[parent[i]].push_back(i);
        }
    }

    vector<int> order = {root};
    for (size_t i = 0; i < order.size(); ++i) {
        int node = order[i];
        for (int child : children[node]) {
            order.push_back(child);
        }
    }

    vector<long long> excess(n + 1, 0);
    vector<long long> trucks(n + 1, 0);
    for (int i = static_cast<int>(order.size()) - 1; i >= 0; --i) {
        int node = order[i];
        long long childExcess = 0;
        long long childTrucks = 0;
        for (int child : children[node]) {
            childExcess += excess[child];
            childTrucks += trucks[child];
        }

        excess[node] = production[node] - storage[node] + childExcess;
        if (excess[node] < 0) {
            excess[node] = 0;
        }

        long long neededTrucks = (excess[node] + truckCapacity - 1) / truckCapacity;
        trucks[node] = max(childTrucks, neededTrucks);
    }

    cout << trucks[root] << '\n';
    cout << excess[root] << '\n';
    return 0;
}