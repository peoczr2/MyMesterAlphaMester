#include <bits/stdc++.h>
using namespace std;

/*
    Egy négyzet alakú járólap akkor jó minden terembe, ha az összes szélesség és
    hosszúság osztója. Ezért minden kastélynál a termek oldalainak összesített
    legnagyobb közös osztóját kell kiszámítani.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    while (k--) {
        int t;
        cin >> t;
        long long g = 0;
        for (int i = 0; i < t; ++i) {
            long long a, b;
            cin >> a >> b;
            g = std::gcd(g, a);
            g = std::gcd(g, b);
        }
        cout << g << '\n';
    }
    return 0;
}