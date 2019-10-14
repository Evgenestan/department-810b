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
    String product4thEdition = "Thinking Java 4th edition";
    String product3rdEdition = "Thinking Java 3rd edition";
    Integer countProduct4thEdition = 10;
    Integer countProduct3thEdition = 20;

    @BeforeClass
    public static void setupClass()
    {

    }

    @Before
    public void setup()
    {
        basketShop1 = new BasketShop();

        basketShop1.addProduct(product3rdEdition,countProduct3thEdition);
        basketShop1.addProduct(product4thEdition,countProduct4thEdition);
    }

    @After
    public void clear() {
        basketShop1 = null;
    }

    @AfterClass
    public static void releaseRecources()
    {

    }

    @Test(expected = ProductNotFoundException.class)
    public void placeProduct()
    {
        var products = basketShop1.getProducts();

        assertThat(products,hasItems(product3rdEdition,product4thEdition));

        String product5thEdition = "Thinking Java 5th edition";

        assertThat(products, not(hasItem(product5thEdition)));

        assertEquals(basketShop1.getProductQuantity(product3rdEdition),countProduct3thEdition);
    }
}
