/*
Megoldás lényege:
A hírátadások egy irányított fát alkotnak: minden átadás egy élt jelent az adótól a kapó felé. A fa gyökere az a tag, akit senki sem kapóként említ, vagyis ő indította a hírt. Az éleket beolvasva adjacencia-listát építünk, majd a gyökérből szélességi bejárást végzünk. Minden tag közvetítőszáma a gyökértől mért élszám, amelyet a bejárás közben számolunk. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || A hír kezdőpontja az a tag, aki sehol nem szerepel kapóként, hiszen minden más tag pontosan egyszer kapta meg a hírt. ||
Hint 2: || A hírátadások a kezdőpontból kiinduló irányított fát alkotnak, ezért szélességi bejárással a kezdőponttól mért lépésszám adja meg mindenki közvetítőszámát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> sendTo(n + 1);
    vector<bool> receivedFrom(n + 1, false);
    for (int i = 0; i < n - 1; ++i) {
        int from, to;
        cin >> from >> to;
        sendTo[from].push_back(to);
        receivedFrom[to] = true;
    }

    int start = 1;
    for (int v = 1; v <= n; ++v) {
        if (!receivedFrom[v]) {
            start = v;
            break;
        }
    }

    vector<int> hops(n + 1, -1);
    queue<int> q;
    hops[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : sendTo[u]) {
            hops[v] = hops[u] + 1;
            q.push(v);
        }
    }

    for (int v = 1; v <= n; ++v) {
        cout << hops[v] << (v == n ? '\n' : ' ');
    }
    return 0;
}
