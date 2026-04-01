/*
Feladat: A hegymászó az 1. tábortól az N.-ig, majd vissza az 1.-ig megy. Legfeljebb M percet tud egyhuzamban menni, pihenést csak táborokban tarthat. Minimalizálni kell a pihenések számát és kiírni a táborokat.
Ötlet: A teljes útvonal egy lineáris checkpointsorozat: 1,2,...,N,N-1,...,1. A szomszédos checkpointok közti menetidők is adottak. Klasszikus „minimum megállás” mohó: mindig a lehető legmesszebbi checkpointig megyünk, ami még belefér M-be. Ez optimális, mert minden pihenésnél maximalizálja az elért előrehaladást.
Hint 1: || Alakítsd át az oda-vissza utat egyetlen lineáris szakaszsorrá. ||
Hint 2: || Egy pihenés után mindig a legtávolabbi elérhető táborig menj, ne állj meg korábban. ||
Hint 3: || A pihenéshelyek a „checkpoint indexből” visszaalakíthatók táborsorszámra. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<int> up(N, 0), down(N, 0);
    for (int i = 1; i <= N - 1; ++i) {
        cin >> up[i] >> down[i];
    }

    vector<int> camp;
    camp.reserve(2 * N - 1);
    for (int i = 1; i <= N; ++i) camp.push_back(i);
    for (int i = N - 1; i >= 1; --i) camp.push_back(i);

    int L = 2 * N - 2;
    vector<int> edge;
    edge.reserve(L);
    for (int i = 1; i <= N - 1; ++i) edge.push_back(up[i]);
    for (int i = N - 1; i >= 1; --i) edge.push_back(down[i]);

    vector<int> rests;
    int pos = 0;
    while (pos < L) {
        int nxt = pos;
        long long sum = 0;
        while (nxt < L && sum + edge[nxt] <= M) {
            sum += edge[nxt];
            ++nxt;
        }

        if (nxt == pos) {
            // A feladat korlátai szerint ez elvileg nem fordul elő (minden él <= M).
            cout << -1 << '\n' << '\n';
            return 0;
        }

        if (nxt == L) break;

        rests.push_back(camp[nxt]);
        pos = nxt;
    }

    cout << rests.size() << '\n';
    for (int i = 0; i < (int)rests.size(); ++i) {
        if (i) cout << ' ';
        cout << rests[i];
    }
    cout << '\n';
    return 0;
}
