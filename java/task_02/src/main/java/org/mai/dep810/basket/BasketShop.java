package org.mai.dep810.basket;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class BasketShop implements Basket
{
    private HashMap<String,Integer> products;

    public BasketShop()
    {
        products = new HashMap();
    }

    @Override
    public void addProduct(String product, int quantity)
    {
        if(quantity <= 0)
        {
            throw new IllegalArgumentException("Количество товара должно быть числом, больлшим нуля");
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
            var errorMessage = new StringBuilder();
            errorMessage.append("Продукта ")
                    .append(product)
                    .append("  корзине нет");
            throw new ProductNotFoundException(errorMessage.toString());
        }
        else
        {
            products.remove(product);
        }
    }

    @Override
    public void updateProductQuantity(String product, int quantity)
    {
        if(quantity <= 0)
        {
            throw new IllegalArgumentException("Количество товара должно быть числом, больлшим нуля");
        }
        else if(!products.containsKey(product))
        {
            var errorMessage = new StringBuilder();
            errorMessage.append("Продукта ")
                    .append(product)
                    .append("  корзине нет");
            throw new ProductNotFoundException(errorMessage.toString());
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
            var errorMessage = new StringBuilder();
            errorMessage.append("Продукта ")
                    .append(product)
                    .append("  корзине нет");
            throw new ProductNotFoundException(errorMessage.toString());
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
