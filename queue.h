#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdexcept>

using namespace std;

const uint32_t
    QUEUE_SIZE = 16;

template <typename QueueType>
class Queue
{
public:
    Queue(uint32_t qSize = QUEUE_SIZE)
    {

        data = new QueueType[qSize];
        capacity = qSize;

        count = tail = 0;
        head = qSize - 1;
    }

    ~Queue() { delete[] data; }

    void clear()
    {
        count = tail = 0;
        head = capacity - 1;
    }

    uint32_t size() { return count; }
    bool isEmpty() { return !count; }

    void enqueue(QueueType &d)
    {

        if (count == capacity)
        {
            auto
                tmpData = new QueueType[2 * capacity];
            if (tmpData == nullptr)
                throw overflow_error("Queue is full");

            for (int i = 0; i < capacity; i++)
                tmpData[i] = data[(head + i + 1) % capacity];
            //
            delete[] data;
            tail = capacity;
            data = tmpData;
            head = 2 * capacity - 1;
            capacity *= 2;
        }
        data[tail] = d;
        tail = ++tail % capacity;
        count++;
    }

    QueueType dequeue()
    {

        if (count == 0)
            throw underflow_error("Queue is empty");

        head = ++head % capacity;

        count--;

        return data[head];
    }

private:
    QueueType
        *data;

    uint32_t
        head,
        tail,
        count,
        capacity;
};

#endif