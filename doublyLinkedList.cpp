#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Node{
public:
    string name;
    Node* successor; //same as next
    Node* predecessor; //same as previous

    Node(string n){
        name = n;
        successor = nullptr;
        predecessor = nullptr;
    }
};

class DoublyLinkedList{
public:

    DoublyLinkedList(){
        head = nullptr;
        tail = nullptr;
    }

    void insertNode(string data);
    void deleteNode(string data);
    void traverseAscending();
    void traverseDescending();

private:
    Node* head;
    Node* tail;
    Node* currNode;

};

void DoublyLinkedList::insertNode(string data){
    Node* newNode = new Node(data);
    if(!head){ //no other nodes
        head = tail = newNode;
    }
    else if (data < head->name){ //smaller than head (insert at beginning if its the smallest)
        newNode->successor = head;
        head->predecessor = newNode;
        head = newNode;
    }
    else if (data > tail->name){ //larger than tail
        newNode->predecessor = tail;
        tail->successor = newNode;
        tail = newNode;
    }
    else{ //somewhere in the middle
        //loop to see where in the middle it would fit
        currNode = head;
        while (currNode && currNode->name < data){
            currNode = currNode->successor;
        }
        Node* temp = currNode->predecessor;
        temp->successor = newNode;
        newNode->predecessor = temp;
        newNode->successor = currNode;
        currNode->predecessor = newNode;
    }
}

void DoublyLinkedList::deleteNode(string data){
    Node* currNode = head;
    while (currNode && currNode->name != data) {
        currNode = currNode->successor;
    }
    if (!currNode){ //If the name isn't found, we don't delete anything
        return;
    }
    Node* successor = currNode->successor;
    Node* predecessor = currNode->predecessor;

    if (successor != nullptr){  //Will delete middle nodes
        successor->predecessor = predecessor;
   }
    if (predecessor != nullptr){
        predecessor->successor = successor;
   }
    if (currNode == head) { //Student may be at head
        head = successor;   //We delete 1st node so we move head forward
   }
    if (currNode == tail) { //Student may be at tail
        tail = predecessor; //We delete last node so we move tail backwards
   }
   delete currNode;
}

void DoublyLinkedList::traverseAscending(){
    currNode = head;
    cout << "Ascending order: \n";
    while(currNode != nullptr){
        cout << currNode->name << endl;
        currNode = currNode->successor; //Will point to next node and then print out
    }
    cout << endl;
}

void DoublyLinkedList::traverseDescending(){
    currNode = tail;
    cout << "Descending order: \n";
    while(currNode != nullptr){
        cout << currNode->name << endl;
        currNode = currNode->predecessor;   //Same as ascending, but points to previous node & starting with tail
    }
    cout << endl;
}

int main(){

    DoublyLinkedList list;
    string word, name;

    ifstream file("input.txt");
    while (file >> word){
        if (word == "delete"){
            file >> name;
            list.deleteNode(name);
        }
        else{
            list.insertNode(word);
        }
    }
    list.traverseAscending();
    list.traverseDescending();

    return 0;
}
