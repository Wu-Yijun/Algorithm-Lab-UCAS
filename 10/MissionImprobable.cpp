// #10B. Mission Improbable (optional)
/***
 * @author Yijun-Wu, UCAS
 * @date 12-Dec-2023
 *
 ***/
#include <algorithm>
#include <iostream>
#include <queue>

using LL = long long;

template <typename T>
void read(T& x);

class Isap {
  public:
    struct Edge {
        int to, next;
        LL capacity;
    }* edges_;
    struct Node {
        int depth, gap, edge, current;
    }* nodes_;
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

constexpr int kRowMax = 110;
constexpr int kColMax = 110;
constexpr int kMaxInt = 1000000010;
int mat[kRowMax][kColMax];

int main() {
    LL total_num = 0, solved_num = 0;
    // 每一行最大，每一列最大
    int rowMax[kRowMax] = {}, colMax[kColMax] = {};
    int r, c, used_count = 0;
    read(r), read(c);
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j) {
            int num;
            read(num);
            rowMax[i] = std::max(rowMax[i], num);
            colMax[j] = std::max(colMax[j], num);
            total_num += num;
            if (num != 0)
                mat[i][j] = 1, ++used_count;
        }
    int id_row[kRowMax], id_col[kColMax];
    int cap_r[kRowMax], cap_c[kColMax];
    for (int i = 0; i < kRowMax; ++i) id_row[i] = i;
    for (int i = 0; i < kColMax; ++i) id_col[i] = i;
    std::sort(id_row, id_row + r, [rowMax](int a, int b) { return rowMax[a] > rowMax[b]; });
    std::sort(id_col, id_col + c, [colMax](int a, int b) { return colMax[a] > colMax[b]; });
    int current = kMaxInt, idex_r = 0, idex_c = 0, cap = 0;
    while (idex_r < r || idex_c < c) {
        current = std::max(rowMax[id_row[idex_r]], colMax[id_col[idex_c]]);
        if (current == 0)
            break;
        int num1 = 0, num2 = 0;
        while (num1 + idex_r < r && rowMax[id_row[num1 + idex_r]] == current) ++num1;
        while (num2 + idex_c < c && colMax[id_col[num2 + idex_c]] == current) ++num2;
        if (num1 == 0 || num2 == 0) {
            cap = num1 + num2;
            idex_r += num1, idex_c += num2;
            solved_num += (LL)current * cap;
            used_count -= cap;
            if (idex_r >= r && idex_c >= c)
                break;
            continue;
        }
        const int s = num1 + num2, t = s + 1;
        Isap graph(t + 1, s + num1 * num2, s, t);
        for (int i = 0; i < num1; ++i) cap_r[i] = -1;
        for (int i = 0; i < num2; ++i) cap_c[i] = -1;
        cap = 0;
        for (int i = 0; i < num1; ++i)
            for (int j = 0; j < num2; ++j)
                if (mat[id_row[i + idex_r]][id_col[j + idex_c]] != 0) {
                    graph.AddEdge(i, j + num1, 1);
                    ++cap_r[i];
                    ++cap_c[j];
                    ++cap;
                }
        for (int i = 0; i < num1; ++i)
            if (cap_r[i] > 0)
                graph.AddEdge(s, i, cap_r[i]);
            else if (cap_r[i] == -1)  // 需要在别的地方额外安排一个
                ++cap;
        for (int i = 0; i < num2; ++i)
            if (cap_c[i] > 0)
                graph.AddEdge(i + num1, t, cap_c[i]);
            else if (cap_c[i] == -1)  // 需要在别的地方额外安排一个
                ++cap;
        cap -= graph.Solve();
        idex_r += num1, idex_c += num2;
        solved_num += (LL)current * cap;
        used_count -= cap;
    }
    solved_num += used_count;
    printf("%lld\n", total_num - solved_num);
    return 0;
}

template <typename T>
void read(T& x) {
    x = 0;
    T f = 1;
    char ch = ' ';
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    x = x * f;
}
