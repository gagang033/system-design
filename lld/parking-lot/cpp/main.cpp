#include<bits/stdc++.h>
using namespace std;

enum Type{
    TWO_WHEELER,
    FOUR_WHEELER,
};

class Vehicle{
    public:
        string number;
        Type type;
        Vehicle(){}
        Vehicle(string number, Type type){
            this->number=number;
            this->type = type;
        }
};

class ParkingSpot{
    public:
        string _id;
        bool _isEmpty;
        Type _type;
        int _price;
        Vehicle* _vehicle;
        ParkingSpot(){}
        ParkingSpot(string id, Type type, int price){
            this->_id=id;
            this->_isEmpty=true;
            this->_type=type;
            this->_price=price;
            this->_vehicle=nullptr;
        }

        bool isEmpty(){
            return this->_isEmpty;
        }

        void parkVehicle(Vehicle* vehicle){
            this->_vehicle=vehicle;
            this->_isEmpty=false;
            cout<<"Vehilce parked at "<<this->_id<<endl;
        }

        void removeVehicle(){
            this->_vehicle=nullptr;
            this->_isEmpty=true;
            cout<<"Vehilce removed from "<<this->_id<<endl;
        }
};

class ParkingStrategy{
    public:
        virtual ParkingSpot* findParkingSpace(vector<ParkingSpot*> parkingSpots) = 0;
};

class FirstAvailableParkingStrategy: public ParkingStrategy{
    public:
        ParkingSpot* findParkingSpace(vector<ParkingSpot*> parkingSpots){
           
            for(ParkingSpot* parkingSpot: parkingSpots){
                if(parkingSpot->isEmpty())
                    return parkingSpot;
            }
            return nullptr;
        }
};

class ParkingSpotManager{
    public:
        virtual ParkingSpot* findParkingSpace() = 0;
};

class TwoWheelerManager: public ParkingSpotManager{
    public:
        vector<ParkingSpot*> parkingSpots;
        ParkingStrategy* strategy;

        TwoWheelerManager(){}
        TwoWheelerManager(vector<ParkingSpot*> parkingSpots, ParkingStrategy* strategy){
            this->parkingSpots = parkingSpots;
            this->strategy = strategy;
        }

        ParkingSpot* findParkingSpace(){
            return strategy->findParkingSpace(parkingSpots);
        }
};

class FourWheelerManager: public ParkingSpotManager{
    public:
        vector<ParkingSpot*> parkingSpots;
        ParkingStrategy* strategy;

        FourWheelerManager(){}
        FourWheelerManager(vector<ParkingSpot*> parkingSpots, ParkingStrategy* strategy){
            this->parkingSpots = parkingSpots;
            this->strategy = strategy;
        }

        ParkingSpot* findParkingSpace(){
            return strategy->findParkingSpace(parkingSpots);
        }
};

class ParkingSpotFactory{
    public:
        int TWO_WHEELER_PRICE=10,FOUR_WHEELER_PRICE=20;

        TwoWheelerManager* twoWheelerManager;
        FourWheelerManager* fourWheelerManager;
        ParkingStrategy* strategy;

        void init(){
            ParkingSpot* a=new ParkingSpot("a",Type::TWO_WHEELER, TWO_WHEELER_PRICE);
            ParkingSpot* b=new ParkingSpot("b",Type::TWO_WHEELER, TWO_WHEELER_PRICE);
            ParkingSpot* c=new ParkingSpot("c",Type::TWO_WHEELER, TWO_WHEELER_PRICE);

            vector<ParkingSpot*> twoWheelerSpots = {a,b,c};

            ParkingSpot* d=new ParkingSpot("d",Type::FOUR_WHEELER, FOUR_WHEELER_PRICE);
            ParkingSpot* e=new ParkingSpot("e",Type::FOUR_WHEELER, FOUR_WHEELER_PRICE);
            
            vector<ParkingSpot*> fourWheelerSpots = {d,e};

            ParkingStrategy* strategy = new FirstAvailableParkingStrategy();

            this->twoWheelerManager = new TwoWheelerManager(twoWheelerSpots, strategy);
            this->fourWheelerManager = new FourWheelerManager(fourWheelerSpots, strategy);
        }

        ParkingSpotFactory(){
            init();
        }
        ParkingSpotManager* getParkingSpotManager(Vehicle* vehicle){
            if(vehicle->type == Type::TWO_WHEELER){
                return this->twoWheelerManager;
            }
            return this->fourWheelerManager;
        }
};

class EntranceGate{
    public:
        ParkingSpotFactory* parkingSpotFactory;
        EntranceGate(){}
        EntranceGate(ParkingSpotFactory* parkingSpotFactory){
            this->parkingSpotFactory = parkingSpotFactory;
        }

        ParkingSpot* findParkingSpace(Vehicle* vehicle){
            ParkingSpotManager* parkingSpotManager = parkingSpotFactory->getParkingSpotManager(vehicle);
            ParkingSpot* parkingSpot = parkingSpotManager->findParkingSpace();
            return parkingSpot;
        }
};

int main(){
    ParkingSpotFactory* parkingSpotFactory = new ParkingSpotFactory();
    EntranceGate* entranceGate = new EntranceGate(parkingSpotFactory);

    Vehicle* a=new Vehicle("1",Type::TWO_WHEELER);
    Vehicle* b=new Vehicle("2",Type::TWO_WHEELER);
    Vehicle* c=new Vehicle("3",Type::TWO_WHEELER);
    Vehicle* d=new Vehicle("4",Type::TWO_WHEELER);

    Vehicle* e=new Vehicle("5",Type::FOUR_WHEELER);
    Vehicle* f=new Vehicle("6",Type::FOUR_WHEELER);
    Vehicle* g=new Vehicle("7",Type::FOUR_WHEELER);

    ParkingSpot* pa = entranceGate->findParkingSpace(a);
    if(pa==nullptr){
        cout<<"No parking spot available for "<<a->number<<endl;
    }
    else{
        pa->parkVehicle(a);
    }

    ParkingSpot* pb = entranceGate->findParkingSpace(b);
    if(pb==nullptr){
        cout<<"No parking spot available for "<<b->number<<endl;
    }
    else{
        pb->parkVehicle(b);
    }

    ParkingSpot* pc = entranceGate->findParkingSpace(c);
    if(pc==nullptr){
        cout<<"No parking spot available for "<<c->number<<endl;
    }
    else{
        pc->parkVehicle(c);
    }

    ParkingSpot* pd = entranceGate->findParkingSpace(d);
    if(pd==nullptr){
        cout<<"No parking spot available for "<<d->number<<endl;
    }
    else{
        pd->parkVehicle(d);
    }

    pb->removeVehicle();

    pd = entranceGate->findParkingSpace(d);
    if(pd==nullptr){
        cout<<"No parking spot available for "<<d->number<<endl;
    }
    else{
        pd->parkVehicle(d);
    }
}