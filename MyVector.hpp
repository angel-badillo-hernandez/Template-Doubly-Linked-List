/* I used this as a start for DLList.hpp, and from there I just looked at
   methods other STL containers use and coded my own for this data type.    */



/*****************************************************************************
*                    
*  Author:           Angel Badillo
*  Email:            badilloa022402@gmail.com
*  Label:            P02
*  Title:            MyVector Class 2
*  Course:           CMPS 2143
*  Semester:         Fall 2021
* 
*  Description:
*        This program implements a class called MyVector that is essentially
*        a double linked list with overloaded constuctors that can append
*        or prepend a double linked list to another double linked list.
*        It can also add items to a specific location, search for an item
*        and return the index, and remove an item at a specific location.
*        In this second program, the [] bracket operator, equal-to operator,
*        the not equal-to operator, the compound assignment operators and 
*        arithmetic are implemented, so you can treat the vector as an array,
*        check for equality, use compound assignment, and add, subtract,
*        multiply, and divide.
*        
*  Usage:
*       - g++ main.cpp -o main && ./main
*       - You just compile and run it.
* 
*  Files:     
*       main.cpp        : driver program
*       MyVector.hpp    : header file with definition and implementation
*       output.txt      : output from program
*****************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

const int INTMAX = numeric_limits<int>::max(); // Max value of int, used for errors

/**
 * Node
 * 
 * Description:
 *      Creates a Node that can stored data, and has pointers meant for
 *      the previous Node and next Node. Meant to be used in double linked list
 * 
 * Public Methods:
 *                Node(int _data, Node *_prev = nullptr, Node *_next = nullptr)
 * 
 * Private Methods:
 *      - None
 * 
 * Usage: 
 * 
 *      Node(val, nullptr, head);   // Creates an instance of Node
 *                                  // stores val in Node.data
 *                                  // sets Node.prev to nullptr
 *                                  // sets Node.next to Node* head
 *       
 */
class Node
{
public:
    int data;   // Data value
    int index;  // Index of item
    Node *prev; // Points to previous node on list
    Node *next; // Points to next node on list

    /**
     * Public: Node
     * 
     * Description:
     *      Constructs an instance of Node
     * 
     * Params:
     *      int     : data of Node
     *      Node*   : pointer to previous Node
     *      Node*   : pointer to next Node
     * 
     */
    Node(int _data, Node *_prev = nullptr, Node *_next = nullptr)
    {
        data = _data;
        prev = _prev;
        next = _next;
    }
};

/**
 * MyVector
 * 
 * Description:
 *      Creates a vector. The vector is based off of a double linked list.
 *      It's size changes dynamically and vectors can be appended/prepended
 *      to other vectors.
 * 
 * Public Methods:
 *                 MyVector()
 *                 MyVector(MyVector& V2)
 *                 MyVector(int* A, int size)
 *                 MyVector(string fileName)
 *                 ~MyVector()
 *        void     pushFront(int val)
 *        void     pushFront(MyVector& V2)
 *        void     pushRear(int val)
 *        void     pushRear(MyVector& V2)
 *        void     pushAt(int loc, int val)
 *        int      popFront()
 *        int      popRear()
 *        int      popAt(int loc)
 *        int      find(int val)
 *        void     print()
 *        void     print(ofstream& infile)
 *        int      getSize()
 * friend ostream  &operator<<(ostream &os, const MyVector &V)
 * friend oftream  &operator<<(oftream &of, const MyVector &V)
 *        int      &operator[](int index)
 *        MyVector &operator=(const MyVector &rhs)
 *        bool     operator==(const MyVector &rhs)
 *        bool     operator!=(const MyVector &rhs)
 *        MyVector &operator+=(const MyVector &rhs)
 *        MyVector &operator-=(const MyVector &rhs)
 *        MyVector &operator*=(const MyVector &rhs)
 *        MyVector &operator/=(const MyVector &rhs)
 *  const MyVector operator+(const MyVector &rhs) const
 *  const MyVector operator-(const MyVector &rhs) const
 *  const MyVector operator*(const MyVector &rhs) const
 *  const MyVector operator/(const MyVector &rhs) const
 * 
 * Private Methods:
 *      - None
 * 
 * Usage: 
 * 
 *      MyVector v1;                // Create instance of MyVector
 *      v1.pushFront(2);            // prepends 2 to vector
 *      v1.pushRear(val);           // appends val to vector
 *      int x = v1.popFront();      // pops front
 *      int y = v1.popRear();       // pops rear
 *      int p = v1.popAt(1);        // pops at index
 *      int z = v1.find();          // finds index of an item
 *      v1.print();                 // prints to screen
 *      v1.print(outfile);          // prints to output file 
 *      cout << v1 << '\n';         // prints to os ostream
 *      fout << v2 << '\n';         // prints to of ofstream
 *      int size = v1.getSize();    // returns size of vector
 *      v1[1] = 10;                 // [] bracket op 
 *      v1 = v2;                    // assignment op
 *      cout << (v1==v2);           // equal-to op  
 *      v1 += v2;                   // Compound assignment
 *      v1 = v1 - v2;               // Subtraction op
 */
class MyVector
{
private:
    Node *head; // Head of the vector
    Node *tail; // Tail of the vector
    int size;   // Size of vector

public:
    /**
     * Public: MyVector
     * 
     * Description:
     *      Creates an empty instance of MyVector
     * 
     * Params:
     *      - None
     */
    MyVector() //Default constructor
    {
        head = tail = nullptr;
        size = 0;
    }

    /**
     * Public: MyVector
     * 
     * Description:
     *      Creates an vector by coping another vector
     * 
     * Params:
     *      MyVector& : vector to be copied
     */
    MyVector(const MyVector &V2)
    {
        head = tail = nullptr;
        size = 0;

        Node *temp = V2.head;

        while (temp)
        {
            pushRear(temp->data);
            temp = temp->next;
        }
    }

    /**
     * Public: MyVector
     * 
     * Description:
     *      Creates an instance of MyVector by copying an array
     * 
     * Params:
     *      int*    : array of integers
     *      int     : size of array
     */
    MyVector(int *A, int _size) //Array constructor
    {
        head = tail = nullptr;
        size = 0;

        for (int i = 0; i < _size; i++)
        {
            pushRear(A[i]);
        }
    }

    /**
     * Public: MyVector
     * 
     * Description:
     *      Creates an instance of MyVector by reading in values from an input file
     * 
     * Params:
     *      string  : file name of input file
     */
    MyVector(string fileName) //Input file constructor
    {
        ifstream infile;
        infile.open(fileName);

        head = tail = nullptr;
        size = 0;

        int val;
        while (!infile.eof())
        {
            infile >> val;
            pushRear(val);
            size++;
        }
        infile.close();
    }

    /**
     * Public: ~MyVector
     * 
     * Description:
     *      Deletes the vector
     * 
     * Params:
     *      - None
     */
    ~MyVector()
    {
        while (head)
        {
            popFront();
        }
    }

    /**
     * Public: pushFront
     * 
     * Description:
     *      Prepends an item to the vector
     * 
     * Params:
     *      int : item to be prepended
     * 
     * Returns:
     *      void
     */
    void pushFront(int val)
    {
        if (!head) // If empty vector
        {
            head = tail = new Node(val); // 1 item, so head & tail are same
        }
        else if (head == tail) // If one item
        {
            head = new Node(val, nullptr, head); // New head->next points to old head
            tail->prev = head;                   // tail->prev points to new head
        }
        else
        {
            head = new Node(val, nullptr, head); // New head->next points to old head
            head->next->prev = head;             // Old head->prev points to new head
        }
        size++;
    }

    /**
     * Public: pushFront
     * 
     * Description:
     *      Prepends an entire other vector to a vector
     * 
     * Params:
     *      MyVector&   : vector object by reference
     * 
     * Returns:
     *      void
     */
    void pushFront(MyVector &V2)
    {
        Node *temp = V2.tail;

        while (temp)
        {
            pushFront(temp->data); // Pushes vector to the front right to left
            temp = temp->prev;
        }
    }

    /**
     * Public: pushRear
     * 
     * Description:
     *      Appends an item to the vector
     * 
     * Params:
     *      int : item to be appended
     * 
     * Returns:
     *      void
     */
    void pushRear(int val) // Pushes
    {
        if (!head)
        {
            head = tail = new Node(val); // 1 item, so head & tail are same
        }
        else if (head == tail)
        {
            tail = new Node(val, tail); // New tail->prev points to old tail
            head->next = tail;          // head->next points to new tail
        }
        else
        {
            tail = new Node(val, tail); // New tail->prev points to old tail
            tail->prev->next = tail;    // Old tail->next points to new tail
        }
        size++;
    }

    /**
     * Public: pushRear
     * 
     * Description:
     *      Appends an entire other vector to a vector
     * 
     * Params:
     *      MyVector&   : vector object by reference
     * 
     * Returns:
     *      void
     */
    void pushRear(MyVector &V2)
    {
        Node *temp = V2.head;

        while (temp)
        {
            pushRear(temp->data); // Pushes vector to the back left to right
            temp = temp->next;
        }
    }

    /**
     * Public: pushAt
     * 
     * Description:
     *      Pushes an item to a specific location in the vector
     * 
     * Params:
     *      int : location in vector
     *      int : item to be pushed
     * 
     * Returns:
     *      void
     */
    void pushAt(int loc, int val)
    {
        if (loc >= 0 && loc < size)
        {
            Node *temp = head;

            for (int i = 0; i > loc; i++)
            {
                temp = temp->next;
            }

            temp->data = val;
        }
    }

    /**
     * Public: popFront
     * 
     * Description:
     *      Pops front item in vector
     * 
     * Params:
     *      - None
     * 
     * Returns:
     *      int : item that was popped from vector
     */
    int popFront()
    {
        if (!head)
        {
            return INTMAX; // Cannot pop from empty vector
        }
        else if (head == tail)
        {
            int returnMe = head->data;
            delete head;
            head = tail = nullptr;
            size--;
            return returnMe;
        }
        else
        {
            int returnMe = head->data; // Save data for return
            Node *deleteMe = head;     // Save pointer for deletion
            head = head->next;         // Move head down
            head->prev = nullptr;

            delete deleteMe;
            size--;
            return returnMe;
        }
    }

    /**
     * Public: popRear
     * 
     * Description:
     *      Pops rear item from the vector
     * 
     * Params:
     *      - None
     * 
     * Returns:
     *      int : item that was popped from vector
     */
    int popRear()
    {
        if (!tail) // Cannot pop from empty vector
        {
            return INTMAX;
        }
        else if (head == tail) // When only one item in vector
        {
            int returnMe = tail->data;
            delete tail;
            head = tail = nullptr;
            size--;
            return returnMe;
        }
        else
        {
            int returnMe = tail->data; // Save data for return
            Node *deleteMe = tail;     // Save pointer for deletion
            tail = tail->prev;         // Move tail up
            tail->next = nullptr;      // Double linked list ends in nullptr

            delete deleteMe;
            size--;
            return returnMe;
        }
    }

    /**
     * Public: popAt
     * 
     * Description:
     *      Pops an item from the vector at a given index
     * 
     * Params:
     *      int : location (index) of item to be popped
     * 
     * Returns:
     *      int : item that was removed from vector
     */
    int popAt(int loc)
    {
        if (!head) // Cannot pop from empty vector
        {
            return INTMAX;
        }
        else if (loc < 0 || loc > size - 1) // Cannot access out of bounds
        {
            return INTMAX;
        }
        else if (loc == 0) // loc is frontmost item
        {
            return popFront();
        }
        else if (loc == size - 1) // loc is rearmost item
        {
            return popRear();
        }
        else // Travels through until it reaches index
        {
            Node *temp = head;
            for (int i = 0; i < loc; i++)
            {
                temp = temp->next;
            }
            int returnMe = temp->data;
            temp->prev->next = temp->next; // Links temp->prev Node to temp->next Node
            temp->next->prev = temp->prev; // and vice-versa
            delete temp;

            return returnMe;
        }
    }

    /**
     * Public: find
     * 
     * Description:
     *      Travels through the vector and searches for the index of an item
     * 
     * Params:
     *      int : item to be searched for
     * 
     * Returns:
     *      int :   index of item that was searched for
     */
    int find(int val)
    {
        Node *temp = head;
        int i = 0;

        while (temp)
        {
            if (val == temp->data) // If found, return index
            {
                return i;
            }
            else // Move to next node
            {
                temp = temp->next;
                i++;
            }
        }
        return -1; // Returns -1 if not found
    }

    /**
     * Public: print
     * 
     * Description:
     *      Prints the entire vector to stdout
     * 
     * Params:
     *      - None
     * 
     * Returns:
     *      void
     */
    void print()
    {
        if (head) // If head exists
        {
            Node *travel = head; // travel points to head

            cout << "[";

            while (travel) // Travels until travel == nullptr
            {
                cout << travel->data; // Print data from node
                if (travel->next)
                {
                    cout << ", ";
                }
                travel = travel->next; // Move to next node
            }
            cout << ']' << endl;
        }
    }

    /**
     * Public: print
     * 
     * Description:
     *      Prints entire vector to output file
     * 
     * Params:
     *      ofstream&   : output file stream by reference
     * 
     * Returns:
     *      void        : returns void but prints to file
     */
    void print(ofstream &outfile)
    {
        if (head) // If head exists
        {
            Node *travel = head; // travel points to head

            outfile << "[";

            while (travel) // Travels until travel == nullptr
            {
                outfile << travel->data; // Print data from node
                if (travel->next)
                {
                    outfile << ", ";
                }
                travel = travel->next; // Move to next node
            }
            outfile << ']' << endl;
        }
    }

    /**
     * Public: getSize()
     * 
     * Description:
     *      Returns the size of the vector
     * 
     * Params:
     *      - None
     * 
     * Returns:
     *      int        : returns size of vector
     */
    int getSize()
    {
        return size;
    }

    /**
     * Public: operator<<
     * 
     * Description:
     *      Prints entire vector to stdout
     * 
     * Params:
     *      ostream&   : ostream by reference
     * 
     * Returns:
     *      ostream&   : returns ostream by reference
     */
    friend ostream &operator<<(ostream &os, const MyVector &V)
    {
        os << fixed << setprecision(2);

        Node *temp = V.head;
        os << "[ ";
        while (temp)
        {
            os << temp->data;
            if (temp->next)
            {
                os << ", ";
            }
            temp = temp->next;
        }
        os << " ]";
        return os;
    }

    /**
     * Public: operator<<
     * 
     * Description:
     *      Prints entire vector to output file stream
     * 
     * Params:
     *      oftream&   : oftream by reference
     * 
     * Returns:
     *      oftream&   : returns oftream by reference
     */
    friend ofstream &operator<<(ofstream &of, const MyVector &V)
    {
        of << fixed << setprecision(2);

        Node *temp = V.head;
        of << "[ ";
        while (temp)
        {
            of << temp->data;
            if (temp->next)
            {
                of << ", ";
            }
            temp = temp->next;
        }
        of << " ]";
        return of;
    }

    /**
     * Public: operator[]
     * 
     * Description:
     *      Prints entire vector to atdout
     * 
     * Params:
     *      int        : index by value
     * 
     * Returns:
     *      int&       : returns data of Node by reference
     */
    int &operator[](int index)
    {
        if (index < 0 || index >= size)
        {
            exit(0);
        }
        else
        {
            Node *temp = head;
            for (int i = 0; i < index; i++)
            {
                temp = temp->next;
            }
            return temp->data;
        }
    }

    /**
     * Public: operator=
     * 
     * Description:
     *      Assigns a vector to a vector
     * 
     * Params:
     *      const MyVector&   : const Vector by reference
     * 
     * Returns:
     *      MyVector&         : returns Vector by reference
     */
    MyVector &operator=(const MyVector &rhs)
    {
        if (this != &rhs)
        {
            this->~MyVector();
            MyVector other(rhs);
            this->pushRear(other);
        }
        return *this;
    }

    /**
     * Public: operator==
     * 
     * Description:
     *      Tests for equality of two vectors
     * 
     * Params:
     *      const MyVector&   : const Vector by reference
     * 
     * Returns:
     *      bool              : returns bool (true/false) by value
     */
    bool operator==(const MyVector &rhs)
    {
        bool isEqual;

        MyVector other = rhs;
        if (this->size != other.size)
        {
            isEqual = false;
        }
        else
        {
            for (int i = 0; i < this->size; i++)
            {
                isEqual = (*this)[i] == other[i];
            }
        }
        return isEqual;
    }

    /**
     * Public: operator!=
     * 
     * Description:
     *      Tests for inequality of two vectors
     * 
     * Params:
     *      const MyVector&   : const Vector by reference
     * 
     * Returns:
     *      bool              : returns bool by value
     */
    bool operator!=(const MyVector &rhs)
    {
        return !(*this == rhs);
    }

    /**
     * Public: operator+=
     * 
     * Description:
     *      Compound assignment operator: addition
     * 
     * Params:
     *      const MyVector&   : const Vector by reference
     * 
     * Returns:
     *      MyVector&         : returns Vector by reference
     */
    MyVector &operator+=(const MyVector &rhs)
    {
        MyVector other = rhs;
        int i = 0;

        if (this->size >= other.size) // If this list is bigger than other
        {
            for (i = 0; i < other.size; i++) // Loop through and add all values
            {
                (*this)[i] += other[i];
            }
        }
        else // If this list smaller than other
        {
            for (i = 0; i < this->size; i++) // Loop through smallest list
            {
                (*this)[i] += other[i]; // and add all values
            }

            while (i < other.size) // Append leftover to this list
            {
                this->pushRear(other[i]);
                i++;
            }
        }
        return *this;
    }

    /**
     * Public: operator-=
     * 
     * Description:
     *      Compound assignment operator: subtraction
     * 
     * Params:
     *      const MyVector&   : const Vector by reference
     * 
     * Returns:
     *      MyVector&         : returns Vector by reference
     */
    MyVector &operator-=(const MyVector &rhs)
    {
        MyVector other = rhs;
        int i = 0;

        if (this->size >= other.size)
        {
            for (i = 0; i < other.size; i++)
            {
                (*this)[i] -= other[i];
            }
        }
        else
        {
            for (i = 0; i < this->size; i++)
            {
                (*this)[i] -= other[i];
            }

            while (i < other.size)
            {
                this->pushRear(other[i]);
                i++;
            }
        }
        return *this;
    }

    /**
     * Public: operator*=
     * 
     * Description:
     *      Compound assignment operator: multiplication
     * 
     * Params:
     *      const MyVector&   : const Vector by reference
     * 
     * Returns:
     *      MyVector&         : returns Vector by reference
     */
    MyVector &operator*=(const MyVector &rhs)
    {
        MyVector other = rhs;
        int i = 0;

        if (this->size >= other.size)
        {
            for (i = 0; i < other.size; i++)
            {
                (*this)[i] *= other[i];
            }
        }
        else
        {
            for (i = 0; i < this->size; i++)
            {
                (*this)[i] *= other[i];
            }

            while (i < other.size)
            {
                this->pushRear(other[i]);
                i++;
            }
        }
        return *this;
    }

    /**
     * Public: operator/=
     * 
     * Description:
     *      Compound assignment operator: division
     * 
     * Params:
     *      const MyVector&   : const Vector by reference
     * 
     * Returns:
     *      MyVector&         : returns Vector by reference
     */
    MyVector &operator/=(const MyVector &rhs)
    {
        MyVector other = rhs;
        int i = 0;

        if (this->size >= other.size)
        {
            for (i = 0; i < other.size; i++)
            {
                if (other[i] == 0) // Cannot divide by 0
                {
                    exit(0);
                }
                else
                {
                    (*this)[i] /= other[i];
                }
            }
        }
        else
        {

            for (i = 0; i < this->size; i++)
            {
                if (other[i] == 0) // Cannot divide by 0
                {
                    exit(0);
                }
                else
                {
                    (*this)[i] /= other[i];
                }
            }

            while (i < other.size)
            {
                this->pushRear(other[i]);
                i++;
            }
        }
        return *this;
    }

    /**
     * Public: operator+
     * 
     * Description:
     *      Addition operator
     * 
     * Params:
     *      const MyVector&   : const Vector by reference
     * 
     * Returns:
     *      const MyVector    : returns Vector by value
     */
    const MyVector operator+(const MyVector &rhs) const
    {
        return MyVector(*this) += rhs; // Creates copy of this, adds rhs to it
    }

    /**
     * Public: operator-
     * 
     * Description:
     *      Subtraction operator
     * 
     * Params:
     *      const MyVector&   : const Vector by reference
     * 
     * Returns:
     *      const MyVector    : returns Vector by value
     */
    const MyVector operator-(const MyVector &rhs) const
    {
        return MyVector(*this) -= rhs; // Creates copy of this, subs rhs from it
    }

    /**
     * Public: operator*
     * 
     * Description:
     *      Multiplication operator
     * 
     * Params:
     *      const MyVector&   : const Vector by reference
     * 
     * Returns:
     *      const MyVector    : returns Vector by value
     */
    const MyVector operator*(const MyVector &rhs) const
    {
        return MyVector(*this) *= rhs; // Creates copy of this, multiply by rhs
    }

    /**
     * Public: operator/
     * 
     * Description:
     *      Division operator
     * 
     * Params:
     *      const MyVector&   : const Vector by reference
     * 
     * Returns:
     *      const MyVector    : returns Vector by value
     */
    const MyVector operator/(const MyVector &rhs) const
    {
        return MyVector(*this) /= rhs; // Creates copy of this, divides by rhs
    }
};
