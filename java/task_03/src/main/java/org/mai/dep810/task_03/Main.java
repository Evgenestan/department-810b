package mai.dep810.task_03;

import mai.dep810.task_03.WebSite;

import java.util.ArrayList;
import java.util.concurrent.*;

public class Main
{
    public static void main(String[] args) throws InterruptedException
    {
        var pages = new WebSite [5];

        pages [0] = new WebSite("www.google.com");
        pages [1] = new WebSite("www.facebook.com");
        pages [2] = new WebSite("www.twitter.com");
        pages [3] = new WebSite("www.yandex.ru");
        pages [4] = new WebSite("www.instagram.com");

        var threads = new Thread[10];

        for (int i = 0; i < 10; i++)
        {
            threads[i] = new Thread(()->
            {
                int pageNum =(int) rnd(5);
                pages[pageNum].visit();
            });
        }

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                threads[i].run();
            }
        }

        for (var page : pages)
        {
            System.out.println(page);
        }

        /*var webSitesVisits = new WebSite();

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

        System.out.println(webSitesVisits);*/
    }

    public static double rnd(final double max)
    {
        return Math.random() * max;
    }



}
