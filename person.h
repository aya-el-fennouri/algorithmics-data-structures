#ifndef PERSON_H
#define PERSON_H

/* Structures in C (slides 23-26) */
struct Date {
    int year, month, day;
};

struct Person {
    char name[32];
    int age;
    struct Date dob;     /* nested struct */
};

void   person_set_name(struct Person *p, const char *name);
void   person_birthday(struct Person *p);              /* uses -> on a pointer */
void   person_print(const struct Person *p);
double person_average_age(const struct Person people[], int n);  /* array of structs */

#endif
