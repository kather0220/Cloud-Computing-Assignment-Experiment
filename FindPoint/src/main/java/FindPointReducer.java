import java.io.IOException;
import java.util.Iterator;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapred.MapReduceBase;
import org.apache.hadoop.mapred.OutputCollector;
import org.apache.hadoop.mapred.Reducer;
import org.apache.hadoop.mapred.Reporter;
import org.apache.hadoop.util.StringUtils;

public class FindPointReducer extends MapReduceBase implements Reducer<PointWritable, Text, Text, Text> {
	
	private static double DIST_CUTOFF = 5.0;
	
	public void reduce(PointWritable key, Iterator<Text> values,
	OutputCollector<Text, Text> output, Reporter reporter) throws IOException {
	
	String out = "";
	while(values.hasNext()){
		String[] cols = StringUtils.getStrings(values.next().toString());
		int x = Integer.parseInt(cols[0]);
		int y = Integer.parseInt(cols[1]);
		
		double dist = Math.sqrt(Math.pow(key.getPoint().x - x, 2) + Math.pow(key.getPoint().y - y, 2));
		
		if(dist <= DIST_CUTOFF)
			out = out + cols[0] + "," + cols[1]+ " ";
	}
	output.collect(new Text(String.valueOf(key.getPoint().x)+ ","+ 
	String.valueOf(key.getPoint().y)), new Text(out));
		
	}
}