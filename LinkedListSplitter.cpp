/*
* Name: Daniel Hinga, 
* Description: write and test a a program to build two sorted linked lists in the forward
    direction. Read it, dread it, run from it, understand it.
* Input: linux input redirection with the attached main()..  data12 file
* Output: outast12 to a file
*/


#include<iostream>
#include<cstddef>
using namespace std;
typedef int ItemType;
struct NodeType;
typedef NodeType *NodePtr;
struct NodeType{
    ItemType component;
    NodePtr link;
};
class List {
public:
    List();
    void Insert(ItemType item);
    void Delete(ItemType item);
    void ResetList();
    ItemType GetNextItem();
    int GetLength() const;
    bool IsEmpty() const;
    bool IsFull() const;
    bool IsThere(ItemType item) const;
    bool HasNext() const;
    void PrintForward() const{
        NodePtr currPtr = dataPtr;
        while (currPtr != NULL) {
            cout << currPtr->component << ",";
            currPtr = currPtr->link;
        }
        cout << endl;
    }
    ~List();// created destructor to delete and set to null pointer

List split_ver1(ItemType item){
// created pointers for the previous and next and current pointers
NodePtr currentptr =NULL;
NodePtr nextptr= NULL;
NodePtr prevptr = NULL;
// curent pointer is set to the head/ first pointer
ResetList();
//returning list;
List temp;

    while(currentptr->component != item){
        // set the previous pointer to the current pointer
        prevptr = currentptr;
        //set the current pointer to be the same as the next pointer
        currentptr = currentptr->link;
    }
    //nextptr = currentptr;
    // while the previous pointer is not null
    while(prevptr->link != NULL){
        // use temp to inset the component of the current position to
        temp.Insert(currentPos->component);
        // rest of last poiners components are deleted
        Delete(lastPtr->component);
        // sets second pointer to the previous link
        //nextptr = prevptr->link;
    }
    return temp;
}


List split_ver2(ItemType item){
    NodePtr currPtr = NULL;
    NodePtr secPtr= NULL;
    NodePtr prevPtr = NULL;
    NodePtr newptr = dataPtr;

    List temp;
    //create a counter that will measure the places
    int distance = 0;
    // this will set the current pointer to tho the first ponter again
    ResetList();

    //loop to make sure that it ends when the item if found and increase
    // the distancet till its found
    while(GetNextItem() != item){
        distance++;
    }
    // set the length equal to the distance to the item

    for (int i = 0; i < distance; i++) {
        newptr = newptr->link;
    }
    // get the lenght
    length = GetLength();
    // set the temp data pointer to the new pointer
    temp.dataPtr = newptr->link;

    //the curent pos is now the new  pointers link to the next item
    temp.currentPos = newptr->link;

    //this will set the temporary last pointer to the last pointer
    temp.lastPtr = lastPtr;

    //lenght minus distance to assign it to temp length, length of the spaces
    temp.length = length - distance;

    //the new pointer is assigned to the last ptr
    lastPtr = newptr;


    //assign dataPtr to currentPos
    ResetList();

    length = distance;
    // set to NULL
    newptr->link = NULL;


    return temp;
}


private:
    NodeType *dataPtr;
    int length;
    NodeType *currentPos;
    NodeType *lastPtr;
};
List::List(){
    dataPtr = NULL;
    currentPos = dataPtr;
    length = 0;
    lastPtr = NULL;
}
void List::Insert(ItemType item){
    NodePtr currPtr, prevPtr, newNodePtr;
    newNodePtr = new NodeType;
    newNodePtr->component = item;
    if (dataPtr == NULL){  // Empty list?
        dataPtr = newNodePtr;
        lastPtr = newNodePtr;
    }
    else{ //Find previous insertion point
        currPtr = dataPtr;
        prevPtr = NULL;
        while (currPtr != NULL && currPtr->component < item) {
            prevPtr = currPtr;
            currPtr = currPtr->link;
        }
// Insert new node
        newNodePtr->link = currPtr;
        if (prevPtr == NULL)  // Insert as first?
            dataPtr = newNodePtr;
        else  prevPtr->link = newNodePtr;
        if (currPtr == NULL) // Insert as last?
            lastPtr = newNodePtr;
    }
    length++;
}
void List::Delete(ItemType item){
    NodePtr prevPtr = NULL;
    NodePtr currPtr = dataPtr;
    while(currPtr != NULL && currPtr->component != item){
        prevPtr = currPtr;
        currPtr = currPtr->link;
    }
    if (currPtr != NULL){
        if (currPtr == dataPtr) dataPtr = currPtr->link;
        else prevPtr->link = currPtr->link;
        if (currPtr == lastPtr) lastPtr = prevPtr;
        delete currPtr;
        length--;
    }
}
void List::ResetList(){
    currentPos = dataPtr;
}
ItemType List::GetNextItem(){
    ItemType item;
    item = currentPos->component;
    currentPos = currentPos->link;
    return item;
}
int List::GetLength() const{
    return length;
}
bool List::IsEmpty() const{
    return (dataPtr == NULL);
}
bool List::HasNext() const{
    return (currentPos != NULL);
}
bool List::IsFull() const{
    return false;
}
bool List::IsThere(ItemType item) const{
    NodePtr currPtr = dataPtr;
    while (currPtr != NULL && currPtr->component != item)
    currPtr = currPtr->link;
    if (currPtr != NULL) return true;
    else return false;
}
List::~List() {
    //temp to store cur pos to delete ptr
    NodePtr temp = NULL;
    //this will mae sure it deletes every ptr by looping all
    while (HasNext()){
        //set temp into null
     temp = currentPos;
     // set the curent positon to tghe next
     currentPos = currentPos->link;
     delete temp;
     temp = NULL;
    }
}
int main(){
    List L1,L2, L3, L4;
    int n, x;
    cin >> n;
//read first list
    for (int i=0; i<n; i++){
        cin >> x;
        L1.Insert(x);
    }
//read second list
    for (int i=0; i<n; i++){
        cin >> x;
        L2.Insert(x);
    }
    cout << "Given List L1: " << endl;
    L1.PrintForward();
    cout << endl;
    cout << "Given List L2: " << endl;
    L2.PrintForward();
    cout << endl;

    cin >> x; // Read item to split the first list
    cout << "Split Data: " << x << endl;
    L3 = L1.split_ver1(x);
    cout << "After splitting L1, first part is: " << endl;
    L1.PrintForward();
    cout << "After splitting L1, second part is: " << endl;
    L3.PrintForward();
    cin >> x; // Read item to split the second list
    cout << "Split Data: " << x << endl;
    L4 = L2.split_ver2(x);
    cout << "After splitting L2, first part is: " << endl;
    L2.PrintForward();
    cout << "After splitting L2, second part is: " << endl;
    L4.PrintForward();
    return 0;
}

