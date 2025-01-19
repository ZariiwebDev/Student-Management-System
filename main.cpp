#include <iostream>
#include"string"
#include"cctype"
#include"windows.h"
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
    int noOfcourses=6;                              // number of courses a student has been EnrolledIn 
    string *coursesNames = new string[noOfcourses];           // stores the courses names
    void getCoursesNames();                     /* adds the courses names into @param coursesNames */
    int *coursesTotalMarks = new int[noOfcourses];          // stores the total marks of each course
    void getCoursesTotalMarks();              /* adds the courses names into @param coursesNames */
    int *coursesObtainedMarks = new int[noOfcourses];     // stores the obtained marks of each course
    void getCoursesObtainedMarks();         /* adds the courses names into @param coursesObtainedMarks */
    int totalInternalMarks;                // stores total marks of quiz lab assessments
    int obtainedInternalMarks;            // stores obtained of totalInternalMarks
};
struct Student{
    StudentPersonalInformation personalInfo;
    StudentContactInformation contactInfo;
    StudentAcedamicInformation acedamicInfo;
};


void addNewStudent(Student*,int&);
void studentRecord(int);
string generateStudentID();
bool validateStudentName(string studentName);
bool validateDob(string dob);
bool validatePhoneNumber(string phoneNumber);

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
            studentRecord(choice);        // adding new student
        }
        else if(choice==2){ 
            cout<<"\033[32m-▶>> You Selected Option 2\033[0m"<<endl;
            studentRecord(choice);
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

void studentRecord(int choice){
     int trackNumberOfStudentsAdded=1;
    Student* students= new Student[trackNumberOfStudentsAdded];
        if(choice ==1){
            addNewStudent(students,trackNumberOfStudentsAdded);
        }else if(choice==2){
            cout<<"Display";
        }

    delete[] students;
}


//!     adding new student Record
void addNewStudent(Student* students,int& trackNumberOfStudentsAdded){
    bool choice=false;
    do{
        for(int i=0;i<trackNumberOfStudentsAdded;i++){
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
            cin.ignore();
            cout<<"Enter your Date of Birth format:dd/mm/yy : ";
            getline(cin,students[i].personalInfo.dob);
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
        }
        cout<<"Do you want to add more students data ? (press 0 for no / press 1 for yes):";
        cin>>choice;
        if(choice==1){
            choice=true;
            trackNumberOfStudentsAdded++;
        }
        else if (choice !=1){
            break;
        }
    }while(choice);
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