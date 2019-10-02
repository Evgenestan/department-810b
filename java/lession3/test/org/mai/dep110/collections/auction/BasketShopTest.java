package org.mai.dep110.collections.auction;


import static org.junit.Assert.*;
import static org.hamcrest.CoreMatchers.*;
import org.junit.*;
import org.mai.dep110.collections.basket.BasketImpl;

import java.util.ArrayList;

public class BasketShopTest {

    BasketImpl basketShop;
    String product4thEdition = "product4";
    String product3rdEdition = "product3";

    Integer cp4ed = 10;
    Integer cp3ed = 20;

    @BeforeClass
    public static void setupClass(){

    }

    @Before
    public  void setup(){
        basketShop = new BasketImpl();
        basketShop.addProduct(product3rdEdition,cp3ed);
        basketShop.addProduct(product4thEdition,cp3ed);
    }

    @After
    public void clear(){
        basketShop = null;
    }

    @AfterClass
    public static void clearAll(){}



    //@Test(expected = ProductNotFoundException.class)
    @Test
    public  void placeProduct() throws Exception {
        var products = basketShop.getProducts();

        assertThat(products,hasItems(product3rdEdition,product4thEdition));

        String product5thEdition = "product5";
        assertThat(products, not(hasItem(product5thEdition)));

        basketShop.removeProduct(product3rdEdition);
        assertThat(basketShop.getProducts(),not(hasItem(product3rdEdition)));
        String newQm = "new quantity";
        Integer quantity = 4;
        System.out.println(basketShop.show_all().get(product4thEdition));
        basketShop.updateProductQuantity(product4thEdition,quantity);
        System.out.println(basketShop.show_all().get(product4thEdition));
        assertEquals(basketShop.show_all().get(product4thEdition),quantity);








    }
}
