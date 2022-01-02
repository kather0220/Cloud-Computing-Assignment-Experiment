import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapred.JobConf;
import org.apache.hadoop.mapred.MapReduceBase;
import org.apache.hadoop.mapred.Mapper;
import org.apache.hadoop.mapred.OutputCollector;
import org.apache.hadoop.mapred.Reporter;
import org.apache.hadoop.util.StringUtils;

public class FindPointMapper extends MapReduceBase implements Mapper<LongWritable, Text, PointWritable, Text> {
	
	private List<Point> N;
	public void configure(JobConf job) {
		N = new ArrayList<Point>();
	}
	public void map(LongWritable key, Text value,
		OutputCollector<PointWritable, Text> output, Reporter reporter) throws IOException {
	
		MyLog log = new MyLog();
		
		
		String[] cols = StringUtils.getStrings(value.toString());
		int x = Integer.parseInt(cols[1]);
		int y = Integer.parseInt(cols[2]);
		
		if(cols[0].equals("N")) {
			N.add(new Point(x,y));
		}else {
			while(N.size() != 1000);
			for(Point n : N)
				output.collect(new PointWritable(new Point(x,y)), new Text(","+String.valueOf(n.x)+","+ String.valueOf(n.y)));
		}
		
		
	     
	}
}