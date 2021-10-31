/*

Francis Chua

Practice Building a Linked List 

10/30/2021

*/

// For this lab, please create a linked list.  Demonstrate your understanding of linked lists by implementing the following functions within your linked list:

// a Node class or struct ( you decide ) for your list nodes
// a printList( ) function:  prints the list
// an insertNode( ) function:  inserts a given node to the list
// a deleteNode( ) function:  deletes referenced node from the list

#include <iostream>

class Node
{
private:
    int data;
    Node *previous;
    Node *next;

public:
    Node(int data, Node* previous, Node* next): data(data), previous(previous), next(next) {}
    int getData()
    {
        return data;
    }
    Node *getNext()
    {
        return next;
    }
    Node *getPrevious()
    {
        return previous;
    }
    void setNext(Node *n)
    {
        next = n;
    }
    void setPrevious(Node *n)
    {
        previous = n;
    }
    void setData(int d)
    {
        data = d;
    }

    void printList()
    {
        Node *temp = this;
        while (temp != NULL)
        {
            std::cout << temp->data << "(" << temp << ") ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
    void insertNode(int d)
    {
        // insert node at end
        Node *temp = this;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new Node(d, temp, NULL);
    }
};

void deleteNodePointer(Node *n)
{
    // delete node at this pointer.
    // changes pointes of previous and next
    if (n->getPrevious() != NULL)
    {
        n->getPrevious()->setNext(n->getNext());
    }
    if (n->getNext() != NULL)
    {
        n->getNext()->setPrevious(n->getPrevious());
    }
    free(n);
}

int main(int argc, char const *argv[])
{
    Node list(0, NULL, NULL);
    int input = 0;
    std::cout << "Enter numbers to insert into the list. End with -1: " << std::endl;
    std::cin >> input;
    list.setData(input);
    while (input != -1)
    {
        std::cin >> input;
        list.insertNode(input);
    }
    std::cout << "List: " << std::endl;
    list.printList();
    std::cout << "Enter a pointer to delete from the list: " << std::endl;
    void* pointer;
    std::cin >> pointer;
    deleteNodePointer((Node*) pointer);
    std::cout << "List: " << std::endl;
    list.printList();
    return 0;
}
