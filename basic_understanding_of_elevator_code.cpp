/*
 * Name: Daniel Hinga,
 * Description: basic understanding of elevaror code.*
 * Input: user inputs elevator info needed to direct the elevaror, elevaror id, floor to go to, and maxfloor.*
 * Output: displays info of the elevator. eg. id, floor, if elevator is in use .
 */


#include <iostream>
#include <cstdlib> //For Absolute value use abs() ie: abs(-5) will return 5
using namespace std;
//Skeleton Program by Jorge Fonseca
//Class Declaration (Design)
class myElevator {
private:
    static int count; //keeps track of how many elevators there are
    int id; //elevator id gets increased every time an elevator is added
    int currentFloor; //location of elevator
    int maxFloor; //Maximum Floor of Elevator
    bool inUse; //Whether elevator is in service
public:
    myElevator(int = 1, int = 50); //constructor
    int getElevatorID() const;
    int getElevatorCurrentFloor() const;
    int getCount() const;
    bool canReach(int) const;
    void ToggleElevator(); //Toggle elevator on or off
    void printElevator() const; //Print information on elevator
    void moveElevator(int); //Moves elevator to the requested floor
};
//Class Implementation
int myElevator::count = 0;
myElevator::myElevator(int floor, int max) {
    this->id = count++;
    this->currentFloor = floor;
    this->inUse = false;
    this->maxFloor = max;
}




int myElevator::getElevatorID() const {
    return id;
}
int myElevator::getElevatorCurrentFloor() const {
    return currentFloor;
}
int myElevator::getCount() const {
    return myElevator::count;
}
bool myElevator::canReach(int floor) const {
    if(maxFloor >= floor) return true;
    else return false;
}




void myElevator::ToggleElevator() {
    cout << "Toggled Elevator" << endl;
    inUse = !inUse;
// whatever it is it will be the oposite
}


void myElevator::printElevator() const {
    cout << "Elevator: " << id << " is";
    if(!inUse) cout << " not";
    cout << " in service." << endl;
    cout << "Floor Location: " << currentFloor << endl;
    cout << "Max Floor for Elevator: " << maxFloor << endl;
}


void myElevator::moveElevator(int floor) {
    // first chack to see if the elevator is in use
    if(inUse) {
        // check if its at max floor
        if (floor > maxFloor) {
            cout << "Error: Elevator Cannot Reach Floor " << floor <<"!" << endl;

            return;
        }
        if (floor == myElevator::currentFloor) {
            // does nothing if on floor requested
            return;
        } else {
            cout << "Elevator Request Received for Elevator " <<
                 myElevator::getElevatorID() << "." <<endl;
            cout << "Moving from Floor " << myElevator::currentFloor << " to Floor " << floor << "." << endl;
            myElevator::currentFloor = floor;
            cout << "Arrived at Floor " << myElevator::currentFloor << "." <<endl;
            return;
        }
    }else
        cout << "Elevator " << myElevator::getElevatorID() <<" is out of service."<< endl;
        //this is if the elevator is not working
}



//Non-Member Functions
int closestElevatorID(myElevator A, myElevator B, int floor) {

    // new variables to store differences; only to look better, can do without

    int distace1= abs(floor - A.getElevatorCurrentFloor());
    int distance2 = abs(floor - B.getElevatorCurrentFloor());

    //if to see which is close to requested floor and return the closest one
    if (distace1 < distance2){
        return A.getElevatorID();
    } else if (distace1 > distance2 ){
        return B.getElevatorID();
    }else
        return A.getElevatorID();
        // retuns the first one if they are eqidistant

} //Returns closest elevators. If equal it just picks the first one




int elevatorDistance(myElevator A, myElevator B) {
    // new variable to store difference
    int distance =0;
    //will return absolute value of difference
    distance = abs(A.getElevatorCurrentFloor() - B.getElevatorCurrentFloor());
    return distance;
} //Returns floor distance between both elevators






// Client Code to test the functionality of the class myElevator
int main() {

    int a,b,c,d,e,f;
    cout<< "inputs"<< endl;
    cin >> a; cin >> b; cin >> c; cin>> d; cin >> e; cin >> f;
    myElevator A; // declare 1 object of type Elevator
    myElevator B;
    myElevator C(a,b); //a=1,b=10
    C.printElevator();
    C.ToggleElevator();
    C.moveElevator(c);//c=11
    A.ToggleElevator();
    A.moveElevator(d);//d=4
    B.moveElevator(e);//e=2
    B.ToggleElevator();
    A.printElevator();
    B.printElevator();
    cout << "Closest Elevator to Floor "<< f << " is Elevator ID: "
         << closestElevatorID(A,B, f) << endl; //f=3
    cout << "Elevator Distance between Elevator " << A.getElevatorID()
         << " and " << B.getElevatorID() << " is "
         << elevatorDistance(A,B) << " Floors." << endl;
    cout << "Total Elevators in Existence: " << A.getCount() << endl;
    return 0;
}