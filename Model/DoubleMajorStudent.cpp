//
// Created by Ali on ۳۱/۰۷/۲۰۲۰.
//

#include "DoubleMajorStudent.h"


using namespace std;

DoubleMajorStudent::DoubleMajorStudent(const string &studentId, string first, string last, double workHours,
        vector<std::string> major1passedCourses, std::map<std::string, double> major2currentSemesterCourses , std::string major2)
        : Student(studentId, move(first), move(last), workHours,move(major1passedCourses),move(major2currentSemesterCourses)) ,
          major2(move(major2)) {}

double DoubleMajorStudent::calculateSalary() const {
    return 6500 * getWorkHours();
}


