/*
* Name: Daniel Hinga,
* Description:write and test a few recursive functions for performing simple
    computations. by linux input redirection

* Input: The first line contains an integer representing number of
        integers on line 2. The second line contains the integer array, each integer is separated by a space. The
    third line is the integer we will be searching for. The fourth line is the integer which we want to print its
    digits in reverse.

* Output: stdout to file and results of program.
*/


#include <iostream>
using namespace std;
//CS 202 AST 11
//Skeleton program by Jorge Fonseca
bool elementPresent(int[], int, int);
void reverseDisplay(int);
void reverse(int[], int, int);
bool isPalindrome(int[], int, int);
void printArray(int[], int);

int main(int argc, char* argv[]) {
    int n, x, y;
    cin >> n;
    int *a;
    a = new int[n];
    for(int i=0;i<n;i++) cin >> a[i];
    cin >> x;
    cin >> y;
    cout << n << " Integer Array:\n";
    printArray(a,n);
    cout << "\nReverse of Given Array:" << endl;
    reverse(a, 0, n);
    printArray(a,n);
    cout << "\n\nis " << x << " present in given array?\n";
    if(elementPresent(a, n, x)) cout << "Aye, Aye Captain!\n";
    else cout << "That's a negative, Captain!\n";
    cout << "\nGiven Integer is: " << y;
    cout << "\nReverse: ";
    reverseDisplay(y);
    cout << "\n\nIs given array a palindrome?\n";
   if(isPalindrome(a, 0, n)) cout << "Afirmative, Captain!\n";
    else cout << "Does not look like it, Captain!\n";
    cout << "\nIs 2 3 5 3 2 a palindrome?\n";
    int b[5] = { 2, 3, 5, 3, 2};
   if(isPalindrome(b, 0, 5)) cout << "Afirmative, Captain!";
   else cout << "Does not look like it, Captain!";
    cout << endl;
    return 0;
}

void printArray(int a[], int n) {
    if(n>0) {
        printArray(a, n-1); //tail
        cout << a[n-1] << " "; //head
    }
}

//Write a recursive function that returns true if integer x is found in integer array a of size n.
bool elementPresent(int a[], int n, int x) {

    //true if x is found at index n
    if (x == a[n]){
        return true;
    }else if(x != a[n] ) {
        // if x is not located at index at n and..

        //..if n is not at 0..
        if (n != 0) {
            //...call the function again but n is going down by 1 till 0
            return elementPresent(a, n - 1, x);
        }else
            return false;
        //if at 0 and x not found return false
    }
}

//Write a recursive function that outputs to stdout the reverse of the given integer.
void reverseDisplay(int x) {
    // thsi will end  once x cannot be less than 0 and has to stop on first
    if(x > 0){
        //%10 to print the remainder of the the array

         cout<< x % 10 ;
         //call the function again, divide it by 10 and cut off/ trow away the remainder
        reverseDisplay(x/10);
    }
}

//Write a recursive function that reverses the content of a n integer array a[].
void reverse(int a[], int left, int right) {
    //make a makeshift bubble sort
    //if statement to make left go untill the index is less than that of right, basically half way
    if (left < right ){
        //temp to store swithing int of the left int.
       int temp = a[left];
       //original is swaped with the right int (-1 cause arrays start at 0)
        a[left] = a[right-1];
        //then the right is switched the left original stored in in temp
        a[right-1] = temp;

        //call itself but increasing the left by 1 and decreasing right also by one.
        reverse(a, left+1 , right-1 );
    }

}


//Write a recursive function that checks if a given array is a palindrome given the left parameter
//is the beginning of the array (0) and the right one is the end of the array (size)
bool isPalindrome(int a[], int left, int right) {
    //if the left side is not equal to the right side (-1 casue arrays start at 0) return false
    if (a[left] != a[right-1] ) {
        return false;
    } else {
        // where it checks if the values are the same if it is increment
        if (left < right) {
            return isPalindrome(a, left + 1, right - 1);
        } else{
            // if theres no more left in the size it returns true
            return true;
        }
    }
}

