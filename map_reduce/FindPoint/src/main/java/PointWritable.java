import java.io.IOException;
import java.io.DataInput;
import java.io.DataOutput;

import org.apache.hadoop.io.WritableComparable;

public class PointWritable implements WritableComparable<PointWritable> {
	private Point p = new Point(0,0);
	public PointWritable() {
		
	}
	
	public PointWritable(Point p) {
		this.p = p;
	}
	
	public Point getPoint() {
		return p;
	}
	public void readFields(DataInput in) throws IOException {
		p.x = in.readInt();
		p.y = in.readInt();
	}
	public void write(DataOutput out) throws IOException {
		out.writeInt(p.x);
		out.writeInt(p.y);
	}
	
	// x1 = x2
	// y1 < y2 -1
	// y1 = y2 0
	// y1 > y2 1
	public int compareTo(PointWritable that) {
		if (this.p.x == that.p.x)
			return (this.p.y<that.p.y? -1: (this.p.y == that.p.y? 0: 1));
		else
			return (this.p.x<that.p.x? -1: (this.p.x == that.p.x? 0: 1));
	}
}
