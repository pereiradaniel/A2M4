#ifndef CONTACTS_H_
#define CONTACTS_H_

// Structure Types
struct Name {
	char firstName[31];
	char middleInitial[7];
	char lastName[36];
};
struct Address {
	int streetNumber;
	char street[41];
	int apartmentNumber;
	char postalCode[8];
	char city[41];
};
struct Numbers {
	char cell[11];
	char home[11];
	char business[11];
};
struct Contact
{
	struct Name name;
	struct Address address;
	struct Numbers numbers;
};

// Function Prototypes
void getName(struct Name* name);
void getAddress(struct Address* address);
void getNumbers(struct Numbers* numbers);
void getContact(struct Contact* contact);

#endif // !CONTACTS_H_