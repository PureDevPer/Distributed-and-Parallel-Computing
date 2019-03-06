package proj;

import org.apache.hadoop.io.Text;

public class airefare {
	
	private int num;
	private String airportCode;
	private String airportName;
	private String airportCity;
	private String airportState;
	private double fare;
	
	
	public airefare(Text text) {
		String[] col = text.toString().split(",");
		
		this.num = 0;
		this.airportCode = col[1];
		this.airportName = col[2];
		this.airportCity = col[3];
		this.airportState = col[4];
		this.fare = Double.parseDouble(col[5]);
		
		
	}
	
	public String airport() {
		return this.airportCode;
	}
	

	public String getAirportName() {
		return this.airportName;
	}
	
	
	public String getAirportCity() {
		return this.airportCity;
	}
	
	
	public String getAirportState() {
		return this.airportState;
	}
	
	
	public double getFare() {
		return this.fare;
	}
}
