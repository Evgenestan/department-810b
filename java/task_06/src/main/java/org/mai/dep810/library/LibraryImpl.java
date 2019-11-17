package org.mai.dep810.library;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class LibraryImpl implements Library
{

    private String jdbcUrl;
    private String user;
    private String password;



    public LibraryImpl(String jdbcUrl, String user, String password)
    {
        this.jdbcUrl = jdbcUrl;
        this.user = user;
        this.password = password;
    }


    public void delete_all() throws SQLException
        {
            try (Statement statement = getConnection().createStatement())
            {
                var delBooks = "truncate table books";
                var delAbonents = "truncate table abonents";

                statement.execute(delAbonents);
                statement.execute(delBooks);
            }
        }

    public Connection getConnection() throws SQLException {
        return DriverManager.getConnection(jdbcUrl, user, password);
    }

    @Override
    public void addNewBook(Book book)
    {
        String insertSql = "insert into books values( ?,?,-1)";

        try (Connection c = getConnection())
        {
            try(PreparedStatement stmt = getConnection().prepareStatement(insertSql))
            {
                stmt.setInt(1,book.getId());
                stmt.setString(2,book.getTitle());

                stmt.executeUpdate();
            }
            catch (SQLException e)
            {
                e.printStackTrace();
            }
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }



    }

    @Override
    public void addAbonent(Student student)
    {
        String insertSql = "insert into abonents values(?,?)";


            try(PreparedStatement stmt = getConnection().prepareStatement(insertSql))
            {
                stmt.setInt(1,student.getId());
                stmt.setString(2,student.getName());

                stmt.executeUpdate();
            }
            catch (SQLException e)
            {
                e.printStackTrace();
            }
        }



    @Override
    public void borrowBook(Book book, Student student)
    {
        String updateSql = "update books set student_id = ? where book_id = ?";
        try ( var stmt = getConnection().prepareStatement(updateSql);)
        {
            stmt.setInt(1, student.getId());
            stmt.setInt(2, book.getId());
            stmt.executeUpdate();
            //getConnection().commit();

        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
    }

    @Override
    public void returnBook(Book book, Student student)
    {
        String updateSql = "update books set student_id = -1 where student_id = ? and book_id = ?";
        //String updateSql = "update books set student_id = NULL where student_id = ? and book_id = ?";
        try (var stmt = getConnection().prepareStatement(updateSql))
        {

            stmt.setInt(1, book.getId());
            stmt.setInt(2, student.getId());
            stmt.executeUpdate();
            //getConnection().commit();
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
    }

    /*public Book getBook(Book book)
    {
        Book resultBook = new Book();
        String selectSql = "select book_id, book_title, student_id from books where book_id = ?" ;
        try (var stmt = getConnection().prepareStatement(selectSql))
        {
            stmt.setInt(1,book.getId());

            try(ResultSet rs = stmt.executeQuery())
            {
                rs.next();

                int book_id = 0;
                int student_id;
                String book_title;
                book_id = rs.getInt("book_id");
                book_title = rs.getString("book_title");
                student_id = rs.getInt("student_id");
                resultBook = new Book(book_id,book_title);
            }


        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }

        return resultBook;
    }*/


    @Override
    public List<Book> findAvailableBooks()
    {
        List<Book> result = new ArrayList<Book>();
        String sql = "select book_id,book_title from books where student_id = -1";
        try (Statement stmt = getConnection().createStatement();
             ResultSet rs = stmt.executeQuery(sql);)
        {
            while (rs.next())
            {
                int book_id = rs.getInt("book_id");
                String book = rs.getString("book_title");
                result.add(new Book(book_id,book));
            }
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }

        return result;
    }

    @Override
    public List<Student> getAllStudents()
    {
        List<Student> result = new ArrayList<Student>();
        String sql = "select student_id,student_name from abonents";
        try (Statement stmt = getConnection().createStatement();
             ResultSet rs = stmt.executeQuery(sql);)
        {
            while (rs.next())
            {
                int student_id = rs.getInt("student_id");
                String student_name = rs.getString("student_name");

                result.add(new Student(student_id,student_name));
            }
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }

        return result;
    }
}
