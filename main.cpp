#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <random>

using namespace std;

class Person {
private:
    string name;
    string surname;
    vector<int> homework;
    int exam;
    double finalAverage;
    double finalMedian;

public:
    Person() : exam(0), finalAverage(0.0), finalMedian(0.0) {}

    Person(const Person& other)
        : name(other.name), surname(other.surname),
          homework(other.homework), exam(other.exam),
          finalAverage(other.finalAverage), finalMedian(other.finalMedian) {}

    Person& operator=(const Person& other) {
        if (this != &other) {
            name = other.name;
            surname = other.surname;
            homework = other.homework;
            exam = other.exam;
            finalAverage = other.finalAverage;
            finalMedian = other.finalMedian;
        }
        return *this;
    }

    ~Person() {}
    friend istream& operator>>(istream& in, Person& p) {
        cout << "Enter your first and last name: ";
        in >> p.name >> p.surname;

        cout << "Enter your homework grades (end with 0): ";
        int mark;
        p.homework.clear();
        while (in >> mark && mark != 0) {
            p.homework.push_back(mark);
        }

        cout << "Enter your exam grade: ";
        in >> p.exam;

        return in;
    }

    friend ostream& operator<<(ostream& out, const Person& p) {
        out << left << setw(12) << p.name
            << left << setw(12) << p.surname
            << right << setw(12) << fixed << setprecision(2) << p.finalAverage
            << " | " << right << setw(12) << fixed << setprecision(2) << p.finalMedian;
        return out;
    }

    void calculateGrades() {
        if (homework.empty()) {
            finalAverage = 0;
            finalMedian = 0;
            return;
        }

        double avg = accumulate(homework.begin(), homework.end(), 0.0) / homework.size();
        finalAverage = 0.4 * avg + 0.6 * exam;

        vector<int> sortedHW = homework;
        sort(sortedHW.begin(), sortedHW.end());
        double median;
        if (sortedHW.size() % 2 == 0)
            median = (sortedHW[sortedHW.size() / 2 - 1] + sortedHW[sortedHW.size() / 2]) / 2.0;
        else
            median = sortedHW[sortedHW.size() / 2];
        finalMedian = 0.4 * median + 0.6 * exam;
    }

    void generateRandomGrades(int hwCount) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, 10);

        homework.clear();
        for (int i = 0; i < hwCount; ++i)
            homework.push_back(dist(gen));
        exam = dist(gen);
    }

    void setName(const string& n, const string& s) {
        name = n;
        surname = s;
    }

    string getName() const { return name; }
    string getSurname() const { return surname; }
};

vector<Person> readFromFile(const string& filename) {
    vector<Person> students;
    ifstream file(filename);
    if (!file) {
        cerr << "Error: file not found!" << endl;
        return students;
    }

    string header;
    getline(file, header); 

    while (!file.eof()) {
        Person p;
        string name, surname;
        file >> name >> surname;
        if (file.fail()) break;

        vector<int> hw(5);
        int exam;
        for (int i = 0; i < 5; ++i)
            file >> hw[i];
        file >> exam;

        p.setName(name, surname);
        for (int h : hw)
            p.generateRandomGrades(5);
        p.calculateGrades();

        students.push_back(p);
    }
    return students;
}

int main() {
    vector<Person> students;

    cout << "Select mode:\n1 - Enter students manually\n2 - Read from file\nEnter selection: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        int n;
        cout << "How many students? ";
        cin >> n;

        for (int i = 0; i < n; ++i) {
            Person p;
            cin >> p;
            p.calculateGrades();
            students.push_back(p);
        }
    } else if (choice == 2) {
        students = readFromFile("Students.txt");
    }

    sort(students.begin(), students.end(),
         [](const Person& a, const Person& b) { return a.getSurname() < b.getSurname(); });

    cout << left << setw(12) << "Name"
         << left << setw(12) << "Surname"
         << right << setw(16) << "Final (Avg.)"
         << " | " << right << setw(12) << "Final (Med.)" << endl;
    cout << string(60, '-') << endl;

    for (const auto& s : students)
        cout << s << endl;

    return 0;
}
