#include "graph.hpp"
#include <algorithm>


Graph::Graph(const vector<Node>& elems)
    : m_elems(elems) { }

void Graph::addNode(const Node& node) {
    if(find(node) != -1) {
        return;
    }
    m_elems.push_back(node);
    m_table.emplace_back();
}

void Graph::addNodes(const vector<Node>& nodes) {
    for(auto& node : nodes) {
        if(find(node) != -1) {
            continue;
        }
        m_elems.push_back(node);
    }
    m_table.resize(m_table.size() + nodes.size());
}

bool Graph::buildEdge(const Node& in, const Node& out, int weight = 1) {
    if(in == out) {
        return false;
    }
    return buildEdge(find(in), find(out), weight);
}

bool Graph::buildEdges(const Node& in, const vector<Node>& outs, const vector<int>& weights) {
    if(std::find(outs.begin(), outs.end(), in) != outs.end()) {
        return false;
    }
    vector<int> out_poses;
    for(auto& out : outs) {
        out_poses.push_back(find(out));
        if(out_poses.back() == -1) {
            return false;
        }
    }
    return buildEdges(find(in), out_poses, weights);
}

vector<Node> Graph::elements() const {
    return m_elems;
}

vector<vector<Edge>> Graph::table() const {
    return m_table;
}

vector<vector<int>> Graph::metrix() const {
    vector<vector<int>> m(m_table.size(), vector<int>(m_table.size(), -1));
    for(size_t i = 0; i < m_table.size(); i++) {
        m[i][i] = 0;
        for(auto& edge : m_table[i]) {
            m[i][edge.out] = edge.weight;
        }
    }
}

void Graph::show(ostream& os) const {
    for(auto& elem : m_elems) {
        os << elem.id << '\t';
    }
    os << '\n';
    auto iter = m_elems.begin();
    auto m = metrix();
    for(auto& row : m) {
        if(iter != m_elems.end()) {
            os << iter->id << '\t';
        }
        for(auto col : row) {
            os << col << '\t';
        }
        os << '\n';
    }
}

int Graph::find(const Node& node) {
    for(size_t i = 0; i < m_elems.size(); i++) {
        if(m_elems[i] == node) {
            return i;
        }
    }
    return -1;
}

bool Graph::buildEdge(int in_pos, int out_pos, int weight = 1) {
    if(in_pos == -1 || out_pos == -1) {
        return false;
    }
    for(auto& edge : m_table[in_pos]) {
        if(edge.out == out_pos) {
            return false;
        }
    }
    m_table[in_pos].push_back({ out_pos, weight });
    return true;
}

bool Graph::buildEdges(int in_pos, vector<int> out_poses, const vector<int>& weights) {
    if(in_pos == -1) {
        return false;
    }
    vector<Edge> edges;
    edges.reserve(out_poses.size());
    for(size_t i = 0; i < out_poses.size(); i++) {
        if(std::find_if(m_table[in_pos].begin(), m_table[in_pos].end(), [i, &out_poses](const Edge& edge) {
            return  out_poses[i] == edge.out;
        }) != m_table[in_pos].end()) {
            return false;
        }
        edges.emplace_back(out_poses[i], i < weights.size() ? weights[i] : 1);
    }
    for(auto& edge : edges) {
        m_table[in_pos].emplace_back(edge);
    }
    return true;
}

bool Node::operator==(const Node& other) const {
    return id == other.id;
}
