/*
Minden megrendeles egyetlen ulohelyet kaphat az [A, A + D] intervallumbol, minden ulohely pedig
legfeljebb egy megrendelohoz rendelheto. Ez tehat maximum bevetelu parositas a megrendelesek es
az ulohelyek kozott, ahol egy megrendeles szomszedsaga egy folytonos intervallum. A megrendeles-
ulohely elereseket szegmensfaval tomoritjuk: egy megrendeles nem minden ulohelyhez kulon kap elet,
hanem csak az intervallumat fedo O(log N) szegmensfa-csomoponthoz. Erre a halora minimumkoltsegu
maximumfolyamot futtatunk, ahol a nyereseg negativ koltsegkent jelenik meg. A vegso folyam szerint
visszakeresheto, melyik nyertes megrendeles melyik konkret ulohelyet kapta.
*/
/*
Hint 1: || Egy megrendeles pontosan egy ulohelyet valaszt az [A, A + D] intervallumbol. ||
Hint 2: || Ez sulyozott bipartit parositas, csak az ulohely-oldali szomszedsag intervallumos. ||
Hint 3: || Szegmensfaval egy intervallum O(log N) csomopontra bonthato, igy a halo sokkal kisebb lesz. ||
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int to;
    int cap;
    int cost;
};

class MinCostFlow {
public:
    explicit MinCostFlow(int node_count) : graph(node_count) {}

    int add_edge(int from, int to, int cap, int cost) {
        int index = static_cast<int>(edges.size());
        edges.push_back({to, cap, cost});
        graph[from].push_back(index);
        edges.push_back({from, 0, -cost});
        graph[to].push_back(index ^ 1);
        return index;
    }

    pair<int, long long> min_cost_max_flow(int source, int sink) {
        const long long inf = numeric_limits<long long>::max() / 4;
        vector<long long> potential(graph.size(), inf);
        vector<int> in_queue(graph.size(), false);
        queue<int> pending;
        potential[source] = 0;
        pending.push(source);
        in_queue[source] = true;

        while (!pending.empty()) {
            int node = pending.front();
            pending.pop();
            in_queue[node] = false;
            for (int edge_index : graph[node]) {
                const Edge& edge = edges[edge_index];
                if (edge.cap == 0) {
                    continue;
                }
                if (potential[node] + edge.cost < potential[edge.to]) {
                    potential[edge.to] = potential[node] + edge.cost;
                    if (!in_queue[edge.to]) {
                        in_queue[edge.to] = true;
                        pending.push(edge.to);
                    }
                }
            }
        }

        for (long long& value : potential) {
            if (value == inf) {
                value = 0;
            }
        }

        int flow = 0;
        long long cost = 0;
        while (true) {
            vector<long long> distance(graph.size(), inf);
            vector<int> parent_edge(graph.size(), -1);
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
            distance[source] = 0;
            pq.push({0, source});

            while (!pq.empty()) {
                auto [dist, node] = pq.top();
                pq.pop();
                if (dist != distance[node]) {
                    continue;
                }
                for (int edge_index : graph[node]) {
                    const Edge& edge = edges[edge_index];
                    if (edge.cap == 0) {
                        continue;
                    }
                    long long reduced = edge.cost + potential[node] - potential[edge.to];
                    if (dist + reduced < distance[edge.to]) {
                        distance[edge.to] = dist + reduced;
                        parent_edge[edge.to] = edge_index;
                        pq.push({distance[edge.to], edge.to});
                    }
                }
            }

            if (parent_edge[sink] == -1) {
                break;
            }

            long long path_cost = distance[sink] + potential[sink] - potential[source];
            if (path_cost >= 0) {
                break;
            }

            for (int node = 0; node < static_cast<int>(graph.size()); ++node) {
                if (distance[node] < inf) {
                    potential[node] += distance[node];
                }
            }

            int add = 1;
            for (int node = sink; node != source; node = edges[parent_edge[node] ^ 1].to) {
                add = min(add, edges[parent_edge[node]].cap);
            }

            for (int node = sink; node != source; node = edges[parent_edge[node] ^ 1].to) {
                int edge_index = parent_edge[node];
                edges[edge_index].cap -= add;
                edges[edge_index ^ 1].cap += add;
            }

            flow += add;
            cost += path_cost * add;
        }

        return {flow, cost};
    }

    vector<vector<int>> graph;
    vector<Edge> edges;
};

struct Order {
    int left;
    int right;
    int fee;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int seat_count, order_count, max_shift;
    cin >> seat_count >> order_count >> max_shift;

    vector<Order> orders(order_count + 1);
    for (int i = 1; i <= order_count; ++i) {
        cin >> orders[i].left >> orders[i].fee;
        orders[i].right = min(seat_count, orders[i].left + max_shift);
    }

    int source = 0;
    int sink = 1;
    int next_node = 2;
    vector<int> order_node(order_count + 1, -1);
    for (int i = 1; i <= order_count; ++i) {
        order_node[i] = next_node++;
    }

    int tree_base = next_node;
    int tree_size = 4 * max(1, seat_count);
    next_node += tree_size;
    MinCostFlow network(next_node);

    vector<int> left_edge(next_node, -1);
    vector<int> right_edge(next_node, -1);
    vector<int> seat_of_node(next_node, -1);
    vector<int> sink_edge(next_node, -1);

    auto tree_node = [&](int index) {
        return tree_base + index;
    };

    auto build_tree = [&](auto&& self, int index, int left, int right) -> void {
        int node = tree_node(index);
        if (left == right) {
            seat_of_node[node] = left;
            sink_edge[node] = network.add_edge(node, sink, 1, 0);
            return;
        }
        int middle = (left + right) / 2;
        int left_child = tree_node(index * 2);
        int right_child = tree_node(index * 2 + 1);
        self(self, index * 2, left, middle);
        self(self, index * 2 + 1, middle + 1, right);
        left_edge[node] = network.add_edge(node, left_child, middle - left + 1, 0);
        right_edge[node] = network.add_edge(node, right_child, right - middle, 0);
    };
    build_tree(build_tree, 1, 1, seat_count);

    vector<vector<int>> order_edges(order_count + 1);
    auto add_interval = [&](auto&& self, int order_id, int index, int left, int right, int query_left, int query_right) -> void {
        if (query_right < left || right < query_left) {
            return;
        }
        if (query_left <= left && right <= query_right) {
            int edge_index = network.add_edge(order_node[order_id], tree_node(index), 1, 0);
            order_edges[order_id].push_back(edge_index);
            return;
        }
        int middle = (left + right) / 2;
        self(self, order_id, index * 2, left, middle, query_left, query_right);
        self(self, order_id, index * 2 + 1, middle + 1, right, query_left, query_right);
    };

    vector<int> source_edge(order_count + 1, -1);
    for (int i = 1; i <= order_count; ++i) {
        source_edge[i] = network.add_edge(source, order_node[i], 1, -orders[i].fee);
        add_interval(add_interval, i, 1, 1, seat_count, orders[i].left, orders[i].right);
    }

    auto result = network.min_cost_max_flow(source, sink);
    long long revenue = -result.second;

    auto extract_seat = [&](auto&& self, int node) -> int {
        if (seat_of_node[node] != -1) {
            int edge_index = sink_edge[node];
            network.edges[edge_index ^ 1].cap -= 1;
            network.edges[edge_index].cap += 1;
            return seat_of_node[node];
        }
        for (int edge_index : {left_edge[node], right_edge[node]}) {
            if (edge_index != -1 && network.edges[edge_index ^ 1].cap > 0) {
                network.edges[edge_index ^ 1].cap -= 1;
                network.edges[edge_index].cap += 1;
                return self(self, network.edges[edge_index].to);
            }
        }
        return -1;
    };

    vector<pair<int, int>> assignment;
    for (int i = 1; i <= order_count; ++i) {
        if (network.edges[source_edge[i]].cap != 0) {
            continue;
        }
        int start_node = -1;
        for (int edge_index : order_edges[i]) {
            if (network.edges[edge_index].cap == 0) {
                start_node = network.edges[edge_index].to;
                break;
            }
        }
        int seat = extract_seat(extract_seat, start_node);
        assignment.push_back({i, seat});
    }

    cout << revenue << '\n';
    cout << assignment.size() << '\n';
    for (const auto& [order_id, seat] : assignment) {
        cout << order_id << ' ' << seat << '\n';
    }
    return 0;
}