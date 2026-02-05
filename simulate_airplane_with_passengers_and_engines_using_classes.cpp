/*
* Name: Daniel Hinga,
* Description: create several classes that will work together to simulate an airplane with passengers and
    engines that can be throttled up and eventually also throttled down.
* Input: add classes and functions.
* Output: file created, terminal information as well as 2 log files.
*/



//Skeleton Code by: Jorge Fonseca
//Assignment Covers Creating an Engine Class, a Person Class, and an Airplane class
//that has engine and person as composition.
//Next the engine is upgraded in a derived class which is then added to a new
//Airplane class with added features.
//Will optionally log output of commands done on engines.
#include<iostream>
#include<fstream> //for  ifstream
#include<cstdlib> //For rand()
#include<string>
#include <ctime>
using namespace std;



//Class Design for the engine.
//model and thrust to not be changed
class engineType {
protected:
    double thrust;
    void printMsg(int) const;

private:
    string model;

public:
    engineType(double , string  );
    double getThrust() const ;
    void idle();
    void turnOff();
    void turnOn();
    void accelerate(const int&);
    void printModel () const;
};


//function definition  for get thrust
double engineType::getThrust() const{
    return thrust;
}


// function definition for idle
void engineType::idle() {
    thrust = 10000;
    printMsg(4);
}


// engine turn on only when thrust is 0
void engineType::turnOn() {

    if (thrust == 0){
        thrust = 10000;
        printMsg(6);
    }else if(thrust != 0){
        printMsg(1);
    }
}


// print the model of the place of the engine
void engineType::printModel() const {
    cout << "Engine Model: " << model<< endl;
}


// function to initially accelarate and only accept positive nembers
void engineType::accelerate(const int & accelaration) {
    if (accelaration < 0){
        cout<<" ERROR"<< endl;
    } else {
        //thrust now adds the acceleration to it
        thrust = thrust + accelaration;
        cout << "Engine RPM changed to " << thrust << endl;
    }
}



engineType::engineType( double q = 0, string m = "Propeller" ){
    thrust = q; //uncomment once you created these memeber variables
    model = m;  //uncomment once you created these memeber variables
}



//Use this function as an example of how to do these.
void engineType::turnOff() {
    if(thrust == 0){ //It was off already
        printMsg(3);
    }
    else{
        printMsg(2);
        thrust = 0;
    }
}


//You must use these messages as part of your class implementation
void engineType::printMsg(int cmd) const{
    switch(cmd){
        case 1:  cout << "Warning: Engine is already On" << endl;
            break;
        case 2:  cout << "VRRR PFPT PTFP HKSSSS Turned Engine Off" << endl;
            break;
        case 3:  cout << "Warning: Engine is Off" << endl;
            break;
        case 4:  cout << "Engine RPM Changed to 10,000" << endl;
            break;
        case 5:  cout << "Warning: Cannot Decelerate This Engine" << endl;
            break;
        case 6:  cout << "P P P VROOM VROOM RRRRRRR! Engine is Turning On!" <<
                      endl;
            break;
        default: cout << "Engine RPM Changed to " << -cmd << endl;
            break;
    }
}



//Enum Declarations
enum FirstNames {
    Jorge,
    Jason,
    Jane,
    James,
    Wendy,
    Ben,
    Tim,
    Sophie,
    Andrew,
    Denzel,
    Vicky,
    Dolly,
    Jyn,
    maxFirstName
};

enum LastNames {
    Fonseca,
    Doe,
    Smith,
    Jackson,
    Pedersen,
    Anderson,
    Bond,
    Washington,
    Skywalker,
    Bourne,
    Jones,
    Solo,
    Erso,
    maxLastName

};


//Non-Member Function Prototypes for Enums
string enum2FirstNameToString(unsigned int);
string enum2LastNameToString(unsigned int);
//Your Code Here for the enum2LastNameToString function prototype



//Class Design for people in the plane
struct personType {
private:
    //names not to be changed
    string firstName;
    string lastName;

public:
    personType();
    personType(string, string);
    string getFirstName() const;
    string getLastName() const ;
    void changeName(const string&, const string&);
};



void printPassengers(const personType[], int);// fucntion call for  print passenger



//constructor to auto randomize
personType::personType(){
    //randomizes firstname
    firstName = enum2FirstNameToString(rand() % maxFirstName);
    //randomizes the last name
    lastName = enum2LastNameToString(rand() % maxLastName);
}



personType::personType(string f, string l)
{
    //value f  goes to firstname
    firstName = f;
    //value l goes to lastname
    lastName = l;
}



string personType::getFirstName() const
{
    //returns first name
    return firstName;
}



string personType::getLastName() const
{
    //returns last name
    return lastName;
}



void personType::changeName(const string &f , const string &l) {
    firstName = f;
    lastName = l;
}



class airplaneType {
private:
    unsigned int capacity;
    string model;

public:
    airplaneType() : capacity(5), model("Propeller"){}; //initalizes capacity to 5and model to "propeller"
    engineType propeller;
    personType pilot;
    personType passengers[5];
    string getModel() const;
    void setModel(string);
    int getPlaneCapacity() const;
    void rollIt(){
        cout << "omg we just did a barrel roll!" << endl;
    }
};



string airplaneType::getModel() const {
    // returns the model of the airplane
    return model;
}


int airplaneType::getPlaneCapacity() const {
    // returns the capacity of the plane
    return capacity ;
}



void airplaneType::setModel(string str)
{
    // grabs the name of the model
    model = str;
}



class upgradedEngineType: public engineType{
private:
    const int maxThrust = 25000;
    ofstream fout;
    string filename;
public:
    //constructor to open output file and start loging
    upgradedEngineType(string filename = "engineLog.txt", double t = 0, string model = "Jet Engine"){
        fout.open(filename);// opens the output file
        fout << " Engine Log File Started \n";
    };

    void accelerate(const int&);
    void decelerate(int);
    void printModel() const ;

    //destructor to log and close the output file
    ~upgradedEngineType(){
        fout << " Log File Complete\n ";
        fout.close();//closes the file
    }
};


//
void upgradedEngineType::printModel() const {
    cout<< "Engine Model: Jet Engine." <<  endl;
}



void upgradedEngineType::decelerate(int decelerate)  {
    if ((thrust-decelerate) < 10000)// checks the value of thrust if you go below the speed
    {
        cout << "Warning: Cannot decelerate below idle speed of 10,000 RPM" << endl;
        fout << "Engine Attempted to decelerate below Idle" << endl;
    }
    else
    {
        thrust = thrust - decelerate;
        cout << " Engine RPM changed to " << thrust << endl;
        fout << " Decelerating Engine from 20,000 RPM to " << thrust <<" RPM \n ";
    }
}



void upgradedEngineType::accelerate(const int &acceleration){
    if ((thrust+acceleration) > maxThrust)// checks if the value of acceleration is above the boundaries
    {
        cout << " Warning: Cannot Accelerate to " << acceleration << " RPM as it would go over the max limit of ";
        cout << maxThrust << "RPM!" << endl;
    }
    else
    {
        thrust = thrust + acceleration;// adds the value of thrust
        fout << " Engine Accelerated from 10,000 RPM to " << thrust <<" RPM \n ";
        cout << " Engine RPM changed to " << thrust << endl;
    }
}



class ModernAirplaneType {
private:
    unsigned int capacity;
    string model;

public:
    personType pilot;
    personType copilot;
    personType passengers[120];
    upgradedEngineType leftTurbine;
    upgradedEngineType rightTurbine;
    ModernAirplaneType(): capacity(120), model(" Jet Engine "),
    leftTurbine("leftEngineLog.txt"), rightTurbine("rightEngineLog.txt"){};
    string getModel() const;
    void setModel(string str);
    int getPlaneCapacity() const;
};



int ModernAirplaneType::getPlaneCapacity() const
{
    // returns the capacity of the plane
    return capacity;
}


// returns the model of the modern airplabne
string ModernAirplaneType::getModel() const
{
    return model;
}



void ModernAirplaneType::setModel(string str) {
    // set the  model name for the plane.
    model = str;
}




string enum2FirstNameToString(unsigned int f){
    switch(f){
        case Jorge :  return "Jorge" ;
        case Jason :  return "Jason" ;
        case Jane  :  return "Jane"  ;
        case James :  return "James" ;
        case Wendy :  return "Wendy" ;
        case Ben   :  return "Ben"   ;
        case Tim   :  return "Tim"   ;
        case Sophie:  return "Sophie";
        case Andrew:  return "Andrew";
        case Denzel:  return "Denzel";
        case Vicky :  return "Vicky" ;
        case Dolly :  return "Dolly" ;
        case Jyn   :  return "Jyn"   ;
        default    :  return "None"  ;
    }
}
//Enum Functions
string enum2LastNameToString(unsigned int f) {
    switch (f) {

        case Fonseca    :
            return "Fonseca";
        case Doe        :
            return "Doe";
        case Smith      :
            return "Smith";
        case Jackson    :
            return "Jackson";
        case Pedersen   :
            return "Pedersen";
        case Anderson   :
            return "Anderson";
        case Bond       :
            return "Bond";
        case Washington :
            return "Washington";
        case Skywalker  :
            return "skywaler";
        case Bourne     :
            return "Bourne";
        case Jones      :
            return "Jones";
        case Solo       :
            return "Solo";
        case Erso       :
            return " Erso";
        default         :
            return "ERROR";
    }
}




//Client Code
int main(int argc, char *argv[]) {
    cout << "Assignment 3: Welcome to CS202 Airways.\n"
         << "Now Offering Non-stop flights to All-nighters coding C++\n"
         << "Book your Flight Today! :D" << endl;
    srand (time(NULL)); //Seed Rand!
    //Let's create an airplane!
    airplaneType Cessna;
//Uncomment line by piece as you write the code, so you can test it
    //Next, let's print out the passengers in our plane!
    printPassengers(Cessna.passengers, Cessna.getPlaneCapacity());
    //Next, let's make ourselves the pilot CUZ I AM TEH CAPTEIN NAOW!
    personType LeCapitaine("Capt.", "Whip");
    Cessna.pilot = LeCapitaine;
    //Now let's print the Captain's greetings
    cout << "Greetings from your pilot. My name is " << Cessna.pilot.getFirstName()
         << " "
         << Cessna.pilot.getLastName() << " and WE'RE GOING TO ROLL IT" << endl;
    //Captain Whip wants you to get this pupper in the air so turn the engines on.
    Cessna.propeller.turnOn();
    cout << "Current Thrust " << Cessna.propeller.getThrust() << endl;
    //When this baby hits 88...
    Cessna.propeller.accelerate(15000); //Accelerate the engine to take off.
    //wooho now we are flying. Let's push this baby to the limit!
    Cessna.propeller.accelerate(40000); //Accelerate the engine to take off.
    cout << "Warning: Engine Overheating. inb4 explosion!" << endl;
    cout <<"Quick lower the power on the engine before it blows!" << endl;
    Cessna.propeller.idle(); //Quick set the engine to idle before it blows!
    Cessna.propeller.turnOff();
    cout << "Omg the engine just cut off! Restart!" << endl;
    cout << "Engine: nah bruh im ded" << endl;
    cout << "Okay when I say go we gonna roll it!" << endl;
    Cessna.rollIt(); //roll it!
    cout << "Plane landed safely and everyone lived! Yay" << endl;
    cout << "Meanwhile at headquarters. In response to this incident they decide\n"
         << "to create a new plane that has two engines and a larger capacity\n"
         << "because safety, also can carry more people and can decelerate engines\
n"
         << "to a specified value instead of having to go all the way to idle.\n";
    //Create a new object of the ModernAirplaneType
    ModernAirplaneType B737MAX; //lol
    //Wow this guy is sweet! Let's fill 'er up with passengers!
    cout << "Our Passengers:" << endl;
    printPassengers(B737MAX.passengers, B737MAX.getPlaneCapacity());
    //Captain Whip is a Hero for saving that plane. Let's make him pilot.

    B737MAX.pilot = LeCapitaine;

    //Your Code Here (1 Line of Code)
    //We also need a co-pilot. The company assigned one. Print out both Pilot's names.
    cout << "Pilot  : " << B737MAX.pilot.getFirstName()
        << " " << B737MAX.pilot.getLastName()
        << "\nCopilot: " << B737MAX.copilot.getFirstName()
        << " " << B737MAX.copilot.getLastName() << endl;


    B737MAX.leftTurbine.turnOn();//Write Code Here that turns each engine on.
    B737MAX.rightTurbine.turnOn();
    B737MAX.leftTurbine.idle();  //Set them both to idle.
    B737MAX.rightTurbine.idle();
    B737MAX.leftTurbine.accelerate(5000);//Accelerate the left one to 15,000 RPM and the Right one to 20,000 RPM.
    B737MAX.rightTurbine.accelerate(10000);

    //Decelerate the right one from 20,000 to 16,000.
    B737MAX.rightTurbine.decelerate(4000);
    //Accelerate the left one past the maximum (25,000) so the new automated system
    // halts you.
    B737MAX.leftTurbine.accelerate(20000);
    B737MAX.rightTurbine.idle(); //Set both Engines to idle.
    B737MAX.leftTurbine.idle();
    B737MAX.leftTurbine.turnOff();//Then turn them off.
    B737MAX.rightTurbine.turnOff();
    //Nice job. Now the plane doesn't explode! You have landed the plane.
    cout << "Thanks for Flying C202 Airways!" << endl;
    return 0;
}

//Your Code Here for printPassengers Function
void printPassengers(const personType people[] , int totalpeople)
{
    for (int i = 0; i < totalpeople; i++)
    {
        cout << i+1 << " " << "Passenger: " << people[i].getFirstName() << " "<< people[i].getLastName() << endl;
    }

}
