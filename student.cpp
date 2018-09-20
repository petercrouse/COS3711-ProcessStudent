#include "student.h"
#include <QRegExp>

QRegExp Student::studentFirstYear(R"--(^\w\w\w1\w+)--");
QRegExp Student::studentThirdYear(R"--(^\w\w\w3\w+)--");

Student::Student()
{

}

Student::Student(QString studentNum) : studentNumber(studentNum)
{

}

QString Student::getNumber() const
{
    return studentNumber;
}

void Student::setNumber(QString number)
{
    studentNumber = number;
}

QMap<QString, int> Student::getModules() const
{
    return moduleMarks;
}

void Student::addModule(QString module, int mark)
{
    moduleMarks.insert(module, mark);
}

double Student::average() const
{
    int totalMarks = 0;
    foreach (int mark, moduleMarks.values())
    {
        totalMarks += mark;
    }

    return totalMarks / moduleMarks.size();
}

bool Student::graduate() const
{
    int firstYearModule = 0;
    int thirdyearModule = 0;
    int modulespassed = 0;
    foreach (QString module, moduleMarks.keys())
    {
        if(studentFirstYear.exactMatch(module) && (moduleMarks.value(module) >= 50))
        {
            firstYearModule++;
        }
        else if(studentThirdYear.exactMatch(module) && (moduleMarks.value(module) >= 50))
        {
            thirdyearModule++;
        }

        if (moduleMarks.value(module) >= 50)
        {
            modulespassed++;
        }
    }

    return ((modulespassed >= 5) && (firstYearModule <= 2) && (thirdyearModule >= 1));
}
