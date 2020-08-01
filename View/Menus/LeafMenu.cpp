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


    // Manager Menu -> People
    else if(name == "Add Professor"){
        string ID;
        cout << "Enter professor number: ";
        cin >> ID;
        string first;
        cout << "Enter First Name: ";
        cin >> first;
        string last;
        cout << "Enter Last Name: ";
        cin >> last;
        string title;
        cout << "Enter title: ";
        cin >> title;
        controller.addProfessor(ID, first, last , title);
    }

    else if(name == "Show Professors"){
        controller.showProfessors();
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
        controller.showStudents();
    }
    // End of Manager Menu -> People

    // Manager Menu -> Courses
    else if(name == "Add Course"){
        string courseName;
        cout << "Enter course name: ";
        cin >> courseName;
        string profLastName;
        cout << "Enter course professor's last name: ";
        cin >> profLastName;
        string semester;
        cout << "Enter semester: ";
        cin >> semester;
        int preCourseSize;
        cout << "Enter the number of course's preCourses: ";
        cin >> preCourseSize;
        string preCName;
        vector<string> preCourses;
        cout << "Enter course preCourses' name: " << endl;
        for (int i = 0; i < preCourseSize; ++i) {
            cout << i+1 << "." ;
            cin >> preCName;
            preCourses.push_back(preCName);
        }
        controller.addCourse(courseName,profLastName , semester , preCourses);
    }

    else if(name == "Show All Courses"){
        controller.showAllCourses();
    }

    else if(name == "Show Current Semester Courses"){
        controller.showThisSemesterCourses();
    }

    //End of Manager Menu -> Courses

    // Math Class Menu
    else if(name == "Read Members From File"){
        controller.readMembersFromFile();
    }

    else if(name == "Calculate Total Salary"){
        cout << setprecision(15) << "Total Salary : " << controller.calculateTotalSalary() << endl;
    }
    // End of Math Class Menu

    else{
        throw invalid_argument("This Menu has not been defined!!");
    }
}
