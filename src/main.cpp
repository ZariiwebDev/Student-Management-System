#include "iostream"
#include"string"
#include"cctype"
#include"windows.h"
#include"iomanip"
#include"fstream"
#include"math.h"
#include"ctime"
using namespace std;

void beep(){
     Beep(820,200);  //-> freq,ms
}
// !    LOIN MENU PROTOTYPES
void displayHeader(void);
void loginMenuDisplay(void);
bool loginMenu(void);
void loginID(void);
string generatingLoginID(void);
bool validID(string);
string currentLoginIDFetch(void);
void currentLoginStatus(void);

//! MAIN MENU PROTOTYPES
void mainMenuDisplay(void);
void mainMenu(void);

//! Student Recor d Prototype & structure
// ! ADD NEW RECORD 
struct StudentPersonalInformation
{
    string fullName;
    string dob;
    char gender;
    string stdID;
    bool validateID(string);
};
struct StudentContactInformation{
    string phoneNumber;
    string emailAddress;
    bool validateEmail();
};
struct StudentAcedamicInformation{
    int noOfcourses=10;                                        // number of courses a student has been EnrolledIn 
    string *coursesNames = new string[noOfcourses];           // stores the courses names
    void getCoursesNames();                                  /* adds the courses names into @param coursesNames */
    int *coursesTotalMarks = new int[noOfcourses];          // stores the total marks of each course
    void getCoursesTotalMarks();                           /* adds the courses names into @param coursesNames */
    int *coursesObtainedMarks = new int[noOfcourses];     // stores the obtained marks of each course
    void getCoursesObtainedMarks();                      /* adds the courses names into @param coursesObtainedMarks */
    char* coursesGrades = new char[noOfcourses];
    void setCoursesGrades();
    char calcgrade(int);
    char averageGrade;
    /**
     * The function `~StudentAcedamicInformation()` is a destructor that deallocates memory for arrays
     * storing information about courses.
     */
    ~StudentAcedamicInformation(){
        delete[] coursesNames;
        delete[] coursesGrades;
        delete[] coursesTotalMarks;
        delete[] coursesObtainedMarks;
    }
};
struct Student{
    StudentPersonalInformation personalInfo;
    StudentContactInformation contactInfo;
    StudentAcedamicInformation acedamicInfo;
};
void addNewStudent(Student[],int&);
string generateStudentID();
bool validateStudentName(string studentName);
bool validateDob(string dob);
bool validatePhoneNumber(string phoneNumber);

//! VIEW RECORDS
void viewRecords(Student[],int,bool);
void viewRecords(Student[],int,int);
// ! Delete Students
void deleteStudent(Student[],int&);
// ! SEARCH FOR A STUDENT
void searchStudents(Student[],int);
// ! Update student record by ID
void updateRecordsMenu(void);
int studentID(Student[],int,string);        // --> returns the index of found id if not found return -1
void updateRecord(Student[],int);
// ! Calculating Average Grade
void calcAverageGrade(Student[],int);
// ! Sorting student data
void sortData(Student[],int);
// ! SAVE AND LOAD RECORDS FROM FILE
bool saveRecords(Student[],int,bool);
bool loadRecords();
// ! Display Top Performers
void displayTopPerformers(Student[],int);
// ! GRADE ANALYSIS
void gradeAnalysis(Student[],int);
// ! Attandance tracking
void attendanceTrack(Student[],int);
//!                                 "MAIN SCOPE "
/**
 * The main function calls the loginMenu function and then the mainMenu function if the login is
 * successful.
 */
int main() {
    bool res = loginMenu();
    if(res){
        mainMenu();
    }
    return 0;
}
// !                                " LOGIN MENU CODE "
/**
 * `displayHeader` prints a stylized header using ASCII art.
 */
void displayHeader(){
    cout<<"\n\n\n";
    cout<<"░█▀▀▀█ ▀▀█▀▀ ░█─░█ ░█▀▀▄ ░█▀▀▀ ░█▄─░█ ▀▀█▀▀ 　 ░█▀▄▀█ ─█▀▀█ ░█▄─░█ ─█▀▀█ ░█▀▀█ ░█▀▀▀ ░█▀▄▀█ ░█▀▀▀ ░█▄─░█ ▀▀█▀▀ 　 ░█▀▀▀█ ░█──░█ ░█▀▀▀█ ▀▀█▀▀ ░█▀▀▀ ░█▀▄▀█\n";
    cout<<"─▀▀▀▄▄ ─░█── ░█─░█ ░█─░█ ░█▀▀▀ ░█░█░█ ─░█── 　 ░█░█░█ ░█▄▄█ ░█░█░█ ░█▄▄█ ░█─▄▄ ░█▀▀▀ ░█░█░█ ░█▀▀▀ ░█░█░█ ─░█── 　 ─▀▀▀▄▄ ░█▄▄▄█ ─▀▀▀▄▄ ─░█── ░█▀▀▀ ░█░█░█\n";
    cout<<"░█▄▄▄█ ─░█── ─▀▄▄▀ ░█▄▄▀ ░█▄▄▄ ░█──▀█ ─░█── 　 ░█──░█ ░█─░█ ░█──▀█ ░█─░█ ░█▄▄█ ░█▄▄▄ ░█──░█ ░█▄▄▄ ░█──▀█ ─░█── 　 ░█▄▄▄█ ──░█── ░█▄▄▄█ ─░█── ░█▄▄▄ ░█──░█\n";
    cout<<"\n\n\n";
}
/**
 * The function `validID` checks if a given string is a valid login ID by ensuring it is 8 characters
 * long and contains only uppercase letters and digits.
 * 
 * @param id The `validID` function checks if a given ID is valid based on the following criteria:
 * 
 * @return The function `validID` returns a boolean value. It returns `true` if the input `id` is a
 * valid login ID according to the specified criteria (8 characters in length and containing only
 * uppercase letters and digits), and `false` otherwise.
 */
bool validID(string id){
    //! valid login must have 8 characters in length and does not contain other alphabets other tha 1-9 and A-Z
    if(id.length() == 8){
        for(char chr : id){
                if(!isupper(chr) && !isdigit(chr)){
                    return false;
                }
        }
    }else{
        return false;
    }
    return true;
}
/**
 * The function "generatingLoginID" generates a random login ID consisting of digits and uppercase
 * alphabets.
 * 
 * @return The function `generatingLoginID` is returning a randomly generated login ID consisting of a
 * combination of digits and uppercase alphabets. The login ID is 8 characters long, with alternating
 * characters of a random digit from 0-9 and a random uppercase alphabet from A-Z.
 */
string generatingLoginID(){
    cout<<"\tgenerating..."<<endl;
    srand(time(0));
    string loginId="";
    string digits = "0123456789";
    int lengDigits = digits.length();
    string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int lengAlphabets = alphabets.length();
    int idLen = 8;
    for(int i=1;i<=idLen/2;i++){
        int randomIndexDig =rand()%(lengDigits-1);
        int randomIndexAlpha =rand()%(lengDigits-1);
        loginId.push_back(digits[randomIndexDig]);
        loginId.push_back(alphabets[randomIndexAlpha]);
    }
    return loginId;
}
/**
 * The function `currentLoginIDFetch` reads the current login ID from a file and returns it if it is
 * valid.
 * 
 * @return The function `currentLoginIDFetch` is returning a string value. The string value being
 * returned is either the `id` read from the file "./LoginID/ID.txt" if it passes the `validID` check,
 * or an empty string if the `id` is not valid.
 */
string currentLoginIDFetch(){
    string id="";
    fstream file("./LoginID/ID.txt",ios::in);
    if(!file){
        cout<<"Sorry does't open a file";
        return "";
    }
    file>>id;
    return validID(id) ? id : "";
}
/**
 * The function generates a unique login ID, validates it, saves it to a file, and provides feedback to
 * the user.
 *  @attention  displays the id to the user
 */
void loginID(){
    string id =generatingLoginID();
    while(!validID(id)){
        id = generatingLoginID();
    }
    cout<<"\nYour LoginID is \033[33m"<<id<<"\033[0m"<<endl;
    fstream file("./LoginID/ID.txt",ios::out);
    if(!file){
        beep();
        cout<<"Sorry we have some issues wile saving your ID \n";
    }else{
        file<<id;
        cout<<"\033[0mWe Successfully ✅ saved your Login Id you can use it later for login !\033[0m"<<endl;
    }
    file.close();
}
/**
 * The function `loginMenuDisplay` displays a menu for users to either login, sign up, or exit with a
 * limited number of attempts (3).
 */
void loginMenuDisplay(){
    displayHeader();
    cout<<"\n";
    cout<<"╭────────────────────────────────····LOGIN····──────────────────────────···"<<endl;
    cout<<"│ "<<endl;
    cout<<"│▶> [1]-Login [select if you already have LoginID]"<<endl;
    cout<<"│"<<endl;
    cout<<"│▶> [2]-Signup [select if you don't have any loginID]"<<endl;
    cout<<"│"<<endl;
    cout<<"│▶> [3]- Exit"<<endl;
    cout<<"│ "<<endl;
    cout<<"│\tselect any of three options,you have only 3 attempts"<<endl;
    cout<<"╰──────────────···"<<endl;
}
/**
 * The function `loginMenu` displays a login menu, handles user input validation, and allows users to
 * login, generate a new ID, or exit the system based on their choice.
 * 
 * @return The function `loginMenu()` returns a boolean value - `true` if the login process is
 * successful and `false` if it is not successful or if the user chooses to exit the system.
 */
bool loginMenu(){
    loginMenuDisplay();
    int choice,chances=3;
    // falsy handling choice 
    do{
        cout<<"Enter your choice [1/2/3] :";
        cin>>choice;
        if(choice != 1 && choice !=2 && choice !=3 && chances>0){
            beep();
            cout<<"\033[31mWrong Choice Please make sure you have choose [1/2/3] ! \033[0m"<<endl;
            chances--;
            if(chances !=0){
                cout<<"\033[34mattempts left "<<chances<<"\033[0m"<<endl;
            }
        }
        if(chances==0){
            cout<<"\tSorry goodbye ! you have 0 attempts left !\n";
            return 0;
        }
    }while((choice != 1 && choice !=2 && choice !=3 ) && chances>=0);
    // truthy handling 
    if(choice ==1){
        bool errorStatus=false;
        string user;
        string id;
        cout<<"\033[32m-▶>> You Selected Option 1\033[0m"<<endl;
        do{
        fstream file("./LoginID/ID.txt",ios::in);
        cout<<"\tEnter your Login ID : ";
        cin>>user;
        if(!file){
            cout<<"File Does not opened !"<<endl;
            errorStatus=true;
        }
        // reading id from file 
        file>>id;
        if(validID(id)){
            if(id.length()>0){
        if(!id.compare(user)){
            cout<<"\033[34m User Login successfully !\033[0m\n";
            errorStatus=false;
        }else{
            cout<<"\033[31m No user found !\033[0m"<<endl;
            errorStatus=true;
        }
        }else{
            cout<<"Sorry File is corrupted ! it has not a valid ID Check it ! "; ///** */
            errorStatus=true;
        }
            file.close();
            }else{
                cout<<"\033[31mSorry we didn't found any login ID in our database !\033[0m"<<endl;
                int choice;
                cout<<"▶> [1] Want to Generate new ID \n";
                cout<<"▶> [2] Want to Exit System \n";
                do{
                    cout<<"Enter your choice [1/2] : ";
                    cin>>choice;
                    if(choice ==1){
                         cout<<"\033[32m-▶>> You Selected Option 1\033[0m"<<endl;
                         errorStatus=false;
                         loginID();
                    }
                    else if (choice ==2){
                         cout<<"\033[32m-▶>> You Selected Option 2\033[0m"<<endl;
                         errorStatus=true;
                         exit(0);
                    }else{
                        cout<<"Wrong Choice Please Choose correct options !\n";
                    }
                }while(choice !=1 && choice !=2);
            }
        }while(errorStatus);
        if(errorStatus){
            return 0;
        }
    }
    else if (choice ==2){
        cout<<"\033[32m-▶>> You Selected Option 2\033[0m"<<endl;
        loginID();
    }
    else{
        cout<<"\033[32m-▶>> You Selected Option 3\033[0m"<<endl;
        cout<<"\t\033[33mThanks see you later ! \033[0m"<<endl;
        return 0;
    }
    return 1;
}
/**
 * The function `currentLoginStatus` displays the current login status and user ID in green color.
 */
void currentLoginStatus(){
     cout<<"\n Current Status: \033[32mLOGGED IN\033[0m"<<endl;
     cout<<" Current UserID: \033[32m"<<currentLoginIDFetch()<<"\033[0m"<<endl;
}

// !                            "MAIN   MENU"
void mainMenuDisplay(){
       currentLoginStatus();
       cout<<"╭────────────────────────────────····MAIN MENU····──────────────────────────···"<<endl;
       cout<<"│ "<<endl;
       cout<<"│ ▶> [1]  Add New Student Record"<<endl;
       cout<<"│ "<<endl;
       cout<<"│ ▶> [2]  View All Student Records"<<endl;
       cout<<"│ "<<endl;
       cout<<"│ ▶> [3]  Search for a Student"<<endl;
       cout<<"│ "<<endl;
       cout<<"│ ▶> [4]  Delete a Student Record"<<endl;
       cout<<"│ "<<endl;
       cout<<"│ ▶> [5]  Update a Student Record"<<endl;
       cout<<"│ "<<endl;
       cout<<"│ ▶> [6]  Calculate Average Grade"<<endl;
       cout<<"│ "<<endl;
       cout<<"│ ▶> [7]  Sort Records by Name or ID"<<endl;
       cout<<"│ "<<endl;
       cout<<"│ ▶> [8]  Display Top Performer(s)"<<endl;
       cout<<"│ "<<endl;
       cout<<"│ ▶> [9]  Grade Analysis"<<endl;
       cout<<"│ "<<endl;
       cout<<"│ ▶> [10] Save Records to File"<<endl;
       cout<<"│ "<<endl;
       cout<<"│ ▶> [11] Load Records from File"<<endl;
       cout<<"│ "<<endl;
       cout<<"│ ▶> [12] Track Attendance"<<endl;
       cout<<"│ "<<endl;
       cout<<"│ ▶> [13] Goto Login Menu"<<endl;
       cout<<"│ "<<endl;
       cout<<"│ ▶> [14] Exit System"<<endl;
       cout<<"│ "<<endl;
       cout<<"│\t\tselect any of these 14 options"<<endl;
       cout<<"╰────────────────────────────────···"<<endl;
}
/**
 * The mainMenu function in C++ displays a menu for managing student records and performs various
 * operations based on user input.
 */
void mainMenu(){
    bool trackFileSaved=false;
    bool avrageGradeTrack=false;
    int trackNumberOfStudentsAdded=0;
    Student students[100];
    bool track=false;
    char choiceMenu;
    do{
        int choice;
        mainMenuDisplay();
        do{
            cout<<"Enter Your Choice [1-14] : ";
            cin>>choice;
            if(!(choice>=1 && choice<=14)){
                beep();
                cout<<"\033[31m Sorry no option found ! TRY AGAIN..\033[0m\n";
            }
        }while(!(choice>=1 && choice<=14));
        
        if(choice==1){
            cout<<"\033[32m-▶>> You Selected Option 1\033[0m"<<endl;
            addNewStudent(students,trackNumberOfStudentsAdded);        // adding new student
            track=true;
        }
        else if(choice==2){
            if(track){
                cout<<"\033[32m-▶>> You Selected Option 2\033[0m"<<endl;
                viewRecords(students,trackNumberOfStudentsAdded,avrageGradeTrack);
            }else{
                cout<<"\033[32m-▶>> You Selected Option 2\033[0m"<<endl;
                cout<<"\tNo records found please first add record !\n";
            }
        }
        else if(choice==3){
            if(track){
                cout<<"\033[32m-▶>> You Selected Option 3\033[0m"<<endl;
                searchStudents(students,trackNumberOfStudentsAdded);
            }else{
                cout<<"\033[32m-▶>> You Selected Option 3\033[0m"<<endl;
                cout<<"\tNo records found please first add record !\n";
            }
        }
        else if(choice==4){
             if(track){
                cout<<"\033[32m-▶>> You Selected Option 4\033[0m"<<endl;
                deleteStudent(students,trackNumberOfStudentsAdded);
            }else{
                cout<<"\033[32m-▶>> You Selected Option 4\033[0m"<<endl;
                cout<<"\tNo records found to delete please first add record !\n";
            }
        }
        else if(choice==5){
             if(track){
                cout<<"\033[32m-▶>> You Selected Option 5\033[0m"<<endl;
                updateRecord(students,trackNumberOfStudentsAdded);
            }else{
                cout<<"\033[32m-▶>> You Selected Option 5\033[0m"<<endl;
                cout<<"\tNo records found to update please first add record !\n";
            }
        }
        else if(choice==6){
            if(track){
                avrageGradeTrack=true;
                cout<<"\033[32m-▶>> You Selected Option 6\033[0m"<<endl;
                calcAverageGrade(students,trackNumberOfStudentsAdded);
                cout<<"\tAverage Grade has been calculated successfully ✅\n";
            }else{
                cout<<"\033[32m-▶>> You Selected Option 6\033[0m"<<endl;
                cout<<"\tNo records found to Calculate Grades please first add record !\n";
            }
        }
        else if(choice==7){
            if(track){
                cout<<"\033[32m-▶>> You Selected Option 7\033[0m"<<endl;
                sortData(students,trackNumberOfStudentsAdded);
                cout<<"\n Data successfully sorted ✅\n";
            }else{
                cout<<"\033[32m-▶>> You Selected Option 7\033[0m"<<endl;
                cout<<"No records found to sort please first add record !\n";
            }
        }
        else if(choice==8){
            if(track){
                cout<<"\033[32m-▶>> You Selected Option 8\033[0m"<<endl;
                displayTopPerformers(students,trackNumberOfStudentsAdded);
            }else{
                cout<<"\033[32m-▶>> You Selected Option 8\033[0m"<<endl;
                cout<<"No records found to display Top Performers,please first add record !\n";
            }
        }
        else if(choice==9){
            if(track){
                cout<<"\033[32m-▶>> You Selected Option 9\033[0m"<<endl;
                avrageGradeTrack=true;
                calcAverageGrade(students,trackNumberOfStudentsAdded);
                gradeAnalysis(students,trackNumberOfStudentsAdded);
                 
            }else{
                cout<<"\033[32m-▶>> You Selected Option 9\033[0m"<<endl;
                cout<<"No records found to Analyze Grades ,please first add record !\n";
            }
        }
        else if(choice==10){
                if(track){
                    cout<<"\033[32m-▶>> You Selected Option 10\033[0m"<<endl;
                    trackFileSaved = saveRecords(students,trackNumberOfStudentsAdded,avrageGradeTrack);
                    if(trackFileSaved){
                        cout<<"Data has been successfully saved !\n";
                    }else{
                        cout<<"Error While Saving Try later ..!\n";
                    }
                }else{
                    cout<<"\033[32m-▶>> You Selected Option 10\033[0m"<<endl;
                    cout<<"No records found to Save please add record first!\n";
                }
        }
        else if(choice==11){
            cout<<"\033[32m-▶>> You Selected Option 11\033[0m"<<endl;
            bool res = loadRecords();
            if(!res){
                cout<<"No records Found !\n";
            }
        }
        else if(choice == 12){
                // if(track){
                    cout<<"\033[32m-▶>> You Selected Option 11\033[0m"<<endl;
                    attendanceTrack(students,trackNumberOfStudentsAdded);
                // }
        }
        else if(choice==13){
            cout<<"\033[32m-▶>> You Selected Option 13\033[0m"<<endl;
            loginMenu();
        }
        else if (choice==14){
            cout<<"\033[32m-▶>> You Selected Option 14\033[0m"<<endl;
            cout<<"Thanks ! GoodBye "<<endl;
            exit(0);
        }
        cout<<"Do you want to continue ? (y/n) : ";
        cin>>choiceMenu;
        if(tolower(choiceMenu) != 'y'){
            cout<<"Thanks ! GoodBye "<<endl;
            break;
        }
    }while(tolower(choiceMenu) == 'y');

}
/**
 * The function `addNewStudent` allows the user to input information for a specified number of students
 * and saves the data for each student in an array.
 * 
 * @param students The `students` parameter is an array of `Student` objects. It is used to store
 * information about multiple students, such as their personal information, contact information, and
 * academic information.
 * @param trackNumberOfStudentsAdded The `trackNumberOfStudentsAdded` parameter is a reference to an
 * integer variable that keeps track of the number of students to be added. This variable is passed by
 * reference to the `addNewStudent` function so that the function can update its value based on user
 * input. This way, the function can
 */
void addNewStudent(Student students[],int& trackNumberOfStudentsAdded){
    cout<<"How many students to add ? ";
    cin>>trackNumberOfStudentsAdded;
    for(int i=0;i<trackNumberOfStudentsAdded;i++){
        cout<<"\t Student: "<<i+1<<endl;
        cout<<"\033[34m\t\t PERSONAL INFORMATION :\033[0m\n";
        do{
            cin.ignore();
            cout<<"Enter Your Full Name : ";
            getline(cin,students[i].personalInfo.fullName);
            if(!validateStudentName(students[i].personalInfo.fullName)){
                beep();
                cout<<"\033[31m Please Enter a correct name , name must be 4 characters long and does not include any digit or symbols !\033[0m\n";
            }
        }while(!validateStudentName(students[i].personalInfo.fullName));
        do{
            cout<<"Enter your Date of Birth format:dd/mm/yy : ";
            cin>>students[i].personalInfo.dob;
        }while(!validateDob(students[i].personalInfo.dob));
        do{
            cout<<"Gender ? (M/F/O)";
            cin>>students[i].personalInfo.gender;
            if(tolower(students[i].personalInfo.gender) !='m' && tolower(students[i].personalInfo.gender) !='f' && tolower(students[i].personalInfo.gender) !='o'){
                beep();
                cout<<"\033[31m Please Enter Correct Gender ! \033[0m\n";
            }
        }while(tolower(students[i].personalInfo.gender) !='m' && tolower(students[i].personalInfo.gender) !='f' && tolower(students[i].personalInfo.gender) !='o');
        cout<<"Generating ....\n";
        students[i].personalInfo.stdID = generateStudentID();
        if(students[i].personalInfo.validateID(students[i].personalInfo.stdID)){
                cout<<"Student ID assigned : \033[34m"<<students[i].personalInfo.stdID<<"\033[0m"<<endl;
        }
        cout<<"\033[34m\t\t CONTACT INFORMATION :\033[0m\n";
        do{
        cin.ignore();
        cout<<"Enter Emergency Contact Number : ";
        cin>>students[i].contactInfo.phoneNumber;
        }while(!validatePhoneNumber(students[i].contactInfo.phoneNumber));
        do{
            cin.ignore();
            cout<<"Enter your Email Address : ";
            cin>>students[i].contactInfo.emailAddress;
            if(!students[i].contactInfo.validateEmail()){
                beep();
                cout<<"\033[31mSorry! Please enter correct email address !\033[0m\n";
            }
        }while(!students[i].contactInfo.validateEmail());
        cout<<"\033[34m\t\t ACEDAMICS INFORMATION :\033[0m\n";
        do{
            cout<<"Enter how many courses have you Enrolled In ! : ";
            cin>>students[i].acedamicInfo.noOfcourses;
        }while(students[i].acedamicInfo.noOfcourses<0 && students[i].acedamicInfo.noOfcourses>100);
        students[i].acedamicInfo.getCoursesNames();
        students[i].acedamicInfo.getCoursesTotalMarks();        
        students[i].acedamicInfo.getCoursesObtainedMarks();
        students[i].acedamicInfo.setCoursesGrades();
        cout<<"Data Sucessfully saved for student "<<(i+1)<<endl;
    }
}

//! Validating Student Name
/**
 * The function `validateStudentName` checks if a given string contains only alphabetic characters and
 * spaces.
 * 
 * @param studentName The `validateStudentName` function is designed to validate a student's name. It
 * checks if the length of the student name is at least 1 character and then iterates through each
 * character in the name. If any character is not an alphabet letter or a space, the function returns
 * false indicating that
 * 
 * @return The function `validateStudentName` returns a boolean value. It returns `true` if the
 * `studentName` meets the validation criteria (contains only alphabetic characters and spaces, and has
 * a length of at least 1), and `false` otherwise.
 */
bool validateStudentName(string studentName){
    if(studentName.length()>=1){
        for(char ch : studentName){
            if(!isalpha(ch) && !isspace(ch)){
                return false;
            }
        }
        return true;
    }

    return false;
}
//! Validating Dob
/**
 * The function `validateDob` checks if a given date of birth string is in the format "dd/mm/yy" and
 * validates the day and month values.
 * 
 * @param dob The function `validateDob` takes a string `dob` as input, which represents a date of
 * birth in the format "dd/mm/yy". The function parses this input string to extract the day, month, and
 * year components. It then validates whether the day is within 1-31
 * 
 * @return The function `validateDob` returns a boolean value - `true` if the date of birth (dob)
 * provided is in the format "dd/mm/yy" and the date and month values are within the valid ranges (1-31
 * for date and 1-12 for month), otherwise it returns `false`.
 */
bool validateDob(string dob){
    bool slash = true;
    string date="";
    string month="";
    string year="";
    int dateEndIndex = dob.find('/');
    if(dateEndIndex<dob.length()){
        date = dob.substr(0,dateEndIndex);
        int monthLastIndex = dob.find('/',(dateEndIndex+1));
            if(monthLastIndex<dob.length()){
                month = dob.substr((dateEndIndex+1),(monthLastIndex-(dateEndIndex+1)));
                year = dob.substr((monthLastIndex+1),(dob.length()-(monthLastIndex+1)));
            }else{
                slash=false;
            }
    }else{
        slash=false;
    }

    if(slash){
        int dateInt = stoi(date); 
        int monthInt = stoi(month);
        if(!(dateInt>=1 && dateInt<=31)){
            cout<<"\033[32m Date must be within 1-31\033[0m\n";
            return false;
        }else if (!(monthInt>=1 && monthInt<=12)){
            cout<<"\033[32m Month must be within 1-12\033[0m\n";
            return false;
        }
        return true;
    }else{
        cout<<"\n\033[31m Sorry Dob was not in dd/mm/yy format !\033[0m"<<endl;
        return false;
    }
}
// ! Validating phone Number
/**
 * The function `validatePhoneNumber` checks if a phone number is valid by ensuring it does not start
 * with a plus sign and contains only digits.
 * 
 * @param phoneNumber The function `validatePhoneNumber` takes a string `phoneNumber` as input and
 * checks if it is a valid phone number. It returns `true` if the phone number consists only of digits
 * and does not start with a '+', otherwise it returns `false`.
 * 
 * @return The function `validatePhoneNumber` returns a boolean value - `true` if the phone number is
 * valid (contains only digits and does not start with '+'), and `false` otherwise.
 */
bool validatePhoneNumber(string phoneNumber){
    if(phoneNumber[0]=='+'){
        cout<<"\033[31m Please Enter number without + \033[0m\n";
        return false;
    }
    else{
        for(char ch : phoneNumber){
                if(!isdigit(ch)){
                    return false;
                }
        }
        return true;   
    }

    return false;
}
// !   Taking user input in Acedamics Record
void StudentAcedamicInformation::getCoursesNames(){
        for(int j=0;j<noOfcourses;j++){
            do{
                cin.ignore();  
                cout<<"Enter Course "<<(j+1)<<" Name :";
                getline(cin,coursesNames[j]);
            }while(!validateStudentName(coursesNames[j]));
        }
}

void StudentAcedamicInformation::getCoursesTotalMarks(){
        for(int j=0;j<noOfcourses;j++){
            do{
            cout<<"Enter Total Marks "<<coursesNames[j]<<" :";
            cin>>coursesTotalMarks[j];
            }while(coursesTotalMarks[j]<0 || coursesTotalMarks[j]>100);
        }
}
void StudentAcedamicInformation::getCoursesObtainedMarks(){
        for(int j=0;j<noOfcourses;j++){
            do{
            cout<<"Enter Obtained Marks "<<coursesNames[j]<<":";
            cin>>coursesObtainedMarks[j];
            }while(coursesObtainedMarks[j]<0 || coursesObtainedMarks[j]>100 || coursesObtainedMarks[j]>coursesTotalMarks[j]);
        }
}
void StudentAcedamicInformation::setCoursesGrades(){
    for(int j=0;j<noOfcourses;j++){
        coursesGrades[j] = calcgrade(j);
    }
}
//! calculating grades
char StudentAcedamicInformation::calcgrade(int index){
    float percentage = (coursesObtainedMarks[index]/(float)coursesTotalMarks[index] )*100.0;
    if(percentage<33){
        return 'F';
    }
    else if(percentage>=33 && percentage<40){
        return 'D';
    }
    else if(percentage>=40 && percentage<66){
        return 'C';
    }
    else if(percentage>=66 && percentage<80){
        return 'B';
    }
    else if(percentage>=80){
        return 'A';
    }else{
        return 'N';         // no grade
    }    
}
// ! Calculating average grade and assigns it to the avrageGraade
void calcAverageGrade(Student students[],int noOfStds){
    for(int k=0;k<noOfStds;k++){
    int totalMarks=0,obtainedMarks=0;
    for(int i=0;i<students[k].acedamicInfo.noOfcourses;i++){
        totalMarks += students[k].acedamicInfo.coursesTotalMarks[i];
        obtainedMarks += students[k].acedamicInfo.coursesObtainedMarks[i];
    }
    float percentage = (obtainedMarks/(float)totalMarks)*100.0;
    if(percentage<33.0){
        students[k].acedamicInfo.averageGrade ='F';
    } 
    else if(percentage>=33.0 && percentage<40.0){
         students[k].acedamicInfo.averageGrade ='D';
    }
    else if(percentage>=40.0 && percentage<66.0){
        students[k].acedamicInfo.averageGrade ='C';
    }
    else if(percentage>=66.0 && percentage<80.0){
         students[k].acedamicInfo.averageGrade ='B';
    }
    else if(percentage>=80.0){
        students[k].acedamicInfo.averageGrade ='A';
    }else{
         students[k].acedamicInfo.averageGrade ='N';         // no grade
    }
    }
}
//! generating student ID 
/**
 * The function generates a random 4-digit student ID using numbers 0-9.
 * 
 * @return A randomly generated student ID consisting of 4 digits.
 */
string generateStudentID(){
    srand(time(0));
    string ID="";
    string numbers = "0123456789";
    for(int i=0;i<4;i++){
        int randomIndex = rand() % 10;
        ID += numbers[randomIndex];
    }
    return ID;
}

//! Validating Student ID
bool StudentPersonalInformation::validateID(string Id){
        if(Id.length()==4){
            for(char ch : Id){
                if(!isdigit(ch)){
                    return false;
                }
            }
            return true;
        }

    return false;
}

//! Validating Gmail Address
bool StudentContactInformation::validateEmail(){
    bool find=false;
    for(char ch : emailAddress){
            if(ch =='@'){
                find=true;
                break;
            }
    }

    return find;
}
void viewRecords(Student students[],int noOfStds,bool avgGrade){
    if(noOfStds>0){
    cout<<"\033[33m\t\tNUMBER OF STUDENTS FOUND "<<(noOfStds)<<"\033[0m\n";
    cout<<"╭───────────────────────────────────────────────────────────────────────────────────────────────────────\n";
    cout<<"│\n";
    for(int i=0;i<noOfStds;i++){
    cout<<"│-▶>> \033[32mStudent ID: \033[31m"<<students[i].personalInfo.stdID<<"\033[0m\n";
    cout<<"│\n";
    cout<<"│\t\033[34mPERSONAL INFORMATION \033[0m\n";
    cout<<"│\n";
    cout<<"│\t\tFull Name: "<<students[i].personalInfo.fullName<<"\n";
    cout<<"│\n";
    cout<<"│\t\tDOB: "<<students[i].personalInfo.dob<<"\n";
    cout<<"│\n";
    cout<<"│\t\tGender: "<<students[i].personalInfo.gender<<"\n";
    cout<<"│\n";
    cout<<"│\t\tStudent ID: "<<students[i].personalInfo.stdID<<"\n";
    cout<<"│\n";
    cout<<"│\t\033[34mCONTACT INFORMATION \033[0m\n";
    cout<<"│\n";
    cout<<"│\t\tPhone Number: "<<students[i].contactInfo.phoneNumber<<"\n";
    cout<<"│\n";
    cout<<"│\t\tEmail: \033[36m"<<students[i].contactInfo.emailAddress<<"\033[0m\n";
    cout<<"│\n";
    cout<<"│\t\033[34mACEDAMICS INFORMATION \033[0m\n";
    cout<<"│\n";
    cout<<"│\t\tCourses Enrolled: "<<students[i].acedamicInfo.noOfcourses<<"\n";
    cout<<"│\n";
    cout<<"│\t\t\t\t╭─────────────────────────────────────────────────────────────────────────────────────────╮\n";
    cout<<"│\t\t\t\t│NAMES"<<fixed<<setw(29)<<"TOTAL MARKS"<<setw(29)<<"OBTAINED MARKS"<<setw(29)<<"GRADE│"<<"\n";
    cout<<"│\t\t\t\t│┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅│"<<"\n";
    for(int j=0;j<students[i].acedamicInfo.noOfcourses;j++){
    cout<<"│\t\t\t\t│"<<fixed<<students[i].acedamicInfo.coursesNames[j]<<fixed<<setw(6)<<students[i].acedamicInfo.coursesTotalMarks[j]<<setw(18)<<students[i].acedamicInfo.coursesObtainedMarks[j]<<setw(37)<<students[i].acedamicInfo.coursesGrades[j]<<setw(8)<<fixed<<"│\n";
    }
    if(avgGrade){
    cout<<"│\t\t\t\t│┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅│"<<"\n";
    cout<<"│\t\t\t\t│"<<fixed<<setw(50)<<"GRADE = "<<students[i].acedamicInfo.averageGrade<<setw(41)<<"│"<<endl;
    }
    cout<<"│\t\t\t\t╰─────────────────────────────────────────────────────────────────────────────────────────╯\n";
    cout<<"│\n";
    cout<<"│\n";
    }
    cout<<"│\n";
    cout<<"╰───────────────────────────────────────────────────────────────────────────────────────────────────────\n";
    }else{
        cout<<"No Students Found to Display !\n";
    }
}

/**
 * The function `searchStudents` in C++ performs a linear search on an array of `Student` objects based
 * on user input of student ID or name and displays search results or a message if no record is found.
 *
 * @param students The `students` parameter is an array of `Student` objects. Each `Student` object
 * likely contains information about a student, such as their personal information like full name and
 * student ID. The function `searchStudents` takes this array of `Student` objects and the number of
 * students (`noOf
 * @param noOfStudents The `noOfStudents` parameter in the `searchStudents` function represents the
 * total number of students in the `students` array that you are searching through. This parameter is
 * used to determine the range of the loop for searching the students' information based on the user
 * input.
 * 
 * @return The `searchStudents` function is designed to search for a student in an array of `Student`
 * objects based on the input provided by the user (either student ID or name). If a matching student
 * is found, the function will display the search results by calling the `viewRecords` function and
 * then return. If no matching student is found, it will display a message indicating that no record
 * was found
 */
void searchStudents(Student students[],int noOfStudents){
        string userInput="";
        cout<<"Enter Student ID or Name To Search :";
        cin.ignore();
        getline(cin,userInput);
        // ! Linear Search
        for(int i=0 ;i<noOfStudents;i++){
                if(!students[i].personalInfo.fullName.compare(userInput) || !students[i].personalInfo.stdID.compare(userInput)){
                        cout<<"\t\t\033[33m\t\t SEARCH RESULTS BY "<<userInput<<"\033[0m\n";
                        viewRecords(students,noOfStudents,i);
                        return;
                }             
        }
    cout<<"Sorry No Record found with "<<userInput<<endl;
}
// ! Delete Students Records
void deleteStudent(Student students[],int &noOfStds){
        char choice = 'n';
        bool userStatus=false;
        string userInput;
        do{
            int index=-1;
            cout<<"Enter Student ID : ";
            cin>>userInput;
            for(int i=0;i<noOfStds;i++){
                    if( !userInput.compare(students[i].personalInfo.stdID)){
                            userStatus=true;
                            index = i;
                            break;
                    }
            }
            if(userStatus && index !=-1){
                    for(int i = index;i<(noOfStds-1);i++){
                            students[i] = students[i+1];
                    }
                    noOfStds--;
                    cout<<"Student Successfully Deleted !\n";
            }else{
                cout<<"No User Found With ID: "<<userInput<<"\n";
            }
            cout<<"Do you want to delete more Students (y/n) : ";
            cin>>choice;
        }while(choice=='y' || choice=='Y');
}
//! Display Search records
void viewRecords(Student students[],int noOfStds,int index){
    if(noOfStds>0){
    cout<<"╭───────────────────────────────────────────────────────────────────────────────────────────────────────\n";
    cout<<"│\n";
    cout<<"│-▶>> \033[32mStudent ID: \033[31m"<<students[index].personalInfo.stdID<<"\033[0m\n";
    cout<<"│\n";
    cout<<"│\t\033[34mPERSONAL INFORMATION \033[0m\n";
    cout<<"│\n";
    cout<<"│\t\tFull Name: "<<students[index].personalInfo.fullName<<"\n";
    cout<<"│\n";
    cout<<"│\t\tDOB: "<<students[index].personalInfo.dob<<"\n";
    cout<<"│\n";
    cout<<"│\t\tGender: "<<students[index].personalInfo.gender<<"\n";
    cout<<"│\n";
    cout<<"│\t\tStudent ID: "<<students[index].personalInfo.stdID<<"\n";
    cout<<"│\n";
    cout<<"│\t\033[34mCONTACT INFORMATION \033[0m\n";
    cout<<"│\n";
    cout<<"│\t\tPhone Number: "<<students[index].contactInfo.phoneNumber<<"\n";
    cout<<"│\n";
    cout<<"│\t\tEmail: \033[36m"<<students[index].contactInfo.emailAddress<<"\033[0m\n";
    cout<<"│\n";
    cout<<"│\t\033[34mACEDAMICS INFORMATION \033[0m\n";
    cout<<"│\n";
    cout<<"│\t\tCourses Enrolled: "<<students[index].acedamicInfo.noOfcourses<<"\n";
    cout<<"│\n";
    cout<<"│\t\t\t\t╭────────────────────────────────────────────────────────────────────╮\n";
    cout<<"│\t\t\t\t│NAMES"<<"\t\t"<<"TOTAL MARKS"<<"\t\t"<<"OBTAINED MARKS"<<"\t\t"<<"GRADE│"<<"\n";
    cout<<"│\t\t\t\t│┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅│"<<"\n";
    cout<<"│\t\t\t\t╭─────────────────────────────────────────────────────────────────────────────────────────╮\n";
    cout<<"│\t\t\t\t│NAMES"<<fixed<<setw(29)<<"TOTAL MARKS"<<setw(29)<<"OBTAINED MARKS"<<setw(29)<<"GRADE│"<<"\n";
    cout<<"│\t\t\t\t│┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅│"<<"\n";
    for(int j=0;j<students[index].acedamicInfo.noOfcourses;j++){
    cout<<"│\t\t\t\t│"<<fixed<<students[index].acedamicInfo.coursesNames[j]<<fixed<<setw(6)<<students[index].acedamicInfo.coursesTotalMarks[j]<<setw(18)<<students[index].acedamicInfo.coursesObtainedMarks[j]<<setw(37)<<students[index].acedamicInfo.coursesGrades[j]<<setw(8)<<fixed<<"│\n";
    }
     cout<<"│\t\t\t\t╰─────────────────────────────────────────────────────────────────────────────────────────╯\n";
    cout<<"│\n";
    cout<<"│\n";
    cout<<"│\n";
    cout<<"╰───────────────────────────────────────────────────────────────────────────────────────────────────────\n";
    cout<<"\n\n";
    }else{
        cout<<"No Students Found to Display !\n";
    }
}
// ! Student Id index returner
int studentID(Student students[],int size,string id){
    for(int i=0 ;i<size;i++){
                if(!students[i].personalInfo.stdID.compare(id)){
                        return i;
                }             
        }
    return -1;
}
//! Update Student Record ->5
void updateRecordsMenu (){
        cout<<"╭──────────────────────────────────────────────────────────────────\n";
        cout<<"│\n";    
        cout<<"│▶> [1]- Update Student Personal Information.\n";    
        cout<<"│\n";    
        cout<<"│▶> [2]- Update Student Contact Information.\n";    
        cout<<"│\n";    
        cout<<"│▶> [3]- Update Student Acedamics Information.\n";
        cout<<"│ "<<endl;
        cout<<"│\t\tselect any of the 3 options"<<endl;
        cout<<"│ "<<endl;
        cout<<"╰──────────────────────·······"<<endl;    
}

void updateRecord(Student students[],int noOfStudents){
    string userID;
    cout<<"Enter Student ID to update his record : ";
    cin>>userID;
    int index = studentID(students,noOfStudents,userID);
    if(index != -1){
        char choose='n';
      do{
        int choice;
        updateRecordsMenu();
        do{
            cout<<"Enter your choice [1-3] : ";
            cin>>choice;
            if(!(choice>=1 && choice<=3)){
                cout<<"Please Enter correct option 1-3 \033[0m\n";
            }
        }while(!(choice>=1 && choice<=3));

        if(choice==1){
            cout<<"\033[31m Updation Of Student Personal Information  for "<<students[index].personalInfo.stdID<<"\033[0m"<<endl;
            do{
            cin.ignore();
            cout<<"\tEnter Your Full Name (e.g Uzair Akram): ";
            getline(cin,students[index].personalInfo.fullName);
            if(!validateStudentName(students[index].personalInfo.fullName)){
                beep();
                cout<<"\033[31m Please Enter a correct name , name must be 4 characters long and does not include any digit or symbols !\033[0m\n";
            }
        }while(!validateStudentName(students[index].personalInfo.fullName));
        do{
            cout<<"Enter your Date of Birth format:dd/mm/yy : ";
            cin>>students[index].personalInfo.dob;
        }while(!validateDob(students[index].personalInfo.dob));
        do{
            cout<<"Gender ? (M/F/O)";
            cin>>students[index].personalInfo.gender;
            if(tolower(students[index].personalInfo.gender) !='m' && tolower(students[index].personalInfo.gender) !='f' && tolower(students[index].personalInfo.gender) !='o'){
                beep();
                cout<<"\033[31m Please Enter Correct Gender ! \033[0m\n";
            }
        }while(tolower(students[index].personalInfo.gender) !='m' && tolower(students[index].personalInfo.gender) !='f' && tolower(students[index].personalInfo.gender) !='o');
        }
        else if (choice ==2){
            cout<<"\033[31m Updation Of Student Contact Information  for "<<students[index].personalInfo.stdID<<"\033[0m"<<endl;
            do{
                cout<<"Enter Emergency Contact Number : ";
                cin>>students[index].contactInfo.phoneNumber;
            }while(!validatePhoneNumber(students[index].contactInfo.phoneNumber));
            do{
                cin.ignore();
                cout<<"Enter your Email Address : ";
                cin>>students[index].contactInfo.emailAddress;
                if(!students[index].contactInfo.validateEmail()){
                    beep();
                    cout<<"\033[31mSorry! Please enter correct email address !\033[0m\n";
                }
            }while(!students[index].contactInfo.validateEmail());
        }
        else if (choice == 3){
            cout<<"\033[31m Updation Of Student Acedamics Information  for "<<students[index].personalInfo.stdID<<"\033[0m"<<endl;
            do{
            cout<<"Enter how many courses have you Enrolled In ! : ";
            cin>>students[index].acedamicInfo.noOfcourses;
            }while(students[index].acedamicInfo.noOfcourses<0 && students[index].acedamicInfo.noOfcourses>100);
            students[index].acedamicInfo.getCoursesNames();
            students[index].acedamicInfo.getCoursesTotalMarks();        
            students[index].acedamicInfo.getCoursesObtainedMarks();
            students[index].acedamicInfo.setCoursesGrades();
        }
            cout<<"Do You Want to update again ? (y/n)";
            cin>>choose;
      }while(tolower(choose) =='y');
    }else{
        cout<<"Sorry no Data was found with that ID \n";
    }
}


// ! sorting data by name/ID
/**
 * The function `sortData` sorts an array of `Student` objects either by name or by ID based on user
 * input.
 * 
 * @param students The `students` parameter is an array of `Student` Structure, and the `size` parameter
 * indicates the number of elements in the array. The function `sortData` sorts the array of `Student`
 * Structure based on the user's choice of sorting criteria - either by name or by ID.
 * @param size The `size` parameter in the `sortData` function represents the number of elements in the
 * `students` array that needs to be sorted. It indicates the total number of `Student` objects in the
 * array that require sorting based on the user's choice of sorting criteria (either by name or by
 */
void sortData(Student students[],int size){
    int choice;
    do{
     cout<<"▶> [1]- Sort by Name \n";
     cout<<"▶> [2]- Sort by ID \n";
     cout<<"Enter Your Choice [1-2] : ";
     cin>>choice;
    }while(choice!=1 && choice!=2);
    switch(choice){
        case 1:
                for(int i=0;i<size;i++){
                    for(int j=0;j<(size-i-1);j++){
                        if(students[j].personalInfo.fullName>students[j+1].personalInfo.fullName){
                            Student temp = students[j];
                            students[j] = students[j+1];
                            students[j+1] = temp;
                        }
                    }
                }
                break;
        case 2:
                for(int i=0;i<size;i++){
                    for(int j=0;j<(size-i-1);j++){
                        if(students[j].personalInfo.stdID > students[j+1].personalInfo.stdID){
                                Student temp = students[j];
                                students[j] = students[j+1];
                                students[j+1] = temp;
                        }
                    }
                }
                break;
    }
}
// ! Display Top Performers [8]
void displayTopPerformers(Student students[],int noOfStds){
        //! Sorting students by grades to obtain top performers
        for(int i=0;i<noOfStds;i++){
            for(int j=0;j<(noOfStds-i-1);j++){
            if(students[j].acedamicInfo.averageGrade > students[j+1].acedamicInfo.averageGrade){
                                Student temp = students[j];
                                students[j] = students[j+1];
                                students[j+1] = temp;
            }
            }
        }  
        // we are displaying  top performers
        int noOfTopPerforms=5;
        cout<<"Top Performers : \n"; 
        if(noOfStds<5){
            noOfTopPerforms=noOfStds;
        }
        for(int i=0;i<noOfTopPerforms;i++){
            viewRecords(students,noOfTopPerforms,i);
        }
}
// ! Grade Analysis [9]
void gradeAnalysis(Student students[],int noOfStds){
    for(int i=0; i<noOfStds; i++){
        if(students[i].acedamicInfo.averageGrade =='A') {
            cout<<"\033[34m GRADE : A\033[0m"<<endl;      
            viewRecords(students,noOfStds,i);
        }
        else if (students[i].acedamicInfo.averageGrade =='F'){
            cout<<"\033[34m GRADE : F\033[0m"<<endl;      
            viewRecords(students,noOfStds,i);       
        }
    }
}
// ! Saving record in a file
bool saveRecords(Student students[],int noOfStds,bool avgGrade){
    fstream file("./records/studentsRecord.txt",ios::out);
    if(!file){
        file.close();
        return false;
    }
    else{
    file<<"╭───────────────────────────────────────────────────────────────────────────────────────────────────────\n";
    file<<"│\n";
    for(int i=0;i<noOfStds;i++){
    file<<"│-▶>> Student ID: "<<students[i].personalInfo.stdID<<"\n";
    file<<"│\n";
    file<<"│\tPERSONAL INFORMATION \n";
    file<<"│\n";
    file<<"│\t\tFull Name: "<<students[i].personalInfo.fullName<<"\n";
    file<<"│\n";
    file<<"│\t\tDOB: "<<students[i].personalInfo.dob<<"\n";
    file<<"│\n";
    file<<"│\t\tGender: "<<students[i].personalInfo.gender<<"\n";
    file<<"│\n";
    file<<"│\t\tStudent ID: "<<students[i].personalInfo.stdID<<"\n";
    file<<"│\n";
    file<<"│\tCONTACT INFORMATION \n";
    file<<"│\n";
    file<<"│\t\tPhone Number: "<<students[i].contactInfo.phoneNumber<<"\n";
    file<<"│\n";
    file<<"│\t\tEmail: "<<students[i].contactInfo.emailAddress<<"\n";
    file<<"│\n";
    file<<"│\tACEDAMICS INFORMATION \n";
    file<<"│\n";
    file<<"│\t\tCourses Enrolled: "<<students[i].acedamicInfo.noOfcourses<<"\n";
    file<<"│\n";
    file<<"│\t\t\t\t╭─────────────────────────────────────────────────────────────────────────────────────────╮\n";
    file<<"│\t\t\t\t│NAMES"<<fixed<<setw(29)<<"TOTAL MARKS"<<setw(29)<<"OBTAINED MARKS"<<setw(29)<<"GRADE│"<<"\n";
    file<<"│\t\t\t\t│┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅│"<<"\n";
    for(int j=0;j<students[i].acedamicInfo.noOfcourses;j++){
    file<<"│\t\t\t\t│"<<fixed<<students[i].acedamicInfo.coursesNames[j]<<fixed<<setw(6)<<students[i].acedamicInfo.coursesTotalMarks[j]<<setw(18)<<students[i].acedamicInfo.coursesObtainedMarks[j]<<setw(37)<<students[i].acedamicInfo.coursesGrades[j]<<setw(8)<<fixed<<"│\n";
    }
    if(avgGrade){
    file<<"│\t\t\t\t│┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅│"<<"\n";
    file<<"│\t\t\t\t│"<<fixed<<setw(50)<<"GRADE = "<<students[i].acedamicInfo.averageGrade<<setw(41)<<"│"<<endl;
    }
    file<<"│\t\t\t\t╰─────────────────────────────────────────────────────────────────────────────────────────╯\n";
    file<<"│\n";
    file<<"│\n";
    }
    file<<"│\n";
    file<<"╰───────────────────────────────────────────────────────────────────────────────────────────────────────\n";
        file.close();
        return true;
    }
}
bool loadRecords(){
    string line;
    fstream file("./records/studentsRecord.txt",ios::in);
    if(!file){
        cout<<"Sorry No records Found Please first save Record !\n";
        return false;
    }
    else{
    while(getline(file,line)){
        bool check=false;
        if(line.length() !=0){
            for(char ch : line){
                if(!isspace(ch)){
                    check=true;
                    break;
                }
            }
            if(check){
                cout<<line<<endl;
            }else{
                return false;
            }
        }
    }
        return true;
    }
}
// done by anjum

void attendanceTrack(Student students[],int noOfStds){
    char attandance[noOfStds]={'0'};
    int choice;
    bool track=false;
    bool saveTrack=false;
    char continueUser='n';
    do{
        cout<<"Press 1 for track attandance\n";
        cout<<"Press 2 for view attdance \n";
        cout<<"Press 3 for save attandance record\n";
        cout<<"Press 4 for load attandance record\n";
        cout<<"Press 5 to goback to main Menu \n";  
        do{
            cout<<"Enter Your choice [1-5] :";
            cin>>choice;
            if(!(choice>=1 && choice<=5)){
                track=true;
                cout<<"Please enter valid choice\n";
            }
        }while(!(choice>=1 && choice<=5));
        if(noOfStds>0){
        if(choice ==1){
            track=true;
            cout<<"Tracking attandace... \n";
            for(int i=0;i<noOfStds;i++){
                do{
                    cout<<"\t Student Name : "<<students[i].personalInfo.fullName<<endl;
                    cout<<"Enter P if present A if absent :  ";
                    cin>>attandance[i];
                    attandance[i] = toupper(attandance[i]); 
                }while(!(attandance[i]=='A' || attandance[i]=='P'));
            }
        }
        else if(choice == 2){
            if(track){
                cout<<"\033[33mTracked Attandance "<<noOfStds<<"\033[0m"<<endl;
                for(int i=0;i<noOfStds;i++){
                    cout<<fixed<<students[i].personalInfo.stdID<<setw(20)<<students[i].personalInfo.fullName<<setw(20)<<attandance[i]<<endl;
                }
            }else{
                cout<<"Please first track attandance \n";
            }
        }
        else if(choice == 3){
            if(track){
                saveTrack=true;
                cout<<"Saving records ...\n";
                fstream file("./AttandaceRecord/attandance.txt",ios::out);
                if(!file){
                    cout<<"File Does Not Opened please try later !\n";
                }else{
                    file<<"Tracked Attandance "<<noOfStds<<endl;
                    for(int i=0;i<noOfStds;i++){
                        file<<fixed<<students[i].personalInfo.stdID<<setw(20)<<students[i].personalInfo.fullName<<setw(20)<<attandance[i]<<endl;
                    }
                    cout<<"Attandance saved successfully ✅\n";
                }
            }else{
                cout<<"Please first track attandance \n";
            }
        }
        }else{
            cout<<"Please First add record !\n";
        }
         if(choice == 4){
                cout<<"loading records ...\n";
                fstream file("./AttandaceRecord/attandance.txt",ios::in);
                string line;
                while(getline(file,line)){
                    cout<<line<<endl;
                }
            }
        else if(choice == 5){
            mainMenu();
        }
        cout<<"Do you want to continue to attandance track operation (y/n) :";
        cin>>continueUser;
    }while(continueUser == 'y');

}