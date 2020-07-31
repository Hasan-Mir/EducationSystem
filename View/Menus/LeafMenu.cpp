#include "LeafMenu.h"
#include <algorithm>
using namespace std;

LeafMenu::LeafMenu(std::string name, Menu* parent)
    : Menu{move(name), parent} {}

void LeafMenu:: showSubMenus() const {}

void LeafMenu::run() {
    setCurrentMenu(parent);

    if(name == "Show This Semester Courses"){
        if(controller.currentSemesterCourses.size() == 0){
            cout << "There is nothing to show !" << endl;
        }
        else{
            for(const auto & course : controller.currentSemesterCourses){
                cout << course.courseName << "  |  ";
            }
            cout << endl;
        }
    }

    else if(name == "Take Course"){

    }

    else if(name == "Drop Course"){

    }

    else if(name == "Show Student Courses In Current Semester"){
        cout << "Enter Student ID:  ";
        string stuID;
        cin >> stuID;
        try{
            Student stu = controller.findStudent(stuID);
            cout << "Student Name: " << stu.getFirstName() << " " << stu.getLastName() << endl;
            if(stu.currentSemesterCourses.size() == 0){
                cout << "There is nothing to show !" << endl;
            }
            else{
                for(const auto& course : stu.currentSemesterCourses){
                    cout << course.first << "\t" << course.second << endl;
                }
                cout << endl;
            }
        }
        catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }

    else if(name == "Calculate Student Salary"){

    }

    else if(name == "Show Professor Courses In Current Semester"){

    }

    else if(name == "Submit Grade"){

    }

    else if(name == "Calculate Professor Salary"){

    }

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

    else{
        throw invalid_argument("This Menu hase not been defined!!");
    }
}
