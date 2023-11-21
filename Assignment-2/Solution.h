#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

template <typename T>
class Stack {
public:
	int top;
	int capacity;
	T* arr;

	Stack() :top(-1), capacity(10), arr(new T[capacity]) { }

	void push(const T val) {
		if (top == capacity - 1) {
			T* temp = new T[capacity + 10];
			for (int i = 0; i <= top; ++i)
				temp[i] = arr[i];
			delete[] arr;
			arr = temp;
		}
		++top;
		arr[top] = val;
	}

	T pop() {
		if (top >= 0) {
			--top;
			return arr[top + 1];
		}
	}

	bool empty() { return top == -1; }

};

struct Node {
	int pos;
	Node* next;
	Node* prev;
	Node* up;
	Node* down;
	bool visited;

	Node(int posId = -1) : pos(posId), next(nullptr), prev(nullptr), up(nullptr), down(nullptr), visited(false) {}

};

class Transport_Layer_optimization {
public:
	Node* metroHead, * busHead, * walkHead, * metroTail, * busTail, * walkTail;
public:
	Transport_Layer_optimization() : metroHead(nullptr), busHead(nullptr), walkHead(nullptr),
		metroTail(nullptr), busTail(nullptr), walkTail(nullptr) {}

	Node* searchMetro(int pos) {
		Node* temp = metroHead;
		while (temp != nullptr) {
			if (temp->pos == pos) {
				return temp;
			}
			temp = temp->next;
		}
		return nullptr;
	}

	Node* searchBus(int pos) {
		Node* temp = busHead;
		while (temp != nullptr) {
			if (temp->pos == pos) {
				return temp;
			}
			temp = temp->next;
		}
		return nullptr;
	}

	Node* searchWalk(int pos) {
		Node* temp = walkHead;
		while (temp != nullptr) {
			if (temp->pos == pos) {
				return temp;
			}
			temp = temp->next;
		}
		return nullptr;
	}

	void addNode(int layer, int pos) {
		/* First checking if the location id is occupied
		* or not before adding a node.
		*/
		bool alreadyOccupied = false;
		Node* checkNode = nullptr;

		if (layer == 1)
			checkNode = searchMetro(pos);
		else if (layer == 2)
			checkNode = searchBus(pos);
		else if (layer == 3)
			checkNode = searchWalk(pos);

		if (checkNode != nullptr && checkNode->pos == pos)
			alreadyOccupied = true;

		if (alreadyOccupied) // The location provided is occupied, can't add a node to it.
			return;

		Node* newNode;
		if (layer == 1) {
			if (metroHead == nullptr) {
				newNode = new Node(pos);
				metroHead = newNode;
				metroTail = newNode;
			}
			else if (pos < metroHead->pos) {
				newNode = new Node(pos);
				newNode->next = metroHead;
				metroHead->prev = newNode;
				metroHead = newNode;
			}

			else if (pos > metroTail->pos) {
				newNode = new Node(pos);
				newNode->prev = metroTail;
				metroTail->next = newNode;
				metroTail = newNode;
			}

			else {
				Node* cur = metroHead;
				while (cur->next->pos < pos && cur->next != metroTail)
					cur = cur->next;
				newNode = new Node(pos);

				Node* nextNode = cur->next;
				newNode->next = nextNode;
				nextNode->prev = newNode;
				cur->next = newNode;
				newNode->prev = cur;
			}
			Node* busTemp = searchBus(pos);
			if (busTemp != nullptr) {
				newNode->down = busTemp;
				busTemp->up = newNode;
			}
		}
		else if (layer == 2) {
			if (busHead == nullptr) {
				newNode = new Node(pos);
				busHead = newNode;
				busTail = newNode;
			}
			else if (pos < busHead->pos) {
				newNode = new Node(pos);
				newNode->next = busHead;
				busHead->prev = newNode;
				busHead = newNode;
			}

			else if (pos > busTail->pos) {
				newNode = new Node(pos);
				newNode->prev = busTail;
				busTail->next = newNode;
				busTail = newNode;
			}

			else {
				Node* cur = busHead;
				while (cur->next->pos < pos && cur->next != busTail)
					cur = cur->next;
				newNode = new Node(pos);

				Node* nextNode = cur->next;
				newNode->next = nextNode;
				nextNode->prev = newNode;
				cur->next = newNode;
				newNode->prev = cur;
			}
			Node* walkTemp = searchWalk(pos);
			if (walkTemp != nullptr) {
				newNode->down = walkTemp;
				walkTemp->up = newNode;
			}

			Node* metroTemp = searchMetro(pos);
			if (metroTemp != nullptr) {
				metroTemp->down = newNode;
				newNode->up = metroTemp;
			}
		}
		else if (layer == 3) {
			if (walkHead == nullptr) {
				newNode = new Node(pos);
				walkHead = newNode;
				walkTail = newNode;
			}
			else if (pos < walkHead->pos) {
				newNode = new Node(pos);
				newNode->next = walkHead;
				walkHead->prev = newNode;
				walkHead = newNode;
			}
			else if (pos > walkTail->pos) {
				newNode = new Node(pos);
				newNode->prev = walkTail;
				walkTail->next = newNode;
				walkTail = newNode;
			}
			else {
				Node* cur = walkHead;
				while (cur->next->pos < pos && cur->next != walkTail)
					cur = cur->next;
				newNode = new Node(pos);

				Node* nextNode = cur->next;
				newNode->next = nextNode;
				nextNode->prev = newNode;
				cur->next = newNode;
				newNode->prev = cur;
			}

			Node* busTemp = searchBus(pos);
			if (busTemp != nullptr) {
				busTemp->down = newNode;
				newNode->up = busTemp;
			}
		}
	}

	void ReadFile(string path) {
		std::ifstream file(path);

		if (!file.is_open()) {
			cout << "Error opening file: " << path << endl;
			return;
		}

		int metroNodes, busNodes, walkNodes;
		if (!(file >> metroNodes >> busNodes >> walkNodes)) {
			cout << "Error reading the number of nodes in each layer." << endl;
			return;
		}

		for (int i = 0; i < metroNodes; ++i) {
			int nodeValue;
			if (!(file >> nodeValue)) {
				cout << "Error reading metroHead value.\n";
				return;
			}
			addNode(1, nodeValue);
		}

		for (int i = 0; i < busNodes; ++i) {
			int nodeValue;
			if (!(file >> nodeValue)) {
				cout << "Error reading busHead value.\n";
				return;
			}
			addNode(2, nodeValue);
		}

		for (int i = 0; i < walkNodes; ++i) {
			int nodeValue;
			if (!(file >> nodeValue)) {
				cout << "Error reading walkNode value.\n";
			}
			addNode(3, nodeValue);
		}

		file.close();
	}

	void DeleteNode(int layer, int pos) {
		Node* temp = nullptr;

		if (layer == 1)
			temp = searchMetro(pos);
		else if (layer == 2)
			temp = searchBus(pos);
		else
			temp = searchWalk(pos);

		if (temp == nullptr) {
			cout << "Attempt to delete null node.\n";
			return;
		}

		if (temp->next != nullptr)
			temp->next->prev = temp->prev;

		if (temp->prev != nullptr)
			temp->prev->next = temp->next;

		if (temp->up != nullptr)
			temp->up->down = nullptr;

		if (temp->down != nullptr)
			temp->down->up = nullptr;

		// Update head and tail pointers if necessary
		if (layer == 1 && temp == metroHead) {
			metroHead = temp->next;
			if (metroHead != nullptr)
				metroHead->prev = nullptr;
			if (temp == metroTail)
				metroTail = nullptr;
		}

		if (layer == 2 && temp == busHead) {
			busHead = temp->next;
			if (busHead != nullptr)
				busHead->prev = nullptr;
			if (temp == busTail)
				busTail = nullptr;
		}

		if (layer == 3 && temp == walkHead) {
			walkHead = temp->next;
			if (walkHead != nullptr)
				walkHead->prev = nullptr;
			if (temp == walkTail)
				walkTail = nullptr;
		}

		delete temp;
	}


	string GetPath(int start, int end) {
		bool prio = (start > end) ? 0 : 1;
		Stack<string> path;
		Node* pathing = searchMetro(start);
		int pathingLayer = 1;
		bool deadEnd = false;

		if (pathing == nullptr) {
			pathing = searchBus(start);
			pathingLayer = 2;
		}
		if (pathing == nullptr) {
			pathing = searchWalk(start);
			pathingLayer = 3;
		}

		while (pathing->pos != end) {

			if (!deadEnd && (!pathing->prev || pathing->prev->visited || abs(pathing->prev->pos - pathing->pos) != 1) && (!pathing->up || pathing->up->visited) && (
				!pathing->next || pathing->next->visited || abs(pathing->next->pos - pathing->pos) != 1) && (!pathing->down || pathing->down->visited)) {
				deadEnd = true;
			}

			if (deadEnd) {
				if (prio == 1) {
					if (pathing->prev && abs(pathing->prev->pos - pathing->pos) == 1 && pathing->prev->visited) {
						pathing = pathing->prev;
						path.pop();
					}
				}
				else if (prio == 0) {
					if (pathing->next && abs(pathing->next->pos - pathing->pos) == 1 && pathing->next->visited) {
						pathing = pathing->next;
						path.pop();
					}
				}

				if (pathing->up) {
					if (pathing->up->visited)
						path.pop();
					pathing = pathing->up;

					if (!pathing->visited)
						path.push(to_string(pathing->pos) + "-" + to_string(pathingLayer) + " -> " + to_string(pathing->down->pos) + "-" + to_string(
					pathingLayer -1));
					--pathingLayer;

					pathing->down->visited = true;
					if (prio == 1) {
						if (pathing->next && abs(pathing->next->pos - pathing->pos) == 1)
							pathing->next->visited = true;
						if (pathing->prev && abs(pathing->prev->pos - pathing->pos) == 1)
							pathing->prev->visited = false;
					}
					else if (prio == 0) {
						if (pathing->next && abs(pathing->next->pos - pathing->pos) == 1)
							pathing->next->visited = false;
						if (pathing->prev && abs(pathing->prev->pos - pathing->pos) == 1)
							pathing->prev->visited = true;
					}
					deadEnd = false;
				}	
				else if (pathing->down) {
					if (pathing->down->visited)
						path.pop();
					pathing = pathing->down;
					if (!pathing->visited)
						path.push(to_string(pathing->pos) + "-" + to_string(pathingLayer) + " -> " + to_string(pathing->down->pos) + "-" + to_string(
					pathingLayer + 1));

					++pathingLayer;

					pathing->up->visited = true;

					if (prio == 1) {
						if (pathing->next && abs(pathing->next->pos - pathing->pos) == 1)
							pathing->next->visited = true;
						if (pathing->prev && abs(pathing->prev->pos - pathing->pos) == 1)
							pathing->prev->visited = false;
					}
					else if (prio == 0) {
						if (pathing->next && abs(pathing->next->pos - pathing->pos) == 1)
							pathing->next->visited = false;
						if (pathing->prev && abs(pathing->prev->pos - pathing->pos) == 1)
							pathing->prev->visited = true;
					}
					deadEnd = false;
				}
				continue;
			}

			if (pathingLayer == 1) {
				if (prio) {
					if (pathing->next != nullptr && abs(pathing->next->pos - pathing->pos) == 1 && !pathing->next->visited) {
						pathing->next->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-1 -> " + to_string(pathing->next->pos) + "-1");
						pathing = pathing->next;
					}
					else if (pathing->down != nullptr && pathing->down->visited == false) {
						pathing->down->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-1 -> " + to_string(pathing->down->pos) + "-2");
						pathing = pathing->down;
						++pathingLayer;
					}
					else if (pathing->prev != nullptr && abs(pathing->prev->pos - pathing->pos) == 1 && !pathing->prev->visited) {
						pathing->prev->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-1 -> " + to_string(pathing->prev->pos) + "-1");
						pathing = pathing->prev;
					}
					else {
						path.pop();
					}
				}
				else {
					// Swap the order of checks
					if (pathing->prev != nullptr && abs(pathing->prev->pos - pathing->pos) == 1 && !pathing->prev->visited) {
						pathing->prev->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-1 -> " + to_string(pathing->prev->pos) + "-1");
						pathing = pathing->prev;
					}
					else if (pathing->down != nullptr && !pathing->down->visited) {
						pathing->down->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-1 -> " + to_string(pathing->down->pos) + "-2");
						pathing = pathing->down;
						++pathingLayer;
					}
					else if (pathing->next != nullptr && abs(pathing->next->pos - pathing->pos) == 1 && !pathing->next->visited) {
						pathing->next->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-1 -> " + to_string(pathing->next->pos) + "-1");
						pathing = pathing->next;
					}
					else {
						path.pop();
					}
				}
			}
			
			else if (pathingLayer == 2) {
				if (prio) {
					if (pathing->up && !pathing->up->visited) {
						pathing->up->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-2 -> " + to_string(pathing->up->pos) + "-1");
						--pathingLayer;
						pathing = pathing->up;
					}
					else if (pathing->next && abs(pathing->next->pos - pathing->pos) == 1 && !pathing->next->visited) {
						pathing->next->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-2 -> " + to_string(pathing->next->pos) + "-2");
						pathing = pathing->next;
					}
					else if (pathing->down && !pathing->down->visited) {
						pathing->down->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-2 -> " + to_string(pathing->down->pos) + "-3");
						pathing = pathing->down;
						++pathingLayer;
					}
					else if (pathing->prev != nullptr && abs(pathing->prev->pos - pathing->pos) == 1 && !pathing->prev->visited) {
						pathing->prev->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-2 -> " + to_string(pathing->prev->pos) + "-2");
						pathing = pathing->prev;
					}
					else {
						path.pop();
					}
				}
				else {
					// Swap the order of checks
					if (pathing->up && !pathing->up->visited) {
						pathing->up->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-2 -> " + to_string(pathing->up->pos) + "-1");
						--pathingLayer;
						pathing = pathing->up;
					}

					else if (pathing->prev != nullptr && abs(pathing->prev->pos - pathing->pos) == 1 && !pathing->prev->visited) {
						pathing->prev->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-2 -> " + to_string(pathing->prev->pos) + "-2");
						pathing = pathing->prev;
					}

					else if (pathing->down && !pathing->down->visited) {
						pathing->down->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-2 -> " + to_string(pathing->down->pos) + "-3");
						pathing = pathing->down;
						++pathingLayer;
					}

					else if (pathing->next && abs(pathing->next->pos - pathing->pos) == 1 && !pathing->next->visited) {
						pathing->next->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-2 -> " + to_string(pathing->next->pos) + "-2");
						pathing = pathing->next;
					}
					else {
						path.pop();
					}
				}
			}

			else if (pathingLayer == 3) {
				if (prio) {
					if (pathing->up && !pathing->up->visited) {
						pathing->up->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-3 -> " + to_string(pathing->up->pos) + "-2");
						pathing = pathing->up;
						--pathingLayer;
					}
					else if (pathing->next && abs(pathing->next->pos - pathing->pos) == 1 && !pathing->next->visited) {
						pathing->next->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-3 -> " + to_string(pathing->next->pos) + "-3");
						pathing = pathing->next;
					}
					else if (pathing->prev != nullptr && abs(pathing->prev->pos - pathing->pos) == 1 && !pathing->prev->visited) {
						pathing->prev->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-3 -> " + to_string(pathing->prev->pos) + "-3");
						pathing = pathing->prev;
					}
					else {
						path.pop();
					}
				}
				else {
					// Swap the order of checks
					if (pathing->up && !pathing->up->visited) {
						pathing->up->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-3 -> " + to_string(pathing->up->pos) + "-2");
						pathing = pathing->up;
						--pathingLayer;
					}

					else if (pathing->prev != nullptr && abs(pathing->prev->pos - pathing->pos) == 1 && !pathing->prev->visited) {
						pathing->prev->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-3 -> " + to_string(pathing->prev->pos) + "-3");
						pathing = pathing->prev;
					}

					else if (pathing->next && abs(pathing->next->pos - pathing->pos) == 1 && !pathing->next->visited) {
						pathing->next->visited = true;
						pathing->visited = true;
						path.push(to_string(pathing->pos) + "-3 -> " + to_string(pathing->next->pos) + "-3");
						pathing = pathing->next;
					}
					else {
						path.pop();
					}
				}
			}
		}

		string temp = "";
		for (int i = 0; i <= path.top; ++i) {
			if (i == 0)
				temp.append(path.arr[i]);
			else {
				if (!(path.arr[i][1] >= '0' && path.arr[i][1] <= '9'))
					temp.append(path.arr[i].substr(4));
				else
					temp.append(path.arr[i].substr(5));
			}
			temp += " ";
		}
		temp.erase(temp.size() - 1);
		return temp;
	}
};