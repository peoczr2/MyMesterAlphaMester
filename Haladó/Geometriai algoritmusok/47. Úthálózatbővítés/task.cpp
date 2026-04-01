/*
Megoldás: A pontok iránya szerint körbejárunk A körül. Minden élhez azt a szögintervallumot
keressük meg, amelyből A-ból nézve metszi a sugár az élt; ez az a két végponti irány közül az,
amelyik tartalmazza az él felezőirányát. A körsöprés alatt az aktív szakaszok sorrendje nem
változik két esemény között, ezért mindig elegendő a legközelebbi metszést nyilvántartani. Egy
csomópont csak akkor látható, ha a saját sugara mentén nincs nála közelebbi aktív él, és ugyanazon
az irányon csak a legközelebbi csomópont lehet jelölt.
*/

#include <bits/stdc++.h>
using namespace std;

struct Vec {
	long long x, y;
};

static inline long long cross(const Vec& a, const Vec& b) {
	return a.x * b.y - a.y * b.x;
}

static inline long long dot(const Vec& a, const Vec& b) {
	return a.x * b.x + a.y * b.y;
}

static inline int halfPlane(const Vec& a) {
	return (a.y > 0 || (a.y == 0 && a.x > 0)) ? 0 : 1;
}

static inline bool sameAngle(const Vec& a, const Vec& b) {
	return cross(a, b) == 0 && halfPlane(a) == halfPlane(b);
}

static inline bool angleLess(const Vec& a, const Vec& b) {
	int ha = halfPlane(a), hb = halfPlane(b);
	if (ha != hb) return ha < hb;
	return cross(a, b) > 0;
}

static inline bool angleLE(const Vec& a, const Vec& b) {
	return angleLess(a, b) || sameAngle(a, b);
}

static inline bool onCCWArc(const Vec& a, const Vec& b, const Vec& c) {
	if (sameAngle(a, b)) return sameAngle(a, c);
	if (angleLess(a, b)) return angleLE(a, c) && angleLE(c, b);
	return angleLE(a, c) || angleLE(c, b);
}

static inline Vec normalizeDir(Vec v) {
	long long g = std::gcd(llabs(v.x), llabs(v.y));
	if (g == 0) return {0, 0};
	v.x /= g;
	v.y /= g;
	return v;
}

struct Fraction {
	__int128 num = 0;
	__int128 den = 1;
};

static inline bool fracLess(const Fraction& a, const Fraction& b) {
	return a.num * b.den < b.num * a.den;
}

struct Segment {
	Vec p, q;
};

static Vec curDir;
static vector<Segment> segs;

static Fraction pointKey(const Vec& p) {
	Fraction f;
	f.num = (__int128)dot(p, curDir);
	f.den = (__int128)dot(curDir, curDir);
	return f;
}

static Fraction segKey(const Segment& s) {
	Vec e{ s.q.x - s.p.x, s.q.y - s.p.y };
	long long den = cross(curDir, e);
	if (den == 0) {
		long long a = dot(s.p, curDir);
		long long b = dot(s.q, curDir);
		Fraction f;
		f.num = min(a, b);
		f.den = (__int128)dot(curDir, curDir);
		return f;
	}

	Fraction f;
	f.num = cross(s.p, e);
	f.den = den;
	if (f.den < 0) {
		f.num = -f.num;
		f.den = -f.den;
	}
	return f;
}

struct SegCmp {
	bool operator()(int a, int b) const {
		if (a == b) return false;
		Fraction ka = segKey(segs[a]);
		Fraction kb = segKey(segs[b]);
		if (fracLess(ka, kb)) return true;
		if (fracLess(kb, ka)) return false;
		return a < b;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int N;
	cin >> N;

	Vec A;
	cin >> A.x >> A.y;

	vector<Vec> p(N + 1);
	vector<Vec> rel(N + 1);
	vector<Vec> dirsRaw;
	dirsRaw.reserve(N);

	for (int i = 1; i <= N; ++i) {
		cin >> p[i].x >> p[i].y;
		rel[i] = {p[i].x - A.x, p[i].y - A.y};
		dirsRaw.push_back(normalizeDir(rel[i]));
	}

	segs.assign(N, {});
	for (int i = 1; i <= N - 1; ++i) {
		int u, v;
		cin >> u >> v;
		segs[i] = {rel[u], rel[v]};
	}

	vector<Vec> dirs = dirsRaw;
	sort(dirs.begin(), dirs.end(), angleLess);
	dirs.erase(unique(dirs.begin(), dirs.end(), sameAngle), dirs.end());

	map<pair<long long, long long>, int, function<bool(const pair<long long, long long>&, const pair<long long, long long>&)>> idOf(
		[](const auto& a, const auto& b) {
			Vec va{a.first, a.second}, vb{b.first, b.second};
			return angleLess(va, vb);
		}
	);
	for (int i = 0; i < (int)dirs.size(); ++i) {
		idOf[{dirs[i].x, dirs[i].y}] = i;
	}

	int K = (int)dirs.size();
	vector<vector<int>> add(K), rem(K), verts(K);

	for (int i = 1; i <= N; ++i) {
		int g = idOf[{dirsRaw[i - 1].x, dirsRaw[i - 1].y}];
		verts[g].push_back(i);
	}

	for (int i = 1; i <= N - 1; ++i) {
		const Vec& a = segs[i].p;
		const Vec& b = segs[i].q;
		Vec da = normalizeDir(a), db = normalizeDir(b);
		int ia = idOf[{da.x, da.y}];
		int ib = idOf[{db.x, db.y}];

		Vec mid{a.x + b.x, a.y + b.y};
		int l, r;
		if (sameAngle(da, db)) {
			l = r = ia;
		} else if (onCCWArc(da, db, mid)) {
			l = ia;
			r = ib;
		} else {
			l = ib;
			r = ia;
		}

		if (l <= r) {
			add[l].push_back(i);
			rem[r].push_back(i);
		} else {
			add[l].push_back(i);
			rem[K - 1].push_back(i);
			add[0].push_back(i);
			rem[r].push_back(i);
		}
	}

	vector<char> visible(N + 1, false);
	set<int, SegCmp> active;

	for (int g = 0; g < K; ++g) {
		curDir = dirs[g];

		for (int id : add[g]) active.insert(id);

		auto& bucket = verts[g];
		sort(bucket.begin(), bucket.end(), [&](int i, int j) {
			__int128 ai = dot(rel[i], curDir);
			__int128 aj = dot(rel[j], curDir);
			if (ai != aj) return ai < aj;
			return i < j;
		});

		if (!bucket.empty()) {
			int v = bucket[0];
			Fraction pv = pointKey(rel[v]);
			bool ok = true;
			if (!active.empty()) {
				int s = *active.begin();
				Fraction ks = segKey(segs[s]);
				ok = !fracLess(ks, pv);
			}
			visible[v] = ok;
		}

		for (int id : rem[g]) active.erase(id);
	}

	vector<int> ans;
	for (int i = 1; i <= N; ++i) {
		if (visible[i]) ans.push_back(i);
	}

	cout << ans.size() << '\n';
	for (int i = 0; i < (int)ans.size(); ++i) {
		if (i) cout << ' ';
		cout << ans[i];
	}
	cout << '\n';
	return 0;
}
