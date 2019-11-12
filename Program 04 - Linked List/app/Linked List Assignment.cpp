#include <DblLinkedList.h>
//#include <TRString.h>

#include <iostream>
#include <string>    // only used temporarily for Lab

int main() {
	DblLinkedList list;
	list.push_back("1");	// insert back...into empty list
	list.push_back("2");	// insert back 	
	list.push_back("3");					
	list.push_back("4");
	list.push_back("5");
	list.push_back("6");
	list.push_back("7");
	list.push_back("8");
	list.push_back("9");
	list.push_back("10");
	
	list.resetIterator();	
	while (list.hasMore()) {
		cout << list.next() << endl;
	}

	list.testConnections();
	
	return 0;
}
