/*
*This is the Thread.cpp file
*/

#include <iostream>
#include <thread>
#include <mutex>
#include "Buffer.hpp"

 // insert item into the buffer
 void Buffer::insertItem(int item)
 {
	buffAccess.lock();
	itemsArray[in] = item;
	in = (in + 1) % SIZE;
	buffAccess.unlock();
 }

 // Removes an item from the buffer and place it in item .
 void Buffer::removeItem(int& item)
 {
	buffAccess.lock();
	item = itemsArray[out];
	out = (out + 1) % SIZE;
	buffAccess.unlock();
 }




