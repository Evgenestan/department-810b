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
    String product4thEdition = "Java 4th edition";
    String product3rdEdition = "Java 3rd edition";
    String javaCoreBook  = "java";
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

    @AfterClass
    public static void releaseRecources() { }

    @Test
    public void placeProductSuccessful()
    {
        basketShop1.addProduct(product4thEdition,countProduct4thEdition);
        var products = basketShop1.getProducts();
        assertThat(products,hasItem(product4thEdition));
        assertEquals(basketShop1.getProductQuantity(product4thEdition),countProduct4thEdition);
    }

    @Test(expected = IllegalArgumentException.class)
    public void placeProductUnSuccessful()
    {
        basketShop1.addProduct(product4thEdition,illegalCountProducts);
        var products = basketShop1.getProducts();
        assertThat(products,hasItem(product4thEdition));
        assertEquals(basketShop1.getProductQuantity(product4thEdition),countProduct4thEdition);
    }

    @Test
    public void takeOutProductSuccessful()
    {
        basketShop1.removeProduct(product3rdEdition);
        var products = basketShop1.getProducts();
        assertThat(products,not(hasItem(product3rdEdition)));
    }

    @Test(expected = ProductNotFoundException.class)
    public void takeOutProductUnSuccessful()
    {
        basketShop1.removeProduct(javaCoreBook);
        var products = basketShop1.getProducts();
        assertThat(products,not(hasItem(javaCoreBook)));
    }

    @Test
    public void editQuantitySuccessful()
    {
        basketShop1.updateProductQuantity(product3rdEdition,countProduct4thEdition);
        assertEquals(basketShop1.getProductQuantity(product3rdEdition),countProduct4thEdition);
    }

    @Test(expected = ProductNotFoundException.class)
    public void editQuantityUnSuccessful()
    {
        basketShop1.updateProductQuantity(product4thEdition,countProduct4thEdition);
        assertEquals(basketShop1.getProductQuantity(product4thEdition),countProduct4thEdition);
    }

    @Test (expected =  IllegalArgumentException.class)
    public void editQuantityUnSuccessfulSetNegative()
    {
        basketShop1.updateProductQuantity(product3rdEdition,illegalCountProducts);
        assertEquals(basketShop1.getProductQuantity(product3rdEdition),illegalCountProducts);
    }

    @Test
    public void getQuantitySuccessful()
    {
        var quantity = basketShop1.getProductQuantity(product3rdEdition);
        assertEquals(quantity,countProduct3thEdition);
    }

    @Test(expected = ProductNotFoundException.class)
    public void getQuantityUnSuccessful()
    {
        var quantity = basketShop1.getProductQuantity(product4thEdition);
        assertEquals(quantity,countProduct4thEdition);
    }
}
