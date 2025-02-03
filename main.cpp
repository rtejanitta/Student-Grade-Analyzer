/*
Name: Ravi Teja Nitta
Filename: main.cpp
*/

#include <iostream>
#include <cctype>
#include "studentlist.h"

using namespace std;

void menu();

int main() {

	char response;
	char filename[30];

	StudentList students;

	menu();

	do {
		cout << "\nEnter your menu selection: ";
		cin >> response;
		response = toupper(response);

		switch (response) {

			case 'I':
				cout << "Please enter a read file: ";
				cin >> filename;

				while (students.ImportFile(filename) == false) {
					cout << "Invalid filename. Please try again: ";
					cin >> filename;
				}
				break;
			case 'S':
				students.ShowList();
				break;
			case 'E':
				cout << "Please enter a write file: ";
				cin >> filename;
	
				while(students.CreateReportFile(filename) == false){
					cout << "Invalid filename. Please try again: ";
					cin >> filename;
				}
				break;
			case 'M':
				menu();
				break;
			case 'O':
				students.sort();
				break;
			case 'Q':
				break;
		}
				

	}

	while (response != 'Q');	
}

void menu(){
	
	//Prints menu
	cout << "\n \t*** Student List menu ***\n\n";
	cout << "I\t Import students from a file\n";
	cout << "S\t Show student list (brief)\n";
	cout << "E\t Export a grade report (to file)\n";
	cout << "O\t sOrt student list\n";
	cout << "M\t Show this Menu\n";	
	cout << "Q\t Quit Program\n";
}
