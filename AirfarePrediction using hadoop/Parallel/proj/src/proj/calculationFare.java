package proj;

public class calculationFare {

	private double[] fare;
	private double alpha;
	private double beta;
	private double[] l;
	private double[] t;
	private double f;
	
	public calculationFare(double[] f) {
		
		this.fare = new double[400];
		this.fare = f;
		this.alpha = 0.3;
		this.beta = 0.6;
		
		this.l = new double[400];
		this.t = new double[400];
		this.f = 0.0;
		
		arr_initialization();
		
	}
	
	public void arr_initialization() {
		for(int i = 0 ; i < 400 ; ++i) {
			
			l[i] = 0.0;
			t[i] = 0.0;
			fare[i] = 0.0;

		}
	}
	
	public void findAirFare() {

		l[0] = fare[0]; t[0] = 0.0;
		
		for(int i = 1 ; i < 400 ; ++i) {
			this.l[i] = this.alpha*this.fare[i] + (1-this.alpha)*(this.l[i-1] + this.t[i-1]);
			this.t[i] = this.beta*(this.l[i] - this.l[i-1]) + (1-this.beta)*this.t[i-1];
			this.f = this.l[i] + this.t[i];
		}
	}
	
	
	// AirFare prediction ticket
	public double getF() {
		return this.f;
	}
	
}
