#include <stdio.h>
#include <string.h>
#include "person.h"

void person_set_name(struct Person *p, const char *name) {
    /* copy safely: never write more than 31 chars + '\0' */
    strncpy(p->name, name, sizeof(p->name) - 1);
    p->name[sizeof(p->name) - 1] = '\0';
}

void person_birthday(struct Person *p) {
    p->age++;            /* same as (*p).age++ */
}

void person_print(const struct Person *p) {
    printf("%s, %d years old, born %d-%02d-%02d\n",
           p->name, p->age, p->dob.year, p->dob.month, p->dob.day);
}

double person_average_age(const struct Person people[], int n) {
    if (n <= 0) return 0.0;
    int total = 0;
    for (int i = 0; i < n; i++) total += people[i].age;
    return (double)total / n;
}
