/*
   Fák száma: a teljes bináris fák száma N levéllel a Catalan-szám
   C_{N-1}. Ezt a klasszikus rekurzív képlettel számoljuk ki.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    unsigned long long ans = 1;
    for (int i = 0; i < N - 1; ++i) {
        __int128 t = ans;
        t *= 2 * (2 * i + 1);
        t /= (i + 2);
        ans = (unsigned long long)t;
    }
    cout << ans << '\n';
    return 0;
}