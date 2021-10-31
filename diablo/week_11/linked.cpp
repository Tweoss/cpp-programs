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
    Node *next;

public:
    Node(int d)
    {
        data = d;
        next = NULL;
    }
    int getData()
    {
        return data;
    }
    Node *getNext()
    {
        return next;
    }
    void setNext(Node *n)
    {
        next = n;
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
            std::cout << temp->data << "(" << temp->next << ") ";
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
        temp->next = new Node(d);
    }
    void deleteNode(int d)
    {
        // delete node with this value
        Node *temp = this;
        while (temp->next != NULL)
        {
            if (temp->next->data == d)
            {
                temp->next = temp->next->next;
                return;
            }
            temp = temp->next;
        }
    }
};

int main(int argc, char const *argv[])
{
    Node list(0);
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
    return 0;
}
