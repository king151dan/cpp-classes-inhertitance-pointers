/*
* Name: Daniel Hinga
* Description: C++ program that  will hack the key system
* Input: none.
* Output: hack and display the hacked password.
*/


#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string>

#ifndef VAULT_H
#include "vault.h"
#endif

/*
These #ifdef DEBUG you see are activated in vault.h you can 
uncomment #define DEBUG there to help you work on the assignment,
but your program must work for BOTH cases when
#define DEBUG is commented out and when it's not. Please add extra 
comments with memory addresses and what you are doing in that 
version. otherwise DO NOT TOUCH vault.h Good luck, Agent! -JF
*/

using namespace std;

int main(){
#ifndef DEBUG
	srand (time(NULL)); // For Rand to seed correctly
#endif
	//Create Key
	key_gen k;

	//Create Variables to store hax0red numbers.
	num h0=0, h1=0, h2=0, h3=0, h4=0, h5=0, h6=0;

	//Check if Haxed:
	k.iskey(h0, h1, h2, h3, h4, h5, h6);

	cout << "\n**Beginning Hack**\n" << endl;

	//Test if lockout works
	for(int i=0; i<15;i++)
	;//	k.iskey(h0, h1, h2, h3, h4, h5, h6);
	
	//Debug
	cout << "Initial Hacked:" << endl;
	cout << h0 << " " << h1 << " " << h2 << " ";
	cout << h3 << " " << h4 << " " << h5 << " " << h6 << endl;



	//Your Code Here:
    //VAULT 0: Easy one they didn't even try...
    //h0 set to from class k vault 0 public variable num key
    h0 = k.v0->key;

	//VAULT 1: Should be easy too
	//call the function maintanace to activate and place the adress of key into pointer maintanance.
	k.v1.maintenanceMode();
	//create a new pointer variable same type as the one ine vault to copy
	num *hackedv1 ;
	//set the new pointer equal to the same pointer as the key which has the adress
	hackedv1 = k.v1.maintenance;
	//set h0 with whatever is stored at the adress of of the new coppied cariable.
	h1 = *hackedv1;


    //VAULT 2: You'll need some pointer casting
    //calls the funtion to place the adress of the key into maintanance;
    k.v2.maintenanceMode();
    //poiner reintpret cast(yolo cast) to the same as h2 from the void maintanace pointer.
    h2 = *(reinterpret_cast<num*>((k.v2.maintenance)));


    //VAULT 3: Kind of a mix of the previous two with static_cast
    //call in the void pointer function to return the key
    k.v3.maintenanceMode();
    // satic cast to num pointer from whatever the function returns( the adress of the key)
    h3 = *(static_cast<num *>(k.v3.maintenanceMode()));


    //VAULT 4: (In array) Hint: use a loop and pointer arithmetics to traverse array (like key[0] to key[1]
    //call function that sill give us the adress the oif the very first part of the key
    k.v4.diversionMode();
    //create a new pointer to store where the false key locations
    num * hackedfkey = &(k.v4.falsekey);
    //for loop for goes through all the array till it hits the key
    for (int i = 0; i < 6;i++ ){
        //keeps moving foward 1 adress;
        hackedfkey++;
    }
    //place whatever is in the hacked key into h4
    h4 = *hackedfkey;



	//VAULT 5: (pointer magic/arithmentic to move around struct)
	//create a new int pointer to store the the adress of the keys location
	int *v5ptr = &k.v5->zero;
	//traverse through the variables though pointes starting at int zero and adding the value of 4 adresses
	h5 = *(v5ptr+4);




	//VAULT 6: (Using a struct equivalent of our vault6 class and reinterpret_cast) //Use the method I showed in class)
    //create a class that is similar to the variables in class vault 6
    struct hack{
        char madeby[14];
        num falsekey;
        num key;
        int denied;
    };
    // new pointer of struct hack
    hack *hackedptr ;
    // make whatever is in vault 6 into the a hack pointer to be able to store it
    hackedptr = reinterpret_cast<hack*>(&(k.v6));
    cout << "v6 original key value: "<<  hackedptr->key<< endl;
    //hacked ptr is a pointer, key is an adress and setting the stuff in adress to 0.
    hackedptr->key = 0;
	{
	//IN this case I want you to print out the original value of k.v6's key but then change it to zero.

#ifdef DEBUG
	 cout << "V6 Key New Value: " << k.v6.getKey() << endl;
#endif
	 h6=0;
	}
	h6=0;


	//End of Your Code
	cout << "\nStatus of Hacked:" << endl;
	cout << h0 << " " << h1 << " " << h2 << " ";
	cout << h3 << " " << h4 << " " << h5 << " " << h6 << endl;

	
	//Debug Solution
#ifdef DEBUG
	cout << k.v0->key << " " << k.v1.getKey() << " ";
	cout << k.v2.getKey() << " " << k.v3.getKey();
	cout << " " << k.v4.getKey() << " " << k.v5->getKey();
	cout << " " << k.v6.getKey() << endl;
#endif
	cout << endl;

	//Check if Haxed:
	if(k.iskey(h0, h1, h2, h3, h4, h5, h6)){
		cout << "\n!!!!1337 Success!!!!\n" << endl; //if this prints you finished your homework :D
	}

	return 0;
}










