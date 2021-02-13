/*
*This is the Thread.hpp file
*/

#ifndef BUFFER_H
#define BUFFER_H

const int SIZE = 5 ; // Buffer size

class Buffer {

public:

 // insert item into the buffer
 void insertItem(int item);

 // Removes an item from the buffer and place it in item
 void removeItem(int& item);


 private:

 int itemsArray[SIZE] = { -1, -1, -1, -1, -1 };// entries will be initialized to -1
 int in = 0;
 int out = 0;
 std::mutex buffAccess; // mutex to access the buffer

};

#endif// BUFFER_H
