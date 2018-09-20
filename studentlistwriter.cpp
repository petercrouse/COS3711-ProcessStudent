#include "studentlistwriter.h"
#include <QDomDocument>
#include <QDomElement>
#include <QDomText>
#include <QFile>
#include <QTextStream>
#include <QDebug>

StudentListWriter::StudentListWriter(QString fileName): _fileName(fileName)
{

}

StudentListWriter& StudentListWriter::operator << (StudentList *studentList)
{
    QFile file(_fileName);
    QTextStream stream(&file);

    if(file.open(QIODevice::WriteOnly))
    {
        QDomDocument doc;
        QDomElement rootElement = doc.createElement("StudentList");
        doc.appendChild(rootElement);

        for(int i = 0; i < studentList->numberOfStudents(); i++)
        {
            QDomElement studentElement = doc.createElement("student");
            rootElement.appendChild(studentElement);

            QDomElement studentNumberElement = doc.createElement("number");
            studentElement.appendChild(studentNumberElement);
            QDomText studentNumberText = doc.createTextNode(studentList->at(i)->getNumber());
            studentNumberElement.appendChild(studentNumberText);

            QMap<QString, int> modules = studentList->at(i)->getModules();
            QDomElement modulesElement = doc.createElement("modules");
            studentElement.appendChild(modulesElement);
            foreach (QString key, modules.keys())
            {
                QDomElement moduleElement = doc.createElement("module");
                modulesElement.appendChild(moduleElement);

                QDomElement codeElement = doc.createElement("code");
                moduleElement.appendChild(codeElement);
                QDomText codeText = doc.createTextNode(key);
                codeElement.appendChild(codeText);

                QDomElement markElemenet = doc.createElement("mark");
                moduleElement.appendChild(markElemenet);
                QDomText markText = doc.createTextNode(QString("%1").arg(modules.value(key)));
                markElemenet.appendChild(markText);
            }
        }
        stream << doc.toString();
    }
    else
    {
         qDebug() << "Error opening file";
    }

    file.close();
    return *this;
}
