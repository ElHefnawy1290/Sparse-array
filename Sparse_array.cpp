#include <iostream>
#include <cassert>
using namespace std;

// Node structure for the sparse array structure
struct ArrayNode
{
    int data{};        // Stores the actual value
    int index{};       // Stores the index position in the array
    ArrayNode *next{}; // Pointer to the next node
    ArrayNode *prev{}; // Pointer to the previous node

    // Constructor to initialize node with data and index
    ArrayNode(int data, int index) : data(data), index(index) {}
};

// Class representing a sparse array using a doubly linked list
class ArrayLinkedList
{
private:
    ArrayNode *head{};  // Pointer to the head node
    ArrayNode *tail{};  // Pointer to the tail node
    int length{};       // Number of nodes in the linked list
    int array_length{}; // Length of the array

    // Helper function to link two nodes together
    void link(ArrayNode *first, ArrayNode *second)
    {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }

    // Inserts a node into the linked list while maintaining order
    void insert_sorted(ArrayNode *node)
    {
        // If the list is empty or the node should be at the front
        if (!head || head->index > node->index)
        {
            insert_front(node);
            return;
        }
        if (head->index == node->index)
        {
            // If a node with the same index exists, update its data
            head->data = node->data;
            return;
        }
        // Find the correct position for insertion
        ArrayNode *curr = head;
        for (; curr->next; curr = curr->next)
        {
            if (curr->next->index == node->index)
            {
                curr->next->data = node->data;
                return;
            }
            if (curr->next->index > node->index)
                break;
        }
        // Insert node at the correct position and ensure data integrity
        bool is_tail = false;
        if (!curr->next)
            is_tail = true;
        link(node, curr->next);
        link(curr, node);
        if (is_tail)
            tail = node;
        length++;
    }
    // Inserts a node at the front of the linked list and ensure data integrity
    void insert_front(ArrayNode *node)
    {
        link(node, head);
        if (!head)
            head = tail = node;
        else
            head = node;
        length++;
    }

public:
    // Constructor to initialize the sparse array size
    ArrayLinkedList(int array_length) : array_length(array_length) {}
    // Destructor to free allocated memory
    ~ArrayLinkedList()
    {
        ArrayNode *curr = head;
        while (curr)
        {
            ArrayNode *temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = tail = nullptr;
    }

    // Sets a value at a specific index
    void set_value(int data, int index)
    {
        ArrayNode *temp = new ArrayNode(data, index);
        insert_sorted(temp);
    }

    // Retrieves the value at a specific index
    // added const to prevent the function from modifying data and ensure data security and encapsulation
    int get_value(int index) const
    {
        assert(index < array_length); // Ensure the index is valid
        ArrayNode *curr = head;
        while (curr)
        {
            if (curr->index == index)
                return curr->data;
            curr = curr->next;
        }
        return 0;
    }

    // Prints the entire array, filling missing indices with 0
    void print_array() const
    {
        int count = 0;
        ArrayNode *curr = head;
        while (count != array_length)
        {
            if (curr && curr->index == count)
            {
                cout << curr->data << " ";
                curr = curr->next;
            }
            else
                cout << 0 << " ";
            count++;
        }
        cout << "\n";
    }

    // Prints only nonzero values in the array [elements in linked list only]
    void print_array_nonzero() const
    {
        ArrayNode *curr = head;
        while (curr)
        {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << "\n";
    }

    // Adds another sparse array to the current array
    void add(ArrayLinkedList &other)
    {
        ArrayNode *curr = other.head;
        while (curr)
        {
            ArrayNode *curr2 = head;
            bool existed = false;
            while (curr2)
            {
                if (curr2->index == curr->index)
                {
                    curr2->data += curr->data; // Add values if index already exists
                    existed = true;
                }
                curr2 = curr2->next;
            }
            if (!existed)
            {
                ArrayNode *temp = new ArrayNode(curr->data, curr->index);
                insert_sorted(temp); // Insert new values if index does not exist
            }
            curr = curr->next;
        }
    }
};