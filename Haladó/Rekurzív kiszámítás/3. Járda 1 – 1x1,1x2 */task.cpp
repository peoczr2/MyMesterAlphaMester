/*
Megoldás lényege:
Az N hosszú járdát az utolsó lap típusa szerint bontjuk fel. Az utolsó lap vagy egy
1-es, vagy egy 2-es, ezért a klasszikus Fibonacci-rekurzió adódik.

*/
/*
Hint 1: || Az utolsó lépés mindig egy 1 hosszú vagy egy 2 hosszú lapból áll. ||
Hint 2: || Az üres szakaszra 1 módon lehet lefedni a „semmit”: ez a rekurzió alapja. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<long long> dp(max(2, N + 1));  // N<=80: a legnagyobb érték (F(81)) belefér 64 bitbe
    dp[0] = 1;
    if (N >= 1) dp[1] = 1;
    for (int i = 2; i <= N; ++i) dp[i] = dp[i - 1] + dp[i - 2];

    cout << dp[N] << '\n';
    return 0;
}
