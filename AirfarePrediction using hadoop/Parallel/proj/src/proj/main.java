package proj;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;



public class main {
	
	public static class TokenizerMapper extends Mapper<DoubleWritable, Text, Text, DoubleWritable>{
		
		//map output
		private final static DoubleWritable outputValue = new DoubleWritable();
		// map output Key
		private Text outputKey = new Text();
		
		public void map(DoubleWritable key, Text value, Context context) throws IOException, InterruptedException{
			airefare af = new airefare(value);
			
			outputKey.set(af.airport());
			
			context.write(outputKey, outputValue);
		}
	}
	
	
	public static class FlightReducer extends Reducer<Text, DoubleWritable, Text, DoubleWritable>{
		
		private DoubleWritable result = new DoubleWritable();
		
		double[] fare = new double[400];
		int count = 0;
		
		public void reduce (Text key, Iterable<DoubleWritable> values, Context context) throws IOException, InterruptedException{
			
			for(DoubleWritable value : values) {
				fare[count] = value.get();
				++count;
			}
			
			calculationFare cf = new calculationFare(fare);
			cf.findAirFare();
			
			double ticketPrice = cf.getF();
			result.set(ticketPrice);
			
			context.write(key, result);
		}
	}
	
	public static void main(String[] args) throws Exception {
		Configuration conf = new Configuration();
		Job job = Job.getInstance(conf, "AirFare");
		job.setJarByClass(main.class);
		

		FileInputFormat.addInputPath(job, new Path(args[0]));
		FileOutputFormat.setOutputPath(job, new Path(args[1]));	
		
		job.setMapperClass(TokenizerMapper.class);
		
		job.setCombinerClass(FlightReducer.class);
		job.setReducerClass(FlightReducer.class);
		
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(DoubleWritable.class);
			
		
		System.exit(job.waitForCompletion(true)?0:1);
		
	}
}
