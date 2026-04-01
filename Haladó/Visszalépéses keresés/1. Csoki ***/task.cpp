/*
Hungarian megoldás: az egyes emberekhez adott csokoládékészleteket úgy keressük
meg, hogy a darabszám-, illetve páronkénti együttjárási feltételek is teljesüljenek.

Hint 1: || Egy ember pontosan Q csokoládét kap, ezért mindig Q elemű részhalmazt választunk. ||
Hint 2: || A type- és pair-számlálókat visszalépéssel kell nullára vinni. ||
Hint 3: || Az azonos sorrendű megoldások szimmetriáját érdemes törni a blokkok rendezésével. ||
*/

#include <bits/stdc++.h>
using namespace std;

int N, M, P, Q, K;
vector<int> types;
vector<vector<int>> pairCnt;
vector<int> ansMask;
vector<int> masks;

bool goodMask(int mask) {
    vector<int> bits;
    for (int i = 0; i < N; ++i) if (mask & (1 << i)) bits.push_back(i);
    for (int x : bits) if (types[x] == 0) return false;
    for (int i = 0; i < (int)bits.size(); ++i) for (int j = i + 1; j < (int)bits.size(); ++j) if (pairCnt[bits[i]][bits[j]] == 0) return false;
    return true;
}

long long sumTypesLeft() {
    long long s = 0;
    for (int x : types) s += x;
    return s;
}

bool dfs(int idx, int lastMask) {
    if (idx == M) {
        for (int x : types) if (x != 0) return false;
        for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) if (pairCnt[i][j] != 0) return false;
        return true;
    }
    int rem = M - idx;
    if (sumTypesLeft() != 1LL * rem * Q) return false;
    for (int x : types) if (x < 0 || x > rem) return false;
    for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) if (pairCnt[i][j] < 0 || pairCnt[i][j] > rem) return false;

    vector<int> cand;
    for (int mask : masks) {
        if (mask < lastMask) continue;
        if (!goodMask(mask)) continue;
        cand.push_back(mask);
    }
    sort(cand.begin(), cand.end(), [&](int a, int b) {
        int sa = 0, sb = 0;
        for (int i = 0; i < N; ++i) {
            if (a & (1 << i)) sa += types[i];
            if (b & (1 << i)) sb += types[i];
        }
        return sa < sb;
    });
    for (int mask : cand) {
        vector<int> bits;
        for (int i = 0; i < N; ++i) if (mask & (1 << i)) bits.push_back(i);
        for (int x : bits) --types[x];
        for (int i = 0; i < (int)bits.size(); ++i) for (int j = i + 1; j < (int)bits.size(); ++j) --pairCnt[bits[i]][bits[j]], --pairCnt[bits[j]][bits[i]];
        ansMask[idx] = mask;
        if (dfs(idx + 1, mask)) return true;
        for (int i = 0; i < (int)bits.size(); ++i) for (int j = i + 1; j < (int)bits.size(); ++j) ++pairCnt[bits[i]][bits[j]], ++pairCnt[bits[j]][bits[i]];
        for (int x : bits) ++types[x];
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> P >> Q >> K;
    types.assign(N, P);
    pairCnt.assign(N, vector<int>(N, K));
    int totalMasks = 1 << N;
    for (int mask = 0; mask < totalMasks; ++mask) if (__builtin_popcount((unsigned)mask) == Q) masks.push_back(mask);
    ansMask.assign(M, 0);
    if (!dfs(0, 0)) {
        cout << -1 << '\n';
        return 0;
    }
    for (int idx = 0; idx < M; ++idx) {
        bool first = true;
        for (int i = 0; i < N; ++i) if (ansMask[idx] & (1 << i)) {
            if (!first) cout << ' ';
            cout << i + 1;
            first = false;
        }
        cout << '\n';
    }
    return 0;
}