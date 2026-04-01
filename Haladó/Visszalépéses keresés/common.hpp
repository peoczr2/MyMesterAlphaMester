#pragma once

#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct E { int to, rev, cap; };
    int n;
    vector<vector<E>> g;
    vector<int> lvl, it;

    explicit Dinic(int n = 0) { init(n); }
    void init(int n_) { n = n_; g.assign(n, {}); }
    void addEdge(int s, int t, int cap) {
        E a{t, (int)g[t].size(), cap};
        E b{s, (int)g[s].size(), 0};
        g[s].push_back(a);
        g[t].push_back(b);
    }
    bool bfs(int s, int t) {
        lvl.assign(n, -1);
        queue<int> q;
        lvl[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &e : g[v]) if (e.cap > 0 && lvl[e.to] < 0) {
                lvl[e.to] = lvl[v] + 1;
                q.push(e.to);
            }
        }
        return lvl[t] >= 0;
    }
    int dfs(int v, int t, int f) {
        if (v == t) return f;
        for (int &i = it[v]; i < (int)g[v].size(); ++i) {
            E &e = g[v][i];
            if (e.cap <= 0 || lvl[e.to] != lvl[v] + 1) continue;
            int got = dfs(e.to, t, min(f, e.cap));
            if (!got) continue;
            e.cap -= got;
            g[e.to][e.rev].cap += got;
            return got;
        }
        return 0;
    }
    int maxflow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            it.assign(n, 0);
            while (int f = dfs(s, t, INT_MAX)) flow += f;
        }
        return flow;
    }
};

struct MinCostMaxFlow {
    struct E { int to, rev, cap, cost; };
    int n;
    vector<vector<E>> g;

    explicit MinCostMaxFlow(int n = 0) { init(n); }
    void init(int n_) { n = n_; g.assign(n, {}); }
    void addEdge(int s, int t, int cap, int cost) {
        E a{t, (int)g[t].size(), cap, cost};
        E b{s, (int)g[s].size(), 0, -cost};
        g[s].push_back(a);
        g[t].push_back(b);
    }
    pair<int, long long> minCostMaxFlow(int s, int t, int need = INT_MAX) {
        const long long INF = (1LL << 60);
        long long cost = 0;
        int flow = 0;
        vector<long long> dist(n), pot(n, 0);
        vector<int> pv(n), pe(n);
        while (flow < need) {
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;
            priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
            pq.push({0, s});
            while (!pq.empty()) {
                auto [d, v] = pq.top();
                pq.pop();
                if (d != dist[v]) continue;
                for (int i = 0; i < (int)g[v].size(); ++i) {
                    auto &e = g[v][i];
                    if (e.cap <= 0) continue;
                    long long nd = d + e.cost + pot[v] - pot[e.to];
                    if (nd < dist[e.to]) {
                        dist[e.to] = nd;
                        pv[e.to] = v;
                        pe[e.to] = i;
                        pq.push({nd, e.to});
                    }
                }
            }
            if (dist[t] == INF) break;
            for (int v = 0; v < n; ++v) if (dist[v] < INF) pot[v] += dist[v];
            int add = need - flow;
            for (int v = t; v != s; v = pv[v]) add = min(add, g[pv[v]][pe[v]].cap);
            flow += add;
            cost += 1LL * add * pot[t];
            for (int v = t; v != s; v = pv[v]) {
                auto &e = g[pv[v]][pe[v]];
                e.cap -= add;
                g[v][e.rev].cap += add;
            }
        }
        return {flow, cost};
    }
};