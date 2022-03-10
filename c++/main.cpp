#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include "pthread.h"
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
using namespace std;





// semaphore implementation used from https://riptutorial.com/cplusplus/example/30142/semaphore-cplusplus-11 
class Semaphore {
public:
	int count;

    Semaphore () 
    {
		count = 0;
    }
    
    inline void signal() {
        std::unique_lock<std::mutex> lock(mtx);
        count++;
        //notify the waiting thread
        cv.notify_one();
    }
    inline void wait() {
        std::unique_lock<std::mutex> lock(mtx);
        while(count == 0) {
            //wait on the mutex until notify is called
            cv.wait(lock);
        }
        count--;
    }
	
private:
    std::mutex mtx;
    std::condition_variable cv;
    
};



// Request class to store id and length of specific request
class Request{
	private:
		int id;
		int reqTime;
	public:
		Request(){}
		int getId() {return id;}
		int getReqTime() {return reqTime;}
		void setId(int rid){ id = rid; }
		void setReqTime(int rtime){reqTime = rtime;}
};


class BoundedBuffer{
	
	public:
		BoundedBuffer(int num)
		{
			N = num;
			numOfRequest = 0;
			requests.resize(N);
			semMutex.count = 1;
			empty.count = N;
			full.count = 0;
		}

		void addRequest(int rid, int rtime){
			empty.wait();
			semMutex.wait();
			// add request to request array
			requests[numOfRequest].setId(rid);
			requests[numOfRequest].setReqTime(rtime);
			//increment number of requeset
			numOfRequest++;
			semMutex.signal();
			full.signal();
		}

		void *removeRequest(){
			// consumer threads will stay in here til program is stopped
			while(true){
				full.wait();
				semMutex.wait();
				// decrement the number of request
				--numOfRequest;
				// remove Request from array
				Request r = requests[numOfRequest];
				// set request values to 0
				requests[numOfRequest].setId(0);
				requests[numOfRequest].setReqTime(0);
				// print consumer message 1
				printf("Consumer %ld: assigned request ID %d, processing request for the next %d seconds\n",
					time(NULL), r.getId(), r.getReqTime());
				// handle request
				handleRequest(r);
			
				semMutex.signal();
				empty.signal();
			}

		}
		
	private:
		Semaphore semMutex;
		Semaphore empty;
		Semaphore full;
		std:: vector<Request> requests; 
		int N;
		int numOfRequest;
		
		
		// sleep for specified time then then print second message
		void handleRequest(Request r){

			// sleep for request time 
			std::this_thread::sleep_for(std::chrono::milliseconds(r.getReqTime()*1000));
			//use stream to get threadid so printf can be used
			// print consumer id
			std::cout << "Consumer " << std::this_thread::get_id();
			// print consumer message 2
			printf(": completed request ID %d at time %ld\n",
				r.getId(), time(NULL));
		}	
};





// Global variables 
int N = 3;
// create Boundedbuffer as a global variable so the consumer threads can call remove request
BoundedBuffer boundedBuffer(N);
// make the request buffer global




static void *consumer(void *arg){
	boundedBuffer.removeRequest();
}

int main (){ 
	// number of threads and size of buffer
	int N = 10;
	// upper bound on process length
	int M = 1; 

	// initialize producer sleep timer
	int producerSleepTimer = 0;
	// initialize request infromation
	int requestId = 1;
	int requestLength = 0;
	// Request* r = NULL;

	//create consumer threads
	pthread_t threads[N];
	int out;

	for(int i = 0; i < N; i++){
		// create threads and send them to the removeRequestfunction
		pthread_create(&threads[i], NULL, consumer, (void*)i);
	}

	
	
	while(true) {
			
			// calculate request length
			requestLength = (int)(((double) rand() / (RAND_MAX)) * M + 1);
				
			//Producer: produced request ID n, length t seconds at time CURRENT-TIME
			printf("Producer: produced request ID %d, length %d seconds at time %ld\n", requestId, requestId, time(NULL));
			//create new request and add request to bounded buffer
			boundedBuffer.addRequest(requestId++, requestLength);
				
			// randomly generate the amount of time for the producer to sleep between 0-4 seconds
			producerSleepTimer = ((int)(((double) rand() / (RAND_MAX))*4));
				
			//Producer: sleeping for X seconds
			printf("Producer: sleeping for %d seconds\n", producerSleepTimer);
				
			// make masterThread sleep for random amount of time
			std::this_thread::sleep_for(std::chrono::milliseconds(producerSleepTimer*1000));
						
		
	}
}
