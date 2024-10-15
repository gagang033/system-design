#include<bits/stdc++.h>
using namespace std;

enum Size {
    SMALL,
    MEDIUM,
    LARGE
};

class Locker {
    public:
        int _lockerId;
        bool _isFree;
        int _pin;
        Size _size;
        Locker(int lockerId, Size size){
            this->_lockerId = lockerId;
            this->_size = size;
            this->_isFree = true;
            this->_pin = -1;
        }

        bool isFree(){
            return this->_isFree;
        }

        void lock(int pin){
            this->_pin = pin;
            this->_isFree = false;
        }

        bool unlock(int pin){
            if(this->_pin == pin){
                this->_pin = -1;
                this->_isFree = true;
                return true;
            }
            return false;
        }
};

class Location {
    public:
        int x,y;
};

class Store {
    public:
        int _storeId;
        set<Locker*> _smallLockers, _mediumLockers, _largeLockers;
        map<int, Locker*> lockerMap;
        Location* _storeLocation;

        Store(int id, Location* location, int small, int medium, int large){
            this->_storeId = id;
            this->_storeLocation = location;
            lockerMap = map<int,Locker*>();

            //add lockers
            int lockerId=0;
            while(small--){
                Locker* locker = new Locker(lockerId, Size::SMALL);
                this->_smallLockers.insert(locker);
                lockerMap[lockerId]=locker;
                lockerId++;
            }
            while(medium--){
                Locker* locker = new Locker(lockerId, Size::MEDIUM);
                this->_mediumLockers.insert(locker);
                lockerMap[lockerId]=locker;
                lockerId++;
            }
            while(large--){
                Locker* locker = new Locker(lockerId, Size::LARGE);
                this->_largeLockers.insert(locker);
                lockerMap[lockerId]=locker;
                lockerId++;
            }
        }

        set<Locker*> getLockers(Size size){
            if(size==Size::SMALL)
                return this->_smallLockers;
            if(size==Size::SMALL)
                return this->_mediumLockers;
            return this->_largeLockers;
        }

        int assignLocker(Size size){
            for(auto locker: getLockers(size)){
                if(locker->isFree())
                    return locker->_lockerId;
            }
            return -1;
        }

        bool unlock(int lockerId, int pin){
            Locker* locker = lockerMap[lockerId];
            return locker->unlock(pin);
        }

        int getLockerPin(int lockerId){
            Locker* locker = lockerMap[lockerId];
            return locker->_pin;
        }
};

class StoreManager{
    public:
        vector<Store*> stores;
        map<int,Store*> storeMap;
        StoreManager(){
            stores = vector<Store*>();
            storeMap = map<int,Store*>();
            addStore(nullptr,3,3,3);
        }

        void addStore(Location* location, int small,int medium, int large){
            int id = stores.size();
            Store* store = new Store(id, location,small,medium,large);
            stores.push_back(store);
            storeMap[id]=store;
        }

        void removeStore(){

        }

        int findClosestStore(Location* location){
            return stores[0]->_storeId;
        }
};

class Order{
    public:
        int orderId;
        Size size;
        int storeId, lockerId;
        int userId;
        Order(int id, Size size, int storeId, int lockerId, int userId){
            this->orderId = id;
            this->size= size;
            this->storeId = storeId;
            this->lockerId = lockerId;
            this->userId = userId;
        }
};

class OrderManager {
    public:
        vector<Order*> orders;
        map<int,Order*> orderMap;
        OrderManager(){
            orders= vector<Order*>();
            orderMap=map<int,Order*>();
        }

        int addOrder(Size size, int storeId, int lockerId, int userId){
            int id = orders.size();
            Order* order = new Order(id, size, storeId, lockerId, userId);
            orders.push_back(order);
            orderMap[id]=order;
            return id;
        }

        Order* getOrderDetails(int orderId){
            return orderMap[orderId];
        }
};

class LockerSystem {
    public:
        OrderManager* orderManager;
        StoreManager* storeManager;

        LockerSystem(){
            orderManager = new OrderManager();
            storeManager = new StoreManager();
        }

        pair<int,int> placeOrder(int userId, Size size, Location* location){
            int storeId = storeManager->findClosestStore(location);
            Store* store = storeManager->storeMap[storeId];
            int lockerId = store->assignLocker(size);
            int pin= rand()%1000;
            Locker* locker = store->lockerMap[lockerId];
            locker->lock(pin);

            int orderId = orderManager->addOrder(size,storeId,lockerId,userId);
            return {orderId,pin};
        }

        bool completeOrder(int orderId, int pin) {
            Order* order = orderManager->getOrderDetails(orderId);
            int storeId = order->storeId;
            int lockerId = order->lockerId;
            Store* store = storeManager->storeMap[storeId];
            Locker* locker = store->lockerMap[lockerId];
            return locker->unlock(pin);
        }

};

class User {
    public:
        int userId;
        Location* location;
        map<int,int> orders; // orderId - pin 
        User(int id, Location* location){
            this->userId = id;
            this->location=location;
            orders = map<int,int>();
        }

        void placeOrder(Size size, LockerSystem* lockerSystem){
            pair<int,int> order = lockerSystem->placeOrder(userId,size,location);
            int orderId = order.first;
            int pin = order.second;
            orders[orderId]=pin;
        }

        void collectParcel(int orderId, LockerSystem* lockerSystem){
            int pin = orders[orderId];
            if(lockerSystem->completeOrder(orderId,pin)){
                cout<<userId<<" collected "<<orderId<<endl;
            }
            else{
                cout<<userId<<" incorrect pin "<<orderId<<endl;
            }
        }
};

int main(){
    Location* location = new Location();
    User* gagan = new User(1,location);
    User* naveen = new User(2,location);

    LockerSystem* lockerSystem = new LockerSystem();

    gagan->placeOrder(Size::MEDIUM,lockerSystem);
    naveen->placeOrder(Size::SMALL,lockerSystem);
    gagan->placeOrder(Size::LARGE,lockerSystem);

    gagan->collectParcel(0,lockerSystem); 
       
}