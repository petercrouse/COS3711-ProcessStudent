#ifndef PROCESSSTUDENT_H
#define PROCESSSTUDENT_H

#include <QDialog>
#include <QProcess>
#include <QDomNode>
#include <QDomElement>
#include <QDomDocument>
#include "studentlist.h"

namespace Ui {
class ProcessStudent;
}

class ProcessStudent : public QDialog
{
    Q_OBJECT
public:
    explicit ProcessStudent(QWidget *parent = 0);
    ~ProcessStudent();
public slots:
    void addStudentAndModules();
    void doneAddingStudentAndModules();
    void addToStudentList();
    void studentAverage();
    void displayStudentDetails();
    void doesStudentGraduate();
    void setButtonUsability();
    void closeEvent(QCloseEvent *event);
private:
    Ui::ProcessStudent *ui;
    QProcess process;
    bool IsGetStudentRunning;
    StudentList* studentList;
    static const QString studentDoesNotExist;
    void disableButtons();
    void enableButtons();
    void serializeListToXML();
};

#endif // PROCESSSTUDENT_H
