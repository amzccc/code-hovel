#include "graph.hpp"
#include <queue>
#include <set>


int maxStream(const Graph& g, Node& s, Node& t) {
    auto nodes = g.elements();
    auto table = g.table();
    int s_pos;
    int t_pos;
    vector<int> dist(nodes.size(), INT_MIN);
    vector<int> prev(nodes.size(), -1);
    for(int i = 0; i < nodes.size(); i++) {
        if(nodes[i] == s) {
            dist[i] = 0;
            s_pos = i;
        }
        else if(nodes[i] == t) {
            t_pos = i;
        }
    }
    set<int> visited;
    int max_stream{ 0 };
    while(max_stream == 0 || visited.find(t_pos) != visited.end()) {
        visited.clear();
        dist = vector<int>(nodes.size(), INT_MIN);
        prev = vector<int>(nodes.size(), -1);
        dist[s_pos] = INT_MAX;
        queue<int> q;
        q.push(s_pos);
        // dijkstra
        while(!q.empty()) {
            if(visited.find(q.front()) != visited.end()) {
                q.pop();
                continue;
            }
            int cur_stream = 0;
            for(auto& edge : table[q.front()]) {
                if(dist[edge.out] == INT_MIN) {
                    prev[edge.out] = q.front();
                    dist[edge.out] = std::min(edge.weight, dist[q.front()]);
                }
                else if(dist[edge.out] < std::min(edge.weight, dist[q.front()])) {
                    dist[edge.out] = std::min(edge.weight, dist[q.front()]);
                    prev[edge.out] = q.front();
                }
            }
            int next = table[q.front()][0].out;
            int min_dist = dist[next];
            for(size_t i = 1; i < table[q.front()].size(); i++) {
                if(min_dist > dist[table[q.front()][i].out]) {
                    next = table[q.front()][i].out;
                    min_dist = dist[next];
                }
            }
            q.push(next);
            visited.insert(q.front());
            q.pop();
        }
        // 更新图
        if(visited.find(t_pos) != visited.end()) {
            int update = t_pos;
            int cur_stream = dist[t_pos];
            while(prev[update] != -1) {
                int i = 0;
                for(; i < table[update].size(); i++) {
                    if(table[update][i].out == prev[update]) {
                        table[update][i].weight += cur_stream;
                        break;
                    }
                }
                if(i == table[update].size()) {
                    table[update].push_back({ prev[update], cur_stream });
                }
                update = prev[update];
            }
            max_stream += cur_stream;
        }
    }

    return max_stream;
}

void prim(const Graph& g, Node& s) {
    auto nodes = g.elements();
    auto table = g.table();
    vector<int> dist(nodes.size(), INT_MAX);
    vector<int> prev(nodes.size(), -1);
    vector<bool> knows(nodes.size(), false);
    int cur;
    for(int i = 0; i < nodes.size(); i++) {
        if(nodes[i] == s) {
            dist[i] = 0;
            cur = i;
            break;
        }
    }
    while(knows[cur] == false) {
        // 更新连接的顶点
        for(auto& edge : table[cur]) {
            if(dist[edge.out] > edge.weight) {
                dist[edge.out] = edge.weight;
                prev[edge.out] = cur;
            }
        }
        knows[cur] = true;
        // 寻找下一个要遍历的顶点
        cur = table[cur][0].out;
        for(int i = 0; i < nodes.size(); i++) {
            if(knows[i] == false && cur == -1 || dist[i] < dist[cur]) {
                cur = i;
            }
        }
    }
}

vector<pair<int, Edge>> kruskal(const Graph& g, Node& s) {
    vector<pair<int, Edge>> res{};
    auto table = g.table();
    priority_queue<pair<int, Edge>> pq;
    for(int i = 0; i < table.size(); i++) {
        for(auto& edge : table[i]) {
            pq.push(std::make_pair(i, edge));
        }
    }
    UnionSets union_set(table.size());
    while(pq.empty()) {
        if(union_set.find(pq.top().first) != union_set.find(pq.top().second.out)) {
            union_set.union(pq.top().first, pq.top().second.out);
            res.push_back(pq.top());
        }
        pq.pop();
    }
    return res;
}