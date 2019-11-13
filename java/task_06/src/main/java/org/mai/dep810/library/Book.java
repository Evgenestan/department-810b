package org.mai.dep810.library;

/**
 * Created by Asus on 10/21/2018.
 */
public class Book {
    private int id;
    private String title;

    public Book(int id, String title) {
        this.id = id;
        this.title = title;
    }

    public Book() {}

    public int getId() {
        return id;
    }

    public String getTitle() {
        return title;
    }

    @Override
    public String toString() {
        return "Book{" +
                "id=" + id +
                ", title='" + title + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object obj) {
        return id == ((Book) obj).id && title.equals (((Book) obj).title);
    }
}
