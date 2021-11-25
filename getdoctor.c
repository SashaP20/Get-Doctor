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


struct WorkMonth
{
	date WorkDay[20][5];

}typedef WorkMonth;

struct Appointment
{
	char type;
	date date;
	char DoctorName[20];

}typedef app;

struct Patient
{
	long id;
	char name[20];
	char phone[11];
	char password[10];
	app appointments[10];
	int numOfAppointments;
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
	app AppointmentsSchedualed[10];
	int numbOfAppointmentSchedualed;
	WorkMonth* WorkMonth;
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
WorkMonth* dateInit();
char* specialityInit();
WorkMonth* SchedualInit();


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

	} while (IDValidDoctor(ID, dArr, *dArrSize) == 0);
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
	newD.WorkMonth = SchedualInit();
	newD.numbOfAppointmentSchedualed = 0;


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

	} while (IDValidPatient(ID, pArr, *pArrSize) == 0);
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
	newP.numOfAppointments = 0;

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
	char* speciality = specialityInit();
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
	int month;
	printf("Choose a work month:\n\n1. January\n 2.February\n 3.March\n 4.April\n 5.May\n 6.June\n 7.July\n 8.August\n 9.September\n 10.October\n 11.November\n 12.December\n");
	scanf("%d", &month);

	printf("Pick a day to schedual your appointment on:\n");
	for (int i = 0; i < 20; i++)
	{

		printf("%d. %d/%d\n", i + 1, i + 1, month);

	}
	int day;
	scanf("%d", &day);
	for (int j = 0; j < 5; j++)
	{
		if (dArr[place[index]].WorkMonth[month - 1].WorkDay[day - 1][j].minute == 0)
		{
			printf("%d. %d:%d0 %s\n", j + 1, dArr[place[index]].WorkMonth[month - 1].WorkDay[day - 1][j].hour, dArr[place[index]].WorkMonth[month - 1].WorkDay[day - 1][j].minute, dArr[place[index]].WorkMonth[month - 1].WorkDay[day - 1][j].availability);

		}
		else
		{
			printf("%d. %d:%d %s\n", j + 1, dArr[place[index]].WorkMonth[month - 1].WorkDay[day - 1][j].hour, dArr[place[index]].WorkMonth[month - 1].WorkDay[day - 1][j].minute, dArr[place[index]].WorkMonth[month - 1].WorkDay[day - 1][j].availability);
		}
	}

	int datepicker;
	scanf("%d", &datepicker);
	date temp = dArr[place[index]].WorkMonth[month - 1].WorkDay[day - 1][datepicker - 1];
	strcpy(dArr[place[index]].WorkMonth[month - 1].WorkDay[day - 1][datepicker - 1].availability, "Unavailable");
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
	app x = { .date = temp,.type = Ctype,.DoctorName = dArr[place[index]].name };
	dArr[place[index]].AppointmentsSchedualed[dArr[place[index]].numbOfAppointmentSchedualed] = x;
	dArr[place[index]].numbOfAppointmentSchedualed++;
	return x;

}
WorkMonth* dateInit()
{
	date DateInit[20][5];
	WorkMonth* Schedual = (WorkMonth*)malloc(12 * sizeof(WorkMonth));
	date day[5];

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


	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			DateInit[i][j] = day[j];
			DateInit[i][j].day = i + 1;
		}
	}
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				Schedual[i].WorkDay[j][k] = DateInit[j][k];
				Schedual[i].WorkDay[j][k].month = i + 1;
			}
		}
	}

	return Schedual;
}

char* specialityInit()
{
	int index = -1;
	char** speciality = (char**)malloc(sizeof(char*) * 5);
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
	return speciality[index - 1];
}

WorkMonth* SchedualInit()
{
	WorkMonth* Schedual = (WorkMonth*)malloc(12 * sizeof(WorkMonth));
	Schedual = dateInit();



	return Schedual;
}

void docAppCancel(app appointment, doc* dArr, int dArrSize)
{

	for (int i = 0; i < dArrSize; i++)
	{
		if (strcmp(dArr[i].name, appointment.DoctorName) == 0)
		{
			for (int j = 0; j < 5; j++)
			{
				if (dArr[i].WorkMonth[appointment.date.month - 1].WorkDay[appointment.date.day - 1][j].hour == appointment.date.hour && dArr[i].WorkMonth[appointment.date.month - 1].WorkDay[appointment.date.day - 1][j].minute == appointment.date.minute)
				{
					strcpy(dArr[i].WorkMonth[appointment.date.month - 1].WorkDay[appointment.date.day - 1][j].availability, "Available");
				}
			}
			app* temp = (app*)malloc(sizeof(app) * (dArr[i].numbOfAppointmentSchedualed));
			for (int j = 0; j < dArr[i].numbOfAppointmentSchedualed - 1; j++)
			{
				if (dArr[i].AppointmentsSchedualed[j].date.day != appointment.date.day && dArr[i].AppointmentsSchedualed[j].date.month != appointment.date.month && dArr[i].AppointmentsSchedualed[j].date.hour != appointment.date.hour && dArr[i].AppointmentsSchedualed[j].date.minute != appointment.date.minute)
				{
					dArr[i].AppointmentsSchedualed[j] = dArr[i].AppointmentsSchedualed[j + 1];
				}
			}
			if (dArr[i].numbOfAppointmentSchedualed > 0)
				dArr[i].numbOfAppointmentSchedualed--;
			for (int j = 0; j < dArr[i].numbOfAppointmentSchedualed; j++)
			{
				dArr[i].AppointmentsSchedualed[j] = temp[j];
			}
			break;
		}
	}
}
app* appointmentCancelation(app* appointments, int* numOfAppointments, doc* dArr, int dArrSize)
{
	printf("Pick an appointment to cancel: \n");
	for (int i = 0; i < (*numOfAppointments); i++)
	{
		printf("%d. %d/%d %d:%d %c\n", i + 1, appointments[i].date.month, appointments[i].date.day, appointments[i].date.hour, appointments[i].date.minute, appointments[i].type);
	}
	int index;
	scanf("%d", &index);
	app tempA = appointments[index];
	(*numOfAppointments)--;
	app* temp = (app*)malloc(sizeof(app) * (*numOfAppointments));
	for (int i = index - 1; i < (*numOfAppointments) - 1; i++)
	{
		appointments[i] = appointments[i + 1];
	}
	docAppCancel(tempA, dArr, dArrSize);
	return temp;
}

void DocInfoPrint(doc* dArr, int dArrSize)
{
	char* speciality = specialityInit();
	int j = 0;
	int place[20] = { 0 };
	printf("Please choose a doctor: \n");
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
	printf("ID: %ld, Nmae: %s, Phone number: %s, Gender: %c, Speciality: %s, Title: %s, price: %d, Rating: %f \n", dArr[place[index-1]].id, dArr[place[index-1]].name, dArr[place[index-1]].phone, dArr[place[index-1]].gender, dArr[place[index-1]].speciality, dArr[place[index-1]].title, dArr[place[index-1]].price, dArr[place[index-1]].rating);
	
}

int main()
{

	doc dArr[10];
	int dArrSize = 0;
	pat pArr[10];
	int pArrSize = 0;
	//signInDoctor(dArr, &dArrSize);


	doc Vlad = { .name = "Vlad",.WorkMonth = SchedualInit(),.speciality = "Family doctor", .numbOfAppointmentSchedualed = 0, .numOfRaters = 0 };
	doc Moshe = { .name = "Moshe",.WorkMonth = SchedualInit(),.speciality = "Psychiatrist",.phone = "0523668318",.id=316164938,.gender='M',.title = "Head of Something",.price = 150,.rating=0.0  };
	dArr[0] = Moshe;
	dArrSize++;
	doc Moshe2 = { .name = "Moshe2",.WorkMonth = SchedualInit(),.speciality = "Family doctor",.phone = "0523668318",.id = 316164938,.gender = 'M',.title = "Head of Something",.price = 150,.rating = 0.0 };
	dArr[1] = Moshe2;
	dArrSize++;
	doc Moshe3 = { .name = "Moshe3",.WorkMonth = SchedualInit(),.speciality = "Family doctor",.phone = "0523668318",.id = 316164938,.gender = 'M',.title = "Head of Something",.price = 150,.rating = 0.0 };
	dArr[2] = Moshe3;
	dArrSize++;
	int i = 0;
	while (i < 3)
	{
		DocInfoPrint(dArr, dArrSize);
		i++;
	}
		DocInfoPrint(dArr, dArrSize);
	//dArr[0] = Vlad;
	//dArrSize++;
	//pat Bar = { .name = "Bar", .numOfAppointments = 0, };
	//for (int i = 0; i < 2; i++) {
	//	app x = appointmentSchedualing(dArr, dArrSize);
	//	Bar.appointments[Bar.numOfAppointments] = x;
	//	printf("%d:%d0 %c", Bar.appointments[Bar.numOfAppointments].date.hour, Bar.appointments[Bar.numOfAppointments].date.minute, Bar.appointments[Bar.numOfAppointments].type);
	//	Bar.numOfAppointments++;
	//}
	//app* temp;
	//temp = appointmentCancelation(Bar.appointments, &Bar.numOfAppointments, dArr, dArrSize);
	//for (int i = 0; i < Bar.numOfAppointments; i++)
	//{
	//	Bar.appointments[i] = temp[i];
	//}
	/*printf("%d:%d0 %d\n", Bar.appointments[Bar.numOfAppointments].date.hour, Bar.appointments[Bar.numOfAppointments].date.minute, Bar.appointments[Bar.numOfAppointments].type);
	DocInfoPrint(dArr, dArrSize);*/


	/*time_t curtime;
	time(&curtime);
	printf("Current time = %s", ctime(&curtime));*/



	/*doc a={.name="Vlad",}
	appointmentSchedualing(dArr, dArrSize);*/


	////printf("Pick an option: \n 1-I'm a Doctor. \n 2-I'm a patient\n");
	////int option;
	////scanf("%d", &option);
	////switch (option)
	////{
	////case 1:
	////	printf("Pick an option: \n 1-Sign in. \n 2-Log in.\n");
	////	scanf("%d", &option);
	////	switch (option)
	////	{
	////	case 1:
	////		signInDoctor(dArr,dArrSize);
	////	case 2:
	////		
	////	default:
	////		break;
	////	}
	////default:
	////	break;
	////}
}