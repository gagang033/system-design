#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int key;
        Node *next,*prev;
        Node(int key){
            this->key=key;
            this->prev=this->next=nullptr;
        }
};

class DoublyLinkedList {
    public:
        Node *head,*tail;
        DoublyLinkedList(){
            this->head=new Node(-1);
            this->tail=new Node(-1);
            this->head->next=this->tail;
            this->tail->prev=this->head;
        }

        Node* addNode(int key){
            Node* newNode = new Node(key);
            placeNodeAtHead(newNode);
            return newNode;
        }

        void placeNodeAtHead(Node* node){
            node->next=this->head->next;
            node->prev=this->head;
            this->head->next->prev=node;
            this->head->next=node;
        }

        int removeNode(){
            Node* temp=tail->prev;
            tail->prev=temp->prev;
            temp->prev->next=tail;
            int key=temp->key;
            delete temp;
            return key;
        }

        void moveNodeToHead(Node* node){
            node->prev->next=node->next;
            node->next->prev=node->prev;
            placeNodeAtHead(node);
        }
};

class EvictionPolicy{
    public:
        virtual void update(int key)=0;
        virtual int evict()=0;
};

class LRUEvictionPolicy: public EvictionPolicy{
    public:
        map<int,Node*> nodeMap;
        DoublyLinkedList *dll;
        LRUEvictionPolicy(){
            nodeMap = map<int,Node*>();
            dll = new DoublyLinkedList();
        }

        void update(int key){
            if(nodeMap.find(key)==nodeMap.end()){
                Node* node=dll->addNode(key);
                nodeMap[key]=node;
            }
            Node* node=nodeMap[key];
            dll->moveNodeToHead(node);
        }

        int evict(){
            int key=dll->removeNode();
            nodeMap.erase(key);
            return key;
        }
};

class HashMapStorage {
    public:
        map<int,int> storage;
        int capacity;
        EvictionPolicy *evictionPolicy;
        HashMapStorage(int capacity,EvictionPolicy *evictionPolicy){
            this->capacity=capacity;
            storage = map<int,int>();
            this->evictionPolicy=evictionPolicy;
        }

        void put(int key,int val){
            if(storage.find(key)!=storage.end()){
                storage[key]=val;
                evictionPolicy->update(key);
            }
            if(storage.size()==this->capacity){
                int key=evictionPolicy->evict();
                cout<<"erasing "<<key<<endl;
                storage.erase(key);
            }
            storage[key]=val;
            evictionPolicy->update(key);
        }

        int get(int key){
            if(storage.find(key)==storage.end()){
                return -1;
            }
            evictionPolicy->update(key);
            return storage[key];
        }
};

class Cache{
    public:
        HashMapStorage* storage;
        int capacity;
        Cache(int capacity){
            this->capacity=capacity;
            storage=new HashMapStorage(capacity,new LRUEvictionPolicy());
        }

        void put(int key,int val){
            storage->put(key,val);
        }
        int get(int key){
            return storage->get(key);
        }
};

int main(){
    Cache *cache = new Cache(2);
    cache->put(1,1);
    cache->put(2,2);
    cout<<cache->get(1)<<endl;
    cache->put(3,3);
    cout<<cache->get(1)<<endl;
    cout<<cache->get(3)<<endl;
    cout<<cache->get(4)<<endl;
    cache->put(4,4);
    cout<<cache->get(1)<<endl;
}