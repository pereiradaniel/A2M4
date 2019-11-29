#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "contactHelpers.h"

#define MAXCONTACTS 5

// Function Definitions
void clearKeyboard(void)
{
	while (getchar() != '\n');
}

void pause(void) {
	printf("(Press Enter to Continue)\n");
	while (getchar() != '\n');
}

int getInt(void) {
	int val = 0;
	char NL = 'x';

	while (NL != '\n')
	{
		scanf("%d%c", &val, &NL);
		if (NL != '\n')
		{
			clearKeyboard();
			printf("*** INVALID INTEGER *** <Please enter an integer>: ");
		}
	}

	return val;
}

int getIntInRange(int min, int max) {
	int value = 0;
	value = getInt();

	while (!(value >= min && value <= max))
	{
		printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", min, max);
		value = getInt();
	}

	return value;
}

int yes(void) {
	char yrn;
	char NL = 'x';

	scanf("%c%c", &yrn, &NL);

	while (NL != '\n' || !(yrn == 'y' || yrn == 'n' || yrn == 'Y' || yrn == 'N'))
	{
		clearKeyboard();
		printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
		scanf("%c%c", &yrn, &NL);
	}

	return ((yrn == 'y' || yrn == 'Y') ? 1 : 0);
}


int menu(void) {
	printf("Contact Management System\n");
	printf("-------------------------\n");
	printf("1. Display contacts\n");
	printf("2. Add a contact\n");
	printf("3. Update a contact\n");
	printf("4. Delete a contact\n");
	printf("5. Search contacts by cell phone number\n");
	printf("6. Sort contacts by cell phone number\n");
	printf("0. Exit\n\n");
	printf("Select an option:> ");

	int opt = getIntInRange(0, 6);

	printf("\n");

	return opt;
}

void contactManagerSystem(void) {
	struct Contact contacts[MAXCONTACTS] =
	{ { { "Rick", {'\0'}, "Grimes" },
		{ 11, "Trailer Park", 0, "A7A 2J2", "King City" },
		{ "4161112222", "4162223333", "4163334444" } },
		{
		{ "Maggie", "R.", "Greene" },
		{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
		{ "9051112222", "9052223333", "9053334444" } },
		{
		{ "Morgan", "A.", "Jones" },
		{ 77, "Cottage Lane", 0, "C7C 9Q9", "Peterborough" },
		{ "7051112222", "7052223333", "7053334444" } },
		{
		{ "Sasha", {'\0'}, "Williams" },
		{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
		{ "9052223333", "9052223333", "9054445555" } },
	};

	int xit = 0;

	while (xit == 0)
	{
		int mselect = menu();

		switch (mselect)
		{
		case 0:
			printf("Exit the program? (Y)es/(N)o: ");
			xit = yes();
			printf("\n");
			break;

		case 1:
			displayContacts(contacts, MAXCONTACTS);
			pause();
			break;

		case 2:
			addContact(contacts, MAXCONTACTS);
			pause();
			break;

		case 3:
			updateContact(contacts, MAXCONTACTS);
			pause();
			break;

		case 4:
			deleteContact(contacts, MAXCONTACTS);
			pause();
			break;

		case 5:
			searchContacts(contacts, MAXCONTACTS);
			pause();
			break;

		case 6:
			sortContacts(contacts, MAXCONTACTS);
			pause();
			break;

		default:
			break;
		}
	}
	printf("Contact Management System: terminated\n");
}

void getTenDigitPhone(char phoneNum[])
{
	int needInput = 1;
	while (needInput == 1)
	{
		int i = 0;
		scanf("%10s", phoneNum);
		clearKeyboard();

		if (strlen(phoneNum) == 10)
		{
			needInput = 0;

			for (i = 0; i < 10; i++)
			{
				if (!isdigit(phoneNum[i]))
				{
					needInput = 1;

					printf("Enter a 10-digit phone number: ");
					break;
				}
			}
		}
		else {
			printf("Enter a 10-digit phone number: ");
		}
	}
}

int findContactIndex(const struct Contact contacts[], int size, const char cellNum[])
{
	int v = -1;
	int i = 0;
	int cExist = 0;
	for (i = 0; i < size; i++)
	{
		cExist = strcmp(contacts[i].numbers.cell, cellNum);
		if (cExist == 0) {
			v = i;
			break;
		}
	}
	return v;
}

void displayContactHeader(void) {
	printf("+-----------------------------------------------------------------------------+\n");
	printf("|%30sContacts Listing%31s|\n", "", "");
	printf("+-----------------------------------------------------------------------------+\n");
}

void displayContactFooter(int count) {
	printf("+-----------------------------------------------------------------------------+\n");
	printf("Total contacts: %d\n\n", count);
}

void displayContact(const struct Contact* contact) {
	if (contact->name.middleInitial[0] == '\0')
	{
		printf(" %s %s\n", contact->name.firstName, contact->name.lastName);
	}
	else
	{
		printf(" %s %s %s\n", contact->name.firstName, contact->name.middleInitial, contact->name.lastName);
	}
	printf("    C: %-10s   H: %-10s   B: %-10s\n", contact->numbers.cell, contact->numbers.home, contact->numbers.business);
	printf("       %d %s, ", contact->address.streetNumber, contact->address.street);
	if (contact->address.apartmentNumber > 0)
	{
		printf("Apt# %d, ", contact->address.apartmentNumber);
	}
	printf("%s, %s\n", contact->address.city, contact->address.postalCode);
}

void displayContacts(const struct Contact contacts[], int size) {
	int i = 0;
	int n = 0;
	displayContactHeader();
	for (i = 0; i < size; i++)
	{
		if (contacts[i].numbers.cell[0] != '\0')
		{
			displayContact(&contacts[i]);
			++n;
		}
	}

	displayContactFooter(n);
}

void searchContacts(const struct Contact contacts[], int size) {
	char cellNumber[11];
	int newIndex = 0;

	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(cellNumber);

	newIndex = findContactIndex(contacts, size, cellNumber);

	if (newIndex != -1)
	{
		printf("\n");
		displayContact(&contacts[newIndex]);
		printf("\n");
	}
	else
	{
		printf("*** Contact NOT FOUND ***\n\n");
	}
}

void addContact(struct Contact contacts[], int size) {
	char blank[11] = "";

	int newIndex = findContactIndex(contacts, size, blank);

	if (newIndex != -1)
	{
		getContact(&contacts[newIndex]);
		printf("--- New contact added! ---\n\n");
	}
	else
	{
		printf("*** ERROR: The contact list is full! ***\n\n");
	}
}

void updateContact(struct Contact contacts[], int size) {
	char cn[11];

	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(cn);

	int newIndex = findContactIndex(contacts, size, cn);

	if (newIndex != -1)
	{
		printf("\nContact found:\n");

		displayContact(&contacts[newIndex]);
		printf("\n");

		printf("Do you want to update the name? (y or n): ");
		int yorn = yes();
		if (yorn == 1)
		{
			getName(&contacts[newIndex].name);
		}

		printf("Do you want to update the address? (y or n): ");
		yorn = yes();
		if (yorn == 1)
		{
			getAddress(&contacts[newIndex].address);
		}

		printf("Do you want to update the numbers? (y or n): ");
		yorn = yes();
		if (yorn == 1)
		{
			getNumbers(&contacts[newIndex].numbers);
		}

		printf("--- Contact Updated! ---\n\n");
	}
	else
	{
		printf("*** Contact NOT FOUND ***\n\n");
	}
}

void deleteContact(struct Contact contacts[], int size) {
	char cn[11];

	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(cn);
	int newIndex = findContactIndex(contacts, size, cn);
	if (newIndex != 1)
	{
		printf("\nContact found:\n");
		displayContact(&contacts[newIndex]);

		printf("\nCONFIRM: Delete this contact? (y or n): ");
		int yorn = yes();
		if (yorn == 1)
		{
			contacts[newIndex].numbers.cell[0] = '\0';
			printf("--- Contact deleted! ---\n\n");
		}
		else if (yorn == 0)
		{
			printf("\n");
		}
	}
	else {
		printf("*** Contact NOT FOUND ***");
	}
}

void sortContacts(struct Contact contacts[], int size) {
	struct Contact swap[1];
	int i, j;

	for (i = 0; i < size - 1; i++)
	{
		for (j = i + 1; j < size; j++)
		{
			if (strcmp(contacts[i].numbers.cell, contacts[j].numbers.cell) > 0)
			{
				swap[0] = contacts[i];
				contacts[i] = contacts[j];
				contacts[j] = swap[0];
			}
		}
	}
	printf("--- Contacts sorted! ---\n\n");
}