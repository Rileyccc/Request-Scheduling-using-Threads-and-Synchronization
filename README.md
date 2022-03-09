# Request-Scheduling-using-Threads-and-Synchronization

Riley Clark


java:design

The java design consist of three classes Request, BoundedBuffer, and Main. 

The request class is simple infromation about a request. Every request has an id and time.

The BoundedBuffer class is a monitor class. This class contains an array of request, a variable to track number of request and N which is the number of consumer threads and the size of the request array. The BoundedBuffer constructor sets the values previosly mentioned then creates the specified number of threads. There is a inner class Consumerthread which extends the thread class and has a start method which calls removeRequest. In the removeRequest function these threads will wait til the producer thread adds request using the addRequest function. When a request is added by the producer, one of the consumer threads will take the request and go to the handle request function and handle the request. The addRequest and removeRequest functions are syncronized to ensure mutal exclusion, in order to prevent deadlock the threads are put to sleep in these methods if the number of request are meeting the condion needed for the specific function. The handleRequest function is not syncronized because many request can be handled at the same time without data corruption. 

The Main class makes a bounded buffer and then runs in an infinite loop creating request then adding them to the bounded buffer. In addition, the main class is where the producer creates new request and prints infromation about the request and producer.

To run the java version first install the java development kit
1. run : sudo apt install openjdk-11-jdk
2. navigate from the project root directory to where the java code is using: cd java/src 
3. run: make -f makefile //to compile and run the java version of the progect
