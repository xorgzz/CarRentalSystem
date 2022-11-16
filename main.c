#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define green "\033[0;92m"
#define white "\033[0;97m"
#define red "\033[0;91m"
#define cyan "\033[0;96m"
#define magenta "\033[0;95m"

int allCars=0, allCustomers=0;
char strInput[128];

struct car {
	int carId;
	long time;
	char carBrand[32];
	char carModel[32];
	char carColor[32];
	char takenFree[64];
	char pricePerDay[8];
};

struct customer {
	int customerId;
	char name[128];
	char drivingLicenceId[64];
	char homeAddress[128];
};

struct customer cust[256];
struct car car[64];

void banner() {
	system("clear");
	printf(cyan);
	printf("██████   █████  ██████          ██████  ███████ ███    ██ ████████  █████  ██\n");
	printf("██      ██   ██ ██   ██         ██   ██ ██      ████   ██    ██    ██   ██ ██\n");
	printf("██      ███████ ██████          ██████  █████   ██ ██  ██    ██    ███████ ██\n");
	printf("██      ██   ██ ██   ██         ██   ██ ██      ██  ██ ██    ██    ██   ██ ██\n");
	printf("██████  ██   ██ ██   ██         ██   ██ ███████ ██   ████    ██    ██   ██ ██████\n\n");
}

char* readInput(int max) {
	for(int i=0; i < max; i++) {
		strInput[i] = getchar();
		if(strInput[i] == 10) {
			strInput[i] = 0;
			break;
		}
	}
	return strInput;
}

char* delUnderscore(char name[64]) {
	int length = strlen(name);
	for(int i=0; i < length; i++) {
		if(name[i] ==  '_') {
			name[i] = ' ';
		}
	}
	return name;
}

char* addUnderscore(char name[64]) {
	int length = strlen(name);
	for(int i=0; i < length; i++) {
		if(name[i] ==  ' ') {
			name[i] = '_';
		}
	}
	return name;
}

void carsRead() {
	allCars = 0;
	FILE* fp;
	fp = fopen("cars", "r");

	if(fp == NULL) {
		printf("no car database\n");
	}
	else {
		for(int i=0; i < 64; i++) {
			if(feof(fp)) {
				allCars = i;
				fclose(fp);
				break;
			}
			fscanf(fp, "%d", &car[i].carId);
			fscanf(fp, "%s", car[i].carBrand);
			fscanf(fp, "%s", car[i].carModel);
			fscanf(fp, "%s", car[i].carColor);
			fscanf(fp, "%s", car[i].takenFree);
			fscanf(fp, "%s", car[i].pricePerDay);
			fscanf(fp, "%ld", &car[i].time);
		}
	}
}

void customerRead() {
	allCustomers = 0;
	FILE* fp;
	fp = fopen("customers", "r");
	if(fp == NULL) {
		printf("trouble with finding customer database\n");
	}
	else {
		for(int i=0; i < 128; i++) {
			if(feof(fp)) {
				allCustomers = i;
				fclose(fp);
				break;
			}
			fscanf(fp, "%d", &cust[i].customerId);
			fscanf(fp, "%s", cust[i].name);
			fscanf(fp, "%s", cust[i].drivingLicenceId);
			fscanf(fp, "%s", cust[i].homeAddress);
		}
	}
}

void printCust() {
	char extra[4];
	customerRead();
	printf("\nID\tName          Dirver's Licence   Home Address\n\n");
	printf(green);
	for(int i = 0; i < allCustomers; i++) {
		if(cust[i].customerId <= 9){
			strcpy(extra, "00");
		}
		else if(cust[i].customerId <= 99) {
			strcpy(extra, "0");
		}
		else {
			strcpy(extra, "");
		}
		printf("%s%d\t%s | %s | %s\n", extra, cust[i].customerId, delUnderscore(cust[i].name), cust[i].drivingLicenceId, delUnderscore(cust[i].homeAddress));
	}
	printf("\n");
}

void saveToDB() {
	FILE* fp;
	fp = fopen("cars", "w");

	if(fp == NULL) {
		printf("no car database\n");
	}
	else {
		for(int i=0; i < allCars; i++) {
			if(i != 0) {
				fprintf(fp, "\n");
			}
			fprintf(fp, "%d ", car[i].carId);
			fprintf(fp, "%s ", addUnderscore(car[i].carBrand));
			fprintf(fp, "%s ", addUnderscore(car[i].carModel));
			fprintf(fp, "%s ", addUnderscore(car[i].carColor));
			fprintf(fp, "%s ", addUnderscore(car[i].takenFree));
			fprintf(fp, "%s ", car[i].pricePerDay);
			fprintf(fp, "%ld", car[i].time);
		}
	}
	fclose(fp);
}

void addCar() {
	char tmpBrand[32], tmpModel[32], tmpColor[32], tmpPrice[8];
	printf("car brand: ");
	strcpy(tmpBrand, readInput(32));
	printf("car model: ");
	strcpy(tmpModel, readInput(32));
	printf("car color: ");
	strcpy(tmpColor, readInput(32));
	printf("car's price per day: ");
	strcpy(tmpPrice, readInput(8));

	FILE* fp;
	fp = fopen("cars", "a");
	fprintf(fp, "\n%d %s %s %s FREE %s", allCars, addUnderscore(tmpBrand), addUnderscore(tmpModel), addUnderscore(tmpColor), tmpPrice);
	fclose(fp);
	carsRead();
}

void printAll(int nav) {
	char extra[4];
	carsRead();
	printf("\nID\tBrand   Model   Color   Status   PricePerDay\n\n");
	for(int i = 0; i < allCars; i++) {
		if(car[i].carId <= 9){
			strcpy(extra, "00");
		}
		else if(car[i].carId <= 99) {
			strcpy(extra, "0");
		}
		else {
			strcpy(extra, "");
		}
		if(nav == 0) {
			printf(red);
		}
		else if(nav == 1) {
			printf(green);
		}

		if(strcmp(car[i].takenFree, "FREE") && nav == 1 || !strcmp(car[i].takenFree, "FREE") && nav == 0) {
			continue;
		}
		else if(nav == 2) {
			if(strcmp(car[i].takenFree, "FREE")) {
				printf(red);
			}
			else {
				printf(green);
			}
		}
		printf("%s%d\t%s | %s | %s | %s | %s $/day\n", extra, car[i].carId, delUnderscore(car[i].carBrand), delUnderscore(car[i].carModel), delUnderscore(car[i].carColor), delUnderscore(car[i].takenFree), car[i].pricePerDay);
	}
 	printf(white);
 	printf("\n");
}

void back() {
	int tmpId, tmpTime, price;
	char tmpIdStr[4], pricePerDay[8];
	carsRead();
	time_t now;
	time(&now);
	printAll(0);
	printf("which car to bring back (ID): ");
	strcpy(tmpIdStr, readInput(4));
	if(!strcmp(tmpIdStr, "") || !strcmp(tmpIdStr, " ")) {
		printf(red);
		printf("no ID given\n\n");
		return;
	}
	tmpId = atoi(tmpIdStr);
	if(tmpId > allCars) {
		printf(red);
		printf("no car with given ID\n\n");
		return;
	}

	if(!strcmp(car[tmpId].takenFree, "FREE")) {
		printf(red);
		printf("car is already FREE\n\n");
		printf(white);
	}
	else {
		strcpy(pricePerDay, car[tmpId].pricePerDay);
		price = atof(pricePerDay);
		strcpy(car[tmpId].takenFree, "FREE");
		tmpTime = car[tmpId].time/3600/24;
		car[tmpId].time = 0;

		now = now/3600/24;
		tmpTime = now - tmpTime;
		if(tmpTime != 0) {
			price = tmpTime * price;
		}
		else {
			tmpTime = 1;
		}

		saveToDB();
		carsRead();
		printf(green);
		printf("car has been succesfuly brought back\ntime used %d days\nfee to pay $ %d\n\n", tmpTime, price);
		printf(white);
	}
}

int inCustList(char customer[128]) {
	for(int i=0; i < allCustomers; i++) {
		if(!strcmp(customer, cust[i].name)) {
			return 1;
		}
	}
	return 0;
}

void saveCust() {
	FILE* fp;
	fp = fopen("customers", "w");
	if(fp == NULL) {
		printf("no customer database\n");
	}
	else {
		for(int i=0; i < allCustomers; i++) {
			if(i != 0) {
				fprintf(fp, "\n");
			}
			fprintf(fp, "%d ", cust[i].customerId);
			fprintf(fp, "%s ", addUnderscore(cust[i].name));
			fprintf(fp, "%s ", addUnderscore(cust[i].drivingLicenceId));
			fprintf(fp, "%s", addUnderscore(cust[i].homeAddress));
		}
	}
	fclose(fp);
}

void rentACar() {
	time_t sec;
	time(&sec);
	int tmpId;
	char tmpName[64], tmpIdStr[4], tmpDrivLic[64], tmpHomeAdd[128];
	printAll(1);
	printf("ID of car to rent: ");
	carsRead();
	strcpy(tmpIdStr, readInput(4));
	tmpId = atoi(tmpIdStr);
	if(tmpId < allCars) {
		if(strcmp(car[tmpId].takenFree, "FREE")) {
			printf(red);
			printf("car already rented by %s\n\n", delUnderscore(car[tmpId].takenFree));
			printf(white);
		}
		else {
			printf("who's renting: ");
			strcpy(tmpName, readInput(64));
			if(!strcmp(tmpName, "") || !strcmp(tmpName, " ")) {
					printf(red);
					printf("wrong name\n\n");
					return;
				}
			customerRead();
			if(!inCustList(addUnderscore(tmpName))) {
				printf(magenta);
				printf("no name in database, full registration needed\n\n");
				printf(white);
				printf("the driver's licence(16): ");
				strcpy(tmpDrivLic, readInput(64));
				if(!strcmp(tmpDrivLic, "") || !strcmp(tmpDrivLic, " ") || strlen(tmpDrivLic) != 16) {
					printf(red);
					printf("wrong driver's licence\n\n");
					return;
				}
				printf("the current place of residence: ");
				strcpy(tmpHomeAdd, readInput(128));
				if(!strcmp(tmpHomeAdd, "") || !strcmp(tmpHomeAdd, " ")) {
					printf(red);
					printf("wrong home address\n\n");
					return;
				}

				// saving to temp database

				cust[allCustomers].customerId = allCustomers;
				strcpy(cust[allCustomers].name, addUnderscore(tmpName));
				strcpy(cust[allCustomers].drivingLicenceId, tmpDrivLic);
				strcpy(cust[allCustomers].homeAddress, addUnderscore(tmpHomeAdd));
				allCustomers++;

				// saving to permanent database

				saveCust();
				customerRead();
			}
			strcpy(car[tmpId].takenFree, tmpName);
			car[tmpId].time = sec;
			saveToDB();
			carsRead();
			printf(green);
			printf("car succesfuly rented\n\n");
			printf(white);
			
		}
	}
	else {
		printf(red);
		printf("no car with folowing ID: %d\n\n", tmpId);
		printf(white);
	}
}

void help() {
	printf(magenta);
	printf("\n");
	printf("?/help\tto print help\n");
	printf("cust\tto display all registered customers\n");
	printf("all\tto print all cars\n");
	printf("av\tto print all available cars\n");
	printf("taken\tto print all taken cars\n");
	printf("add\tadd a car to list\n");
	printf("rent\trent a car\n");
	printf("back\tto give back a rented car\n");
	printf("exit\tto exit software\n");
	printf("\n");
}

int main() {
	//banner(); // works properly only in Linux shell
	help();
	char comms[16];
	customerRead();
	carsRead();
	while(1) {
		strcpy(comms, "");
		printf(cyan);
		printf("~~> ");
		printf(white);
		strcpy(comms, readInput(16));
		if(!strcmp(comms, "exit")) {
			break;
		}
		else if(!strcmp(comms, "help") || !strcmp(comms, "?")) {
			help();
		}
		else if(!strcmp(comms, "cust")) {
			printCust();
		}
		else if(!strcmp(comms, "add")) {
			addCar();
		}
		else if(!strcmp(comms, "all")) {
			printAll(2);
		}
		else if(!strcmp(comms, "rent")) {
			rentACar();
		}
		else if(!strcmp(comms, "av")) {
			printAll(1);
		}
		else if(!strcmp(comms, "taken")) {
			printAll(0);
		}
		else if(!strcmp(comms, "back")) {
			back();	
		}
	
	}

	return 0;
}