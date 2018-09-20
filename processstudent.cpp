#include "processstudent.h"
#include "ui_processstudent.h"
#include "studentlistwriter.h"
#include <QTextStream>
#include <QCloseEvent>

const QString ProcessStudent::studentDoesNotExist("The student does not exist");

ProcessStudent::ProcessStudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProcessStudent)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    setWindowTitle("Process Student");
    IsGetStudentRunning = false;
    studentList = StudentList::students();

    ui->studentNumberLineEdit->setInputMask("9999");
    disableButtons();

    connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(addStudentAndModules()));
    connect(&process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(doneAddingStudentAndModules()));
    connect(ui->addModuleButton, SIGNAL(clicked(bool)), this, SLOT(addToStudentList()));
    connect(ui->averageButton, SIGNAL(clicked(bool)), this, SLOT(studentAverage()));
    connect(ui->displayButton, SIGNAL(clicked(bool)), this, SLOT(displayStudentDetails()));
    connect(ui->graduateButton, SIGNAL(clicked(bool)), this, SLOT(doesStudentGraduate()));
    connect(ui->studentNumberLineEdit, SIGNAL(textChanged(QString)), this, SLOT(setButtonUsability()));
}

ProcessStudent::~ProcessStudent()
{
    delete ui;
}

void ProcessStudent::addToStudentList()
{
    if(!IsGetStudentRunning)
    {
        process.start("GetStudent");
        IsGetStudentRunning = true;
    }
    ui->addModuleButton->setEnabled(false);
}

void ProcessStudent::doneAddingStudentAndModules()
{
    IsGetStudentRunning = false;
    ui->addModuleButton->setEnabled(true);
}

void ProcessStudent::addStudentAndModules()
{
    static QRegExp studentNumRegExp(R"---(\b[0-9]{4}\b)---");
    static QRegExp moduleCodeRegExp(R"---(\b[A-Z]{3}[1-3]\d\d[0-9A-Z]\b)---");
    static QRegExp markRegExp(R"---(\b\d\d0?\b)---");

    //capture data from readyReadStandardOutput
    QByteArray bytes = process.readAllStandardOutput();
    QString studentData(bytes);
    int pos = studentNumRegExp.indexIn(studentData);
    QString studentNum = studentNumRegExp.capturedTexts().at(0);
    pos = moduleCodeRegExp.indexIn(studentData);
    QString moduleCode = moduleCodeRegExp.capturedTexts().at(0);
    pos = markRegExp.indexIn(studentData);
    int mark = markRegExp.capturedTexts().at(0).toInt();

    int indexOfStudent = studentList->exists(studentNum);
    if(indexOfStudent != -1)
    {
        Student *student = studentList->getStudent(indexOfStudent);
        student->addModule(moduleCode, mark);
    }
    else
    {
        Student* newStudent = new Student();
        newStudent->setNumber(studentNum);
        newStudent->addModule(moduleCode, mark);
        studentList->addStudent(newStudent);
    }
}

void ProcessStudent::studentAverage()
{
    QString result;
    QTextStream stream(&result);
    ui->textEdit->clear();
    QString studentNumber = ui->studentNumberLineEdit->text();
    int pos = studentList->exists(studentNumber);
    if(pos == -1)
    {
        result = studentDoesNotExist;
    }
    else
    {
        Student* student = studentList->getStudent(pos);
        stream << "Displaying student" << endl
               << "Number: " << student->getNumber() << endl
               << "Average: " << student->average() << endl;
    }
    ui->textEdit->setText(result);
}

void ProcessStudent::displayStudentDetails()
{
    QString result;
    QTextStream stream(&result);
    ui->textEdit->clear();
    QString studentNumber = ui->studentNumberLineEdit->text();
    int pos = studentList->exists(studentNumber);
    if(pos == -1)
    {
        result = studentDoesNotExist;
    }
    else
    {
        Student* student = studentList->getStudent(pos);
        stream << "Displaying student" << endl
               << "Number: " << student->getNumber() << endl;
        QMap<QString, int> modules = student->getModules();
        foreach (QString key, modules.keys())
        {
            stream << "Module: " << key << " Mark: " << modules.value(key) << endl;
        }
    }
    ui->textEdit->setText(result);
}

void ProcessStudent::doesStudentGraduate()
{
    QString result;
    QTextStream stream(&result);
    ui->textEdit->clear();
    QString studentNumber = ui->studentNumberLineEdit->text();
    int pos = studentList->exists(studentNumber);
    if(pos == -1)
    {
        result = studentDoesNotExist;
    }
    else
    {
        Student* student = studentList->getStudent(pos);
        stream << "Displaying student" << endl
               << "Number: " << student->getNumber() << endl
               << "Graduate: " << ((student->graduate()) ? "Yes" : "No") << endl;
    }
    ui->textEdit->setText(result);
}

void ProcessStudent::setButtonUsability()
{
    if(ui->studentNumberLineEdit->text().length() == 4)
    {
        enableButtons();
    }
    else
    {
        disableButtons();
    }
    ui->textEdit->clear();
}

void ProcessStudent::disableButtons()
{
    ui->averageButton->setEnabled(false);
    ui->graduateButton->setEnabled(false);
    ui->displayButton->setEnabled(false);
}

void ProcessStudent::enableButtons()
{
    ui->averageButton->setEnabled(true);
    ui->graduateButton->setEnabled(true);
    ui->displayButton->setEnabled(true);
}

void ProcessStudent::serializeListToXML()
{
    StudentListWriter writer("studentList.xml");
    writer << studentList;
}

void ProcessStudent::closeEvent(QCloseEvent *event)
{
    serializeListToXML();
    event->accept();
}
