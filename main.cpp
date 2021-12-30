#include <iostream>
#include "ArraySequence.h"
#include "Graph.h"
#include "DiGraph.h"
#include <random>
#include <functional>

using namespace std;

const string defaultMessage = "⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⣀⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠄⠄⠄⠄\n⠄⠄⠄⠄⠄⢀⣀⣀⡀⠄⠄⠄⡠⢲⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀⠄⠄\n⠄⠄⠄⠔⣈⣀⠄⢔⡒⠳⡴⠊⠄⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⣿⣿⣧⠄⠄\n⠄⢜⡴⢑⠖⠊⢐⣤⠞⣩⡇⠄⠄⠄⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⠄⠝⠛⠋⠐\n⢸⠏⣷⠈⠄⣱⠃⠄⢠⠃⠐⡀⠄⠄⠄⠄⠙⠻⢿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠸⠄⠄⠄⠄\n⠈⣅⠞⢁⣿⢸⠘⡄⡆⠄⠄⠈⠢⡀⠄⠄⠄⠄⠄⠄⠉⠙⠛⠛⠛⠉⠉⡀⠄⠡⢀⠄⣀\n⠄⠙⡎⣹⢸⠄⠆⢘⠁⠄⠄⠄⢸⠈⠢⢄⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠃⠄⠄⠄⠄⠄\n⠄⠄⠑⢿⠈⢆⠘⢼⠄⠄⠄⠄⠸⢐⢾⠄⡘⡏⠲⠆⠠⣤⢤⢤⡤⠄⣖⡇⠄⠄⠄⠄⠄\n⣴⣶⣿⣿⣣⣈⣢⣸⠄⠄⠄⠄⡾⣷⣾⣮⣤⡏⠁⠘⠊⢠⣷⣾⡛⡟⠈⠄⠄⠄⠄⠄⠄\n⣿⣿⣿⣿⣿⠉⠒⢽⠄⠄⠄⠄⡇⣿⣟⣿⡇⠄⠄⠄⠄⢸⣻⡿⡇⡇⠄⠄⠄⠄⠄⠄⠄\n⠻⣿⣿⣿⣿⣄⠰⢼⠄⠄⠄⡄⠁⢻⣍⣯⠃⠄⠄⠄⠄⠈⢿⣻⠃⠈⡆⡄⠄⠄⠄⠄⠄\n⠄⠙⠿⠿⠛⣿⣶⣤⡇⠄⠄⢣⠄⠄⠈⠄⢠⠂⠄⠁⠄⡀⠄⠄⣀⠔⢁⠃⠄⠄⠄⠄⠄\n⠄⠄⠄⠄⠄⣿⣿⣿⣿⣾⠢⣖⣶⣦⣤⣤⣬⣤⣤⣤⣴⣶⣶⡏⠠⢃⠌⠄⠄⠄⠄⠄⠄\n⠄⠄⠄⠄⠄⠿⠿⠟⠛⡹⠉⠛⠛⠿⠿⣿⣿⣿⣿⣿⡿⠂⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄\n⠠⠤⠤⠄⠄⣀⠄⠄⠄⠑⠠⣤⣀⣀⣀⡘⣿⠿⠙⠻⡍⢀⡈⠂⠄⠄⠄⠄⠄⠄⠄⠄⠄\n⠄⠄⠄⠄⠄⠄⠑⠠⣠⣴⣾⣿⣿⣿⣿⣿⣿⣇⠉⠄⠻⣿⣷⣄⡀⠄⠄⠄⠄⠄⠄⠄⠄";


template<class R>
bool Contains(R data, ArraySequence<R> array){
    for(int i = 0; i < array.GetLength(); i++){
        if(array[i] == data){
            return true;
        }
    }
    return false;
}


void RandomGraph(){
    auto temp9 = time(nullptr);
    cout << temp9 << endl;
//    srand (1640713082);
    srand (temp9);
    int temp = rand() % 6 + 6;
    Graph<int, int> g = Graph<int, int>();
    for(int i = 0; i < temp; i++){
        int roll1 = rand() % 100;
        g.Append(roll1);
    }

    int tempr = rand() % 20 + 1;
    for(int i = 0; i < tempr; i++){
        int temp1 = rand() % g.GetNodesCount();
        if(i % g.GetNodesCount() != temp1 % g.GetNodesCount()) {
            g.BindNodesByID(i % g.GetNodesCount(), temp1 % g.GetNodesCount(), rand() % 100);
        }
    }

    auto nodes = g.GetNodes();
    for(int i = 0; i < nodes.GetLength(); i++){
        cout << nodes[i]->GetID() << " | ";
    }
    cout << "\n";

//    int id1 = ((int)nodes.GetLength()-1) / 2;
    int id1 = (int)nodes.GetLength()-1;
    cout << id1 << endl;
    ArraySequence<Arc<int, int>*> shortest;
    while(id1 > 0) {
        shortest = g.GetShortestPathByID(0, id1);
        for (int i = (int) shortest.GetLength() - 1; i >= 0; i--) {
            cout << shortest[i]->GetStartNode()->GetID() << " - " << shortest[i]->GetStartNode()->GetID() << " | ";
        }
        if (shortest.GetLength() == 0) {
            cout << "Node " << id1 << " is unreachable from node 0.\n";
            id1--;
        }
        else{
            break;
        }
    }
    cout << "\n\n";

    auto graphOutput = g.GetArcs();
    cout << "graph G{\n";
    for(int i = 0; i < graphOutput.GetLength(); i++){
        cout << graphOutput[i]->GetStartNode()->GetID() << "--" << graphOutput[i]->GetEndNode()->GetID() << "[label=" << graphOutput[i]->GetData() << "]";
        if(Contains(graphOutput[i], shortest)){
            cout << "[color=red]";
        }
        cout << "\n";
    }
    cout << "}\n\n";
}

void RandomDiGraph(){
    auto temp9 = time(nullptr);
    cout << temp9 << endl;
//    srand (1640860509);
    srand (temp9);
    int temp = rand() % 6 + 6;
    DiGraph<int, int> g = DiGraph<int, int>();
    for(int i = 0; i < temp; i++){
        int roll1 = rand() % 100;
        g.Append(roll1);
    }

    int tempr = rand() % 20 + 1;
    for(int i = 0; i < tempr; i++){
        int temp1 = rand() % g.GetDiNodesCount();
        if(i % g.GetDiNodesCount() != temp1 % g.GetDiNodesCount()) {
            g.BindDiNodesByID(i % g.GetDiNodesCount(), temp1 % g.GetDiNodesCount(), rand() % 100);
        }
    }

    auto nodes = g.GetDiNodes();
    for(int i = 0; i < nodes.GetLength(); i++){
        cout << nodes[i]->GetID() << " | ";
    }
    cout << "\n";

//    int id1 = ((int)nodes.GetLength()-1) / 2;
    int id1 = (int)nodes.GetLength()-1;
    cout << id1 << endl;
    ArraySequence<DiArc<int, int>*> shortest;
    while(id1 > 0) {
        shortest = g.GetShortestPathByID(0, id1);
        for (int i = (int) shortest.GetLength() - 1; i >= 0; i--) {
            cout << shortest[i]->GetStartDiNode()->GetID() << " - " << shortest[i]->GetEndDiNode()->GetID() << " | ";
        }
        if (shortest.GetLength() == 0) {
            cout << "Node " << id1 << " is unreachable from node 0.\n";
            id1--;
        }
        else{
            break;
        }
    }
    cout << "\n\n";

    auto graphOutput = g.GetDiArcs();
    cout << "digraph G{\n";
    for(int i = 0; i < graphOutput.GetLength(); i++){
        cout << graphOutput[i]->GetStartDiNode()->GetID() << "->" << graphOutput[i]->GetEndDiNode()->GetID() << "[label=" << graphOutput[i]->GetData() << "]";
        if(Contains(graphOutput[i], shortest)){
            cout << "[color=red]";
        }
        cout << "\n";
    }
    cout << "}\n\n";
}

int main() {
    int msg = -1;
    bool exit = false;
    while(!exit){
        cout << "Lab 3 sem 3: Graphs \nTo visualize graphs copy the output to viz.js\n1 - directed graph\n2 - undirected graph\n3 - exit\n";
        cin >> msg;
        switch(msg){
            case 1:
                RandomDiGraph();
                break;
            case 2:
                RandomGraph();
                break;
            case 3:
                exit = true;
                break;
            default:
                cout << defaultMessage << endl;
                break;
        }
    }
    return 0;
}

