/*
Name: Ravi Teja Nitta
File: studentlist.h
*/

#include <fstream>

class Student {

	public:
		Student(char* lname, char* fname, char* sub);	//Constructor
		char* getfname();			//Returns first name
		char* getlname();			//Returns last name
		char* getSubject();			//Returns subject 
		virtual double compute() const = 0;	//Placeholder for different compute functions
		virtual int getExam() const = 0;	//Placeholder for different exam getters
		virtual char letterGrade() const = 0;
	protected:
		//Stores the name/subject of each student
		char first_name[21];
		char last_name[21];
		char subject[8];

};

class English : public Student {

	public:
		//Constructor
		English(char* lname, char* fname, int att, int pro, int mid, int ex, char* sub);
		double compute() const;			//Computes final english grade
		int getExam() const;			//Returns english exam grade
		char letterGrade() const;		//Returns letter grade
	private:
		//Stores major assignment grades in english
		int attendance;
		int project;
		int midterm;
		int exam;

};

class History : public Student {

	public:
		//Constructor
		History(char* lname, char* fname, int pap, int mid, int ex, char* sub);
		double compute() const;			//Computes final history grade
		int getExam() const;			//Returns history exam grade
		char letterGrade() const;		//Returns letter grade
	private:
		//Stores major assignment grades in history
		int paper;				
		int midterm;
		int exam;

};

class Math : public Student {
	
	public:
		//Constructor 
		Math(char* lname, char* fname, int one, int two, int three, int four, int five, int t1, int t2, int ex, char* sub); 
		double compute() const;			//Computes final math grade
		int getExam() const;			//Returns math exam grade
		char letterGrade() const ;		//Returns letter grade
	private:
		//Stores major assignment grades in math
		double quiz_avg;
		int test1;
		int test2;
		int exam;
}; 

class StudentList {

	public:
		StudentList();		//starts out empty
		~StudentList();		//cleanup (destructor)

		bool ImportFile(const char* filename);
		bool CreateReportFile(const char* filename);
		void ShowList() const;	//print basic list data
		void sort();		//Sorts list in alphabetical order

	private:
		Student** list;		//Stores the array of students
		int size;		//Keeps track of the size of the array
		void array_change(int s);	//Resizes the array of students;

};
