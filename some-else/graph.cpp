#include <vector>
#include <iostream>
#include "graph.hpp"

using namespace std;
const unsigned VertexMaxSize = 100;
//邻接表法表示图

//邻接表中的链结点
struct EdgeNode {   
    char adj_node;  //邻接的顶点，顶点的关键字是char型
    int weight;     //到邻接顶点的权重
    EdgeNode* next = nullptr; //下一个结点，因为是以链表的形式，需要将所有邻接点通过链表串联起来
};

//顶点数据结构
struct Vertex {
    char data;  //顶点存储的信息
    EdgeNode *edge = nullptr; //邻接链表的头结点
};

class Graph {
public:
    Graph():vertexSize(0),edgeSize(0) {
        vertexArr = move(vector<Vertex>(100));
    } 
private:
    unsigned vertexSize;
    unsigned edgeSize; 
public:
    bool setVertexSize();
    bool setEdgeSize();
    void setVertex();
    void setEdge();
    void show();
public:
    vector<Vertex> vertexArr;
};

int main()
{
    Graph graph;
    graph.setVertexSize();
    graph.setEdgeSize();
    graph.setVertex();
    graph.setEdge();
    graph.show();

    return 0;
}

bool Graph::setVertexSize() {
    cout << "输入图的顶点数: ";
    unsigned num;
    cin >> num;
    if(num > VertexMaxSize) {
        cout << "顶点数超出范围." << endl;
        return false;
    }
    vertexSize = move(num);
    return true;
}

bool Graph::setEdgeSize() {
    cout << "输入图的边数: ";
    cin >> edgeSize;
    return true;
}

void Graph::setVertex() {
    cout << "输入顶点数据: " << endl;
    
    for(int i = 0; i < vertexSize; i++) {
        Vertex ver;
        cin >> ver.data;
        vertexArr.at(i) = move(ver);
    }
}

void Graph::setEdge() {
    cout << "输入各边(vi, vj)参数: " << endl;
    char ch[2];
    for(int i = 0; i < edgeSize; i++) {
        cin >> ch;
        for(int j = 0; j < vertexSize; j++) {
            if(vertexArr[j].data == ch[0]) {
                EdgeNode* temp = new EdgeNode;
                temp->adj_node = ch[1];
                temp->next = vertexArr[j].edge;
                vertexArr[j].edge = temp;
            }
        }
    }
}

void Graph::show() {
    for(int i = 0; i < vertexSize; i++) {
        cout << vertexArr[i].data;
        EdgeNode *ptr = vertexArr[i].edge;
        while(ptr != nullptr) {
            cout << "-";
            cout << ptr->adj_node;
            ptr = ptr->next;
        }
        cout << endl;
    }
}