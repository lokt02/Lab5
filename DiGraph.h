#pragma once

#include "ArraySequence.h"

template<class T, typename T1>
class DiGraph{
private:
    class DiArc;

    class DiNode{
    private:
        int id{};
        T data;
        ArraySequence<DiArc*> inDiArcs;
        ArraySequence<DiArc*> outDiArcs;
        T1 distance;
    public:
        DiNode *previous;
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

        ArraySequence<DiArc*> GetOut(){
            return outDiArcs;
        }
        ArraySequence<DiArc*> GetIn(){
            return inDiArcs;
        }
        ArraySequence<DiArc*> GetInOut(){
            auto temp = ArraySequence<DiArc*>(outDiArcs);
            auto temp1 = ArraySequence<DiArc*>(temp.Concat(inDiArcs));
            return temp1;
        }
        void AddInDiArc(DiArc* inDiArc){
            inDiArcs.Append(inDiArc);
        }
        void AddOutDiArc(DiArc* outDiArc){
            outDiArcs.Append(outDiArc);
        }
        void AddInOutDiArc(DiArc* Diarc){
            inDiArcs.Append(Diarc);
            outDiArcs.Append(Diarc);
        }

        bool operator==(const DiNode & Dinode){
            return id == Dinode.GetID() && data == Dinode.GetData();
        }
    };

    class DiArc{
    private:
        int id{};
        DiNode* startDiNode;
        DiNode* endDiNode;
        T1 data;
    public:
        DiArc(DiNode* start, DiNode* end, T1 data, int id): startDiNode(start), endDiNode(end), data(data), id(id){}

        explicit DiArc(T1 data, int id): startDiNode(), endDiNode(), data(data), id(id){}

        DiArc(): DiArc(T(), 0){}

        DiNode* GetStartDiNode() {
            return startDiNode;
        }
        DiNode* GetEndDiNode(){
            return endDiNode;
        }
        T1 GetData(){
            return data;
        }
        int GetID(){
            return id;
        }

        bool operator==(const DiArc& Diarc){
            return startDiNode == Diarc.GetStartDiNode() && endDiNode == Diarc.GetEndDiNode() && data == Diarc.GetData() && id == Diarc.GetID();
        }
    };

    ArraySequence<DiNode*> Dinodes;
    ArraySequence<DiArc*> Diarcs;

    void AddDiNode(DiNode* Dinode){
        Dinodes.Append(Dinode);
    }
    void AddDiArc(DiArc* Diarc){
        Diarcs.Append(Diarc);
    }

    bool DiArcExists(DiNode* Dinode1, DiNode* Dinode2){
        for(int i = 0; i < Diarcs.GetLength(); i++){
            if(Diarcs[i]->GetStartDiNode() == Dinode1 && Diarcs[i]->GetEndDiNode() == Dinode2
               || Diarcs[i]->GetStartDiNode() == Dinode2 && Diarcs[i]->GetEndDiNode() == Dinode1)
                return true;
        }
        return false;
    }
    DiArc* BindDiNodes(DiNode* Dinode1, DiNode* Dinode2, T1 weight){
        if(DiArcExists(Dinode1, Dinode2)){
            return nullptr;
        }
        auto Diarc = new DiArc(Dinode1, Dinode2, weight, GetDiArcsCount());
        Dinode1->AddOutDiArc(Diarc);
        Dinode2->AddInDiArc(Diarc);
        AddDiArc(Diarc);
        return Diarc;
    }

public:
    DiGraph() = default;

    DiGraph(std::initializer_list<T> list) : DiGraph(){
        for(T item : list){
            Append(item);
        }
    }

    ArraySequence<ArraySequence<int>> GraphOutput(){
        ArraySequence<ArraySequence<int>> res;
        for(int i = 0; i < Diarcs.GetLength(); i++){
            res.Append(ArraySequence<int>({Diarcs[i]->GetStartDiNode()->GetID(), Diarcs[i]->GetEndDiNode()->GetID(), Diarcs[i]->GetData()}));
        }
        return res;
    }

    ArraySequence<int> GetNodesIDs(){
        ArraySequence<int> res;
        for (int i = 0; i < Dinodes.GetLength(); i++) {
            res.Append(Dinodes[i]->GetID());
        }
        return res;
    }

    ArraySequence<int> GetArcsIDs(){
        ArraySequence<int> res;
        for (int i = 0; i < Diarcs.GetLength(); i++) {
            res.Append(Diarcs[i]->GetID());
        }
        return res;
    }

    ArraySequence<T> GetNodes(){
        ArraySequence<T> res;
        for (int i = 0; i < Dinodes.GetLength(); i++) {
            res.Append(Dinodes[i]->GetData());
        }
        return res;
    }

    ArraySequence<T1> GetArcs(){
        ArraySequence<T1> res;
        for (int i = 0; i < Diarcs.GetLength(); i++) {
            res.Append(Diarcs[i]->GetData());
        }
        return res;
    }

    size_t GetDiNodesCount(){
        return Dinodes.GetLength();
    }
    size_t GetDiArcsCount(){
        return Diarcs.GetLength();
    }

    void Append(T data){
        auto Dinode = new DiNode(GetDiNodesCount(), data);
        AddDiNode(Dinode);
    }

    void BindDiNodesByID(int id1, int id2, T1 weight){
        auto Dinode1 = Dinodes[id1];
        auto Dinode2 = Dinodes[id2];
        BindDiNodes(Dinode1, Dinode2, weight);
    }

    ArraySequence<ArraySequence<int>> GetShortestPathByID(int start, int end){
        auto Dinode1 = Dinodes[start];
        auto Dinode2 = Dinodes[end];
        return GetShortestPathDjikstra(Dinode1, Dinode2);
    }

private:
    ArraySequence<ArraySequence<int>> GetShortestPathDjikstra(DiNode* start, DiNode* end){
        ArraySequence<DiNode*> localDiNodes = ArraySequence<DiNode*>(Dinodes);
        // Assign the shortest path collection (set)
        ArraySequence<ArraySequence<int>> shortest = ArraySequence<ArraySequence<int>>();
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
            DiNode* smallest = nullptr;
            for(int i = 0; i < localDiNodes.GetLength(); i++){
                if(localDiNodes[i]->GetDist() < min){
                    min = localDiNodes[i]->GetDist();
                    smallest = localDiNodes[i];
                }
            }
            if(!smallest) break;
            // Get adjacent Dinodes
            ArraySequence<DiNode*> adjacentDiNodes = ArraySequence<DiNode*>();
            ArraySequence<DiArc*> adjacentDiArcs = smallest->GetOut();
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
            localDiNodes.Delete(smallest);
        }

        // Making path
        DiNode* previous = end->previous;
        DiNode* cur = end;
        while(previous){
            auto DiarcsInDiNode = cur->GetIn();
            for(int i = 0; i < DiarcsInDiNode.GetLength(); i++){
                if(DiarcsInDiNode[i]->GetStartDiNode() == previous || DiarcsInDiNode[i]->GetEndDiNode() == previous){
                    ArraySequence<int> temp1 = ArraySequence<int>({DiarcsInDiNode[i]->GetStartDiNode()->GetID(), DiarcsInDiNode[i]->GetEndDiNode()->GetID()});
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
