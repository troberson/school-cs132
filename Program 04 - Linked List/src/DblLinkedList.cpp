#include <DblLinkedList.h>
#include <iostream>


using namespace std;

DblLinkedList::DblLinkedList() {
	head = nullptr;
	tail = nullptr;
	it = nullptr;
	count = 0;
}


bool DblLinkedList::push_back(const string& str) {	// write first
		// insert str at back of list
	return true;
}

void DblLinkedList::resetIterator() const {			// write second
	// needs to be written:  set it to head
}

bool DblLinkedList::hasMore() const {				// and so on....
	// needs to be written: is it pointing to nullptr
	return false;
}

string DblLinkedList::next() const {
	// needs to be written: gets the string the it pointer is pointing to
	//   then moves the it pointer to next "node" (could be nullptr)
	return string("stub");
}

void DblLinkedList::testConnections() {	
	// write test for connections:  loop through the list testing each node 
	cout << "TEST CONNECTIONS Passed\n";	
}

