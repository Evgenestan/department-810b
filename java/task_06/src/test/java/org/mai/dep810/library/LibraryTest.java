package org.mai.dep810.library;

import org.junit.After;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

import java.sql.*;

public class LibraryTest
{

    private Book book_1;
    private Book book_2;
    private Student student_1;
    private Student student_2;
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

    }

    @Before
    public void setUp() throws Exception
    {
        book_1 = new Book(0,"Война и мир");
        book_2 = new Book(1,"Дубровский");

        student_1 = new Student(0,"Иван");
        student_2 = new Student(1,"Петр");

    }

    @After
    public void tearDown() throws Exception
    {

    }

    @Test
    public void addNewBook() throws Exception
    {
        library.addNewBook(book_1);
        library.addNewBook(book_2);

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
        library.addAbonent(student_2);

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

        assertEquals(student_id,-1);
    }

    @Test(expected =  java.lang.AssertionError.class)
    public void findAvailableBooks() throws Exception
    {
        var booksOrigin = new Book[2];
        booksOrigin[0] = book_1;
        booksOrigin[1] = book_2;
        var books = library.findAvailableBooks().toArray();

        assertArrayEquals(books,booksOrigin);
    }

    @Test
    public void getAllStudents() throws Exception
    {
        var studentsOrigin = new Student[2];
        studentsOrigin [0] = student_1;
        studentsOrigin [1] = student_2;
        var students = library.getAllStudents().toArray();

        assertArrayEquals(students,studentsOrigin);

        //assertArrayEquals(students,studentsOrigin);
    }

}