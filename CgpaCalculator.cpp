#include <iostream>
#include <vector>
#include <iomanip>

struct Course {
    double grade;
    int credits;
};

int main() {
    std::cout << "CGPA Calculator\n";
    std::cout << "----------------\n";

    int semesters;
    std::cout << "Enter number of semesters: ";
    if (!(std::cin >> semesters) || semesters <= 0) {
        std::cerr << "Invalid number of semesters. Please enter a positive integer.\n";
        return 1;
    }

    std::vector<std::vector<Course>> semesterCourses(semesters);
    double totalGradePoints = 0.0;
    int totalCredits = 0;

    for (int s = 0; s < semesters; ++s) {
        std::cout << "\nSemester " << (s + 1) << ":\n";
        int courses;
        std::cout << "Enter number of courses in semester " << (s + 1) << ": ";
        if (!(std::cin >> courses) || courses <= 0) {
            std::cerr << "Invalid number of courses. Please enter a positive integer.\n";
            return 1;
        }

        semesterCourses[s].resize(courses);
        for (int c = 0; c < courses; ++c) {
            std::cout << "  Course " << (c + 1) << " grade (0.0 - 10.0): ";
            if (!(std::cin >> semesterCourses[s][c].grade) || semesterCourses[s][c].grade < 0.0 || semesterCourses[s][c].grade > 10.0) {
                std::cerr << "Invalid grade. Please enter a value between 0.0 and 10.0.\n";
                return 1;
            }

            std::cout << "  Course " << (c + 1) << " credit hours: ";
            if (!(std::cin >> semesterCourses[s][c].credits) || semesterCourses[s][c].credits <= 0) {
                std::cerr << "Invalid credit hours. Please enter a positive integer.\n";
                return 1;
            }

            totalCredits += semesterCourses[s][c].credits;
            totalGradePoints += semesterCourses[s][c].grade * semesterCourses[s][c].credits;
        }
    }

    if (totalCredits == 0) {
        std::cerr << "Total credits must be greater than zero.\n";
        return 1;
    }

    std::cout << "\nCourse details and semester GPAs:\n";
    std::cout << std::fixed << std::setprecision(2);

    int overallCredits = 0;
    double cumulativeGradePoints = 0.0;
    for (int s = 0; s < semesters; ++s) {
        std::cout << "\nSemester " << (s + 1) << ":\n";
        int semesterCredits = 0;
        double semesterPoints = 0.0;

        for (int c = 0; c < static_cast<int>(semesterCourses[s].size()); ++c) {
            const Course &course = semesterCourses[s][c];
            std::cout << "  Course " << (c + 1) << ": grade=" << course.grade << ", credits=" << course.credits << "\n";
            semesterCredits += course.credits;
            semesterPoints += course.grade * course.credits;
        }

        double semesterGPA = semesterCredits > 0 ? semesterPoints / semesterCredits : 0.0;
        std::cout << "  Semester total credits: " << semesterCredits << "\n";
        std::cout << "  Semester GPA: " << semesterGPA << "\n";

        overallCredits += semesterCredits;
        cumulativeGradePoints += semesterPoints;
    }

    double cgpa = cumulativeGradePoints / overallCredits;
    std::cout << "\nOverall total credits: " << overallCredits << "\n";
    std::cout << "Final CGPA: " << cgpa << "\n";

    return 0;
}
