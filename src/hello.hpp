#ifndef GRADEBOOK_HPP
#define GRADEBOOK_HPP

#include <string>
#include <vector>
#include <map>

struct Student {
    std::string first;
    std::string last;
    std::string id;
};

struct Assignment {
    std::string name;
    int total_points;
};

class Gradebook {
private:
    std::vector<Student> students;
    std::vector<Assignment> assignments;

    std::map<std::string, std::map<std::string, int>> grades;

public:
    void add_student(const std::string& full_name, const std::string& id);
    void add_assignment(const std::string& name, int total_points);
    void enter_grade(const std::string& full_name, const std::string& assignment, int grade);

    std::string report() const;
};

#endif
