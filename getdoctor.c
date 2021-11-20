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

}typedef date;


struct Appointment
{
	int type;
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
	date availableDates[10];
	float rating;
	int numOfRaters;
	date passwordDate;

}typedef doc;

struct Month
{
	char month[20];
	date date[10];
} typedef month;



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
	printf("Enter a speciality: \n");
	char speciality[20];
	getchar();
	fgets(speciality, 20, stdin);
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
	char speciality[5][20];
	strcpy(speciality[0], "Family doctor");
	strcpy(speciality[1], "Psychiatrist");
	strcpy(speciality[2], "Gynecologist");
	strcpy(speciality[3], "Cardiologist");
	printf("Please choose what speciality of the doctor you want: \n");
	for (int i = 0; i < 4; i++)
	{
		printf("%d. %s \n", i + 1, speciality[i]);
	}
	int index = -1;
	scanf("%d", &index);
	printf("Please choose a doctor: \n");
	int j = 0;
	int place [20];
	for (int i = 0; i < dArrSize; i++)
	{
		if (strcmp(dArr[i].speciality, speciality[index])==0)
		{
			
			place[j] = i;
			printf("%d. %s \n", j+1, dArr[i].name);
			j++;
		}
	}
	scanf("%d", &index);
	index--;
	printf("Please choose a month: \n 1. January \n 2. February \n 3. March \n 4. April \n 5. May \n 6. June \n 7. July\n 8. August\n 9. September\n 10. October\n 11. November\n 12. December\n");
	int month;
	scanf("%d", &month);
	
}


int main()
{
	
	doc dArr[10];
	

	pat pArr[10];
	int pArrSize = 0;
	
	int dArrSize = 0;
	

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
	