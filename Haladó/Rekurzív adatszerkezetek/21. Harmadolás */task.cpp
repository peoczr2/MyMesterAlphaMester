/*
Megoldás lényege:
A vállalkozók egy fát alkotnak, a gyökér az 1-es csúcs, és minden továbbadás a pénz
harmadára csökkenti az összeget. Egy továbbadó vállalkozó a pénz egyharmadát megtartja,
a munkát meg nem osztó (levél) vállalkozó viszont az egészet. Így egy v csúcs által
megtartott pénz X / 3^e alakú, ahol e = mélység + 1, ha v továbbad, és e = mélység,
ha v levél. A legkevesebbet megtartók a legnagyobb e-jű csúcsok, a legtöbbet megtartók
a legkisebb e-jű csúcsok, a munkát tovább nem adók pedig a levelek. Mindezt egy BFS-sel
kapjuk meg O(N) időben.
*/
/*
Hint 1: || Minden továbbadásnál a pénz harmadára csökken, ezért a pénz nagysága egyedül a mélységtől függ. ||
Hint 2: || Egy továbbadó vállalkozó a pénz egyharmadát tartja meg, egy levél az egészet, így a megtartott összeg nevezőjének kitevője mélység vagy mélység + 1. ||
Hint 3: || A legkevesebb pénzt a legnagyobb kitevőjű csúcsok tartják meg, a legtöbbet a legkisebb kitevőjűek, és a levelek egy külön halmazt adnak. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // A bemenet összes számát kiolvassuk, így a fájl eleji UTF-8 BOM és a CRLF sorvégek nem zavarnak.
    string all((istreambuf_iterator<char>(cin)), istreambuf_iterator<char>());
    vector<long long> nums;
    long long cur = 0;
    bool inNum = false;
    for (unsigned char c : all) {
        if (c >= '0' && c <= '9') {
            cur = cur * 10 + (c - '0');
            inNum = true;
        } else if (inNum) {
            nums.push_back(cur);
            cur = 0;
            inNum = false;
        }
    }
    if (inNum) nums.push_back(cur);
    if (nums.empty()) return 0;

    int N = (int)nums[0];
    long long maxIdRead = 2LL * N + 1;
    for (size_t i = 1; i < nums.size(); ++i) maxIdRead = max(maxIdRead, nums[i]);
    int maxId = (int)maxIdRead;

    vector<vector<int>> children(maxId + 1);
    for (int i = 0; i < N; ++i) {
        int s = (int)nums[1 + 3 * i];
        int a = (int)nums[2 + 3 * i];
        int b = (int)nums[3 + 3 * i];
        children[s].push_back(a);
        children[s].push_back(b);
    }

    // BFS a gyökérből (1-es vállalkozás): mélységek
    vector<int> depth(maxId + 1, -1);
    queue<int> q;
    depth[1] = 0;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : children[u]) {
            if (depth[v] == -1) {
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }
    }

    // e: a megtartott pénz nevezőjének kitevője (X / 3^e)
    vector<int> e(maxId + 1, -1);
    int emin = INT_MAX, emax = INT_MIN;
    for (int v = 1; v <= maxId; ++v) {
        if (depth[v] < 0) continue;
        bool passes = !children[v].empty();
        e[v] = depth[v] + (passes ? 1 : 0);
        emin = min(emin, e[v]);
        emax = max(emax, e[v]);
    }

    vector<int> fewestMoney, mostMoney, leaves;
    for (int v = 1; v <= maxId; ++v) {
        if (depth[v] < 0) continue;
        if (e[v] == emax) fewestMoney.push_back(v); // a legkevesebb pénzt tartják meg
        if (e[v] == emin) mostMoney.push_back(v);   // a legtöbb pénzt tartják meg
        if (children[v].empty()) leaves.push_back(v); // nem adják tovább a munkát
    }

    auto print = [](const vector<int>& xs) {
        cout << xs.size();
        for (int x : xs) cout << ' ' << x;
        cout << '\n';
    };
    print(fewestMoney);
    print(mostMoney);
    print(leaves);
    return 0;
}
