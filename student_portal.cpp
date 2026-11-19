// Student Portal - C++ Mini Project (Option C)
// Features: add / search / list / update / delete students,
//           calculate result & grade, save/load to CSV file,
//           validation of ID and marks, exception handling.

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <limits>
using namespace std;

// ---------------- Student class ----------------
class Student {
private:
    int id;
    string name;
    string course;
    double marks;

public:
    Student() : id(0), marks(0) {}

    Student(int id, const string& name, const string& course, double marks) {
        setId(id);
        setName(name);
        setCourse(course);
        setMarks(marks);
    }

    // Setters with validation (throw invalid_argument on bad data)
    void setId(int v) {
        if (v <= 0) throw invalid_argument("ID must be a positive number.");
        id = v;
    }
    void setName(const string& v) {
        if (v.empty()) throw invalid_argument("Name cannot be empty.");
        if (v.find(',') != string::npos) throw invalid_argument("Name cannot contain a comma.");
        name = v;
    }
    void setCourse(const string& v) {
        if (v.empty()) throw invalid_argument("Course cannot be empty.");
        if (v.find(',') != string::npos) throw invalid_argument("Course cannot contain a comma.");
        course = v;
    }
    void setMarks(double v) {
        if (v < 0 || v > 100) throw invalid_argument("Marks must be between 0 and 100.");
        marks = v;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    string getCourse() const { return course; }
    double getMarks() const { return marks; }

    string getGrade() const {
        if (marks >= 90) return "A+";
        if (marks >= 80) return "A";
        if (marks >= 70) return "B";
        if (marks >= 60) return "C";
        if (marks >= 50) return "D";
        if (marks >= 40) return "E";
        return "F";
    }
    string getResult() const { return marks >= 40 ? "PASS" : "FAIL"; }

    void display() const {
        cout << left << setw(6) << id
             << setw(22) << name
             << setw(16) << course
             << setw(8) << fixed << setprecision(2) << marks
             << setw(7) << getGrade()
             << getResult() << "\n";
    }

    string toCSV() const {
        ostringstream os;
        os << id << "," << name << "," << course << "," << marks;
        return os.str();
    }
};

// ---------------- StudentPortal class ----------------
class StudentPortal {
private:
    map<int, Student> records;   // STL container: ID -> Student
    string filename;

public:
    explicit StudentPortal(const string& file) : filename(file) {}

    void addStudent(const Student& s) {
        if (records.count(s.getId()))
            throw runtime_error("A student with this ID already exists.");
        records[s.getId()] = s;
    }

    Student& findStudent(int id) {
        auto it = records.find(id);
        if (it == records.end())
            throw out_of_range("No student found with ID " + to_string(id) + ".");
        return it->second;
    }

    void deleteStudent(int id) {
        if (records.erase(id) == 0)
            throw out_of_range("No student found with ID " + to_string(id) + ".");
    }

    static void printHeader() {
        cout << left << setw(6) << "ID" << setw(22) << "Name" << setw(16) << "Course"
             << setw(8) << "Marks" << setw(7) << "Grade" << "Result\n";
        cout << string(66, '-') << "\n";
    }

    void listAll() const {
        if (records.empty()) { cout << "No records available.\n"; return; }
        printHeader();
        for (const auto& p : records) p.second.display();
        cout << "Total students: " << records.size() << "\n";
    }

    void searchByName(const string& key) const {
        bool found = false;
        for (const auto& p : records) {
            if (p.second.getName().find(key) != string::npos) {
                if (!found) printHeader();
                p.second.display();
                found = true;
            }
        }
        if (!found) cout << "No student matches \"" << key << "\".\n";
    }

    void save() const {
        ofstream out(filename);
        if (!out) throw runtime_error("Cannot open file for writing: " + filename);
        for (const auto& p : records) out << p.second.toCSV() << "\n";
    }

    void load() {
        ifstream in(filename);
        if (!in) return;   // first run: no file yet
        string line;
        int lineNo = 0, skipped = 0;
        while (getline(in, line)) {
            lineNo++;
            if (line.empty()) continue;
            try {
                stringstream ss(line);
                string sid, name, course, smarks;
                getline(ss, sid, ',');
                getline(ss, name, ',');
                getline(ss, course, ',');
                getline(ss, smarks, ',');
                addStudent(Student(stoi(sid), name, course, stod(smarks)));
            } catch (const exception&) {
                skipped++;
            }
        }
        cout << "Loaded " << records.size() << " record(s) from " << filename;
        if (skipped) cout << " (" << skipped << " invalid line(s) skipped)";
        cout << "\n";
    }
};

// ---------------- Input helpers ----------------
string readLine(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

int readInt(const string& prompt) {
    while (true) {
        string s = readLine(prompt);
        try {
            size_t pos;
            int v = stoi(s, &pos);
            if (pos != s.size()) throw invalid_argument("x");
            return v;
        } catch (const exception&) {
            cout << "Invalid number. Try again.\n";
        }
    }
}

double readDouble(const string& prompt) {
    while (true) {
        string s = readLine(prompt);
        try {
            size_t pos;
            double v = stod(s, &pos);
            if (pos != s.size()) throw invalid_argument("x");
            return v;
        } catch (const exception&) {
            cout << "Invalid number. Try again.\n";
        }
    }
}

// ---------------- Main ----------------
int main() {
    StudentPortal portal("students.csv");
    portal.load();

    int choice;
    do {
        cout << "\n===== STUDENT PORTAL =====\n"
             << "1. Add student\n"
             << "2. List all students\n"
             << "3. Search by ID\n"
             << "4. Search by name\n"
             << "5. Update marks\n"
             << "6. Delete student\n"
             << "7. Save to file\n"
             << "0. Save & Exit\n";
        choice = readInt("Enter choice: ");

        try {
            switch (choice) {
            case 1: {
                int id = readInt("Student ID: ");
                string name = readLine("Name: ");
                string course = readLine("Course: ");
                double marks = readDouble("Marks (0-100): ");
                portal.addStudent(Student(id, name, course, marks));
                cout << "Student added.\n";
                break;
            }
            case 2:
                portal.listAll();
                break;
            case 3: {
                int id = readInt("Enter ID: ");
                Student& s = portal.findStudent(id);
                StudentPortal::printHeader();
                s.display();
                break;
            }
            case 4:
                portal.searchByName(readLine("Enter name (or part): "));
                break;
            case 5: {
                int id = readInt("Enter ID: ");
                Student& s = portal.findStudent(id);
                s.setMarks(readDouble("New marks (0-100): "));
                cout << "Marks updated. New grade: " << s.getGrade()
                     << " (" << s.getResult() << ")\n";
                break;
            }
            case 6: {
                portal.deleteStudent(readInt("Enter ID to delete: "));
                cout << "Student deleted.\n";
                break;
            }
            case 7:
                portal.save();
                cout << "Saved.\n";
                break;
            case 0:
                portal.save();
                cout << "Data saved. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice.\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    } while (choice != 0);

    return 0;
}