package mai.dep810.task_03;

import java.util.HashMap;
import java.util.Map;

public class Page {
    private String website;
    private Integer count;
    public Page(String _website)
    {
        website = _website;
        count = 0;
    }
    public synchronized void Visit(){
        this.count +=1;
    }

    @Override
    public String toString() {
        StringBuffer sb = new StringBuffer();
        sb.append(website);
        sb.append(count);
        return sb.toString();
    }
}
