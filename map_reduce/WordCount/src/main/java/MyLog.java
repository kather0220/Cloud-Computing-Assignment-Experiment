import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
public class MyLog {
	public Logger logger;
	public MyLog() {

		this.logger = LoggerFactory.getLogger(this.getClass());
	}
}