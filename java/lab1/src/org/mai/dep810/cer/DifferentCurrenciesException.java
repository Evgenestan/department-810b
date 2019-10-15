package org.mai.dep810.cer;

/**
 * Created by VPerov on 17.09.2018.
 */
public class DifferentCurrenciesException extends RuntimeException {
    public DifferentCurrenciesException(String message) {
        super(message);
    }
}
