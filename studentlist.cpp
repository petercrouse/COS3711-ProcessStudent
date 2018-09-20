#include "studentlist.h"

StudentList* StudentList::instance = NULL;

StudentList::StudentList()
{

}

StudentList* StudentList::students()
{
    if(instance == NULL)
    {
        instance = new StudentList();
    }
    return instance;
}

void StudentList::addStudent(Student *student)
{
    instance->append(student);
}

int StudentList::exists(QString studentNum)
{
    for(int i = 0; i < instance->size(); i++)
    {
        if(instance->at(i)->getNumber() == studentNum)
        {
            return i;
        }
    }
    return -1;
}

Student* StudentList::getStudent(int index)
{
    return instance->at(index);
}

int StudentList::numberOfStudents()
{
    return instance->size();
}
