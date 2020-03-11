#include "IntList.h"

using namespace std;

IntList::IntList() 
{
    head = nullptr;
    tail = nullptr;
}

IntList::~IntList()
{
    while(head){
        IntNode* next = head->next;
        delete head;
        head = next;
    }
    head = nullptr;
    tail = nullptr;
}

IntList::IntList(const IntList &cpy)
{
    if(cpy.head == nullptr)
    {
        head = nullptr;
    }
    else
    {
        head = new IntNode(cpy.head->data);
        //you want to track the what your copying and what your not.
        //new head.
        IntNode* current = head;
        //find copys head.
        IntNode* cpyHead = cpy.head;
        //use to track through each node and copy them: start at head.
        IntNode* currCpy = cpyHead;
        while(currCpy->next != nullptr)
        {
            //Should be dealing with just current and currcpy pointers.
            current->next = new IntNode(currCpy->next->data);
            //now we move on to what we want to copy next.
            currCpy = currCpy->next;
            //now we move onto curr next as well to copy at that place.
            current = current->next;
        }
    }
}

void IntList::push_front(int value)
{
    IntNode* newNode = new IntNode(value);
   
    if(head == nullptr)
    {
        head = newNode;
        tail = newNode;
    } 
    else
    {
        newNode->next = head;
        head = newNode;
    }
}

void IntList::pop_front()
{
    if(head != nullptr)
    {
        IntNode* frontNode;
        if(head->next == nullptr)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            frontNode = head->next;
            delete head;
            head = frontNode;
        }
    }
}

bool IntList::empty() const
{
    return (head == nullptr && tail == nullptr);
}

const int& IntList::front() const 
{
    if(head != nullptr)
    {    
        return head->data;
    }
    else
    {
       throw out_of_range("IntList::at_range_check"); 
    }
}

const int& IntList::back() const 
{
    if(tail != nullptr)
    {
        return tail->data;
    }
    else
    {
        throw out_of_range("IntList::at_range_check"); 
    }
}

ostream& operator<<(ostream& out, const IntList& list)
{
    IntNode* curr = list.head;
    bool first = true;
    while(curr != nullptr)
    {
        if(first)
        {
        out << curr->data;
        first = false;
        curr = curr->next;
        }
        else
        {
        out << " ";
        out << curr->data;
        curr = curr->next;
        }
    }
    return out;
}

IntList& IntList::operator=(const IntList &rhs)
{
    if(this != &rhs)
    {
        this->clear();
        IntNode* temp = rhs.head;
        while(temp != nullptr)
        {
            this->push_back(temp->data);
            temp = temp->next;
        }
    }
    return *this;
}

 void IntList::push_back(int value)
 {
     IntNode* backNode = new IntNode(value);
     if(empty())
     {
        head = backNode;
        tail = backNode;
     }
     else
     {
         tail->next = backNode;
         tail = backNode;     
     }
 }

void IntList::clear()
{
    this->~IntList();
}

void IntList::selection_sort()
{
    if(head != nullptr)
    {
        IntNode* small;
        IntNode* currCompare;
        for(small = head; small->next != nullptr; small = small->next)
        {
            for(currCompare = small->next; currCompare != nullptr; currCompare = currCompare->next)
            {
                if(small->data > currCompare->data)
                {
                    int temp = small->data;
                    small->data = currCompare->data;
                    currCompare->data = temp;
                }
            }

        }
    }
}

void IntList::insert_ordered(int value)
{
    IntNode* val = new IntNode(value);
    if(head == nullptr || head->data >= val->data)
    {
        val->next = head;
        head = val;
    }
    else 
    {
        IntNode* curr = head;
        while(curr->next != nullptr && curr->next->data < val->data)
        {
            curr = curr->next;
        }
        val->next = curr->next;
        curr->next = val;
    }
}

void IntList::remove_duplicates()
{
   for(IntNode* a = head; a != nullptr; a = a->next)
   {
       for(IntNode* b = a->next; b != nullptr; b = b->next)
       {
           IntNode* curr = a;
           while(curr->next != b)
           {
               curr = curr->next;
           }
           if(a->data == b->data)
           {
               curr->next = b->next;
               if(b == tail)
               {
                   tail = curr;
               }
               IntNode* del = b;
               delete del;
           }
       }
   }
}