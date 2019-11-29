#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "contacts.h"
#include "contactHelpers.h"

void getName(struct Name* name) {
	int yorn;
	printf("Please enter the contact's first name: ");
	scanf("%[^\n]s", name->firstName);
	clearKeyboard();

	printf("Do you want to enter a middle initial(s)? (y or n): ");
	yorn = yes();
	if (yorn == 1)
	{
		printf("Please enter the contact's middle initial(s): ");
		scanf("%[^\n]s", name->middleInitial);
		clearKeyboard();
	}
	else
	{
		name->middleInitial[0] = '\0';
	}
	printf("Please enter the contact's last name: ");
	scanf("%[^\n]s", name->lastName);
	clearKeyboard();
}

void getAddress(struct Address* address) {
	int yorn;
	printf("Please enter the contact's street number: ");
	address->streetNumber = getInt();

	while (address->streetNumber < 1)
	{
		printf("*** INVALID STREET NUMBER *** <must be a positive number>: ");
		address->streetNumber = getInt();
	}

	printf("Please enter the contact's street name: ");
	scanf("%[^\n]s", address->street);
	clearKeyboard();

	printf("Do you want to enter an apartment number? (y or n): ");
	yorn = yes();
	if (yorn == 1)
	{
		printf("Please enter the contact's apartment number: ");
		address->apartmentNumber = getInt();
		while (address->apartmentNumber < 1)
		{
			printf("*** INVALID APARTMENT NUMBER *** <must be a positive number>: ");
			address->apartmentNumber = getInt();
		}

	}
	else
	{
		address->apartmentNumber = 0;
	}

	printf("Please enter the contact's postal code: ");
	scanf("%7[^\n]s", address->postalCode);
	clearKeyboard();

	printf("Please enter the contact's city: ");
	scanf("%40[^\n]s", address->city);
	clearKeyboard();
}

void getNumbers(struct Numbers* numbers) {
	int yorn;
	printf("Please enter the contact's cell phone number: ");
	getTenDigitPhone(numbers->cell);

	printf("Do you want to enter a home phone number? (y or n): ");
	yorn = yes();
	if (yorn == 1)
	{
		printf("Please enter the contact's home phone number: ");
		getTenDigitPhone(numbers->home);
	}
	else
	{
		numbers->home[0] = '\0';
	}

	printf("Do you want to enter a business phone number? (y or n): ");
	yorn = yes();

	if (yorn == 1)
	{
		printf("Please enter the contact's business phone number: ");
		getTenDigitPhone(numbers->business);
	}
	else
	{
		numbers->business[0] = '\0';
	}
}

void getContact(struct Contact* contact) {
	getName(&contact->name);
	getAddress(&contact->address);
	getNumbers(&contact->numbers);
}