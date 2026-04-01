/*
Az i-edik táborból a j-edikbe akkor lehet továbblépni egy újabb megállással, ha az i-edik táborban feltöltött és az
odaérkezéskor megmaradt élelem elég a két tábor közti útra. Mivel a táborok távolság szerint rendezettek, ez egy DAG,
ahol minden él költsége 1 megállás, az állapot értéke pedig az adott táborban megállás után megmaradó élelem. Minden
táborhoz a legkevesebb megállásszámú elérés közül a legtöbb maradék élelmet tartjuk meg, így O(N^2) időben megkapjuk
az optimális megállólistát is.
*/
/*
Hint 1: || Egy táborból továbbindulva a maradék készletből le kell vonni az odáig megtett utat, majd hozzáadni az ottani élelmet, de H-nál nem lehet több. ||
Hint 2: || Ha ugyanannyi megállással kétféleképpen elérsz egy tábort, akkor a több maradék élelem mindig jobb. ||
Hint 3: || A táborok rendezettek, ezért elegendő minden korábbi táborból minden későbbit megpróbálni. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t, h;
    cin >> n >> t >> h;
    vector<int> dist(n + 1), food(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> dist[i] >> food[i];
    }

    const int INF = 1e9;
    vector<int> stops(n + 1, INF), fuel(n + 1, -1), parent(n + 1, -1);
    stops[1] = 1;
    fuel[1] = min(h, food[1]);

    for (int i = 1; i <= n; ++i) {
        if (stops[i] == INF) {
            continue;
        }
        for (int j = i + 1; j <= n; ++j) {
            int need = dist[j] - dist[i];
            if (need > fuel[i]) {
                break;
            }
            int next_fuel = min(h, fuel[i] - need + food[j]);
            if (stops[i] + 1 < stops[j] || (stops[i] + 1 == stops[j] && next_fuel > fuel[j])) {
                stops[j] = stops[i] + 1;
                fuel[j] = next_fuel;
                parent[j] = i;
            }
        }
    }

    int best = -1;
    for (int i = 1; i <= n; ++i) {
        if (stops[i] != INF && t - dist[i] <= fuel[i]) {
            if (best == -1 || stops[i] < stops[best] || (stops[i] == stops[best] && fuel[i] > fuel[best])) {
                best = i;
            }
        }
    }

    vector<int> route;
    for (int x = best; x != -1; x = parent[x]) {
        route.push_back(x);
    }
    reverse(route.begin(), route.end());

    cout << route.size() << '\n';
    for (int i = 0; i < (int)route.size(); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << route[i];
    }
    cout << '\n';
    return 0;
}