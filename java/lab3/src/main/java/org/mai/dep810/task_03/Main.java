package mai.dep810.task_03;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.*;

public class Main
{
    public static void main(String[] args) throws InterruptedException
    {
        Page wArr[] = new Page[5];
        wArr[0] = new Page("Vk.com");
        wArr[1] = new Page("mail.com");
        wArr[2] = new Page("google.com");
        wArr[3] = new Page("foot.com");
        wArr[4] = new Page("ball.com");


        var threads = new Thread[10];

        for (int i = 0; i< 10; ++i){
            threads[i] = new Thread(()->{
                var temp = Math.random()*wArr.length;
                wArr[(int)temp].Visit();
            });

        }
        for(int i = 0; i<10; ++i){
            for(int j = 0; j<50; ++j){
                threads[i].run();
            }
        }

        for (int i =0 ; i < wArr.length; ++i){
            System.out.println(wArr[i]);
        }

    }
}
