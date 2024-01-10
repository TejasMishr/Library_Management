#include <iostream>
#include<bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;


class Student{
public:
    string studentId; 
    string studentName;
};
class lib{
private:
    vector<Student> students;

public:
    void createStudentRecord();
    void displayAllStudents();
    void displaySpecificStudent();
     void modifyStudentRecord();
     void deleteStudentRecord();
};

void lib::createStudentRecord(){
    Student newStudent;
    cout<<"Enter Student ID:";
    cin>>newStudent.studentId;
    cout<<"Enter Student Name:";
    cin.ignore();
    getline(cin, newStudent.studentName);

    students.push_back(newStudent);
    cout<<"Student record created successfully!"<<endl;
}

void lib::displayAllStudents() {
    cout<< "List of Students:"<<endl;
    cout<<"ID\tName\n";

    for(auto s: students) {
        cout<<s.studentId<<"\t" <<s.studentName <<endl;
    }
}

void lib::displaySpecificStudent() {
    string searchId;
    cout<<"Enter Student ID to display: "<<endl;
    cin>> searchId;

    for(auto s:students) {
        if (s.studentId ==searchId) {
            cout<< "Student Found:\n";
            cout<<"ID: "<<s.studentId <<endl;
            cout<<"Name: " <<s.studentName <<endl;
            return;
        }
    }
    cout<<"Student not found."<<endl;
}

void lib::modifyStudentRecord() {
    string searchId;
    cout<<"Enter Student ID to modify: "<<endl;
    cin>> searchId;
    for(auto s:students) {
        if(s.studentId == searchId) {
            cout<<"Enter new Student ID: ";
            cin>>s.studentId;
            cout<<"Enter new Student Name: ";
            cin.ignore();
            getline(cin, s.studentName);

            cout<<"Student record modified successfully!"<<endl;
            return;
        }
    }
    cout<<"Student not found."<<endl;
}

void lib::deleteStudentRecord() {
    string searchId;
    cout<<"Enter Student ID to delete: ";
    cin>>searchId;
    auto it = remove_if(students.begin(), students.end(),[searchId](const Student& student) {
            return student.studentId == searchId;});
    if(it!= students.end()) {
        students.erase(it,students.end());
        cout<<"Student record deleted successfully!\n";
    } else {
        cout<<"Student not found."<<endl;
    }
}






int main(){
    lib library;

    char choice;

    do{
        cout<< "--------------------------------------------" << endl;
        cout<< "--------------------------------------------" << endl;
        cout<<"1-Create Students Record"<<endl;
        cout<<"2-Display All Students Record"<<endl;
        cout<<"3-Display Specific Student Record"<<endl;
        cout<<"4-Modify Student Record"<<endl;
        cout<<"5-Delete Student Record"<<endl;
        
        
        cout<<"6-Display Book List" << endl;
        cout<<"7-Extract Book" << endl;
        cout<<"8-Add Book"<<endl;
        cout<<"9-Remove Book" <<endl;
        cout<<"10-Issue Book"<< endl;
        cout<<"11-Show Issued Books"<<endl;
        cout<<"12-Return Book"<< endl;
        cout<<"13-Show Available Books"<<endl;

        cout<< "0- Exit"<< endl;
        cout<< "---------------------------------------------" << endl;
        cout<< "--------------------------------------------" << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                library.createStudentRecord();
                break;

            case '2':
                library.displayAllStudents();
                break;

            case '3':
                library.displaySpecificStudent();
                break;

            case '4':
                library.modifyStudentRecord();
                break;
            case '5':
                library.deleteStudentRecord();
                break;

            
            /*case '6':
                library.bookList();
                break;

            case '7':
                library.extractBook();
                break;

            
            case '8':
                library.addBook();
                break;

            case '9':
                library.removeBook();
                break;

            case '10':
                library.issueBook();
                break;

            case '11':
                library.showIssuedBooks();
                break;

            
            case '12':
                library.returnBook();
                break;

            case '13':
                library.showAvailableBooks();
                break; */

            case '0':
                cout<<"Exiting the program. Goodbye!" <<endl;
                break;

            default:
                cout<<"Invalid choice! Please enter a valid option." <<endl;
        }
    }
    while(choice != '0');

    return 0;
}