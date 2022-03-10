# Request-Scheduling-using-Threads-and-Synchronization

Riley Clark

Reid Folk

Aalia Omarali


#### Contrubutions 

Riley: 
all java code.
all java design.
java makefile 
how to run java section in readme 
99% c++ code
how to run c++ code 

##### java:design

The java design consist of three classes Request, BoundedBuffer, and Main. 

The request class is simple infromation about a request. Every request has an id and time.

The BoundedBuffer class is a monitor class. This class contains an array of request, a variable to track number of request and N which is the number of consumer threads and the size of the request array. The BoundedBuffer constructor sets the values previosly mentioned then creates the specified number of threads. There is a inner class Consumerthread which extends the thread class and has a start method which calls removeRequest. In the removeRequest function these threads will wait til the producer thread adds request using the addRequest function. When a request is added by the producer, one of the consumer threads will take the request and go to the handle request function and handle the request. The addRequest and removeRequest functions are syncronized to ensure mutal exclusion, in order to prevent deadlock the threads are put to sleep in these methods if the number of request are meeting the condion needed for the specific function. The handleRequest function is not syncronized because many request can be handled at the same time without data corruption. 

The Main class makes a bounded buffer and then runs in an infinite loop creating request then adding them to the bounded buffer. In addition, the main class is where the producer creates new request and prints infromation about the request and producer.

#### How to run java project on linux
To run the java version first install the java development kit
1. run : sudo apt install openjdk-11-jdk
2. navigate from the project root directory to where the java code is using: cd java/src 
3. To compile and run the java version of the project run: make -f makefile 

#### c++ design
The c++ design consists of 4 classes, Semaphore, Request, BoundedBuffer, and Main.

The Semaphore class is a premade design taken from https://riptutorial.com/cplusplus/example/30142/semaphore-cplusplus-11 , which implements the use of semaphores. For this design, we utlize semaphores as opposed to Monitors, some small changes were made.

The Request class, like its java equivalent, is used to store simple information such as the requests id and its request time.

The BoundedBuffer class 4 parts: The initailization, addRequest, removeRequest, and handleRequest. The constructor initializes the semaphores used sets the size of the request array. the add request is handled by the producer thread it adds a request to the request vector. The add request funtion first checks the empty semaphore which repersents when the semaphore is full it waits, if it is not full it takes the "mutex" so the removerequest function cannot run, or alterantivaly it waits for the mutex to be free it then runs and releases the mutex after adding an item and allows another thread to run, either addRequest or removeRequest. The semaphore use in removeRequest is the same design but it checks the full semaphore instead of the empty. the remove request remove request from the requests vector and adds handles sends them to the handle request function which makes the one of the consumer threads sleep for the request length then prints consumer and time info.

#### how to run c++ on linux
To run the c++ version 
1. navigate from project root directory to the c++ file using: cd c++
2. run: g++ main.cpp -lpthread
3. run: ./a.out
