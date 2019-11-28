#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "contacts.h"
#include "contactHelpers.h"

void getName(struct Name* name)
{
	int yorn;
	// Ask for first name:
	printf("Please enter the contact's first name: ");
	scanf(" %30[^\n]", name->firstName);
	clearKeyboard();

	// Ask for middle initial:
	printf("Do you want to enter a middle initial(s)? (y or n): ");
	yorn = yes();
	if (yorn == 1)
	{
		printf("Please enter the contact's middle initial(s): ");
		scanf(" %6[^\n]", name->middleInitial);
		clearKeyboard();
	} else
	{
		name->middleInitial[0] = '\0';
	}

	// Ask for last name:
	printf("Please enter the contact's last name: ");
	scanf(" %35[^\n]", name->lastName);
	clearKeyboard();
}
void getAddress(struct Address* address)
{
	// Ask for street number:
	printf("Please enter the contact's street number: ");
	do {
		address->streetNumber = getInt();
		if (address->streetNumber < 1) {
			printf("*** INVALID STREET NUMBER *** <must be a positive number>: ");
		}
	} while (address->streetNumber < 1);

	// Ask for street name:
	printf("Please enter the contact's street name: ");
	scanf(" %40[^\n]", address->street);
	clearKeyboard();

	// Ask for apartment number:
	printf("Do you want to enter an apartment number? (y or n): ");
	int yorn = yes();
	if (yorn == 1)
	{
		printf("Please enter the contact's apartment number: ");
		do
		{
			address->apartmentNumber = getInt();
			if (address->apartmentNumber < 1) {
				printf("*** INVALID APARTMENT NUMBER *** <must be a positive number>: ");
			}
		} while (address->apartmentNumber < 1);
	}

	// Ask for postal code:
	printf("Please enter the contact's postal code: ");
	scanf(" %7[^\n]", address->postalCode);
	clearKeyboard();

	// Ask for city:
	printf("Please enter the contact's city: ");
	scanf(" %40[^\n]", address->city);
	clearKeyboard();
}
void getNumbers(struct Numbers* numbers)
{
	int yorn2;
	// Ask for cell number:
	printf("Please enter the contact's cell phone number: ");
	getTenDigitPhone(numbers->cell);

	// Ask for home number:
	printf("Do you want to enter a home phone number? (y or n): ");
	yorn2 = yes();
	if (yorn2 == 1)
	{
		printf("Please enter the contact's home phone number: ");
		getTenDigitPhone(numbers->home);
	}
	else {
		numbers->home[0] = '\0';
	}

	// Ask for business number:
	printf("Do you want to enter a business phone number? (y or n): ");
	yorn2 = yes();
	if (yorn2 == 1)
	{
		printf("Please enter the contact's business phone number: ");
		getTenDigitPhone(numbers->business);
	}
	else {
		numbers->business[0] = '\0';
	}
}

void getContact(struct Contact* contact) {
	struct Contact newContact;

	getName(&newContact.name);
	getAddress(&newContact.address);
	getNumbers(&newContact.numbers);

	*contact = newContact;
}
