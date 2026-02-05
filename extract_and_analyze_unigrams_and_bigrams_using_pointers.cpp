/*
* Name: Daniel Hinga, NSHE ID 2001442321, Assignment 5
* Description: C++ program that will extract the unigrams and
  bigrams from a text file and allow you to do some analysis on them using pointers.
* Input: file to read in text and user interface
* Output: 3 file created, 1 unigrams, 2 bigrams, 3 replacement words .
*/

#include <iostream>
#include <cctype>
#include <fstream>
#include <string>

using namespace std;

// struct created for the Unigram
struct Unigram{
    // word to store the unigram
    string word;
    // freq of the words to be read in
    int frequency;
};
//struct crated for the Bigram
struct Bigram{
    // word1 of the Bigram
    string word1;
    // word2 of the Bigram
    string word2;
    // store the frequency of the words
    int frequency;
};

// prototypes
int readdata(string, string*&, int&);
int getLongestWord(string* , int);
void cleanUp(string*, int);
int inList(string, Unigram*, int&);
int inList(string, string, Bigram*, int&);
void generate_unigrams(Unigram*, int&, string*, int);
void generate_bigrams(Bigram*, int&, string*, int);
void sortgms(Unigram*, int);
void sortgms(Bigram*, int);
void write1gmalog(Unigram*, int);
void write2gmalog(Bigram*, int);

int main(int argc, char *argv[]){


    if (argc != 2){
        cout << "invalid arguments\nusage: ./a.out filename "<<endl;
        return 1;
    }
    string filename = argv[1];



    // unigram pointer of unigram type
    Unigram *unigram;
    unigram = NULL;
    //bigram pointer of bigram type
    Bigram *bigram;
    bigram = NULL;
    // string pointer array
    string *word;
    word = NULL;

    int wordCount = 0;
    int unigramCount = 0;
    int bigramCount = 0;
    readdata(filename, word, wordCount);


    //dynamic allocation of the unigrams and bigrams
    unigram = new Unigram[wordCount];
    bigram = new Bigram[wordCount];


    cout << "*******JF***********************************************" << endl;

    // calls the function for the clean up of the words
    cleanUp(word, wordCount);
    // calls the functions get the longest word
    getLongestWord(word, wordCount);

    //genertate the bigram and unigram
    generate_unigrams(unigram, unigramCount, word, wordCount);
    generate_bigrams(bigram, bigramCount, word, wordCount);

    // sort the bigrams and unigrams
    sortgms(unigram, unigramCount);
    sortgms(bigram, bigramCount);// calls the function of sorting the unigram

    //first choice of user in main comand
    string user1in;
    //string to enter for the search of unigrams
    string unisearch;


    do{
        //main commads to come up
        cout << "\nCommands\n" <<
             "Unigram: search for unigram\n" <<
             "Bigram : search for bigram\n" <<
             "Save : save 1gms.txt and 2gms.txt\n" <<
             "Index : print index of unigram or bigram\n" <<
             "Quit/q : terminate program" <<
             " Choose your command:" << " " << endl;
        // enter the main comand choice
        cin >> user1in;

        //for loop to auto lower every letter.
        for (int i = 0; i < user1in.length(); i++){
            user1in[i] = tolower(user1in[i]);
        }

        if (user1in == "unigram"){

            int search;
            cout << " Enter Word To Search: ";
            cin >> unisearch; // where we input the word we are looking for
            search = inList(unisearch, unigram, unigramCount);
            cout << "Searching for " << unisearch << endl;
            // error checking
            if (search == -1){
                cout << "unigram not found" << endl;
            }
            else{
                cout << " Unigram Found at Index " << search << " " <<
                " with frequency of " << unigram[search].frequency << endl;
            }
        }
        else if (user1in == "bigram"){

            string bigramword1;
            string bigramword2;
            bool search;
            cout << "enter first word to search: ";
            cin >> bigramword1;
            search = inList(bigramword1, bigramword2, bigram, bigramCount);
            cout << "enter second word to search: ";
            cin >> bigramword2;
            search = inList(bigramword1, bigramword2, bigram, bigramCount);
            cout << search << endl;
            cout << "Searching for " << bigramword1 << " " << bigramword2 << endl;

            if (!search){
                cout << " Word is not in the file" << endl;
            }else{
                cout << "Bigram found at index: " << search
                << " with frequency of " << bigram[search].frequency << endl;
            }

        }else if (user1in == "q" or user1in == "Q" or user1in == "quit"){
            cout << " Good Bye" << endl;
            // deallocates unigram
            delete unigram;
            //deallocates bigram
            delete bigram;
            //deallocates word
            delete word;

            return 0;
        }
        else if (user1in == "index"){
            int choice;
            string choice2;

            cout << " Enter Index: ";
            cin >> choice;
            cout << " Unigram , or Bigram? ";
            cin >> choice2;

            for (int i = 0; i < choice2.length(); i++){
                choice2[i] = tolower(choice2[i]);
            }

            if (choice2 == "unigram"){

                cout << " Index " << choice << " : " << unigram[choice].word
                     << " with a frequency of "  << unigram[choice].frequency;
            }
            else if (choice2 == "bigram"){
                cout << " Index: "  << choice << " : "
                << bigram[choice].word1 << " " << bigram[choice].word2
                << " with the frequency of " << bigram[choice].frequency;
            }
        }
        else if (user1in == "save"){
            cout << "Writing log to 1gms.txt" << endl;
            cout << "Writing log to 2gms.txt" << endl;

            write1gmalog(unigram, unigramCount);
            write2gmalog(bigram, bigramCount);

        }
    } while (true);
}

// this function opens the file fstream
int readdata(string filename, string*& word, int& wordCount){
    //initial file to open and count the words in the file
    ifstream infileCount;
    // file to actually store the words
    ifstream infilec;
    //create a temporrary string to store inital words
    string tempstore;
    //open the file to count the words using filename pased in
    infileCount.open(filename.c_str());

    //if the file doesnt open terminate the program
    if(!infileCount.is_open()){
        cout << " File can not be opened " << endl;
        return 0;
    }

    infilec.open(filename.c_str());
    //if not at enf of file count words
    while (!infileCount.eof()){
        infileCount >> tempstore;
        wordCount++;
    }

    //allocates the string of word using the size of the initial wordcount
    word = new string[wordCount];

    //for loop to place the words into the the open file to store them
    for (int i = 0; i < wordCount; i++){
        infilec >> word[i];
    }

    cout << "openning file: "<< filename
         << "\nFinished reading "<< wordCount
         << " words. "<< "closing file: "<< endl;

    //close the files open
    infileCount.close();
    infilec.close();
    return 1;
}


// function that grabs the longest word
int getLongestWord(string* word, int size){


    // string to store the longest word
    string longword;

    //this will make sure that whenever the word is to come is bigger tiwill place it ib longword
    for(int j =0; j < size; j ++){
        if (longword.length() < word[j].length()){
            longword = word[j];
        }
    }

    cout << "Longest Word: "<<   longword<< endl;
    return sizeof(longword);
}

// this is the function that cleans up the words
void cleanUp(string* word, int wordCount){
    //store the users chioce
    char userchoice;
    //file to stoer the non alphanumeric replacement log file
    ofstream ofile;
    bool logging = false;


    cout<< "log clean up?(y/n).... ";
    cin >> userchoice;

    // cleans it up if users chooses to
    if (userchoice == 'Y' || userchoice == 'y'){
        cout<< "writing log to \"ast1log.txt\""<< endl;
        ofile.open("ast1log.txt");
        ofile << "non alphanumeric replacement log file:\n" << endl;
        logging = true;
    }

    // lower cases all the words
    for (int i = 0; i < wordCount; i++){
        for (int j = 0; j < word[i].length(); j++){
            word[i][j] = tolower(word[i][j]);
        }
    }

    // removes all the random punctuations
    for (int i = 0; i < wordCount; i++){
        for (int j = 0; j < word[i].length(); j++){
            if (!isalpha(word[i][j])) {
                if (!isdigit(word[i][j])) {
                    word[i].erase(j, 1);
                }
            }
            // makes words that has numbers in it into NON ALPHA
            if (isdigit(word[i][j])){
                word[i] = "NONALPHA";
            }
        }
    }

    //after all clean up had been done store the words
    for (int i = 0; i < wordCount; i++){
        ofile << word[i] << endl;
    }
    //close the file.
    ofile.close();
}

//searches to see if the word is in the unigrams
int inList(string word, Unigram* unigram, int& count){
    for (int i = 0; i < count; i++){
        if (unigram[i].word == word){
            return i;
        }
    }
    return -1;
}

// where the bigram gets listed
int inList(string word1, string word2, Bigram* bigram, int& count){
    for (int i = 0; i < count; i++){
        if (word1 == bigram[i].word1 and word2 == bigram[i].word2){
            return i;
        }
    }
    return -1;
}


// generate bigrams
void generate_bigrams(Bigram* bigram, int& bigramCount, string* word, int wordCount){

    for (int i = 0; i < wordCount - 1; i++){
        //make sure that the eithe words are not bigrams
        if (word[i] != "NONALPHA" and word[i + 1] != "NONALPHA"){

            int index;
            //placeof the word
            index = inList(word[i], word[i + 1], bigram, bigramCount);

            if (index == -1){
                //first word
                bigram[bigramCount].word1 = word[i];
                // second word  is the second word stored
                bigram[bigramCount].word2 = word[i + 1];
                bigram[bigramCount].frequency = 1;
                //increase the count of bigrams
                bigramCount++;

            }
            else{
                // if there is already a bigram just add freq
                bigram[index].frequency++;
            }
        }
    }
}


// where the unigram gets generated
void generate_unigrams(Unigram* unigram, int& unigramCount, string* word, int wordCount){

    for (int i = 0; i < wordCount; i++)
    {
        if (word[i] != "NONALPHA")
        {
            int index;
            //position of the word
            index = inList(word[i], unigram, unigramCount);

            //if the the word is not found alreay then placed in unigram
            if (index == -1){
                unigram[unigramCount].word = word[i];
                unigram[unigramCount].frequency = 1;
                //adds the ammount of unigrams
                unigramCount++;

            }
            else{
                //if there is already a unigram add that it has more freq
                unigram[index].frequency++;
            }
        }
    }
}


// the function that sorts the list of unigram
void sortgms(Unigram* unigram, int unigramCount){

    // only way to store the temp words cause the type is the same
    struct Unigram temp;
    //variable to store the freaq to use in the bubbble sort
    int tempnumber;

    //basic bubble sort to sort the word and freq
    for (int i = 0; i < unigramCount; i++){
        for (int j = 0; j < unigramCount; j++){
            // this will sort the words in frequency order
            if (unigram[j].frequency < unigram[j + 1].frequency){

                //this will sort the words
                temp = unigram[j];
                unigram[j] = unigram[j + 1];
                unigram[j + 1] = temp;

                //this will sort the frquency while sorting the name
                tempnumber = unigram[j].frequency;
                unigram[j].frequency = unigram[j + 1].frequency;
                unigram[j + 1].frequency = tempnumber;
            }
        }
    }
}

// sorts the list of bigrams
void sortgms(Bigram * bigram, int bigramCount){
    //variable to help switch the freq
    int freqswap = 0;
    //struct to help swap the words cause it will be the same type
    struct Bigram temp;

    //big bubbble sort for bigram both words and freq swaping
    for (int i = 0; i < bigramCount - 1; i++){
        for (int j = 0; j < bigramCount - 1; j++){
            if (bigram[j].word1 > bigram[j + 1].word1){
                temp = bigram[j];
                bigram[j] = bigram[j + 1];
                bigram[j + 1] = temp;

                //swaping the frequency
                freqswap = bigram[j].frequency;
                bigram[j].frequency = bigram[j + 1].frequency;
                bigram[j + 1].frequency = freqswap;


            }
            if (bigram[j].word1 == bigram[j + 1].word1){
                if (bigram[j].word2 > bigram[j + 1].word2){
                    temp = bigram[j];
                    bigram[j] = bigram[j + 1];
                    bigram[j + 1] = temp;


                    freqswap = bigram[j].frequency;
                    bigram[j].frequency = bigram[j + 1].frequency;
                    bigram[j + 1].frequency = freqswap;


                }
            }
        }
    }

}

void write1gmalog(Unigram* unigram, int unigramCount){
    //crate the file for unigrams
    ofstream unigramwrite;
    unigramwrite.open("1gms.txt");

    //write the words into the file.
    for (int i = 0; i < unigramCount; i++){
        unigramwrite << unigram[i].word << " " << unigram[i].frequency << endl;
    }
    //close the file after done.
    unigramwrite.close();
}
// where we write the bigram in an output file
void write2gmalog(Bigram* bigram, int bigramCount){

    //crate a file to store the bigrams
    ofstream bigramwrite;
    bigramwrite.open("2gms.txt");

    //write bigram into the file.
    for (int i = 0; i < bigramCount; i++){
        bigramwrite << bigram[i].word1 << " " << bigram[i].word2
                    << " " << bigram[i].frequency << endl;
    }
    //close the file
    bigramwrite.close();
}

