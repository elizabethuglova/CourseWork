// Углова_Елизавета_08 CourseWork
#include <iostream>
#include <windows.h>
#include <string>
#include <stdio.h>
#include <fstream>  
#include <sstream>
#include <time.h>
#include <stdlib.h> 

using namespace std;
bool flag_of_end = true;

struct Date {
    unsigned short day;
    unsigned short month;
    unsigned short year;
};

class StudentBase
{
    string lastname;    
    string name;      
    string surname;     
    Date date;              
    int yearAdm;            
    string faculty;        
    string cathedra;        
    string group;           
    string sex;          
    string number;             

public:
    StudentBase() {
        setLastName("");setName("");setSurName(""); setDate({ 0, 0, 0 });
        setYearAdm(0); setFaculty(""); setCathedra(""); setGroup("");
        setSex(""); setNumber("");
    };   
    ~StudentBase() {};  
    void setStudent(string _lastname, string _name, string _surname, struct Date _date, int _yearAdm,
        string _faculty, string _cathedra, string _group, string _sex, string _number)
    {
        lastname = _lastname;
        name = _name;
        surname = _surname;
        date = _date;
        yearAdm = _yearAdm;
        faculty = _faculty;
        cathedra = _cathedra;
        group = _group;
        sex = _sex;
        number = _number;
    };
    void setLastName(string _lastname) { lastname = _lastname; }
    void setName(string _name) { name = _name; }
    void setSurName(string _surname) { surname = _surname; }
    void setDate(struct Date _date) { date = _date; }
    void setYearAdm(int _yearAdm) { yearAdm = _yearAdm; }
    void setFaculty(string _faculty) { faculty = _faculty; }
    void setCathedra(string _cathedra) { cathedra = _cathedra; }
    void setGroup(string _group) { group = _group; }
    void setSex(string _sex) { sex = _sex; }
    void setNumber(string _number) { number = _number; }

    void printcorrectDate(unsigned short day, unsigned short month, unsigned short year) {
        if (day > 0 and day < 10)
            cout << "0";
        cout << day << ".";
        if (month > 0 and month < 10)
            cout << "0";
        cout << month << "." << year;
    }
    void display() {
        cout << lastname << " " << name << " " << surname << " "; printcorrectDate(date.day, date.month, date.year);
        cout << " " << yearAdm << " " << faculty << " " << cathedra << " " << group << " " << sex << " " << number << endl;
    }

    string getLastname() const { return lastname; }
    string getName() const { return name; }
    string getSurname() const { return surname; }
    unsigned short getDay() const { return date.day; }
    unsigned short getMonth() const { return date.month; }
    unsigned short getYear() const { return date.year; }
    int getYearAdm() const { return yearAdm; }
    string getFaculty() const { return faculty; }
    string getCathedra() const { return cathedra; }
    string getGroup() const { return group; }
    string getSex() const { return sex; }
    string getNumber() const { return number; }
};

class Node
{
    StudentBase data_student;
    Node* prev;
    Node* next;
public:
    Node(StudentBase _data_student, Node* _prev = nullptr, Node* _next = nullptr) : 
        data_student(_data_student), prev(_prev), next(_next) {}; 
    ~Node() {};     
    StudentBase getData() { return data_student; } 
    Node* getPrev() { return prev; }       
    Node* getNext() { return next; }       
    void setData(StudentBase _data_student) { data_student = _data_student; }   
    void setPrev(Node* _prev) { prev = _prev; }         
    void setNext(Node* _next) { next = _next; }         
};

class DoublyLinkedList
{
    Node* head;    
    Node* tail;     
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}; 
    ~DoublyLinkedList() {};                               
    Node* getHead() { return head; }
    Node* getTail() { return tail; }
    bool isEmpty() const { return head == nullptr && tail == nullptr; }

    void addNode(StudentBase _data)
    {
        Node* node = new Node(_data, tail, nullptr);
        if (isEmpty()) head = tail = node;
        else {
            tail->setNext(node);
            tail = node;
        }
    } 

    void display() const
    {
        Node* current = head;
        while (current != nullptr) {
            current->getData().display();
            current = current->getNext();
        }
    } 

    Node* findNode(string _number) const
    {
        Node* current = head;
        while (current != nullptr && current->getData().getNumber() != _number)
            current = current->getNext();
        return current;
    }

    void updateNode(string _updateNumber, string fieldToUpdate, string newValue)
    {
        Node* nodeToUpdate = findNode(_updateNumber);
        StudentBase student = nodeToUpdate->getData();
        if (nodeToUpdate == nullptr) { cout << "Студент не найден"; }
        else if (fieldToUpdate == "lastname") {
            student.setLastName(newValue);
            nodeToUpdate->setData(student);
        }
        else if (fieldToUpdate == "name") {
            student.setName(newValue);
            nodeToUpdate->setData(student);
        }
        else if (fieldToUpdate == "surname") {
            student.setSurName(newValue);
            nodeToUpdate->setData(student);
        }
        else if (fieldToUpdate == "yearAdm") {
            student.setYearAdm(stoi(newValue)); 
            nodeToUpdate->setData(student);
        }
        else if (fieldToUpdate == "faculty") {
            student.setFaculty(newValue);
            nodeToUpdate->setData(student);
        }
        else if (fieldToUpdate == "cathedra") {
            student.setCathedra(newValue);
            nodeToUpdate->setData(student);
        }
        else if (fieldToUpdate == "group") {
            student.setGroup(newValue);
            nodeToUpdate->setData(student);
        }
        else if (fieldToUpdate == "sex") {
            student.setSex(newValue);
            nodeToUpdate->setData(student);
        }
        else if (fieldToUpdate == "number") {
            student.setNumber(newValue);
            nodeToUpdate->setData(student);
        }
    }

    void updateDateNode(string _updateNumber, Date newValue) {
        Node* nodeToUpdate = findNode(_updateNumber);
        StudentBase student = nodeToUpdate->getData();
        if (nodeToUpdate == nullptr) { cout << "Студент не найден"; }
        else {
            student.setDate(newValue);
            nodeToUpdate->setData(student);
        }
    }

    void deleteNode(string _deleteNumber)
    {
        Node* nodeToDelete = findNode(_deleteNumber);
        if (nodeToDelete == nullptr) return;
        if (nodeToDelete == head && nodeToDelete == tail) {
            head = tail = nullptr;
            delete nodeToDelete;
            return;
        }
        if (nodeToDelete == head) {
            head = head->getNext();
            head->setPrev(nullptr);
            delete nodeToDelete;
            return;
        }
        if (nodeToDelete == tail) {
            tail = tail->getPrev();
            tail->setNext(nullptr);
            delete nodeToDelete;
            return;
        }
        Node* prevNode = nodeToDelete->getPrev();
        Node* nextNode = nodeToDelete->getNext();
        prevNode->setNext(nextNode);
        nextNode->setPrev(prevNode);
        delete nodeToDelete;
    }
};

struct ExamsRecords {
    string nameExam;
    int mark;
};

class Exams {
    string number;
    ExamsRecords data[9][10]; 
public:  
    Exams() {
        number = "-";
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 10; j++) {
                data[i][j].nameExam = "-";
                data[i][j].mark = 0;
            }
        }   
    }

    ~Exams() {};
    void setNumber(string _number) {
        number = _number; 
    }
    void setSession(int sessionNum, int subjectNum, string nameExam, int mark) {       
        data[sessionNum][subjectNum].nameExam = nameExam;
        data[sessionNum][subjectNum].mark = mark;
    }
    string getNameExam(int sessionNum, int subjectNum) {
        return data[sessionNum][subjectNum].nameExam;
    }
    int getMark(int sessionNum, int subjectNum) {
        return data[sessionNum][subjectNum].mark;
    }
    string getNumber() {
        return number;
    }

    void display() {
        cout << "Студент: " << number << endl;
        for (int i = 0; i < 9; i++) {
            cout << "Сессия " << i + 1 << ":" << endl;
            for (int j = 0; j < 10; j++) {               
                cout << "Экзамен " << j + 1<< ": "<< data[i][j].nameExam << endl;
                cout << "Оценка: " << data[i][j].mark << endl;
            }
        }
        cout << endl;
    }

    void task() {
        int amount_all = 0; int amount_3 = 0;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 10; j++) {
                if (!(data[i][j].nameExam == "-" && data[i][j].mark == 0)) {amount_all++;}
                if (data[i][j].mark == 3) { amount_3++; }
            }
        }
        if (amount_3 <= floor(amount_all * 0.25)) {
            cout << number << "  количество оценок 3 равно "<< amount_3 << ", "<<"общее количество оценок равно "<< amount_all<< endl;
        }
    }
};

class NodeE
{
    Exams data_exams;
    NodeE* prev;
    NodeE* next;
public:
    NodeE(Exams _data_exams, NodeE* _prev = nullptr, NodeE* _next = nullptr) : 
        data_exams(_data_exams), prev(_prev), next(_next) {}; 
    ~NodeE() {};     
    Exams getData() { return data_exams; } 
    NodeE* getPrev() { return prev; }       
    NodeE* getNext() { return next; }       
    void setData(Exams _data_exams) { data_exams = _data_exams; }   
    void setPrev(NodeE* _prev) { prev = _prev; }        
    void setNext(NodeE* _next) { next = _next; }         
};

class DoublyLinkedListE 
{
    NodeE* head;     
    NodeE* tail;     
public:
    DoublyLinkedListE() : head(nullptr), tail(nullptr) {}; 
    ~DoublyLinkedListE() {};                               
    NodeE* getHead() { return head; }
    NodeE* getTail() { return tail; }
    bool isEmpty() const { return head == nullptr && tail == nullptr; }

    void addNode(Exams _data)
    {
        NodeE* node = new NodeE(_data, tail, nullptr);
        if (isEmpty()) head = tail = node;
        else {
            tail->setNext(node);
            tail = node;            
        }
    } 

    void display() const
    {
        NodeE* current = head;
        while (current != nullptr) {
            current->getData().display();
            current = current->getNext();           
        }
    } 

    NodeE* findNode(string _number) const
    {
        NodeE* current = head;
        while (current != nullptr && current->getData().getNumber() != _number)
            current = current->getNext();
        return current;
    }

    void deleteNode(string _deleteNumber)
    {
        NodeE* nodeToDelete = findNode(_deleteNumber);
        if (nodeToDelete == nullptr) return;
        if (nodeToDelete == head && nodeToDelete == tail) {
            head = tail = nullptr;
            delete nodeToDelete;
            return;
        }
        if (nodeToDelete == head) {
            head = head->getNext();
            head->setPrev(nullptr);
            delete nodeToDelete;
            return;
        }
        if (nodeToDelete == tail) {
            tail = tail->getPrev();
            tail->setNext(nullptr);
            delete nodeToDelete;
            return;
        }
        NodeE* prevNode = nodeToDelete->getPrev();
        NodeE* nextNode = nodeToDelete->getNext();
        prevNode->setNext(nextNode);
        nextNode->setPrev(prevNode);
        delete nodeToDelete;
    }

    void updateNode(string _updateNumber, int i, int j, string nameExam, int mark)
    {
        NodeE* nodeToUpdate = findNode(_updateNumber);
        Exams exams = nodeToUpdate->getData();
        if (nodeToUpdate == nullptr) { cout << "Студент не найден"; }
        else {           
            exams.setSession(i - 1, j - 1, nameExam, mark);
            nodeToUpdate->setData(exams);
        }
    }

    void task() {
        NodeE* current = head;
        while (current != nullptr) {
            current->getData().task();
            current = current->getNext();
        }
    }
};

void HelpMenu() {
    cout << endl;
    int n;
    cout << "Для выхода в главное меню нажмите 1 " << endl;
    cout << "Для завершения нажмите 0" << endl;
    cin >> n; system("cls");
    switch (n) {
    case 0: cout << "Закрытие программы..." << endl;  flag_of_end = false;  break;
    case 1: cout << "Переход в Главное меню" << endl; flag_of_end = true; break;
    }
}

bool correctName(string corname) {
    string alphabet = "йцукенгшщзхъфывапролджэячсмитьбюёЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ";
    for (char c : corname) {
        if (alphabet.find(c) == std::string::npos) { 
            return false; 
        }
    }
    return true;
}

bool correctDate(unsigned short d, unsigned short m, unsigned short y)
{
    if (m > 0 && m < 13)
    {
        int maxDay;
        switch (m)
        {
        case 2: maxDay = (y % 4 == 0) ? 29 : 28; 
        case 1: case 3: case 5: case 7:case 8: case 10: case 12: maxDay = 31;
        default: maxDay = 30;
        }
        if (d > 0 && d <= maxDay)
        {
            if (y > 0) {
                return true;
            }
            else return false;
        }
        else return false;
    }
    return false;
}

void printHead() {
    cout << "ФАМИЛИЯ ИМЯ ОТЧЕСТВО ДР ПОСТУП.ГОД ФАКУЛЬТЕТ КАФЕДРА ГРУППА ПОЛ ЗАЧ.КНИЖКА" << endl; cout << endl;
}

void writeListToFileStudents(DoublyLinkedList list) {
    ofstream outFile("students.txt", ios_base::out | ios_base::trunc);
    if (!outFile) {
        cerr << "Не удается открыть файл students.txt";
        exit(1);   
    }
    Node* current = list.getHead();
    while (current != nullptr) {
        StudentBase data = current->getData();
        outFile << data.getLastname() << " "
            << data.getName() << " "
            << data.getSurname() << " "
            << data.getDay() << " "
            << data.getMonth() << " "
            << data.getYear() << " "
            << data.getYearAdm() << " "
            << data.getFaculty() << " "
            << data.getCathedra() << " "
            << data.getGroup() << " "
            << data.getSex() << " "
            << data.getNumber() << endl;
        current = current->getNext();
    }
    outFile.close();
}

void writeListToFileExams(DoublyLinkedListE list) {
    ofstream outFile("exams.txt", ios_base::out | ios_base::trunc);
    if (!outFile) {
        cerr << "Не удается открыть файл exams.txt";
        exit(1);   
    }
    NodeE* current = list.getHead();
    while (current != nullptr) {
        Exams data = current->getData();
        outFile << data.getNumber() << " ";
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 10; j++) {
                outFile << data.getNameExam(i, j) << " " << data.getMark(i, j) << " ";
            }
        }
        outFile << endl; 
        current = current->getNext();
    }
    outFile.close();
}

DoublyLinkedList readFromFileStudents(string filename) {
    ifstream inFile(filename, ios_base::in);
    DoublyLinkedList list;
    if (!inFile) {
        cerr << "Не удается открыть файл students.txt";
        exit(1);   
    }
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string lastname, name, surname, faculty, cathedra, group, sex, number;
        Date date;
        int yearAdm;
        ss >> lastname >> name >> surname >> date.day >> date.month >> date.year
            >> yearAdm >> faculty >> cathedra >> group >> sex >> number;
        StudentBase student;
        student.setStudent(lastname, name, surname, date, yearAdm, faculty, cathedra, group, sex, number);
        list.addNode(student);
    }
    inFile.close();
    return list;
}

DoublyLinkedListE readFromFileExams(string filename) {
    ifstream inFile(filename, ios_base::in);
    DoublyLinkedListE list;
    if (!inFile) {
        cerr << "Не удается открыть файл exams.txt";
        exit(1);   
    }
    string line; 
    while (getline(inFile, line)) {
        stringstream ss(line);
        string number;
        Exams exams;
        ExamsRecords mass;
        ss >> number; exams.setNumber(number);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 10; j++) {
                ss >> mass.nameExam >> mass.mark; exams.setSession(i, j, mass.nameExam, mass.mark);
            }
        }
        list.addNode(exams);
    }   
    inFile.close();
    return list;
}

void updateStudent() {
    DoublyLinkedList list = readFromFileStudents("students.txt");
    cout << "Изначальный список студентов"; cout << endl; printHead();
    list.display(); cout << endl;
    cout << "Введите номер зачетной книжки студента," << endl;
    cout << "данные которого Вы хотите изменить -> ";
    string updateNumber; cin >> updateNumber; cout << endl;
    cout << "Введите цифру, соответствующую действию, которое Вы хотите сделать" << endl;
    cout << "1 - изменить Фамилию" << endl; cout << "2 - изменить Имя" << endl;
    cout << "3 - изменить Отчество" << endl; cout << "4 - изменить Дату рождения" << endl;
    cout << "5 - изменить год поступления" << endl; cout << "6 - изменить факультет" << endl;
    cout << "7 - изменить кафедру" << endl; cout << "8 - изменить группу" << endl;
    cout << "9 - изменить пол" << endl; cout << "10 - номер зачетной книжки" << endl; cout << endl;
    int n; cin >> n;
    if (n == 1) {
        string newlastname; cout << "Введите новую Фамилию -> "; cin >> newlastname;
        if (correctName(newlastname)) { list.updateNode(updateNumber, "lastname", newlastname); }
        else { "Фамилия некорректна"; }
    }
    else if (n == 2) {
        string newname; cout << "Введите новое Имя -> "; cin >> newname;
        if (correctName(newname)) { list.updateNode(updateNumber, "name", newname); }
        else { "Имя некорректно"; }
    }
    else if (n == 3) {
        string newsurname; cout << "Введите новое Отчество -> "; cin >> newsurname;
        if (correctName(newsurname)) { list.updateNode(updateNumber, "surname", newsurname); }
        else { "Отчество неккоректно"; }
    }
    else if (n == 4) {
        Date newdate;
        unsigned short d;
        unsigned short m;
        unsigned short y;
        cout << "Введите новый день рождения: " << endl;
        cout << "День -> "; cin >> d;
        cout << "Месяц -> "; cin >> m;
        cout << "Год -> "; cin >> y;
        if (correctDate(d, m, y))
        {
            newdate.day = d; newdate.month = m; newdate.year = y;
            list.updateDateNode(updateNumber, newdate);
        }
        else { cout << "Дата некорректна"; }
    }
    else if (n == 5) {
        string newyearAdm; cout << "Введите новый год поступления -> "; cin >> newyearAdm;
        list.updateNode(updateNumber, "yearAdm", newyearAdm);
    }
    else if (n == 6) {
        string newfaculty; cout << "Введите новый факультет -> "; cin >> newfaculty;
        list.updateNode(updateNumber, "faculty", newfaculty);
    }
    else if (n == 7) {
        string newcathedra; cout << "Введите новую кафедру -> "; cin >> newcathedra;
        list.updateNode(updateNumber, "cathedra", newcathedra);
    }
    else if (n == 8) {
        string newgroup; cout << "Введите новую группу -> "; cin >> newgroup;
        list.updateNode(updateNumber, "group", newgroup);
    }
    else if (n == 9) {
        string newsex; cout << "Введите новый пол -> "; cin >> newsex;
        list.updateNode(updateNumber, "sex", newsex);
    }
    else if (n == 10) {
        string newnumber; cout << "Введите новый номер зачетной книжки -> "; cin >> newnumber;
        list.updateNode(updateNumber, "number", newnumber);
    }
    printHead();
    list.display();
    writeListToFileStudents(list);
    HelpMenu();
} 

void updateSession() {
    DoublyLinkedListE list = readFromFileExams("exams.txt");
    cout << "Изначальный список сессий студентов"; cout << endl;
    list.display(); cout << endl;
    cout << "Введите номер зачетной книжки студента," << endl;
    cout << "данные которого Вы хотите изменить -> ";
    string updateNumber; cin >> updateNumber; cout << endl;   
    cout << endl;
    int i, j; 
    string nameExam; int mark;
    cout << "Введите номер сессии -> ";  cin >> i;
    cout << "Введите номер предмета -> "; cin >> j;
    cout << "Введите новый предмет -> ";  cin >> nameExam; 
    cout << "Введите новую оценку -> "; cin >> mark; cout << endl;
    list.updateNode(updateNumber, i, j, nameExam, mark);
    cout << "Изменённый список сессий"; cout << endl;
    list.display();
    writeListToFileExams(list);
    HelpMenu();
} 

void deleteFromFileStudents() {
    DoublyLinkedList list = readFromFileStudents("students.txt");
    cout << "Изначальный список студентов"; cout << endl;
    printHead();
    list.display(); cout << endl;  
    cout << "Введите номер зачетной книжки студента," << endl;
    cout << "которого Вы хотите удалить -> ";
    string deleteNumber; cin >> deleteNumber; cout << endl;
    list.deleteNode(deleteNumber);
    cout << "Изменённый список студентов"; cout << endl;
    list.display();
    writeListToFileStudents(list);
    HelpMenu();
}

void deleteFromFileExams() {
    DoublyLinkedListE list = readFromFileExams("exams.txt");
    cout << "Изначальный список сессий студентов"; cout << endl;
    list.display(); cout << endl;
    cout << "Введите номер зачетной книжки студента," << endl;
    cout << "которого Вы хотите удалить -> ";
    string deleteNumber; cin >> deleteNumber; cout << endl;
    list.deleteNode(deleteNumber);
    cout << "Изменённый список сессий студентов"; cout << endl;
    list.display();   
    writeListToFileExams(list);
    HelpMenu();
}

void displayFromFileStudents() {
    DoublyLinkedList list = readFromFileStudents("students.txt");
    printHead();
    list.display();
    HelpMenu();
}

void displayFromFileExams() {
    DoublyLinkedListE list = readFromFileExams("exams.txt");
    list.display();
    HelpMenu();
}

void addSessionToFile(Exams& exams, string number) {
    ofstream outFile;
    outFile.open("exams.txt", ios_base::app);
    if (!outFile) {
        cerr << "Не удается открыть файл exams.txt";
        exit(1);   
    }
    outFile << number << " ";
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 10; j++) {
            outFile << exams.getNameExam(i, j) << " " << exams.getMark(i, j) << " ";
        }       
    }
    outFile << endl;   
    outFile.close();
}

void addSession(string number) {
    Exams newExams;
    cout << "Если данных о предмете нет, то введите название '-'" << endl;
    cout << "а оценка '0'. 0 это отсутствие оценки при или 'незачет' при наличии предмета" << endl; cout << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 10; j++) {
            string nameExam;
            int mark;           
            cout << "Введите название предмета " << j + 1 << " для сессии " << i + 1<< ": ";
            cin >> nameExam;
            cout << "Введите оценку для предмета " << j + 1 << " для сессии " << i + 1 << ": ";
            cin >> mark;
            cout << endl;
            newExams.setNumber(number);
            newExams.setSession(i, j, nameExam, mark);
        }
        system("cls");
    }
    addSessionToFile(newExams, number);
    newExams.display();
    HelpMenu();
}

void addStudentToFile(StudentBase& student)
{
    ofstream outFile;
    outFile.open("students.txt", ios_base::app);
    if (!outFile) {
        cerr << "Не удается открыть файл students.txt";
        exit(1);   
    }
    outFile << student.getLastname() << " " << student.getName() << " " << student.getSurname() 
        << " " << student.getDay() << " " << student.getMonth() << " " << student.getYear() << " "
        << student.getYearAdm() << " " << student.getFaculty() << " " << student.getCathedra() << " " << student.getGroup() 
        << " " << student.getSex() << " " << student.getNumber() << endl;
    outFile.close();
}

void addStudent() {
    StudentBase newStudent;
    string newlastname;
    string newname;
    string newsurname;
    Date newdate;
    int newyearAdm;
    string newfaculty;
    string newcathedra;
    string newgroup;
    string newsex;
    string newnumber;
    unsigned short d;
    unsigned short m;
    unsigned short y;
    cout << "Введите: " << endl;
    cout << "Фамилия-> "; cin >> newlastname; cout << endl;
    if (correctName(newlastname))
    {
        cout << "Имя-> "; cin >> newname; cout << endl;
        if (correctName(newname))
        {
            cout << "Отчество-> "; cin >> newsurname; cout << endl;
            if (correctName(newsurname))
            {
                cout << "Дата рождения: " << endl;
                cout << "День-> "; cin >> d; cout << endl;
                cout << "Месяц-> "; cin >> m; cout << endl;
                cout << "Год-> "; cin >> y; cout << endl;
                if (correctDate(d, m, y))
                {
                    newdate.day = d; newdate.month = m; newdate.year = y;
                    cout << "Год поступления-> "; cin >> newyearAdm; cout << endl;
                    cout << "Факультет(например,ИКБ)-> "; cin >> newfaculty; cout << endl;
                    cout << "Кафедра(например,КБ-1)-> "; cin >> newcathedra; cout << endl;
                    cout << "Группа(в формате БББО-05-22)-> "; cin >> newgroup; cout << endl;
                    cout << "Пол(Ж или М)-> "; cin >> newsex; 
                    cout << endl;cout << "Номер зачетной книжки-> "; cin >> newnumber; cout << endl;
                    newStudent.setStudent(newlastname, newname, newsurname, newdate, newyearAdm, 
                        newfaculty, newcathedra, newgroup,
                        newsex, newnumber);
                    addStudentToFile(newStudent);
                    newStudent.display(); cout << endl;
                    cout << "Если вы хотите добавить также данные о сессии студента, нажмите 1" << endl;
                    cout << "Если данных о сессии нет,то нажмите 0" << endl;
                    int n; cin >> n; system("cls");
                    switch (n) {
                    case 0: HelpMenu(); break;
                    case 1: addSession(newnumber); break;
                    }
                }
                else {
                    cout << "Некорректная дата рождения"; cout << endl;
                }
            }
            else {
                cout << "В отчестве присутствуют посторонние символы"; cout << endl;
            }
        }
        else {
            cout << "В имени присутствуют посторонние символы"; cout << endl;
        }
    }
    else {
        cout << "В фамилии присутствуют посторонние символы"; cout << endl;
    }
}; 

void task() {
    cout << "Вариант №8:" << endl;
    cout << "Распечатать всех студентов, у которых не более 25 % " << endl;
    cout << "троек за все время обучения" << endl; cout << endl;
    DoublyLinkedListE list = readFromFileExams("exams.txt");
    cout << "Список сессий студентов" << endl; cout << endl;
    list.display();
    cout << "Номера зачетных книжок студентов, выполняющих условие задания" << endl; cout << endl;
    list.task();  
    HelpMenu();
}

void MainMenu() {
    int n;
    cout << "Введите число:" << endl; 
    cout.width(50); cout.fill('-'); cout << "-" << endl; cout.fill(' ');
    cout.width(49); cout << left << "|1 - отобразить данные о студенте"; cout << "|" << endl; cout.width(50); cout.fill('-'); cout << "-" << endl; cout.fill(' ');
    cout.width(49); cout << left << "|2 - добавить данные о студенте"; cout << "|" << endl; cout.width(50); cout.fill('-'); cout << "-" << endl; cout.fill(' ');
    cout.width(49); cout << left << "|3 - изменить данные о студенте"; cout << "|" << endl; cout.width(50); cout.fill('-'); cout << "-" << endl; cout.fill(' ');
    cout.width(49); cout << left << "|4 - удалить данные о студенте"; cout << "|" << endl; cout.width(50); cout.fill('-'); cout << "-" << endl; cout.fill(' ');
    cout.width(49); cout << left << "|5 - отобразить данные о сессиях студентов"; cout << "|" << endl; cout.width(50); cout.fill('-'); cout << "-" << endl; cout.fill(' ');
    cout.width(49); cout << left << "|6 - удалить данные о сессии студента"; cout << "|" << endl; cout.width(50); cout.fill('-'); cout << "-" << endl; cout.fill(' ');
    cout.width(49); cout << left << "|7 - добавить данные о сессиях студента"; cout << "|" << endl; cout.width(50); cout.fill('-'); cout << "-" << endl; cout.fill(' ');
    cout.width(49); cout << left << "|8 - изменить данные о сессии студента"; cout << "|" << endl; cout.width(50); cout.fill('-'); cout << "-" << endl; cout.fill(' ');
    cout.width(49); cout << left << "|9 - выполнить задание №8"; cout << "|" << endl; cout.width(50); cout.fill('-'); cout << "-" << endl; cout.fill(' ');
    cout.width(49); cout << left << "|0 - выйти"; cout << "|" << endl; cout.width(50); cout.fill('-'); cout << "-" << endl; cout.fill(' ');
    cout << endl;
    cin >> n; system("cls");
    string number;
    switch (n)
    {
    case 1: cout << "Данные из файла" << endl; displayFromFileStudents(); break;
    case 2: cout << "Добавим данные о студенте" << endl; addStudent(); break;
    case 3: updateStudent(); break;
    case 4: deleteFromFileStudents(); break;
    case 5: displayFromFileExams(); break;
    case 6: deleteFromFileExams(); break;
    case 7:  cout << "Введите номер зачетной книжки студента -> "; cin >> number; 
        cout << endl; addSession(number); break;
    case 8: updateSession(); break;
    case 9: task(); break;
    case 0: cout << "Закрытие программы..." << endl;  flag_of_end = false; break;
    default: cout << "Неверное число. Повторите попытку..." << endl;
    }
}

void Crypt()
{
    srand(time(NULL));
    char* pass = new char[65];
    for (int i = 0; i < 64; ++i) {
        switch (rand() % 3) {
        case 0:
            pass[i] = rand() % 10 + '0';
            break;
        case 1:
            pass[i] = rand() % 26 + 'A';
            break;
        case 2:
            pass[i] = rand() % 26 + 'a';
            break;
        }
    }
    pass[64] = '\0';
    string command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -pbkdf2 -salt -in students.txt -out students.txt.enc -pass pass:";
    command += pass;
    system(command.c_str());
    if (remove("students.txt") != 0) {
        cout << "Ошибка удаления НЕзашифрованной базы данных!" << endl;
    }
    ofstream file;
    file.open("key.txt", ios::binary);
    file.write(pass, 64);
    file.close();
    command = "openssl\\bin\\openssl.exe rsautl -encrypt -inkey rsa.public -pubin -in key.txt -out key.txt.enc";
    system(command.c_str());
    if (remove("key.txt") != 0) {
        cout << "Ошибка удаление пароля для шифрования базы данных!" << endl;
    }
    cout << "Шифрование файла о студентах прошло успешно" << endl;
    delete[] pass;
}

void Decrypt()
{
    string command = "openssl\\bin\\openssl.exe rsautl -decrypt -inkey rsa.private -in key.txt.enc -out key.txt";
    system(command.c_str());
    if (remove("key.txt.enc") != 0) {
        cout << "Ошибка удаления зашифрованного пароля для дешифрования базы данных!" << endl;
    }
    char* pass = new char[65];
    ifstream file;
    file.open("key.txt", ios::binary);
    file.read(pass, 64);
    file.close();
    pass[64] = '\0';
    if (remove("key.txt") != 0) {
        cout << "Ошибка удаления пароля для дешифрования базы данных!" << endl;
    }
    command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -d -pbkdf2 -in students.txt.enc -out students.txt -pass pass:";
    command += pass;
    system(command.c_str());
    if (remove("students.txt.enc") != 0) {
        cout << "Ошибка удаления зашифрованной базы данных!" << endl;
    }
    delete[] pass;
    cout << "Дешифрование файла о студентах прошло успешно" << endl;
}
void CryptE()
{
    srand(time(NULL));
    char* pass = new char[65];
    for (int i = 0; i < 64; ++i) {
        switch (rand() % 3) {
        case 0:
            pass[i] = rand() % 10 + '0';
            break;
        case 1:
            pass[i] = rand() % 26 + 'A';
            break;
        case 2:
            pass[i] = rand() % 26 + 'a';
            break;
        }
    }
    pass[64] = '\0';
    string command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -pbkdf2 -salt -in exams.txt -out exams.txt.enc -pass pass:";
    command += pass;
    system(command.c_str());
    if (remove("exams.txt") != 0) {
        cout << "Ошибка удаления НЕзашифрованной базы данных!" << endl;
    }
    ofstream file;
    file.open("keyE.txt", ios::binary);
    file.write(pass, 64);
    file.close();
    command = "openssl\\bin\\openssl.exe rsautl -encrypt -inkey rsa.public -pubin -in keyE.txt -out keyE.txt.enc";
    system(command.c_str());
    if (remove("keyE.txt") != 0) {
        cout << "Ошибка удаление пароля для шифрования базы данных!" << endl;
    }
    cout << "Шифрование файла с сессиями прошло успешно" << endl;
    delete[] pass;
}

void DecryptE()
{
    string command = "openssl\\bin\\openssl.exe rsautl -decrypt -inkey rsa.private -in keyE.txt.enc -out keyE.txt";
    system(command.c_str());
    if (remove("keyE.txt.enc") != 0) {
        cout << "Ошибка удаления зашифрованного пароля для дешифрования базы данных!" << endl;
    }
    char* pass = new char[65];
    ifstream file;
    file.open("keyE.txt", ios::binary);
    file.read(pass, 64);
    file.close();
    pass[64] = '\0';
    if (remove("keyE.txt") != 0) {
        cout << "Ошибка удаления пароля для дешифрования базы данных!" << endl;
    }
    command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -d -pbkdf2 -in exams.txt.enc -out exams.txt -pass pass:";
    command += pass;
    system(command.c_str());
    if (remove("exams.txt.enc") != 0) {
        cout << "Ошибка удаления зашифрованной базы данных!" << endl;
    }
    delete[] pass;
    cout << "Дешифрование файла с сессиями прошло успешно" << endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    //Decrypt(); DecryptE();
    while (flag_of_end) {             
        MainMenu();
    }
    //Crypt(); CryptE();
}
