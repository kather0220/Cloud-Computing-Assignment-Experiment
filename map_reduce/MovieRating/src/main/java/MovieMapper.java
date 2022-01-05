import java.io.IOException;
import java.util.StringTokenizer;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapred.MapReduceBase;
import org.apache.hadoop.mapred.Mapper;
import org.apache.hadoop.mapred.OutputCollector;
import org.apache.hadoop.mapred.Reporter;

public class MovieMapper extends MapReduceBase implements Mapper<LongWritable, Text, IntWritable, IntWritable> {
	public void map(LongWritable key, Text value,
		OutputCollector<IntWritable, IntWritable> output, Reporter reporter) throws IOException {
	
		MyLog log = new MyLog();
		
		String[] cols = value.toString().split("::");
		
		int uid = Integer.valueOf(cols[0]);
		int rating = Integer.valueOf(cols[2]);
		
		output.collect(new IntWritable(uid), new IntWritable(rating));
		
		
	     
	}
}