#include "Controller.h"
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>


using namespace std;

Controller::Controller(std::string currentSemester)
        : currentSemester{move(currentSemester)} {}


void Controller::load() {
    ifstream inputStu("students.txt");
    int studentSize;
    inputStu >> studentSize;
    Student stu;
    for (size_t i{0}; i < studentSize; ++i) {
        inputStu >> stu;
        students.push_back(stu);
    }
    inputStu.close();

    ifstream inputProf("professors.txt");
    int profSize;
    inputProf >> profSize;
    Professor prof;
    for (size_t i{0}; i < profSize; ++i) {
        inputProf >> prof;
        professors.push_back(prof);
    }
    inputProf.close();

    ifstream inputCourse("courses.txt");
    int courseSize;
    inputCourse >> courseSize;
    Course crs;
    for (size_t i{0}; i < courseSize; ++i) {
        inputCourse >> crs;
        courses.push_back(crs);
        if (crs.semester == currentSemester) {
            currentSemesterCourses.push_back(crs);
        }
    }
    inputCourse.close();
}

void Controller::save() const {
    ofstream outputStu("students.txt", ios::out);
    outputStu << students.size() << endl;
    for (auto const &stu : students) {
        outputStu << stu << endl;
    }
    outputStu.close();

    ofstream outputProf("professors.txt");
    outputProf << professors.size() << endl;
    for (const auto &prof : professors) {
        outputProf << prof << endl;
    }
    outputProf.close();

    ofstream outputCourse("courses.txt");
    outputCourse << courses.size() << endl;
    for (auto const &crs : courses) {
        outputCourse << crs << endl;
    }
    outputCourse.close();
}

void Controller::addStudent(std::string ID, std::string first, std::string last) {
    if (!inStudents(ID)) {
        Student stu{move(ID), move(first), move(last), 0,
                    vector<string>{}, map<string, double>{}};
        students.push_back(stu);
    }
}

void Controller::addProfessor(std::string ID, std::string first,
                              std::string last, std::string title) {
    if (!inProfessors(ID)) {
        Professor prof{move(ID), move(first), move(last), 0, move(title)};
        professors.push_back(prof);
    }
}

void Controller::addCourse(std::string courseName, std::string profLast, std::string semester,
                           std::vector<std::string> pre) {
    if (!inCourses(courseName) && inProfessorsByLastName(profLast)) {
        Course crs{move(courseName), move(profLast), move(semester), move(pre)};
        courses.push_back(crs);
        if (crs.semester == currentSemester) {
            currentSemesterCourses.push_back(crs);
        }
    }

}

bool Controller::inStudents(const std::string &ID) const {
    for (const auto &stu : students) {
        if (stu.studentId == ID) {
            return true;
        }
    }
    return false;
}

bool Controller::inProfessors(const std::string &ID) const {
    for (const auto &prof : professors) {
        if (prof.profId == ID) {
            return true;
        }
    }
    return false;
}

bool Controller::inCourses(const std::string &courseName) const {
    for (const auto &crs : courses) {
        if (crs.courseName == courseName) {
            return true;
        }
    }
    return false;
}

bool Controller::inProfessorsByLastName(const std::string &last) const {
    for (const auto &prof : professors) {
        if (prof.getLastName() == last) {
            return true;
        }
    }
    return false;
}

Student &Controller::findStudent(string ID) {
    for (auto &stu : students) {
        if (stu.studentId == ID) {
            return stu;
        }
    }
    throw invalid_argument("The Student was not found!!");
}

Course & Controller::findCourse(std::string courseName){
    for (auto &crs : courses) {
        if (crs.courseName == courseName) {
            return crs;
        }
    }
    throw invalid_argument("The Student was not found!!");
}

bool Controller::checkPreCoursesInPassedCourses(const Student& stu , const Course& course){
    for(const auto & preCrs : course.preCourses){
        if(find(stu.passedCourses.begin() , stu.passedCourses.end() , preCrs) == stu.passedCourses.end()){
            return false;
        }
    }
    return true;
}

void Controller::takeCourse(const std::string &studentID, const std::string &courseName) {
    Student & stu = findStudent(studentID);     // * stu must be reference
    Course crs = findCourse(courseName);
    try{
        if (inCourses(courseName)) {
            if (!stu.inPassedCourses(courseName) && !stu.inCurrentSemesterCourses(courseName)) {
                if(checkPreCoursesInPassedCourses(stu, crs)){
                    stu.currentSemesterCourses.insert({courseName , 0});
                    save();      // save the changes
                    cout << "The course has been taken successfully." << endl;
                }
                else{
                    cout << "You haven't passed some pre courses of " << courseName << endl;
                }
            }
            else {
                cout << "The course has already been taken!" << endl;
            }
        }
        else{
            cout << "The course doesn't exist!" << endl;
        }
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }
}

void Controller::dropCourse(const std::string& studentID, const std::string& courseName){
    try{
        Student & stu = findStudent(studentID);
        auto crs = stu.currentSemesterCourses.find(courseName);
        if(crs == stu.currentSemesterCourses.end()){
            cout << "The Course doesn't exist in the student's courses." << endl;
        }
        else{
            stu.currentSemesterCourses.erase(crs);
            save();
            cout << "The course has been deleted successfully." << endl;
        }
    }
    catch(const invalid_argument& e){
        cout << e.what() << endl;
    }
}

void Controller::readMembersFromFile(){
    ifstream input("members.txt");
    char typeSpecifier;
    Student *stu;
    Professor *prof;
    DoubleMajorStudent *dmStu;
    string id;
    string first;
    string last;
    string title;
    double wh;
    while (!input.eof()){   // text file must not have empty line at the end
        input >> typeSpecifier;
        if(typeSpecifier == 'S'){
            input >> id >> first >> last >> wh;
            stu = new Student(id,first,last,wh,vector<string>{} , map<string , double>{});
            mathClass.push_back(stu);
        }
        else if(typeSpecifier == 'P'){
            input >> id >> first >> last >> title >> wh;
            prof = new Professor(id , first , last , wh , title);
            mathClass.push_back(prof);
        }
        else if(typeSpecifier == 'D'){
            input >> id >> first >> last >> wh;
            dmStu = new DoubleMajorStudent(id , first , last , wh , vector<string>{} , map<string , double>{} , "");
            mathClass.push_back(dmStu);
        }
    }
    input.close();
}

double Controller::calculateTotalSalary(){
    double totalSalary = 0;
    for(const auto& person : mathClass){
        totalSalary += person->calculateSalary();
    }
    return totalSalary;
}

void Controller::showThisSemesterCourses() const{
    if(currentSemesterCourses.size() == 0){
        cout << "There is nothing to show !" << endl;
    }
    else{
        for(const auto & course : currentSemesterCourses){
            cout << course.courseName << "  |  ";
        }
        cout << endl;
    }
}