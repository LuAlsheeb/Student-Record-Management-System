#include <iostream>
#include <fstream>
#include <cstring>

#ifdef _WIN32
#define PAUSE system("pause")
#else
#define PAUSE system("read -p 'Press any key to continue...' var")
#endif

using namespace std;
    
    void create_user();
    bool login();
    void main_menu();
    void gpa(float *, char *, float [],int);
    void create_record();
    void display_record();
    void display_specific();
    void delete_record();
    void save_records();
    void load_records();

const int MAX_STUDENTS = 100;
const int MAX_PASSWORD_LENGTH = 20;

struct Student
{
int id;
char name[50];
float marks[5];
float gpa;
char grade;
};

Student students[MAX_STUDENTS];
int student_count = 0;


char username[] = "admin";
char password[MAX_PASSWORD_LENGTH] = "admin123";

int main()
{
        
    create_user();
    
    if ( login() )
    {
    load_records();
     main_menu();
     save_records();
    }
    

    
    return 0;
}


void create_user()
{
    
ifstream user_name_file_check("user_name.txt");
ifstream pass_file_check("pass.txt");

if (!user_name_file_check.is_open() || !pass_file_check.is_open()){
    
    ofstream user_name_file("user_name.txt");
    user_name_file << username;
    user_name_file.close();
    
    ofstream pass_file("pass.txt");
    pass_file << password;
    pass_file.close();
    
        cout << "Default credentials are stored in user_name.txt and pass.txt.\n";
        
    }else{
        cout << "Credential files already exist. Skipping creation.\n";
    }
    
user_name_file_check.close();
pass_file_check.close();
}

bool login(){

    char input_username[50];
    char input_password[MAX_PASSWORD_LENGTH];

        cout << "\nEnter username: ";
        cin >> input_username;
        
        cout << "Enter password: ";
        cin >> input_password;

    ifstream file("user_name.txt");
        file >> username;
        file.close();
    
    file.open("pass.txt");
        file >> password;
        file.close();

if(strcmp(input_username, username) == 0 && strcmp(input_password, password) == 0){
    
       cout << "\nLogin successful.\n";
        return true;
}

    cout <<"\033[1;90m"<< "\nWanna try again? (Y/n): "<<"\033[0m";
        char x;
        cin >> x;
    if (x == 'y' || x == 'Y')
    {
        return login();
    }
    cout << "\033[31m\nInvalid login.\033[0m\n";
        return false;
    }


void main_menu(){
    int choice;

do
{
    cout << "\033[1;36m";
    cout << "\n----- Main Menu -----\n";
    cout << "1. Create Record\n";
    cout << "2. Display All Records\n";
    cout << "3. Display Specific Record\n";
    cout << "4. Delete Record\n";
    cout << "5. Exit\n";
    cout << "\033[0m";
    cout << "\nEnter your choice: ";
    cin >> choice;
    cout<<"\n";
    switch (choice)
    {
        case 1:
            create_record();
            break;
        case 2:
            display_record();
            break;
        case 3:
            display_specific();
            break;
        case 4:
            delete_record();
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cerr << "\033[31mInvalid choice! Try again.\033[0m" << endl;
         }
            } while (choice != 5);
        }


void gpa(float *gpa, char *grade, float marks[], int num_subjects){

    float total = 0.0;

    //Calculate total marks:
    for (int i = 0; i < num_subjects; ++i)
    {
        total += marks[i];
    }

    //Calculate percentage:
    float percentage = (total / (num_subjects * 100.0));

    //Convert percentage to GPA:
    *gpa = (percentage * 5.0);

    //Assign letter grade based on GPA value:
    if (*gpa >= 4.5)
        *grade = 'A';
    else if (*gpa >= 4.0)
        *grade = 'B';
    else if (*gpa >= 3.5)
        *grade = 'C';
    else if (*gpa >= 3.0)
        *grade = 'D';
    else if (*gpa >= 2.5)
        *grade = 'E';
    else
        *grade = 'F';
}


void create_record(){
 
    //check if array is full:
 if (student_count >= MAX_STUDENTS){
     
     //Error message:
     cerr<<"\033[31mYou have reached the Student limit. No more records can be added.\n\033[0m";
     
 }else{
     
     Student s; // new Student object
     bool ID_Available = true;  
     
     //Loop to keep asking for ID until a unique one is entered
     do{
         cout<<"\033[32mEnter Student ID: \033[0m";
         cin>>s.id;
         
         // reset the flag 
         ID_Available = true;
         
         // Loop to check for a repeated ID
         for(int i=0 ; i < student_count ; i++){
             
             //check match
             if(s.id == students[i].id){
                 
                 //Show an error message
                 cerr<<"\033[1;91m\nID already exists! Please try again....\033[0m\n\n";
                 
                 //mark unvailable
                 ID_Available = false;
                 break; //Exit
             }
         }
            // if ID available -> Exit
            if (ID_Available == true){
             break;
         }
     }while(true);  // repeat until ID is unique
     
     
     cin.ignore();
     
     //asking for student name
     cout<<"\033[32mEnter Student Name: \033[0m";
     
     cin.getline(s.name , 50); // read full name with spaces
     
     //ask for marks
     cout<<"\033[32mEnter 5 subjects marks (0-100):\033[0m \n";
     
     //Loop to read 5 marks
     for(int i=0; i < 5; ){
         
         cout<<"\033[32msubject [\033[0m"<<i+1<<"\033[32m]: \033[0m";
         cin>> s.marks[i];
         
         //chec if mark is vaild
         if(s.marks[i]>=0 && s.marks[i]<=100){
             i++;   //move to next subject
             
         }else{ //error message
             cerr<< "\033[1;91m\nPlease enter a correct value (0-100)!\033[0m\n\n";
         }
     }
     
     //call gpa function
     gpa(&s.gpa, &s.grade, s.marks, 5);
     
     //store student in array
     students[student_count] = s;
     
     // increase number of students
     student_count++;
 }
    PAUSE;
}

void display_record() 
{
    // Check if there are no student records stored
    if (student_count == 0) {
            cout << "\033[31mNo records to display.\033[0m\n";
            PAUSE;   // Pause so the user can read the message
            return; // Exit the function
    }else{

    cout <<"\033[1;90m"<< "\n----- All Student Records -----\n";
    cout<<"-------------------------------\n";
    cout<<"ID\tNAME\tGPA\tGRADE\n";
    cout<<"-------------------------------\n";
    
    // Loop through all stored students
    for (int i = 0; i < student_count; i++) {
        
        cout <<students[i].id<<"\t"
         <<students[i].name<<"\t"
         << students[i].gpa<<"\t"
         << students[i].grade<<"\n" ;
        cout << endl  ;
        
    }
    cout<<"\033[0m\n";
}
    PAUSE; // Pause to let the user view the output
}

void display_specific()
{
    int searchID;
    
    // Ask the user to enter the student ID they want to search for
    cout << "\n\033[32mEnter Student ID to search:\033[0m";
    cin >> searchID;
    
    // Loop through all students to find a match
    for (int i = 0; i < student_count; i++) {
        
        // Check if the current student's ID matches the entered ID
        if (students[i].id == searchID) {
            
            cout <<"\033[1;90m"<< "\nRecord Found:\n";
             cout<<"-------------------------------\n";
            cout<<"ID\tNAME\tGPA\tGRADE\n";
            cout<<"-------------------------------\n";
            cout <<students[i].id<<"\t"
         <<students[i].name<<"\t"
         << students[i].gpa<<"\t"
         << students[i].grade<<"\n" ;
         cout<<"\033[0m\n";
            PAUSE;   // Pause so the user can read the information
            return;  // Exit the function after finding the student
        }
    }

    cerr << "\033[31mRecord not found.\033[0m\n"; // If the loop finishes with no match found
    PAUSE; // Pause before returning to the menu
}

void delete_record() 
{
    int id;

    //Ask the user to enter the student ID they want to delete
    cout << "\033[32mEnter the ID of the student to delete:\033[0m";
    cin >> id;

    int index = -1;  
    //index = -1 means the record has not been found yet

    //Search for the student record using the entered ID
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            index = i;    //Store the position of the record
            break;        //Stop searching once found
        }
    }

    //If index is still -1 → the student does not exist in the records
    if (index == -1) {
        cerr << "\033[31mStudent record not found!\033[0m\n";
        PAUSE;
        return; //Exit the function because nothing can be deleted
    }

    /*Shift all records after the deleted one one position to the left
      This removes the gap created by the deletion and keeps the array organized
    */
    for (int i = index; i < student_count - 1; i++) {
        students[i] = students[i + 1];
    }

    //Decrease the total student count after removing the record
    student_count--;

    cout << "Record deleted successfully.\n";
    PAUSE;
}

void save_records(){
 ofstream file ("students.dat" , ios ::binary ); //Open file "student.dat" in binary write mode.
 
    //Check if file failed to open
    if(!file){
        cerr << "\033[31mFile error.. saving process failed.\n";
        return; 
    }
    
    /*Write the number of students to the file
    (needed it as later when loading records)*/
     file.write(reinterpret_cast<char*>(&student_count),sizeof(student_count));
     
     //Write all student records as a binary block.
     file.write(reinterpret_cast<char*>(students),sizeof(Student)* student_count);
     
    //Check if writing to file was successful
        if(!file.good())
            cerr << "\033[31mErorr: occourred while writing the File.\033[0m\n";
            
        
        else 
            cout << "Records saved successfully!\n";
        
        //Close the file after finishing
        file.close();
    }




    void load_records() {
    ifstream file("students.dat", ios::binary);   // Attempt to open the records file in binary mode

    if (!file) {
        cerr << "Unable to load the file...\n";   // Failed to open the file
    } else {

        int temp_student_count;

        // Read the number of stored records inside the file
        file.read((char*)&temp_student_count, sizeof(temp_student_count));

        // Make sure the read number is valid and not corrupted
        if (temp_student_count < 0 || temp_student_count > MAX_STUDENTS) {
            cout << "Data inside the file seems invalid, skipping loading...\n";
            file.close();
        } else {

            // Read all student data into the array
            file.read((char*)students, sizeof(Student) * temp_student_count);

            // Update the actual number of students in the program
            student_count = temp_student_count;

            file.close();
        }
    }
}
