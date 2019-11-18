package mai.dep810.task_03;

public class WebSite
{
    private String _page;
    private int _counter;

    public WebSite(String page)
    {
        _page = page;
        _counter = 0;
    }

    synchronized public void visit()
    {
        try {
            wait(0);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        _counter++;
        notify();
        System.out.println(Thread.currentThread().getName());
    }

    @Override
    public String toString()
    {

        var res = new StringBuffer();

        res.append("WebSite - ");
        res.append(_page);
        res.append(" Count visits - ");
        res.append(_counter);

        return res.toString();
    }
}

/*public class WebSite
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
}*/
