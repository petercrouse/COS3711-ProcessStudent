#ifndef STUDENT_H
#define STUDENT_H
#include <QString>
#include <QMap>

class Student
{
public:
    Student();
    Student(QString studentNum);
    QString getNumber() const;
    void setNumber(QString number);
    QMap<QString,int> getModules() const;
    void addModule(QString module, int mark);
    double average() const;
    bool graduate() const;
private:
    QString studentNumber;
    QMap<QString,int> moduleMarks;
    static QRegExp studentFirstYear;
    static QRegExp studentThirdYear;
};

#endif // STUDENT_H
