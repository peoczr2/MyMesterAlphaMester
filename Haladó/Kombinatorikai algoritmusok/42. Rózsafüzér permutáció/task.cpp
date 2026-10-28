/*
   Rózsafüzér permutáció: a kanonikus alakban az 1 a második helyen áll, és az első elem (i)
   kisebb a harmadiknál (j). Az 1 nélküli sorozat következő permutációját keressük. Ha i-t megtartjuk,
   a j-től kezdődő rész next_permutation-nel rendezhető tovább, és j nem csökken, így i < j megmarad.
   Ha ez a rész már csökkenő, i-t kell növelni: az új első elem i+1 (csak ha i+1 < N), utána i+2 áll,
   a többi szám növekvő sorrendben. Ha i = N-1, az utolsó rózsafüzér után a 2 1 3 … N következik.
   Az időigény O(N).
*/
/*
Hint 1: || Hagyd el az 1-est a sorozatból, így a maradék számok rendezéseit kell végigjárnod. A kanonikus feltétel (i < j) az első két maradék elemre vonatkozik. ||
Hint 2: || Ha az első elemet (i) megtartod, a j-től kezdődő részre a szokásos next_permutation adja a következőt, mert j nem csökken, így i < j mindig teljesül. Ez csak akkor nem megy, ha a rész már csökkenő sorrend. ||
Hint 3: || Csökkenő résznél az első elemet kell növelni: az új első elem i+1 legyen (de csak ha i+1 kisebb N-nél), utána i+2, a többi szám pedig növekvő sorrendben. Ha i = N-1, következik a 2 1 3 … N. ||
*/
#include <bits/stdc++.h>
using namespace std;

static void print(const vector<int>& a) {
    for (int i = 0; i < (int)a.size(); ++i) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> p(N);
    for (int i = 0; i < N; ++i) cin >> p[i];

    vector<int> q;
    q.reserve(N - 1);
    for (int x : p) if (x != 1) q.push_back(x);

    if (next_permutation(q.begin() + 1, q.end())) {
        vector<int> ans;
        ans.push_back(q[0]);
        ans.push_back(1);
        ans.insert(ans.end(), q.begin() + 1, q.end());
        print(ans);
        return 0;
    }

    int a0 = q[0];
    if (a0 + 1 < N) {
        int a = a0 + 1;
        vector<int> ans = {a, 1, a + 1};
        for (int v = 2; v <= N; ++v) if (v != a && v != a + 1) ans.push_back(v);
        print(ans);
        return 0;
    }

    vector<int> ans;
    ans.push_back(2);
    ans.push_back(1);
    for (int v = 3; v <= N; ++v) ans.push_back(v);
    print(ans);
    return 0;
}