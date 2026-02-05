/*
* Name: Daniel Hinga,
* Description: practice using pointers and dynamic allocation
* Input: add classes and pointers and memory allocation
* Output: print the info of the animss type of animal, age, and breed.
*/

#include<iostream> //cout
#include<stdlib.h> //Malloc/Free
#include<stdio.h>  //printf
#include<cstring>   //strcpy
#include<string>   //Strings
using namespace std;
//Create a class called animal_t with two pointers, name and age (string and int pointers). All members of the class are public.
//Create constructor that allocates memory to name and age and then initializes them to "Default" and 0. Use the new keyword
//Create accessors and mutators for both member variables [ int setAge() , void getAge(int a)  etc... ]
//Create a print function that prints: "Animal> Name: X, Age: Y\n" replace X and Y with name and age variables. ie: "Animal> Name: Default, Age 0"
//Create a Destructor that uses delete and sets age and name pointers to null.
class animal_t{
public:
string *name = NULL;
int *age = NULL;
animal_t(string, int );
void setAge(int a);
int getAge() const ;
void printanimal();
void setName(string string1);


// deconstractor of animal class
~animal_t(){
    //delete the memory allocattions and set them to null
    delete age;
    delete name;
    age = NULL;
    name = NULL;
};
};


// animal class function to set the name of the animal.
void animal_t::setName(string string1) {
    // wherever name is stored place string1 there
    *name = string1;
}


//constructor to allocate the name and age and initialize them
animal_t::animal_t( string dname = "Default", int initalage = 0) {
    name = new string;
    age = new int;
    *name = dname;
    *age = initalage;
}

//wherever age is place the value of a there
void animal_t::setAge(int a) {
    *age = a;
}


//returns the age of the animal
int animal_t::getAge() const {
    return *age;
}


// prints out the animal name and age
void animal_t::printanimal(){
    cout << "Animal> Name: "<< *name << ", Age: "<< *age<< endl;
}

//Create a class dog_t that publicly inherits animal_t
//Create a public char pointer called breed
//Create getBreed()accessor that returns a char pointer to breed.
//Create a mutator setBreed() that takes a string and converts it to char array and stores it in breed.
//To do this,  you will need to delete the old breed using free and then allocate a new breed char array.
//Use str.length() to find length needed to allocate it. use strcpy(thestring, breed) to copy the string into the char array.
//This breed pointer will be an array of characters (null terminated) to store the name of the breed.
//Creater 2 constructors. A default constructor that dynamically allocates the breed array with a size of 8 and initalize it with "Unknown"
//After the 2nd n in Unknown. add a null character '\0' That's what we mean with null terminated.
//The second constructor should expect two parameters. the size to dynamically allocate our char array first,
//then the actual breed name to store in the array, passed as a char array. Make sure to make a deep copy.
//For this class you are not allowed to use NEW and DELETE, you must use malloc and free.
//Create a destructor that will free the memory and set pointer to null for breed.
//redefine the print function but this time have it print Dog> infront of the name  and age. Also print the Breed after the age:
//For example:  Dog> Name: Default, Age: 0, Breed: Unknown
class dog_t : public animal_t{
public:
   char* breed = NULL;
    char* getBreed();
    void setbreed(string str);
    dog_t();
    dog_t(int, string);
    ~dog_t();
    void printdg();

};

//priint function to print dogs information
void dog_t::printdg() {
    cout << "Dog> Name: "<< *name << ", Age: "<< *age<< ", Breed: ";
    for (int i = 0; breed[i] != NULL; i++){
        cout<< breed[i];
    }
    cout<< endl;
}


//deconstractor for dog classs
dog_t::~dog_t() {
    // free up space that breed takes up
    free(breed);
    // set the pointer to null
    breed = NULL;
}


dog_t::dog_t(int size, string breedname) {

}

// constractor that uses the set breed function in dog class and sets it to unknown
dog_t::dog_t() {
    setbreed("unknown");
}

//character pointer function that returns the breed name
char* dog_t::getBreed(){
    return breed;
}

void dog_t::setbreed(string str) {
   free(breed);
   breed = (char*)malloc(sizeof(str) +1 * sizeof(char));
    for(int i = 2; i < sizeof(str); i++){
        breed[i] = str[i];
    }
    breed[sizeof(str)] = NULL;
    cout << breed<< endl;
}





class bird_t : public animal_t{ //bird_t that publicly inherits animal_t, don't edit me.
    static int id;
public:
    void print(){cout << "Bird>" << ++id << endl;}
}; int bird_t::id = 0;


//Create a struct called house_t that has 1 dogs and 1 birds pointer
struct house_t{
    string name; //Don't touch this.
    dog_t *dogs;
    bird_t *birds;
};

// Client/Driver Code
int main(){
    int x = 5;
    int y = 10; //will be used for bird array
    string str = "Cavalier Spaniel"; //will be used later
//Your Code Here
//Create a pointer called Name of type string
string *name;

//dynamically allocate it;
name = new string;

//Store "Padme" in your new string
*name = "Padme";

//create an integer pointer ptr;
int *ptr;

//Make it point to x;
ptr = &x;

//Store the value of 2 into ptr (should indirectly change x)
*ptr = 2;



//cout the address of ptr
cout << "ptr Address: ";
cout << ptr ;
cout << " : ";
//cout the value ptr points to. Then cout and endline.
cout<< *ptr<< endl;

//Create an integer pointer mptr;
int *mptr;

//Dynamically allocate it using malloc.
mptr = (int *)malloc(sizeof (int));

//Copy the value of what ptr is pointing to there (so basically copy the value stored in x, but without using the x variable in code
*mptr = *ptr;

//Use printf to output the following statement:   "MPTR, Address: $, : Valuev $\n"  //
// Replace dollar signs with approrpriate syntax to print address and value mptr points to.
printf("MPTR, Address: %x, : Value, %d\n", mptr, *mptr);


//Create an pointer of animal_t type called animal1
animal_t *animal = NULL;

//dynamically allocate animal1 using new
animal = new animal_t;

//call animal1.print() . Do not use arrow operator do it using parenthesis and dereference operator. Should print: Animal> Name: Default, Age: 0
(*animal).printanimal();

//Create an object of dog_t type called dog1
dog_t dog1;

//Set the age of dog1 to 2 (get it from mptr)
dog1.setAge(*mptr);

//Set the name of dog1 to your string Name that has Padme stored in it.)
dog1.setName(*name);

//call dog1.print(), should print out: Dog> Name: Padme, Age: 2, Breed: Unknown
    (dog1).printdg();

//Set the pointer of animal1 to point to the address of dog1.
animal = &dog1;

//Call animal1.print() This time use arrow operator (makes no difference which you use but wanted you to try both ways)
animal->printanimal();

//Let's set the Breed of Dog1 to string str which has "Cavalier Spaniel".
//To do it call setBreed to the dog1 object
//Notice that if you tried to do it to the animal1 object you would get an error.
dog1.setbreed(str);


//animal1->setBreed(str); //Try it by uncommenting this then comment it again after you see the error
//Call animal1.print() (if you accidentally use member access instead of arrow, you will see a nice error try it, see it, then do it the right way.
animal->printanimal();

//Call dog1.print();
    dog1.printdg();

//Create a bird_t pointer called birds
bird_t *birds;

//Dynamically allocate an array of size y (see top of main)
birds = new bird_t[y];

//create a new house_t pointer called house, then dynamically allocate it using malloc; (2lines)
house_t *house;
house = (house_t*) malloc(sizeof(house_t));


//Lets place Padme into the house struct (1 line of code so don't do anything weird)
house->name = str;

//lets place all our 10 birds into the house (1 line of code so don't do anything weird)
house->birds = birds ;
cout << "\nHouse:" << endl;
dog1.printdg();
//using house print out all the birds and dogs that live there. You'll need a loop for the birds
for (int i  =0; i < y; i++){
    house->birds[i].print(); //.print();
}

//(remember y tells us how many there are)
//Great Job!!!! We have given home to all these beautiful animals. Remember to adopt your next pet and support responsible breeding!
//
//...20 years later...
//
//All the dogs and birds are death. circle of life, hakuna matata, They lived happy lives. Time to bury/cremate the remains...
//de-allocate the memory of the birds (from the house) (don't worry they will be in our hearts forever!) use delete.
delete [] birds;

//set to null after... I know rough!
birds = NULL;


//We cannot de-allocate the memory of the dog in the house using free or delete as she was not dynamically allocated.
//If we tried it we would get a core dump, try it:
//free(house->dogs); //Make sure you uncomment after you try it.
//What we can do is set the dogs pointer to NULL so we don't accidentally try to access it since the dog is stil there (Padme is indestructible!)




//This program went dark real fast! I guess let's just call it a day :\
//Free up your last pointers and submit this. That includes anything we dynamically allocated. So like the animal1 we did.
//Oh wait we can't access it because we overwrote it! MEMORY LEAK :( Well at least when program ends it will be back but SHAME ON YOU
//for not noticing. That's literally like we forgot our animal in the park! Well nothing to do now.
//Still make sure you de-allocate other pointers like house in general.
    delete house;
    house = NULL;
    delete mptr;
    mptr= NULL;
//Note that had we called free(house) before deleting individual objects we would have ended up with memory leaks.
// Use free or delete for the rest of the pointers. Don't forget to set them to null so we don't have any dangling pointers as well
    cout << "F" << endl; //Also don't forget to cout F to pay respects to dogs and birds. RIP
    return 0;//Disclaimer: No Animals, Dogs, or Birds were harmed in the making of this program. The same cannot be said about memory locations.
}

