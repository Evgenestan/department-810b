package org.mai.dep810;

import org.junit.*;
import org.mai.dep810.basket.BasketShop;
import org.mai.dep810.basket.ProductNotFoundException;

import static org.junit.Assert.*;
import static org.hamcrest.CoreMatchers.*;

public class BasketShopTest
{
    BasketShop basketShop1;
    BasketShop basketShop2;
    String product4thEdition = "Prod1";
    String product3rdEdition = "Prod2";
    String javaCoreBook  = "Prod3";
    Integer illegalCountProducts = -1;
    Integer countProduct4thEdition = 10;
    Integer countProduct3thEdition = 20;

    @BeforeClass
    public static void setupClass() { }

    @Before
    public void setup()
    {
        basketShop1 = new BasketShop();
        basketShop1.addProduct(product3rdEdition,countProduct3thEdition);
    }

    @After
    public void clear() {
        basketShop1 = null;
    }



    @Test
    public void placeProduct()
    {
        basketShop1.addProduct(product4thEdition,countProduct4thEdition);
        var products = basketShop1.getProducts();
        assertThat(products,hasItem(product4thEdition));
        assertEquals(basketShop1.getProductQuantity(product4thEdition),countProduct4thEdition);
    }


    @Test
    public void takeOutProduct()
    {
        basketShop1.removeProduct(product3rdEdition);
        var products = basketShop1.getProducts();
        assertThat(products,not(hasItem(product3rdEdition)));
    }



    @Test
    public void editQuantity()
    {
        basketShop1.updateProductQuantity(product3rdEdition,countProduct4thEdition);
        assertEquals(basketShop1.getProductQuantity(product3rdEdition),countProduct4thEdition);
    }




    @Test
    public void getQuantitySuccessful()
    {
        var quantity = basketShop1.getProductQuantity(product3rdEdition);
        assertEquals(quantity,countProduct3thEdition);
    }


}
