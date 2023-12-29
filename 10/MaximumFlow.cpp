// #10A. Maximum Flow
/***
 * @author Yijun-Wu, UCAS
 * @date 30-Dec-2023
 *
 ***/
#include <iostream>
#include <queue>

using LL = long long;

class Isap {
  public:
    struct Edge {
        int to, next;
        LL capacity;
    } *edges_;
    struct Node {
        int depth, gap, edge, current;
    } *nodes_;
    constexpr static LL kMaxNum_ = 1LL << 50LL;
    const int kNumV_, kMaxE_, kSource_, kSink_;
    int num_edges_ = 1;

    Isap(int v, int e, int s, int t) : kNumV_(v), kMaxE_(2 * e), kSource_(s), kSink_(t) {
        edges_ = new Edge[2 * e + 2]{};
        nodes_ = new Node[v + 2]{};
    }
    void AddEdge(int from, int to, int capacity) {
        edges_[++num_edges_] = {to, nodes_[from].edge, capacity};
        nodes_[from].edge = num_edges_;
        edges_[++num_edges_] = {from, nodes_[to].edge, 0};
        nodes_[to].edge = num_edges_;
    }
    void BfsDepth() {
        for (int i = 0; i <= kNumV_; ++i) nodes_[i].depth = -1, nodes_[i].gap = 0;
        std::queue<int> to_depth({kSink_});
        nodes_[kSink_].depth = 0, nodes_[kSink_].gap = 1;
        while (!to_depth.empty()) {
            int u = to_depth.front();
            to_depth.pop();
            for (int i = nodes_[u].edge; i != 0; i = edges_[i].next)
                if (edges_[i].capacity == 0 && nodes_[edges_[i].to].depth == -1) {
                    auto k = nodes_[u].depth + 1;
                    nodes_[edges_[i].to].depth = k;
                    ++nodes_[k].gap;
                    to_depth.push(edges_[i].to);
                }
        }
    }
    LL DfsFlow(int start, LL max_flow) {
        if (start == kSink_)
            return max_flow;
        LL res_flow = 0;
        for (int i = nodes_[start].current; i != 0; nodes_[start].current = i = edges_[i].next)
            if (edges_[i].capacity > 0 && nodes_[edges_[i].to].depth + 1 == nodes_[start].depth) {
                LL flow = DfsFlow(edges_[i].to, std::min(max_flow - res_flow, edges_[i].capacity));
                edges_[i].capacity -= flow, edges_[i ^ 1].capacity += flow;
                if ((res_flow += flow) >= max_flow)
                    return res_flow;
            }
        if (--nodes_[nodes_[start].depth].gap == 0)
            nodes_[kSource_].depth = kNumV_;
        ++nodes_[start].depth;
        ++nodes_[nodes_[start].depth].gap;
        return res_flow;
    }
    LL Solve() {
        BfsDepth();
        LL max_flow = 0;
        while (nodes_[kSource_].depth < kNumV_) {
            for (int i = 0; i <= kNumV_; ++i) nodes_[i].current = nodes_[i].edge;
            max_flow += DfsFlow(kSource_, kMaxNum_);
        }
        return max_flow;
    }
};

int main() {
    int m, n, s, t;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    Isap graph(n, 2 * m, s, t);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &s, &t, &n);
        graph.AddEdge(s, t, n);
    }
    printf("%lld\n", graph.Solve());
    return 0;
}
