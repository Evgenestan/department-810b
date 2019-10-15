package mai.dep810.task_03;

import java.util.ArrayList;
import java.util.concurrent.*;

public class Main
{
    public static void main(String[] args) throws InterruptedException
    {
        var webSitesVisits = new WebSite();

        var executor = Executors.newFixedThreadPool(50);

        var googleVisiter = new WebSiteVisiter(webSitesVisits,"www.google.com");
        var twitterVisiter = new WebSiteVisiter(webSitesVisits,"www.twitter.com");
        var yandexVisiter = new WebSiteVisiter(webSitesVisits,"www.yandex.ru");
        var vkVisiter = new WebSiteVisiter(webSitesVisits,"www.vkonakte.com");

        var listVisitsCall = new ArrayList<WebSiteVisiter>();

        for (int i = 0; i < 10; i++)
        {
            listVisitsCall.add(googleVisiter);
            listVisitsCall.add(twitterVisiter);
            listVisitsCall.add(yandexVisiter);
            listVisitsCall.add(vkVisiter);
        }

        executor.invokeAll(listVisitsCall);
        executor.shutdown();

        System.out.println(webSitesVisits);
    }
}
