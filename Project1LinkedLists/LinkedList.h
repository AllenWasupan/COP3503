#include <iostream>
#include <vector>
using namespace std;

// & takes the address, * takes the value
template <typename T>
class LinkedList {

public:
	class Node {
	public:
		Node* next;
		Node* prev;
		T data;
	};

	//Behaviors
	//Prints forwards
	void PrintForward() const {
		Node* nextn = head;

		while (nextn != NULL) {
			cout << nextn->data << endl;
			nextn = nextn->next;
		}
	}
	//Prints reverse
	void PrintReverse() const {
		Node* nextn = tail;

		while (nextn != NULL) {
			cout << nextn->data << endl;
			nextn = nextn->prev;
		}
	}

	void PrintForwardRecursive(const Node* node) const {
		if (node != NULL) {
			cout << node->data << endl;
		}
		if (node->next != NULL) {
			PrintForwardRecursive(node->next);
		}
		
	}
	void PrintReverseRecursive(const Node* node) const {
		
		if (node != NULL) {
			cout << node->data << endl;
		}
		if (node->prev != NULL) {
			PrintReverseRecursive(node->prev);
		}
	}

	//Accessor
	//Returns count
	unsigned int NodeCount() const {
		return count;
	}
	//Finds many nodes with a data
	void FindAll(vector<Node*>& outData, const T &value) const {
		Node* temp = head;
		for (unsigned int i = 0; i < count; i++) {
			if (temp->data == value) {
				outData.push_back(temp);
			}
			temp = temp->next;
		}
	}
	//Find a node with a certain data
	const Node* Find(const T& data) const {
		Node* nextn = head;
		for (unsigned int i = 0; i < count; i++) {
			if (nextn->data == data) {
				return nextn;
			}
			nextn = nextn->next;
		}
		return NULL;
	}
	Node* Find(const T& data) {
		Node* nextn = head;
		for (unsigned int i = 0; i < count; i++) {
			if (nextn->data == data) {
				return nextn;
			}
			nextn = nextn->next;
		}
		return NULL;
	}
	//Find a node at a index
	const Node* GetNode(unsigned int index) const {
		if (count < index + 1) {
			throw out_of_range("Invalid Index");
		}
		else {
			Node* nextn = head;
			unsigned int c = 0;

			while (c != index) {
				nextn = nextn->next;
				c++;
				
			}
			return nextn;
		}
	}
	Node* GetNode(unsigned int index) {
		if (count < index + 1) {
			throw out_of_range("Invalid Index");
		}
		else {
			Node* nextn = head;
			unsigned int c = 0;

			while (c != index) {
				nextn = nextn->next;
				c++;
				
			}
			return nextn;
		}
	}
	//Returns head
	Node* Head() {
		return head;
	}
	const Node* Head() const {
		return head;
	}
	//Returns tail
	Node* Tail() {
		return tail;
	}
	const Node* Tail() const {
		return tail;
	}

	//Insertion
	//Add head
	void AddHead(const T& data) {
		//Initializes new head
		Node* temp = new Node();
		temp->data = data;
		temp->next = NULL;
		temp->prev = NULL;

		//If there is already a head, set its next to that head
		if (head == NULL) {
			head = temp;
			tail = temp;
			head->next = NULL;
			head->prev = NULL;
		}
		else {
			head->prev = temp;
			if (count == 1) {
				tail->prev = temp;
			}
			temp->next = head;
			head = temp;
		}
		count++;
	}
	//Add tail
	void AddTail(const T& data) {
		temp = new Node();
		temp->data = data;
		temp->next = NULL;
		temp->prev = NULL;
		//If there is already a head, set its next to that head
		if (tail == NULL) {
			head = temp;
			tail = temp;
			tail->next = NULL;
			tail->prev = NULL;
		}
		else {
			tail->next = temp;
			if (count == 1) {
				head->next = temp;
			}
			temp->prev = tail;
			temp->next = NULL;
			tail = temp;
			temp = NULL;
		}
		count++;
	}
	//Inserts after a designated node
	void InsertAfter(Node* node, const T& data) {
		Node* temp = new Node();

		temp->data = data;
		temp->prev = node;
		temp->next = node->next;

		// Update the node attributes
		node->next->prev = temp;
		node->next = temp;
		count++;
	}
	//Same but before
	void InsertBefore(Node* node, const T& data) {
		Node* temp = new Node();

		temp->data = data;
		temp->prev = node->prev;
		temp->next = node;

		// Update the node attributes
		node->prev->next = temp;
		node->prev = temp;
		count++;
	}
	//Insert node after designated index
	void InsertAt(const T& data, unsigned int index) {
		if (count < index) {
			throw out_of_range("Invalid Index");
		}
		else if (index == count) {
			AddTail(data);
		}
		else {
			//cout << "Adding: " << data << endl;
			Node* temp = new Node();
			unsigned int c = 0;
			temp->data = data;

			Node* nextn = Head();

			while (c != index) {
				nextn = nextn->next;
				c++;
			}
			temp->next = nextn;
			temp->prev = nextn->prev;

			if (nextn->prev != NULL) {
				temp->prev->next = temp;
			}
			else {
				head = temp;
			}
			nextn->prev = temp;
			count++;
		}
	}
	//Add many nodes starting from heads and tails
	void AddNodesHead(const T* data, unsigned int count) {
		int c = count;
		for (int i = c-1; i >= 0; i--) {
			AddHead(data[i]);
		}
	}

	void AddNodesTail(const T* data, unsigned int count) {

		for (unsigned int i = 0; i < count; i++) {
			AddTail(data[i]);
		}
	}
	
	//Removal
	bool RemoveHead() {
		if (head == NULL) {
			return false;
		}

		Node* temp = head;

		if (head->next == NULL) {
			delete temp;
			head = NULL;
			tail = NULL;
		}

		else {
			head->next->prev = NULL;
			head = temp->next;
			delete temp;
		}
		

		
		count--;

		return true;
	}
	bool RemoveTail() {
		if (tail == NULL) {
			return false;
		}

		Node* temp = tail;

		if (head->next == NULL) {
			delete temp;
			head = NULL;
			tail = NULL;
		}
		else {
			tail->prev->next = NULL;
			tail = temp->prev;
			delete temp;
		}

		count--;

		return true;
	}
	
	unsigned int Remove(const T& data) {
		unsigned int c = 0;
		Node* nextn = head;
		Node* temp;
		while (nextn != NULL) {

			temp = nextn->next;
			if (nextn->data == data) {
				if (nextn == head) {
					nextn->next->prev = NULL;
				}
				else if (nextn == tail) {
					nextn->prev->next = NULL;
				}
				else {
					nextn->prev->next = nextn->next;
					nextn->next->prev = nextn->prev;
					
				}
				c++;
				delete nextn;
				
			}
			nextn = temp;
		}
		count -= c;
		return c;
	}

	bool RemoveAt(unsigned int index) {
		if (index < count) {
			if (index == 0) {
				return RemoveHead();
			}
			else if (index == count) {
				return RemoveTail();
			}
			else {
				Node* temp = GetNode(index);
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
				count--;
				return true;
			}
		}
		else {
			return false;
		}
	}
	
	void Clear() {
		Node* track = Head();
		Node* temp;

		while (track != NULL) {
			temp = track->next;
			//cout << "Deleting: " << track->data << endl;
			delete track;
			track = temp;
		}

		head = NULL;
		tail = NULL;

		count = 0;
	}
	//Operators
	//Overload subscript operator, returns data from the node at index cons and non
	const T& operator[] (unsigned int index) const {
		if (index >= count) {
			throw out_of_range("Invalid Index");
		}
		else {
			unsigned int c = 0;
			Node* nextn = head;
			while (c != index) {
				c++;
				nextn = nextn->next;
			}
			return nextn->data;
		}
	}
	T& operator[] (unsigned int index) {
		if (index >= count) {
			throw out_of_range("Invalid Index");
		}
		else {
			unsigned int c = 0;
			Node* nextn = head;
			while (c != index) {
				c++;
				nextn = nextn->next;

			}
			return nextn->data;
		}
	}

	//Shows ==
	bool operator==(const LinkedList<T>& rhs) const {
		if (count != rhs.count) {
			return false;
		}
		else {
			for (unsigned int i = 0; i < count; i++) {
				if (GetNode(i)->data != rhs.GetNode(i)->data) {
					return false;
				}
			}
			return true;
		}
	}

	//Assignment Operator
	LinkedList<T> &operator= (const LinkedList<T>& rhs) {
		count = 0;
		head = NULL;
		tail = NULL;

		for (unsigned int i = 0; i < rhs.count; i++) {
			//cout << "Adding with assignment op" << rhs.GetNode(i)->data << endl;
			AddTail(rhs.GetNode(i)->data);
		}
				
		return *this;

	}

	//Constructor
	LinkedList() {
		count = 0;
		head = NULL;
		tail = NULL;
	}
	//Copy Constructor
	LinkedList(const LinkedList<T>& list) {
		count = 0;
		head = NULL;
		tail = NULL;
		for (unsigned int i = 0; i < list.count; i++) {
			//cout << "Adding with copy cons " << list.GetNode(i)->data << endl;
			AddTail(list.GetNode(i)->data);
			
		}
	}
	//Destructor
	~LinkedList() {
		Node* track = Head();
		Node* temp;

		while (track != NULL) {
			temp = track->next;
			//cout << "Deleting: " << track->data << endl;
			delete track;
			track = temp;
		}

		head = NULL;
		tail = NULL;

		count = 0;
	}

	unsigned int count;
	Node* head;
	Node* tail;
	Node* prev;
	Node* next;
	Node* nextn;
	Node* temp;
};
