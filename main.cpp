/*/$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$
  |______/|______/|______/|______/|______/|______/|______/|______/|______/|______/|______/|______/|______/|______/|______/|______/|______/|______/


   /$$$$$$$                      /$$       /$$                 /$$       /$$           /$$                       /$$       /$$       /$$             /$$
  | $$__  $$                    | $$      | $$                | $$      |__/          | $$                      | $$      | $$      |__/            | $$
  | $$  \ $$  /$$$$$$  /$$   /$$| $$$$$$$ | $$ /$$   /$$      | $$       /$$ /$$$$$$$ | $$   /$$  /$$$$$$   /$$$$$$$      | $$       /$$  /$$$$$$$ /$$$$$$
  | $$  | $$ /$$__  $$| $$  | $$| $$__  $$| $$| $$  | $$      | $$      | $$| $$__  $$| $$  /$$/ /$$__  $$ /$$__  $$      | $$      | $$ /$$_____/|_  $$_/
  | $$  | $$| $$  \ $$| $$  | $$| $$  \ $$| $$| $$  | $$      | $$      | $$| $$  \ $$| $$$$$$/ | $$$$$$$$| $$  | $$      | $$      | $$|  $$$$$$   | $$
  | $$  | $$| $$  | $$| $$  | $$| $$  | $$| $$| $$  | $$      | $$      | $$| $$  | $$| $$_  $$ | $$_____/| $$  | $$      | $$      | $$ \____  $$  | $$ /$$
  | $$$$$$$/|  $$$$$$/|  $$$$$$/| $$$$$$$/| $$|  $$$$$$$      | $$$$$$$$| $$| $$  | $$| $$ \  $$|  $$$$$$$|  $$$$$$$      | $$$$$$$$| $$ /$$$$$$$/  |  $$$$/
  |_______/  \______/  \______/ |_______/ |__/ \____  $$      |________/|__/|__/  |__/|__/  \__/ \_______/ \_______/      |________/|__/|_______/    \___/
                                               /$$  | $$
                                              |  $$$$$$/
                                               \______/

   /$$$$ /$$$$$$$  /$$       /$$       /$$$$$$  /$$$$$$  /$$$$$$$$ /$$$$
  | $$_/| $$__  $$| $$      | $$      |_  $$_/ /$$__  $$|__  $$__/|_  $$
  | $$  | $$  \ $$| $$      | $$        | $$  | $$  \__/   | $$     | $$
  | $$  | $$  | $$| $$      | $$        | $$  |  $$$$$$    | $$     | $$
  | $$  | $$  | $$| $$      | $$        | $$   \____  $$   | $$     | $$
  | $$  | $$  | $$| $$      | $$        | $$   /$$  \ $$   | $$     | $$
  | $$$$| $$$$$$$/| $$$$$$$$| $$$$$$$$ /$$$$$$|  $$$$$$/   | $$    /$$$$
  |____/|_______/ |________/|________/|______/ \______/    |__/   |____/


   /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$
  |______/|______/|______/|______/|______/|______/|______/|______/|______/|______/|______/|______/|______/|______/|______/|______/|______/|______/*/
/**************************************************************************************************************************************************
 *
 *  @author @It-Is-Legend27
 *
 *  @date Jan. 2022
 *
 *  @brief A simple template class to create doubly linked lists, with some other added
 *         methods that pertain to other STL containers. STL std::list does
 *         not allow elements in the the list to be accessed with the
 *         [] operator, however this DLList class does, as well as some other
 *        methods. DLList::at(size_t n), DLList::resize(size_t sz, T val),
 *        DLList::fill(T val). There are also some other overloaded operators,
 *        such as << for cout and ofstream, and = for deep copying. The main
 *        driver below simply demonstrates the usage of the template class DLList,
 *        and prints some output to cout as well as a file called "DLList_test.txt".
 **************************************************************************************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include "DLList.hpp"

using namespace std;

int main()
{
    DLList<int> L0;            // []                : Construct empty list
    L0.resize(2);              // [0, 0]            : Resize to 2 elements with new elements having default values
    L0.resize(4, 69);          // [0, 0, 69, 69]    : Resize to 4 elements with new elements having value 69 : [ 0, 0, 69, 69]
    bool isEmpty = L0.empty(); // false             : Results in false (0), not empty
    L0.fill(69);               // [ 69, 69, 69, 69] : Changes all values to 69
    L0.clear();                // []                : Clears the list

    string S[2] = {"Hello", "world!"};
    DLList<string> L1(S, 2); // [Hello, world!] : Construct list using C-style array

    array<char, 10> A;
    A.fill('A');
    DLList<char> L2(A); // [A, A, A, A ...] : Construct list using std::array from STL
    L2.resize(4);       // [A, A, A, A]     : Resize to 4 elements

    vector<float> V;
    V.resize(69, 4.20);
    DLList<float> L3(V); // [ 4.20, 4.20 ...]  : Construct list using std::vector from STL

    DLList<float> L4(L3); // [ 4.20, 4.20 ...] : Construct list via copy constructor

    DLList<string> L5;
    L5.resize(2, "?");             // [?, ?]
    L5.push_front("What");         // [What, ?, ?]          : Push value to front of list
    L5.pop_back();                 // [What, ?]             : Remove last item from list
    L5.push_back("!");             // [What, ?, !]          : Push value to back of list
    L5.pop_front();                // [?, !]                : Remove first item from list
    L5.push_front(L1);             // [Hello, world!, ?, !] : Push other list to front of this list
    L5.at(1) = "!";                // [Hello, !, ?, !]      : Access element 1
    L5.clear();                    // []                    : Clear list
    L5.push_front("Well");         // [Well]                : Push to front
    L5.push_back(L1);              // [Well, Hello, world!] : Push other list to back of this list
    L5[0] = "Why";                 // [Why, Hello, world!]  : Access element 0
    L5.erase(1);                   // [Why, world!]         : Erase element 1
    size_t size = L5.size();       // 2                     : size of list
    L5.swap(L1);                   // [Hello, world!]       : Swap other list with this list, and vice-versa.
    size_t pos = L5.find("Hello"); // 0                     : position of value "Hello" in the list

    DLList<char> L6 = L2; // [A, A, A, A]    : Assign other list to this list (deep copy)
    L6.push_front('B');   // [B, A, A, A, A] : Push value to front of list
    L6.remove('A');       // [B]             : Removes all values matching 'A' from list
    L6.remove('B');       // []              : ``
    L6.push_front('P');   // [P]             : Pushin' 'P' (to the front of the list)

    L6.print();
    cout << '\n';       // Output: [P] : Prints list to output stream (cout by default)
    L6.print(cout);
    cout << '\n';       // Output: [P] : Prints list to specified output stream
    cout << L6 << '\n'; // Output: [P] : Inserts list to output stream to specified output stream

    ofstream outfile("DLList_test.txt");
    L6.print(outfile);
    outfile << '\n';       // Output: [P] : Prints list to specified output stream
    outfile << L6 << '\n'; // Output: [P] : Inserts list to output stream
    outfile.close();

    return 0;
}
