#ifndef STUDENTLIST_H
#define STUDENTLIST_H
#include "student.h"
#include <QString>

class StudentList : public QList<Student*>
{
public:
    static StudentList* students();
    void addStudent(Student* student);
    int exists(QString studentNum);
    Student* getStudent(int index);
    int numberOfStudents();
private:
    StudentList();
    static StudentList* instance;
};

#endif // STUDENTLIST_H
