#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Student structure
struct Student {
    string name;
    int marks;
    int scholarshipPercent;
};

// Scholarship calculation logic
int calculateScholarship(int marks) {
    if (marks >= 90)
        return 50;
    else if (marks >= 80)
        return 40;
    else if (marks >= 70)
        return 30;
    else
        return 0;
}

// Sorting comparator (descending by marks)
bool compareByMarks(Student a, Student b) {
    return a.marks > b.marks;
}

// Max-heap comparator for top scorers
struct Compare {
    bool operator()(Student a, Student b) {
        return a.marks < b.marks;
    }
};

int main() {
    ifstream fin("students.txt");
    ofstream fout("result.txt");

    if (!fin) {
        cerr << "Error: students.txt not found!" << endl;
        return 1;
    }

    int n;
    fin >> n;
    if (n <= 0) {
        cerr << "Invalid number of students!" << endl;
        return 1;
    }

    vector<Student> students(n);

    for (int i = 0; i < n; ++i) {
        fin >> students[i].name >> students[i].marks;
        students[i].scholarshipPercent = calculateScholarship(students[i].marks);
    }

    // Sort students by marks
    sort(students.begin(), students.end(), compareByMarks);

    // Priority queue (heap) for top 3 scorers
    priority_queue<Student, vector<Student>, Compare> pq;
    for (auto s : students) pq.push(s);

    // Write results to file
    fout << "🎓 Scholarship Allocation Result\n\n";

    for (const auto& s : students) {
        fout << "Name: " << s.name << "\n";
        fout << "Marks: " << s.marks << "%\n";
        fout << "Scholarship Awarded: " << s.scholarshipPercent << "%\n";
        fout << "-----------------------------\n";
    }

    fout << "\n🏆 Top 3 Scorers:\n";
    for (int i = 0; i < 3 && !pq.empty(); ++i) {
        Student top = pq.top();
        fout << top.name << " (" << top.marks << "%)\n";
        pq.pop();
    }

    fout.close();
    fin.close();

    cout << "✅ Scholarship allocation complete. See result.txt." << endl;
    return 0;
}
