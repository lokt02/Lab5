#include <iostream>
#include "Cache.h"
#include "Person.h"
#include "Indexes.h"
#include "Dictionary.h"
#include "ArraySequence.h"
#include <random>
#include <chrono>

using namespace std;

const string defaultMessage = "⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⣀⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠄⠄⠄⠄\n⠄⠄⠄⠄⠄⢀⣀⣀⡀⠄⠄⠄⡠⢲⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀⠄⠄\n⠄⠄⠄⠔⣈⣀⠄⢔⡒⠳⡴⠊⠄⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⣿⣿⣧⠄⠄\n⠄⢜⡴⢑⠖⠊⢐⣤⠞⣩⡇⠄⠄⠄⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⠄⠝⠛⠋⠐\n⢸⠏⣷⠈⠄⣱⠃⠄⢠⠃⠐⡀⠄⠄⠄⠄⠙⠻⢿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠸⠄⠄⠄⠄\n⠈⣅⠞⢁⣿⢸⠘⡄⡆⠄⠄⠈⠢⡀⠄⠄⠄⠄⠄⠄⠉⠙⠛⠛⠛⠉⠉⡀⠄⠡⢀⠄⣀\n⠄⠙⡎⣹⢸⠄⠆⢘⠁⠄⠄⠄⢸⠈⠢⢄⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠃⠄⠄⠄⠄⠄\n⠄⠄⠑⢿⠈⢆⠘⢼⠄⠄⠄⠄⠸⢐⢾⠄⡘⡏⠲⠆⠠⣤⢤⢤⡤⠄⣖⡇⠄⠄⠄⠄⠄\n⣴⣶⣿⣿⣣⣈⣢⣸⠄⠄⠄⠄⡾⣷⣾⣮⣤⡏⠁⠘⠊⢠⣷⣾⡛⡟⠈⠄⠄⠄⠄⠄⠄\n⣿⣿⣿⣿⣿⠉⠒⢽⠄⠄⠄⠄⡇⣿⣟⣿⡇⠄⠄⠄⠄⢸⣻⡿⡇⡇⠄⠄⠄⠄⠄⠄⠄\n⠻⣿⣿⣿⣿⣄⠰⢼⠄⠄⠄⡄⠁⢻⣍⣯⠃⠄⠄⠄⠄⠈⢿⣻⠃⠈⡆⡄⠄⠄⠄⠄⠄\n⠄⠙⠿⠿⠛⣿⣶⣤⡇⠄⠄⢣⠄⠄⠈⠄⢠⠂⠄⠁⠄⡀⠄⠄⣀⠔⢁⠃⠄⠄⠄⠄⠄\n⠄⠄⠄⠄⠄⣿⣿⣿⣿⣾⠢⣖⣶⣦⣤⣤⣬⣤⣤⣤⣴⣶⣶⡏⠠⢃⠌⠄⠄⠄⠄⠄⠄\n⠄⠄⠄⠄⠄⠿⠿⠟⠛⡹⠉⠛⠛⠿⠿⣿⣿⣿⣿⣿⡿⠂⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄\n⠠⠤⠤⠄⠄⣀⠄⠄⠄⠑⠠⣤⣀⣀⣀⡘⣿⠿⠙⠻⡍⢀⡈⠂⠄⠄⠄⠄⠄⠄⠄⠄⠄\n⠄⠄⠄⠄⠄⠄⠑⠠⣠⣴⣾⣿⣿⣿⣿⣿⣿⣇⠉⠄⠻⣿⣷⣄⡀⠄⠄⠄⠄⠄⠄⠄⠄";

struct PersonHash{
    unsigned long int operator()(const Person& value) const {
        return (unsigned long)(value.GetID().series + value.GetID().number) % 12345;
    }
};

template<typename TKey, typename TValue>
void DictOutput(Dictionary<TKey, TValue> dict){
    cout << "\n|||||\n";
    dict.Map([](Pair<TKey, TValue> pair){
        cout << "[" << pair.key << "] -> " << pair.value << " :||: \n";
        return pair;
    });
    cout << "|||||\n";
}
template<class T>
void CacheOutput(Cache<T> cache){
    DictOutput(cache.GetCache());
}

void DoCache(){
    Cache<Person> cache = Cache<Person>(5);
    cout << "# Cache mod\n You have a cache to store people (with size 5), what do you want to do?\n";
    cout << "1. Add person\n";
    cout << "2. View cache\n";
    cout << "3. Exit (cache will be killed)\n";
    bool exitCond = true;
    int msg;
    while(exitCond){
        msg = -1;
        cin >> msg;
        switch (msg) {
            case 1: {
                cout << "Person template: { id series firstname middlename lastname birthdate(size_t/int) } : ";
                Person person;
                cin >> person;
                cache.Add(person);
                break;
            }
            case 2:
                CacheOutput(cache);
                break;
            case 3:
                exitCond = false;
                break;
            default:
                cout << defaultMessage << endl;
                break;
        }
    }
}

void DoIndexes(){
    ArraySequence<Person> array = ArraySequence<Person>();
    cout << "# Index mod\n Append people that you want to be indexed.\n Type 1 to append and 2 to stop.\n";
    bool exitCond = true;
    int msg;
    while(exitCond){
        msg = -1;
        cin >> msg;
        switch (msg) {
            case 1: {
                cout << "Person template: { id series firstname middlename lastname birthdate(size_t/int) } : ";
                Person person;
                cin >> person;
                array.Append(person);
                break;
            }
            case 2:
                exitCond = false;
                break;
            default:
                cout << defaultMessage << endl;
                return;
        }
    }

    Indexes<int, Person> indexes;
    cout << "\nChoose how you want data to be indexed.\n";
    cout << "1. By series\n";
    cout << "2. By number\n";
    cout << "3. Exit (everything will be killed)\n";
    int msg1;
    cin >> msg1;
    switch(msg1){
        case 1:{
            indexes = Indexes<int, Person>([](const Person& person){
                return person.GetID().series;
            });
            break;
        }
        case 2:{
            indexes = Indexes<int, Person>([](const Person& person){
                return person.GetID().number;
            });
            break;
        }
        default:
            return;
    }

    for(int i = 0; i < array.GetLength(); i++){
        indexes.AddData(array[i]);
    }
    indexes.BuildIndexed();

    DictOutput(indexes.ReturnIndexed());
}

void DoHashTable(){
    HashTable<Person, PersonHash> table = HashTable<Person, PersonHash>();
    bool exitCond = true;
    int msg;
    while(exitCond){
        cout << "# HashTable mod\n You want to store people in a hash map.\n What will you do?\n";
        cout << "1. Add person\n";
        cout << "2. Remove by hash\n";
        cout << "3. View table\n";
        cout << "4. Exit (hashes and table will be killed)\n";
        msg = -1;
        cin >> msg;
        switch (msg) {
            case 1: {
                cout << "Person template: { id series firstname middlename lastname birthdate(size_t/int) } : ";
                Person person;
                cin >> person;
                table.Add(person);
                break;
            }
            case 2: {
                cout << "enter hash: ";
                unsigned long hash;
                cin >> hash;
                table.Remove(hash);
                break;
            }
            case 3:
                DictOutput(table.ToDictionary());
                break;
            case 4:
                exitCond = false;
                break;
            default:
                cout << defaultMessage << endl;
                break;
        }
    }
}

int main() {
    int msg;
    cout << "Lab5 launched. Cache, Indexes, Dictionary, HashTable and so on.\n";
    while(true) {
        cout << "1. Cache\n";
        cout << "2. Indexes\n";
        cout << "3. HashTable\n";
        msg = -1;
        cin >> msg;
        switch (msg) {
            case 1:
                DoCache();
                break;
            case 2:
                DoIndexes();
                break;
            case 3:
                DoHashTable();
                break;
            default:
                cout << defaultMessage << endl;
                break;
        }
    }
    return 0;
}
