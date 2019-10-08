package org.mai.dep810.cer;

import java.math.BigDecimal;
import java.util.Currency;

/**
 * Created by Asus on 9/17/2018.
 */
public class Main {
    public static void main(String[] args) {
        Currency usd = Currency.getInstance("USD");
        Currency gbp = Currency.getInstance("GBP");

        Money usdMoney = new Money(usd, new BigDecimal(100));
        Money tenDollars = new Money(usd, new BigDecimal(10.5));
        Money tenPound = new Money(gbp, new BigDecimal(10));
        CurrencyExchangeRate poundToUsd = new CurrencyExchangeRate(new BigDecimal(1.5), gbp, usd);

        //should set usdMoney 110 with scale 2
        usdMoney = usdMoney.add(tenDollars);
        System.out.println(usdMoney.getAmount());
        System.out.println(usdMoney.getAmount().equals(new BigDecimal(110).setScale(2)));

        //should throw DifferentCurrenciesException
        /*try {
            usdMoney = usdMoney.subtract(tenPound);
        } catch(DifferentCurrenciesException ex) {
            System.out.println("DifferentCurrenciesException thrown");
        }*/

        //should set usdMoney 95 with scale 2
        usdMoney = usdMoney.subtract(poundToUsd.convert(tenPound));
        System.out.println(usdMoney.getAmount().equals(new BigDecimal(95).setScale(2)));
        System.out.println(usdMoney.getAmount());
        System.out.println(new BigDecimal(95).setScale(2));
        System.out.println(tenDollars.getAmount());
        System.out.println("DDD");
        Money u = tenDollars.devide(new BigDecimal(11));
        System.out.println(u.getAmount());
        System.out.println(u.getAmount().multiply(new BigDecimal(5.3)));


    }
}
