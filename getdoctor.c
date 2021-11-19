#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>



struct Date
{
	int day;
	int month;
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
	float rating;
	int numOfRaters;
	date passwordDate;

}typedef doc;

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
			strcpy(pArr[index].password, NewPassword(pArr[index].password, index));
			
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
	newD.passwordDate.month = (today2->tm_mon)+1;
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




int main()
{
	//pat p1, p2, p3;
	//// patient 1 information
	//strcpy(p1.name, "Alex");
	//p1.id = 321223075;
	//strcpy(p1.password, "A123456");
	//strcpy(p1.phone, "0545542719");

	////patient 2 information
	//strcpy(p2.name, "Bar");
	//p2.id = 123456789;
	//strcpy(p2.password, "B123456");
	//strcpy(p2.phone, "0557483593");


	////patient 3 information
	//strcpy(p3.name, "Shira");
	//p3.id = 123456789;
	//strcpy(p3.password, "C123456");
	//strcpy(p3.phone, "0325236324");

	//doc d1, d2, d3;

	////doctor 1 information
	/*strcpy(d1.name, "Neta");
	d1.gender = 'F';
	d1.id = 123456789;
	d1.isReferral = 1;
	strcpy(d1.password, "D123456");
	strcpy(d1.phone, "0542245135");
	d1.price = 100;
	strcpy(d1.speciality, "Eye");*/

	////doctor 2 information
	//strcpy(d2.name, "David");
	//d2.gender = 'M';
	//d2.id = 123456789;
	//d2.isReferral = 0;
	//strcpy(d2.password, "E123456");
	//strcpy(d2.phone, "0501244545");
	//d2.price = 75;
	//strcpy(d2.speciality, "Family");


	////doctor 3 information
	//strcpy(d3.name, "Vlad");
	//d3.gender = 'M';
	//d3.id = 123456789;
	//d3.isReferral = 1;
	//strcpy(d3.password, "F123456");
	//strcpy(d3.phone, "0521235693");
	//d3.price = 50;
	//strcpy(d3.speciality, "Dermatologist");

	doc dArr[10];
	//dArr[0] = d1;
	//dArr[1] = d2;
	//dArr[2] = d3;

	pat pArr[10];
	int pArrSize = 0;
	//pArr[0] = p1;
	//pArr[1] = p2;
	//pArr[2] = p3;
	//int pArrSize = 3;
	int dArrSize = 0;
	/*signInPatient(pArr, &pArrSize);*/
	/*time_t moshe = time(NULL);
	printf("%dl \n", moshe);
	struct tm* moshe2 = localtime(&moshe);
	printf("%d \n", (moshe2->tm_mon)+1);*/
	
	//for (int i = 0; i < pArrSize; i++)
	//{
	//	printf("outside %s", pArr[i].name);
	//}

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


}