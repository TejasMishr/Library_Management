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

class Book{
public:
    string bookId;
    string bookName;
    string author;
    bool isIssued;
    string issuedTo;
};
class lib{
private:
    vector<Student> students;
    vector<Book> books;
    
public:
    fstream studentFile;
    fstream bookFile;

    void createStudentRecord();
    void displayAllStudents();
    void displaySpecificStudent();
     void modifyStudentRecord();
     void deleteStudentRecord();
     void addBook();
    void displayBookList(); 
    void extractBook();
    void removeBook();
     void issueBook();
    void showIssuedBooks();
    void returnBook();
    void showAvailableBooks();

};

void lib::createStudentRecord(){
    Student newStudent;
    cout<<"Enter Student ID:";
    cin>>newStudent.studentId;
    cout<<"Enter Student Name:";
    cin.ignore();
    getline(cin, newStudent.studentName);

    students.push_back(newStudent);
    studentFile<<newStudent.studentId<<","<<newStudent.studentName<<endl;
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

            studentFile.close();
            studentFile.open("students.txt", ios::out | ios::trunc);
            for(auto student:students) {
                studentFile<<student.studentId<<","<<student.studentName<<endl;
            }
            studentFile.close();

            cout << "Student record modified successfully!" << endl;
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

        studentFile.close();
        studentFile.open("students.txt", ios::out | ios::trunc);
        for(auto student:students) {
            studentFile<<student.studentId<<","<<student.studentName<<endl;
        }
        studentFile.close();
        cout<<"Student record deleted successfully!\n";
    } else {
        cout<<"Student not found."<<endl;
    }
}


void lib::addBook(){
    Book newBook;
    cout<<"Enter Book ID: ";
    cin>>newBook.bookId;
    cout<<"Enter Book Name: ";
    cin.ignore();
    getline(cin, newBook.bookName);
    cout<<"Enter Author Name: ";
    getline(cin, newBook.author);
    

    books.push_back(newBook);
    bookFile.open("library.txt", ios::app);
    bookFile<<newBook.bookId<< ","<<newBook.bookName<< "," <<newBook.author<<endl;
    bookFile.close();
    cout<<"Book added successfully!\n";
}
   
    


void lib::displayBookList(){
    bookFile.open("books.txt",ios::in);
    if(!bookFile){
        cout<<"No books in the library.\n";
        return;
    }

    cout<<"Books in the Library:\n";
    cout<<"ID\tName\tAuthor\n";

    string line;
    while(getline(bookFile, line)){
        cout<<line<<endl;
    }

    bookFile.close();
}

void lib::extractBook(){
    string searchId;
    cout<<"Enter Book ID to extract: ";
    cin>>searchId;

    bookFile.open("books.txt", ios::in);
    if(!bookFile){
        cout<<"No books in the library."<<endl;
        return;
    }

    string line;
    bool found = false;
    while(getline(bookFile, line)) {
        size_t pos1=line.find(",");
        size_t pos2=line.find(",", pos1 + 1);

        string currentId=line.substr(0, pos1);
        string currentName=line.substr(pos1 + 1, pos2 - pos1 - 1);
        string currentAuthor=line.substr(pos2 + 1);

        if (currentId == searchId) {
            cout<< "Book Found:\n";
            cout<<"ID: "<<currentId <<endl;
            cout<<"Name: "<<currentName<<endl;
            cout<<"Author: "<<currentAuthor<<endl;
            found=true;
            break;
        }
    }

    bookFile.close();

    if (!found) {
        cout<<"Book not found.\n";
    }
}

void lib::removeBook(){
    string searchId;
    cout<<"Enter Book ID to remove:";
    cin>>searchId;
    ifstream inputFile("books.txt");
    ofstream outputFile("temp.txt");

    string line;
    bool found=false;

    while(getline(inputFile, line)) {
        size_t pos1= line.find(",");
        string currentId=line.substr(0, pos1);
        if(currentId!=searchId) {
            outputFile<<line<< endl;
        } else{
            found=true;
        }
    }

    inputFile.close();
    outputFile.close();

    remove("books.txt");
    rename("temp.txt","books.txt");

    if(found){
        cout<<"Book removed successfully!\n";
    }else{
        cout<<"Book not found."<<endl;
    }
}


void lib::issueBook() {
    std::string studentId, bookId;
    std::cout << "Enter Student ID: ";
    std::cin >> studentId;
    std::cout << "Enter Book ID: ";
    std::cin >> bookId;

    // Find student and book by their IDs
    auto studentIt = std::find_if(students.begin(), students.end(),
                                  [studentId](const Student &student) { return student.studentId == studentId; });

    auto bookIt = std::find_if(books.begin(), books.end(),
                               [bookId](const Book &book) { return book.bookId == bookId && !book.isIssued; });

    if (studentIt != students.end() && bookIt != books.end()) {
        // Update book status and record the student who issued the book
        bookIt->isIssued = true;
        bookIt->issuedTo = studentId;

        std::cout << "Book issued successfully!" << std::endl;
    } else {
        std::cout << "Invalid Student ID or Book ID. Cannot issue the book." << std::endl;
    }
}

void lib::showIssuedBooks() {
    std::cout << "Issued Books:" << std::endl;
    std::cout << "Book ID\tBook Name\tIssued To Student ID" << std::endl;

    for (const auto &book : books) {
        if (book.isIssued) {
            std::cout << book.bookId << "\t" << book.bookName << "\t" << book.issuedTo << std::endl;
        }
    }
}

void lib::returnBook() {
    std::string bookId;
    std::cout << "Enter Book ID to return: ";
    std::cin >> bookId;

    auto bookIt = std::find_if(books.begin(), books.end(),
                               [bookId](const Book &book) { return book.bookId == bookId && book.isIssued; });

    if (bookIt != books.end()) {
        // Update book status
        bookIt->isIssued = false;
        bookIt->issuedTo = "";

        std::cout << "Book returned successfully!" << std::endl;
    } else {
        std::cout << "Book not found or not issued. Cannot return the book." << std::endl;
    }
}

void lib::showAvailableBooks() {
    std::cout << "Available Books:" << std::endl;
    std::cout << "Book ID\tBook Name\tAuthor" << std::endl;

    for (const auto &book : books) {
        if (!book.isIssued) {
            std::cout << book.bookId << "\t" << book.bookName << "\t" << book.author << std::endl;
        }
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
        
        
        cout<<"6-Add Book" << endl;
        cout<<"7-Display Book List"<<endl;
        cout<<"8-Extract Book" << endl;
        
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

            case '6':
                library.addBook();
                break;
            case '7':
                library.displayBookList();
                break;

            case '8':
                library.extractBook();
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
                break;
            

            

            case '0':
                cout<<"Exiting the program. Goodbye!" <<endl;
                break;

            default:
                cout<<"Invalid choice! Please enter a valid option." <<endl;
        }
    }
    while(choice!='0');

    return 0;
}