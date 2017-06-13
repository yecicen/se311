#ifndef PROJECT_H
#define PROJECT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <stdexcept>
#include <cstdlib>
using namespace std;

//Forward Declarations
class Location;
class Database;
class Observer;
class ElectronicDevice;
class AbsCattle;
class BeefCattle;
class MilkCattle;
class CarbonHydrate;
class Protein;
class Visitor;
class MinistryGuy;
class PhysicianVisitor;
class ZigbeeSignals;
class BluetoothSignals;
class AdaptorBluetoothToZigbee;
/* # Singleton Pattern # */
class Location
{
private:
    int x;
    int y;
public:
    int getX();
    int getY();
    void setX(int _x);
    void setY(int _y);
};

class Database
{
private:
    vector<int> IDs;
    vector<Location>locations;
    vector<string> signals;
    Database(){};
    Database(const Database&);
    Database& operator=(const Database&);
    static Database* instance;
public:
    static Database* getInstance()
    {
        if(instance == NULL)
        {
            if(instance == NULL)
                instance = new Database();
        }
            return instance;
    }
    void storeLocation(Location location);
    void storeIDs(int id);
    void storeSignals(string signal);
    int cattleSize();
    vector <int> getIDVector();
    vector <Location> getLocations();
    vector <string> getSignals();
};

/* # Factory Pattern # */
class CarbonHydrate
{
public:
    CarbonHydrate(){};
};
class Corn: public CarbonHydrate
{
public:

    Corn():CarbonHydrate(){};
};


class Wheat: public CarbonHydrate
{
public:
    Wheat():CarbonHydrate(){};
};

class Protein
{
public:
    Protein(){};
};

class SoyBean: public Protein
{
public:
    SoyBean():Protein(){};
};

class Canola:public Protein
{
public:
    Canola():Protein(){};
};
class AbsCattle
{
private:
    int id;
    bool state;
public:
    virtual CarbonHydrate* createCarbonhydrate() = 0;
    virtual Protein* createProtein() = 0;

    void setID(int _id);
    int getID();
    virtual bool getState();
    void setState(bool _state);
};

class MilkCattle: public AbsCattle
{
private:
    deque<ElectronicDevice> devices;
    Location location;
public:
    CarbonHydrate* createCarbonhydrate();
    Protein* createProtein();

    void Attach(ElectronicDevice device);
    void Detach(ElectronicDevice device);
    void Notify();
    void setLocation(int x, int y);
    Location getLocation();
};



class BeefCattle:public AbsCattle
{
private:
    deque<ElectronicDevice> devices;
    Location location;
public:
    CarbonHydrate* createCarbonhydrate();
    Protein* createProtein();
    void Attach(ElectronicDevice device);
    void Detach(ElectronicDevice device);
    void Notify();
    void setLocation(int x, int y);
    Location getLocation();
};
/* #Observer Pattern# */
class Observer
{
public:
    virtual void UpdateBeef() = 0;
    virtual void UpdateMilk() = 0;
};
class ElectronicDevice: public Observer
{
private:
    BeefCattle _cattle1;
    MilkCattle _cattle2;
    string signalType;
    bool observerState;
public:
    ElectronicDevice(){};
    void UpdateBeef();
    void UpdateMilk();
    void setSignalType(string _signalType);
    string getSignalType();
};

/* # ADAPTER PATTERN # */
//Target Signal
class BluetoothSignals
{
public:
    BluetoothSignals(){};
    virtual string UsingZigbeeSignals() = 0;
};
//Adaptee
class ZigbeeSignals
{
public:
    string UsingZigbeeSignals();
};

//Adaptor
class AdaptorBluetoothToZigbee: public ZigbeeSignals
{
private:
    ZigbeeSignals* Zsignal;
public:
    string UsingZigbeeSignals();
    AdaptorBluetoothToZigbee(){};
    AdaptorBluetoothToZigbee(ZigbeeSignals* _signal):Zsignal(_signal) {};
};
/* #VISITOR PATTERN# */
class Visitor
{
protected:
    Visitor() {};
public:
    virtual ~Visitor() {};
    virtual void Visit(BeefCattle element) = 0;
    virtual void Visit(MilkCattle element) = 0;
};
class PhysicianVisitor: public Visitor
{
public:
    void Visit(BeefCattle element);
    void Visit(MilkCattle element);
};
class MinistryGuy: public Visitor
{
public:
    void Visit(BeefCattle element);
    void Visit(MilkCattle element);
};
#endif
#include "project.h"

int Location::getX()
{
    return x;
}

int Location::getY()
{
    return y;
}

void Location::setX(int _x)
{
    x = _x;
}

void Location::setY(int _y)
{
    y = _y;
}

void Database::storeLocation(Location location)
{
    cout << "Location " << location.getX() << ", " << location.getY() << " added to database " << endl;
    locations.push_back(location);
}

void Database::storeIDs(int id)
{
    cout << "Cattle " << id << " added to database" << endl;
    IDs.push_back(id);
}

void Database::storeSignals(string signal)
{
    cout << signal << " added to database" << endl;
    signals.push_back(signal);
}

int Database::cattleSize()
{
    return IDs.size() || locations.size();
}

vector <int> Database::getIDVector()
{
    return IDs;
}

vector <Location> Database::getLocations()
{
    return locations;
}

vector <string> Database::getSignals()
{
    return signals;
}

Database* Database::instance = 0;

/*------------------- Observer -------------  */
void ElectronicDevice::UpdateBeef()
{
    cout << "Caution! A Beef Cattle tried to escape!" << endl;
}
void ElectronicDevice::UpdateMilk()
{
    cout << "Caution! A Milk Cattle tried to escape!" << endl;
}
void ElectronicDevice::setSignalType(string _signalType)
{
    signalType = _signalType;
}
string ElectronicDevice::getSignalType()
{
    return signalType;
}
void AbsCattle::setID(int _id)
{
    id = _id;
}
int AbsCattle::getID()
{
    return id;
}

bool AbsCattle::getState()
{
    return state;
}

void AbsCattle::setState(bool _state)
{
    state = _state;
}

CarbonHydrate* MilkCattle::createCarbonhydrate()
{
    cout << "Here is a yummy Corn"; //We saved this corn from aliens, they ruined the farm with symbols
    return new Corn();
}
Protein* MilkCattle::createProtein()
{
    cout << "Here is a not yummy Soybean"; //I thought only vegans eat them.
    return new SoyBean();
}


void MilkCattle::Attach(ElectronicDevice device)
{
    devices.push_back(device);
}
void MilkCattle::Detach(ElectronicDevice device)
{
    unsigned int i = 0;
    for(i = 0; i<devices.size(); i++)
    {
        devices.erase(devices.begin()+i);
    }
}
void MilkCattle::Notify()
{
    unsigned int i = 0;
    for(i = 0; i < devices.size(); i++)
    {
        devices[i].UpdateMilk();
    }
}
void MilkCattle::setLocation(int x, int y)
{
    //Farm borders are 0,0,100,100 its simply a square with size 100.
    if(x>100 || y>100)
        Notify();
    location.setX(x);
    location.setY(y);
}
Location MilkCattle::getLocation()
{
    return location;
}

CarbonHydrate* BeefCattle::createCarbonhydrate()
{
    cout << "Here is a delicious Wheat";
    return new Wheat();
}
Protein* BeefCattle::createProtein()
{
    cout << "Look! Its a Canola";
    return new Canola();
}

void BeefCattle::Attach(ElectronicDevice device)
{
    devices.push_back(device);
}
void BeefCattle::Detach(ElectronicDevice device)
{
    unsigned int i = 0;
    for(i = 0; i<devices.size(); i++)
    {
        devices.erase(devices.begin()+i);
    }
}
void BeefCattle::Notify()
{
    unsigned int i = 0;
    for(i = 0; i < devices.size(); i++)
    {
        devices[i].UpdateBeef();
    }
}

void BeefCattle::setLocation(int x, int y)
{
    //Farm borders are 0,0,100,100 its simply a square with size 100.
    if(x>100 || y>100)
        Notify();
    location.setX(x);
    location.setY(y);
}
Location BeefCattle::getLocation()
{
    return location;
}

string ZigbeeSignals::UsingZigbeeSignals()
{
    return "Zigbee Signal";
}


string AdaptorBluetoothToZigbee::UsingZigbeeSignals()
{
    string signal = Zsignal->UsingZigbeeSignals();
    return signal;
}


void PhysicianVisitor::Visit(BeefCattle element)
{
    if(element.getID() != NULL)
    {
        cout << "ID of the current Beef cattle is: " << element.getID() << endl;
        cout << "Giving vaccination to current cattle " << endl;
    }
    else
        cout << "o.O This Beef cattle has no tag id or even worse there is no cattle :( " << endl;
}
void PhysicianVisitor::Visit(MilkCattle element)
{
    if(element.getID() != NULL)
    {
        cout << "ID of the current Milk cattle is:  " << element.getID() << endl;
        cout << "Giving vaccination... I hate my job :( " << endl;
    }


    else
        cout << "This Milk cattle has no tag id or are we sure that this is cattle???" << endl;
}
void MinistryGuy::Visit(BeefCattle element)
{
    if(element.getID() != NULL)
    {
        cout << "This Beef Cattle has ear tag and ID: " << element.getID() << endl;
    }
    else
        cout << "This Beef Cattle has no tag ID" << endl;
}
void MinistryGuy::Visit(MilkCattle element)
{
    if(element.getID() != NULL)
    {
        cout << "This Milk Cattle has ear tag and ID: " << element.getID() << endl;
    }
    else
        cout << "This Milk Cattle has no tag ID" << endl;
}





int main()
{
    int i = 0, j = 0; //indices

    //Singleton Test
    Database *db1 = Database::getInstance();
    Database *db2 = Database::getInstance();
    if(db1 == db2)
        cout << "Creating more databases won't effect" << endl;

    //Creating Ecosystem
    deque<MilkCattle> milk;
    MilkCattle m0;
    MilkCattle m1;
    MilkCattle m2;
    MilkCattle m3;
    MilkCattle m4;
    milk.push_back(m0);
    milk.push_back(m1);
    milk.push_back(m2);
    milk.push_back(m3);
    milk.push_back(m4);
    deque<BeefCattle> beef;
    BeefCattle b0;
    BeefCattle b1;
    BeefCattle b2;
    BeefCattle b3;
    BeefCattle b4;

    beef.push_back(b0);
    beef.push_back(b1);
    beef.push_back(b2);
    beef.push_back(b3);
    beef.push_back(b4);

    deque<ElectronicDevice> devices;
    ElectronicDevice d0;
    ElectronicDevice d1;
    ElectronicDevice d2;
    ElectronicDevice d3;
    ElectronicDevice d4;

    devices.push_back(d0);
    devices.push_back(d1);
    devices.push_back(d2);
    devices.push_back(d3);
    devices.push_back(d4);

    deque<AdaptorBluetoothToZigbee> Zsignals;
    AdaptorBluetoothToZigbee z0;
    AdaptorBluetoothToZigbee z1;
    AdaptorBluetoothToZigbee z2;
    AdaptorBluetoothToZigbee z3;
    AdaptorBluetoothToZigbee z4;


    Zsignals.push_back(z0);
    Zsignals.push_back(z1);
    Zsignals.push_back(z2);
    Zsignals.push_back(z3);
    Zsignals.push_back(z4);

    //Actually one physician was enough but we don't beware of any expenses.
    deque<PhysicianVisitor> physicians;
    PhysicianVisitor phy0;
    PhysicianVisitor phy1;
    PhysicianVisitor phy2;
    PhysicianVisitor phy3;
    PhysicianVisitor phy4;

    physicians.push_back(phy0);
    physicians.push_back(phy1);
    physicians.push_back(phy2);
    physicians.push_back(phy3);
    physicians.push_back(phy4);

    //Actually one ministry guy was enough but we don't fear from any audit.
    deque<MinistryGuy> ministry;
    MinistryGuy g0;
    MinistryGuy g1;
    MinistryGuy g2;
    MinistryGuy g3;
    MinistryGuy g4;

    ministry.push_back(g0);
    ministry.push_back(g1);
    ministry.push_back(g2);
    ministry.push_back(g3);
    ministry.push_back(g4);

    // Setting ID for cattles
    for(i = 0; i < milk.size(); i++)
    {
        milk[i].setID(i);
    }

    for(i = 0; i < beef.size(); i++)
    {
        beef[i].setID(i+milk.size());
    }
    //Giving devices to signals
    for(i = 0; i < devices.size(); i++)
    {
        devices[i].setSignalType(Zsignals[i].UsingZigbeeSignals());
    }
    //Adding Signals to Database
    for(i = 0; i <Zsignals.size(); i++)
    {
        db1->storeSignals(devices[i].getSignalType());
    }
    //Adding cattles to database
    for(i = 0; i < milk.size(); i++)
    {
        db1->storeIDs(milk[i].getID());
    }
    for(i = 0; i < beef.size(); i++)
    {
        db1->storeIDs(beef[i].getID());
    }
    //Observer Test, Looking for is any cattle out of bounds
    for(i = 0; i < beef.size(); i++)
    {
        beef[i].Attach(devices[i]);
    }
    for(i = 0; i < milk.size(); i++)
    {
        milk[i].Attach(devices[i]);
    }
    // Setting location for cattles
    for(i = 0; i < beef.size(); i++)
    {
        beef[i].setLocation(rand()%150, rand()%150);
    }
    for(i = 0; i < milk.size(); i++)
    {
        milk[i].setLocation(rand()%150, rand()%150);
    }


    // Adding locations to database
    for(i = 0; i < milk.size(); i++)
    {
        db1->storeLocation(milk[i].getLocation());
    }
    for(i = 0; i < beef.size(); i++)
    {
        db1->storeLocation(beef[i].getLocation());
    }
    //Factory Test, Giving cattles food
    cout << "----------\tFeeding Milk Cattles\t----------" << endl;
    for(i = 0; i < milk.size(); i++)
    {
        milk[i].createCarbonhydrate();
        cout << " for Cattle " << milk[i].getID() << endl;
    }
    for(i = 0; i < milk.size(); i++)
    {
        milk[i].createProtein();
        cout << " for Cattle " << milk[i].getID() << endl;
    }
    cout << endl;
    cout << "-----------\tFeeding Beef Cattles\t---------" << endl;
    for(i = 0; i < beef.size(); i++)
    {
        beef[i].createCarbonhydrate();
        cout << " for Cattle " << beef[i].getID() << endl;
    }
    for(i = 0; i < beef.size(); i++)
    {
        beef[i].createProtein();
        cout << " for Cattle " <<  beef[i].getID() << endl;
    }

    //Visitors Part
    string seasons[4] = {"Winter", "Spring", "Summer", "Autumn"};

    for(i = 0; i < 4; i++)
    {
        if(i == 1)
        {
            cout << "\n SEASON : " << seasons[i] << endl;
            cout << " \\\\\ Ministry of Food visiting ///// " << endl;
            for(j = 0; j < ministry.size(); j++)
            {
                ministry[j].Visit(beef[j]);
                ministry[j].Visit(milk[j]);
            }
        }
        else if(i == 3)
        {
            cout << "\n SEASON : " << seasons[i] << endl;
            cout << " \\\\\ Physicians are visiting ///// " << endl;
            for(j = 0; j < physicians.size(); j++)
            {
                physicians[j].Visit(beef[j]);
                physicians[j].Visit(milk[j]);
            }
        }
        else
        {
            cout << "\n SEASON : " << seasons[i] <<", No available time for visitors" << endl;
        }
    }
    return 0;
}