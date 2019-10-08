package org.mai.dep810.cer;

import sun.reflect.generics.reflectiveObjects.NotImplementedException;
import java.math.BigDecimal;
import java.util.Currency;

/**
 * Created by VPerov on 17.09.2018.
 */
public class CurrencyExchangeRate {

    private Currency cur_from;
    private Currency cur_to;
    private BigDecimal rate;

    public CurrencyExchangeRate(BigDecimal rate, Currency from, Currency to) {
        this.cur_from = from;
        this.rate = rate;
        this.cur_to = to;
    }

    public Money convert(Money m) {
        boolean flag = false;
        Currency temp;
        BigDecimal rezult;
        if(m.getCurrency().equals(this.cur_from)){
            temp = this.cur_to;
            rezult = m.getAmount().multiply(this.rate);
        }
        else if (m.getCurrency().equals(this.cur_to)){
            temp = this.cur_from;
            rezult = m.getAmount().divide(this.rate);
        }
        else {
            throw new DifferentCurrenciesException("Error during convert procedure. There is no such a currency.");
        }
        return new Money(temp,rezult);
        //throw new NotImplementedException();
    }
}
