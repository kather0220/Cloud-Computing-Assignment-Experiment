import java.io.IOException;
import java.util.StringTokenizer;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapred.MapReduceBase;
import org.apache.hadoop.mapred.Mapper;
import org.apache.hadoop.mapred.OutputCollector;
import org.apache.hadoop.mapred.Reporter;

public class WordCountMapper extends MapReduceBase implements Mapper<LongWritable, Text, Text, IntWritable> {
	public void map(LongWritable key, Text value,
		OutputCollector<Text, IntWritable> output, Reporter reporter) throws IOException {
	
		MyLog log = new MyLog();
		
		String line = value.toString();
		StringTokenizer tokenizer = new StringTokenizer(line);
		while (tokenizer.hasMoreTokens()) {
			Text outputKey = new Text(tokenizer.nextToken());
			// info 는 string 타입 받으므로 string 으로 cast
			log.logger.info("***"+ outputKey.toString());
			output.collect(outputKey, new IntWritable(1));
		}
	     
	}
}