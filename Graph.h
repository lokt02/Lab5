#pragma once

#include "ArraySequence.h"
template<class T, typename T1>
class Graph{
private:
    class Arc;

    class Node{
    private:
        int id{};
        T data;
        ArraySequence<Arc*> inArcs;
        ArraySequence<Arc*> outArcs;
        T1 distance;
    public:
        Node *previous;
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

        ArraySequence<Arc*> GetOut(){
            return outArcs;
        }
        ArraySequence<Arc*> GetIn(){
            return inArcs;
        }
        ArraySequence<Arc*> GetInOut(){
            auto temp = ArraySequence<Arc*>(outArcs);
            auto temp1 = ArraySequence<Arc*>(temp.Concat(inArcs));
            return temp1;
        }
        void AddInArc(Arc* inArc){
            inArcs.Append(inArc);
        }
        void AddOutArc(Arc* outArc){
            outArcs.Append(outArc);
        }
        void AddInOutArc(Arc* arc){
            inArcs.Append(arc);
            outArcs.Append(arc);
        }

        bool operator==(const Node & node){
            return id == node.GetID() && data == node.GetData();
        }
    };

    class Arc{
    private:
        int id{};
        Node* startNode;
        Node* endNode;
        T1 data;
    public:
        Arc(Node* start, Node* end, T1 data, int id): startNode(start), endNode(end), data(data), id(id){}

        explicit Arc(T1 data, int id): startNode(), endNode(), data(data), id(id){}

        Arc(): Arc(T(), 0){}

        Node* GetStartNode() {
            return startNode;
        }
        Node* GetEndNode(){
            return endNode;
        }
        T1 GetData(){
            return data;
        }
        int GetID(){
            return id;
        }

        bool operator==(const Arc& arc){
            return startNode == arc.GetStartNode() && endNode == arc.GetEndNode() && data == arc.GetData() && id == arc.GetID();
        }
    };

    ArraySequence<Node*> nodes;
    ArraySequence<Arc*> arcs;

    void AddNode(Node* node){
        nodes.Append(node);
    }
    void AddArc(Arc* arc){
        arcs.Append(arc);
    }

    Arc* BindNodes(Node* node1, Node* node2, T1 weight){
        if(ArcExists(node1, node2)){
            return nullptr;
        }
        auto arc = new Arc(node1, node2, weight, GetArcsCount());
        node1->AddInOutArc(arc);
        node2->AddInOutArc(arc);
        AddArc(arc);
        return arc;
    }

    bool ArcExists(Node* node1, Node* node2){
        for(int i = 0; i < arcs.GetLength(); i++){
            if(arcs[i]->GetStartNode() == node1 && arcs[i]->GetEndNode() == node2
               || arcs[i]->GetStartNode() == node2 && arcs[i]->GetEndNode() == node1)
                return true;
        }
        return false;
    }
public:
    Graph() = default;

    Graph(std::initializer_list<T> list) : Graph(){
        for(T item : list){
            Append(item);
        }
    }

    ArraySequence<ArraySequence<int>> GraphOutput(){
        ArraySequence<ArraySequence<int>> res;
        for(int i = 0; i < arcs.GetLength(); i++){
            res.Append(ArraySequence<int>({arcs[i]->GetStartNode()->GetID(), arcs[i]->GetEndNode()->GetID(), arcs[i]->GetData()}));
        }
        return res;
    }

    ArraySequence<int> GetNodesIDs(){
        ArraySequence<int> res;
        for (int i = 0; i < nodes.GetLength(); i++) {
            res.Append(nodes[i]->GetID());
        }
        return res;
    }

    ArraySequence<int> GetArcsIDs(){
        ArraySequence<int> res;
        for (int i = 0; i < arcs.GetLength(); i++) {
            res.Append(arcs[i]->GetID());
        }
        return res;
    }

    ArraySequence<T> GetNodes(){
        ArraySequence<T> res;
        for (int i = 0; i < nodes.GetLength(); i++) {
            res.Append(nodes[i]->GetData());
        }
        return res;
    }

    ArraySequence<T1> GetArcs(){
        ArraySequence<T1> res;
        for (int i = 0; i < arcs.GetLength(); i++) {
            res.Append(arcs[i]->GetData());
        }
        return res;
    }

    size_t GetNodesCount(){
        return nodes.GetLength();
    }
    size_t GetArcsCount(){
        return arcs.GetLength();
    }

    void Append(T data){
        auto node = new Node(GetNodesCount(), data);
        AddNode(node);
    }

    void BindNodesByID(int id1, int id2, T1 weight){
        auto node1 = nodes[id1];
        auto node2 = nodes[id2];
        BindNodes(node1, node2, weight);
    }

    ArraySequence<ArraySequence<int>> GetShortestPathByID(int start, int end){
        auto node1 = nodes[start];
        auto node2 = nodes[end];
        return GetShortestPathDjikstra(node1, node2);
    }

private:
    ArraySequence<ArraySequence<int>> GetShortestPathDjikstra(Node* start, Node* end){
        ArraySequence<Node*> localNodes = ArraySequence<Node*>(nodes);
        // Assign the shortest path collection (set)
        ArraySequence<ArraySequence<int>> shortest = ArraySequence<ArraySequence<int>>();
        // Assign distances of all nodes
        for(int i = 0; i < localNodes.GetLength(); i++){
            if(localNodes[i] == start){
                localNodes[i]->SetDist(T1());
            }
            else {
                localNodes[i]->SetDist(std::numeric_limits<T1>::max());
            }
        }

        while(localNodes.GetLength() > 0){
            // Find min and smallest
            T1 min = std::numeric_limits<T1>::max();
            Node* smallest = nullptr;
            for(int i = 0; i < localNodes.GetLength(); i++){
                if(localNodes[i]->GetDist() < min){
                    min = localNodes[i]->GetDist();
                    smallest = localNodes[i];
                }
            }
            if(!smallest) break;
            // Get adjacent nodes
            ArraySequence<Node*> adjacentNodes = ArraySequence<Node*>();
            ArraySequence<Arc*> adjacentArcs = smallest->GetInOut();
            for(int i = 0; i < adjacentArcs.GetLength(); i++){
                if(smallest != adjacentArcs[i]->GetEndNode()) {
                    adjacentNodes.Append(adjacentArcs[i]->GetEndNode());
                }
                else {
                    if(smallest != adjacentArcs[i]->GetStartNode())
                        adjacentNodes.Append(adjacentArcs[i]->GetStartNode());
                }
            }

            for(int i = 0; i < adjacentNodes.GetLength(); i++){
                auto adj = adjacentNodes[i];
                T1 distance = adjacentArcs[i]->GetData() + smallest->GetDist();

                if(distance < adj->GetDist()){
                    adj->SetDist(distance);
                    adj->previous = smallest;
                }
            }
            localNodes.Delete(smallest);
        }

        // Making path
        Node* previous = end->previous;
        Node* cur = end;
        while(previous){
            auto arcsInNode = cur->GetInOut();
            for(int i = 0; i < arcsInNode.GetLength(); i++){
                if(arcsInNode[i]->GetStartNode() == previous || arcsInNode[i]->GetEndNode() == previous){
                    ArraySequence<int> temp1 = ArraySequence<int>({arcsInNode[i]->GetStartNode()->GetID(), arcsInNode[i]->GetEndNode()->GetID()});
                    shortest.Append(temp1);
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
// ПОЧИНИТЬ РАНДОМ: СОЗДАВАТЬ ТОЛЬКО "ИНТЕРЕСНЫЕ ГРАФЫ"
