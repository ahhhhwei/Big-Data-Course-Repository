#pragma once
#pragma once
#include<iostream>
#include<cassert>
using namespace std;
struct Node
{
    Node* _next;
    int _data;
    Node(const int x)
        :_next(nullptr)
        , _data(x)
    {

    }

};
class Queue
{
public:
    Queue()
    {
        _tail = nullptr;
    }
    void enqueue(const int val)
    {
        Node* temp = new Node(val);
        if (_tail != nullptr)
        {
            Node* head = _tail->_next;
            Node* prevtail = _tail;
            _tail = temp;
            prevtail->_next = _tail;
            _tail->_next = head;
        }
        else//一个节点
        {
            _tail = temp;
            _tail->_next = _tail;
        }
    }
    void dequeue()
    {
        if (_tail->_next == _tail)
        {
            delete _tail;
            _tail = nullptr;
        }
        else
        {
            _tail->_next = _tail->_next->_next;
        }
    }
    int Front()
    {
        if(_tail)
            return _tail->_next->_data;
        else
        {
            cerr << "队空，无法获取队头元素！" << endl;
            size_t n = -1;
            return n;
        }
    }
    Queue(const Queue& q)
    {
        Node* temp = q._tail->_next;
        while (temp!=q._tail)
        {
            this->enqueue(temp->_data);
            temp = temp->_next;
        }
        this->enqueue(temp->_data);
    }
    Queue& operator=(Queue q)
    {
        if (this != &q)
        {
            std::swap(q._tail, _tail);
        }
        return *this;
    }
    ~Queue()
    {
        while (!empty())
        {
            dequeue();
        }
    }
    bool empty()
    {
        return _tail == nullptr;
    }
    void display(ostream& out)
    {
        Node* cur = _tail->_next;
        while (cur!=_tail)
        {
            out << cur->_data << ' ';
            cur = cur->_next;
        }
        out << _tail->_data << endl;
    }
private:
    Node* _tail;
};