/** ------------------------------------------------------------
* Tests for double linked list implementation
* Alexander Karlsson 2015-07-12
* -------------------------------------------------------------- */
#include "../doubly_linked_list.cc"
using namespace std;


int main() {
	DoublyLinkedList<int> DL;

	cout << "print empty list" << endl;
	DL.print();

	DL.push_back(0);
	DL.push_back(1);
	DL.push_back(2);
	DL.push_back(3);

	cout << "ordinary print " << endl;
	DL.print();
	cout << "rev print " << endl;
	DL.print_rev();

	cout << "push front" << endl;
	DL.push_front(-1);
	DL.push_front(-2);
	cout << "ordinary print " << endl;
	DL.print();
	cout << "rev print " << endl;
	DL.print_rev();

	/* Tests for insertAt() -------------------------------*/
	cout << "----------------------------------------------" << endl;
	cout << "insertAt() tests " << endl;
	cout << endl;

	DoublyLinkedList<int> DL2;
	cout << "insert at in an empty list" << endl;
	DL2.insertAt(0,1);
	DL2.print();
	cout << "reverse ------" << endl;
	DL2.print_rev();
	cout << "insert at index 0" << endl;
	DL2.insertAt(0,0);
	DL2.print();
	cout << "reverse ------" << endl;
	DL2.print_rev();
	cout << "insert at index > length " << endl;
	DL2.insertAt(1000,4);
	DL2.print();
	cout << "reverse ------" << endl;
	DL2.print_rev();
	cout << "insert at ordinary " << endl;
	DL2.insertAt(2,3);
	DL2.insertAt(2,2);
	DL2.print();
	cout << "reverse ------" << endl;
	DL2.print_rev();

	/* Tests for pop_front() -------------------------------*/
	cout << "----------------------------------------------" << endl;
	cout << "pop_front() tests " << endl;
	cout << endl;

	DoublyLinkedList<int> DL3;
	cout << "Test pop_front() in empty list " << endl;
	DL3.pop_front();
	DL3.print();
	cout << "reverse ------" << endl;
	DL3.print_rev();
	cout << "Test pop_front() in list with lengt == 1" << endl;
	DL3.push_back(1);
	DL3.pop_front();
	DL3.print();
	cout << "reverse ------" << endl;
	DL3.print_rev();
	cout << "Normal pop_front()" << endl;
	DL3.push_back(1);
	DL3.push_back(2);
	DL3.push_back(3);
	DL3.push_back(4);
	DL3.push_back(5);
	DL3.pop_front();
	DL3.pop_front();
	DL3.print();
	cout << "reverse ------" << endl;
	DL3.print_rev();

	/* Tests for pop_back() --------------------------------- */

	cout << "----------------------------------------------" << endl;
	cout << "pop_back() tests " << endl;
	cout << endl;
	DoublyLinkedList<int> DL4;
	cout << "Test pop_back() in empty list " << endl;
	DL4.pop_back();
	DL4.print();
	cout << "reverse ------" << endl;
	DL4.print_rev();
	cout << "Test pop_back() in list with length == 1" << endl;
	DL4.push_back(77);
	DL4.pop_back();
	DL4.print();
	cout << "reverse ------" << endl;	
	DL4.print_rev();
	cout << "Normal pop_back()" << endl;
	DL4.push_back(11);
	DL4.push_back(22);
	DL4.push_back(33);
	DL4.push_back(44);
	DL4.push_back(55);
 	DL4.push_back(66);
 	DL4.pop_back();
 	DL4.pop_back();
	DL4.pop_back();
 	DL4.print();
 	cout << "reverse ------" << endl;
 	DL4.print_rev(); 	

 	/* Tests for clear() */
 	/* Tests for removeAt(int index) -------------------------*/
 	cout << "----------------------------------------------" << endl;
	cout << "clear() tests " << endl;
	cout << endl;

	DL4.clear();
	DL4.print();
	cout << "reverse ------" << endl;
	DL4.print_rev();	


 	/* Tests for removeAt(int index) -------------------------*/
 	cout << "----------------------------------------------" << endl;
	cout << "removeAt() tests " << endl;
	cout << endl;
	DoublyLinkedList<int> DL5;
	cout << "Test removeAt in empty list" << endl;
	DL5.removeAt(0);
	DL5.removeAt(200);
	DL5.print();
	cout << "reverse ------" << endl;
	DL5.print_rev();
	cout << "Test removeAt index > length" << endl;
	DL5.push_back(1);
	DL5.push_back(2);
	DL5.removeAt(2);
	DL5.print();
	cout << "reverse ------" << endl;
	DL5.print_rev();
	cout << "Test removeAt index==lenght AND length == 1" << endl;
	DL5.pop_back();
	DL5.removeAt(0);
	DL5.print();
	cout << "reverse ------" << endl;
	DL5.print_rev();
	cout << "Test removeAt index == 0" << endl;
	DL5.push_back(666);
	DL5.push_back(1);
	DL5.push_back(2);
	DL5.push_back(3);
	DL5.removeAt(0);
	DL5.print();
	cout << "reverse ------" << endl;
	DL5.print_rev();
	cout << "Test remove at index==length-1" << endl;
	DL5.removeAt(2);
	DL5.print();
	cout << "reverse ------" << endl;
	DL5.print_rev();
	cout << "Test normal conditions" << endl;
	DL5.push_back(363);
	DL5.push_back(123);
	DL5.push_back(3);
	DL5.push_back(4);
	DL5.removeAt(2);
	DL5.removeAt(2),
	DL5.print();
	cout << "reverse ------" << endl;
	DL5.print_rev();


	/* Tests for front() and back() */
 	cout << "----------------------------------------------" << endl;
	cout << "front() and back() tests " << endl;
	cout << endl;

	DoublyLinkedList<int> DL6;
	cout << "Test front() in an empty list" << endl;
	DL6.front();
	cout << "Test back() in an empty list" << endl;
	DL6.back();
	cout << "Test front() with list length==1, e.g. front==back" << endl;
	DL6.push_back(11);
	int f = DL6.front();
	int b = DL6.back();
	cout << (f==b) << endl;


	/* Tests for at(int index) */
	cout << "----------------------------------------------" << endl;
	cout << "at(int index) tests " << endl;
	cout << endl;

	DoublyLinkedList<int> DL7;
	cout << "Test at(index) in an empty list" << endl;
	int test1 = DL7.at(0);
	cout <<  test1 << endl;
	cout << "Test at(index) where index > lenght" << endl;
	DL7.push_back(111);
	int test2 = DL7.at(1);
	cout << test2 << endl;
	cout << "Test normal at(index)" << endl;
	DL7.pop_back();
	DL7.push_back(0);
	DL7.push_back(1);
	DL7.push_back(2);
	DL7.push_back(3);
	cout << "at(1) " << DL7.at(1) << " at(2) " << DL7.at(2) << endl;



	//DONE ? :D

}