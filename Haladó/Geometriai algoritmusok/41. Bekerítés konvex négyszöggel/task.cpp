/*
Megoldás: először megpróbáljuk a célpont körüli négy nyílt kvadráns legközelebbi
pontjából álló jelöltet, mert ez adja a mintában szereplő természetes négyszöget.
Ha ez nem jó, egy kis, irányokból és oktánsokból vett jelöltkészleten próbálunk ki
konvex négyszögeket, és minden jelöltet pontosan ellenőrzünk egy kd-fával.
*/

#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
    int id;
};

static long long cross(const Pt& a, const Pt& b, const Pt& c) {
    __int128 v = (__int128)(b.x - a.x) * (c.y - a.y) - (__int128)(b.y - a.y) * (c.x - a.x);
    if (v < 0) return -1;
    if (v > 0) return 1;
    return 0;
}

static __int128 cross128(long long ax, long long ay, long long bx, long long by) {
    return (__int128)ax * by - (__int128)ay * bx;
}

static long long sqr(long long v) {
    return v * v;
}

static long long dist2(const Pt& a, const Pt& b) {
    return sqr(a.x - b.x) + sqr(a.y - b.y);
}

static vector<Pt> convexHullStrict(vector<Pt> pts) {
    sort(pts.begin(), pts.end(), [](const Pt& a, const Pt& b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.id < b.id;
    });
    pts.erase(unique(pts.begin(), pts.end(), [](const Pt& a, const Pt& b) {
        return a.x == b.x && a.y == b.y;
    }), pts.end());

    int n = (int)pts.size();
    if (n <= 1) return pts;

    vector<Pt> lower, upper;
    for (const auto& p : pts) {
        while ((int)lower.size() >= 2 && cross(lower[(int)lower.size() - 2], lower.back(), p) <= 0) lower.pop_back();
        lower.push_back(p);
    }
    for (int i = n - 1; i >= 0; --i) {
        const auto& p = pts[i];
        while ((int)upper.size() >= 2 && cross(upper[(int)upper.size() - 2], upper.back(), p) <= 0) upper.pop_back();
        upper.push_back(p);
    }

    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

static bool pointInConvexPolygonInclusive(const vector<Pt>& poly, const Pt& p) {
    int n = (int)poly.size();
    if (n == 0) return false;
    if (n == 1) return p.x == poly[0].x && p.y == poly[0].y;
    if (n == 2) {
        return cross(poly[0], poly[1], p) == 0 &&
               min(poly[0].x, poly[1].x) <= p.x && p.x <= max(poly[0].x, poly[1].x) &&
               min(poly[0].y, poly[1].y) <= p.y && p.y <= max(poly[0].y, poly[1].y);
    }
    if (cross(poly[0], poly[1], p) < 0) return false;
    if (cross(poly[0], poly[n - 1], p) > 0) return false;
    int l = 1, r = n - 1;
    while (r - l > 1) {
        int m = (l + r) >> 1;
        if (cross(poly[0], poly[m], p) >= 0) l = m;
        else r = m;
    }
    return cross(poly[l], poly[l + 1], p) >= 0;
}

static array<Pt, 4> normalizeQuad(array<Pt, 4> q) {
    long double cx = 0, cy = 0;
    for (const auto& p : q) {
        cx += (long double)p.x;
        cy += (long double)p.y;
    }
    cx /= 4.0L;
    cy /= 4.0L;
    sort(q.begin(), q.end(), [&](const Pt& a, const Pt& b) {
        long double aa = atan2l((long double)a.y - cy, (long double)a.x - cx);
        long double ab = atan2l((long double)b.y - cy, (long double)b.x - cx);
        if (aa != ab) return aa < ab;
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.id < b.id;
    });
    long long area = 0;
    for (int i = 0; i < 4; ++i) {
        const Pt& a = q[i];
        const Pt& b = q[(i + 1) % 4];
        area += a.x * b.y - a.y * b.x;
    }
    if (area < 0) reverse(q.begin(), q.end());
    return q;
}

static bool pointInStrictConvexQuad(const array<Pt, 4>& q, const Pt& p) {
    long long o = cross(q[0], q[1], q[2]);
    if (o == 0) return false;
    if (o > 0) {
        for (int i = 0; i < 4; ++i) if (cross(q[i], q[(i + 1) % 4], p) <= 0) return false;
    } else {
        for (int i = 0; i < 4; ++i) if (cross(q[i], q[(i + 1) % 4], p) >= 0) return false;
    }
    return true;
}

static bool quadContainsPointInclusive(const array<Pt, 4>& q, long long x, long long y) {
    Pt p{x, y, -1};
    long long o = cross(q[0], q[1], q[2]);
    if (o == 0) return false;
    if (o > 0) {
        for (int i = 0; i < 4; ++i) if (cross(q[i], q[(i + 1) % 4], p) < 0) return false;
    } else {
        for (int i = 0; i < 4; ++i) if (cross(q[i], q[(i + 1) % 4], p) > 0) return false;
    }
    return true;
}

static bool isEmptyQuad(const array<Pt, 4>& q, const vector<Pt>& pts) {
    for (const auto& p : pts) {
        bool vertex = false;
        for (int i = 0; i < 4; ++i) {
            if (p.id == q[i].id) {
                vertex = true;
                break;
            }
        }
        if (vertex) continue;
        if (quadContainsPointInclusive(q, p.x, p.y)) return false;
    }
    return true;
}

struct KdNode {
    long long minx, maxx, miny, maxy;
    int left = -1, right = -1;
    int begin = 0, end = 0;
};

static const int LEAF_SIZE = 16;

struct KdTree {
    const vector<Pt>* pts = nullptr;
    vector<int> order;
    vector<KdNode> nodes;

    int build(int l, int r) {
        int id = (int)nodes.size();
        nodes.push_back({});

        nodes[id].minx = nodes[id].maxx = (*pts)[order[l]].x;
        nodes[id].miny = nodes[id].maxy = (*pts)[order[l]].y;
        for (int i = l + 1; i < r; ++i) {
            const Pt& p = (*pts)[order[i]];
            nodes[id].minx = min(nodes[id].minx, p.x);
            nodes[id].maxx = max(nodes[id].maxx, p.x);
            nodes[id].miny = min(nodes[id].miny, p.y);
            nodes[id].maxy = max(nodes[id].maxy, p.y);
        }

        if (r - l <= LEAF_SIZE) {
            nodes[id].begin = l;
            nodes[id].end = r;
            return id;
        }

        bool splitX = (nodes[id].maxx - nodes[id].minx >= nodes[id].maxy - nodes[id].miny);
        int m = (l + r) >> 1;
        nth_element(order.begin() + l, order.begin() + m, order.begin() + r, [&](int a, int b) {
            if (splitX) {
                if ((*pts)[a].x != (*pts)[b].x) return (*pts)[a].x < (*pts)[b].x;
                if ((*pts)[a].y != (*pts)[b].y) return (*pts)[a].y < (*pts)[b].y;
            } else {
                if ((*pts)[a].y != (*pts)[b].y) return (*pts)[a].y < (*pts)[b].y;
                if ((*pts)[a].x != (*pts)[b].x) return (*pts)[a].x < (*pts)[b].x;
            }
            return (*pts)[a].id < (*pts)[b].id;
        });

        nodes[id].left = build(l, m);
        nodes[id].right = build(m, r);
        return id;
    }

    void init(const vector<Pt>& p) {
        pts = &p;
        order.resize(p.size());
        iota(order.begin(), order.end(), 0);
        nodes.clear();
        if (!p.empty()) build(0, (int)p.size());
    }

    bool anyInside(int id, const array<Pt, 4>& q, const array<int, 4>& excluded) const {
        const KdNode& node = nodes[id];

        auto cornerInside = [&](long long x, long long y) {
            return quadContainsPointInclusive(q, x, y);
        };

        bool allInside = true;
        for (long long x : {node.minx, node.maxx}) {
            for (long long y : {node.miny, node.maxy}) {
                if (!cornerInside(x, y)) allInside = false;
            }
        }
        if (allInside) {
            if (node.end - node.begin > 4) return true;
        }

        auto edgeOutside = [&](int a, int b) {
            long long vals[4] = {
                (long long)cross128(q[b].x - q[a].x, q[b].y - q[a].y, node.minx - q[a].x, node.miny - q[a].y),
                (long long)cross128(q[b].x - q[a].x, q[b].y - q[a].y, node.minx - q[a].x, node.maxy - q[a].y),
                (long long)cross128(q[b].x - q[a].x, q[b].y - q[a].y, node.maxx - q[a].x, node.miny - q[a].y),
                (long long)cross128(q[b].x - q[a].x, q[b].y - q[a].y, node.maxx - q[a].x, node.maxy - q[a].y)
            };
            bool allNeg = true, allPos = true;
            for (long long v : vals) {
                allNeg &= (v < 0);
                allPos &= (v > 0);
            }
            return allNeg || allPos;
        };

        for (int i = 0; i < 4; ++i) {
            if (edgeOutside(i, (i + 1) % 4)) return false;
        }

        if (node.left == -1) {
            for (int i = node.begin; i < node.end; ++i) {
                const Pt& p = (*pts)[order[i]];
                bool skip = false;
                for (int ex : excluded) {
                    if (p.id == ex) {
                        skip = true;
                        break;
                    }
                }
                if (skip) continue;
                if (quadContainsPointInclusive(q, p.x, p.y)) return true;
            }
            return false;
        }

        if (anyInside(node.left, q, excluded)) return true;
        return anyInside(node.right, q, excluded);
    }
};

static bool candidateQuadWorks(const array<Pt, 4>& q, const Pt& target, const vector<Pt>& pts, const KdTree& kd, array<Pt, 4>& answer) {
    array<Pt, 4> ordered = normalizeQuad(q);
    if (!pointInStrictConvexQuad(ordered, target)) return false;
    if (kd.nodes.empty()) return false;
    array<int, 4> excluded{ordered[0].id, ordered[1].id, ordered[2].id, ordered[3].id};
    if (kd.anyInside(0, ordered, excluded)) return false;
    if (!isEmptyQuad(ordered, pts)) return false;
    answer = ordered;
    return true;
}

static int octantOf(long long dx, long long dy) {
    if (dx >= 0 && dy >= 0) return (dx >= dy) ? 0 : 1;
    if (dx < 0 && dy >= 0) return (-dx <= dy) ? 2 : 3;
    if (dx < 0 && dy < 0) return (-dx >= -dy) ? 4 : 5;
    return (dx <= -dy) ? 6 : 7;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    if (!(cin >> K)) return 0;

    while (K--) {
        int N;
        Pt target;
        cin >> N >> target.x >> target.y;

        vector<Pt> pts(N);
        bool targetIsPoint = false;
        for (int i = 0; i < N; ++i) {
            cin >> pts[i].x >> pts[i].y;
            pts[i].id = i + 1;
            if (pts[i].x == target.x && pts[i].y == target.y) targetIsPoint = true;
        }

        if (targetIsPoint || N < 4) {
            cout << "0 0 0 0\n";
            continue;
        }

        vector<Pt> hull = convexHullStrict(pts);
        if ((int)hull.size() < 3 || !pointInConvexPolygonInclusive(hull, target)) {
            cout << "0 0 0 0\n";
            continue;
        }

        KdTree kd;
        kd.init(pts);

        bool found = false;
        array<Pt, 4> answer{};

        auto tryQuad = [&](const array<Pt, 4>& q) {
            if (found) return;
            if (candidateQuadWorks(q, target, pts, kd, answer)) found = true;
        };

        auto pickClosest = [&](int quadrant) -> bool {
            bool ok = false;
            long long best = (1LL << 62);
            Pt bestPt{};
            for (const auto& p : pts) {
                long long dx = p.x - target.x;
                long long dy = p.y - target.y;
                int q = -1;
                if (dx < 0 && dy < 0) q = 0;
                else if (dx > 0 && dy < 0) q = 1;
                else if (dx > 0 && dy > 0) q = 2;
                else if (dx < 0 && dy > 0) q = 3;
                if (q != quadrant) continue;
                long long d = dx * dx + dy * dy;
                if (!ok || d < best || (d == best && p.id < bestPt.id)) {
                    ok = true;
                    best = d;
                    bestPt = p;
                }
            }
            if (ok) {
                static array<Pt, 4> stage1;
                stage1[quadrant] = bestPt;
                return true;
            }
            return false;
        };

        array<optional<Pt>, 4> quadrantPick;
        array<long long, 4> quadrantBestDist{};
        quadrantBestDist.fill((1LL << 62));
        for (const auto& p : pts) {
            long long dx = p.x - target.x;
            long long dy = p.y - target.y;
            int q = -1;
            if (dx < 0 && dy < 0) q = 0;
            else if (dx > 0 && dy < 0) q = 1;
            else if (dx > 0 && dy > 0) q = 2;
            else if (dx < 0 && dy > 0) q = 3;
            if (q == -1) continue;
            long long d = dx * dx + dy * dy;
            if (!quadrantPick[q].has_value() || d < quadrantBestDist[q] || (d == quadrantBestDist[q] && p.id < quadrantPick[q]->id)) {
                quadrantBestDist[q] = d;
                quadrantPick[q] = p;
            }
        }
        if (quadrantPick[0] && quadrantPick[1] && quadrantPick[2] && quadrantPick[3]) {
            array<Pt, 4> q{*quadrantPick[0], *quadrantPick[1], *quadrantPick[2], *quadrantPick[3]};
            if (pointInStrictConvexQuad(q, target) && isEmptyQuad(q, pts)) {
                answer = q;
                found = true;
            }
        }

        vector<Pt> candidates;
        auto addCandidate = [&](const Pt& p) {
            for (const auto& x : candidates) {
                if (x.id == p.id) return;
            }
            candidates.push_back(p);
        };

        for (const auto& opt : quadrantPick) if (opt) addCandidate(*opt);

        const pair<long long, long long> dirs[] = {
            {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}
        };
        for (auto [vx, vy] : dirs) {
            bool ok = false;
            long long best = -(1LL << 62);
            Pt bestPt{};
            for (const auto& p : pts) {
                long long dx = p.x - target.x;
                long long dy = p.y - target.y;
                long long val = dx * vx + dy * vy;
                if (!ok || val > best || (val == best && p.id < bestPt.id)) {
                    ok = true;
                    best = val;
                    bestPt = p;
                }
            }
            if (ok) addCandidate(bestPt);
        }

        array<vector<pair<long long, Pt>>, 8> oct;
        for (const auto& p : pts) {
            long long dx = p.x - target.x;
            long long dy = p.y - target.y;
            if (dx == 0 && dy == 0) continue;
            int o = octantOf(dx, dy);
            oct[o].push_back({dx * dx + dy * dy, p});
        }
        for (int o = 0; o < 8; ++o) {
            sort(oct[o].begin(), oct[o].end(), [](const auto& a, const auto& b) {
                if (a.first != b.first) return a.first < b.first;
                return a.second.id < b.second.id;
            });
            for (int i = 0; i < (int)oct[o].size() && i < 3; ++i) addCandidate(oct[o][i].second);
        }

        sort(candidates.begin(), candidates.end(), [&](const Pt& a, const Pt& b) {
            long double aa = atan2l((long double)(a.y - target.y), (long double)(a.x - target.x));
            long double ab = atan2l((long double)(b.y - target.y), (long double)(b.x - target.x));
            if (aa < 0) aa += 2.0L * acosl(-1.0L);
            if (ab < 0) ab += 2.0L * acosl(-1.0L);
            if (aa != ab) return aa < ab;
            long long da = dist2(a, target);
            long long db = dist2(b, target);
            if (da != db) return da < db;
            return a.id < b.id;
        });

        int m = (int)candidates.size();
        for (int i = 0; i < m && !found; ++i) {
            for (int j = i + 1; j < m && !found; ++j) {
                for (int k = j + 1; k < m && !found; ++k) {
                    for (int l = k + 1; l < m && !found; ++l) {
                        array<Pt, 4> q{candidates[i], candidates[j], candidates[k], candidates[l]};
                        tryQuad(q);
                    }
                }
            }
        }

        if (found) {
            cout << answer[0].id << ' ' << answer[1].id << ' ' << answer[2].id << ' ' << answer[3].id << '\n';
        } else {
            cout << "0 0 0 0\n";
        }
    }

    return 0;
}