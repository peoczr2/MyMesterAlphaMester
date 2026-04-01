#include <bits/stdc++.h>
using namespace std;

/*
    Az életkorok 1 és 150 közé esnek, ezért gyakorisági tömbbel megkereshető a
    középső elem.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> freq(151);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        ++freq[x];
    }

    int cel = (n + 1) / 2;
    for (int age = 1, sum = 0; age <= 150; ++age) {
        sum += freq[age];
        if (sum >= cel) {
            cout << age << '\n';
            return 0;
        }
    }
    return 0;
}
