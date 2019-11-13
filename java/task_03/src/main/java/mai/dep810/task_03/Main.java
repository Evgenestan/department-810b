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
                for(int j = 0;j<50; j++) {
                    int pageNum = (int) rnd(5);
                    pages[pageNum].visit();
                }
            });
            threads[i].start();

        }

        for (int i = 0; i < 10; i++)
        {
            threads[i].join();
        }

        for (var page : pages)
        {
            System.out.println(page);
        }

        //через wait notify
    }

    public static double rnd(final double max)
    {
        return Math.random() * max;
    }



}
