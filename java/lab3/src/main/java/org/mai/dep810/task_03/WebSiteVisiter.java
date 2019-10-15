package mai.dep810.task_03;

import java.util.concurrent.Callable;

public class WebSiteVisiter implements Runnable, Callable<String>
{
    private WebSite webSites;
    private String webSite;

    public WebSiteVisiter(WebSite _webSites,String _webSite)
    {
      webSites = _webSites;
      webSite = _webSite;
    }

    @Override
    public void run()
    {
        webSites.addVisit(webSite);
    }


    /**
     * Computes a result, or throws an exception if unable to do so.
     *
     * @return computed result
     * @throws Exception if unable to compute a result
     */
    @Override
    public String call() throws Exception
    {
        run();
        return webSite;
    }
}
