package pac; 

public class Main {
	public static void main(String[] args) {
		// number of request allowed to be in buffer, and number of slave threads
		int N = 10;
		// upper bound for the amount of time the master thread will wait to add request
		int M = 1;
		
		BoundedBuffer boundedBuffer = new BoundedBuffer(N);
		
		int requestId = 1; 
		int requestLength = 0;
		int producerSleepTimer = 0;
		Request r = null;
		
		while(true) {
			
			try {
				// make masterThread sleep for random amount of time
				Thread.sleep((int)((Math.random()*N) *1000));
			
				// calculate request length
				requestLength = (int)(Math.random() * M + 1);
				
//				Producer: produced request ID n, length t seconds at time CURRENT-TIME
//				Producer: sleeping for X seconds
				
				//create new request
				r = new Request(requestId++, requestLength);
				System.out.printf("Producer: produced request ID %d, length %d seconds at time %d\n", requestId, requestId, System.currentTimeMillis());
				//add request to bounded buffer
				boundedBuffer.addRequest(r);
				
				producerSleepTimer = (int)((Math.random()*4));
				
				System.out.printf("Producer: sleeping for %d seconds\n", producerSleepTimer);
				
				// make masterThread sleep for random amount of time
				Thread.sleep(producerSleepTimer*1000);
				
				
				
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			
			
		}
	}
}
