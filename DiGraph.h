#pragma once

#include "ArraySequence.h"

template <class T, typename T1>
class DiArc;

template <class T, typename T1>
class DiNode{
private:
    int id{};
    T data;
    ArraySequence<DiArc<T, T1>*> inDiArcs;
    ArraySequence<DiArc<T, T1>*> outDiArcs;
    T1 distance;
public:
    DiNode<T, T1> *previous;
    DiNode(int id, T data) {
        this->id = id;
        this->data = data;
        previous = nullptr;
    }

    DiNode():DiNode(int(), T()){}

    DiNode(const DiNode&) = default;

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

    ArraySequence<DiArc<T, T1>*> GetOut(){
        return outDiArcs;
    }
    ArraySequence<DiArc<T, T1>*> GetIn(){
        return inDiArcs;
    }
    ArraySequence<DiArc<T, T1>*> GetInOut(){
        auto temp = ArraySequence<DiArc<T, T1>*>(outDiArcs);
        auto temp1 = ArraySequence<DiArc<T, T1>*>(temp.Concat(inDiArcs));
        return temp1;
    }
    void AddInDiArc(DiArc<T, T1>* inDiArc){
        inDiArcs.Append(inDiArc);
    }
    void AddOutDiArc(DiArc<T, T1>* outDiArc){
        outDiArcs.Append(outDiArc);
    }
    void AddInOutDiArc(DiArc<T, T1>* Diarc){
        inDiArcs.Append(Diarc);
        outDiArcs.Append(Diarc);
    }

    bool operator==(const DiNode<T, T1> & Dinode){
        return id == Dinode.GetID() && data == Dinode.GetData();
    }
};

template <class T, typename T1>
class DiArc{
private:
    int id{};
    DiNode<T, T1>* startDiNode;
    DiNode<T, T1>* endDiNode;
    T1 data;
public:
    DiArc(DiNode<T, T1>* start, DiNode<T, T1>* end, T1 data, int id): startDiNode(start), endDiNode(end), data(data), id(id){}

    explicit DiArc(T1 data, int id): startDiNode(), endDiNode(), data(data), id(id){}

    DiArc(): DiArc(T(), 0){}

    DiNode<T, T1>* GetStartDiNode() {
        return startDiNode;
    }
    DiNode<T, T1>* GetEndDiNode(){
        return endDiNode;
    }
    T1 GetData(){
        return data;
    }
    int GetID(){
        return id;
    }

    bool operator==(const DiArc<T, T1>& Diarc){
        return startDiNode == Diarc.GetStartDiNode() && endDiNode == Diarc.GetEndDiNode() && data == Diarc.GetData() && id == Diarc.GetID();
    }
};

template<class T, typename T1>
class DiGraph{
private:
    ArraySequence<DiNode<T, T1>*> Dinodes;
    ArraySequence<DiArc<T, T1>*> Diarcs;

    void AddDiNode(DiNode<T, T1>* Dinode){
        Dinodes.Append(Dinode);
    }
    void AddDiArc(DiArc<T, T1>* Diarc){
        Diarcs.Append(Diarc);
    }

    bool DiArcExists(DiNode<T, T1>* Dinode1, DiNode<T, T1>* Dinode2){
        for(int i = 0; i < Diarcs.GetLength(); i++){
            if(Diarcs[i]->GetStartDiNode() == Dinode1 && Diarcs[i]->GetEndDiNode() == Dinode2
               || Diarcs[i]->GetStartDiNode() == Dinode2 && Diarcs[i]->GetEndDiNode() == Dinode1)
                return true;
        }
        return false;
    }
    DiArc<T, T1>* BindDiNodes(DiNode<T, T1>* Dinode1, DiNode<T, T1>* Dinode2, T1 weight){
        if(DiArcExists(Dinode1, Dinode2)){
            return nullptr;
        }
        auto Diarc = new DiArc<T, T1>(Dinode1, Dinode2, weight, GetDiArcsCount());
        Dinode1->AddOutDiArc(Diarc);
        Dinode2->AddInDiArc(Diarc);
        AddDiArc(Diarc);
        return Diarc;
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
                return;
            }
        }
        std::runtime_error("There is no such element in this array");
    }

public:
    DiGraph() = default;

    DiGraph(std::initializer_list<T> list) : DiGraph(){
        for(T item : list){
            Append(item);
        }
    }

    ArraySequence<DiNode<T, T1>*> GetDiNodes(){
        return Dinodes;
    }
    ArraySequence<DiArc<T, T1>*> GetDiArcs(){
        return Diarcs;
    }

    size_t GetDiNodesCount(){
        return Dinodes.GetLength();
    }
    size_t GetDiArcsCount(){
        return Diarcs.GetLength();
    }

    void Append(T data){
        auto Dinode = new DiNode<T, T1>(GetDiNodesCount(), data);
        AddDiNode(Dinode);
    }

    void BindDiNodesByID(int id1, int id2, T1 weight){
        auto Dinode1 = Dinodes[id1];
        auto Dinode2 = Dinodes[id2];
        BindDiNodes(Dinode1, Dinode2, weight);
    }

    ArraySequence<DiArc<T, T1>*> GetShortestPathByID(int start, int end){
        auto Dinode1 = Dinodes[start];
        auto Dinode2 = Dinodes[end];
        return GetShortestPathDjikstra(Dinode1, Dinode2);
    }

private:
    ArraySequence<DiArc<T, T1>*> GetShortestPathDjikstra(DiNode<T, T1>* start, DiNode<T, T1>* end){
        ArraySequence<DiNode<T, T1>*> localDiNodes = ArraySequence<DiNode<T, T1>*>(Dinodes);
        // Assign the shortest path collection (set)
        ArraySequence<DiArc<T, T1>*> shortest = ArraySequence<DiArc<T, T1>*>();
        // Assign distances of all Dinodes
        for(int i = 0; i < localDiNodes.GetLength(); i++){
            if(localDiNodes[i] == start){
                localDiNodes[i]->SetDist(T1());
            }
            else {
                localDiNodes[i]->SetDist(std::numeric_limits<T1>::max());
            }
        }

        while(localDiNodes.GetLength() > 0){
            // Find min and smallest
            T1 min = std::numeric_limits<T1>::max();
            DiNode<T, T1>* smallest = nullptr;
            for(int i = 0; i < localDiNodes.GetLength(); i++){
                if(localDiNodes[i]->GetDist() < min){
                    min = localDiNodes[i]->GetDist();
                    smallest = localDiNodes[i];
                }
            }
            if(!smallest) break;
            // Get adjacent Dinodes
            ArraySequence<DiNode<T, T1>*> adjacentDiNodes = ArraySequence<DiNode<T, T1>*>();
            ArraySequence<DiArc<T, T1>*> adjacentDiArcs = smallest->GetOut();
            for(int i = 0; i < adjacentDiArcs.GetLength(); i++){
                if(smallest != adjacentDiArcs[i]->GetEndDiNode()) {
                    adjacentDiNodes.Append(adjacentDiArcs[i]->GetEndDiNode());
                }
//                else {
//                    if(smallest != adjacentDiArcs[i]->GetStartDiNode())
//                        adjacentDiNodes.Append(adjacentDiArcs[i]->GetStartDiNode());
//                }
            }

            for(int i = 0; i < adjacentDiNodes.GetLength(); i++){
                auto adj = adjacentDiNodes[i];
                T1 distance = adjacentDiArcs[i]->GetData() + smallest->GetDist();

                if(distance < adj->GetDist()){
                    adj->SetDist(distance);
                    adj->previous = smallest;
                }
            }
            Delete(smallest, localDiNodes);
        }

        // Making path
        DiNode<T, T1>* previous = end->previous;
        DiNode<T, T1>* cur = end;
        while(previous){
            auto DiarcsInDiNode = cur->GetIn();
            for(int i = 0; i < DiarcsInDiNode.GetLength(); i++){
                if(DiarcsInDiNode[i]->GetStartDiNode() == previous || DiarcsInDiNode[i]->GetEndDiNode() == previous){
                    shortest.Append(DiarcsInDiNode[i]);
                    break;
                }
            }
            cur = previous;
            previous = previous->previous;
        }

        return shortest;
    }
};
