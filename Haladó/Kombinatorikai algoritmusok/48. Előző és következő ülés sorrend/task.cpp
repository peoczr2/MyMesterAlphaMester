/*
   Előző és következő ülés sorrend: az M hely kiválasztása az 1..N halmazból
   szigorúan növekvő sorozatként. Ez a kombinációk lexikografikus előzője és
   következője.
*/
#include <bits/stdc++.h>
using namespace std;

static bool nextComb(vector<int>& a, int N) {
    int M = (int)a.size();
    for (int i = M - 1; i >= 0; --i) {
        int limit = N - (M - 1 - i);
        if (a[i] < limit) {
            ++a[i];
            for (int j = i + 1; j < M; ++j) a[j] = a[j - 1] + 1;
            return true;
        }
    }
    for (int i = 0; i < M; ++i) a[i] = i + 1;
    return false;
}

static bool prevComb(vector<int>& a, int N) {
    int M = (int)a.size();
    for (int i = M - 1; i >= 0; --i) {
        int lower = (i == 0 ? 1 : a[i - 1] + 1);
        if (a[i] > lower) {
            --a[i];
            for (int j = i + 1; j < M; ++j) a[j] = N - (M - 1 - j);
            return true;
        }
    }
    for (int i = 0; i < M; ++i) a[i] = N - M + 1 + i;
    return false;
}

static void printComb(const vector<int>& a) {
    for (int i = 0; i < (int)a.size(); ++i) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<int> a(M);
    for (int i = 0; i < M; ++i) cin >> a[i];

    auto prevA = a;
    auto nextA = a;
    prevComb(prevA, N);
    nextComb(nextA, N);
    printComb(prevA);
    printComb(nextA);
    return 0;
}