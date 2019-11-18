package org.mai.dep810.library;

import org.junit.After;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;
import static org.hamcrest.CoreMatchers.*;

import java.sql.*;

public class LibraryTest
{

    private static Book book_1;
    private static Book book_2;
    private static Book book_3;
    private static Student student_1;
    private static Student student_2;
    public static LibraryImpl library;
    public static  Connection connection;

    @BeforeClass
    public static void setupClass() throws SQLException
    {


        library = new LibraryImpl("jdbc:h2:mem:library", "", "");

        connection = library.getConnection();
        //Connection connection = DriverManager.getConnection("jdbc:derby:memory:basket;create=true");
        try(Statement stmt = connection.createStatement();)
        {
            String tableSql = "create table abonents(student_id int, student_name varchar(255))";
            String tableBooksSql = "create table books(book_id int, book_title varchar(255), student_id int)";
            stmt.execute(tableSql);
            stmt.execute(tableBooksSql);
        }

        book_1 = new Book(0,"Book1");
        book_2 = new Book(1,"Book2");
        book_3 = new Book(3,"Book3");

        student_1 = new Student(0,"Student1");
        student_2 = new Student(1,"Student2");

    }

    @Before
    public void setUp() throws Exception
    {
        library.delete_all();

    }

    /*@After
    public void tearDown() throws Exception
    {

    }*/

    @Test
    public void addNewBook() throws Exception
    {
        library.addNewBook(book_1);
        //library.addNewBook(book_2);

         Book book = new Book();

        String selectSql = "select book_id,book_title,student_id from books where book_id = ?";
        try (PreparedStatement stmt = connection.prepareStatement(selectSql))
        {
            stmt.setInt(1,book_1.getId());
            try(ResultSet rs = stmt.executeQuery())
            {
                rs.next();
                int book_id = rs.getInt("book_id");
                String book_title = rs.getString("book_title");
                int student_id = rs.getInt("student_id");

                book = new Book(book_id,book_title);
            }
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }

        assertEquals(book,book_1);

    }

    @Test
    public void addAbonent() throws Exception
    {
        library.addAbonent(student_1);
        //library.addAbonent(student_2);

        Student student = new Student();

        String selectSql = "select student_id,student_name from abonents where student_id = ?";
        try (PreparedStatement stmt = connection.prepareStatement(selectSql))
        {
            stmt.setInt(1,student_1.getId());
            try(ResultSet rs = stmt.executeQuery())
            {
                rs.next();
                int student_id = rs.getInt("student_id");
                String student_name = rs.getString("student_name");

                student = new Student(student_id,student_name);
            }
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }

        assertEquals(student,student_1);

    }

    @Test
    public void borrowBook() throws Exception
    {
        library.borrowBook(book_1,student_1);

        int student_id = 0;

        String selectSql = "select student_id from books where book_id = ?";
        try (PreparedStatement stmt = connection.prepareStatement(selectSql))
        {
            stmt.setInt(1,book_1.getId());
            try(ResultSet rs = stmt.executeQuery())
            {
                rs.next();
                student_id = rs.getInt("student_id");
            }
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }


        assertEquals(student_id,student_1.getId());
    }

    @Test//(expected =  java.lang.AssertionError.class)
    public void returnBook() throws Exception
    {

        library.addNewBook(book_1);
        library.addNewBook(book_2);
        library.addAbonent(student_1);
        library.addAbonent(student_2);


        library.returnBook(book_1,student_1);
        int student_id = 0;

        String selectSql = "select student_id from books where book_id = ? ";
        try (PreparedStatement stmt = connection.prepareStatement(selectSql))
        {
            stmt.setInt(1,book_1.getId());
            try (ResultSet rs = stmt.executeQuery())
            {
                rs.next();
                student_id = rs.getInt("student_id");
            }
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }

        //System.out.println("Id:");
        //System.out.println(student_id);
        assertEquals(student_id,-1);
    }

    @Test//(expected =  java.lang.AssertionError.class)
    public void findAvailableBooks() throws Exception
    {
        var booksOrigin = new Book[2];
        library.addNewBook(book_1);
        library.addNewBook(book_2);
        library.addNewBook(book_3);
        library.addAbonent(student_1);
        library.borrowBook(book_1,student_1);
        //booksOrigin[0] = book_1;
        booksOrigin[0] = book_2;
        booksOrigin[1] = book_3;
        var books = library.findAvailableBooks();

        //System.out.println(books.length);
        //System.out.println(booksOrigin.length);


//        assertArrayEquals(books,booksOrigin);
        assertThat(books, hasItems(book_2, book_3));
        assertThat(books, not(hasItems(book_1)));
    }

    @Test//(expected =  java.lang.AssertionError.class)
    public void getAllStudents() throws Exception
    {
        library.addAbonent(student_1);
        library.addAbonent(student_2);

        var studentsOrigin = new Student[2];
        studentsOrigin [0] = student_1;
        studentsOrigin [1] = student_2;
        var students = library.getAllStudents().toArray();

        assertArrayEquals(students,studentsOrigin);

        //assertArrayEquals(students,studentsOrigin);
    }

}