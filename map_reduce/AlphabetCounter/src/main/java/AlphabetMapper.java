import java.io.IOException;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapred.MapReduceBase;
import org.apache.hadoop.mapred.Mapper;
import org.apache.hadoop.mapred.OutputCollector;
import org.apache.hadoop.mapred.Reporter;

public class AlphabetMapper extends MapReduceBase implements Mapper<LongWritable, Text, Text, IntWritable> {
	public void map(LongWritable key, Text value,
		OutputCollector<Text, IntWritable> output, Reporter reporter) throws IOException {
		String line = value.toString();
		char[] arrCh = line.toCharArray();    
	        for(char c : arrCh)  
	        {  if(Character.isAlphabetic(c)) {
	        	char temp = Character.toLowerCase(c);
	            Text charKey = new Text(Character.toString(temp));  
	            IntWritable One = new IntWritable(1);  
	            output.collect(charKey, One);     
	        }
	     }  
	}
}