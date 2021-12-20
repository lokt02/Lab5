#pragma once

#include "ArraySequence.h"

template <class T>
class Arc;

template <class T>
class Node{
private:
    int id{};
    T data;
    ArraySequence<Arc<T>*> inArcs;
    ArraySequence<Arc<T>*> outArcs;
public:
    Node(int id, T data) {
        this->id = id;
        this->data = data;
    }

    Node():Node(int(), T()){}

    Node(const Node&) = default;

    int GetID(){
        return id;
    }
    T GetData(){
        return data;
    }

    bool operator==(const Node<T> & node){
        return id == node.GetID() && data == node.GetData();
    }
};

template <class T>
class Arc{
private:
    int id{};
    Node<T>* startNode;
    Node<T>* endNode;
    T data;
public:
    Arc(Node<T>* start, Node<T>* end, T data, int id): startNode(start), endNode(end), data(data), id(id){}

    explicit Arc(T data, int id): startNode(), endNode(), data(data), id(id){}

    Arc(): Arc(T(), 0){}

    Node<T>* GetStartNode() {
        return startNode;
    }
    Node<T>* GetEndNode(){
        return endNode;
    }
    T GetData(){
        return data;
    }
    int GetID(){
        return id;
    }

    bool operator==(const Arc<T>& arc){
        return startNode == arc.GetStartNode() && endNode == arc.GetEndNode() && data == arc.GetData() && id == arc.GetID();
    }
};

//template<class T>
//class Path{
//private:
//    ArraySequence<Arc<T>> arcs;
//public:
//    ArraySequence<Arc<T>> GetArcs(){
//        return arcs;
//    }
//};

template<class T, typename T1>
class Graph{
private:
    ArraySequence<Node<T>> nodes;
    ArraySequence<Arc<T1>> arcs;
public:
    Graph() = default;
    ArraySequence<Node<T>> GetNodes(){
        return nodes;
    }
    ArraySequence<Arc<T1>> GetArcs(){
        return arcs;
    }

    size_t GetNodesCount(){
        return nodes.GetLength();
    }
    size_t GetArcsCount(){
        return arcs.GetLength();
    }

    void Append(T data){
        Node<T> node = Node<T>(data, GetNodesCount() - 1);
        AddNode(node);
    }

    void AddNode(Node<T> node){
        nodes.Append(node);
    }
    void AddArc(Arc<T1> arc){
        arcs.Append(arc);
    }

    Arc<T1> BindNodes(Node<T>* node1, Node<T>* node2, T1 weight){
        auto arc = Arc<T1>(node1, node2, weight, GetArcsCount() - 1);
        return arc;
    }
};
