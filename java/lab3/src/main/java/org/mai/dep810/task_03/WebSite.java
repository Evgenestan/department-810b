package mai.dep810.task_03;

import java.util.HashMap;
import java.util.Map;

public class WebSite
{
    private Map<String,Integer> visits;

    public WebSite()
    {
        visits = new HashMap<>();
    }

    public void addVisit(String webPage)
    {
        if(visits.containsKey(webPage))
        {
            int oldValue = visits.get(webPage);
            visits.replace(webPage,oldValue+1);
        }
        else
        {
            visits.put(webPage,1);
        }

        System.out.println();
    }

    @Override
    public String toString()
    {
        var result = new StringBuffer();

        for(var value : visits.entrySet())
        {
            result.append(value.getKey());
            result.append(" ");
            result.append(value.getValue());
            result.append("\n");
        }

        return result.toString();
    }
}
