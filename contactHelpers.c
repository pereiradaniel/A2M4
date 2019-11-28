//==============================================
// Name:           Full name here
// Student Number: #########
// Email:          userID@myseneca.ca
// Section:        XXX
// Date:           
//==============================================
// Assignment:     2
// Milestone:      4
//==============================================

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
// #include <stdlib.h>
#include "contactHelpers.h"

#define MAXCONTACTS 5

// Function Definitions
//--------------------------------
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        function definitions below...            |

// Function Definitions
void clearKeyboard(void)
{
	while (getchar() != '\n'); // empty execution code block on purpose
}

void pause(void) {

	printf("(Press Enter to Continue)");
	clearKeyboard();
}

int getInt(void) {
	int value;		// integer
	char NL = 'x';	// new line
	scanf("%d%c", &value, &NL);

	while (NL != '\n')
	{
		clearKeyboard();
		printf("*** INVALID INTEGER *** <Please enter an integer>: ");
		scanf("%d%c", &value, &NL);
	}
	return value;
}

int getIntInRange(int min, int max) {
	int mid = getInt();
	while ((mid < min) || (mid > max))
	{
		printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", min, max);
		mid = getInt();
	}
	return mid;
}

int yes(void) {
	char yn = 'x';
	char nlc = 'x';
	int res = -1;

	scanf(" %c%c", &yn, &nlc);

	while (!((nlc == '\n') && ((yn == 'Y') || (yn == 'y') || (yn == 'n') || (yn == 'N'))))
	{
		clearKeyboard();
		printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
		scanf(" %c%c", &yn, &nlc);
	}

	if ((yn == 'Y') || (yn == 'y'))
	{
		res = 1;
	}
	else if ((yn == 'N') || (yn == 'n'))
	{
		res = 0;
	}

	return res;
}

int menu(void)
{
	int moption;  // menuoption

	printf("Contact Management System\n");
	printf("-------------------------\n");
	printf("1. Display contacts\n");
	printf("2. Add a contact\n");
	printf("3. Update a contact\n");
	printf("4. Delete a contact\n");
	printf("5. Search contacts by cell phone number\n");
	printf("6. Sort contacts by cell phone number\n");
	printf("0. Exit\n");
	printf("\n");
	printf("Select an option:> ");

	moption = getIntInRange(0, 6);
	return moption;
}

void contactManagerSystem(void)
{
	int mselect;	// menu selection
	struct Contact contactlist[MAXCONTACTS] =
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

	do {
		mselect = menu();
		switch (mselect)
		{
		case 0:
			printf("\nExit the program? (Y)es/(N)o: ");
			int quit = yes();
			if (quit == 1) {
				printf("\nContact Management System: terminated\n");
				return;
			}
			else { printf("\n"); }

			break;
		case 1:
			displayContacts(contactlist, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 2:
			addContact(contactlist, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 3:
			updateContact(contactlist, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 4:
			deleteContact(contactlist, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 5:
			searchContacts(contactlist, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 6:
			sortContacts(contactlist, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		default:
			printf("*** OUT OF RANGE *** <Enter a number between 0 and 6> ");
			break;
		}

	} while ((mselect >= 0) || (mselect <= 6));

	return;
}

// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        empty function definitions below...      |
// +-------------------------------------------------+

void getTenDigitPhone(char phoneNum[])
{
	int needInput = 1;

	while (needInput == 1) {
		int i = 0;
		scanf("%10s", phoneNum);
		clearKeyboard();

		//Ensuring all values entered are numerical digits and the length of string is 10
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
		else
		{
			printf("Enter a 10-digit phone number: ");
		}

	}
}

// findContactIndex:
int findContactIndex(const struct Contact contacts[], int size, const char cellNum[])
{
	int z = -1;
	int i;
	for (i = 0; i < size; i++)
	{
		if (strcmp(contacts[i].numbers.cell, cellNum) == 0)
		{
			z = i;
		}
	}
	return z;
}

void displayContactHeader(void)
{
	printf("+-----------------------------------------------------------------------------+\n");
	printf("|                              Contacts Listing                               |\n");
	printf("+-----------------------------------------------------------------------------+\n");
	return;
};

void displayContactFooter(int count)
{
	printf("+-----------------------------------------------------------------------------+\n");
	printf("Total contacts: %d\n\n", count);
	return;
};

void displayContact(const struct Contact* contact)
{
	char fullName[77] = { '\0' };

	// Full name
	if (strlen(contact->name.firstName) != 0)
	{
		strcat(fullName, contact->name.firstName);

		if (strlen(contact->name.middleInitial) != 0)
		{
			strcat(fullName, " ");
			strcat(fullName, contact->name.middleInitial);
		}

		strcat(fullName, " ");
		strcat(fullName, contact->name.lastName);


		printf(" %s\n", fullName);
		printf("    C: %-10s   H: %-10s   B: %-10s\n", contact->numbers.cell, contact->numbers.home, contact->numbers.business);
		printf("       %d %s, ", contact->address.streetNumber, contact->address.street);

		//apt number
		if (contact->address.apartmentNumber > 0)
		{
			printf("Apt# %d, ", contact->address.apartmentNumber);
		}

		printf("%s, %s\n", contact->address.city, contact->address.postalCode);
	}

	return;
};

void displayContacts(const struct Contact contacts[], int size)
{
	putchar('\n');
	displayContactHeader();  // header

	int i;
	int n = 0;

	for (i = 0; i < size; i++)
	{
		if (strlen(contacts[i].numbers.cell) > 0)
		{
			displayContact(&contacts[i]);  // contact
			n++;
		}
	}

	displayContactFooter(n);  // footer
	return;
};

void searchContacts(const struct Contact contacts[], int size)
{
	char sn[11];
	int x;

	printf("\nEnter the cell number for the contact: ");
	getTenDigitPhone(sn);

	x = findContactIndex(contacts, size, sn);

	if (x != -1)
	{
		putchar('\n');
		displayContact(&contacts[x]);
		putchar('\n');
	}
	else
	{
		printf("*** Contact NOT FOUND ***\n");
	}

	return;
};

void addContact(struct Contact contacts[], int size)
{
	int i;
	int w = -1;

	for (i = 0; i < size; i++)
	{
		if (strlen(contacts[i].numbers.cell) == 0)
		{
			w = i;
		}
	}

	if (w != -1)
	{
		putchar('\n');
		getContact(&contacts[w]);
		printf("--- New contact added! ---\n");
	}
	else
	{
		printf("\n*** ERROR: The contact list is full! ***\n");
	}

	return;
};

void updateContact(struct Contact contacts[], int size)
{
	char cn[11];
	int v;


	printf("\nEnter the cell number for the contact: ");
	getTenDigitPhone(cn);
	v = findContactIndex(contacts, size, cn);

	if (v != -1)
	{
		printf("\nContact found:\n");
		displayContact(&contacts[v]);

		putchar('\n');


		printf("Do you want to update the name? (y or n): ");
		if (yes())
		{
			getName(&contacts[v].name);
		}


		printf("Do you want to update the address? (y or n): ");
		if (yes())
		{
			getAddress(&contacts[v].address);
		}


		printf("Do you want to update the numbers? (y or n): ");
		if (yes())
		{
			getNumbers(&contacts[v].numbers);
		}

		printf("--- Contact Updated! ---\n");

	}

	else
	{
		printf("*** Contact NOT FOUND ***\n");
	}

	return;
};

void deleteContact(struct Contact contacts[], int size)
{
	char cn[11];
	int u;

	printf("\nEnter the cell number for the contact: ");
	getTenDigitPhone(cn);

	u = findContactIndex(contacts, size, cn);

	if (u != -1)
	{
		printf("\nContact found:\n");
		displayContact(&contacts[u]);

		putchar('\n');

		printf("CONFIRM: Delete this contact? (y or n): ");
		if (yes())
		{
			strcpy(&contacts[u].numbers.cell[0], "\0");
			printf("--- Contact deleted! ---\n");
		}
	}
	else
	{
		printf("*** Contact NOT FOUND ***\n");
	}

	return;
};

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