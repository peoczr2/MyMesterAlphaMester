/*
Megoldás lényege:
Egy település akkor mindig fagyos, ha minden napra 0 foknál kisebb hőmérsékletet jósolnak. Soronként végigmegyünk az értékeken, és ha valamelyik nem negatív, a település kiesik. A sor beolvasását akkor is be kell fejezni, ha a település már kiesett, különben a következő sor olvasása elcsúszik. Az idő O(N·M), a memória O(N).
*/
/*
Hint 1: || Egy település akkor "mindig fagyos", ha az összes napi előrejelzése 0-nál kisebb. A 0 maga már nem fagyos, ezért a 0 is kizárja a települést. ||
Hint 2: || Egy soron belül elég egy nem negatív értéket találni, de a sor többi számát is be kell olvasni, különben a következő település adatai elcsúsznak. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> fagyos;
    for (int i = 0; i < n; i++) {
        bool mindig = true;
        for (int j = 0; j < m; j++) {
            int x;
            cin >> x;
            if (x >= 0) mindig = false;
        }
        if (mindig) fagyos.push_back(i + 1);
    }

    cout << fagyos.size();
    for (int s : fagyos) cout << ' ' << s;
    cout << '\n';
    return 0;
}
