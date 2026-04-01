#include <bits/stdc++.h>
using namespace std;

/*
    A ritka számok bináris alakjában nincs egymás melletti két 1-es. Ezeket a
    számokat növekvő sorrendben lehet unrankelni a megfelelő Fibonacci-szerű
    darabszámokkal.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;
    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }
    --n;

    vector<long long> lenCnt(50, 0);
    vector<long long> suf0(50, 0), suf1(50, 0);
    suf0[0] = suf1[0] = 1;
    for (int i = 1; i < 50; ++i) {
        suf0[i] = suf0[i - 1] + suf1[i - 1];
        suf1[i] = suf0[i - 1];
    }
    for (int len = 1; len < 50; ++len) lenCnt[len] = suf1[len - 1];

    int len = 1;
    while (n > lenCnt[len]) {
        n -= lenCnt[len];
        ++len;
    }

    string bits;
    bits.push_back('1');
    int prev = 1;
    for (int pos = 2; pos <= len; ++pos) {
        int rem = len - pos;
        if (prev == 1) {
            bits.push_back('0');
            prev = 0;
        } else {
            long long zeroCnt = suf0[rem];
            if (n <= zeroCnt) {
                bits.push_back('0');
                prev = 0;
            } else {
                bits.push_back('1');
                n -= zeroCnt;
                prev = 1;
            }
        }
    }

    long long ans = 0;
    for (char c : bits) ans = ans * 2 + (c - '0');
    cout << ans << '\n';
    return 0;
}