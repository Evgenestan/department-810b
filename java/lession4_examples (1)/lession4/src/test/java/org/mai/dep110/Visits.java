package org.mai.dep110;


import java.util.LinkedHashMap;
import java.util.Map;

public class Visits {
    Map<String, Integer> mySite = new LinkedHashMap<String, Integer>();
    static User obj;
    static User obj2;
    public static void main( String[] args ){
        obj = new User("1");
        obj2 = new User("2");
        Thread myThread = new Thread(obj);
        Thread myThread2 = new Thread(obj2);
        myThread.start();
        myThread2.start();
        for(int i = 0; i < 5; i++)
        {
            try{
                Thread.sleep(1000);		//Приостанавливает поток на 1 секунду
            }catch(InterruptedException e){}

            System.out.println("Primary!");
        }
        System.out.println("End");
    }


}
