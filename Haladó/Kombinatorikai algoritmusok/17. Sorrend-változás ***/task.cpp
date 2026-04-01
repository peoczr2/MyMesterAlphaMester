/*
   Sorrend-változás: a lehetséges sorrendek az egymást nem fedő szomszédos
   párok cseréiből állnak. Ezért bináris döntési fa szerint generálhatjuk
   őket lexikografikus sorrendben.
*/
#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> cur;
unsigned long long total;

void gen(int pos) {
    if (pos > N) {
        for (int i = 0; i < (int)cur.size(); ++i) {
            if (i) cout << ' ';
            cout << cur[i];
        }
        cout << '\n';
        return;
    }
    cur.push_back(pos);
    gen(pos + 1);
    cur.pop_back();
    if (pos < N) {
        cur.push_back(pos + 1);
        cur.push_back(pos);
        gen(pos + 2);
        cur.pop_back();
        cur.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    vector<unsigned long long> fib(N + 2, 0);
    fib[0] = fib[1] = 1;
    for (int i = 2; i <= N + 1; ++i) fib[i] = fib[i - 1] + fib[i - 2];
    total = fib[N];
    cout << total << '\n';
    gen(1);
    return 0;
}