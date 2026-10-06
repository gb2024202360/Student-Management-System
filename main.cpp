#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Student
{
public:
    int id;
    string name;
    int age;
    string course;
    float marks;
    void input()
    {
        cout << "Enter Student ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter Course: ";
        getline(cin, course);
        cout << "Enter Marks: ";
        cin >> marks;
    }
    void display()
    {
        cout << "\n-----------------------------";
        cout << "\nStudent ID : " << id;
        cout << "\nName       : " << name;
        cout << "\nAge        : " << age;
        cout << "\nCourse     : " << course;
        cout << "\nMarks      : " << marks;
        cout << "\n-----------------------------\n";
    }
};

// Add Student
void addStudent()
{
    Student s;
    ofstream file("students.txt", ios::app);
    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }
    s.input();
    file << s.id << "|"
         << s.name << "|"
         << s.age << "|"
         << s.course << "|"
         << s.marks << endl;
    file.close();
    cout << "\nStudent added successfully!\n";
}
// Display Students
void displayStudents()
{
    ifstream file("students.txt");
    if (!file)
    {
        cout << "\nNo student records found!\n";
        return;
    }
    Student s;
    string line;
    bool found = false;
    cout << "\n========== STUDENT RECORDS ==========\n";
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);
        s.id = stoi(line.substr(0, p1));
        s.name = line.substr(p1 + 1, p2 - p1 - 1);
        s.age = stoi(line.substr(p2 + 1, p3 - p2 - 1));
        s.course = line.substr(p3 + 1, p4 - p3 - 1);
        s.marks = stof(line.substr(p4 + 1));
        s.display();
        found = true;
    }
    file.close();
    if (!found)
        cout << "No student records found!\n";
}
// Update Student
void updateStudent()
{
    int id;
    cout << "Enter Student ID to update: ";
    cin >> id;
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    if (!file || !temp)
    {
        cout << "Error opening file!\n";
        return;
    }
    Student s;
    string line;
    bool found = false;
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);
        s.id = stoi(line.substr(0, p1));
        s.name = line.substr(p1 + 1, p2 - p1 - 1);
        s.age = stoi(line.substr(p2 + 1, p3 - p2 - 1));
        s.course = line.substr(p3 + 1, p4 - p3 - 1);
        s.marks = stof(line.substr(p4 + 1));
        if (s.id == id)
        {
            cout << "\nEnter new details:\n";
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, s.name);
            cout << "Enter Age: ";
            cin >> s.age;
            cin.ignore();
            cout << "Enter Course: ";
            getline(cin, s.course);
            cout << "Enter Marks: ";
            cin >> s.marks;
            found = true;
        }
        temp << s.id << "|"
             << s.name << "|"
             << s.age << "|"
             << s.course << "|"
             << s.marks << endl;
    }
    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found)
        cout << "\nStudent updated successfully!\n";
    else
        cout << "\nStudent not found!\n";
}
// Delete Student
void deleteStudent()
{
    int id;
    cout << "Enter Student ID to delete: ";
    cin >> id;
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    if (!file || !temp)
    {
        cout << "Error opening file!\n";
        return;
    }
    Student s;
    string line;
    bool found = false;
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);
        s.id = stoi(line.substr(0, p1));
        s.name = line.substr(p1 + 1, p2 - p1 - 1);
        s.age = stoi(line.substr(p2 + 1, p3 - p2 - 1));
        s.course = line.substr(p3 + 1, p4 - p3 - 1);
        s.marks = stof(line.substr(p4 + 1));
        if (s.id == id)
        {
            found = true;
            continue;
        }
        temp << s.id << "|"
             << s.name << "|"
             << s.age << "|"
             << s.course << "|"
             << s.marks << endl;
    }
    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found)
        cout << "\nStudent deleted successfully!\n";
    else
        cout << "\nStudent not found!\n";
}
// Main Function
int main()
{
    int choice;
    do
    {
        cout << "\n====================================";
        cout << "\n      STUDENT MANAGEMENT SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Add Student";
        cout << "\n2. Display Students";
        cout << "\n3. Update Student";
        cout << "\n4. Delete Student";
        cout << "\n5. Exit";
        cout << "\n====================================";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            updateStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            cout << "\nThank you for using Student Management System!\n";
            break;
        default:
            cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 5);
    return 0;
}
