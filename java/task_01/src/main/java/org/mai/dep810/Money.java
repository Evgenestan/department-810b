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

    public Money[] devideOn (BigDecimal ration)
    {
        int n = ration.intValue();
        var monies = new Money[n];

        var number = this.devide(ration);
        var checking = number.multiply(ration).amount;


        if(!checking.equals(this.amount))
        {
            var reminder = amount.subtract(checking, new MathContext(4, RoundingMode.HALF_UP));

            BigDecimal rem;

            for (int i = 2; i < n; i++)
            {
                var divider = new BigDecimal(i);
                rem = reminder.divide(divider, 2,RoundingMode.HALF_UP);
                var checkDevide = rem.multiply(divider);
                if(reminder.equals(checkDevide))
                {
                    rem = rem.add(number.amount,new MathContext(4));
                    for (int j = 0; j < n - i; j++)
                    {
                        monies[j] = new Money(currency,number.amount);
                    }
                    for (int j = n - i; j < n; j++)
                    {
                        monies[j] = new Money(currency,rem);
                    }
                    break;
                }
            }
            if(monies[0] == null)
            {
                for (int i = 0; i < n - 1; i++)
                {
                    monies[i] = number;
                }

                var value = number.amount.add(reminder, new MathContext(4));
                monies[n-1] =  new Money(currency,value);
            }
        }
        else
        {
            for (int i = 0; i < n ; i++)
            {
                monies[i] = number;
            }
        }

        return monies;
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
