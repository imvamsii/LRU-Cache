#include<iostream>
#include<list>
#include<unordered_map>

using namespace std;


//Node to store the Linked list...
class Node{
public:
    string key;
    int value;
    Node(string key, int value){
        this->key = key;
        this->value = value;
    }
};

//LRU's Data Structure...
class LRUCache{
public:
    int maxSize;
    list<Node> l;
    unordered_map<string, list<Node>::iterator> m;

    LRUCache(int maxSize){
        this->maxSize = maxSize >1 ? maxSize : 1;
    }
    
    //get a key-value pair....
    void insertKeyValue(string key, int value){

        if(m.count(key) != 0){   //value already present, then updates the value...
            auto it =m[key];
            it->value = value;
        }
        else{

            if(l.size() == maxSize){  //check the cache memory and remove the least recently used item...
                Node last = l.back();
                m.erase(last.key); // removes from hashmap
                l.pop_back(); //removes from  L.L
            }
            
            Node n(key, value);
            l.push_front(n);
            m[key] = l.begin();
        }
    }

    int* getValue(string key){

        if(m.count(key)!= 0){
            auto it = m[key];

            int value = it->value;
            l.push_front(*it);
            l.erase(it);
            m[key] = l.begin();
            return &l.begin()->value; //in the cache every key may not present that's why returning address...
        }
        return NULL;
    }

    string mostRecentKey(){
        return l.front().key;
    }
};

//Driver's code...

int main(){
    LRUCache lru(3);

    lru.insertKeyValue("mango", 10);
    lru.insertKeyValue("apple", 20);
    lru.insertKeyValue("guava", 30);

    cout << lru.mostRecentKey() << endl;

    lru.insertKeyValue("mango", 40);
    cout << lru.mostRecentKey() << endl;

    int *orders = lru.getValue("mango");
    if(orders != NULL){
        cout << "Value of Mango is:" << *orders << endl;
    }

    lru.insertKeyValue("banana", 20);

    if(lru.getValue("apple")  == NULL) cout << "Apple doesn't exist!";

    if(lru.getValue("guava")  == NULL) cout << "Guava doesn't exist!";

    if(lru.getValue("banana") == NULL) cout << "Banana doesn't exist!";

    if(lru.getValue("mango")  == NULL) cout << "Mango doesn't exist!";
}