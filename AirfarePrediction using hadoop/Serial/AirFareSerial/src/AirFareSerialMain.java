
public class AirFareSerialMain {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		// args[0] = inputFileName; args[1] = outputFileName;
		String inputFileName = "2011_Q1.csv";
		String outputFileName = "output";
		AirFareSerial airfare = new AirFareSerial(inputFileName, outputFileName);
		airfare.parseFile();
		airfare.findAirFare();
		airfare.writeOutput();
	}

}
