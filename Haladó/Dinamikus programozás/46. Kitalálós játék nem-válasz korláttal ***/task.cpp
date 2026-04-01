/*
Legyen dp[k][h] az a darabszám, ahány különböző szám biztosan megkülönböztethető k kérdéssel és legfeljebb h darab
"nem" válasszal. Az első kérdés két részre osztja a lehetőségeket: az "igen" ág még h nem-válasszal kezelhető, a "nem"
ág már csak h-1-gyel, ezért dp[k][h] = dp[k-1][h] + dp[k-1][h-1]. Addig növeljük a kérdések számát, amíg ez az érték el
nem éri N-et.
*/
/*
Hint 1: || Inkább azt számold, adott kérdésszámmal mekkora tartomány kezelhető, ne közvetlenül a minimális K-t. ||
Hint 2: || A "nem" ág fogyaszt egyet a még megengedett nem-válaszokból, az "igen" ág nem. ||
Hint 3: || Ha 0 darab "nem" válasz maradhat, akkor valójában csak 1 szám kezelhető biztosan. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    int H;
    cin >> n >> H;

    vector<long long> dp(H + 1, 1), next_dp(H + 1, 1);
    int questions = 0;
    while (dp[H] < n) {
        ++questions;
        next_dp[0] = 1;
        for (int h = 1; h <= H; ++h) {
            next_dp[h] = min(n, dp[h] + dp[h - 1]);
        }
        dp.swap(next_dp);
    }

    cout << questions << '\n';
    return 0;
}
