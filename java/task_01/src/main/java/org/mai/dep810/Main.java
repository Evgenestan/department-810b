package org.mai.dep810;

import java.math.BigDecimal;
import java.math.RoundingMode;
import java.text.DecimalFormat;
import java.util.Currency;

public class Main
{
    public static void main(String [] args)
    {
        //dsds
        var usd = Currency.getInstance("USD");
        var gbp = Currency.getInstance("GBP");

        var usdMoney = new Money(usd, new BigDecimal(100));
        var number = new BigDecimal(103);
        var amount = new Money(usd, number);

        var num = new BigDecimal(28);
        //System.out.println(number.divide(num).setScale(2).toPlainString());

        System.out.println(number.divide(num, 2,RoundingMode.FLOOR));



        System.out.println("Then");
        var monies = amount.devideOnNew(num);
        for (var money : monies)
        {
            System.out.println(money);
        }
        //var checkdevision = Money.sum(monies);

        var itog = new BigDecimal(0);
        for (var money : monies)
        {
            itog = itog.add(money);
            //System.out.println(money);

        }

        System.out.println(itog);
        //System.out.println(checkdevision);

        var tenDollars = new Money(usd,new BigDecimal(10));
        var tenPound = new Money(gbp, new BigDecimal(10));
        CurrencyExchangeRate poundToUsd = new CurrencyExchangeRate(new BigDecimal(1.5), gbp, usd);

        //should set usdMoney 110 with scale 2
        usdMoney = usdMoney.add(tenDollars);
        System.out.println(usdMoney.getAmount().equals(new BigDecimal(110).setScale(2)));

        //should throw DifferentCurrenciesException
        try
        {
            usdMoney = usdMoney.subtract(tenPound);
        }
        catch(DifferentCurrenciesException ex)
        {
            System.out.println("DifferentCurrenciesException thrown");
        }



        //should set usdMoney 95 with scale 2
        usdMoney = usdMoney.subtract(poundToUsd.convert(tenPound));
        System.out.println(usdMoney.getAmount().equals(new BigDecimal(95).setScale(2)));

    }
}
