#ifndef HOMEWORK_H_
#define HOMEWORK_H_

#include <iostream>
#include <vector>
using namespace std;
class Country;
class Region;
class City;
class Town;
class District;
class Component
{
protected:
    string name;
    int type;
public:
    Component(string _name, int _type){name = _name; type = _type;};
    string getName(){return name;};
    int getType(){return type;};
    virtual int Count() = 0;
};
//Class Definitions
class Country: public Component
{
private:
    int total;
public:
    Country(string name, int type):Component(name,type){};
    int Count();
    void setTotal(int _total){total=_total;};
    int getCountryTotal(){return total;};
};
class Region: public Country
{
private:
    int Rtotal;
public:
    Region( string name, int type):Country(name,type){};
    int Count(Country &cnt);
    void setTotal(int _total){Rtotal=_total;};
    int getRegionTotal(){return Rtotal;};
};
class City: public Region
{
private:
    int Ctotal;
    public:
    City(string name, int type):Region(name,type){};
    int Count(Region &r);
    void setTotal(int _total){Ctotal=_total;};
    int getCityTotal(){return Ctotal;};
};
class Town:public City
{
private:
    int Ttotal;
public:
    Town(string name, int type):City(name,type){};
    int Count(City &c);
    void setTotal(int _total){Ttotal=_total;};
    int getTownTotal(){return Ttotal;};
};
class District: public Town
{
private:
    int population;
public:
    District(int population, string name,int type):Town(name,type){};
    int getPopulation(){return population;};
    int Count(District &d,Town &t);
};
/* *********************************************************************************************************************** */
class AbstractIterator {
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() const = 0;
	virtual Component* CurrentComp() const = 0;
protected:
	AbstractIterator() {}
};
class Collection;
class CollectionIterator: public AbstractIterator {
public:
	CollectionIterator(const Collection *collection);
	void First();
	void Next();
	Component* CurrentComp() const;
	bool IsDone() const;
private:
	const Collection *_collection;
	int _current;
};
class CountryIterator: public AbstractIterator {
public:
	CountryIterator(const Collection *collection);
	void First();
	void Next();
	Component* CurrentComp() const;
	bool IsDone() const;
private:
	const Collection *_collection;
	int _current;
};
class RegionIterator: public AbstractIterator {
public:
	RegionIterator(const Collection *collection);
	void First();
	void Next();
	Component* CurrentComp() const;
	bool IsDone() const;
private:
	const Collection *_collection;
	int _current;
};
class CityIterator: public AbstractIterator {
public:
	CityIterator(const Collection *collection);
	void First();
	void Next();
	Component* CurrentComp() const;
	bool IsDone() const;
private:
	const Collection *_collection;
	int _current;
};
class TownIterator: public AbstractIterator {
public:
	TownIterator(const Collection *collection);
	void First();
	void Next();
	Component* CurrentComp() const;
	bool IsDone() const;
private:
	const Collection *_collection;
	int _current;
};
class DistrictIterator: public AbstractIterator {
public:
	DistrictIterator(const Collection *collection);
	void First();
	void Next();
	Component* CurrentComp() const;
	bool IsDone() const;
private:
	const Collection *_collection;
	int _current;
};
/* *********************************************************************************************************************** */
class AbstractAggregate {
public:
	virtual ~AbstractAggregate() {}
	virtual AbstractIterator* CreateIterator(int iteratorType) = 0;
	virtual void add(Component *) = 0; 		// Not needed for iteration.
	virtual int getCount() const = 0; // Needed for iteration.
	virtual Component * get(int) const = 0; // Needed for iteration.
protected:
	AbstractAggregate() {}
};
class Collection: public AbstractAggregate {
private:
	vector<Component*> _components;
public:
	// #4 *** 'CreateIterator' method modification *** #4 //
	AbstractIterator* CreateIterator(int iteratorType) {
		if (iteratorType == 1)
			return new CountryIterator(this);
		else if (iteratorType == 2)
			return new RegionIterator(this);
		else if (iteratorType == 3)
			return new CityIterator(this);
        else if (iteratorType == 4)
			return new TownIterator(this);
        else if (iteratorType == 5)
			return new DistrictIterator(this);
		else
			return NULL;
	}
	int getCount() const {
		return _components.size();
	}
	void add(Component *cmp) {
		_components.push_back(cmp);
	}
	Component * get(int index) const {
		return _components[index];
	}
};

#endif
