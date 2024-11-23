#ifndef CMS_H
#define CMS_H

#include <string.h>

#define MAX_CONTACTS 100
#define NAME_LENGTH 50
#define PHONE_LENGTH 15
#define EMAIL_LENGTH 50
#define ERROR_LENGTH 256

typedef struct {
    char name[NAME_LENGTH];
    char phone[PHONE_LENGTH];
} Contact;

typedef struct {
	int success;
    char error[ERROR_LENGTH];
} CMSResult;

CMSResult addContact(const char* name, const char* phone);

const Contact* getContacts();
int getContactCount();


#endif // CMS_H