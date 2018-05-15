/*Prince Clumson-Eklu
*This the main.cpp file
*/

#include <iostream>
#include <iomanip>
#include <cstdlib> // for rand()
#include <ctime>
#include <thread>
#include <mutex>
#include <semaphore.h>
#include <unistd.h> //for sleep
#include <string>

#include "Buffer.hpp"

const double FACTOR = 0.000000001 ; // ONE-BILLIONTH

std::mutex global_lock;

sem_t empty[2];
sem_t full[2];
Buffer b[2];

int getRandomBufferIndex()
{
	return rand() % 2;
}

void outputThread(std::string message)
{
	global_lock.lock();
	std::cout << message << std::endl;
	global_lock.unlock();
}

void producer(int prodId)
{
	int item;
	double sleepTime; // how long the producer sleeps

	// std::cout << "Producer " << prodId << " is running" << std::endl;

	while (true)
	{
		sleepTime = rand() * FACTOR;

		sleep(sleepTime);    // sleep for sleepTime unit of time in second

		item = rand() % 100 ; // generate a random number as item

		int bufferIndex = getRandomBufferIndex();
		sem_wait ;

		b[bufferIndex].insertItem(item);// should be call on the buffer

		outputThread("Producer " + std::to_string(prodId) + "  inserted	" + std::to_string(item)+ "   into   buffer "+std::to_string(bufferIndex) );
		//std::cout << "Producer " << prodId <<" insert " << item << std::endl;
		sem_post;
	}
}

void consumer(int consId) // 1 <+ consId <= numConsumers
{
	int item;
	int sleepTime; // how long the producer sleeps

	while (true)
	{
		sleepTime = rand() * FACTOR;
		sleep(sleepTime);    // sleep for x unit of time
		//item = rand() % 100 ; // generate a random number as item

		int bufferIndex = getRandomBufferIndex();
		sem_wait ;

		b[bufferIndex].removeItem(item);

		outputThread("Consumer " + std::to_string(consId) + "  consumed 	" + std::to_string(item + 2)+ "   from   buffer "+std::to_string(bufferIndex));
	}
	sem_post;
}

int main( int argc , char * argv[])
{
	int item;

	//1-how long main() should sleep before terminating
	int sleepTime;

	//2-The number of producer threads
	int numProducers;

	//3-The number of consumer threads
	int numConsumers;

	if (argc != 4)
	{
		std::cout << "Please enter tree arguments after the program name"<< std::endl;
		std::cout << "Program's name "<< argv[0] << std::endl;
		std::cout << "Time to sleep before terminating " << std::endl;
		std::cout << "The number of producer Thread "    << std::endl;
		std::cout << "The number of consumer Thread "    << std::endl;
		exit(0);

	}
	else
	{
		std::cout << "prodCons is running" << std::endl;
		sleepTime 	 = abs(atoi(argv[1]));
		numProducers = abs(atoi(argv[2]));
		numConsumers = abs(atoi(argv[3]));
	}

	//TO DO : Create and initialize full and empty
	sem_t empty[0];
	sem_init(&empty[0], 0, SIZE);

	//Produmer
	std::thread producers[numProducers];
	for (int i = 0; i < numProducers; i++)
	{
		producers[i] = std::thread(producer, i);
	}

	//Consumer Thread
	std::thread consumers[numConsumers];
	for (int i = 0; i < numConsumers; i++)
	{
		consumers[i] = std::thread(consumer, i) ;
	}

	// sleep for sleepTime seconds
	sleep(sleepTime);

	return 0;
}
