# Student-Grade-Analyzer
A C++ program that stores student objects and allows for various statistics to be shown about their academics

The information for each student is embedded in a Student object which has 3 child classes: Math, English, and History.
These 3 child classes account for the differences in grading for each subject, and all of them are stored in a StudentList
object through the utilization of polymorphism. As a result, once a single StudentList object is created, it can import
data through a file that creates a corresponding student object depending on a specific student's subject

Once all of the data has been fed in through a file (in the format of test1.txt), a report showing the final grades of 
a student given the assignments of a class is calculated and can be displayed (alphabetically if desired through the 
.sort() method). The specific weights for this implementation are

      - History: 25% paper, 35% midterm exam, 40% final exam
      - Math: 15% quiz average (6 quizzes), 25% test 1, 25% test 2, 35% final exam 
      - English: 10% attendance, 30% project, 30% midterm exam, 30% final exam

There is also a main program (main.cpp) that illustrates the functionality of all the features of the StudentList object
