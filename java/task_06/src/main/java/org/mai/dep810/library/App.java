package org.mai.dep810.library;

import org.apache.log4j.Logger;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

public class App
{
    private static Logger log = Logger.getLogger(org.mai.dep810.basket.App.class);

    public static void main(String [] args) throws SQLException
    {
        var library = new LibraryImpl("jdbc:h2:mem:library", "", "");

        Connection connection = DriverManager.getConnection("jdbc:h2:mem:library");
        //Connection connection = DriverManager.getConnection("jdbc:derby:memory:basket;create=true");
        try(Statement stmt = connection.createStatement();)
        {
            String tableSql = "create table abonents(student_id int, student_name varchar(255))";
            String tableBooksSql = "create table books(book_id int, book_title varchar(255), student_id int)";
            stmt.execute(tableSql);
            stmt.execute(tableBooksSql);
        }

        var students = new ArrayList<Student>();
        var books = new ArrayList<Book>();

        students.add(new Student(0,"St1"));
        students.add(new Student(1, "St2"));

        books.add(new Book(0,"B1"));
        books.add(new Book(1,"B2"));

        for (var book : books)
        {
            library.addNewBook(book);
        }
        for (var student : students)
        {
            library.addAbonent(student);
        }

        for (var book : library.findAvailableBooks())
        {
            System.out.println(book);
        }

        for(var student : library.getAllStudents())
        {
            System.out.println(student);
        }

    }
}
