package org.mai.dep110.collections.basket;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class BasketImpl implements Basket {

    private HashMap<String,Integer> products;

    public BasketImpl(){
        products = new HashMap<String,Integer>();
    }

    @Override
    public void addProduct(String product, int quantity) {
        if(products.containsKey(product)){
            throw new IllegalArgumentException("The key has been found");
        }
        else{
            products.put(product,quantity);
        }
    }

    @Override
    public void removeProduct(String product) {
        if(!products.containsKey(product)){
            throw new IllegalArgumentException("The key has not been found");
        }
        else{
            products.remove(product);
        }
    }

    @Override
    public void updateProductQuantity(String product, int quantity) {
        if(!products.containsKey(product)){
            throw new IllegalArgumentException("The key has been found");
        }
        else{
            products.replace(product,quantity);
        }
    }

    @Override
    public List<String> getProducts() {
        return new ArrayList<>(products.keySet());
    }

    public HashMap<String,Integer> show_all(){
        return products;
    }
}
