#pragma once

#include "ArraySequence.h"

template <class T, typename T1>
class Arc;

template <class T, typename T1>
class Node{
private:
    int id{};
    T data;
    ArraySequence<Arc<T, T1>*> inArcs;
    ArraySequence<Arc<T, T1>*> outArcs;
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

    ArraySequence<Arc<T, T1>*> GetOut(){
        return outArcs;
    }
    ArraySequence<Arc<T, T1>*> GetIn(){
        return inArcs;
    }
    void AddInArc(Arc<T, T1>* inArc){
        inArcs.Append(inArc);
    }
    void AddOutArc(Arc<T, T1>* outArc){
        outArcs.Append(outArc);
    }
    void AddInOutArc(Arc<T, T1>* arc){
        inArcs.Append(arc);
        outArcs.Append(arc);
    }

    bool operator==(const Node<T, T1> & node){
        return id == node.GetID() && data == node.GetData();
    }
};

template <class T, typename T1>
class Arc{
private:
    int id{};
    Node<T, T1>* startNode;
    Node<T, T1>* endNode;
    T1 data;
public:
    Arc(Node<T, T1>* start, Node<T, T1>* end, T1 data, int id): startNode(start), endNode(end), data(data), id(id){}

    explicit Arc(T1 data, int id): startNode(), endNode(), data(data), id(id){}

    Arc(): Arc(T(), 0){}

    Node<T, T1>* GetStartNode() {
        return startNode;
    }
    Node<T, T1>* GetEndNode(){
        return endNode;
    }
    T1 GetData(){
        return data;
    }
    int GetID(){
        return id;
    }

    bool operator==(const Arc<T, T1>& arc){
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
    ArraySequence<Node<T, T1>*> nodes;
    ArraySequence<Arc<T, T1>*> arcs;
public:
    Graph() = default;

    Graph(std::initializer_list<T> list) : Graph(){
        for(T item : list){
            Append(item);
        }
    }

    ArraySequence<Node<T, T1>*> GetNodes(){
        return nodes;
    }
    ArraySequence<Arc<T, T1>*> GetArcs(){
        return arcs;
    }

    size_t GetNodesCount(){
        return nodes.GetLength();
    }
    size_t GetArcsCount(){
        return arcs.GetLength();
    }

    void Append(T data){
        auto node = new Node<T, T1>(data, GetNodesCount());
        AddNode(node);
    }

    void AddNode(Node<T, T1>* node){
        nodes.Append(node);
    }
    void AddArc(Arc<T, T1>* arc){
        arcs.Append(arc);
    }

    Arc<T, T1>* BindNodes(Node<T, T1>* node1, Node<T, T1>* node2, T1 weight){
        auto arc = new Arc<T, T1>(node1, node2, weight, GetArcsCount());
        node1->AddInOutArc(arc);
        node2->AddInOutArc(arc);
        AddArc(arc);
        return arc;
    }

    void BindNodesByID(int id1, int id2, T1 weight){
        auto node1 = nodes[id1];
        auto node2 = nodes[id2];
        BindNodes(node1, node2, weight);
    }

    template<class R>
    bool Contains(R data, ArraySequence<R> array){
        for(int i = 0; i < array.GetLength(); i++){
            if(array[i] == data){
                return true;
            }
        }
        return false;
    }

    ArraySequence<Arc<T, T1>*> GetShortestPath(Node<T, T1>* start, Node<T, T1>* end){
        auto unvisited = ArraySequence<Node<T, T1>*>();
        auto visited = ArraySequence<bool>();
        auto tentativeDistance = ArraySequence<T1>();
        for(int i = 0; i < nodes.GetLength(); i++){
            if(nodes[i]->id != start->id){
                unvisited.Append(nodes[i]);
                visited.Append(false);
                tentativeDistance.Append(std::numeric_limits<T1>::max());
            }
            else{
                visited.Append(true);
                tentativeDistance.Append(T1());
            }
        }

        auto current = start;
        size_t count = 0;
        while (unvisited.GetLength() >= count) {
            // Get arc that lead to neighbors
            ArraySequence<Arc<T, T1>*> neighbors = current->GetOut();
            auto unvisitedNeighbors = ArraySequence<Arc<T, T1>*>();

            // Get unvisited neighbors
            for(int i = 0; i < neighbors.GetLength(); i++){
                Node<T, T1>* neighbor = neighbors[i]->GetEndNode();
                if(!visited[neighbor->GetID()]){
                    unvisitedNeighbors.Append(neighbors[i]);
                }
            }

            // Get distance between start node and neighbor's node
            for (int i = 0; i < unvisitedNeighbors.GetLength(); i++) {
                Node<T, T1>* uNeighbor = unvisitedNeighbors[i]->GetEndNode();
                T1 dist = unvisitedNeighbors[i]->GetData() + tentativeDistance[current->GetID()];
                if (dist < tentativeDistance[uNeighbor->GetID()]) {
                    tentativeDistance[uNeighbor->GetID()] = dist;
                }
            }
            visited[current->GetID()] = true;
            if(visited[end->GetID()]){
                // Return shortest path
                break;
            }
            current = unvisited[count];
            count++;
        };
    }
};

// TODO: There might be zero and negative weights in Graph. FIX IT!
