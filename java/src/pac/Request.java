package pac;

public class Request {
	private int id;
	private int time;
	
	
	public Request(int id, int time) {
		this.id = id;
		this.time = time; 
	}
	
	public int getId() {
		return id;
	}
	
	public int getTime() {
		return time;
	}

}
