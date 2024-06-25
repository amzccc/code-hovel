/******************************************
 * @file		graph.hpp
 * @brief		图
 * @author		cheng wentao
 * @version		v1.0.0
 * @date		2024-04-02 21:41
 ******************************************/
#ifndef GRAPH_H__
#define GRAPH_H__

#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Node {
    string name{};
    int long long id{ -1 };

    bool operator==(const Node& other) const;
};

struct Edge {
    int out{ -1 };
    int weight{ 1 };
};

class Graph {
public:
    Graph() = default;

    explicit Graph(const vector<Node>& elems);

    virtual ~Graph() = default;

    void addNode(const Node& node);

    void addNodes(const vector<Node>& nodes);

    bool buildEdge(const Node& in, const Node& out, int weight = 1);

    bool buildEdges(const Node& in, const vector<Node>& outs, const vector<int>& weights = {});

    vector<Node> elements() const;

    vector<vector<Edge>> table() const;

    vector<vector<int>> metrix() const;

    void show(ostream& os = cout) const;

    int find(const Node& node);

private:
    bool buildEdge(int in_pos, int out_pos, int weight = 0);

    bool buildEdges(int in_pos, vector<int> out_poses, const vector<int>& weights = {});



private:
    vector<Node> m_elems{};
    vector<vector<Edge>> m_table{};
};

#endif // !graph.hpp