#ifndef STUDENTLISTWRITER_H
#define STUDENTLISTWRITER_H
#include "studentlist.h"

class StudentListWriter
{
public:
    StudentListWriter(QString fileName);
    StudentListWriter& operator<< (StudentList *studentList);
private:
    QString _fileName;
};

#endif // STUDENTLISTWRITER_H
