/*
* Name: Daniel Hinga,
* Description: practice oprator overloading without stings
* Input: operand and characters
* Output: operand operations when overloades
*/



#include <iostream>
using namespace std;


const int buffersize = 100;

class stringg{
public:
    int wordCount(){
        return size;
    }
    stringg(){
        size = 0;
        word = new char[buffersize];
    }


    friend istream& operator >>(istream& in, stringg& data);
    friend ostream& operator <<(ostream& out,const stringg& info);
    stringg operator +(stringg rightside);
    stringg operator -(stringg rightside);
    stringg operator *(int multiplier);
    stringg * operator / (int divisor);
    stringg operator % (int module);

~stringg(){

    delete word;
    word = NULL;

}
private:

    int size;
    char* word;
};

/*
//readword function that takes the characters from file and checks if theres a blank, end of line, or end of file
char *readword(bool &newline, int &size){

    char* word = new char[buffersize];
    for(int i =0; i<buffersize; i++) word[i] = '\0'; //Initialize array starting from
    //the first element with a bunch of '\0' for 100 spots (full array)
    //memset(word, '\0', 100*sizeof(char)); //this would work too if we
    //included the cstring library.
    size = 0;
    char c = getchar();
    for(size=0; size<buffersize && !(c == ' ' || c == '\n' || c == EOF) ;size++){
        word[size] = c;
        c = getchar();
    }
    if(c == '\n'){
        cout << "WOULD YOU LOOK AT THAT, A LINE FEED DETECTED!" << endl;
        newline = true;
    }
    cout << "Size: " << size << endl;
    return word;
}
//printing my string dynamic character
void printstring(char *mystr){
    char *ptr = mystr;
    while(*ptr != '\0'){
        cout << *ptr;
        ptr++;
    }
}

*/
istream& operator >>(istream& in, stringg& data){
    in >> data.word[data.size];
    // brings the reader back
    for (data.size = 1 ; cin.peek() != ' ' && cin.peek() != '\n' ; data.size++){
        in >> data.word[data.size];
    }
    return in;
}

ostream& operator <<(ostream& out, const stringg& info){
    for (int i = 0; i < info.size; i++){
        out  << info.word[i] ;
    }
    return out;
}

//this will overload the add operator to add the second word
stringg stringg:: operator +(stringg rightside){
    //this will make sure no chages will be made to entered word
    stringg original;
    //store the size
    original.size = this->size;
    //loop to deep copy in word to original to not mess with in word
    for(int i = 0; i < original.size; i++){
        original.word[i] = this->word[i];
    }


    //create an object to temporary deep copy to
    stringg temp;
    //the new size should be the original + the size of the new word
    temp.size = original.size + rightside.size;
    //this will deep copy the contents of the original word and store it in temp
    for(int i = 0; i < temp.size; i++){
        temp.word[i] = original.word[i];
    }

    //this eill keep adding the word intil the end of the new size
    for(int i = original.size ; i < temp.size; i++){
        //[i - og size] this is beecause we need i to begin at 0;
        temp.word[i] = rightside.word[i - (original.size) ];
    }

    return temp;
}

//overload the multiple operator
stringg stringg:: operator *(int multiplier){

    //this will make sure no chages will be made to entered word
    stringg original;
    //store the size
    original.size = this->size;
    //loop to deep copy in word to original to not mess with in word
    for(int i = 0; i < original.size; i++){
        original.word[i] = this->word[i];
    }

    //create an object to temporary deep copy to
    stringg temp;
    //the new size should be the original + the size of the new word
    temp.size = original.size;
    //this will deep copy the contents of the original word and store it in temp
    for(int i = 0; i < temp.size; i++){
        temp.word[i] = original.word[i];
    }

    //this function will add the word of its self; primal multiply
    for(int i = 0; i < multiplier - 1; i++){
        // its multiplier - 1 because it has one word of itself
        //this wil add the whatever it is by what is it and an original
        temp = temp + original ;
    }

    return temp;
}

//overload the modulous
stringg stringg::operator%(int module) {
    //this will make sure no chages will be made to entered word
    stringg original;
    //store the size
    original.size = this->size;
    //loop to deep copy in word to original to not mess with in word
    for(int i = 0; i < original.size; i++){
        original.word[i] = this->word[i];
    }

    //returning object that we will modify
    stringg temp;
    //this will be the number of char that the remaider would return
    temp.size = (original.size) % module;
    //this starts at the last characters before remainder size till original word
    for(int i = (original.size) - temp.size ; i < original.size; i++){
    // temp starts at o by subtracting it by itself first
     temp.word[i - ((original.size) - temp.size )] = original.word[i];
    }

    return temp;
}

//subtraction overload
stringg stringg:: operator -(stringg rightside){


    //this will make sure no chages will be made to entered word
    stringg original;
    //store the size
    original.size = this->size;
    //loop to deep copy in word to original to not mess with in word
    for(int i = 0; i < original.size; i++){
        original.word[i] = this->word[i];
    }

    //returning object
    stringg temp;
    //the total size will be the differnce in letters
    temp.size = original.size - rightside.size;

    int i, j;
    int found = 0;
    for(i=0; i<original.size; i++){
       found = 0;
        for(j=0; j<rightside.size; j++){
            if(original.word[i+j] == rightside.word[j]){

                found = 1;

                break;
            }
        }
             //If word has been found then remove it by shifting characters
            if(found == 1){
                for(j=i; j <=(original.size - rightside.size); j++){
                    temp.word[j] = original.word[j + rightside.size];
                }
                // Terminate from loop so only first occurrence is removed
            }else{
                //if not found loop again
                continue;
            }
    }
    return temp;
}

// overload divison while retrning a pointer array
stringg * stringg::operator/(int divisor) {

    //this will make sure no chages will be made to entered word
    stringg original;
    //store the size
    original.size = this->size;
    //loop to deep copy in word to original to not mess with in word
    for (int i = 0; i < original.size; i++) {
        original.word[i] = this->word[i];
    }

    // returning object of pointer
    stringg *temp = NULL;
    // devisor basically makes the size of the array;

    //what happens if devisor is just 1
    if (divisor == 1) {
        //crate new alloated space of 1 size
        temp = new stringg[divisor];

        //this will make temp return the original word
        for (int i = 0; i < original.size; i++) {
            temp->word[i] = original.word[i];
        }


    }
    if (divisor == 0) {
        // this will allocate the space of 1
        temp = new stringg[1];
        for (int i = 0; i < original.size; i++) {
            // set the char array to to null
            temp[0].word[i] = '\0';
        }

    }
    if (divisor > 1) {
        // this will allocate the space of the divisor
        temp = new stringg[divisor];


        for (int i = 0; i < original.size; i++) {
            temp[i].size = this->size / divisor;

            // temp[i].size = this->size/divisor;
            for(int j = 0; j < divisor; j++){
            temp[j].word[i] = original.word[i];
             }


        }
    }
        //delete temp;
        return temp;

}



int main(){

    stringg *firstword;
    // object firstword from stringg to grab the firstword thing in the  file
    firstword = new stringg;
    // object second from stringg to grab the second thing in the file
    stringg second;
    // char made for when we pass the operation in the file
    char opert;
    // int made for when we pass the  value from the file
    int x;
    // brings in the firstword objeft
    cin >> *firstword ;
    // loop to keep grabbing while theres a cin
    while( cin >> opert)
    {
    // switch for different operations
        switch(opert)
        {
            // case if operation is additon
            case '+':
                cout << "What is the second word" << endl;
                cin >> second;
                cout << *firstword + second << endl;
                break;
        // case if operation is subtraction
            case '-':
                cout << "What is the second word" << endl;
                cin >> second;
                cout << *firstword - second << endl;
                break;
                // case if operation is multiplication
            case '*':
                cout << "what is multiple number " << endl;
                cin >> x;
                cout << *firstword * x << endl;
                break;
                // case if operation is modulus
            case '%':
                cout << "What is the remainder wanted" << endl;
                cin >> x;
                cout << *firstword % x << endl;
                break;
                // case if operation is division
            case '/':
                cout << "What is the word to be diveded by what number" << endl;
                cin >> x;
                firstword = (*firstword / x);
                for(int i = 0 ; i < x ; i++){
                    cout << *(firstword + i) << endl;
                }
                break;
            default:
                cout<< "error enter correct operand"<< endl;
                continue;
        }
    }



    return 0;
}

