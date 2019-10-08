package org.mai.dep810.cer;

import sun.reflect.generics.reflectiveObjects.NotImplementedException;



import java.math.BigDecimal;
import java.math.MathContext;
import java.math.RoundingMode;
import java.util.Currency;

public class Money {
    private Currency currency;
    private BigDecimal amount;

    public Money(Currency currency, BigDecimal amount) {
        this.currency = currency;
        this.amount = amount.setScale(this.currency.getDefaultFractionDigits(),RoundingMode.HALF_UP);
    }

    public Currency getCurrency() {
        return currency;
    }

    public BigDecimal getAmount() {
        return amount;
    }

    public Money add(Money m) {
        if(!m.getCurrency().equals(this.getCurrency())){
            throw new DifferentCurrenciesException("Attention");
        }
        //throw new NotImplementedException();
        return new Money(this.getCurrency(), m.getAmount().add(this.amount, new MathContext(4)));
    }

    public Money subtract(Money m) {
        if(!m.getCurrency().equals(this.getCurrency())){
            throw new DifferentCurrenciesException("Attention");
        }
        return  new Money(this.getCurrency(),this.getAmount().subtract(m.getAmount(), new MathContext(4,RoundingMode.HALF_UP)));
    }

    public Money multiply(BigDecimal ratio) {

        return new Money(this.getCurrency(),this.getAmount().multiply(ratio,new MathContext(4,RoundingMode.HALF_UP)).setScale(2,RoundingMode.HALF_UP));
    }

    public Money devide(BigDecimal ratio) {
        //ratio.di
        return new Money(this.getCurrency(),this.getAmount().divide(ratio,4, RoundingMode.HALF_UP));
    }
}
