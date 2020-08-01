//
// Created by Ali on ۳۱/۰۷/۲۰۲۰.
//

#include "DoubleMajorStudent.h"


using namespace std;

DoubleMajorStudent::DoubleMajorStudent(const string &studentId, string first, string last, double workHours,
                                       vector<std::string> passedCourses, std::map<std::string, double> currentSemesterCourses , std::string major2)
        : Student(studentId, move(first), move(last), workHours, move(passedCourses), move(currentSemesterCourses)) ,
          major2(move(major2)) {}

double DoubleMajorStudent::calculateSalary() const {
    return 6500 * getWorkHours();
}


