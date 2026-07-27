#include <iostream>
#include <string>

using namespace std;

class Student
{
private:
    string name;
    string age;
    string studentID;
    string gradesAvg;
    string grade;

public:
    // Getters
    string getName()
    {
        return name;
    }

    string getAge()
    {
        return age;
    }

    string getID()
    {
        return studentID;
    }

    string getAvg()
    {
        return gradesAvg;
    }

    string getGrade()
    {
        return grade;
    }

    // Print student information
    void printInfo()
    {
        cout << "====== Student Info ======\n";
        cout << "Name       : " << name << endl;
        cout << "Age        : " << age << endl;
        cout << "Student ID : " << studentID << endl;
        cout << "Average    : " << gradesAvg << endl;
        cout << "Grade      : " << grade << endl;
        cout << "==========================\n";
    }

    // Setters
    void setName(string studentName)
    {
        name = studentName;
    }

    void setAge(string studentAge)
    {
        age = studentAge;
    }

    void setStudentID(string studentId)
    {
        studentID = studentId;
    }

    void setAverage(string studentAvg)
    {
        gradesAvg = studentAvg;
    }

    void setGrade(string studentGrade)
    {
        grade = studentGrade;
    }
};

int main()
{
    Student student1;

    cout << "Let's set student data\n\n";

    student1.setName("Mohamed");
    student1.setAge("21");
    student1.setStudentID("248339");
    student1.setAverage("91%");
    student1.setGrade("A-");

    student1.printInfo();

    return 0;
}