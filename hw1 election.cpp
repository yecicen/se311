#include "homework.h"

using namespace std;
/* ***************************************COUNT METHODS*************************************************************************** */
int Country::Count()
{
    //return total;
}
int Region::Count(Country &cnt)
{
    cnt.setTotal(Rtotal);
    //return Rtotal;
}
int City::Count(Region &r)
{
    r.setTotal(Ctotal);
    //return Ctotal;
}
int Town::Count(City &c)
{
    c.setTotal(Ttotal);
    return Ttotal;
}
int District::Count(District &d,Town &t)
{
    t.setTotal(d.getPopulation());
    //return population;
}

/* ******************************************ITERATORS****************************************************************************************** */
CollectionIterator::CollectionIterator(const Collection *collection) :
		_collection(collection), _current(0) {
}
void CollectionIterator::First() {
	_current = 0;
}
void CollectionIterator::Next() {
	_current++;
}
Component *CollectionIterator::CurrentComp() const {
	return (IsDone() ? NULL : _collection->get(_current));
}
bool CollectionIterator::IsDone() const {
	return _current >= _collection->getCount();
}
// Country Iterator
CountryIterator::CountryIterator(const Collection *collection) :
		_collection(collection), _current(0) {
}
void CountryIterator::First() {
	_current = 0;
	// pass to next element if it is not equal to given type
	while (_collection->get(_current)->getType() != 1) {
		Next();
	}
}
void CountryIterator::Next() {
	_current++;
	// find element in given type until collection is traversed completely
	while (!IsDone() && (_collection->get(_current)->getType() != 1)) {
		Next();
	}
}
Component *CountryIterator::CurrentComp() const {
	return (IsDone() ? NULL : _collection->get(_current));
}
bool CountryIterator::IsDone() const {
	return _current >= _collection->getCount();
}
//RegionIterator
RegionIterator::RegionIterator(const Collection *collection) :
		_collection(collection), _current(0) {
}
void RegionIterator::First() {
	_current = 0;
	// pass to next element if it is not equal to given type
	while (_collection->get(_current)->getType() != 2) {
		Next();
	}
}
void RegionIterator::Next() {
	_current++;
	// find element in given type untill collection is traversed completely
	while (!IsDone() && (_collection->get(_current)->getType() != 2)) {
		Next();
	}
}
Component *RegionIterator::CurrentComp() const {
	return (IsDone() ? NULL : _collection->get(_current));
}
bool RegionIterator::IsDone() const {
	return _current >= _collection->getCount();
}
//CityIterator
CityIterator::CityIterator(const Collection *collection) :
		_collection(collection), _current(0) {
}
void CityIterator::First() {
	_current = 0;
	// pass to next element if it is not equal to given type
	while (_collection->get(_current)->getType() != 3) {
		Next();
	}
}
void CityIterator::Next() {
	_current++;
	// find element in given type untill collection is traversed completely
	while (!IsDone() && (_collection->get(_current)->getType() != 3)) {
		Next();
	}
}
Component *CityIterator::CurrentComp() const {
	return (IsDone() ? NULL : _collection->get(_current));
}
bool CityIterator::IsDone() const {
	return _current >= _collection->getCount();
}
//Town Iterator
TownIterator::TownIterator(const Collection *collection) :
		_collection(collection), _current(0) {
}
void TownIterator::First() {
	_current = 0;
	// pass to next element if it is not equal to given type
	while (_collection->get(_current)->getType() != 4) {
		Next();
	}
}
void TownIterator::Next() {
	_current++;
	// find element in given type untill collection is traversed completely
	while (!IsDone() && (_collection->get(_current)->getType() != 4)) {
		Next();
	}
}
Component *TownIterator::CurrentComp() const {
	return (IsDone() ? NULL : _collection->get(_current));
}
bool TownIterator::IsDone() const {
	return _current >= _collection->getCount();
}
//District Iterator
DistrictIterator::DistrictIterator(const Collection *collection) :
		_collection(collection), _current(0) {
}
void DistrictIterator::First() {
	_current = 0;
	// pass to next element if it is not equal to given type
	while (_collection->get(_current)->getType() != 5) {
		Next();
	}
}
void DistrictIterator::Next() {
	_current++;
	// find element in given type untill collection is traversed completely
	while (!IsDone() && (_collection->get(_current)->getType() != 5)) {
		Next();
	}
}
Component *DistrictIterator::CurrentComp() const {
	return (IsDone() ? NULL : _collection->get(_current));
}
bool DistrictIterator::IsDone() const {
	return _current >= _collection->getCount();
}
void printAggregate(AbstractIterator& i) {
	cout << "Iterating over collection:" << endl;
	for (i.First(); !i.IsDone(); i.Next()) {
		cout << i.CurrentComp()->getName() << endl;
		cout << i.CurrentComp()->Count() << endl;
	}
	cout << endl;
}
/* *************************************************************END ITERATORS******************************************************************* */
int main()
{
    AbstractAggregate *aggregate = new Collection();
	aggregate->add(new Country("Turkey",1));
	aggregate->add(new Region("Aegean",2));
	aggregate->add(new City("Izmir",3));
	aggregate->add(new Town("Balcova",4));
	aggregate->add(new District(0,"Uckuyular",5));

	AbstractIterator *CountryIterator = aggregate->CreateIterator(4);
    printAggregate(*CountryIterator);
	delete CountryIterator;
    /*
    Region *r = new Region(1,"tr",2);
    City *c = new City(10,"Bursa",3);
    Town *t = new Town(12,"Balcova",4);
    cout<<t->getName()<<t->getTotal()<<endl;
    cout<<c->getName()<<c->getType()<<endl;
    cout<<r->getName()<<endl;*/
    return 0;

}
