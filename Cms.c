#include "Cms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Contact contacts[MAX_CONTACTS];
int contactCount = 0;

CMSResult resultSuccess() {
	CMSResult result;
	result.success = 1;
	return result;
}

CMSResult resultFail(const char* error) {
	printf(error);

	CMSResult result;
	result.success = 0;
	strcpy(result.error, error);
	return result;
}

int nameDuplicate(const char *name);
int validateEmail(const char *email);
int validatePhoneNumber(const char *phone);
int validateName(const char *name);

CMSResult addContact(const char* name, const char* phone) {
    if (contactCount >= MAX_CONTACTS) {
        return resultFail("Contact list is full.\n");
    }

    Contact newContact;

	if (strlen(name) >= NAME_LENGTH) {
		return resultFail("Name is too long. Please enter a shorter name.\n");
	} else if (nameDuplicate(name)) {
		return resultFail("A contact with this name already exists. Please enter another name.\n");
	} else if (!validateName(name)) {
		return resultFail("Invalid name. Please enter alphabetic characters only.\n");
	}

	strcpy(newContact.name, name);
	newContact.name[strcspn(name, "\n")] = 0; // Remove trailing newline

	if (strlen(phone) >= PHONE_LENGTH) {
		return resultFail("Phone number is too long. Please enter a shorter phone number.\n");
	} else
	if (!validatePhoneNumber(phone)) {
		return resultFail("Invalid phone number. Please try again.\n");
	}

	strcpy(newContact.phone, phone);
	newContact.phone[strcspn(phone, "\n")] = 0; // Remove trailing newline

	newContact.id = contactCount;

    contacts[contactCount++] = newContact;
    printf("Contact added successfully.\n");

	return resultSuccess();
}

CMSResult removeContact(int id) {
	if (id < 0 || id >= contactCount) {
		return resultFail("Invalid contact ID.\n");
	}

	// Shift all contants down staring from the index of the contact to be removed.
	for (int i = id; i < contactCount - 1; i++) {
		contacts[i] = contacts[i + 1];
		contacts[i].id = i;
	}

	contactCount--;
	printf("Contact removed successfully.\n");

	return resultSuccess();
}

const Contact* getContacts(){
	return contacts;
}

int getContactCount() {
	return contactCount;
}

int nameDuplicate(const char *name) {
    for (int i = 0; i < contactCount; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            return 1; // Duplicate found
        }
    }
    return 0; // No duplicates
}

int validatePhoneNumber(const char *phone) {
    int length = strlen(phone);
    if ((strncmp(phone, "+44", 3) == 0 && length == 13) || 
        (strncmp(phone, "+60", 3) == 0 && length >= 10 && length <= 12)) {
        return 1;
    }
    return 0; // Invalid format
}

int validateEmail(const char *email) {
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');
    return (at && dot && at < dot);  // Ensure '@' comes before '.'
}

int validateName(const char *name) {
    if (strlen(name) == 0)
		return 0;  // Name can't be empty
    for (int i = 0; i < strlen(name); i++) {
        if (!isalpha(name[i]) && name[i] != ' ')
			return 0;  // Alphabetic characters only
    }

	return 1;
}