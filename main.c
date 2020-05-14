#include "myfunctions.h"

//the username for HR login is "hr" and the password is "hr1234".
//the academic leader and Lecturers profile must be created first to get login details. 

struct User
{	// this structure contains datas related to user info.
	// this structur used when a new profile is created.
	int userID;
	char Name[20];
	char Gender;
	int age;
	char userName[20];
	char passWord[20];
};


struct userList
{
	//this structure is used in listing the users details and recording it into a file.
	int userID;
	char Name[30];
	char role[30];
	char userName[30];
	char passWord[30];
};


struct faqList
{
	int faqID;
	char question[100];
	char answer[200];
};



struct leaveApplication
{
	int leaveID;
	int UserID;
	struct LeaveDate
	{
		int day;
		int month;
		int year;
	}startingDate;

	int totalDay;
	int status;
};

//Declaration of global variables for file names.
int SharedID;
char userFileName[] = "UserFile.txt";	//in this file user's login details are stored.

char tempFileName[]= "tempUser.txt";

char faqFileName[] = "FAQ.txt";		// in this file all the faqs are stored with their id.

char leaveFileName[] = "LeaveApplicationFile.txt";	// here all the leave applications are stored.


int main()
{
//	main fucntion 


////LecturerActivity();
//academicActivity();
//adminActivity();
	Header();
	MainMenu();
	system("pause");
return 0;

}

void Header(){
	// this is the header for the mainmenu.
	printf("\t\t__________________________________________________________\n");
	printf("\t\t________EMPLOYEES LEAVE MANAGEMENT SYSTEM (ELMS)__________\n");
	printf("\t\t__________________________________________________________\n");
	printf("\n\n\n");

}


int LastuserID(){
	//this function assigns a new user iD everytime when a new profile is created.
	int userID = 0;
	FILE *myfile;
	myfile = fopen("User.txt", "rb");
	struct User user;
	while ((fread(&user, sizeof(struct User), 1 , myfile) ) == 1){
		userID = user.userID;
	}

	fclose(myfile);
	return userID+1;
}





int ValidationInteger(){
//this function checks whether the input is integer or stirng.
int n;	
		while (scanf("%d", &n)!=1)
		{
			system("cls");
			printf("\n\n\n\n\t\t:::YOU ARE ONLY ALLOWED TO ENTER INTEGER:::\n");
			Sleep(500);
			system("cls");
			printf("\n\n\t\tENTER AGAIN: ");
			while (getchar()!='\n');
		}
		return n;
}

void adminMenu(){
	// this function displays the header of the HR menu.
	printf("\t\t____________________________________________\n");
	printf("\t\t___________________HR MENU__________________\n");
	printf("\t\t____________________________________________\n");
	printf("\n\n\n");
}


void adminLogin(){
//	this function is for the login of admin. if accepts the username and password of HR and verifies it.
	struct Admin
	{
		char userName[20];
		char password[20];

	};

	struct Admin admin;
	printf("\t\tENTER USERNAME:");
	scanf("%s", admin.userName);
	printf("\t\tENTER PASSWORD:");
	scanf("%s", admin.password);
	if ((strcmp(strlwr(admin.userName), "hr")) == 0 && (strcmp(strlwr(admin.password), "hr1234") == 0) )
	// if username is hr and password hr1234 then only hr can get logged in to the system
	{
	    system("cls");		//clears the screen
		adminActivity();
	}
	else
	{	// if the password or username is incorrect this block of code executes.
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n\n\t....:::SORRY!! YOU ENTERED WRONG INFORMATIONS::::......\n");
		Sleep(700);
		system("cls");
		adminMenu();
		adminLogin();
	}

}


void listofUserList(){
//this function displays the lists of user whose accounts has been created in the system.
	FILE *ufile;
	ufile = fopen(userFileName, "rb");		//opens file in read mode.
	struct userList tr;		//naming variable for the structure userList.

	printf("\t\t_____________________________________________________________________________________\n");
	printf("\t\t_____________________________________USER LIST_______________________________________\n");

	printf("\t\t+ ID         NAME                ROLE              USERNAME           PASSWORD       +\n");
	printf("\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	while ((fread(&tr, sizeof(struct userList), 1 , ufile) ) == 1){

		{
			printf("\t\t+  %d        %-15s     %-15s       %-10s       %-10s\n", tr.userID,  tr.Name, tr.role, tr.userName, tr.passWord);
		}

	}

	printf("\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n\n");
	fclose(ufile);
}

void searchLecturerTable(){


    listofUserList();

	char userSearchKeyword[20];		//variable to search user profile in HR menu.
	printf("\t\tENTER USER NAME TO SEARCH: ");
	gets(userSearchKeyword);
    int count = 0;
	FILE *myfile;
	myfile = fopen(userFileName, "rb");		//opens file containing user details in read mode.
	struct userList tr;		//declaring variable name for structure userList.

	printf("\t\t_____________________________________________________________________________________\n");
	printf("\t\t_____________________________________USER LIST_______________________________________\n");

	printf("\t\t+ ID         NAME                ROLE              USERNAME           PASSWORD       +\n");
	printf("\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	while ((fread(&tr, sizeof(struct userList), 1 , myfile) ) == 1){

		if(strstr(strlwr(tr.Name),strlwr(userSearchKeyword)) != NULL ){
			printf("\t\t+  %d        %-15s     %-15s       %-10s       %-10s\n", tr.userID,  tr.Name, tr.role, tr.userName, tr.passWord);
			count++;
		}

	}

	if(count==0){		// if the file is empty this block of code is displayed.
    printf("\t\t+++++++++++++++++                NO RECORD FOUND                  ++++++++++++++++++++\n");
	}

	printf("\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n\n");
	fclose(myfile);

	printf("\t\t...:::PRESS ANY KEY TO CONTINUE:::....");
	getch();
	system("cls");
	adminActivity();	// redirects to the HR menu.

}



void viewOnlyLecturerTable(){
//this for listing only lecturers details. lists the number of lectrers
    int count = 0;
	FILE *myfile;
	myfile = fopen(userFileName, "rb");
	struct userList tr;		//declaring variable name for structure.

	printf("\t\t_____________________________________________________________________________________\n");
	printf("\t\t_________________________________LECTURER LIST_______________________________________\n");

	printf("\t\t+ ID         NAME                ROLE              USERNAME           PASSWORD       +\n");
	printf("\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	while ((fread(&tr, sizeof(struct userList), 1 , myfile) ) == 1){

		if(strstr(strlwr(tr.role),"lecturer") != NULL ){
			printf("\t\t+  %d        %-15s     %-15s       %-10s       %-10s\n", tr.userID,  tr.Name, tr.role, tr.userName, tr.passWord);
			count++;
		}

	}

	if(count==0){
    printf("\t\t+++++++++++++++++                NO RECORD FOUND                  ++++++++++++++++++++\n");
	}

	printf("\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n\n");
	fclose(myfile);		//file is closed.

	printf("\t\t...:::PRESS ANY KEY TO CONTINUE:::....");
	getch();
	system("cls");
	adminActivity();	//redirect to HR menu.

}



int serachLastID(char *fileName){
	int userID = 0;
	FILE *myfile;		//declaring file pointer.
	myfile = fopen(fileName, "rb");
	struct userList user;		//declaring structure variable name.
	while ((fread(&user, sizeof(struct userList), 1 , myfile) ) == 1){
		userID = user.userID;		//userID is assigned from file.
	}

	fclose(myfile);
	return userID+1;	//user ID is incremented
}

void registrationNewUser(char *array){
// new user can be registered from this function.
    struct userList user;	
    user.userID = serachLastID(userFileName);
    strncpy(user.role, array, 30);

    printf("\t\tUSER ID: %d\n", user.userID);
    printf("\t\tUSER ROLE:%s\n", user.role);


    	printf("\t\tENTER NAME:");
        gets(user.Name);	//this value is holded by the structure "userList"
        printf("\t\tENTER USERNAME:");
        gets(user.userName);	//this value is holded by the structure "userList"
        printf("\t\tENTER PASSWORD:");
        gets(user.passWord);	//this value is holded by the structure "userList"


    FILE *myfile;
	myfile = fopen(userFileName, "ab");		//user file is opened in append-binary mode.
	
	fwrite(&user, sizeof(struct userList), 1, myfile);
	fclose(myfile);

	system("cls");
	printf("\n\n\n\n\t\t:::SUCCESSFULLY ADDED TO THE SYSTEM:::\n");
	Sleep(700);		//pauses the system
	system("cls");		//clears the screen.

	adminMenu();
	adminActivity();


}


void updateLecturerDetails(){


    int count = 0;
	FILE *myfile =fopen(userFileName, "rb");
	FILE *myfile2 = fopen(tempFileName, "ab");
	struct userList tr;

	printf("\t\t_____________________________________________________________________________________\n");
	printf("\t\t_________________________________LECTURER LIST_______________________________________\n");

	printf("\t\t+ ID         NAME                ROLE              USERNAME           PASSWORD       +\n");
	printf("\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	while ((fread(&tr, sizeof(struct userList), 1 , myfile) ) == 1){

		if(strstr(strlwr(tr.role),"lecturer") != NULL ){
			printf("\t\t+  %d        %-15s     %-15s       %-10s       %-10s\n", tr.userID,  tr.Name, tr.role, tr.userName, tr.passWord);
			count++;
		}

	}

	if(count==0){
    printf("\t\t+++++++++++++++++                NO RECORD FOUND                  ++++++++++++++++++++\n");
	}

	printf("\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n\n");
	fclose(myfile);



	printf("\t\tENTER LECTURER ID:");
    int LecturerID = ValidationInteger();

    fflush(stdin);


    myfile = fopen(userFileName, "rb");
	struct userList ur;
	count =0;

	while ((fread(&ur, sizeof(struct userList), 1 , myfile) ) == 1){

		if((strstr(strlwr(ur.role),"lecturer") != NULL) && LecturerID==ur.userID){
			count++;
		}

	}
	fclose(myfile);


	if(count==0){		//if file does'nt exists.
    printf("\t\t+++++++++++++++++                NO RECORD FOUND                  ++++++++++++++++++++\n");
	}

	else{

        myfile = fopen(userFileName, "rb");
        struct userList ur2;


	while ((fread(&ur2, sizeof(struct userList), 1 , myfile) ) == 1){

		if((strstr(strlwr(ur2.role),"lecturer") != NULL) && LecturerID==ur2.userID){
			printf("\t\tENTER NEW NAME:");
            gets(ur2.Name);
            printf("\t\tENTER NEW USERNAME:");
            gets(ur2.userName);
            printf("\t\tENTER NEW PASSWORD:");
            gets(ur2.passWord);
            fwrite(&ur2, sizeof(struct userList), 1, myfile2);
		}else{
		    fwrite(&ur2, sizeof(struct userList), 1, myfile2);
		}

	}

    fclose(myfile);
	fclose(myfile2);
	remove(userFileName);
	rename(tempFileName,userFileName);

}
printf("\t\t...:::PRESS ANY KEY TO CONTINUE:::....");
	getch();
	system("cls");
	adminActivity();

}



void deleteLecturereProfile(){
//	this function deletes a user profile.

    int count = 0;
	FILE *myfile =fopen(userFileName, "rb");
	FILE *myfile2 = fopen(tempFileName, "ab");
	struct userList tr;

	printf("\t\t_____________________________________________________________________________________\n");
	printf("\t\t_________________________________LECTURER LIST_______________________________________\n");

	printf("\t\t+ ID         NAME                ROLE              USERNAME           PASSWORD       +\n");
	printf("\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	while ((fread(&tr, sizeof(struct userList), 1 , myfile) ) == 1){

		if(strstr(strlwr(tr.role),"lecturer") != NULL ){
			printf("\t\t+  %d        %-15s     %-15s       %-10s       %-10s\n", tr.userID,  tr.Name, tr.role, tr.userName, tr.passWord);
			count++;
		}

	}

	if(count==0){
    printf("\t\t+++++++++++++++++                NO RECORD FOUND                  ++++++++++++++++++++\n");
	}

	printf("\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n\n");
	fclose(myfile);



	printf("\t\tENTER LECTURER ID:");
    int LecturerID = ValidationInteger();

    fflush(stdin);


    myfile = fopen(userFileName, "rb");
	struct userList ur;
	count =0;

	while ((fread(&ur, sizeof(struct userList), 1 , myfile) ) == 1){

		if((strstr(strlwr(ur.role),"lecturer") != NULL) && LecturerID==ur.userID){
			count++;
		}

	}
	fclose(myfile);


	if(count==0){
    printf("\t\t+++++++++++++++++                NO RECORD FOUND                  ++++++++++++++++++++\n");
	}

	else{

        myfile = fopen(userFileName, "rb");
        struct userList ur2;


	while ((fread(&ur2, sizeof(struct userList), 1 , myfile) ) == 1){

		if((strstr(strlwr(ur2.role),"lecturer") != NULL) && LecturerID!=ur2.userID){
		    fwrite(&ur2, sizeof(struct userList), 1, myfile2);
		}

	}

    fclose(myfile);
	fclose(myfile2);
	remove(userFileName);
	rename(tempFileName,userFileName);

}
printf("\t\t...:::PRESS ANY KEY TO CONTINUE:::....");
	getch();
	system("cls");
	adminActivity();


}

void adminActivity(){
		//this functions gives all the access for the HR. this function does all the activity of a HR.
		system("cls");
        adminMenu();
		printf("\n\n");
		printf("\t\t*******************************************\n");
		printf("\t\t*     A. Create new Lecturer              *\n");
		printf("\t\t*     B. Create new Academic Leader       *\n");
		printf("\t\t*     C. Search lecturer profile          *\n");
		printf("\t\t*     D. View lecturer profile            *\n");
		printf("\t\t*     E. Update lecturer profile          *\n");
        printf("\t\t*     F. Delete lecturer profile          *\n");
		printf("\t\t*     G. View employee leave status       *\n");
		printf("\t\t*     H. Upload the yearly leaves         *\n");
		printf("\t\t*     I. Upload FAQs about University     *\n");
		printf("\t\t*     J. Update FAQs about University     *\n");
		printf("\t\t*     K. LOGOUT                           *\n");
		printf("\t\t*******************************************\n");
		printf("\n\n\n");

		printf("\t\tENTER YOUR CHOICE:");
		char c ;
		char choice = getch();
		fflush(stdin);
		switch (choice)
		{
		case 'A':
        case 'a':
			system("cls");
			adminMenu();
			char array[] = "Lecturer";
			registrationNewUser(array);
			break;
		case 'B':
        case 'b':
			system("cls");
			adminMenu();
			char array2[] = "Academic Leader";
			registrationNewUser(array2);
			break;
		case 'C':
        case 'c':

			system("cls");
			adminMenu();
			searchLecturerTable();
			break;
		case 'D':
        case 'd':
			system("cls");
			adminMenu();
			viewOnlyLecturerTable();
			break;
		case 'E':
		case 'e':
			system("cls");
			adminMenu();
			updateLecturerDetails();
			break;
		case 'F':
        case 'f':
			system("cls");
			adminMenu();
			deleteLecturereProfile();
			break;

		case 'G':
        case 'g':
			system("cls");
			adminMenu();
viewAllLeaveApplicationAdmin();
			break;

		case 'H':
        case 'h':
			system("cls");
			adminMenu();
uploadYearlyLeave();
			break;


		case 'I':
        case 'i':
			system("cls");
			adminMenu();
			UploadFaq();
			break;


		case 'J':
        case 'j':
			system("cls");
			adminMenu();
			UpdateFAQ();
			break;


		case 'K':
		case 'k':
			system("cls");
			printf("\n\n\t\tPRESS 'Y' TO LOGOUT THE SYSTEM.....");
			c= getch();
			if (c == 'Y' || c == 'y' )
		{
			system("cls");
			Header();
			MainMenu();
		}
		else
		{
			system("cls");
			adminMenu();
			adminActivity();
		}
			break;

		default:
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n\t....:::SORRY!! YOU ENTERED A WRONG INPUT::::......\n");
			Sleep(700);
			system("cls");
			adminMenu();
			adminActivity();
			break;
		}



}



void viewAllLeaveApplicationAdmin(){
// this function is called to view the leave application status.
// this fucntion is used by HR and Academic leader.

     int count = 0;
	FILE *myfile;
	myfile = fopen(leaveFileName, "rb");
	struct leaveApplication tr;

	printf("\t\t_____________________________________________________________________________________\n");
	printf("\t\t__________________________________APPLICATION STATUS__________________________________\n");

	printf("\t\t+ ID         UserID      Start Day              Total           status       +\n");
	printf("\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");


	while ((fread(&tr, sizeof(struct leaveApplication), 1 , myfile) ) == 1){



if(tr.status==0){
    			printf("\t\t+  %d        %d             %d/%d/%d                   %-10d       Progress\n", tr.leaveID,  tr.UserID, tr.startingDate.day, tr.startingDate.month, tr.startingDate.year, tr.totalDay);
}else{
printf("\t\t+  %d        %d             %d/%d/%d                   %-10d       Approved\n", tr.leaveID,  tr.UserID, tr.startingDate.day, tr.startingDate.month, tr.startingDate.year, tr.totalDay);
}


			count++;


	}

	if(count==0){
    printf("\t\t+++++++++++++++++                NO RECORD FOUND                  ++++++++++++++++++++\n");
	}

	printf("\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n\n");
	fclose(myfile);


printf("\t\t...:::PRESS ANY KEY TO CONTINUE:::....");
	getch();
		system("cls");
		userMenu();
			adminActivity();

}


int yearlyLeave = 20;

void uploadYearlyLeave(){


	printf("\t\t____________________________________________\n");
	printf("\t\t_________________USER MENU__________________\n");
	printf("\t\t____________________________________________\n");
	printf("\n\n\n");

    printf("\t\tCurrently Yearly Leave: %d\n", yearlyLeave);

    printf("\t\tPlease Enter Updated Yearly Leave: ");
    scanf("%d", &yearlyLeave);



    	system("cls");
	printf("\n\n\n\n\t\t:::SUCCESSFULLY ADDED TO THE SYSTEM:::\n");
	Sleep(700);
	system("cls");

	adminMenu();
	adminActivity();


}


int serachLastFAQID(){
	int userID = 0;
	FILE *myfile;
	myfile = fopen(faqFileName, "rb");
	struct faqList user;
	while ((fread(&user, sizeof(struct faqList), 1 , myfile) ) == 1){
		userID = user.faqID;
	}

	fclose(myfile);
	return userID+1;	// it increaments the user Id for the next time
}



int serachLastLeaveID(){
	int userID = 0;
	FILE *myfile;
	myfile = fopen(leaveFileName, "rb");
	struct leaveApplication user;
	while ((fread(&user, sizeof(struct leaveApplication), 1 , myfile) ) == 1){
		userID = user.leaveID;
	}

	fclose(myfile);
	return userID+1;
}


void UploadFaq(){
    struct faqList faq;

    faq.faqID = serachLastFAQID(faqFileName);

    printf("\t\tFAQ ID: %d\n", faq.faqID);



    	printf("\t\tENTER QUESTION:");
        gets(faq.question);
        printf("\t\tENTER ANSWER:");
        gets(faq.answer);


    FILE *myfile;
	myfile = fopen(faqFileName, "ab");
	fwrite(&faq, sizeof(struct faqList), 1, myfile);
	fclose(myfile);

	system("cls");
	printf("\n\n\n\n\t\t:::SUCCESSFULLY ADDED TO THE SYSTEM:::\n");
	Sleep(700);
	system("cls");

	adminMenu();
	adminActivity();
}

void viewFaq(){



    int count = 0;
	FILE *myfile;
	myfile = fopen(faqFileName, "rb");
	struct faqList tr;

	printf("\t\t_____________________________________________________________________________________\n");
	printf("\t\t______________________________________FAQ LIST_______________________________________\n");

	while ((fread(&tr, sizeof(struct faqList), 1 , myfile) ) == 1){


	printf("\t\tQuestion ID: %d\n", tr.faqID);
	printf("\t\tQuestion   : %s\n", tr.question);
	printf("\t\tAnswer     : %s\n\n", tr.answer);

			count++;

	}

	if(count==0){
    printf("\t\t+++++++++++++++++                NO RECORD FOUND                  ++++++++++++++++++++\n");
	}

	printf("\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n\n");
	fclose(myfile);

//	printf("\t\t...:::PRESS ANY KEY TO CONTINUE:::....");
//	getch();
//
//	adminActivity();


}

void UpdateFAQ(){
	
    viewFaq();

    printf("\t\tENTER FAQ ID TO UPDATE:");
    int FAQID = ValidationInteger();

    fflush(stdin);

    FILE *myfile = fopen(faqFileName, "rb");
    FILE *myfile2 = fopen(tempFileName, "ab");
	struct faqList ur;
	int count =0;

	while ((fread(&ur, sizeof(struct faqList), 1 , myfile) ) == 1){

		if(FAQID==ur.faqID){
			count++;
		}

	}
	fclose(myfile);


	if(count==0){
    printf("\t\t+++++++++++++++++                NO RECORD FOUND                  ++++++++++++++++++++\n");
	}
	else
	{


	    myfile = fopen(faqFileName, "rb");
        struct faqList ur2;

        while ((fread(&ur2, sizeof(struct faqList), 1 , myfile) ) == 1){
            if(FAQID==ur2.faqID){

            printf("\t\tENTER NEW QUESTION NAME:");
            gets(ur2.question);
            printf("\t\tENTER NEW ANSWER:");
            gets(ur2.answer);
            fwrite(&ur2, sizeof(struct faqList), 1, myfile2);

            }
            else{
                fwrite(&ur2, sizeof(struct faqList), 1, myfile2);

            }

        }

        fclose(myfile);
        fclose(myfile2);
        remove(faqFileName);
        rename(tempFileName,faqFileName);

	}


	printf("\t\t...:::PRESS ANY KEY TO CONTINUE:::....");
	getch();

	adminActivity();

}

void userMenu(){
	// this function displays the header for the User menu.
	printf("\t\t____________________________________________\n");
	printf("\t\t________________USER MENU__________________\n");
	printf("\t\t____________________________________________\n");
	printf("\n\n\n");
}

void lecturerLoginAccess(){
	char userName[30];
	char password[30];
	printf("\t\tENTER USERNAME:");
	scanf("%s", userName);
	printf("\t\tENTER PASSWORD:");
	scanf("%s", password);
	struct userList user;
	bool flag = false;
	FILE *myfile = fopen(userFileName, "rb");
	while ((fread(&user, sizeof(struct userList), 1 , myfile) ) == 1){
		if ((strcmp(userName, user.userName) == 0) && (strcmp(password, user.passWord) == 0) && (strcmp(user.role, "Lecturer") == 0))
	{
		flag = true;
		SharedID = user.userID;
	}
	}

	if (flag == true)
	{
		system("cls");

		userMenu();
		LecturerActivity();
	}
	else
	{
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n\n\t....:::SORRY!! YOU ENTERED WRONG INFORMATIONS::::......\n");
		Sleep(700);
		system("cls");
		userMenu();
        MainMenu();
	}

}

void academicLoginAccess(){
	char userName[30];
	char password[30];
	printf("\t\tENTER USERNAME:");
	scanf("%s", userName);
	printf("\t\tENTER PASSWORD:");
	scanf("%s", password);
	struct userList user;
	bool flag = false;
	FILE *myfile = fopen(userFileName, "rb");
	while ((fread(&user, sizeof(struct userList), 1 , myfile) ) == 1){
		if ((strcmp(userName, user.userName) == 0) && (strcmp(password, user.passWord) == 0) && (strcmp(user.role, "Academic Leader") == 0) )
	{
		flag = true;
		SharedID = user.userID;
	}
	}

	if (flag == true)
	{
		system("cls");
		
		userMenu();
		academicActivity();
	}
	else
	{
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n\n\t....:::SORRY!! YOU ENTERED WRONG INFORMATIONS::::......\n");
		Sleep(700);
		system("cls");
		MainMenu();
	}




}

void MainMenu(){
	//this is the main menu of the system.
	printf("\t\t******************************\n");
	printf("\t\t*     1. HR                  *\n");
	printf("\t\t*     2. Academic Leader     *\n");
	printf("\t\t*     3. Lecturer            *\n");
	printf("\t\t*     4. EXIT                *\n");
	printf("\t\t******************************\n");
	printf("\n\n\n");

	printf("\t\tENTER YOUR CHOICE:");
	char choice = getch();
	fflush(stdin);

	if(choice == '1'){
		system("cls");
		WaitingTime();
		adminMenu();
		adminLogin();
	}
	else if (choice == '2'){
		system("cls");
		WaitingTime();
		userMenu();
		academicLoginAccess();
	}
	else if (choice == '3'){
		system("cls");
		WaitingTime();
		userMenu();
		lecturerLoginAccess();
	}
	else if (choice == '4')
	{

		printf("\n\n\t\tPRESS 'Y' TO EXIT THE SYSTEME.....");
		char x = getch();
		if (x == 'Y' || x == 'y' )
		{
			exit(0);
		}
		else
		{
			system("cls");
			Header();
			MainMenu();
		}

	}
	else{
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n\n\t....:::SORRY!! YOU ENTERED A WRONG KEYWORD::::......\n");
		Sleep(700);
		system("cls");
		Header();
		MainMenu();
	}
}


void academicActivity(){
	//these function contains all the features for the HR.
    	printf("\n\n");
		printf("\t\t******************************************************\n");
		printf("\t\t*     1. VIEW LECTURER LEAVE APPLICATION             *\n");
		printf("\t\t*     2. APPROVE/REJECT/ DELETE LEAVE APPLICATION    *\n");
		printf("\t\t*     3. VIEW ALL HOIDAY AND POLICY                  *\n");
		printf("\t\t*     4. LOGOUT                                      *\n");
		printf("\t\t******************************************************\n");
		printf("\n\n\n");

		printf("\t\tENTER YOUR CHOICE:");
		char c ;
		char choice = getch();
		fflush(stdin);
		switch (choice)
		{
		case '1':
			system("cls");
			userMenu();
            viewAllLeaveApplication();
			break;
		case '2':
			system("cls");
			userMenu();
deleteEditUpdateLeaveApplication();
			break;
		case '3':
			system("cls");
			userMenu();
			ViewHolidayAndPolicy();
			break;
		case '4':
			system("cls");
			printf("\n\n\t\tPRESS 'Y' TO LOGOUT THE SYSTEM.....");
			fflush(stdin);
			c= getch();
			if (c == 'Y' || c == 'y' )
		{
			system("cls");
			userMenu();
			MainMenu();
		}
		else
		{
			system("cls");
			userMenu();
			academicActivity();
		}
			break;

		default:
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n\t....:::SORRY!! YOU ENTERED A WRONG INPUT::::......\n");
			Sleep(700);
			system("cls");
			userMenu();
			academicActivity();
			break;
		}

}





void deleteEditUpdateLeaveApplication(){

    int count = 0;
	FILE *myfile;
	myfile = fopen(leaveFileName, "rb");
	struct leaveApplication tr;

	printf("\t\t_____________________________________________________________________________________\n");
	printf("\t\t__________________________________APPLICATION STATUS__________________________________\n");

	printf("\t\t+ ID         UserID      Start Day              Total           status       +\n");
	printf("\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");


	while ((fread(&tr, sizeof(struct leaveApplication), 1 , myfile) ) == 1){
        if(tr.status==0){
            printf("\t\t+  %d        %d             %d/%d/%d                   %-10d       Progress\n", tr.leaveID,  tr.UserID, tr.startingDate.day, tr.startingDate.month, tr.startingDate.year, tr.totalDay);
        }else{
            printf("\t\t+  %d        %d             %d/%d/%d                   %-10d       Approved\n", tr.leaveID,  tr.UserID, tr.startingDate.day, tr.startingDate.month, tr.startingDate.year, tr.totalDay);
        }
            count++;
        }
        	fclose(myfile);

	if(count==0){
    printf("\t\t+++++++++++++++++                NO RECORD FOUND                  ++++++++++++++++++++\n");
	}else{

	printf("\t\tPlease Enter the Leave ID: ");
	int leaveID = ValidationInteger();


	count = 0;
	myfile = fopen(leaveFileName, "rb");
	struct leaveApplication tr2;

	while ((fread(&tr2, sizeof(struct leaveApplication), 1 , myfile) ) == 1){
            if(tr2.leaveID==leaveID){
            count++;
            }
        }

                	fclose(myfile);

	if(count==0){
system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n\t....:::SORRY!! YOU ENTERED A WRONG INPUT::::......\n");
			printf("\t\tPRESS ANY KEY TO CONTINUE.....");
			getch();
			system("cls");
			academicActivity();
	}else{



	system("cls");

        printf("\n\n");
		printf("\t\t*******************************\n");
		printf("\t\t*     1. APPROVE              *\n");
		printf("\t\t*     2. REJECT               *\n");
		printf("\t\t*     3. DELETE               *\n");
		printf("\t\t*******************************\n");
		printf("\n\n\n");

		printf("\t\tPlease enter your choice: ");
		int status = ValidationInteger();

		if(status==1){
                rejectApprove(1, leaveID);

		}else if(status==2){
		    rejectApprove(0, leaveID);

		}else if(status==3){
		    deleteLeaveApplication(leaveID);

		} else{
		printf("\n\n\n\n\n\n\n\n\n\n\t....:::SORRY!! YOU ENTERED A WRONG INPUT::::......\n");
			printf("\t\tPRESS ANY KEY TO CONTINUE.....");
			getch();
			system("cls");
						academicActivity();
		}
            }
            }
            }



void rejectApprove(int res, int leaveID){

        printf("\t\tLeave Application ID: %d\n", leaveID);
        printf("\t\tLeave STATUS ID: %d\n", res);

        FILE *myfile = fopen(leaveFileName, "rb");
//        FILE *myfile2 = fopen(tempFileName, "rb");
        FILE *myfile2 = fopen(tempFileName, "ab");
        struct leaveApplication ur2;

        while ((fread(&ur2, sizeof(struct leaveApplication), 1 , myfile) ) == 1){
            if(leaveID==ur2.leaveID){
                ur2.status = res;
//                printf("Leave ID is equal");
            fwrite(&ur2, sizeof(struct leaveApplication), 1, myfile2);
            }
            else{
//                                    printf("Leave ID is NOT equal");
                fwrite(&ur2, sizeof(struct leaveApplication), 1, myfile2);
                }
        }

        fclose(myfile);
        fclose(myfile2);
        remove(leaveFileName);
        rename(tempFileName,leaveFileName);

	system("cls");
	printf("\n\n\n\n\t\t:::SUCCESSFULLY UPDATED TO THE SYSTEM:::\n");
	Sleep(700);
	system("cls");

			userMenu();
			academicActivity();


}


void deleteLeaveApplication(int leaveID){

        printf("\t\tLeave Application ID: %d\n", leaveID);


        FILE *myfile = fopen(leaveFileName, "rb");

        FILE *myfile2 = fopen(tempFileName, "ab");
        struct leaveApplication ur2;

        while ((fread(&ur2, sizeof(struct leaveApplication), 1 , myfile) ) == 1){
            if(leaveID!=ur2.leaveID){
                fwrite(&ur2, sizeof(struct leaveApplication), 1, myfile2);
                }
        }

        fclose(myfile);
        fclose(myfile2);
        remove(leaveFileName);
        rename(tempFileName,leaveFileName);

	system("cls");
	printf("\n\n\n\n\t\t:::SUCCESSFULLY UPDATED TO THE SYSTEM:::\n");
	Sleep(700);
	system("cls");

			userMenu();
			academicActivity();



}

void applicationForLeave(){



     struct leaveApplication la;

    la.leaveID = serachLastLeaveID(leaveFileName);

    printf("\t\tLeave Application ID: %d\n", la.leaveID);



    la.UserID = SharedID;

    printf("\t\tLeave Application User ID: %d\n", la.UserID);

    la.status = 0;
    printf("\t\tLeave Application Status: Progress\n");


    	printf("\t\tENTER STARTING DATE:\n");
    	printf("\t\t\t\tDAY (DD):");
        la.startingDate.day = ValidationInteger();
    	printf("\t\t\t\tMonth (MM):");
        la.startingDate.month = ValidationInteger();
    	printf("\t\t\t\tYear (YYYY):");
    	la.startingDate.year = ValidationInteger();


    	printf("\t\tENTER TOTAL DAYS: ");
    	la.totalDay = ValidationInteger();


    FILE *myfile;
	myfile = fopen(leaveFileName, "ab");
	fwrite(&la, sizeof(struct leaveApplication), 1, myfile);
	fclose(myfile);

	system("cls");
	printf("\n\n\n\n\t\t:::SUCCESSFULLY ADDED TO THE SYSTEM:::\n");
	Sleep(700);
	system("cls");

			userMenu();
			LecturerActivity();

}


void viewAllLeaveApplication(){

   int count = 0;
	FILE *myfile;
	myfile = fopen(leaveFileName, "rb");
	struct leaveApplication tr;

	printf("\t\t_____________________________________________________________________________________\n");
	printf("\t\t__________________________________APPLICATION STATUS__________________________________\n");

	printf("\t\t+ ID         UserID      Start Day              Total           status       +\n");
	printf("\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");


	while ((fread(&tr, sizeof(struct leaveApplication), 1 , myfile) ) == 1){



if(tr.status==0){
    			printf("\t\t+  %d        %d             %d/%d/%d                   %-10d       Progress\n", tr.leaveID,  tr.UserID, tr.startingDate.day, tr.startingDate.month, tr.startingDate.year, tr.totalDay);
}else{
printf("\t\t+  %d        %d             %d/%d/%d                   %-10d       Approved\n", tr.leaveID,  tr.UserID, tr.startingDate.day, tr.startingDate.month, tr.startingDate.year, tr.totalDay);
}


			count++;


	}

	if(count==0){
    printf("\t\t+++++++++++++++++                NO RECORD FOUND                  ++++++++++++++++++++\n");
	}

	printf("\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n\n");
	fclose(myfile);


printf("\t\t...:::PRESS ANY KEY TO CONTINUE:::....");
	getch();

		userMenu();
			academicActivity();

}

void LecturerActivity(){
		// this function is the dashboard for the lecturer.
    	printf("\n\n");
		printf("\t\t**************************************************\n");
		printf("\t\t*     1. APPLY FOR LEAVE                         *\n");
		printf("\t\t*     2. CHECK LEAVE APPLICATION STATUS          *\n");
		printf("\t\t*     3. VIEW ALL HOIDAY AND POLICY              *\n");
		printf("\t\t*     4. LOGOUT                                  *\n");
		printf("\t\t**************************************************\n");
		printf("\n\n\n");

		printf("\t\tENTER YOUR CHOICE:");
		char c ;
		char choice = getch();
		fflush(stdin);
		switch (choice)
		{
		case '1':
			system("cls");
			userMenu();
			applicationForLeave();
			break;
		case '2':
			system("cls");
			userMenu();
			checkLeaveStatus();
			break;
		case '3':
			system("cls");
			userMenu();
			ViewHolidayAndPolicy();
			break;
		case '4':
			system("cls");
			printf("\n\n\t\tPRESS 'Y' TO LOGOUT THE SYSTEM.....");
			fflush(stdin);
			c= getch();
			if (c == 'Y' || c == 'y' )
		{
			system("cls");
			userMenu();
			MainMenu();
		}
		else
		{
			system("cls");
			userMenu();
			LecturerActivity();
		}
			break;

		default:
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n\t....:::SORRY!! YOU ENTERED A WRONG INPUT::::......\n");
			Sleep(700);
			system("cls");
			userMenu();
			LecturerActivity();
			break;
		}

}


void checkLeaveStatus(){

   int count = 0;
	FILE *myfile;
	myfile = fopen(leaveFileName, "rb");
	struct leaveApplication tr;

	printf("\t\t_____________________________________________________________________________________\n");
	printf("\t\t__________________________________APPLICATION STATUS__________________________________\n");

	printf("\t\t+ ID         UserID      Start Day              Total           status       +\n");
	printf("\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");


	while ((fread(&tr, sizeof(struct leaveApplication), 1 , myfile) ) == 1){
            if(tr.UserID == SharedID){


if(tr.status==0){
    			printf("\t\t+  %d        %d             %d/%d/%d                   %-10d       Progress\n", tr.leaveID,  tr.UserID, tr.startingDate.day, tr.startingDate.month, tr.startingDate.year, tr.totalDay);
}else{
printf("\t\t+  %d        %d             %d/%d/%d                   %-10d       Approved\n", tr.leaveID,  tr.UserID, tr.startingDate.day, tr.startingDate.month, tr.startingDate.year, tr.totalDay);
}


			count++;
			}

	}

	if(count==0){
    printf("\t\t+++++++++++++++++                NO RECORD FOUND                  ++++++++++++++++++++\n");
	}

	printf("\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n\n");
	fclose(myfile);


printf("\t\t...:::PRESS ANY KEY TO CONTINUE:::....");
	getch();

		userMenu();
			LecturerActivity();




}


void ViewHolidayAndPolicy(){

	printf("\n\n\n");

    printf("\t\tCurrently Yearly Leave: %d\n", yearlyLeave);

    	printf("\n\n\n");

    printf("\t\t________________  PRESS ANY KEY TO CONTINUE ______________\n");
getch();
	Sleep(700);
	system("cls");


academicActivity();

}



void WaitingTime(){
	//this is a loading screen function.
	system("cls");
	printf("\n\n\n\n\t\tLOADING");
	Sleep(100);
	system("cls");
	printf("\n\n\n\n\t\tLOADING.");
	Sleep(100);
	system("cls");
	printf("\n\n\n\n\t\tLOADING..");
	Sleep(100);
	system("cls");
	printf("\n\n\n\n\t\tLOADING...");
	Sleep(100);
	system("cls");
	printf("\n\n\n\n\t\tLOADING....");
	Sleep(100);
	system("cls");
	printf("\n\n\n\n\t\tLOADING.....");
	system("cls");
	Sleep(100);

}
