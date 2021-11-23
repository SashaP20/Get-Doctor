#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>






struct Date
{
	int month;
	int day;
	int hour;
	int minute;
	char availability[30];

}typedef date;


struct Appointment
{
	char type;
	date date;

}typedef app;

struct Patient
{
	long id;
	char name[20];
	char phone[11];
	char password[10];
	app appointments[10];
	date passwordDate;


}typedef pat;

struct Doctor
{
	long id;
	char name[20];
	char phone[11];
	char password[20];
	char gender;
	char speciality[20];
	char title[20];
	int price;
	int isReferral;
	app reservedApp[10];
	app AppointmentsSecheualed[10];
	date** AppointmentsAvailable;
	float rating;
	int numOfRaters;
	date passwordDate;

}typedef doc;




char* NewPassword(char* password, int index);
int DIDForPasswordCheck(doc* dArr, long idCheck, int dArrSize);
int PasswordCompareDoc(doc* dArr, long idCheck, int dArrSize);
int PIDForPasswordCheck(pat* pArr, long idCheck, int pArrSize);
int PasswordComparePat(pat* pArr, long idCheck, int pArrSize);
int IDLenCheck(long ID);
int IDValidDoctor(long ID, doc* dArr, int dArrSize);
void signInDoctor(doc* dArr, int* dArrSize);
int PasswordCheck(char* password);
int IDValidPatient(long ID, pat* pArr, int pArrSize);
void signInPatient(pat* pArr, int* pArrSize);
app appointmentSchedualing(doc* dArr, int dArrSize);
date** dateInit();
char* specialityInit();


int DIDForPasswordCheck(doc* dArr, long idCheck, int dArrSize) // getting ID and check if the ID  exists in the array, return index.
{
	for (int i = 0; i < dArrSize; i++)
	{
		if (dArr[i].id == idCheck)
		{
			return i;
		}
	}
	printf("ID does not exist\n");
	return -1;

}

int PasswordCompareDoc(doc* dArr, long idCheck, int dArrSize) // Compare password with id
{
	int index = DIDForPasswordCheck(dArr, idCheck, dArrSize);
	if (index == -1)
		return -1;
	char password[20];
	printf("Enter a password:\n");
	scanf("%s", &password);
	if (strcmp(password, dArr[index].password) == 0)
	{
		time_t today = time(NULL);
		struct tm* today2 = localtime(&today);
		if (abs(dArr[index].passwordDate.month - ((today2->tm_mon) + 1)) >= 3)
		{
			printf("The password need to be changed,  3 months passed \n");
			strcpy(dArr[index].password, NewPassword(dArr[index].password, index));
		}
		return index;
	}

	else
	{

		printf("Invalid password\n");
		return -1;
	}
}

int PIDForPasswordCheck(pat* pArr, long idCheck, int pArrSize) // getting ID and check if the ID  exists in the array, return index.
{
	for (int i = 0; i < pArrSize; i++)
	{
		if (pArr[i].id == idCheck)
		{
			return i;
		}
	}
	printf("ID does not exist\n");
	return -1;

}

int PasswordComparePat(pat* pArr, long idCheck, int pArrSize)
{
	int index = PIDForPasswordCheck(pArr, idCheck, pArrSize);
	if (index == -1)
		return -1;
	char password[20];
	printf("Enter a password:\n");
	scanf("%s", &password);
	if (strcmp(password, pArr[index].password) == 0)
	{
		time_t today = time(NULL);
		struct tm* today2 = localtime(&today);
		if (abs(pArr[index].passwordDate.month - ((today2->tm_mon) + 1)) >= 3)
		{
			printf("The password need to be changed,  3 months passed \n");
			strcpy(pArr[index].password, (char*)NewPassword(pArr[index].password, index));

		}
		return index;
	}
	else
		printf("Invalid password\n");
	return -1;

}

int IDLenCheck(long ID)
{
	if (ID >= 100000000 && ID <= 999999999)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int IDValidDoctor(long ID, doc* dArr, int dArrSize)
{
	if (IDLenCheck(ID) == 1) //ID is 9 digits
	{
		for (int i = 0; i < dArrSize; i++)
		{
			if (ID == dArr->id) // ID already exists
			{
				printf("Error, ID already exists.\n");
				return 0;
			}
		}
		return 1; //ID is 9 digits and it doesn't already exist.
	}
	else //ID is not 9 digits.
	{
		printf("Error, ID isn't 9 digits long.\n");
		return 0;
	}
}

int PasswordCheck(char* password)
{
	for (int i = 0; i < strlen(password); i++)
	{
		if (password[i] >= 'A' && password[i] <= 'Z')
			return 1;
	}
	printf("Error, no capital letter.\n");
	return 0;
}


void signInDoctor(doc* dArr, int* dArrSize)
{
	printf("Enter a name: \n");
	char name[20];
	scanf("%s", &name);
	printf("Enter a phone number: \n");
	char phone[11];
	scanf("%s", &phone);

	char gender = 'M';
	printf("Enter a gender: M or F \n");
	do
	{
		getchar();

		scanf("%c", &gender);

		if (gender != 'M' && gender != 'F' && gender != 'm' && gender != 'f')
		{
			printf("Error wrong gender entered, try again.\n");
		}

	} while (gender != 'M' && gender != 'F' && gender != 'm' && gender != 'f');
	char* speciality = specialityInit();
	getchar();
	printf("Enter a title: \n");

	char title[20];
	fgets(title, 20, stdin);

	int price = 0;
	printf("Enter a price: \n");
	do
	{
		scanf("%d", &price);

		if (price < 0)
		{
			printf("Invalid price, try again \n");
		}
	} while (price < 0);
	int referral = -1;
	printf("Do you need a refferal: \n 1. Yes \n 0. No.\n");
	do
	{
		scanf("%d", &referral);

		if (referral != 1 && referral != 0)
		{
			printf("Invalid choice, try again \n");
		}
	} while (referral != 1 && referral != 0);
	long ID;
	printf("Enter an ID: \n");
	do
	{
		scanf("%ld", &ID);

	} while (IDValidDoctor(ID, dArr, dArrSize) == 0);
	char password[20];
	printf("Enter a password:\n");
	do
	{
		scanf("%s", &password);

	} while (PasswordCheck(password) == 0);
	doc newD;
	newD.gender = gender;
	newD.id = ID;
	newD.isReferral = referral;
	strcpy(newD.name, name);
	strcpy(newD.password, password);
	strcpy(newD.phone, phone);
	newD.price = price;
	strcpy(newD.speciality, speciality);
	strcpy(newD.title, title);
	newD.rating = 0;
	newD.numOfRaters = 0;
	time_t today = time(NULL);
	struct tm* today2 = localtime(&today);
	newD.passwordDate.day = (today2->tm_mday) + 1;
	newD.passwordDate.month = (today2->tm_mon) + 1;
	newD.passwordDate.hour = (today2->tm_hour) + 1;
	newD.passwordDate.minute = (today2->tm_min) + 1;
	newD.AppointmentsAvailable = dateInit();
	

	dArr[*dArrSize] = newD;
	(*dArrSize)++;
}
int IDValidPatient(long ID, pat* pArr, int pArrSize)
{
	if (IDLenCheck(ID) == 1) //ID is 9 digits
	{
		for (int i = 0; i < pArrSize; i++)
		{
			if (ID == pArr->id) // ID already exists
			{
				printf("Error, ID already exists.\n");
				return 0;
			}
		}
		return 1; //ID is 9 digits and it doesn't already exist.
	}
	else //ID is not 9 digits.
	{
		printf("Error, ID isn't 9 digits long.\n");
		return 0;
	}
}
void signInPatient(pat* pArr, int* pArrSize)
{
	printf("Enter a name: \n");
	char name[20];
	scanf("%s", &name);
	printf("Enter a phone number: \n");
	char phone[11];
	scanf("%s", &phone);
	long ID;
	printf("Enter an ID: \n");
	do
	{
		scanf("%ld", &ID);

	} while (IDValidPatient(ID, pArr, pArrSize) == 0);
	char password[20];
	printf("Enter a password:\n");
	do
	{
		scanf("%s", &password);

	} while (PasswordCheck(password) == 0);
	pat newP;


	newP.id = ID;
	strcpy(newP.name, name);
	strcpy(newP.password, password);
	strcpy(newP.phone, phone);
	time_t today = time(NULL);
	struct tm* today2 = localtime(&today);
	newP.passwordDate.day = (today2->tm_mday) + 1;
	newP.passwordDate.month = (today2->tm_mon) + 1;
	newP.passwordDate.hour = (today2->tm_hour) + 1;
	newP.passwordDate.minute = (today2->tm_min) + 1;

	pArr[*pArrSize] = newP;
	(*pArrSize)++;
}

char* NewPassword(char* password, int index) // new password after 3 months
{
	char NewPassword[20];
	printf("Enter a new password:\n");
	do
	{
		scanf("%s", &NewPassword);

	} while (PasswordCheck(NewPassword) == 0);
	strcpy(password, NewPassword);
	return NewPassword;
}

app appointmentSchedualing(doc* dArr, int dArrSize)
{
	char* speciality= specialityInit();
	printf("Please choose a doctor: \n");
	int j = 0;
	int place[20] = { 0 };
	for (int i = 0; i < dArrSize; i++)
	{
		if (strcmp(dArr[i].speciality, speciality) == 0)
		{

			place[j] = i;
			printf("%d. %s \n", j + 1, dArr[i].name);
			j++;
		}
	}
	int index;

	scanf("%d", &index);
	int day;
	printf("Choose a work day:\n\n 1. Sunday\n 2.monday\n 3.tuesday\n 4.wednesday\n 5.thursday\n");
	scanf("%d", &day);
	
	printf("Pick a date to schedual your appointment on:\n");
	for (int i = 0; i < 5; i++)
	{
		if (dArr[place[index]].AppointmentsAvailable[day - 1][i].minute==0)
		{
			printf("%d. %d:%d0 %s\n",i+1, dArr[place[index]].AppointmentsAvailable[day - 1][i].hour, dArr[place[index]].AppointmentsAvailable[day - 1][i].minute,dArr[place[index]].AppointmentsAvailable[day-1][i].availability);

		}
		else 
		{
			printf("%d. %d:%d %s\n",i+1, dArr[place[index]].AppointmentsAvailable[day - 1][i].hour, dArr[place[index]].AppointmentsAvailable[day - 1][i].minute, dArr[place[index]].AppointmentsAvailable[day - 1][i].availability);
		}
	}
	int datepicker;
	scanf("%d", &datepicker);
	date temp = dArr[place[index]].AppointmentsAvailable[day - 1][datepicker-1];
	strcpy(dArr[place[index]].AppointmentsAvailable[day - 1][datepicker - 1].availability,"Unavailable");
	printf("%s", dArr[place[index]].AppointmentsAvailable[day - 1][datepicker - 1].availability);
	int type;
	char Ctype;
	do
	{

	
	printf("Pick the type of the appointment:\n\n 1. Frontal \n 2. By phone\n");
	scanf("%d", &type);
	if (type == 1)
		Ctype = 'F';
	else if (type == 2)
		Ctype = 'P';
	else 
	{
		printf("Try again\n");
	}
	} while (type != 1 && type != 2);
	app x = { .date = temp,.type = Ctype };
	return x;
	
}
date** dateInit()
{
	date day[5];
	date** workWeek = (date**)malloc(sizeof(date*)*5);
	for (int i = 0; i < 5; i++)
	{
		workWeek[i] = (date*)malloc(sizeof(date)*5);
	}

	day[0].hour = 8;
	day[0].minute = 0;
	strcpy(day[0].availability, "Available");
	day[1].hour = 8;
	day[1].minute = 30;
	strcpy(day[1].availability, "Available");
	day[2].hour = 9;
	day[2].minute = 0;
	strcpy(day[2].availability, "Available");
	day[3].hour = 9;
	day[3].minute = 30;
	strcpy(day[3].availability, "Available");
	day[4].hour = 10;
	day[4].minute = 0;
	strcpy(day[4].availability, "Available");

	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			workWeek[i][j]=day[j];
		}
	}
	return workWeek;
}

char* specialityInit()
{
	int index = -1;
	char** speciality = (char**)malloc(sizeof(char*)*5);
	for (int i = 0; i < 5; i++)
	{
		speciality[i] = (char*)malloc(sizeof(char) * 20);
	}
	strcpy(speciality[0], "Family doctor");
	strcpy(speciality[1], "Psychiatrist");
	strcpy(speciality[2], "Gynecologist");
	strcpy(speciality[3], "Cardiologist");
	printf("Please choose the speciality you want: \n");
	for (int i = 0; i < 4; i++)
	{
		printf("%d. %s \n", i + 1, speciality[i]);
	}
	do
	{	
	
	scanf("%d", &index);
	if (index != 0 && index != 1 && index != 2 && index != 3 && index != 4)
	{
		printf("Wrong index entered try again. \n");
	}
	} while (index != 0 && index != 1 && index != 2 && index != 3 && index != 4);
	return speciality[index-1];
}

int main()
{

	doc dArr[10];
	dateInit();

	pat pArr[10];
	int pArrSize = 0;

	/*int dArrSize = 0;
	doc Vlad = { .name = "Vlad",.AppointmentsAvailable = dateInit(),.speciality = "Family doctor" };
	dArr[0] = Vlad;
	dArrSize++;
	app x = appointmentSchedualing(dArr, dArrSize);
	printf("%d:%d0 %c", x.date.hour,x.date.minute, x.type);*/

	time_t today = time(NULL);
	struct tm* today2 = ctime(&today);
	int local = today2->tm_mday;
	for (int i = 1; i <= 7; i++)
	{
		
		if (today2->tm_mon == 4 || today2->tm_mon == 6 || today2->tm_mon == 9 || today2->tm_mon == 11) {
			if (local + i - 1 == 30)
				local = 0 - i + 1;
		}
		if (today2->tm_mon == 1 || today2->tm_mon == 3 || today2->tm_mon == 5 || today2->tm_mon == 7 || today2->tm_mon == 8 || today2->tm_mon == 10 || today2->tm_mon == 12) {
			if (local + i - 1 == 31)
				local = 0 - i + 1;
		}
		if (today2->tm_mon == 2) {
			if (local + i - 1 == 28)
				local = 0 - i + 1;
		}

		printf("%d: \n", local + i);
	}
	/*time_t curtime;

	time(&curtime);

	printf("Current time = %s", ctime(&curtime));*/

}

	/*doc a={.name="Vlad",}
	appointmentSchedualing(dArr, dArrSize);*/


		//printf("Pick an option: \n 1-I'm a Doctor. \n 2-I'm a patient\n");
		//int option;
		//scanf("%d", &option);
		//switch (option)
		//{
		//case 1:
		//	printf("Pick an option: \n 1-Sign in. \n 2-Log in.\n");
		//	scanf("%d", &option);
		//	switch (option)
		//	{
		//	case 1:
		//		signInDoctor(dArr,dArrSize);
		//	default:
		//		break;
		//	}
		//default:
		//	break;
		//}

