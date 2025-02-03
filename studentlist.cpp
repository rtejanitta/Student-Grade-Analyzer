/*
Name: Ravi Teja Nitta
File: studentlist.cpp
*/

#include "studentlist.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

StudentList::StudentList(){		//starts out empty

	size = 0;
}

StudentList::~StudentList(){		//cleanup (destructor)

	if (size != 0) {		//makes sure list is only deallocated if it was allocated previously

		for (int i = 0; i < size;i++) {	//Deletes individual student objects
			delete list[i];		
		}

		delete[] list;			//Deletes array 
		size = 0;
	}

}

bool StudentList::ImportFile(const char* filename){

	 
	int iterations;				//Keeps track of how many students need to be read in
	char fname[21];				//Holds first name 
	char lname[21];				//Holds last name
	char subject[8];			//Holds class type
	Student* temp;				//Temporary variable to be used in obtaining addresses of new student objects

	//Opening file 
	ifstream fin;
	
	if (!filename)				//Aborts function if filename is invalid		
		return false;

	fin.open(filename);

	//Determining how many students are in the file
	fin >> iterations;
	int oldsize = size;			//Keeps track of previous size
	array_change(size + iterations);	//Making sure previous imports are saved

	for (int i = oldsize; i < size; i++) {

		fin.ignore();				//Ignores newline

		//Getting first/last name 
		fin.getline(lname,21,',');
		fin.ignore();				//ignores space
		fin.getline(fname,21, '\n');	

		fin >> subject;				//reads in subject
		//Read in specifications for if the class is math
		if (strcmp(subject,"Math") == 0) {
		
			//declaring variables for information to be read into 
			int quizzes[5];			//Array to save quizzes
			int t1, t2, final;
		
			//Reading in data
			for (int j = 0; j < 5; j++) {	
				fin >> quizzes[j];
			}
	
			fin >> t1 >> t2 >> final;
			//Creating Math object with data
			temp = new  Math(lname,fname,quizzes[0],quizzes[1],quizzes[2],quizzes[3],quizzes[4],t1,t2,final,subject);	
			list[i] = temp;
		}

		//Read in specifications for if the class is history
		else if (strcmp(subject,"History") == 0) {
				
			//Reading in data
			int paper, midterm, exam;
			fin >> paper >> midterm >> exam;
			//Creating History object with data
			temp = new History(lname,fname,paper,midterm,exam,subject);
			list[i] = temp;
		}

		//Read in specifications for if the class is english
		else {
			
			//Reading in data
			int attendance, project, midterm, exam;
			fin >> attendance >> project >> midterm >> exam;
			//Creating English object with data
			temp = new English(lname,fname,attendance,project,midterm,exam,subject);
			list[i] = temp;	
		}		
	
	}

	//Closes file and returns true if filename is valid
	fin.close();
	return true;

}

bool StudentList::CreateReportFile(const char* filename){

	int distribution[5] = {0};				//Stores how many students had each of the five letter grades
	char letter_grades[5] = {'A','B','C','D','F'};		//Used in future loop to simplify printout

	//Opening write file 
	ofstream fout;		

	if (!filename) 						//returns false if file cannot be opened
		return false;

	fout.open(filename);

	ios_base::fmtflags oldflags = fout.flags();		//Saving old flags

	//Setting formatting rules
	fout.setf(ios::left);
	fout << fixed << showpoint;
	fout.precision(2);

	//Printing file header
	fout << "Student Grade Summary\n";
	fout << "---------------------\n\n";

	//English printout
	fout << "ENGLISH CLASS\n\n";
	fout << setw(40) << "Student" << setw(8) << "Final" << setw(8) << "Final" << "Letter" << '\n';
	fout <<  setw(40) << "Name" << setw(8) << "Exam" << setw(8) << "Avg" << "Grade" << '\n';
	fout << "----------------------------------------------------------------------\n";

	for (int i = 0;i < size;i++) {

		if (strcmp(list[i]->getSubject(),"English") == 0){
	
			//Connecting firstname, space, and last name in a temporary variable
			char temp[strlen(list[i]->getfname()) + strlen(list[i]->getlname()) + 2];
			strcpy(temp,list[i]->getfname());
			strcat(temp, " ");
			strcat(temp,list[i]->getlname());

			fout << setw(40) << temp << setw(8) << list[i]->getExam() << setw(8) << list[i]->compute() << list[i]->letterGrade() << '\n';
			 	
		}
	}

	//History Printout 	
	fout << "\n\nHISTORY CLASS\n\n";
	fout << setw(40) << "Student" << setw(8) << "Final" << setw(8) << "Final" << "Letter" << '\n';
	fout <<  setw(40) << "Name" << setw(8) << "Exam" << setw(8) << "Avg" << "Grade" << '\n';
	fout << "----------------------------------------------------------------------\n";

	for (int i = 0;i < size;i++) {

		if (strcmp(list[i]->getSubject(),"History") == 0){
						
			//Connecting firstname, space, and last name in a temporary variable
			char temp[strlen(list[i]->getfname()) + strlen(list[i]->getlname()) + 2];
			strcpy(temp,list[i]->getfname());
			strcat(temp, " ");
			strcat(temp,list[i]->getlname());

			fout << setw(40) << temp << setw(8) << list[i]->getExam() << setw(8) << list[i]->compute() << list[i]->letterGrade() << '\n';
			 	
		}
	}
	
	//Math Printout
	fout << "\n\nMATH CLASS\n\n";
	fout << setw(40) << "Student" << setw(8) << "Final" << setw(8) << "Final" << "Letter" << '\n';
	fout <<  setw(40) << "Name" << setw(8) << "Exam" << setw(8) << "Avg" << "Grade" << '\n';
	fout << "----------------------------------------------------------------------\n";

	for (int i = 0;i < size;i++) {

		if (strcmp(list[i]->getSubject(), "Math") == 0){

			//Connecting firstname, space, and last name in a temporary variable
			char temp[strlen(list[i]->getfname()) + strlen(list[i]->getlname()) + 2];
			strcpy(temp,list[i]->getfname());
			strcat(temp, " ");
			strcat(temp,list[i]->getlname());

			fout << setw(40) << temp << setw(8) << list[i]->getExam() << setw(8) << list[i]->compute() << list[i]->letterGrade() << '\n';
 	
		}
	}

	//Grade Distribution Calculator
	for (int i = 0;i < size;i++) {
		
		char letter = list[i]->letterGrade();	//stores letter grade in temporary variable
		
		//Adjusts grade distribution accordingly
		switch (letter)	{

			case 'A':
				distribution[0]++;
				break;
			case 'B':
				distribution[1]++;
				break;
			case 'C':
				distribution[2]++;
				break;
			case 'D':
				distribution[3]++;
				break;
			case 'F':
				distribution[4]++;
				break;
		}
	}
	
	//Printing grade distribution
	fout << "\n\nOVERALL GRADE DISTRIBUTION\n\n";
	
	for (int i = 0; i < 5; i++) {
		fout << letter_grades[i] << ":\t" << distribution[i] << '\n';
	}

	//Resetting flags and closing file
	fout.setf(oldflags);
	fout.close();

	return true;					//returns true to show that the contents have been written to the file
}

void StudentList::ShowList() const{	//print basic list data

	//Saving old flags and setting printout to left justify 
	ios_base::fmtflags oldflags = cout.flags();
	cout.setf(ios::left);

	cout << '\n' << setw(21) << "Last" << setw(21) << "First" << "Course" << "\n\n";	//Printing header
	
	//Prints the name and subject of each student
	for (int i = 0; i < size; i++) {

		cout << setw(21) << list[i]->getlname() << setw(21) << list[i]->getfname() << list[i]->getSubject() << '\n';
	}
	
	cout.setf(oldflags);									//Resetting cout to old flags

}

void StudentList::array_change(int s){	//Changes the size of the array

	//Creating a new array of size s for a new file
	Student** temp = new Student*[s];

	for (int i = 0; i < size; i++) {							//Copying data
		temp[i] = list[i];
	}

	if (size != 0)	{									//Makes sure array is only deallocated if it has previously been allocated
		
		delete[] list;									//Deletes array	if (size = 0)
	}
	
	list = temp;
	temp = 0;
	size = s;
	
}

void StudentList::sort() {

	int first = 0;										//Holds the index of the first alphabetical element

	for (int i = 0; i < size - 1; i++) {
		
		int first = i;									//Initializes to the current element

		for (int j = i; j < size; j++) {						//Goes through every element in the list 
		
			if (strcmp(list[first]->getlname(), list[j]->getlname()) > 0) 		//Compares only last names
				first = j;


			else if (strcmp(list[first]->getlname(), list[j]->getlname()) == 0) {	//Checks first names if last names are the same
				
				if (strcmp(list[first]->getfname(),list[j]->getlname()) > 0)
					first = j;			

			}
			
		} 	
		
		Student* temp = list[i];							//Swaps current element with first alphabetical element found above
		list[i] = list[first];
		list[first] = temp;			
	
	}
}

Student::Student(char* lname, char* fname, char* sub){	//Constructor
	
	strcpy(last_name, lname);
	strcpy(first_name, fname);
	strcpy(subject,sub);
}

char* Student::getfname() {			 //Returns first name		
	return first_name;
}

char* Student::getlname(){			//Returns last name 
	return last_name;
}

char* Student::getSubject() {			//Returns subject
	return subject;
}
		
//Constructor
English::English(char* lname, char* fname, int att, int pro, int mid, int ex, char* sub) : Student(lname, fname, sub){

	attendance = att;
	project = pro;
	midterm = mid;
	exam = ex; 
}
		
double English::compute() const{			//Computes final english grade
	return ((0.1 * attendance) + (0.3 * project) + (0.3 * midterm) + (exam * 0.3));	
}

int English::getExam() const{			//Returns english exam grade
	return exam;
}

char English::letterGrade() const{

	double percentage = compute();		//Saves the student's final grade average
	
	//Returns letter grade based on final grade average
	if (percentage > 90) 
		return 'A';
	else if (percentage > 80 && percentage < 90)
		return 'B';
	else if (percentage > 70 && percentage < 80)
		return 'C';
	else if (percentage > 60 && percentage < 70)
		return 'D';
	else
		return 'F';
}

//Constructor
History::History(char* lname, char* fname, int pap, int mid, int ex, char* sub) : Student(lname, fname, sub){

	paper = pap;
	midterm = mid;
	exam = ex;
}
		
double History::compute() const{			//Computes final history grade
	return ((0.25 * paper) + (0.35 * midterm) + (0.4 *exam));
}

int History::getExam() const{			//Returns history exam grade
	return exam;
}

char History::letterGrade() const{

	double percentage = compute();		//Stores student's final grade avg
	
	//Returns letter grade based on final grade average
	if (percentage > 90) 
		return 'A';
	else if (percentage > 80 && percentage < 90)
		return 'B';
	else if (percentage > 70 && percentage < 80)
		return 'C';
	else if (percentage > 60 && percentage < 70)
		return 'D';
	else
		return 'F';
}

//Constructor 
Math::Math(char* lname, char* fname, int one, int two, int three, int four, int five, int t1, int t2, int ex, char* sub) : Student(lname, fname, sub){

	exam = ex;
	test1 = t1;
	test2 = t2;
	quiz_avg = (one + two + three + four + five) / 5.0; 
}
		
double Math::compute() const{			//Computes final math grade
	return ((0.15 * quiz_avg) + (0.25 * test1) + (0.25 * test2) + (0.35 * exam));
}
		
int Math::getExam() const{			//Returns math exam grade
	return exam;
}

char Math::letterGrade() const{

	double percentage = compute();		//Stores student's final grade avg

	//Returns letter grade based on final grade average
	if (percentage > 90) 
		return 'A';
	else if (percentage > 80 && percentage < 90)
		return 'B';
	else if (percentage > 70 && percentage < 80)
		return 'C';
	else if (percentage > 60 && percentage < 70)
		return 'D';
	else
		return 'F';
}



