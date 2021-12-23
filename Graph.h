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
    T1 distance;
public:
    Node<T, T1> *previous;
    Node(int id, T data) {
        this->id = id;
        this->data = data;
        previous = nullptr;
    }

    Node():Node(int(), T()){}

    Node(const Node&) = default;

    int GetID(){
        return id;
    }
    T GetData(){
        return data;
    }
    T1 GetDist(){
        return distance;
    }
    void SetDist(T1 dist){
        distance = dist;
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
        auto node = new Node<T, T1>(GetNodesCount(), data);
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
    template<class R>
    void Delete(R data, ArraySequence<R>& array){
        for(int i = 0; i < array.GetLength(); i++){
            if(array[i] == data){
                array.RemoveAt(i);
            }
        }
    }

    ArraySequence<Arc<T, T1>*> GetShortestPathByID(int start, int end){
        auto node1 = nodes[start];
        auto node2 = nodes[end];
        return GetShortestPath(node1, node2);
    }

    ArraySequence<Arc<T, T1>*> GetShortestPath(Node<T, T1>* start, Node<T, T1>* end){
        ArraySequence<Node<T, T1>*> localNodes = ArraySequence<Node<T, T1>*>(nodes);
        // Assign the shortest path collection (set)
        ArraySequence<Arc<T, T1>*> shortest = ArraySequence<Arc<T, T1>*>();
        // Assign distances of all nodes
        for(int i = 0; i < nodes.GetLength(); i++){
            if(nodes[i] == start){
                nodes[i]->SetDist(T1());
            }
            else {
                nodes[i]->SetDist(std::numeric_limits<T1>::max());
            }
        }

        while(localNodes.GetLength() > 0){
            // Find min and smallest
            T1 min = std::numeric_limits<T1>::max();
            Node<T, T1>* smallest;
            for(int i = 0; i < localNodes.GetLength(); i++){
                if(localNodes[i]->GetDist() < min){
                    min = localNodes[i]->GetDist();
                    smallest = localNodes[i];
                }
            }
            // Get adjacent nodes
            ArraySequence<Node<T, T1>*> adjacentNodes = ArraySequence<Node<T, T1>*>();
            ArraySequence<Arc<T, T1>*> adjacentArcs = smallest->GetOut();
            for(int i = 0; i < adjacentArcs.GetLength(); i++){
                adjacentNodes.Append(adjacentArcs[i]->GetEndNode());
            }

            for(int i = 0; i < adjacentNodes.GetLength(); i++){
                auto adj = adjacentNodes[i];
                T1 distance = adjacentArcs[i]->GetData() + smallest->GetDist();

                if(distance < adj->GetDist()){
                    adj->SetDist(distance);
                    adj->previous = smallest;
                }
            }
            Delete(smallest, localNodes);
        }

        // Making path
        Node<T, T1>* previous = end->previous;
        Node<T, T1>* cur = end;
        while(previous){
            auto arcsInNode = cur->GetIn();
            for(int i = 0; i < arcsInNode.GetLength(); i++){
                if(arcsInNode[i]->GetStartNode() == previous){
                    shortest.Append(arcsInNode[i]);
                    break;
                }
            }
            cur = previous;
            previous = previous->previous;
        }

        return shortest;
    }
};

// TODO: There might be zero and negative weights in Graph. FIX IT!
