#include <iostream>
#include"string"
#include"cctype"
#include"windows.h"
#include"iomanip"
#include"fstream"
#include"time.h"
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
void displayCurrentDatenTime(void);
void currentLoginStatus(void);

//! MAIN MENU PROTOTYPES
void mainMenuDisplay(void);
void mainMenu(void);

//! Student Record Prototype & structure
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
void viewRecords(Student[],int);
void viewRecords(Student[],int,int);

// ! SEARCH FOR A STUDENT
void searchStudents(Student[],int);
// ! Update student record by ID
void updateRecordsMenu(void);
int studentID(Student[],int,string);        // --> returns the index of found id if not found return -1
void updateRecord(Student[],int);
//!                                 "MAIN SCOPE "
int main() {
    bool res = loginMenu();
    if(res){
        mainMenu();
    }
    return 0;
}
// !                                " LOGIN MENU CODE "
void displayHeader(){
    cout<<"\n\n\n";
    cout<<"░█▀▀▀█ ▀▀█▀▀ ░█─░█ ░█▀▀▄ ░█▀▀▀ ░█▄─░█ ▀▀█▀▀ 　 ░█▀▄▀█ ─█▀▀█ ░█▄─░█ ─█▀▀█ ░█▀▀█ ░█▀▀▀ ░█▀▄▀█ ░█▀▀▀ ░█▄─░█ ▀▀█▀▀ 　 ░█▀▀▀█ ░█──░█ ░█▀▀▀█ ▀▀█▀▀ ░█▀▀▀ ░█▀▄▀█\n";
    cout<<"─▀▀▀▄▄ ─░█── ░█─░█ ░█─░█ ░█▀▀▀ ░█░█░█ ─░█── 　 ░█░█░█ ░█▄▄█ ░█░█░█ ░█▄▄█ ░█─▄▄ ░█▀▀▀ ░█░█░█ ░█▀▀▀ ░█░█░█ ─░█── 　 ─▀▀▀▄▄ ░█▄▄▄█ ─▀▀▀▄▄ ─░█── ░█▀▀▀ ░█░█░█\n";
    cout<<"░█▄▄▄█ ─░█── ─▀▄▄▀ ░█▄▄▀ ░█▄▄▄ ░█──▀█ ─░█── 　 ░█──░█ ░█─░█ ░█──▀█ ░█─░█ ░█▄▄█ ░█▄▄▄ ░█──░█ ░█▄▄▄ ░█──▀█ ─░█── 　 ░█▄▄▄█ ──░█── ░█▄▄▄█ ─░█── ░█▄▄▄ ░█──░█\n";
    cout<<"\n\n\n";
}
//! it validates login ID and return 0 in false case else return 1
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
// @attention  displays the id to the user
void loginID(){
    string id =generatingLoginID();
    while(!validID(id)){
        id = generatingLoginID();
    }
    cout<<"\nYour LoginID is \033[33m"<<id<<"\033[0m"<<endl;
    fstream file("./LoginID/ID.txt",ios::out);
    if(!file){
        beep();
        cerr<<"Sorry we have some issues wile saving your ID \n";
    }else{
        file<<id;
        cout<<"\033[0mWe Successfully ✅ saved your Login Id you can use it later for login !\033[0m"<<endl;
    }
    file.close();
}
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
            cerr<<"Sorry File is corrupted ! it has not a valid ID Check it ! "; ///** */
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
void displayCurrentDatenTime(){
     time_t now = time(0);
     char* dnt = ctime(&now);
     cout<<dnt<<endl;
}
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
       cout<<"╰──────────────···"<<endl;
}
void mainMenu(){
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
                viewRecords(students,trackNumberOfStudentsAdded);
            }else{
                cout<<"\033[32m-▶>> You Selected Option 2\033[0m"<<endl;
                cout<<"No records found please first add record !\n";
            }
        }
        else if(choice==3){
            if(track){
                cout<<"\033[32m-▶>> You Selected Option 3\033[0m"<<endl;
                searchStudents(students,trackNumberOfStudentsAdded);
            }else{
                cout<<"\033[32m-▶>> You Selected Option 3\033[0m"<<endl;
                cout<<"No records found please first add record !\n";
            }
        }
        else if(choice==4){
             if(track){
                cout<<"\033[32m-▶>> You Selected Option 4\033[0m"<<endl;
            }else{
                cout<<"\033[32m-▶>> You Selected Option 4\033[0m"<<endl;
                cout<<"No records found to delete please first add record !\n";
            }
        }
        else if(choice==5){
             if(track){
                cout<<"\033[32m-▶>> You Selected Option 5\033[0m"<<endl;
                updateRecord(students,trackNumberOfStudentsAdded);
            }else{
                cout<<"\033[32m-▶>> You Selected Option 5\033[0m"<<endl;
                cout<<"No records found to update please first add record !\n";
            }
        }
        else if(choice==6){
            if(track){
                cout<<"\033[32m-▶>> You Selected Option 6\033[0m"<<endl;
            }else{
                cout<<"\033[32m-▶>> You Selected Option 6\033[0m"<<endl;
                cout<<"No records found to Calculate Grades please first add record !\n";
            }
        }
        else if(choice==7){
            if(track){
                cout<<"\033[32m-▶>> You Selected Option 7\033[0m"<<endl;
            }else{
                cout<<"\033[32m-▶>> You Selected Option 7\033[0m"<<endl;
                cout<<"No records found to sort please first add record !\n";
            }
        }
        else if(choice==8){
            if(track){
                cout<<"\033[32m-▶>> You Selected Option 8\033[0m"<<endl;
            }else{
                cout<<"\033[32m-▶>> You Selected Option 8\033[0m"<<endl;
                cout<<"No records found to Calculate Grades please first add record !\n";
            }
        }
        else if(choice==9){
            if(track){
                cout<<"\033[32m-▶>> You Selected Option 9\033[0m"<<endl;
            }else{
                cout<<"\033[32m-▶>> You Selected Option 9\033[0m"<<endl;
                cout<<"No records found to Calculate Grades please first add record !\n";
            }
        }
        else if(choice==10){
                cout<<"\033[32m-▶>> You Selected Option 10\033[0m"<<endl;
        }
        else if(choice==11){
                cout<<"\033[32m-▶>> You Selected Option 11\033[0m"<<endl;
        }
        else if(choice==13){
            cout<<"\033[32m-▶>> You Selected Option 13\033[0m"<<endl;
            loginMenu();
            break;
        }
        else if (choice==14){
            cout<<"\033[32m-▶>> You Selected Option 14\033[0m"<<endl;
            cout<<"Thanks ! GoodBye "<<endl;
            exit(0);
        }
        cout<<"Do you want to continue ? (y/n) : ";
        cin>>choiceMenu;
        if(tolower(choiceMenu) != 'y'){
            cout<<"GoodeBye ....\n";
            break;
        }
    }while(tolower(choiceMenu) == 'y');

}

//!     adding new student Record
void addNewStudent(Student students[],int& trackNumberOfStudentsAdded){
    cout<<"How many students to add ? ";
    cin>>trackNumberOfStudentsAdded;
    for(int i=0;i<trackNumberOfStudentsAdded;i++){
        cout<<"\t Student: "<<i+1<<endl;
        cout<<"\033[34m\t\t PERSONAL INFORMATION :\033[0m\n";
        do{
            cin.ignore();
            cout<<"\tEnter Your Full Name (e.g Uzair Akram): ";
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
        do{
        cin.ignore();
        cout<<"\033[34m\t\t CONTACT INFORMATION :\033[0m\n";
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
//! generating student ID 
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
void viewRecords(Student students[],int noOfStds){
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
    cout<<"│\t\t\t\t╭────────────────────────────────────────────────────────────────────╮\n";
    cout<<"│\t\t\t\t│NAMES"<<"\t\t"<<"TOTAL MARKS"<<"\t\t"<<"OBTAINED MARKS"<<"\t\t"<<"GRADE│"<<"\n";
    cout<<"│\t\t\t\t│┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅│"<<"\n";
    for(int j=0;j<students[i].acedamicInfo.noOfcourses;j++){
    cout<<"│\t\t\t\t│"<<fixed<<students[i].acedamicInfo.coursesNames[j]<<fixed<<setw(18)<<students[i].acedamicInfo.coursesTotalMarks[j]<<setw(28)<<students[i].acedamicInfo.coursesObtainedMarks[j]<<setw(18)<<students[i].acedamicInfo.coursesGrades[j]<<setw(6)<<fixed<<"│\n";
    }
    cout<<"│\t\t\t\t╰────────────────────────────────────────────────────────────────────╯\n";
    cout<<"│\n";
    cout<<"│\n";
    }
    cout<<"│\n";
    cout<<"╰───────────────────────────────────────────────────────────────────────────────────────────────────────\n";
}

// !    Serach for Students -> 3
void searchStudents(Student students[],int noOfStudents){
        string userInput="";
        cout<<"Enter Student ID or Name To Search :";
        cin>>userInput;

        // ! Linear Search
        for(int i=0 ;i<noOfStudents;i++){
                if(!students[i].personalInfo.fullName.compare(userInput) || !students[i].personalInfo.stdID.compare(userInput)){
                        viewRecords(students,noOfStudents,i);
                        return;
                }             
        }
    cout<<"Sorry No Record found with "<<userInput<<endl;
}
//! Display Search records
void viewRecords(Student students[],int noOfStds,int index){
    cout<<"\033[33m\t\t STUDENT FOUND "<<"\033[0m\n";
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
    for(int j=0;j<students[index].acedamicInfo.noOfcourses;j++){
    cout<<"│\t\t\t\t│"<<fixed<<students[index].acedamicInfo.coursesNames[j]<<fixed<<setw(18)<<students[index].acedamicInfo.coursesTotalMarks[j]<<setw(28)<<students[index].acedamicInfo.coursesObtainedMarks[j]<<setw(18)<<students[index].acedamicInfo.coursesGrades[j]<<setw(6)<<fixed<<"│\n";
    }
    cout<<"│\t\t\t\t╰────────────────────────────────────────────────────────────────────╯\n";
    cout<<"│\n";
    cout<<"│\n";
    cout<<"│\n";
    cout<<"╰───────────────────────────────────────────────────────────────────────────────────────────────────────\n";
    cout<<"\n\n";
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
            cout<<"\033[31m Updation Of Student Personal Information  for "<<students[index].personalInfo.stdID<<endl;
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
            cout<<"\033[31m Updation Of Student Personal Information  for "<<students[index].personalInfo.stdID<<endl;
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
            cout<<"\033[31m Updation Of Student Personal Information  for "<<students[index].personalInfo.stdID<<endl;
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