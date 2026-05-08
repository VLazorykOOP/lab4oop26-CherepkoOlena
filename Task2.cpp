//
// Created by acer_ on 07.05.2026.
//

#include "Task2.h"
#include <iostream>
#include <string>

using namespace std;

struct StudentRecord {
    int id;
    string fullName;
};

class GroupDictionary {
    private:
        StudentRecord* records;
        int size;
        int capacity;


    void resize() {
        capacity *= 2;
        StudentRecord* newRecords = new StudentRecord[capacity];
        for (int i = 0; i < size; i++) {
            newRecords[i] = records[i];
        }
        delete[] records;
        records = newRecords;
    }

public:
    int CodeError;

    GroupDictionary(int cap = 10) : size(0), capacity(cap), CodeError(0) {
        records = new StudentRecord[capacity];
    }

    ~GroupDictionary() {
        delete[] records;
    }


    void addRecord(int id, const string& name) {
        if (size >= capacity) {
            resize();
        }
        records[size].id = id;
        records[size].fullName = name;
        size++;
    }

    string operator[](int id) {
        CodeError = 0;
        for (int i = 0; i < size; i++) {
            if (records[i].id == id) {
                return records[i].fullName;
            }
        }

        CodeError = 1;
        return "Error 1";
    }

    string operator()(int id) {
        CodeError = 0;
        for (int i = 0; i < size; i++) {
            if (records[i].id == id) {
                return records[i].fullName;
            }
        }
        CodeError = 1;
        return "Error 1";
    }


    friend ostream& operator<<(ostream& out, const GroupDictionary& dict) {
        if (dict.size == 0) {
            out << "empty list\n";
            return out;
        }
        out << "Group list\n";
        for (int i = 0; i < dict.size; i++) {
            out << dict.records[i].id << ". " << dict.records[i].fullName << "\n";
        }
        return out;
    }

    friend istream& operator>>(istream& in, GroupDictionary& dict) {
        int id;
        string name;
        cout << "Enter ID: ";
        in >> id;

        cout << "Enter full name: ";
        getline(in, name);

        dict.addRecord(id, name);
        return in;
    }
};


void Task2() {

    GroupDictionary group;

    group.addRecord(1, "Mykhailenko Serhii Igorovich");
    group.addRecord(2, "Babich Anastasiya Ryslanivna");
    group.addRecord(5, "Cherepko Olena Oleksandrivna");
    group.addRecord(8, "Zozulya Darina Vyacheslavivna");

    cout << group << endl;

    cout << "Find student 2: " << group[2] << endl;
    cout << "CodeError: " << group.CodeError << "\n" << endl;

    cout << "Find student 5: " << group(5) << endl;
    cout << "CodeError: " << group.CodeError << "\n" << endl;

    cout << "Find student 10 to get error: " << group[10] << endl;
    cout << "CodeError: " << group.CodeError << endl;

    cout << "Add new student:" << endl;
    cin >> group;

    cout << "\nNew list " << group;
}