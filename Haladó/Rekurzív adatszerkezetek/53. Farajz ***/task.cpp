/*
Megoldási ötlet:
A fa megrajzolásánál minden részfára több, egymást nem domináló kontúr is előfordulhat. Egy kontúr mélységenként
megadja a legbaloldalibb és legjobboldalibb csúcs helyét a gyökeréhez képest. Két gyerekrészfát a lehető legkisebb
szimmetrikus eltolással rakunk egymás mellé úgy, hogy az azonos mélységű csúcsok között mindenhol legalább 2 egység
legyen a távolság. Az így keletkező kontúrokat megőrizzük, de a dominált változatokat eldobjuk.
*/
/*
Hint 1: || Egy levél kontúrja egyszerű: csak maga a gyökér. ||
Hint 2: || Két részfa csak azonos mélységen ütközhet, ezért mélységenként kell összehasonlítani a kontúrjaikat. ||
Hint 3: || Ha egy kontúr minden mélységben belül van egy másikban, akkor soha nem lesz jobb választás. ||
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int left = 0;
    int right = 0;
};

struct Profile {
    vector<int> low;
    vector<int> high;
};

string text;
int pos = 0;
vector<Node> nodes(1);

int parseTree() {
    int id = (int)nodes.size();
    nodes.push_back(Node{});
    ++pos;
    if (pos < (int)text.size() && text[pos] == '(') {
        ++pos;
        nodes[id].left = parseTree();
        ++pos;
        nodes[id].right = parseTree();
        ++pos;
    }
    return id;
}

static bool sameProfile(const Profile& a, const Profile& b) {
    return a.low == b.low && a.high == b.high;
}

static bool dominates(const Profile& a, const Profile& b) {
    if (a.low.size() != b.low.size() || a.high.size() != b.high.size()) return false;
    for (size_t i = 0; i < a.low.size(); ++i) {
        if (a.low[i] < b.low[i] || a.high[i] > b.high[i]) return false;
    }
    return true;
}

static vector<Profile> prune(vector<Profile> candidates) {
    vector<char> keep(candidates.size(), 1);
    for (size_t i = 0; i < candidates.size(); ++i) {
        if (!keep[i]) continue;
        for (size_t j = i + 1; j < candidates.size(); ++j) {
            if (!keep[j]) continue;
            if (sameProfile(candidates[i], candidates[j]) || dominates(candidates[i], candidates[j])) {
                keep[j] = 0;
            } else if (dominates(candidates[j], candidates[i])) {
                keep[i] = 0;
                break;
            }
        }
    }

    vector<Profile> result;
    result.reserve(candidates.size());
    for (size_t i = 0; i < candidates.size(); ++i) {
        if (keep[i]) result.push_back(candidates[i]);
    }
    return result;
}

static int evenCeil(int value) {
    if (value % 2 != 0) ++value;
    return value;
}

static vector<Profile> mergeProfiles(const Profile& left, const Profile& right) {
    int leftHeight = (int)left.low.size() - 1;
    int rightHeight = (int)right.low.size() - 1;
    int overlap = min(leftHeight, rightHeight);
    int shift = 0;
    for (int depth = 0; depth <= overlap; ++depth) {
        shift = max(shift, left.high[depth] - right.low[depth] + 2);
    }
    shift = evenCeil(max(shift, 2));

    vector<Profile> result;
    for (int extra = 0; extra <= 1; ++extra) {
        int offset = shift / 2 + extra;

        Profile cur;
        cur.low.assign(max(leftHeight, rightHeight) + 2, 0);
        cur.high.assign(max(leftHeight, rightHeight) + 2, 0);
        cur.low[0] = 0;
        cur.high[0] = 0;

        for (int depth = 0; depth <= max(leftHeight, rightHeight); ++depth) {
            int bestLow = 1e9;
            int bestHigh = -1e9;

            if (depth <= leftHeight) {
                bestLow = min(bestLow, left.low[depth] - offset);
                bestHigh = max(bestHigh, left.high[depth] - offset);
            }
            if (depth <= rightHeight) {
                bestLow = min(bestLow, right.low[depth] + offset);
                bestHigh = max(bestHigh, right.high[depth] + offset);
            }

            cur.low[depth + 1] = bestLow;
            cur.high[depth + 1] = bestHigh;
        }

        result.push_back(cur);
    }

    return prune(result);
}

static vector<Profile> solve(int node) {
    if (nodes[node].left == 0) {
        return {{{0}, {0}}};
    }

    vector<Profile> left = solve(nodes[node].left);
    vector<Profile> right = solve(nodes[node].right);

    vector<Profile> candidates;
    candidates.reserve(left.size() * right.size() * 2);
    for (const Profile& l : left) {
        for (const Profile& r : right) {
            vector<Profile> merged = mergeProfiles(l, r);
            candidates.insert(candidates.end(), merged.begin(), merged.end());
        }
    }

    return prune(candidates);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> text;
    pos = 0;
    nodes.reserve((int)text.size() + 1);
    int root = parseTree();

    vector<Profile> profiles = solve(root);
    int answer = 1e9;
    for (const Profile& profile : profiles) {
        int minX = 0, maxX = 0;
        for (int value : profile.low) minX = min(minX, value);
        for (int value : profile.high) maxX = max(maxX, value);
        answer = min(answer, maxX - minX);
    }

    cout << answer << '\n';
    return 0;
}