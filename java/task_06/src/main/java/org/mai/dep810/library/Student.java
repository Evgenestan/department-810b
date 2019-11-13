package org.mai.dep810.library;

/**
 * Created by Asus on 10/21/2018.
 */
public class Student{
    private int id;
    private String name;

    public Student(int id, String name) {
        this.id = id;
        this.name = name;
    }

    public Student()
    {

    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return "Student{" +
                "id=" + id +
                ", name='" + name + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object stud) {
        return name.equals(((Student)stud).name) && id == ((Student)stud).id;
    }



}

