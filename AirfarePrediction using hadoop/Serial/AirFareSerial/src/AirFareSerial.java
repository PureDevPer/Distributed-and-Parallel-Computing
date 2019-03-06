import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class AirFareSerial {
	private String inputFileName;
	private String outputFileName;
	
	private String[] airport;
	double[][] fare;
	
	private int count;
	
	private double alpha;
	private double beta;
	private double[] l;
	private double[] t;
	private double [][] f;
	
	public AirFareSerial(String inputFileName, String outputFileName) {
		this.inputFileName = inputFileName;
		this.outputFileName = outputFileName;
		
		this.airport = new String[410];
		this.fare = new double[410][27];
		
		this.count = 0;
		
		this.alpha = 0.3;
		this.beta = 0.6;
		this.l = new double[410];
		this.t = new double[410];
		this.f = new double[410][1];
	}
	
	public void parseFile() {
		try {
			BufferedReader br = new BufferedReader(new FileReader(this.inputFileName));
			String line;
			
			while((line=br.readLine()) != null) {
				String[] splitLine = line.split(",");
				
				this.airport[count] = splitLine[0];
				
				for(int i = 0 ; i < this.fare[0].length ; ++i) {
					this.fare[count][i] = Double.parseDouble(splitLine[i+1]);
				}
				
				this.l[count] = 0.0;
				this.t[count] = 0.0;
				this.f[count][0] = 0.0;
				
				++this.count;
				
				br.close();
			}
			
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			System.err.println("File not found");
			System.exit(0);
		} catch (IOException e) {
			System.err.println("File not found");
			System.exit(0);
		}
		
		findAirFare();
	}
	
	
	public void writeOutput() {
		FileWriter fw;
		PrintWriter bw;
		
		try {
			fw = new FileWriter(this.outputFileName + ".txt");
			bw = new PrintWriter(fw);
			printAirFare(bw);
			bw.close();
			
		} catch (IOException e) {
			System.err.println("Cannot open output file");
		}
	}
	
	
	public void findAirFare() {
		

		int j = 0;
		for(int i = 0 ; i < this.count ; ++i) {
			l[i] = fare[i][0]; t[i] = 0.0;
			for(j = 1 ; j < this.fare[0].length ; ++j) {
				this.l[j] = this.alpha*this.fare[i][j] + (1-this.alpha)*(this.l[j-1] + this.t[j-1]);
				//System.out.println("Airport: " + this.airport[i] + "\tLn : " + this.l[j]);
				this.t[j] = this.beta*(this.l[j]-this.l[j-1]) + (1-this.beta)*this.t[j-1];
				//System.out.println("Airport: " + this.airport[i] + "\tTn : " + this.t[j]);
				this.f[i][0] = this.l[j] + this.t[j];
				
			}
			//this.f[i] = this.l[j] + this.t[j];
			//System.out.println("Ln : " + this.l[j]);
			//System.out.println("Ln : " + this.t[j]);
			System.out.println(i+1 + ". Airport: " + this.airport[i] + "\tFn : " + this.f[i][0]);
		}
	}
	
	public void printAirFare(PrintWriter bw) throws IOException{
		for(int i = 0 ; i < this.count ; ++i) {
			
			bw.write(String.valueOf(this.airport[i]));
			bw.write(",");
			bw.write(String.valueOf(this.f[i][0] +"\n"));
		}
	}
}
