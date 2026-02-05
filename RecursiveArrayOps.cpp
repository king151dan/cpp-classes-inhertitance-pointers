/*
* Name: Daniel Hinga, 
* Description: test a few recursive functions for performing simple
    computations and execute your program by using data-in by linux input redirection with the attached client code
* Input: The first line contains an integer representing number of integers
    on line 3. The second line contains an integer representing the number of characters in line 4. Line 4 is
    the aforementioned characters. Whitespace is not counted in the character count given in line 2.
* Output: the calulated information.
*/

#include <iostream>
using namespace std;
//CS 202 AST 10
//Skeleton program by Jorge Fonseca
int min2(int, int);
int intSum(int[], int);
int minEntry(int[], int);
int vowelCount(char[], int);
void printArray(int[], int);
void printArray(char[], int);
bool areEqual(int[], int[], int, int);

int main(int argc, char* argv[]) {
    int n,m;
    cin >> n >> m;
    int *a;
    char *c;
    a = new int[n];
    c = new char[m];
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<m;i++) cin >> c[i];
    cout << n << " Integers:\n";
    printArray(a,n);
    cout << "\nSum: " << intSum(a,n);
   cout << "\nMin: " << minEntry(a, n);
    cout << "\n\n" << m << " Characters:\n";
    printArray(c,m);
   cout << "\nVowel Count: " << vowelCount(c, m);
    int a2[6] = {2, 3, 6, 2,
                 4, 6};
    cout << "\n\nTesting Equality with a2... ";
    if(areEqual(a, a2, n, 6)) cout << "They are Equal.\n";
    else cout << "They are not equal.\n";
    return 0;
}

int intSum(int a[], int n) {
    if(n == 1)
        return a[0];
    else
        return ( intSum(a, n-1) + a[n-1]);
}


int min2(int a, int b) {
    return ( (a<b) ? a : b );
}

//Your Code Here(minEntry and vowelCount)
// Write a recursive function that returns the minumum element in an integer array a[] of size n.
//founded from example
int minEntry(int a[], int n) {
    //in case there is its an aray of 1 for no reson
    if (n == 1) {
        //return the only array
        return a[0];
    }else
    return min2(a[n-1], minEntry(a, n-1));
    // recall min 2 with minenry to compaer the differences between them and since min 2 only retuns..
    //..the min so no need of variable cration to store it.
    }



//Write a recursive function that counts vowels (upper and lowercase) in a given character array c[] of size n.
int vowelCount(char c[], int n){
    //create a variable to return
    int vcount=0;
    //make a vouel list in in both uperand lower case vowel to  check
    char vowel[10] = {'A', 'E', 'O', 'I', 'U', 'a', 'e', 'o', 'i', 'u'};
    //this is for when n is -1 because we need the array of 0 index to be ran
    if (n == -1){
        return vcount;
    }else{
        //this is when n is greater or equal to 0;
        for (int i = 0; i < 10 ; i++) {
            //loop to check each n to every vowel in array
            if (c[n] == vowel[i] ){
                //if its found incrase the vowel count by 1
              vcount++;
            }
        }
        //once the vowel is found return vcount and call the function again with the increased vowel count
        return (vcount + vowelCount(c, n - 1));
    }
}

void printArray(int a[], int n) {
    //this acts as a stop for the recall
    if(n>0) {
        printArray(a, n-1);//tail
        cout << a[n-1] << " "; //head
    }
}

void printArray(char a[], int n) {
    if(n>0) {
        printArray(a, n-1);//tail
        cout << a[n-1] << " "; //head
    }

}

bool areEqual(int a[], int b[], int n1, int n2) {
    // if  the sizes are not the same it will return false
    if( n1 != n2){
        return false;
    }else{
        // where it checks if the values are the same if it is increment
        if(a[n1-1] == b[n2-1]){
            return areEqual(a,b,n1-1,n2-1);
        }
        if(n1 == 0 ){ return true;}
        // if theres no more left in the size it returns true
    }
}
