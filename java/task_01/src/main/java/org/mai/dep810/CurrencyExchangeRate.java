package org.mai.dep810;

import java.math.BigDecimal;
import java.util.Currency;

/**
 * Created by VPerov on 17.09.2018.
 */
public class CurrencyExchangeRate
{
    private BigDecimal _rate;
    private  Currency _from;
    private  Currency _to;

    public CurrencyExchangeRate(BigDecimal rate, Currency from, Currency to)
    {
        _rate = rate;
        _from = from;
        _to = to;
    }

    public Money convert(Money m)
    {
        if(!(m.getCurrency().equals(_from)||(m.getCurrency().equals(_to))))
            throw new IncorrectExchangeRateException("Different currency");
        Money result = new Money(_to,m.getAmount().multiply(_rate));
        return result;
    }
}
