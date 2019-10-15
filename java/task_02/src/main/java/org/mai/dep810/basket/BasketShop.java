package org.mai.dep810.basket;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class BasketShop implements Basket
{
    private HashMap<String,Integer> products;

    public BasketShop()
    {
        products = new HashMap<String, Integer>();
    }

    @Override
    public void addProduct(String product, int quantity)
    {
        if(products.containsKey(product))
        {
            throw new IllegalArgumentException("Такой ключ уже есть");
        }
        else
        {
            products.put(product,quantity);
        }
    }

    @Override
    public void removeProduct(String product)
    {
        if(!products.containsKey(product))
        {
            throw new IllegalArgumentException("Такого ключа нет");
        }
        else
        {
            products.remove(product);
        }
    }

    @Override
    public void updateProductQuantity(String product, int quantity)
    {
        if(!products.containsKey(product))
        {
            throw new IllegalArgumentException("Такого ключа нет");
        }
        else
        {
            products.replace(product,quantity);
        }
    }

    public Integer getProductQuantity(String product)
    {
        if(!products.containsKey(product))
        {
            throw new IllegalArgumentException("Такого ключа нет");
        }
        else
        {
            return products.get(product);
        }
    }

    @Override
    public List<String> getProducts()
    {
        return new ArrayList<>(products.keySet());
    }
}
