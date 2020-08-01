#include "LeafMenu.h"
#include <iomanip>
#include <algorithm>
using namespace std;

LeafMenu::LeafMenu(std::string name, Menu* parent)
    : Menu{move(name), parent} {}

void LeafMenu:: showSubMenus() const {}

void LeafMenu::run() {
    setCurrentMenu(parent);

    // Student Menu
    if(name == "Show This Semester Courses"){
        controller.showThisSemesterCourses();
    }

    else if(name == "Take Course"){
        string stuID;
        string courseName;
        cout << "Enter Student's ID:  ";
        cin >> stuID;
        cout << "Enter Course's Name:  ";
        cin >> courseName;
        controller.takeCourse(stuID , courseName);
    }

    else if(name == "Drop Course"){
        string stuID;
        string courseName;
        cout << "Enter Student's ID:  ";
        cin >> stuID;
        cout << "Enter Course's Name:  ";
        cin >> courseName;
        controller.dropCourse(stuID , courseName);
    }

    else if(name == "Show Student Courses In Current Semester"){
        cout << "Enter Student ID:  ";
        string stuID;
        cin >> stuID;
        try{
            Student stu = controller.findStudent(stuID);
            controller.showStudentCoursesInCurrentSemester(stu);
        }
        catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }

    else if(name == "Calculate Student Salary"){
        string stuID;
        cout << "Enter Student's ID:  ";
        cin >> stuID;
        Student stu = controller.findStudent(stuID);
        cout << stu.getFirstName() << " " << stu.getLastName() << "'s salary : " << stu.calculateSalary() << endl;
    }
    // End of Student Menu

    // Professor Menu
    else if(name == "Show Professor Courses In Current Semester"){

    }

    else if(name == "Submit Grade"){

    }

    else if(name == "Calculate Professor Salary"){
        string profID;
        cout << "Enter Professor's ID:  ";
        cin >> profID;
        Professor prof = controller.findProfessor(profID);
        cout << setprecision(10) << prof.getFirstName() << " " << prof.getLastName() << "'s salary : " << prof.calculateSalary() << endl;
    }
    // End of Professor Menu


    else if(name == "Add Professor"){

    }

    else if(name == "Show Professors"){

    }

    else if(name == "Add Student"){
        string ID;
        cout << "Enter student number: ";
        cin >> ID;
        string first;
        cout << "Enter First Name: ";
        cin >> first;
        string last;
        cout << "Enter Last Name: ";
        cin >> last;
        controller.addStudent(ID, first, last);
    }

    else if(name == "Show Students"){

    }

    else if(name == "Add Course"){

    }

    else if(name == "Show All Courses"){

    }

    // Math Class Menu
    else if(name == "Read Members From File"){
        controller.readMembersFromFile();
    }

    else if(name == "Calculate Total Salary"){
        cout << setprecision(15) << "Total Salary : " << controller.calculateTotalSalary() << endl;
    }

    else{
        throw invalid_argument("This Menu has not been defined!!");
    }
}
