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
 *  @brief A simple class to create doubly linked lists, with some other added
 *         methods that pertain to other STL containers. STL std::list does
 *         not allow elements in the the list to be accessed with the
 *         [] operator, however this DLList class does, as well as some other
 *        methods. DLList::at(size_t n), DLList::resize(size_t _size, T _data),
 *        DLList::fill(T _data). There are also some other overloaded operators,
 *        such as << for cout and ofstream, and = for deep copying.
 **************************************************************************************************************************************************/
#pragma once

#include <iostream>
#include <fstream>
#include <array>
#include <vector>

using namespace std;

/**
 * Node Class
 * @brief Simple templated Node class for use in templated doubly linked list (DLList).
 *
 * @tparam T any type
 */
template <typename T>
class Node
{
public:
    T data{T()};         // Data value
    Node *prev{nullptr}; // Points to previous node on list
    Node *next{nullptr}; // Points to next node on list

    /**
     * Node
     * @brief Construct a new Node object.
     *
     */
    Node() {}

    /**
     * Node
     * @brief Construct a new Node object with params.
     *
     * @param _data data to store in Node
     * @param _prev pointer to previous Node
     * @param _next pointer to next Node
     */
    Node(T _data, Node *_prev = nullptr, Node *_next = nullptr)
    {
        this->data = _data;
        this->prev = _prev;
        this->next = _next;
    }
};

/**
 * DLList Class
 * @brief Templated Doubly Linked List that makes use of subscript [] operator
 *        stream insertion << operator, and other array / vector-like methods.
 *
 * @tparam T any type
 */
template <typename T>
class DLList
{
private:
    Node<T> *front{nullptr}; // Head of the list
    Node<T> *back{nullptr};  // Tail of the list
    size_t list_size{0};     // Size of list

public:
    /**
     * DLList
     *
     * @brief Construct a new empty DLList object.
     *
     */
    DLList() {}

    /**
     * DLList
     * @brief Construct a new DLList object by copying another.
     *
     * @param other DLList of type T.
     */
    DLList(const DLList<T> &other)
    {
        Node<T> *temp = other.front;
        while (temp)
        {
            this->push_back(temp->data);
            temp = temp->next;
        }
    }

    /**
     * DLList
     * @brief Construct a new DLList object using a C-style array.
     *
     * @param A array of type T.
     * @param _size size of array.
     */
    DLList(const T A[], size_t _size)
    {
        for (int i = 0; i < _size; i++)
            this->push_back(A[i]);
    }

    /**
     * DLList
     * @brief Construct a new DLList object using a std::array.
     *
     * @tparam _size size of array.
     * @param A array of type T.
     */
    template <size_t _size>
    DLList(const array<T, _size> A)
    {
        for (const T x : A)
            this->push_back(x);
    }

    /**
     * DLList
     * @brief Construct a new DLList object using a std::vector.
     *
     * @param L vector of type T.
     */
    DLList(const vector<T> L)
    {
        for (const T x : L)
            this->push_back(x);
    }

    /**
     * ~DLList
     * @brief Destroy the DLList object
     *
     */
    ~DLList()
    {
        this->clear();
    }

    /**
     * public: void resize
     * @brief Resizes the list, and pushes default values if needed. Default
     *        values are whatever T() results in.
     *
     * @param _size new size of the list.
     */
    void resize(size_t _size)
    {
        if (this->list_size == _size || (int)_size < 0) // If same size, or invalid value, no resize needed
        {
            return;
        }
        else if (this->list_size > _size) // If new size is smaller, remove values
        {
            size_t removeAmount = this->list_size - _size;
            for (size_t i = 0; i < removeAmount; i++)
                this->pop_back();
        }
        else if (list_size < _size) // If new size is greater, add default values
        {
            size_t removeAmount = _size - this->list_size;
            for (size_t i = 0; i < removeAmount; i++)
                this->push_back(T());
        }
    }

    /**
     * public: void resize
     * @brief Resizes the list, and pushes '_data' to new nodes if needed.
     *
     * @param _size new size of the list.
     * @param _data value to push in new nodes, if any.
     */
    void resize(size_t _size, T _data)
    {
        if (this->list_size == _size || (int)_size < 0) // If same size, or invalid value, no resize needed
        {
            return;
        }
        else if (this->list_size > _size) // If new size is smaller, remove values
        {
            size_t removeAmount = this->list_size - _size;
            for (size_t i = 0; i < removeAmount; i++)
                this->pop_back();
        }
        else if (list_size < _size) // If new size is greater, add default values
        {
            size_t removeAmount = _size - this->list_size;
            for (size_t i = 0; i < removeAmount; i++)
                this->push_back(_data);
        }
    }

    /**
     * public: bool empty
     * @brief Tests if the list is empty.
     *
     * @return true if empty, false otherwise.
     */
    bool empty()
    {
        return this->list_size == 0;
    }

    /**
     * public: void fill
     * @brief Fills the list with '_data'.
     *
     * @param _data value to fill list with.
     */
    void fill(T _data)
    {
        if (!(this->empty())) // If not empty
        {
            Node<T> *travel = this->front; // travel points to front

            while (travel) // Travels until travel == nullptr
            {
                travel->data = _data;    // Replace value
                travel = travel->next; // Move to next node
            }
        }
    }

    /**
     * public: void clear
     * @brief Clears the list. Makes it empty.
     *
     */
    void clear()
    {
        while (!(this->empty()))
            this->pop_back();
    }

    /**
     * public: void push_front
     * @brief Pushes a value to the front of the list.
     *
     * @param _data value to push to front of list.
     */
    void push_front(T _data)
    {
        if (this->empty()) // If empty list
        {
            this->front = this->back = new Node<T>(_data); // 1 item, so front & back are same
        }
        else if (list_size == 1) // If one item
        {
            this->front = new Node<T>(_data, nullptr, this->front); // New front->next points to old front
            this->back->prev = this->front;                       // back->prev points to new front
        }
        else
        {
            this->front = new Node<T>(_data, nullptr, this->front); // New front->next points to old front
            this->front->next->prev = this->front;                // Old front->prev points to new front
        }
        this->list_size++;
    }

    /**
     * public: void push_front
     * @brief Pushes an entire DLList to the front of this list.
     *
     * @param other other list to push to front of this one.
     */
    void push_front(const DLList &other)
    {
        Node<T> *temp = other.back;

        while (temp)
        {
            this->push_front(temp->data); // Pushes list to the front right to left
            temp = temp->prev;
        }
    }

    /**
     * public: void push_back
     * @brief Pushes a value to the back of the list.
     *
     * @param _data value to push to back of the list.
     */
    void push_back(T _data)
    {
        if (this->empty())
        {
            this->front = this->back = new Node<T>(_data); // 1 item, so front & back are same
        }
        else if (this->list_size == 1)
        {
            this->back = new Node<T>(_data, this->back); // New back->prev points to old back
            this->front->next = this->back;            // front->next points to new back
        }
        else
        {
            this->back = new Node<T>(_data, this->back); // New back->prev points to old back
            this->back->prev->next = this->back;       // Old back->next points to new back
        }
        this->list_size++;
    }

    /**
     * public: void push_back
     * @brief Pushes an entire DLList to the front of this list.
     *
     * @param other other list to push to front of this one.
     */
    void push_back(const DLList &other)
    {
        Node<T> *temp = other.front;

        while (temp)
        {
            this->push_back(temp->data); // Pushes list to the back left to right
            temp = temp->next;
        }
    }

    /**
     * public: T& at
     * @brief Returns read/write reference to element 'n' in the list. Same as DLList::operator[].
     *
     * @param n position of element.
     * @return T& reference to element n.
     */
    T &at(size_t n)
    {
        if ((int)n < 0 || n >= this->list_size)
        {
            exit(1);
        }
        else
        {
            Node<T> *temp = this->front;
            for (size_t i = 0; i < n; i++)
            {
                temp = temp->next;
            }
            return temp->data;
        }
    }

    /**
     * public: void pop_front
     * @brief Removes element from front of the list. Does not return
     * the _dataue, however, so it must be retrieved before calling this
     * function, if desired.
     *
     */
    void pop_front()
    {
        if (this->empty())
        {
            return; // Cannot pop from empty list
        }
        else if (this->list_size == 1)
        {
            delete this->front;
            this->front = this->back = nullptr;
            this->list_size--;
        }
        else
        {
            Node<T> *deleteMe = this->front; // Save pointer for deletion
            this->front = this->front->next; // Move front down
            this->front->prev = nullptr;
            delete deleteMe;
            this->list_size--;
        }
    }

    /**
     * public: void pop_back
     * @brief Removes element from back of the list. Does not return
     * the _dataue, however, so it must be retrieved before calling this
     * function, if desired.
     *
     */
    void pop_back()
    {
        if (this->empty()) // Cannot pop from empty list
        {
            return;
        }
        else if (this->list_size == 1) // When only one item in list
        {
            delete this->back;
            this->front = this->back = nullptr;
            this->list_size--;
        }
        else
        {
            Node<T> *deleteMe = this->back; // Save pointer for deletion
            this->back = this->back->prev;  // Move back up
            this->back->next = nullptr;     // Double linked list ends in nullptr
            delete deleteMe;
            this->list_size--;
        }
    }

    /**
     * public: void erase
     * @brief Removes element at position 'n' from the list.
     *
     * @param n position of the element to remove.
     */
    void erase(size_t n)
    {
        if (this->empty()) // Cannot erase from empty list
        {
            return;
        }
        else if ((int)n < 0 || n >= this->list_size) // Cannot access out of bounds
        {
            return;
        }
        else if (n == 0) // n is frontmost item
        {
            this->pop_front();
        }
        else if (n == this->list_size - 1) // n is rearmost item
        {
            this->pop_back();
        }
        else // Travels through until it reaches index
        {
            Node<T> *temp = this->front;
            for (size_t i = 0; i < n; i++)
            {
                temp = temp->next;
            }
            temp->prev->next = temp->next; // Links temp->prev Node to temp->next Node
            temp->next->prev = temp->prev; // and vice-versa
            delete temp;
            this->list_size--;
        }
    }

    /**
     * public: void remove
     * @brief Removes all values that match '_value' from the list.
     *
     * @param _value value to be removed from the list.
     */
    void remove(T _value)
    {
        size_t i = this->find(_value); // Get index of first occurence of _value

        while (i != (size_t)-1) // While index i is valid
        {
            this->erase(i);
            i = this->find(_value);
        }
    }

    /**
     * @brief Finds first occurence of '_value' in the list and returns its position.
     *
     * @param _value value to be searched for.
     * @return size_t - position where '_value' is located.
     */
    size_t find(T _value)
    {
        Node<T> *temp = this->front;
        size_t i = 0;

        while (temp)
        {
            if (_value == temp->data) // If found, return index
            {
                return i;
            }
            else // Move to next node
            {
                temp = temp->next;
                i++;
            }
        }
        return (size_t)-1; // Returns -1 if not found
    }

    /**
     * public: void print
     * @brief Prints the entire list to an output stream. Prints to cout by
     *        default. Can print to ofstream as well.
     *
     */
    void print(ostream &os = cout)
    {
        if (!(this->empty())) // If not empty
        {
            Node<T> *travel = this->front; // travel points to front

            os << "[";

            while (travel) // Travels until travel == nullptr
            {
                os << travel->data; // Print data from node
                if (travel->next)
                {
                    os << ", ";
                }
                travel = travel->next; // Move to next node
            }
            os << ']';
        }
    }

    /**
     * public: size_t size
     * @brief Returns the size of the list.
     *
     * @return size_t size of the list.
     */
    size_t size()
    {
        return this->list_size;
    }

    /**
     * @brief Returns the maximum size possible (however it takes a lot of memory).
     * 
     * @return size_t 
     */
    size_t max_size()
    {
        return INT32_MAX; // 
    }

    /**
     * public: void swap
     * @brief Swaps the contents of this list, with another. Utilizes
     *        std::swap function.
     *
     * @param other other list to swap with this list.
     */
    void swap(DLList<T> &other)
    {
        std::swap<DLList<T>>((*this), other);
    }

    /**
     * public: ostream& operator<<
     * @brief Overloaded stream insertion << operator for printing list to
     *        an output stream. Works with ofstream as well.
     *
     * @param os output stream to insert list to.
     * @param L DLList of type T.
     * @return ostream& output stream by reference.
     */
    friend ostream &operator<<(ostream &os, const DLList<T> &L)
    {
        Node<T> *temp = L.front;
        os << "[";
        while (temp)
        {
            os << temp->data;
            if (temp->next)
            {
                os << ", ";
            }
            temp = temp->next;
        }
        os << "]";
        return os;
    }

    /**
     * @brief Overloaded subscript [] operator. Used for accessing an element at
     *        position 'n' of the list. Returns read/write reference to that
     *        element. Same as DLList::at.
     *
     * @param n position of element.
     * @return T& reference to element n.
     */
    T &operator[](size_t n)
    {
        if ((int)n < 0 || n >= this->list_size)
        {
            exit(1);
        }
        else
        {
            Node<T> *temp = this->front;
            for (size_t i = 0; i < n; i++)
            {
                temp = temp->next;
            }
            return temp->data;
        }
    }

    /**
     * @brief Overloaded assignment = operator. Used for assigning another
     *        list to the current one in such a way to prevent shallowing
     *        copying.
     *
     * @param rhs list on the right-hand side of assignment statement.
     * @return DLList<T>& list to assign to left-hand list of assignment statement.
     */
    DLList<T> &operator=(const DLList<T> &rhs)
    {
        if (this != &rhs)
        {
            this->clear();
            this->push_back(rhs);
        }
        return *this;
    }
};
