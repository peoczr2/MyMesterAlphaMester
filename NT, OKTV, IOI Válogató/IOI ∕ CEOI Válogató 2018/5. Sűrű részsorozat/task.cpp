/*
Megoldás lényege:
Az első feltétel azt jelenti, hogy a kiválasztott indexeknek minden M hosszú
ablakban szerepelniük kell, vagyis intervallumfedést kell végezni a [1, N-M+1]
ablakkezdési pozíciókon. A második feltétel szerint először a kiválasztott elemek
maximális értékét kell minimalizálni, majd azonos maximum esetén a kiválasztott
indexek számát.

Legyen X a kiválasztott elemek legnagyobb értéke. Ahhoz, hogy ilyen megoldás
egyáltalán létezzen, minden M hosszú ablakban kell legyen legalább egy <= X értékű
elem. A legkisebb ilyen X a csúszóablak-minimumok maximuma. Ha ezt X-et tudjuk,
akkor a <= X értékű pozíciók közül a legkevesebb indexet egy klasszikus greedy
intervallumfedéssel választjuk: mindig az aktuálisan még fedetlen ablakban a lehető
legjobbra eső megengedett pozíciót vesszük.
*/
/*
Hint 1: || A második feltétel miatt először a kiválasztott maximumot kell minimalizálni. Keresd meg a legkisebb X értéket, amelynél minden M hosszú ablakban van X-nél nem nagyobb elem: ez a csúszóablak-minimumok maximuma. ||
Hint 2: || Az X-nél nem nagyobb értékű pozíciók közül a fedéshez legkevesebb pozíciót kell választani. Ehhez intervallumfedés kell: mindig az első még fedetlen ablakban a lehető legjobbra eső megengedett pozíciót vedd. ||
Hint 3: || A csúszóablak-minimum egy monoton deque-kel számolható O(N) időben, a greedy fedés pedig a megengedett pozíciók sorfolytonos bejárásával, egy mutatóval szintén O(N) időben megoldható. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<long long> s(n + 1);
    for (int i = 1; i <= n; ++i) cin >> s[i];

    deque<int> dq;
    long long need = 0;
    for (int i = 1; i <= n; ++i) {
        while (!dq.empty() && s[dq.back()] >= s[i]) dq.pop_back();
        dq.push_back(i);
        while (!dq.empty() && dq.front() <= i - m) dq.pop_front();
        if (i >= m) need = max(need, s[dq.front()]);
    }

    vector<int> allowed;
    for (int i = 1; i <= n; ++i) {
        if (s[i] <= need) allowed.push_back(i);
    }

    vector<int> answer;
    int ptr = 0;
    int start = 1;
    int limit = n - m + 1;
    while (start <= limit) {
        while (ptr < (int)allowed.size() && allowed[ptr] < start) ++ptr;
        int best = -1;
        while (ptr < (int)allowed.size() && allowed[ptr] <= start + m - 1) {
            best = allowed[ptr];
            ++ptr;
        }
        if (best == -1) {
            // Elvileg nem fordulhat elő, mert need biztosítja a fedhetőséget.
            break;
        }
        answer.push_back(best);
        start = best + 1;
    }

    cout << answer.size() << '\n';
    for (int i = 0; i < (int)answer.size(); ++i) {
        if (i) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}