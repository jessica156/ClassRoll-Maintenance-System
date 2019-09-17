#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>

/* Program that functions as a small class-roll maintenance system. 
For each student, the follow data is included: 
-	Name (up to 40 characters)
-	USF ID (10 characters)
-	Email (up to 40 characters)
-	Grade of the presentation (numerical value from 0 (F) to 4 (A))
-	Grade of essay (numerical value from 0 (F) to 4 (A))
-	Grade of the term project (numerical value from 0 (F) to 4 (A))

This class-roll maintenace system function with the assumption that every different student will have a unique USF ID.
The student data is read from and written to a text file called class_roll.txt.
When updating the class-roll through the console, remember to print out to the text file before exiting the program to
get the updated class-roll in the text file.
*/


using namespace std;
enum searchOption { studentName, studentUSF_ID, studentEmail };


struct studentData {
	string name;
	string USF_ID;
	string email;
	float present_grade;
	float essay_grade;
	float project_grade;
	bool empty;
	friend std::ostream& operator<<(std::ostream& os, studentData& s) {
		 os << left << setw(26) << setfill(' ') << s.name
			<< left << setw(26) << setfill(' ') << s.USF_ID
			<< left << setw(26) << setfill(' ') << s.email
			<< left << setw(26) << setfill(' ') << s.present_grade
			<< left << setw(26) << setfill(' ') << s.essay_grade
			<< left << setw(26) << setfill(' ') << s.project_grade
			<< endl;
		return os;
	}
	studentData() { empty = true; };
};


//Functions declaration
studentData addStudent();
void deleteStudent(vector<studentData> &class_roll);
void read(vector<studentData> &class_roll);
void write(vector<studentData> &class_roll);
void updateStudentData(vector<studentData> &class_roll);
void retrieveStudentData(vector<studentData> &class_roll);
vector<studentData>::iterator search(vector<studentData> &class_roll, string value, searchOption option);


int main() {
	vector<studentData> class_roll;
	studentData newStudent;
	int option = 0;
	unsigned int i = 0;
	bool exists = false;
	
	//Provide options and prompt the user to choose one
	//Keep looping until the user choose the exit option at which point exit the for loop and close the program
	for (;;) {
		cout << "Option List:" << endl;
		cout << "1 - Add a student" << endl;
		cout << "2 - Delete a student" << endl;
		cout << "3 - Read student data" << endl;
		cout << "4 - Write student data" << endl;
		cout << "5 - Update student data" << endl;
		cout << "6 - Retrieve student data based on search by name, ID, or email" << endl;
		cout << "7 - Exit Program" << endl;
		cout << "Please provide the number of the option you want to choose." << endl;
		cin >> option;

		//Checking to make sure the option input is valid
		if (!cin) {
			cout << "Not a valid option!" << endl << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		switch (option) {
			case 1:
				newStudent = addStudent();
				//Check to make sure that the student does not already exist in the system by USF ID
				for (i = 0; i < class_roll.size(); i++) {
					if (class_roll[i].USF_ID == newStudent.USF_ID) {
						cout << "Student with that USF ID already exists in system!" << endl << endl;
						exists = true;
						break;
					}
				}
				//Add the student to the system if the student is not already in there
				if (!exists) {
					class_roll.push_back(newStudent);
					cout << "New student added!" << endl << endl;
				}
				exists = false;
				break;
			
			case 2:
				if (class_roll.size() != 0)
					deleteStudent(class_roll);
				else
					cout << "No student in class-roll system!" << endl << endl;

				break;
			
			case 3:
				read(class_roll);
				break;
			
			case 4:
				write(class_roll);
				break;
			
			case 5:
				if (class_roll.size() != 0)
					updateStudentData(class_roll);
				else
					cout << "No student in class-roll system!" << endl << endl;

				break;
			
			case 6:
				if (class_roll.size() != 0)
					retrieveStudentData(class_roll);
				else
					cout << "No student in class-roll system!" << endl << endl;

				break;
			
			case 7: 
				break;
			
			default:
				cout << "Not a valid option!" << endl << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		if (option == 7)
			break;
	}

	return 0;
}


//Function to add student
studentData addStudent() {
	studentData newStudent;
	
	//Get student's name
	cout << endl << "Please enter student's name. The student's name can only be up to 40 characters long." << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, newStudent.name);
	//Ensure that it is no more than 40 characters
	while (newStudent.name.size() > 40) {
		cout << "Student's name can only be up to 40 characters. Please re-enter a valid name." << endl;
		getline(cin, newStudent.name);
	}

	//Get student's USF ID
	cout << "Please enter student's USF ID. The USF ID needs to be 10 characters long." << endl;
	cin >> newStudent.USF_ID;
	//Ensure that it is 10 characters
	while (newStudent.USF_ID.size() != 10) {
		cout << "Student's USF ID needs to be 10 characters. Please re-enter a valid USF ID." << endl;
		cin >> newStudent.USF_ID;
	}

	//Get student's email
	cout << "Please enter student's email. The student's email can only be up to 40 characters long." << endl;
	cin >> newStudent.email;
	//Ensure that it is no more than 40 characters
	while (newStudent.email.size() > 40) {
		cout << "Student's email can only be up to 40 characters. Please re-enter a valid email." << endl;
		cin >> newStudent.email;
	}

	// Get student's presentation grade
	cout << "Please enter student's grade of the presentation. Enter grade from 0-4." << endl;
	//Ensure that grade is a numerical value and from 0 - 4
	while (true) {
		cin >> newStudent.present_grade;
		if (!cin)
		{
			cout << "Grade should be a numerical value!" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		if (newStudent.present_grade < 0 || newStudent.present_grade > 4)
		{
			cout << "Grade can only be from 0 to 4. Please re-enter a valid grade." << endl;
			continue;
		}
		break;
	}

	// Get student's essay grade
	cout << "Please enter student's grade of the essay. Enter grade from 0-4." << endl;
	//Ensure that grade is a numerical value and from 0 - 4
	while (true) {
		cin >> newStudent.essay_grade;
		if (!cin)
		{
			cout << "Grade should be a numerical value!" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		if (newStudent.essay_grade < 0 || newStudent.essay_grade > 4)
		{
			cout << "Grade can only be from 0 to 4. Please re-enter a valid grade." << endl;
			continue;
		}
		break;
	}

	// Get student's term project grade
	cout << "Please enter student's grade of the term project. Enter grade from 0-4." << endl;
	//Ensure that grade is a numerical value and from 0 - 4
	while (true) {
		cin >> newStudent.project_grade;
		if (!cin)
		{
			cout << "Grade should be a numerical value!" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		if (newStudent.project_grade < 0 || newStudent.project_grade > 4)
		{
			cout << "Grade can only be from 0 to 4. Please re-enter a valid grade." << endl;
			continue;
		}
		break;
	}

	newStudent.empty = false;

	return newStudent;
}

//Function to read data
void read(vector<studentData> &class_roll) {
	ifstream inFile;
	string line;
	studentData newStudent;
	string firstName, lastName, tempName, USF_ID, email;
	float present_grade, essay_grade, project_grade;
	unsigned int i = 0;
	bool ID_exist = false;

	inFile.open("class_roll.txt");

	// Check to make sure file open correctly
	if (!inFile)
	{
		cout << "Error: Unable to open input file!" << endl;
		return;		// Terminate the program with error
	}

	//Get rid of the first line of the text file
	getline(inFile, line);

	//Read in the student data and store into the vector of structs
	while (getline(inFile, line)) {
		istringstream line_stream(line);
		line_stream >> firstName >> lastName >> USF_ID >> email >> present_grade >> essay_grade >> project_grade;
		tempName = firstName + ' ' + lastName;

		//Check to make sure that the USF ID is not already in the system
		for (i = 0; i < class_roll.size(); i++) {
			if (class_roll[i].USF_ID == USF_ID) {
				ID_exist = true;
				break;
			}
		}

		//Add student if the USF ID is not in the system
		if (!ID_exist) {
			newStudent.name = tempName;
			newStudent.USF_ID = USF_ID;
			newStudent.email = email;
			newStudent.present_grade = present_grade;
			newStudent.essay_grade = essay_grade;
			newStudent.project_grade = project_grade;
			newStudent.empty = false;
			class_roll.push_back(newStudent);
		}
		else {
			cout << "Student with USF ID " << USF_ID << " from text file already exists in the system." << endl << endl;
			ID_exist = false;
		}
	}

	cout << "Done reading in student data from text file." << endl << endl;

	//Close file
	inFile.close();
}

//Function to write data
void write(vector<studentData> &class_roll) {
	//Creating an output text file to output the converted MIDI data 
	ofstream outfile;
	outfile.open("class_roll.txt");
	outfile << left << setw(26) << setfill(' ') << "Name"
		<< left << setw(26) << setfill(' ') << "USF_ID"
		<< left << setw(26) << setfill(' ') << "Email"
		<< left << setw(26) << setfill(' ') << "Present Grade"
		<< left << setw(26) << setfill(' ') << "Essay Grade"
		<< left << setw(26) << setfill(' ') << "Project Grade"
		<< endl;
	//Put student data out to text file
	auto iter = class_roll.begin();
	while (iter != class_roll.end()) {
		outfile << *iter;
		iter++;
	}

	cout << "Student data printed to class_roll.txt" << endl << endl;

	//Close file
	outfile.close();
}

//Function to delete student
void deleteStudent(vector<studentData> &class_roll) {
	string USF_ID;

	//Get the USF_ID of the student that needs to be deleted
	cout << endl << "Please enter the USF ID of the student that needs to be deleted. The USF ID needs to be 10 characters long." << endl;
	cin >> USF_ID;

	//Ensure that it is 10 characters
	while (USF_ID.length() != 10) {
		cout << "Student's USF ID needs to be 10 characters. Please re-enter a valid USF ID." << endl;
		cin >> USF_ID;
	}

	//Find the student to delete
	auto iter = find_if(class_roll.begin(), class_roll.end(), [&](const studentData &class_roll) {
		return class_roll.USF_ID == USF_ID; }
	);

	//Delete the student if the student is in the system
	if (iter == class_roll.end()) {
		cout << "Student does not exists in the system. Nothing to delete." << endl << endl;
	}
	else {
		class_roll.erase(iter);
		cout << "Student has been deleted!" << endl << endl;
	}
}

//Function to update student data
void updateStudentData(vector<studentData> &class_roll) {
	string searchID, name, USF_ID, email;
	float present_grade, essay_grade, project_grade;
	int option = 0;
	unsigned int i = 0;
	bool ID_exist = false, flag = false;
	vector<studentData>::iterator student;

	//Get the USF_ID of the student that needs to be updated
	cout << endl << "Please enter the USF ID of the student that needs to be updated. The USF ID needs to be 10 characters long." << endl;
	cin >> searchID;

	//Ensure that it is 10 characters
	while (searchID.length() != 10) {
		cout << "Student's USF ID needs to be 10 characters. Please re-enter a valid USF ID." << endl;
		cin >> searchID;
	}

	//Search for the student to update
	student = search(class_roll, searchID, studentUSF_ID);

	//Check to see if student was find and print out data if it exists
	if (student != class_roll.end()) {
		cout << "Student to Update:" << endl;
		cout << "Name: " << student->name << endl;
		cout << "USF ID: " << student->USF_ID << endl;
		cout << "Email: " << student->email << endl;
		cout << "Presentation Grade: " << student->present_grade << endl;
		cout << "Essay Grade: " << student->essay_grade << endl;
		cout << "Project Grade: " << student->project_grade << endl << endl;
	}
	else {
		cout << "Student was not found in the system!" << endl << endl;
		return;
	}

	//Update student data
	for (;;) {
		cout << endl << "Option List:" << endl;
		cout << "1 - Name" << endl;
		cout << "2 - USF ID" << endl;
		cout << "3 - Email" << endl;
		cout << "4 - Presentation Grade" << endl;
		cout << "5 - Essay Grade" << endl;
		cout << "6 - Project Grade" << endl;
		cout << "7 - Done" << endl;
		cout << "Please provide what to update." << endl;
		cin >> option;

		//Checking to make sure the option input is valid
		if (!cin) {
			cout << "Not a valid option!" << endl << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		switch (option) {
		case 1:
			//Get student's name
			cout << "Please enter student's name. The student's name can only be up to 40 characters long." << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, name);

			//Ensure that it is no more than 40 characters
			while (name.length() > 40) {
				cout << "Student's name can only be up to 40 characters. Please re-enter a valid name." << endl;
				cin >> name;
			}

			//Update name
			student->name = name;

			break;

		case 2:
			//Get student's USF ID
			cout << "Please enter student's USF ID. The USF ID needs to be 10 characters long." << endl;
			cin >> USF_ID;

			//Ensure that it is 10 characters
			while (USF_ID.length() != 10) {
				cout << "Student's USF ID needs to be 10 characters. Please re-enter a valid USF ID." << endl;
				cin >> USF_ID;
			}

			//Check to make sure that the USF ID is not already in the system
			for (i = 0; i < class_roll.size(); i++) {
				if (class_roll[i].USF_ID == USF_ID) {
					cout << "USF ID already exists in system!" << endl << endl;
					ID_exist = true;
					break;
				}
			}

			//Update USF_ID if no student in the system has the inputted USF ID
			if (!ID_exist)
				student->USF_ID = USF_ID;

			break;

		case 3:
			//Get student's email
			cout << "Please enter student's email. The student's email can only be up to 40 characters long." << endl;
			cin >> email;

			//Ensure that it is no more than 40 characters
			while (email.length() > 40) {
				cout << "Student's email can only be up to 40 characters. Please re-enter a valid email." << endl;
				cin >> email;
			}

			//Update email
			student->email = email;

			break;

		case 4:
			// Get student's presentation grade
			cout << "Please enter student's grade of the presentation. Enter grade from 0-4." << endl;
			
			//Ensure that grade is a numerical value and from 0 - 4
			while (true) {
				cin >> present_grade;
				if (!cin)
				{
					cout << "Grade should be a numerical value!" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}
				if (present_grade < 0 || present_grade > 4)
				{
					cout << "Grade can only be from 0 to 4. Please re-enter a valid grade." << endl;
					continue;
				}
				break;
			}

			//Update presentation grade
			student->present_grade = present_grade;

			break;

		case 5:
			// Get student's essay grade
			cout << "Please enter student's grade of the essay. Enter grade from 0-4." << endl;
			
			//Ensure that grade is a numerical value and from 0 - 4
			while (true) {
				cin >> essay_grade;
				if (!cin)
				{
					cout << "Grade should be a numerical value!" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}
				if (essay_grade < 0 || essay_grade > 4)
				{
					cout << "Grade can only be from 0 to 4. Please re-enter a valid grade." << endl;
					continue;
				}
				break;
			}

			//Update essay grade
			student->essay_grade = essay_grade;

			break;

		case 6:
			// Get student's term project grade
			cout << "Please enter student's grade of the term project. Enter grade from 0-4." << endl;
			//Ensure that grade is a numerical value and from 0 - 4
			while (true) {
				cin >> project_grade;
				if (!cin)
				{
					cout << "Grade should be a numerical value!" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}
				if (project_grade < 0 || project_grade > 4)
				{
					cout << "Grade can only be from 0 to 4. Please re-enter a valid grade." << endl;
					continue;
				}
				break;
			}

			//Update project grade
			student->project_grade = project_grade;

			break;

		case 7:
			break;

		default:
			cout << "Not a valid option!" << endl << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			flag = true;
		}

		if (option == 7) {
			cout << endl;
			break;
		}
		else if (!ID_exist && !flag) {
			cout << endl << "Student Updated:" << endl;
			cout << "Name: " << student->name << endl;
			cout << "USF ID: " << student->USF_ID << endl;
			cout << "Email: " << student->email << endl;
			cout << "Presentation Grade: " << student->present_grade << endl;
			cout << "Essay Grade: " << student->essay_grade << endl;
			cout << "Project Grade: " << student->project_grade << endl << endl;
		}

		ID_exist = false;
		flag = false;
	}
}

//Function to search
vector<studentData>::iterator search(vector<studentData> &class_roll, string value, searchOption option) {

	auto iter = find_if(class_roll.begin(), class_roll.end(), [&](const studentData &class_roll) {
		if (option == studentName)
			return class_roll.name == value;
		if (option == studentUSF_ID)
			return class_roll.USF_ID == value;
		if (option == studentEmail)
			return class_roll.email == value; }
	);

	return iter;
}

//Function to retrieve student data
void retrieveStudentData(vector<studentData> &class_roll) {
	string name, USF_ID, email;
	vector<studentData>::iterator student;
	int option = 0;
	bool flag = false;

	//Provide options and prompt the user to choose one
	//Keep looping until the user choose the done option at which point exit the for loop and return to main
	for (;;) {
		flag = false;

		cout << endl << "Option List:" << endl;
		cout << "1 - Name" << endl;
		cout << "2 - USF ID" << endl;
		cout << "3 - Email" << endl;
		cout << "4 - Done" << endl;
		cout << "Please provide the option to search by." << endl;
		cin >> option;

		//Checking to make sure the option input is valid
		if (!cin) {
			cout << "Not a valid option!" << endl << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		switch (option) {
			case 1:
				//Get student's name
				cout << endl << "Please enter student's name. The student's name can only be up to 40 characters long." << endl;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				getline(cin, name);
				
				//Ensure that it is no more than 40 characters
				while (name.length() > 40) {
					cout << "Student's name can only be up to 40 characters. Please re-enter a valid name." << endl;
					cin >> name;
				}
				
				//Search for student
				student = search(class_roll, name, studentName);
				break;
			
			case 2:
				//Get student's USF ID
				cout << "Please enter student's USF ID. The USF ID needs to be 10 characters long." << endl;
				cin >> USF_ID;
				
				//Ensure that it is 10 characters
				while (USF_ID.length() != 10) {
					cout << "Student's USF ID needs to be 10 characters. Please re-enter a valid USF ID." << endl;
					cin >> USF_ID;
				}
				
				//Search for student
				student =search(class_roll, USF_ID, studentUSF_ID);
				break;
			
			case 3:
				//Get student's email
				cout << "Please enter student's email. The student's email can only be up to 40 characters long." << endl;
				cin >> email;
				
				//Ensure that it is no more than 40 characters
				while (email.length() > 40) {
					cout << "Student's email can only be up to 40 characters. Please re-enter a valid email." << endl;
					cin >> email;
				}
				
				//Search for student
				student = search(class_roll, email, studentEmail);
				break;
			
			case 4:
				break;
			
			default:
				cout << "Not a valid option!" << endl << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				flag = true;
		}

		//Skip past the rest of the lines of code if the option is invalid so an empty student is never accessed
		if (flag)
			continue;

		if (option == 4) {
			cout << endl;
			break;
		}

		//Check to see if student was find and print out data if it exists
		if (student != class_roll.end()) {
			cout << "Student's Info:" << endl;
			cout << "Name: " << student->name << endl;
			cout << "USF ID: " << student->USF_ID << endl;
			cout << "Email: " << student->email << endl;
			cout << "Presentation Grade: " << student->present_grade << endl;
			cout << "Essay Grade: " << student->essay_grade << endl;
			cout << "Project Grade: " << student->project_grade << endl << endl;
		}
		else
			cout << "Student was not found in the system!" << endl << endl;
	}
}
