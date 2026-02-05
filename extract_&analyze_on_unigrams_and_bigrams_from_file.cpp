/*
* Name: Daniel Hinga
* Description: C++ program that will extract the unigrams and
  bigrams from a text file and allow you to do some analysis on them.
* Input: file to read in text and user interface
* Output: 3 file created, 1 unigrams, 2 bigrams, 3 replacement words .
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>


using namespace std;
const int ArrayMax = 50000;

struct Unigram  {
    string word;
    int frequency;
};

struct Bigram {
    string word1;
    string word2;
    int frequency;
};


void write1gmslog(struct Bigram bigram[],  int size);
void write1gmslog(struct Unigram unigram[],  int size);
int inList(string word, struct Unigram *list, int count);
int inList(string word1, string word2, struct Bigram *list, int count);
void readdata(string filename, string Word[ArrayMax], int &wordCount);
int getlongestword(string *word, int size);
void cleanup(string *word, int wordCount);
void sortgms(struct Bigram bigram[], int size);
void sortgms(struct Unigram unigram[], int size);
void generate_unigrams(struct Unigram unigram[], int &unigramCount, string word[], int wordCount);
void generate_Bigrams(struct Bigram bigram[], int &bigramCount,string word[], int wordCount);

int main(int argc, char *argv[]) {



    int Wordcount = 0;
    int unigramcount = 0;
    int bigramcount = 0;
    string word[ArrayMax];
    string Filename = argv[1];


    if (argc != 2){
        cout << "invalid arguments\nusage: ./a.out filename "<<endl;
        return 1;
    }
    // first call to read in data and get word count
    readdata(Filename, word, Wordcount);


    string userin;
    Unigram unigram[Wordcount];
    Bigram bigram[Wordcount];

    // rest of the function calls
    cleanup(word, Wordcount);
    getlongestword(word, Wordcount);
    generate_unigrams(unigram, unigramcount, word, Wordcount);
    generate_Bigrams(bigram, bigramcount, word, Wordcount);

    cout << "*******JF***********************************************" << endl;

    cout << "\nCommands\n" <<
         "Unigram: search for unigram\n" <<
         "Bigram : search for bigram\n" <<
         "Save : save 1gms.txt and 2gms.txt\n" <<
         "Index : print index of unigram or bigram\n" <<
         "Quit/q : terminate program" << endl;

    // do while to run at least once
    do{
        cin >> userin;

        // lowers the users input
    for (int i = 0; i < userin.length(); i++) {

        userin[i] = tolower(userin[i]);
    }

    cout << userin << endl;


    if (userin == "unigram") {
        string search;
        cout << "enter word to search: ";
        cin >> search;

        for (int i = 0; i < search.length(); i++) {
            search[i] = tolower(search[i]);
        }
        cout << "searching for " << search << endl;
        int index = inList(search, unigram, unigramcount);
        if (index == -1) {
            cout << "unigram not found" << endl;
        } else {
            cout << "unigram found at index " << index
                 << " with frequency of: " << unigram[index].frequency
                 << endl;
        }
    } else if (userin == "bigram") {
        string search1, search2;
        cout << "enter first word to search: ";
        cin >> search1;

        cout << "enter second word to search: ";
        cin >> search2;
        for (int i = 0; i < search1.length(); i++) {
            search1[i] = tolower(search1[i]);
            search2[i] = tolower(search2[i]);
        }

        cout << "searching for " << search1 << " " << search2 << endl;
        int index = inList(search1, search2, bigram, bigramcount);
        if (index == -1) {
            cout << "bigram not found" << endl;
        } else {
            cout << "Bigram found at index: " << index
                 << "with frequency of: " << bigram[index].frequency
                 << endl;
        }

    } else if (userin == "save") {

        cout<< "writing Log to '1gms.txt'\n"
            << "writing Log to '2gms.txt'\n"<< endl;
        write1gmslog(unigram,Wordcount);
        write1gmslog(bigram,Wordcount);

    } else if (userin == "index") {
        int indexsearch =0;
        string choice = "";
        cout<< "Enter index: ";
        cin>> indexsearch;

        while (cin.fail()or (indexsearch < 0) or (indexsearch > ArrayMax))
        {
            cin.clear(); // clear input buffer to restore cin to a usable state
            cin.ignore(INT_MAX, '\n'); // ignore last input
            cout << "errror .\n";
            cout << "Enter a number.\n";
            cin >> indexsearch;
        }

        cout << "\nunigram or bigram?  ";
        cin >> choice;
        for (int i = 0; i < choice.length(); i++){
            choice[i]= tolower(choice[i]);
        }
        if(choice == "unigram"){

            cout<< "index "<< indexsearch<< ":"
            << unigram[indexsearch].word
            << " with frequency "
            <<  unigram[indexsearch].frequency <<endl;
        }else if (choice == "bigram"){

            cout<< "index "<< indexsearch<< ":"
            << bigram[indexsearch].word1
            <<" " << bigram[indexsearch].word2
            << " with " << bigram[indexsearch].frequency << endl;
        }


    } else if (userin == "q" or userin == "quit") {
        cout<< "goodbye"<< endl;

        return 0;
    }
}while (userin != "q" or userin != "quit");



}

// Reads in the data
void readdata(string Filename, string *Word, int &wordCount) {

    ifstream infile;
    infile.open(Filename.c_str());
    cout << "Array size: "<< ArrayMax << endl;


    while(!infile.is_open()) {
        cout<< "Error File not open\n "
            << "Renter filename: "<< endl;

        cin.clear();
        cin.ignore(100, '\n');
        cin >> Filename;
        infile.open(Filename.c_str());

    }

    for (int i =0; !infile.eof(); i++){
        infile >> Word[i];
        wordCount++;
    }

    infile.close();


    cout << "openning file: "<< Filename
         << "\nFinished reading "<< wordCount
         << " words. "<< "closing file: "<< endl;
}


//This does all the cleanup mentioned. Inside of this function you ask
        //user if they want to log the cleanup and write it out to ast1log.txt
void cleanup(string *word, int wordCount) {


    string input;
    string temp ="";
    bool logging = false;
    ofstream ofile;


    cout<< "log clean up?(y/n).... ";
    cin >> input;
    if (input == "y" or input =="Y"){
        cout<< "writing log to \"ast1log.txt\""<< endl;
        ofile.open("ast1log.txt");
        ofile << "nonalphanumeric replacement log file:\n" << endl;
        logging = true;
    }



    for (int i = 0; i < wordCount; i++){
        //lowercases all the words
        for (int j = 0; j < word[i].length(); j++ ){
            string temp1 = word[i];
            temp1[j] = tolower(temp1[j]);
            word[i] = temp1;

        }
        bool logit = false;


        // removes anything if not  decimal digit or an uppercase or lowercase letter
        string temp3 = "";
        for (int j = 0; j < word[i].length(); j++ ){

            string temp2 = word[i];
            if (isalnum(temp2[j])){

                temp3 += temp2[j];
            }
            else {
                logit = true;
            }
        }



        if (logging and logit){
            ofile << word[i] << "\t\t\t\t" << temp3 << endl;
        }
        word[i]= temp3;

        // checks if characters are alphabet letters
        for(int j =0;j < word[i].length(); j++ ){
            if(!isalpha(temp3[j])){

                if (logging){
                    ofile<< word[i] << "\t\t-->" << "NONALPHA"<< endl;
                }
            }
        }
    }

}


//Returns the index of the longest word in the word array
int getlongestword(string *word, int size) {
    string longword = "";
    longword = word[0];


        for(int j =0; j < size; j ++){

            if (longword.length() < word[j].length()){

                longword = word[j];
            }
        }

    cout << "Longest Word: "<<   longword<< endl;
    return sizeof(longword);
}

//functions create the unigram logs. Basically print out the structs into a text file
void write1gmslog(struct Unigram unigram[],  int size){
    ofstream ofile;
    ofile.open("1gms.txt");

    for(int i = 0; i < size; i++) {
        ofile << unigram[i].word
        << "\t\t-->"
        << unigram[i].frequency<<  endl;
    }
}
//These 2 functions create the logs. Basically print out the structs into a text file
void write1gmslog(struct Bigram bigram[],  int size){
    ofstream ofile;
    ofile.open("2gms.txt");

    for(int i = 0; i < size; i++) {
        ofile << bigram[i].word1 << " "
              << bigram[i].word2 << "\t\t-->"
              << bigram[i].frequency<<  endl;
    }
}


//sort the unigrams
void sortgms(struct Unigram unigram[], int size) {

    int temp;
    string temps;

    for (int i = 1; i < size; i++) {
        for (int j = 0; j < size-i; j++) {

            if (unigram[j].frequency < unigram[j + 1].frequency) {

                temps = unigram[j].word;
                unigram[j].word = unigram[j + 1].word;
                unigram[j + 1].word = temps;

                temp = unigram[j].frequency;
                unigram[j].frequency = unigram[j + 1].frequency;
                unigram[j + 1].frequency = temp;

            }
        }
    }
}


//sort the bigrams
void sortgms(struct Bigram bigram[], int size){

    string temp;

        //bubble sort
        for (int j = 0; j < size; j++ ){
            if (bigram[j].word1 > bigram[j+1].word1){
                temp = bigram[j].word1;
                bigram[j].word1 = bigram[j + 1].word1;
                bigram[j + 1 ].word1 = temp;
            }
        }


    // bubble sort
    for (int i = 0; i < size; i ++){
        for (int j = 0; j < size; j++ ){
            if (bigram[j].word2 > bigram[j+1].word2){
                temp = bigram[j].word2;
                bigram[j].word2 = bigram[j + 1].word2;
                bigram[j + 1 ].word2 = temp;
            }
        }
    }
}


//Checks if word already exists in our array,
//if it does it returns the index. if it does not it returns -1.
int inList(string word, struct Unigram *list, int count) {
    for(int i = 0; i < count; i++ ){

        if (list[i].word == word){
            return i;
        }


    }
    return -1;
}

//Checks if words already exists in our array, if it does it returns the index.
// if it does not it returns -1.
int inList(string word1, string word2, struct Bigram *list, int count) {
    for (int i = 0; i < count; i++) {

        if (list[i].word1 == word1 and list[i].word2 == word2) {
            return i;
        }

    }
    return -1;
}



//This will generate array of unigrams (dictionary) and call the sort function to sort them)
void generate_Bigrams(struct Bigram bigram[], int &bigramCount,string word[], int wordCount){



    for(int i  = 0; i < wordCount; i++){


           int index = inList(word[i], word[i+1], bigram, wordCount);
           if (!index == -1){

               bigram[bigramCount].word1 = word[i];
               bigram[bigramCount].word2 = word[i+1];
               bigram[bigramCount].frequency = 1;
               bigramCount++;
           }
           else{
               bigram[index].frequency++;
           }

    }



sortgms(bigram, wordCount);
}


//This will generate array of unigrams (dictionary) and call the sort function to sort them)
void generate_unigrams(struct Unigram unigram[], int &unigramCount, string word[], int wordCount){

    unigram[0].word = word[0];
    unigram[0].frequency = 1;


  for(int i = 0;i < wordCount; i ++ ){
       int index =  inList(word[i], unigram, wordCount);
        if(index == -1 ){
        unigram[unigramCount].word = word[i];
        unigram[unigramCount].frequency = 1;
        unigramCount++;
        } else{

            unigram[index].frequency++;
        }
    }
   sortgms(unigram, wordCount);

    }






























