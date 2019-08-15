#include <stdio.h>
#include<string.h>

typedef int(*familyDuty)(char*);

struct person {
	char*	 name;
	int	 age;
	familyDuty func;
};



struct familyTree {
	int nMembers;
	struct person p[2];
	struct familyTree* 	next;
};

typedef struct person Person_t;
typedef struct familyTree FamilyTree_t;

int Refua(char* name) { printf("I'm a doctor\n");		return 0; }
int Handasa(char* name) { printf("I'm an engineer\n");  return 0; }
FamilyTree_t Halakhmi = { 2, "Ilan", 28, Handasa, "Gilad", 26, Refua, 0};
FamilyTree_t Buchler = { 2, "Rita", 38, Handasa, "Brian", 30, Refua, 0};

void DoIt(FamilyTree_t* ftPtr, char* name) {	
	int i;
	for(i = 0; strcmp(name, ftPtr->p[i].name) != 0; i++);

	ftPtr->p[i].func(name);
}

int main() {
	DoIt(&Halakhmi, "Ilan");
	DoIt(&Halakhmi, "Gilad");
	DoIt(&Buchler, "Rita");
	return 1;
}
