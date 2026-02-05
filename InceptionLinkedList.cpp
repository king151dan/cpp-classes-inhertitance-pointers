/*
* Name: Daniel Hinga,
* Description: Doubly Linked List of Nodes. Each of these nodes may contain a
link to the beginning of other linked lists along with a data field that contains a string representing what
type of node it is.
 * Input: linux redirection// levels// test file input
* Output: the text files have the output.
*/


//Because of to_string compile with std=c++11
//INCEPTION
//Give him the kick at the right order to wake them up. Else program crashes.

#define DEBUG_MODE

#include<iostream>   //cin/cout
#include<string>     //to_string
#include<sstream>    //String Streams
using namespace std; //Avoid std:: infront of everything.

//The input file consists of all of the dream levels in the right order in the
//first line. The second line is all of the different ticks that identify which
//dream level they represent. See sample input files.

//Maintains the dream levels in the world. Class stores them in array of strings
//that we can use to check where in the dream hierarchy we are.
class Levels{
  public:
    Levels(int s = 0) : size(s){
        if(size == 0) return;
        cout << size << " Levels Created." << endl;
        name = new string [size];
    }
    ~Levels(){
        if(size != 0){
            delete [] name;
            name = NULL;
        }
    }
    //Returns -1 if not found, otherwise returns dream level that matches.
    int findLevel(string search){
        for(int i = 0; i < size; i++){
            if(name[i] == search){
                return i;
            }
        }
        return -1;
    }

    friend ostream& operator<<(ostream& os, const Levels & lvl);
    friend istream& operator>>(istream& is, Levels& lvl);
    string *name;
    int size;
};


ostream& operator<<(ostream& os, const Levels & lvl){
    for(int i = 0; i < lvl.size; i++){
        os << " Level " << " " << i+1 << " : "
           << lvl.name[i] << endl;
    }
    return os;
}


istream& operator>>(istream& is, Levels& lvl){
    string line, word;
    getline(cin,line);
    stringstream sstream(line);
    if(lvl.size != 0){
        delete [] lvl.name;
    }
    while(getline(sstream, word, ' ')){
        lvl.size++; //First Loop counts how big to make array
    }
    lvl.name = new string[lvl.size];
    cout << lvl.size << " Levels Created." << endl;
    stringstream sstream2(line);
    for(int i=0; i< lvl.size; i++){
        getline(sstream2, word, ' ');
        lvl.name[i] = word;
    }    
    return is;
}

class LinkedList; //Forward Declaration

//Nodes that make the heart of the linked list.
//Data is a string which identifies what level we are at.
//The DeeperDream is kept null unless this signifies the beginning
//of a deeper dream level.
//Because it is a doubly linked list, we have a prev and next pointer.
//Both the node and linked list class have a static to keep track of
//how many objects have been made so each can have a unique identifier
class Node {
  public:
    Node() : next(NULL), prev(NULL), id(count++) {
        #ifdef DEBUG_MODE
        cout << "New Node: ";
        #endif
        data = new string;
        DeeperDream = NULL;
    }
    ~Node(){
        #ifdef DEBUG_MODE
        //cout << "Node Destructor" << endl; //Commented Out Until Memory Leak Fixed
        #endif
        delete data;
        data=NULL;
        next=prev=NULL;
        DeeperDream=NULL;
    }
    int getID(){return id;}
    friend ostream& operator<<(ostream& os, const Node& node);
    friend ostream& operator<<(ostream& os, const Node *node);
    friend istream& operator>>(istream& is, Node& node);
    friend istream& operator>>(istream& is, Node *node);

    string *data;
    //Node* DeeperDream;
    LinkedList* DeeperDream;
    //void *data;
    Node *next;
    Node *prev;
  private:
    int   id;
    static int count;
};
int Node::count = 0;

ostream& operator<<(ostream& os, const Node & node){
    //os << "Node " << node.id << ": " << *static_cast<string*>(node.data);
    os << "Node " << node.id << ": " << *node.data;
    return os;
}
ostream& operator<<(ostream& os, const Node *node){
    os << "Node " << node->id << ": " << *node->data;
    return os;
}

istream& operator>>(istream& is, Node& node){
    is >> *node.data;
    return is;
}
istream& operator>>(istream& is, Node *node){
    //is >> *static_cast<string*>(node->data);
    is >>  *node->data;
    return is;
}

//Stores all of the nodes and has a head and tail that point to the 
//beginning and end of the linked list.
class LinkedList {
  public:
    LinkedList() : head(NULL), tail(NULL), id(count++) {
        #ifdef DEBUG_MODE
        cout << "New Linked List" << endl;
        #endif
    }
    ~LinkedList(){
        #ifdef DEBUG_MODE
        //cout << "Linked List Destructor" << endl; //Commented Out Until Memory Leak Fixed
        #endif
        //De-allocate Nodes:
        //Your Code Here
        delete [] head;
        delete[] tail;

        head=tail=NULL;
    }
    int getID(){return id;}
    friend ostream& operator<<(ostream& os, const LinkedList & linkedlist);
    friend ostream& operator<<(ostream& os, const LinkedList  *linkedlist);
    void fwdPrintList(){
        //Your Code Here
        Node *temp = head;
        while(temp != NULL){
            cout << *temp << ", " << " " ;
            temp = temp->next;
        }
        delete [] temp;
        temp = NULL;
    }


    void bkwdPrintList(){
        Node *temp = tail;
        while(temp != NULL){
            cout << *temp << ", " << " " ;
            temp = temp->prev;
        }
        delete [] temp;
        temp = NULL;

    }


    void insertEndNode(Node *n){
        if(head == NULL){
            head = n;
            tail = head;
        } else{
            tail->next = n;//points at the last node
            tail = tail->next;//now tails gets the value of the last node
        }
    }


    void insertDreamNode(Node *n, Levels &lvl){
        //We need to see what dream it is, figure out its level and insert in the right spot.
        int level2insert = lvl.findLevel(*n->data);
        //Your Code Here

        LinkedList* temp = new LinkedList[lvl.size];

        //current = gotoLevel(level2insert);
        temp = gotoLevel(level2insert);
        Node *current = tail;

        //temp->tail->DeeperDream = new LinkedList;
        gotoLevel(level2insert)->tail->DeeperDream = new LinkedList[lvl.size] ;
            temp = gotoLevel(level2insert);
                    //->DeeperDream;
        //tail->DeeperDream->insertEndNode(n);

        for(int currlevel=0; currlevel < lvl.size ; currlevel++){
            tail->DeeperDream->head = tail->DeeperDream->head->next;
        }



    }

    //Function Returns Pointer to beginning of list at a certan level.i
    LinkedList* gotoLevel(int lvl){
        if(lvl==0){ //REALITY
            return this;
        }
        cout << "Searching LVL:" << lvl+1 << endl;
        Node *curr = head;
        LinkedList* currList;
        for(int currlevel=0; currlevel < lvl; currlevel++){
            //Your Code Here
            curr = curr->next;
        }
        if(curr!=NULL)
            cout << "FOUND?: " << *curr->data << endl;
        else{
             cout << "Error: We Tried to Enter A Deeper Dream Directly!" << endl
                  << "Paradox: Terminating Program." << endl;
             exit(0); //Otherwise We crash
        }
        return currList;
    }
    Node *head;
    Node *tail;
  private:
    int   id;
    static int count;
};
int LinkedList::count = 0;

ostream& operator<<(ostream& os, const LinkedList & linkedlist){
    os << "LinkedList: " << linkedlist.id;
    return os;
}
ostream& operator<<(ostream& os, const LinkedList  *linkedlist){
    //Your Code Here
    os << "LinkedList: " << linkedlist->id;
    return os;
}

class World {
  public:
    World(){
        reality = new LinkedList;
    }
    ~World(){
        delete reality;
        reality = NULL;
    }
    static int DFStraversal(ostream& os, Node* node);

    //This Function deletes all dream states (de-allocates them), but does not touch Reality. 
    int givehimthekick(){
        cout << "\nNon, rien de rien, Non, je ne regrette rien,"
             << " Ni le bien qu'on m'a fait BRRRR BRRRRRRR "
             << "BRRRRRR BRRRRRRRRR" << endl;
        Node* currNode = this->reality->head;
        LinkedList** currList = new LinkedList*[this->levels.size];
        //Your Code Here
        for (int i = 0; i < this->levels.size; ++i) {
            delete [] currList[i];
        }

        //Begin De-Allocation.
        delete [] currList;
        currList= NULL;

        //Your Code Here
        return 0;
    }
    void printbylevel(){
        cout << "\nPrinting World by Level:\n" << endl;

        LinkedList *currList = this->reality;
        currList->fwdPrintList(); 
        cout << endl;
        //Your Code Here
    }

    LinkedList* reality;    
    Levels levels;

    friend istream& operator>>(istream& is, World& world);
    friend istream& operator>>(istream& is, World *world);
    friend ostream& operator<<(ostream& os, const World & world);
};
istream& operator>>(istream& is, World& world){
    Node* tick = new Node;
    while(cin >> tick){
        world.reality->insertEndNode(tick);
        tick = new Node;
    }
    delete tick;
    return is;
}
istream& operator>>(istream& is, World *world){
    Node* tick = new Node;
    while(cin >> tick){
        if(*tick->data == world->levels.name[0]){
            #ifdef DEBUG_MODE
            cout << "REALITY" << endl;
            #endif
            world->reality->insertEndNode(tick);
        }
        else{//Dream Logic
            #ifdef DEBUG_MODE
            cout << "DREAM" << endl;
            #endif
            world->reality->insertDreamNode(tick, world->levels);
        }
        tick = new Node;
    }
    delete tick;
    return is;
} 

//Function Requires the OS stream on where to print traversal. 
//The node parameter is where it is at as it traverses the tree.
//It will perform a DFS traversal. Function is Recursive.
int World::DFStraversal(ostream& os, Node* curr){ //Static Function
        if(curr == NULL){
            os << "Error: DFStraversal got lost..." << endl;
            return 0;
        }
        //curr != NULL at this point
        int visitCnt = 1;
    if (curr->next !=NULL ) {
        os << "New node:  " << curr->next << " " << endl;
        visitCnt = DFStraversal(os, curr->next);

    } else if (curr->next != NULL){
        visitCnt= 1 + DFStraversal(os, curr->next);
    }
    return visitCnt;
}

ostream& operator<<(ostream& os, const World & world){
    os << "The World As We Know It: " << endl;
    os << world.levels;
    os << "\nDream Architecture:" << endl;
    int visitCnt = world.DFStraversal(os, world.reality->head);
    os << "\b\b. \nNode Visited: " << visitCnt << endl;
    return os;

}

void testCode();
int main(int, char**){////////////////////
    cout << "Inception" << endl << endl;//
    //testCode();/////////////////////////
    World *world = new World;/////////////
    cin >> world->levels;/////////////////
    //cout << world->levels;//////////////
    cin >> world;/////////////////////////
    //world->reality->fwdPrintList();/////
    //world->reality->bkwdPrintList();////
    world->printbylevel();////////////////
    cout << *world;///////////////////////
    world->givehimthekick();//////////////
    delete world; world = NULL;///////////
    cout << "\nTHE END\n\nCreated by ";///
    cout << "Jorge Fonseca" << endl;//////
    return 0;/////////////////////////////
}   //////////////////////////////////////

#ifdef DEBUG_MODE
void testCode(){
    //This code is to help you test basics. //
    //Add anything here you want to test.   //
    cout << "Start of Test Code" << endl;
    Node testNode;
    cout << testNode.getID() << testNode << endl;
    Node *testNodePtr = new Node;
    cout << testNodePtr->getID() << testNodePtr << endl;
    LinkedList testList;
    cout << testList.getID() << testList << endl;
    LinkedList *testListPtr = new LinkedList;
    cout << testListPtr->getID() << testListPtr << endl;
    delete testNodePtr; testNodePtr = NULL; 
    delete testListPtr; testListPtr = NULL;

    Levels level(3);
    cout << level;

    cout << "End of Test Code" << endl;
}
#endif
