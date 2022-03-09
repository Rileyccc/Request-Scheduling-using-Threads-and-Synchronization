package pac;

public class BoundedBuffer {
	
	private Request[] requestBuffer;
	private int numOfRequest;
	private int N;
	
	public BoundedBuffer(int N) {
		this.requestBuffer = new Request[N];
		this.numOfRequest = 0;
		this.N = N;
		
		createThreadArmy(N);
	}
	
	
	public void createThreadArmy(int N) {
		ConsumerThread ct;
		for(int i = 0; i < N; i++) {
			ct = new ConsumerThread();
			// create thread 
			Thread t = new Thread(ct);
			// start thread 
			t.start();
		}
	}
	
	
	public synchronized void addRequest(Request r) {
		
		// while request buffer is full wait
		try {	
			while(numOfRequest == N - 1) {
				wait();
			}
		} catch (InterruptedException e) {
				e.printStackTrace();			
		}
		
		// add request to requestbuffer
		requestBuffer[numOfRequest++] = r; 
		notify(); // notify any waiting threads job is done
	
	}
	
	private synchronized void removeRequest() {
		
		// while request buffer is empty wait for new request
		try {
			while(numOfRequest == 0) {
				wait();
			}
		}catch(InterruptedException e) {
			e.printStackTrace();
		}
		// decrement num of request
		--numOfRequest;
		
		// extract request details
		int id = requestBuffer[numOfRequest].getId();
		int time = requestBuffer[numOfRequest].getTime();
		
		// print consumer message
		System.out.printf("Consumer %d: assigned request ID %d, processing request for the next %d seconds\n",
				Thread.currentThread().getId(), id, time);
		
		// handle request 
		handleRequest(id, time);
		
		// remove requeset from buffer and decreament num of request
		requestBuffer[numOfRequest] = null; 
		
		notify(); // notify any waiting threads job is done
		
		// after completion stay in removeRequest to complete more tasks 
		removeRequest();
	}
	
	public void handleRequest(int id, int time) {
		//convert milliseconds to seconds and make the thread sleep for amount of time
		try {
			Thread.sleep(time);
		}catch(InterruptedException e) {
			e.printStackTrace();
		}
		// print request info simulate doing a task
		System.out.printf("Consumer %d: completed request ID %d at time %d\n",
				Thread.currentThread().getId(), id, System.currentTimeMillis());
	}
	
	class ConsumerThread implements Runnable{

		@Override
		public void run() {
			removeRequest();
		}
		
	}

}
