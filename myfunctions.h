/* This is a header file of ELMS system. 
	This file contains all the headers required in this system.
	all the declaration of functions are done in this file. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#include <Windows.h>

/* Declaration of functions according to the flow of the system. */
void MainMenu();
void Header();
void WaitingTime();
void adminMenu();
void adminLogin();

int ValidationInteger();


void registrationNewUser(char *array);
int serachLastID(char *fileName);
void searchLecturerTable();
void listofUserList();
void viewOnlyLecturerTable();
void updateLecturerDetails();
void deleteLecturereProfile();
void lecturerLoginAccess();
void academicLoginAccess();
void LecturerActivity();
void academicActivity();
void UploadFaq();
void viewFaq();
void UpdateFAQ();
int serachLastFAQID();
void uploadYearlyLeave();
void viewAllLeaveApplicationAdmin();


void applicationForLeave();
void ViewHolidayAndPolicy();
void checkLeaveStatus();


void viewAllLeaveApplication();
void deleteEditUpdateLeaveApplication();
void rejectApprove(int res, int leaveID);
void deleteLeaveApplication(int leaveID);
