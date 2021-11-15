#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

struct Appointment
{
	int day;
	int month;
	char hour[6];
	struct p* patients;
	int type;
}typedef app;

struct Patient
{
	long id;
	char name[20];
	char phone[11];
	char password[10];
	app appointment1[10];

}typedef pat;

struct Doctor
{
	long id;
	char name[20];
	char phone[11];
	char password[10];
	char gender;
	char speciality[10];
	int price;
	int isReferral;
}typedef doc;

doc IDcheck(doc *dArr,long idCheck, int dArrSize)
{
	for (int i = 0; i < dArrSize; i++)
	{
		if (dArr[i].id == idCheck)
		{
			return dArr[i];
		}
	}
	printf("Inavalid ID");
	return;

}

int main()
{
	pat p1, p2, p3;
	// patient 1 information
	strcpy(p1.name, "Alex");
	p1.id = 321223075;
	strcpy(p1.password, "A123456");
	strcpy(p1.phone, "0545542719");

	//patient 2 information
	strcpy(p2.name, "Bar");
	p2.id = 123456789;
	strcpy(p2.password, "B123456");
	strcpy(p2.phone, "0557483593");


	//patient 3 information
	strcpy(p3.name, "Shira");
	p3.id = 123456789;
	strcpy(p3.password, "C123456");
	strcpy(p3.phone, "0325236324");

	doc d1, d2, d3;

	//doctor 1 information
	strcpy(d1.name, "Neta");
	d1.gender = 'F';
	d1.id = 123456789;
	d1.isReferral = 1;
	strcpy(d1.password, "D123456");
	strcpy(d1.phone, "0542245135");
	d1.price = 100;
	strcpy(d1.speciality, "Eye");

	//doctor 2 information
	strcpy(d2.name, "David");
	d2.gender = 'M';
	d2.id = 123456789;
	d2.isReferral = 0;
	strcpy(d2.password, "E123456");
	strcpy(d2.phone, "0501244545");
	d2.price = 75;
	strcpy(d2.speciality, "Family");

	
	//doctor 3 information
	strcpy(d3.name, "Vlad");
	d3.gender = 'M';
	d3.id = 123456789;
	d3.isReferral = 1;
	strcpy(d3.password, "F123456");
	strcpy(d3.phone, "0521235693");
	d3.price = 50;
	strcpy(d3.speciality, "Dermatologist");

	doc dArr[10];
	dArr[0] = d1;
	dArr[1] = d2;
	dArr[2] = d3;
	int dArrSize = 3;

	pat pArr[10];
	pArr[0] = p1;
	pArr[1] = p2;
	pArr[2] = p3;
	int pArrSize = 3;


	printf("Pick an option: \n 1-I'm a Doctor. \n 2-I'm a patient");
	int num;
	scanf("%d", &num);
	printf("Enter an ID: \n");
	long idCheck;
	scanf("%ld", &idCheck);
	if (num == 1)
	{
		IDcheck(dArr, idCheck, dArr);
	}
	switch (num)
	{
	case 1:

		printf
	default:
		break;
	}

}