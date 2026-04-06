#include "hello.hpp"
#include <sstream>
#include <iostream>

static std::pair<std::string, std::string> split_name(const std::string& full) {
    size_t space = full.find(' ');
    return { full.substr(0, space), full.substr(space + 1) };
}

void Gradebook::add_student(const std::string& full_name, const std::string& id) {
    auto [first, last] = split_name(full_name);
    students.push_back({ first, last, id });
}

void Gradebook::add_assignment(const std::string& name, int total_points) {
    assignments.push_back({ name, total_points });
}

void Gradebook::enter_grade(const std::string& full_name,
                            const std::string& assignment,
                            int grade)
{
    auto [first, last] = split_name(full_name);

    // find student ID
    std::string id = "";
    for (const auto& s : students) {
        if (s.first == first && s.last == last) {
            id = s.id;
            break;
        }
    }

    if (id == "") return; // student not found

    grades[id][assignment] = grade;
}

std::string Gradebook::report() const {
    std::ostringstream out;

    // header
    out << "Last_Name,First_Name,Student_Id";
    for (const auto& a : assignments)
        out << "," << a.name;
    out << "\n";

    // rows
    for (const auto& s : students) {
        out << s.last << "," << s.first << "," << s.id;

        for (const auto& a : assignments) {
            auto it = grades.find(s.id);

            if (it != grades.end() && it->second.count(a.name))
                out << "," << it->second.at(a.name);
            else
                out << ",none";
        }

        out << "\n";
    }

    return out.str();
}