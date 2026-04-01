/*
Az első sorban keresett érték a klasszikus minimális maximális szegmensösszeg: a konténereket K darab,
nem üres, összefüggő részre kell bontani úgy, hogy a legnagyobb részösszeg minimális legyen. Erre bináris
keresést végzünk, és egy adott felső korlátról mohón eldöntjük, hány kamion kellene. Miután megvan a minimális
terhelési plafon, hátulról visszaépítjük pontosan K nem üres szegmens kezdőindexeit.
*/
/*
Hint 1: || Ha adott egy X terhelési korlát, akkor mohón megmondható, legfeljebb hány kamion kell. ||
Hint 2: || A válasz a legnagyobb konténersúly és az összsúly között binárisan kereshető. ||
Hint 3: || A konkrét felosztást célszerű hátulról visszaépíteni, hogy biztosan maradjon minden korábbi kamionnak legalább egy konténer. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<long long> a(n + 1);
    long long low = 0, high = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        low = max(low, a[i]);
        high += a[i];
    }

    auto need_trucks = [&](long long limit) {
        int trucks = 1;
        long long sum = 0;
        for (int i = 1; i <= n; ++i) {
            if (sum + a[i] > limit) {
                ++trucks;
                sum = a[i];
            } else {
                sum += a[i];
            }
        }
        return trucks;
    };

    while (low < high) {
        long long mid = (low + high) / 2;
        if (need_trucks(mid) <= k) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    long long answer = low;
    vector<int> start(k + 1, 1);
    int right = n;
    for (int truck = k; truck >= 1; --truck) {
        long long sum = 0;
        int left = right;
        while (left >= truck && sum + a[left] <= answer) {
            sum += a[left];
            --left;
        }
        start[truck] = left + 1;
        right = left;
    }

    cout << answer << '\n';
    for (int i = 1; i <= k; ++i) {
        if (i > 1) {
            cout << ' ';
        }
        cout << start[i];
    }
    cout << '\n';
    return 0;
}