package org.mai.dep810;

import java.math.BigDecimal;
import java.math.MathContext;
import java.math.RoundingMode;
import java.text.DecimalFormat;
import java.util.Currency;

public class Money
{
    private Currency currency;
    private BigDecimal amount;

    public Money(Currency currency, BigDecimal amount)
    {
        this.currency = currency;
        this.amount = amount.setScale(this.currency.getDefaultFractionDigits(),RoundingMode.HALF_UP);
    }

    public Currency getCurrency() {
        return currency;
    }

    public BigDecimal getAmount() {
        return amount;
    }

    public Money add(Money m)
    {
        if(m.getCurrency().getCurrencyCode()!=currency.getCurrencyCode())
        {
            throw new DifferentCurrenciesException("Складываются разные валюты");
        }
        var resAmount = this.amount.add(m.amount,new MathContext(4));
        var result = new Money(this.currency,resAmount);

        return result;
    }

    public Money subtract(Money m)
    {
        if(m.getCurrency().getCurrencyCode()!=currency.getCurrencyCode())
        {
            throw new DifferentCurrenciesException("Складываются разные валюты");
        }

        var resAmount = this.amount.subtract(m.amount,new MathContext(4,RoundingMode.HALF_UP));
        var result = new Money(this.currency,resAmount);

        return result;
    }

    public Money multiply(BigDecimal ratio)
    {
        var resAmount = this.amount.multiply(ratio,new MathContext(4,RoundingMode.HALF_UP)).setScale(2,RoundingMode.HALF_UP);
        var result = new Money(this.currency,resAmount);

        return result;
    }

    public Money devide(BigDecimal ratio)
    {
        var resAmount = this.amount.divide(ratio,4,RoundingMode.HALF_UP);
        var result = new Money(this.currency,resAmount);

        return result;
    }


    public BigDecimal[] devideOnNew (BigDecimal ration){
        int n = ration.intValue();
        BigDecimal[] result = new BigDecimal[n];
        BigDecimal a = amount.divide(ration, 2,RoundingMode.FLOOR);
        BigDecimal r = amount.subtract(a.multiply(ration));

        for(int i = 0 ; i < n; ++i){
            result[i] = a;
        }

        for(int i = 0; i< new BigDecimal(100).multiply(r).intValue();++i){
            result[i]=result[i].add(new BigDecimal(0.01)).setScale(2, RoundingMode.FLOOR);
        }
        //System.out.println("Ostatok");
        //System.out.println(r);



        return result;

    }


    public BigDecimal[] devideOn (BigDecimal ration)
    {
        int n = ration.intValue();
        BigDecimal[] result = new BigDecimal[n];
        BigDecimal p = new BigDecimal(0);

        if (amount.remainder(BigDecimal.valueOf(n)).compareTo(p) == 0){
            for (int i = 0; i < n; i++ ){
                result[i] = amount.divide(BigDecimal.valueOf(n));
            }
            return result;
        }
        else{
            int k = 0;
            try{
                result[0] = amount.divide(BigDecimal.valueOf(n));
            } catch (ArithmeticException ex) {
                k = 1;
                for (int i = 0; i < n; i++){
                    result[i] = amount.divideAndRemainder(BigDecimal.valueOf(n))[0];
                }
                double vs = (1/(Math.pow(10, this.currency.getDefaultFractionDigits())));
                Double z = amount.divideAndRemainder(BigDecimal.valueOf(n))[1].doubleValue();

                //System.out.println(" pppppp " + (z - vs*n));
                while (z > 0){
                    for (int i = 0; i < n; i++){
                        z = z - vs;
                        if (z < 0){
                            break;
                        }
                        else {

                            result[i] = result[i].add(BigDecimal.valueOf(vs));
                        }

                    }

                }
                return result;
            }

            if (k == 0){
                for (int i = 0; i < n; i++ ){
                    result[i] = amount.divide(BigDecimal.valueOf(n));
                }
            }

            return result;
        }
    }

    public static Money sum(Money monies[])
    {
        for (int i =1; i < monies.length;i++)
        {
            var prevCurrency = monies[i-1].currency;
            var currentCurrency = monies[i].currency;

            if (currentCurrency.getCurrencyCode()!=currentCurrency.getCurrencyCode())
            {
                throw new DifferentCurrenciesException("Суммируются различные валюты");
            }
        }

        var currency = monies[0].currency;

        var sum =  new Money(currency,new BigDecimal(0));

        for (var n : monies)
        {
            sum = sum.add(n);
        }

        return sum;
    }

    @Override
    public String toString()
    {
        var decimalFormat = new DecimalFormat("#,####.00");
        return decimalFormat.format(amount);
    }
}
