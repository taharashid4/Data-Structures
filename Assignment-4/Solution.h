#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

template <typename T>
class QueueNode {
public:
    T data;
    QueueNode* next;

    QueueNode(T d = NULL) : data(d), next(nullptr) {}
};

template <typename T>
class Queue {
public:
    QueueNode<T>* front;
    QueueNode<T>* rear;

    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(T item) {
        QueueNode<T>* newNode = new QueueNode<T>(item);

        if (front == nullptr)
            front = newNode;

        if (rear == nullptr)
            rear = newNode;
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    T dequeue() {
        if (front == nullptr) {
            return NULL;
        }
        else if (front == rear) {
            T temp = front->data;
            delete front;
            front = nullptr;
            rear = nullptr;
            return temp;
        }
        else {
            T temp = front->data;
            QueueNode<T>* nextNode = front->next;
            delete front;
            front = nextNode;
            return temp;
        }
    }

    T peek() {
        if (front == nullptr)
            return NULL;
        else
            return front->data;
    }

    bool is_empty() { return front == nullptr; }

    int size() {
        int size = 0;
        QueueNode<T>* temp = front;
        while (temp) {
            ++size;
            temp = temp->next;
        }
        return size;
    }

    void clear() {
        int s = size();
        for (int i = 0; i < s; ++i) {
            QueueNode<T>* temp = front;
            front = front->next;
            delete temp;
        }
    }

    ~Queue() { clear(); }

};

struct Task {
    int mTaskId;
    std::string mDescription;
    int mPrio;
    std::string mAssigneeID;
    bool bCompleted;

    Task(int id, std::string desc, int prio, std::string ID, bool comp = false) : mTaskId(id), mDescription(desc), mPrio(prio), mAssigneeID(ID), bCompleted(comp) {}

    Task(const Task& rhs) {
        mTaskId = rhs.mTaskId;
        mDescription = rhs.mDescription;
        mPrio = rhs.mPrio;
        mAssigneeID = rhs.mAssigneeID;
        bCompleted = rhs.bCompleted;
    }

    bool operator<(const Task& rhs) const {
        return mPrio < rhs.mPrio;
    }

    bool operator>(const Task& rhs) const {
        return mPrio > rhs.mPrio;
    }

    bool operator==(const Task& rhs) const {
        return mPrio == rhs.mPrio;
    }

    bool operator>=(const Task& rhs) const {
        return mPrio >= rhs.mPrio;
    }

    friend ostream& operator<<(ostream& out, const Task& task) {
        out << "Task ID: " << task.mTaskId << ", ";
        out << "Description: " << task.mDescription << ", ";
        out << "Priority: " << task.mPrio << ", ";
        out << "Assignee: ";
        return out;
    }
};

struct Assignee {
    std::string mFirstName;
    std::string mLastName;
    std::string mAddress;
    std::string mDOB;
    std::string mAssigneeId;
    int mIntId;

    Assignee(std::string fN, std::string lN, std::string addr,
        std::string dob, int numAssignees) : mFirstName(fN), mLastName(lN), mAddress(addr),
        mDOB(dob) {
        mAssigneeId = "A";
        if (numAssignees < 10)
            mAssigneeId += "00" + std::to_string(numAssignees);
        else if (numAssignees >= 10 && numAssignees < 100)
            mAssigneeId += "0" + std::to_string(numAssignees);
        else if (numAssignees > 100)
            mAssigneeId += std::to_string(numAssignees);
        mIntId = numAssignees;
    }

    Assignee(const Assignee& rhs) {
        mFirstName = rhs.mFirstName;
        mLastName = rhs.mLastName;
        mAddress = rhs.mAddress;
        mDOB = rhs.mDOB;
        mAssigneeId = rhs.mAssigneeId;
        mIntId = rhs.mIntId;
    }

    bool operator<(const Assignee& rhs) const {
        return mIntId < rhs.mIntId;
    }

    bool operator>(const Assignee& rhs) const {
        return mIntId > rhs.mIntId;
    }

    bool operator==(const Assignee& rhs) const {
        return mIntId == rhs.mIntId;
    }

    bool operator>=(const Assignee& rhs) const {
        return mIntId >= rhs.mIntId;
    }

    friend ostream& operator<<(ostream& output, const Assignee& assignee) {
        output << "Name: " << assignee.mFirstName << " " << assignee.mLastName << ", ";
        output << "Address: " << assignee.mAddress << ", ";
        output << "DOB: " << assignee.mDOB << ", ";
        output << "Assignee ID: " << assignee.mAssigneeId << "\n";
        return output;
    }
};

template <typename T>
struct Node {
    T mData;
    Node* pLeft, * pRight, * pParent;
    bool bBlack, bDoubleBlack;
    Node(T data) : mData(data), pLeft(nullptr), pRight(nullptr), pParent(nullptr), bBlack(false), bDoubleBlack(false) {}
};

template <typename T>
class RedBlackTree {
public:

    Node<T>* mRoot;
    int numNodes;

    RedBlackTree() : mRoot(nullptr), numNodes(0) {}

    void insert(T data) {
        insertNode(mRoot, data);
    }

    void remove(T data) {
        deleteNode(mRoot, data);
    }



    void insertNode(Node<Assignee>*& node, Assignee data) {
        if (node == nullptr) {
            ++numNodes;
            node = new Node<T>(data);
            rebalanceTree(node);
            return;
        }
        else if (data < node->mData) {
            if (node->pLeft == nullptr) {
                ++numNodes;
                node->pLeft = new Node<T>(data);
                node->pLeft->pParent = node;
                rebalanceTree(node->pLeft);
                return;
            }
            else if (node->pLeft != nullptr) {
                insertNode(node->pLeft, data);
            }
        }
        else if (data > node->mData) {
            if (node->pRight == nullptr) {
                ++numNodes;
                node->pRight = new Node<T>(data);
                node->pRight->pParent = node;
                rebalanceTree(node->pRight);
                return;
            }
            else if (node->pRight != nullptr) {
                insertNode(node->pRight, data);
            }
        }        
    }

    void insertNode(Node<Task>*& node, Task data) {
        if (node == nullptr) {
            ++numNodes;
            node = new Node<T>(data);
            rebalanceTree(node);
            return;
        }
        else if (data < node->mData) {
            if (node->pLeft == nullptr) {
                ++numNodes;
                node->pLeft = new Node<T>(data);
                node->pLeft->pParent = node;
                rebalanceTree(node->pLeft);
                return;
            }
            else if (node->pLeft != nullptr) {
                insertNode(node->pLeft, data);
            }
        }
        else if (data > node->mData) {
            if (node->pRight == nullptr) {
                ++numNodes;
                node->pRight = new Node<T>(data);
                node->pRight->pParent = node;
                rebalanceTree(node->pRight);
                return;
            }
            else if (node->pRight != nullptr) {
                insertNode(node->pRight, data);
            }
        }
        else if (data == node->mData) {
            if (data.mTaskId < node->mData.mTaskId) {
                if (node->pLeft == nullptr) {
                    ++numNodes;
                    node->pLeft = new Node<T>(data);
                    node->pLeft->pParent = node;
                    rebalanceTree(node->pLeft);
                    return;
                }
                else if (node->pLeft != nullptr) {
                    insertNode(node->pLeft, data);
                }
            }
            else if (data.mTaskId > node->mData.mTaskId) {
                if (node->pRight == nullptr) {
                    ++numNodes;
                    node->pRight = new Node<T>(data);
                    node->pRight->pParent = node;
                    rebalanceTree(node->pRight);
                    return;
                }
                else if (node->pRight != nullptr) {
                    insertNode(node->pRight, data);
                }
            }
        }
    }

    void rotateRight(Node<T>*& node) {
        Node<T>* swapNode = node->pLeft;
        node->pLeft = swapNode->pRight;

        if (swapNode->pRight) // Updating the parent of the new subtree
            swapNode->pRight->pParent = node;

        swapNode->pRight = node;

        if (node->pParent) { // Updating the child connection that the old parent had
            if (node->mData < node->pParent->mData) {
                node->pParent->pLeft = swapNode;
            }
            else {
                node->pParent->pRight = swapNode;
            }
        }
        else
            mRoot = swapNode;

        Node<T>* tempParent = node->pParent; // Updating the parent connection that the old node had
        node->pParent = swapNode;
        swapNode->pParent = tempParent;

        node = swapNode;
    }

    void rotateLeft(Node<T>*& node) {

        Node<T>* swapNode = node->pRight;
        node->pRight = swapNode->pLeft;

        if (swapNode->pLeft) // Updating the parent of the new subtree
            swapNode->pLeft->pParent = node;

        swapNode->pLeft = node;

        if (node->pParent) { // Updating the child connection that the old parent had
            if (node->mData < node->pParent->mData) {
                node->pParent->pLeft = swapNode;
            }
            else {
                node->pParent->pRight = swapNode;
            }
        }
        else
            mRoot = swapNode;

        Node<T>* tempParent = node->pParent; // Updating the parent connection that the old node had
        node->pParent = swapNode;
        swapNode->pParent = tempParent;

        node = swapNode;
    }

    void rebalanceTree(Node<T>*& node) {
        if (node == mRoot) {
            node->bBlack = true;
            return;
        }
        else {
            node->bBlack = false; // Make the node red
            Node<T>* parent = node->pParent;

            if (parent->bBlack == false) {

                Node<T>* grandParent = node->pParent->pParent;
                Node<T>* uncle = parent->mData < grandParent->mData ? grandParent->pRight : grandParent->pLeft;


                if (uncle && uncle->bBlack == false) { // In the case that the uncle is red and we have a double red
                    parent->bBlack = true;
                    uncle->bBlack = true;

                    if (grandParent != mRoot)
                        grandParent->bBlack = false;

                    if (grandParent == mRoot || grandParent->pParent->bBlack == false)
                        rebalanceTree(grandParent);
                }
                else if (uncle == nullptr || uncle && uncle->bBlack) { // The uncle is black and we have a double red
                    if (node->mData < parent->mData && parent->mData < grandParent->mData) { // LL Rotation
                        grandParent->bBlack = false;
                        parent->bBlack = true;
                        rotateRight(grandParent);
                    }
                    else if (node->mData >= parent->mData && parent->mData < grandParent->mData) { // LR Rotation
                        rotateLeft(parent);
                        grandParent->bBlack = false;
                        parent->bBlack = true;
                        rotateRight(grandParent);
                    }
                    else if (node->mData >= parent->mData && parent->mData >= grandParent->mData) { // RR Rotation
                        grandParent->bBlack = false;
                        parent->bBlack = true;
                        rotateLeft(grandParent);
                    }
                    else if (node->mData < parent->mData && parent->mData > grandParent->mData) { // RL Rotation
                        rotateRight(parent);
                        grandParent->bBlack = false;
                        parent->bBlack = true;
                        rotateLeft(grandParent);
                    }
                }
            }
        }
    }

    void deleteNode(Node<T>*& node, T data) {
        if (node == nullptr) {
            throw std::runtime_error("Value not found\n");
        }
        else if (data < node->mData)
            deleteNode(node->pLeft, data);
        else if (data > node->mData)
            deleteNode(node->pRight, data);
        else if (data == node->mData)
            makeDeletion(node);
    }

    void makeDeletion(Node<T>*& node) {
        int numChildren = 0;
        if (node->pLeft)
            ++numChildren;
        if (node->pRight)
            ++numChildren;

        if (numChildren <= 1) {

            if (node->bBlack == true && ((!node->pLeft && !node->pRight) || (node->pLeft && node->pLeft->bBlack == true) || (node->pRight && node->pRight->bBlack == true)))
                node->bDoubleBlack = true;

            if (node->pLeft == nullptr && node->pRight != nullptr) { // One child
                Node<T>* temp = node;
                node = node->pRight;
                node->pParent = temp->pParent;
                node->pParent->pRight = node;
                delete temp;
            }
            else if (node->pLeft != nullptr && node->pRight == nullptr) { // One child
                Node<T>* temp = node;
                node = node->pLeft;
                node->pParent = temp->pParent;
                node->pParent->pLeft = node;
                delete temp;
            }

            else if (node->pLeft == nullptr && node->pRight == nullptr) { // No children
                if (node->bBlack == false) {

                    if (node && node->pParent->pLeft == node)
                        node->pParent->pLeft = nullptr;
                    else if (node && node->pParent->pRight == node)
                        node->pParent->pRight = nullptr;

                    delete node;
                    node = nullptr;

                    return;
                }
                else if (node == mRoot) {
                    delete node;
                    node = nullptr;
                    return;
                }
            }

            balanceDeletion(node, node->bDoubleBlack);
        }
        else {
            Node<T>* highestLeft = node->pLeft;
            while (highestLeft->pRight != nullptr)
                highestLeft = highestLeft->pRight;

            T temp = highestLeft->mData;
            highestLeft->mData = node->mData;
            node->mData = temp;
            makeDeletion(highestLeft);
        }
    }

    void balanceDeletion(Node<T>*& node, bool doubleBlack) {
        if (node->bBlack == false)
            node->bBlack = true;
        else if (node != mRoot && doubleBlack) {
            resolveDoubleBlack(node);
        }
    }

    void resolveDoubleBlack(Node<T>*& node) {
        Node<T>* sibling = node->pParent->pLeft != node ? node->pParent->pLeft : node->pParent->pRight;
        Node<T>* parent = node->pParent;
        if (sibling->bBlack) {

            // Case 1: The sibling of the deleted node has at least one red child. If it has more than one red child,
            // then we simply perform the LL or RR rotation just like if the one-red-child case where it is on the 
            // outside. If it has only one red child and it's located on the inside subtree, then we perform the LR or RL rotation.

            if ((sibling->pLeft && sibling->pLeft->bBlack == false) || (sibling->pRight && sibling->pRight->bBlack == false)) {

                Node<T>* redChild = nullptr;

                if (sibling->mData < parent->mData && (sibling->pLeft && sibling->pLeft->bBlack == false)) { // LL rotation 

                    // The parent and red newphew are turned to black, and the sibling is turned to parent's previous color
                    sibling->pLeft->bBlack = true;
                    sibling->bBlack = parent->bBlack;
                    parent->bBlack = true;

                    rotateRight(parent);
                }

                else if (sibling->mData < parent->mData && (sibling->pRight && sibling->pRight->bBlack == false)) { // LR rotation
                    sibling->pRight->bBlack = true;
                    sibling->bBlack = parent->bBlack;
                    parent->bBlack = true;
                    rotateLeft(sibling);
                    rotateRight(parent);

                }

                else if (sibling->mData > parent->mData && (sibling->pRight && sibling->pRight->bBlack == false)) { // RR rotation

                    sibling->pRight->bBlack = true;
                    sibling->bBlack = parent->bBlack;
                    parent->bBlack = true;

                    rotateLeft(parent);
                }

                else if (sibling->mData > parent->mData && (sibling->pLeft && sibling->pLeft->bBlack == false)) { // RL rotation
                    sibling->pLeft->bBlack = true;
                    sibling->bBlack = parent->bBlack;
                    parent->bBlack = true;
                    rotateRight(sibling);
                    rotateLeft(parent);
                }
            }

            // Case 2: The sibling of the deleted node has no red children.
            else {
                sibling->bBlack = false;
                if (parent->bBlack == false) // Case 2a: The parent is red
                    parent->bBlack = true;
                else if (parent->bBlack && parent != mRoot) // Case 2b: The parent is black
                    resolveDoubleBlack(parent);
            }
        }
        else {
            // Case 3: The sibling of the deleted node is red
            sibling->bBlack = true;
            parent->bBlack = false;

            if (sibling->mData < parent->mData)
                rotateRight(parent);
            else
                rotateLeft(parent);

            resolveDoubleBlack(node);
        }

        if (node == mRoot)
            node->bBlack = true;

        else if (node && node->bDoubleBlack) {
            if (node && node->pParent->pLeft == node)
                node->pParent->pLeft = nullptr;
            else if (node && node->pParent->pRight == node)
                node->pParent->pRight = nullptr;
            delete node;
            node = nullptr;
        }
    }

    bool search(Node<T>*& node, T data) {
        if (node == nullptr)
            return false;
        else if (node->mData < data)
            return search(node->pRight, data);
        else if (node->mData > data)
            return search(node->pLeft, data);
        else if (node->mData == data)
            return true;
    }
};

int idToInt(std::string assigneeID) {
    // A000 -> 0
    // A010 -> 10
    // A110 -> 110
    int pow = 0;
    int num = 0;
    while (assigneeID[3 - pow] != 'A') {
        num += (assigneeID[3 - pow] - '0') * std::pow(10, pow);
        ++pow;
    }
    return num;
}

class taskManagementSystem {
public:
    RedBlackTree<Task> mTaskTree;
    RedBlackTree<Assignee> mAssigneeTree;

    taskManagementSystem() : mTaskTree(), mAssigneeTree() {}



    void addAssignee(std::string fN, std::string lN, std::string addr, std::string dob) {
        mAssigneeTree.insert(Assignee{ fN, lN, addr, dob, mAssigneeTree.numNodes + 1 });
    }

    void displayID(Node<Assignee>*& node, std::string ID, std::ostream& out) {
        if (node == nullptr) {
            throw std::runtime_error("Value not found\n");
        }
        else if (ID < node->mData.mAssigneeId)
            displayID(node->pLeft, ID, out);
        else if (ID > node->mData.mAssigneeId)
            displayID(node->pRight, ID, out);
        else if (ID == node->mData.mAssigneeId)
            out << node->mData;
    }

    void displaybyID(std::ostream& output, std::string ID) {
        displayID(mAssigneeTree.mRoot, ID, output);
    }

    void inorderNames(Node<Assignee>*& node, std::string firstName, std::string lastName, std::ostream& out) {
        if (node) {
            inorderNames(node->pLeft, firstName, lastName, out);
            if (node->mData.mFirstName == firstName && node->mData.mLastName == lastName)
                out << node->mData;
            inorderNames(node->pRight, firstName, lastName, out);
        }
    }

    void displaybyname(std::ostream& output, std::string firstName, std::string lastName) {
        inorderNames(mAssigneeTree.mRoot, firstName, lastName, output);
    }

    void addTask(int id, std::string desc, int prio, std::string assigneeID) {
        mTaskTree.insert(Task{ id, desc, prio, assigneeID});
    }

    void assigneeHasTask(Node<Task>*& node, std::string assigneeID, bool& hasTask) {
        if (node) {
            assigneeHasTask(node->pLeft, assigneeID, hasTask);
            if (node->mData.mAssigneeID == assigneeID)
                hasTask = true;
            assigneeHasTask(node->pRight, assigneeID, hasTask);
        }
    }

    void displayNoTasks(Node<Assignee>*& node, ostream& out) {
        if (node) {
            displayNoTasks(node->pLeft, out);

            bool hasTask = false;
            assigneeHasTask(mTaskTree.mRoot, node->mData.mAssigneeId, hasTask);
            if (!hasTask)
                out << node->mData;

            displayNoTasks(node->pRight, out);
        }
    }

    void AssigneeWithNoTask(std::ostream& out) {
        displayNoTasks(mAssigneeTree.mRoot, out);
    }

    void shiftTasksInOrder(Node<Task>*& node, std::string leftAssignee, std::string rightAssignee) {
        if (node) {
            shiftTasksInOrder(node->pLeft, leftAssignee, rightAssignee);

            if (node->mData.mAssigneeID == leftAssignee && node->mData.bCompleted == false)
                node->mData.mAssigneeID = rightAssignee;

            shiftTasksInOrder(node->pRight, leftAssignee, rightAssignee);
        }
    }

    void ShiftTask(std::string leftAssignee, std::string rightAssignee) {
        shiftTasksInOrder(mTaskTree.mRoot, leftAssignee, rightAssignee);
    }

    std::string getAssigneeName(std::string id) {
        Node<Assignee>* traverse = mAssigneeTree.mRoot;
        while (traverse != nullptr) {
            if (traverse->mData.mAssigneeId < id)
                traverse = traverse->pRight;
            else if (traverse->mData.mAssigneeId > id)
                traverse = traverse->pLeft;
            else if (traverse->mData.mAssigneeId == id)
                return traverse->mData.mFirstName;
        }
        throw std::runtime_error("Assignee not found\n");
    }

    void printTasksInOrder(Node<Task>*& node, std::ostream& out) {
        if (node) {
            printTasksInOrder(node->pLeft, out);

            if (node->mData.bCompleted == false)
                out << node->mData << getAssigneeName(node->mData.mAssigneeID) << " (" << node->mData.mAssigneeID << ")\n";

            printTasksInOrder(node->pRight, out);
        }
    }

    void printTaskQueue(std::ostream& out) {
        printTasksInOrder(mTaskTree.mRoot, out);
    }

    void DeleteAssignee(std::string assigneeID) {
        bool hasTask = false;
        assigneeHasTask(mTaskTree.mRoot, assigneeID, hasTask);
        if (!hasTask)
            mAssigneeTree.deleteNode(mAssigneeTree.mRoot, Assignee{ "", "", "", "", idToInt(assigneeID) });
    }

    void fullAssigneeInOrder(Node<Assignee>*& node, std::ostream& out) {
        if (node) {
            fullAssigneeInOrder(node->pLeft, out);
            out << node->mData;
            fullAssigneeInOrder(node->pRight, out);
        }
    }

    void DisplayAssignee(std::ostream& out) {
        fullAssigneeInOrder(mAssigneeTree.mRoot, out);
    }

    void assigneeIdsInOrder(Node<Assignee>*& node, std::ostream& out) {
        if (node) {
            assigneeIdsInOrder(node->pLeft, out);

            out << node->mData.mAssigneeId << " (";
            if (node->bBlack)
                out << "black)\n";
            else
                out << "red)\n";

            assigneeIdsInOrder(node->pRight, out);
        }
    }

    void AssigneeInOrder(std::ostream& out) {
        assigneeIdsInOrder(mAssigneeTree.mRoot, out);
    }

    Node<Task>*& searchById(int taskID) {
        // Level-wise traversal since that's the only way I can think of to check each node
        Queue<Node<Task>*> nodeQueue;
        nodeQueue.enqueue(mTaskTree.mRoot);

        while (!nodeQueue.is_empty()) {
            Node<Task>* curr = nodeQueue.peek();
            nodeQueue.dequeue();

            if (curr == nullptr) {
                continue;
            }
            else if (curr->mData.mTaskId == taskID) {
                return curr;
            }

            if (curr->pLeft) {
                nodeQueue.enqueue(curr->pLeft);
            }

            if (curr->pRight) {
                nodeQueue.enqueue(curr->pRight);
            }
        }

        cout << '\n';
    }

    void completeTask(int taskID) {
        Node<Task>* completedTask = searchById(taskID);

        if (completedTask != nullptr) {
            completedTask->mData.bCompleted = true;
            mTaskTree.numNodes--;
        }
        else
            throw std::runtime_error("Task not found\n");
    }

    void updateTaskPriority(int taskID, int newPrio) {
        Node<Task>* swapPrio = searchById(taskID);
        if (swapPrio && swapPrio->mData.bCompleted == false) {
            Task temp = swapPrio->mData;
            mTaskTree.deleteNode(mTaskTree.mRoot, swapPrio->mData);
            temp.mPrio = newPrio;
            mTaskTree.insert(Task{ temp.mTaskId, temp.mDescription, temp.mPrio, temp.mAssigneeID, temp.bCompleted});
        }
    }

    void deleteTask(int taskID) {
        Node<Task>* taskToDelete = searchById(taskID);
        if (taskToDelete->mData.bCompleted == false)
            mTaskTree.numNodes--;
        mTaskTree.deleteNode(mTaskTree.mRoot, taskToDelete->mData);
    }

    void printAllTasksWithPrio(Node<Task>*& node, int prio, std::ostream& out) {
        if (node) {
            printAllTasksWithPrio(node->pLeft, prio, out);

            if (node->mData.mPrio == prio && node->mData.bCompleted == false)
                out << "Highest Priority Task: " << node->mData << getAssigneeName(node->mData.mAssigneeID) << " (" << node->mData.mAssigneeID << ")\n";

            printAllTasksWithPrio(node->pRight, prio, out);
        }
    }

    void findHighestPrio(Node<Task>*& node, int& prio) {
        if (node) {
            findHighestPrio(node->pLeft, prio);

            if (node->mData.mPrio < prio && node->mData.bCompleted == false)
                prio = node->mData.mPrio;

            findHighestPrio(node->pRight, prio);
        }
    }

    void findHighestPriorityTask(std::ostream& out) {
        if (mTaskTree.mRoot) {
            int highestPrio = INT_MAX;
            
            findHighestPrio(mTaskTree.mRoot, highestPrio);
            printAllTasksWithPrio(mTaskTree.mRoot, highestPrio, out);
        }
        else
            throw std::runtime_error("No tasks\n");
    }

    void inOrderAssigneeID(Node<Task>*& node, std::string AssigneeID, std::ostream& out) {
        if (node) {
            inOrderAssigneeID(node->pLeft, AssigneeID, out);

            if (node->mData.mAssigneeID == AssigneeID && node->mData.bCompleted == false)
                out << node->mData << getAssigneeName(node->mData.mAssigneeID) << " (" << node->mData.mAssigneeID << ")\n";

            inOrderAssigneeID(node->pRight, AssigneeID, out);
        }
    }

    void findTasksByAssignee(std::string AssigneeID, std::ostream& out) {
        out << "Tasks Assigned to \"" << getAssigneeName(AssigneeID) << " (" << AssigneeID << ")\":\n";
        inOrderAssigneeID(mTaskTree.mRoot, AssigneeID, out);
    }

    void countTotalTasks(std::ostream& out) {
        out << "Total Tasks in the System: " << mTaskTree.numNodes << "\n";
    }

    void printCompletedTasks(Node<Task>*& node, std::ostream& out) {
        if (node) {
            printCompletedTasks(node->pLeft, out);

            if (node->mData.bCompleted == true)
                out << node->mData << getAssigneeName(node->mData.mAssigneeID) << " (" << node->mData.mAssigneeID << ")\n";

            printCompletedTasks(node->pRight, out);
        }
    }

    void displayCompletedTasks(std::ostream& out) {
        out << "Completed Tasks:\n";
        printCompletedTasks(mTaskTree.mRoot, out);
    }

    void searchTasksByPriorityRange(Node<Task>*& node, int low, int high, std::ostream& out) {
        if (node) {
            searchTasksByPriorityRange(node->pLeft, low, high, out);

            if (node->mData.mPrio >= low && node->mData.mPrio <= high && node->mData.bCompleted == false)
                out << node->mData << getAssigneeName(node->mData.mAssigneeID) << " (" << node->mData.mAssigneeID << ")\n";

            searchTasksByPriorityRange(node->pRight, low, high, out);
        }
    }

    void searchTasksByPriorityRange(int low, int high, std::ostream& out) {
        out << "Tasks within Priority Range (" << low << " to " << high << "):\n";
        searchTasksByPriorityRange(mTaskTree.mRoot, low, high, out);
    }

    void PrintTreeInOrder(Node<Task>*& node, std::ostream& out) {
        if (node) {
            PrintTreeInOrder(node->pLeft, out);

            if (node->mData.bCompleted == false) {
                out << node->mData.mTaskId << " (";
                if (node->bBlack == true)
                    out << "black)\n";
                else
                    out << "red)\n";
            }

            PrintTreeInOrder(node->pRight, out);
        }
    }

    void PrintTreeInorder(std::ostream& out) {
        PrintTreeInOrder(mTaskTree.mRoot, out);
    }

};

