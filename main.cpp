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
    int phoneNumber;
    string emailAddress;
    bool validateEmail();
};
struct StudentAcedamicInformation{
    int noOfcourses;                              // number of courses a student has been EnrolledIn 
    string *coursesNames = new string;           // stores the courses names
    void getCoursesNames();                     /* adds the courses names into @param coursesNames */
    int *coursesTotalMarks = new int;          // stores the total marks of each course
    void getCoursesTotalMarks();              /* adds the courses names into @param coursesNames */
    int *coursesObtainedMarks = new int;     // stores the obtained marks of each course
    void getCoursesObtainedMarks();         /* adds the courses names into @param coursesObtainedMarks */
    int totalInternalMarks;                // stores total marks of quiz lab assessments
    int obtainedInternalMarks;            // stores obtained of totalInternalMarks
};
struct Student{
    StudentPersonalInformation personalInfo;
    StudentContactInformation contactInfo;
    StudentAcedamicInformation acedamicInfo;
};

void addNewStudent();
string generateStudentID();



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
            addNewStudent();        // addind new student
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
    }while(true);
}


//!         [1]- adding new student Record
void addNewStudent(){
    bool choice=false;
    int trackNumberOfStudentsAdded=1;
    Student* students= new Student;
    do{
        cout<<"/033[34m\t\t PERSONAL INFORMATION :\033[0m\n";
        cout<<"\tEnter Your Full Name (e.g Uzair Akram): ";
        cin.ignore();
        getline(cin,students->personalInfo.fullName);
        cout<<"Enter your Date of Birth format:dd/mm/yy : ";
        cin.ignore();
        getline(cin,students->personalInfo.dob);
        do{
            cout<<"Gender ? (M/F/O)";
            cin>>students->personalInfo.gender;
            if(tolower(students->personalInfo.gender) !='m' && tolower(students->personalInfo.gender) !='f' && tolower(students->personalInfo.gender) !='o'){
                
            }
        }while(tolower(students->personalInfo.gender) !='m' && tolower(students->personalInfo.gender) !='f' && tolower(students->personalInfo.gender) !='o');
        cout<<"Generating ....\n";
        students->personalInfo.stdID = generateStudentID();
        if(students->personalInfo.validateID(students->personalInfo.stdID)){
                cout<<"Student ID assigned : \033[34m"<<students->personalInfo.stdID<<"\033[0m"<<endl;
        }
    }while(choice);


    delete students;
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