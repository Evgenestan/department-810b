package org.mai.dep110;
import java.util.concurrent.TimeUnit;
public class User implements Runnable{

    private static String g;
    public  User(String a){
        System.out.println(a);
        g = a;
    }
    @Override
    public void run(){
        for(int i = 0; i < 5; i++)
        {
            try{
                Thread.sleep(1000);		//Приостанавливает поток на 1 секунду
            }catch(InterruptedException e){}

            System.out.println(g);
        }
    }
}
