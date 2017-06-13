//============================================================================
// Name        : IteratorPattern2.cpp
// Description : Implements the Collection Iterator and the client code.
//============================================================================
#include "Iterator.h"

using namespace std;

CollectionIterator::CollectionIterator(const Collection *collection) :
	_collection(collection), _current(0) {
}
void CollectionIterator::First() {
	_current = 0;
}
void CollectionIterator::Next()  {
	_current++;
}
Item *CollectionIterator::CurrentItem() const {
	return (IsDone()?NULL:_collection->get(_current));
}
bool CollectionIterator::IsDone() const {
	return _current >= _collection->getCount();
}

void printAggregate(AbstractIterator& i) {
	cout << "Iterating over collection:" << endl;
	for(i.First();  !i.IsDone(); i.Next()) {
		cout << i.CurrentItem()->getName() << endl;
	}
	cout << endl;
}
int main()
{
	// Create Aggregate.
	AbstractAggregate *aggregate = new Collection();
	aggregate->add(new Item("Item 0"));
	aggregate->add(new Item("Item 1"));
	aggregate->add(new Item("Item 2"));
	aggregate->add(new Item("Item 3"));
	aggregate->add(new Item("Item 4"));
	aggregate->add(new Item("Item 5"));
	aggregate->add(new Item("Item 6"));
	aggregate->add(new Item("Item 7"));
	aggregate->add(new Item("Item 8"));

	// Create Iterator
	AbstractIterator *iterator = aggregate->CreateIterator();

	// Traverse the Aggregate.
	printAggregate(*iterator);
	delete iterator;
}
