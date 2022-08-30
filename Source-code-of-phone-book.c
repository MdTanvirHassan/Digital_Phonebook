#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

enum Type{Mobile=1, Home=2, Work=3, Main=4, Other=5 };
enum Group{Emergency=1, Colleague=2, Family=3, Friend=4, Not_Available=5 };
enum Relationship{Parent=1, Mother=2, Father=3, Brother=4, Sister=5, Friends=6, Relative=7, Unknown=8};

typedef enum { False, True } boolean;

struct Contact{
	int Id;
	char CreateTime[50];
	char Name[100];
	char PhoneNumber[11];
	char Email[100];
	int Group;
	char Company[100];
	char Address[100];
	int Relationship;
	char Notes[100];
	char Phone[11];
	boolean IsBlocked;
};

struct Contact contacts[100];
struct Contact contactList[1000];
int Total = 0;
int K=0;
boolean showBlockContacts = False;

void CreateNewContact();
void ViewContacts();
void EditContact();
void FindContact();
void RemoveContact();
void BlockContact();
void ViewBlockContact();

void showTitle(){
	printf("\n\n\n");
	printf("\t\t\t*****************************************\n");
	printf("\t\t\tWelcome to my Digital Phonebook\n");
	printf("\t\t\t*****************************************\n\n");
}

void showOptions(){
	printf("\t\t\t1. Create new contact\n");
	printf("\t\t\t2. View all contact\n");
	printf("\t\t\t3. Edit contact\n");
	printf("\t\t\t4. Find contact\n");
	printf("\t\t\t5. Remove contact\n");
	printf("\t\t\t6. Block contact\n");
	printf("\t\t\t7. View Block contacts\n");
	printf("\t\t\t8. Exit\n\n");
	printf("\t\t\tSelect your option: ");

}

void showContactActionTitle(char a[100]){
	printf("\t\t\t%s\n",a);
}

void processUserOption(){
	int n;
	scanf("%d",&n);
	switch(n){
		case 1:
			CreateNewContact();
			break;
		case 2:
			K = 0;
			showBlockContacts = False;
			ViewContacts();
			break;
		case 3:
			K = 0;
			showBlockContacts = False;
			EditContact();
			break;
		case 4:
			K = 0;
			showBlockContacts = False;
			FindContact();
			break;
		case 5:
			K = 0;
			showBlockContacts = False;
			RemoveContact();
			break;
		case 6:
			K = 0;
			showBlockContacts = False;
			BlockContact();
			break;
		case 7:
			K = 0;
			showBlockContacts = True;
			ViewBlockContact();
			break;
		case 8:
		 	printf("\t\t\tGoodbye...");
			exit(1);
			break;
		default:
			system("cls");
			showTitle();
			showOptions();
			printf("\n\t\t\tPlease select again: ");
			processUserOption();
			break;
	}
}

void Reset(){
	system("cls");
	showTitle();
	showOptions();
	processUserOption();
}

int main(){
	showTitle();
	showOptions();
	processUserOption();
}

int getId(){
		FILE *fp;
		int id = 0;
		fp = fopen ("id.txt", "r" );
		fscanf(fp,"%d",&id);
		if(id == 0){
			id = 1;
		}else{
			id = id + 1;
		}

		fclose(fp);

		fp = fopen ("id.txt", "w" );
		fprintf(fp,"%d", id);
		fclose(fp);

		return id;
}

void setContactId(int currentId){
	FILE *fp;
	int id = 0;
	fp = fopen ("id.txt", "r" );
	fscanf(fp,"%d",&id);

	if(currentId == 0){
		currentId = 1;
	}

	id = currentId;

	fclose(fp);

	fp = fopen ("id.txt", "w" );
	fprintf(fp,"%d", id);
	fclose(fp);

}

int checkDomain(const char *email, const char *domain) {
    int slen = strlen(email);
    int domain_len = strlen(domain);

	if(domain_len>slen){
		return 0;
	}

	if(strncmp(email + slen - domain_len, domain,domain_len)==0){
		return 1;
	}

    return 0;
}

struct Contact getContactInfo(){
	  struct Contact contact;
	  int valid = 0;
	  int g,r,i=0;
      contact.Id = getId();

	  fflush(stdin);
	  printf("\t\t\tName: ");
	  gets(contact.Name);

	  //printf("\t\t\tPhoneNumber: ");
	  //gets(contact.PhoneNumber);

	 // while(strlen(contact.PhoneNumber)>11 || strlen(contact.PhoneNumber)<10){
	  	//printf("\t\t\tPhoneNumber must be 11 digit.");
	  	//printf("\n\t\t\tPhoneNumber: ");
	   // gets(contact.PhoneNumber);
	  //}

	  printf("\t\t\tEmail: ");
	  gets(contact.Email);

	  valid = checkDomain(contact.Email, "@gmail.com")==1 || checkDomain(contact.Email, "@yahoo.com")==1 || checkDomain(contact.Email, "@outlook.com")==1;

	  while(valid==0){
	  	printf("\t\t\tEmail should be with a valid email domain");
	  	printf("\n\t\t\tEmail: ");
	  	gets(contact.Email);
	  	valid = checkDomain(contact.Email, "@gmail.com")==1 || checkDomain(contact.Email, "@yahoo.com")==1 || checkDomain(contact.Email, "@outlook.com")==1;
	  }

	  printf("\t\t\tGroup(1. Emergency, 2. Colleague, 3. Family, 4. Friend, 5. Not Available): ");
	  scanf("%d",&g);
	  if(g<1 || g>5){
	  	 g = 5;
	  }

	  contact.Group = g;

	  fflush(stdin);
	  printf("\t\t\tCompany: ");
	  gets(contact.Company);

	  printf("\t\t\tAddress: ");
	  gets(contact.Address);

	  printf("\t\t\tRelationship(1. Parent, 2. Mother, 3. Father, 4. Brother, 5. Sister, 6. Friends, 7. Relative, 8. Unknown): ");
	  scanf("%d",&r);
	  if(r<1 || r>8){
	  	 r = 8;
	  }

	  contact.Relationship = r;

	  fflush(stdin);
	  printf("\t\t\tNotes: ");
	  gets(contact.Notes);


      printf("\t\t\tPhoner: ");
	  gets(contact.Phone);



    while(strlen(contact.Phone)>11 || strlen(contact.Phone)<10){
	  	printf("\t\t\Phone must be 11 digit.");
	  	printf("\n\t\t\Phone: ");
	   gets(contact.Phone);
    }



	  contact.IsBlocked = False;

	  return contact;
}

void sortContactList(){
	int i,j;
	struct Contact temp;

	for(i=0;i<Total;i++){
		for(j=i+1;j<Total;j++){
			if(strcmp(contactList[i].Name,contactList[j].Name)>0){
				temp = contactList[i];
				contactList[i] = contactList[j];
				contactList[j] = temp;
			}
		}
	}
}

void AddToContactList(struct Contact contact){
		FILE *fp;
		char ch;

		printf("\n\t\t\tCreating....\n");
	  	sleep(3);

	  	loadContacts(1);
	  	contactList[Total] = contact;
	  	Total = Total + 1;
	  	sortContactList();

		fp = fopen ("contact.txt", "wb" );
		fwrite(contactList, sizeof(struct Contact), Total, fp);
	  	fclose (fp);

	  	printf("\t\t\tYour contact added successfully!\n");
	  	printf("\t\t\tDo you want to add another contact?(Y = Yes, N = No): ");

		scanf("%c",&ch);

	  	if(ch=='Y' || ch=='y'){
	  		CreateNewContact();
		}else{
			Reset();
		}
}

void CreateNewContact(){
	  system("cls");
	  showTitle();
	  showContactActionTitle("Create Contact");

	  struct Contact contact;

	  contact = getContactInfo();

	  AddToContactList(contact);
}

const char * getGroup(int g){
	if(g==1){
		return "Emergency";
	}else if(g==2){
		return "Colleague";
	}else if(g==3){
		return "Family";
	}else if(g==4){
		return "Friend";
	}else if(g==5){
		return "Not Available";
	}
}

const char * getRelationship(int r){
	if(r==1){
		return "Parent";
	}else if(r==2){
		return "Mother";
	}else if(r==3){
		return "Father";
	}else if(r==4){
		return "Brother";
	}else if(r==5){
		return "Sister";
	}else if(r==6){
		return "Friends";
	}else if(r==7){
		return "Relative";
	}else if(r==8){
		return "Unknown";
	}
}

void showContacts(int i, struct Contact contact){
	printf("\t\tContact %d\n",i);
	printf("\t\t\tName: %s\n",contact.Name);
	//printf("\t\t\tPhoneNumber000: %s\n",contact.PhoneNumber);
	printf("\t\t\tEmail: %s\n",contact.Email);
	printf("\t\t\tGroup: %s\n",getGroup(contact.Group));
	printf("\t\t\tCompany: %s\n",contact.Company);
	printf("\t\t\tAddress: %s\n",contact.Address);
	printf("\t\t\tRelationship: %s\n",getRelationship(contact.Relationship));
	printf("\t\t\tNotes: %s\n",contact.Notes);
	printf("\t\t\tPhone: %s\n",contact.Phone);
}

void loadContacts(int hide){
	struct Contact contact;
	FILE *fp;
	char ch;
	int i = 0;
	Total = 0;
	fp = fopen ("contact.txt", "rb" );
	if(hide==0){
		printf("\t\t\tLoading....");
		sleep(3);
		printf("done\n\n");
	}

	while (fread(&contact, sizeof(contact), 1, fp) == 1 ){
		contactList[i++] = contact;
		if(contact.IsBlocked==showBlockContacts){
			K++;
			contacts[K-1] = contact;
			if(hide==0){
				showContacts(K, contact);
			}
		}

	}
	Total = i;
	if(K<1 && hide==0){
		printf("\t\t\tNo Contact found!");
	}

	fclose(fp);
}

void PressAnyKey(){
	printf("\n\t\t\tPress any key to show options....");
	getch();
}

void ViewContactList(){
	loadContacts(0);
	PressAnyKey();
	Reset();
}

void ViewContacts(){
	 system("cls");
	 showTitle();
	 showContactActionTitle("Your Contacts");

	 ViewContactList();
}

void blockAnyContact(){
		FILE *fp;
		int id,i,n;
		char ch;
		struct Contact contact;
		n = K;

		if(K==0){
			printf("\n\t\t\tPress any key to show options....");
			getch();
			Reset();
		}

		printf("\n\t\t\tEnter the contact Id to block (0. Show Options ): ");
		scanf("%d",&id);
		if(id == 0){
			Reset();
		}
		if(id>K || id<1){
			printf("\n\t\t\tNo contact found for Id : %d",id);
			blockAnyContact();
		}else{
			for(i=0;i<Total;i++){
				if(contactList[i].Id==contacts[id-1].Id){
					contactList[i].IsBlocked = True;
					n = n - 1;
					break;
				}
			}

			fp = fopen ("contact.txt", "wb" );
			fwrite(contactList, sizeof(struct Contact), Total, fp);
		  	fclose (fp);

			printf("\n\t\t\tContact blocked successfully!");
		}

		if(n>0){
			printf("\n\t\t\tDo you want to block another contact?(Y = Yes, N = No): ");
			ch = getch();
			if(ch=='Y' || ch=='y'){
	  			BlockContact();
			}
		}
		PressAnyKey();
		Reset();
}

void BlockContact(){
	 system("cls");
	 showTitle();
	 showContactActionTitle("Block Contact");
	 loadContacts(0);
	 blockAnyContact();
}

void unblockAnyContact(){
	FILE *fp;
	int id,i,n;
	char ch;
	struct Contact contact;
	n = K;

	if(K==0){
		printf("\n\t\t\tPress any key to show options....");
		getch();
		Reset();
	}

	printf("\n\t\t\tEnter the contact Id to unblock (0. Show Options ): ");
	scanf("%d",&id);
	if(id == 0){
		Reset();
	}

	if(id>K || id<1){
		printf("n\t\t\tNo contact found for Id : %d",id);
	}else{
		for(i=0;i<Total;i++){
			if(contactList[i].Id==contacts[id-1].Id){
				contactList[i].IsBlocked = False;
				n = n - 1;
				break;
			}
		}

		fp = fopen ("contact.txt", "wb" );
		fwrite(contactList, sizeof(struct Contact), Total, fp);
	  	fclose (fp);

		printf("\n\t\t\tContact unblocked successfully!");
	}

	if(n>0){
		printf("\n\t\t\tDo you want to unblock another contact?(Y = Yes, N = No): ");
		ch = getch();
		if(ch=='Y' || ch=='y'){
	  		ViewBlockContact();
		}
	}
	PressAnyKey();
	Reset();
}

void ViewBlockContact(){
	 system("cls");
	 showTitle();
	 showContactActionTitle("Block listed Contacts");
	 loadContacts(0);
	 unblockAnyContact();
}

void RemoveAnyContact(){
	FILE *fp;
	int id,i,n;
	char ch;
	struct Contact contact;
	n = K;

	if(K==0){
		printf("\n\t\t\tPress any key to show options....");
		getch();
		Reset();
	}

	printf("\n\t\t\tEnter the contact Id to remove (0. Show Options ): ");
	scanf("%d",&id);
	if(id == 0){
		Reset();
	}

	if(id>K || id<1){
		printf("\n\t\t\tNo contact found for Id : %d",id);
		RemoveAnyContact();
	}else{
		for(i=id;i<Total;i++){
			contactList[i-1] = contactList[i];
		}
		Total = Total - 1;

		fp = fopen ("contact.txt", "wb" );
		fwrite(contactList, sizeof(struct Contact), Total, fp);
	  	fclose (fp);

	  	setContactId(Total);

		printf("\n\t\t\tContact removed successfully!");
	}

	if(n>0){
		printf("\n\t\t\tDo you want to remove another contact?(Y = Yes, N = No): ");
		ch = getch();
		if(ch=='Y' || ch=='y'){
	  		RemoveContact();
		}
	}
	PressAnyKey();
	Reset();
}

void RemoveContact(){
	system("cls");
	showTitle();
	showContactActionTitle("Remove Contact");
	loadContacts(0);
	RemoveAnyContact();
}

struct Contact EditContactInfo(struct Contact contact){
	char ch;
	int g,r;

	printf("\n\t\t\tDo you want to update Name? (Y==Yes, N=No): ");
	ch = getch();
	if(ch=='Y' || ch=='y'){
		fflush(stdin);
  		printf("\n\t\t\tCurrent Name: %s",contact.Name);
		printf("\n\t\t\tUpdated Name: ");
		gets(contact.Name);
	}

	printf("\n\t\t\tDo you want to update PhoneNumber? (Y==Yes, N=No): ");
	ch = getch();
	if(ch=='Y' || ch=='y'){
  		printf("\n\t\t\tCurrent PhoneNumber: %s",contact.PhoneNumber);
		printf("\n\t\t\tUpdated PhoneNumber: ");
		gets(contact.PhoneNumber);
	}

	printf("\n\t\t\tDo you want to update Email? (Y==Yes, N=No): ");
	ch = getch();
	if(ch=='Y' || ch=='y'){
  		printf("\n\t\t\tCurrent Email: %s",contact.Email);
		printf("\n\t\t\tUpdated Email: ");
		gets(contact.Email);
	}

	printf("\n\t\t\tDo you want to update Group? (Y==Yes, N=No): ");
	ch = getch();
	if(ch=='Y' || ch=='y'){
  		printf("\n\t\t\tCurrent Group: %s",getGroup(contact.Group));
		printf("\n\t\t\tUpdated Group(1. Emergency, 2. Colleague, 3. Family, 4. Friend, 5. Not Available): ");
		scanf("%d",&g);
		if(g<1 || g>5){
		  	g = 5;
		}
		contact.Group = g;
		fflush(stdin);
	}

	printf("\n\t\t\tDo you want to update Company? (Y==Yes, N=No): ");
	ch = getch();
	if(ch=='Y' || ch=='y'){
  		printf("\n\t\t\tCurrent Company: %s",contact.Company);
		printf("\n\t\t\tUpdated Company: ");
		gets(contact.Company);
	}

	printf("\n\t\t\tDo you want to update Address? (Y==Yes, N=No): ");
	ch = getch();
	if(ch=='Y' || ch=='y'){
  		printf("\n\t\t\tCurrent Address: %s",contact.Address);
		printf("\n\t\t\tUpdated Address: ");
		gets(contact.Address);
	}

	printf("\n\t\t\tDo you want to update Relationship? (Y==Yes, N=No): ");
	ch = getch();
	if(ch=='Y' || ch=='y'){
  		printf("\n\t\t\tCurrent Relationship: %s",getRelationship(contact.Relationship));
		printf("\n\t\t\tUpdated Relationship(1. Parent, 2. Mother, 3. Father, 4. Brother, 5. Sister, 6. Friends, 7. Relative, 8. Unknown): ");
		scanf("%d",&r);
		if(r<1 || r>8){
		  	r = 8;
		}
		contact.Relationship = r;
		fflush(stdin);
	}
	printf("\n\t\t\tDo you want to update Notes? (Y==Yes, N=No): ");
	ch = getch();
	if(ch=='Y' || ch=='y'){
  		printf("\n\t\t\tCurrent Notes: %s",contact.Notes);
		printf("\n\t\t\tUpdated Notes: ");
		gets(contact.Notes);
	}

	return contact;
}

void EditAnyContact(){
	FILE *fp;
	int id,i,n;
	char ch;
	struct Contact contact;
	n = K;

	if(K==0){
		printf("\n\t\t\tPress any key to show options....");
		getch();
		Reset();
	}
	printf("\n\t\t\tEnter the contact Id to edit (0. Show Options ): ");
	scanf("%d",&id);
	if(id == 0){
		Reset();
	}

	if(id>K || id<1){
		printf("\n\t\t\tNo contact found for Id : %d",id);
		EditAnyContact();
	}else{
		for(i=0;i<Total;i++){
			if(contactList[i].Id==contacts[id-1].Id){
				contact = contacts[id-1];
			}
		}

		contact = EditContactInfo(contact);

		for(i=0;i<Total;i++){
			if(contactList[i].Id==contact.Id){
				contactList[i] = contact;
			}
		}

		sortContactList();

		fp = fopen ("contact.txt", "wb" );
		fwrite(contactList, sizeof(struct Contact), Total, fp);
	  	fclose (fp);

		printf("\n\n\t\t\tContact edited successfully!");
	}
	if(n>0){
		printf("\n\t\t\tDo you want to edit another contact?(Y = Yes, N = No): ");
		ch = getch();
		if(ch=='Y' || ch=='y'){
	  		EditContact();
		}
	}
	PressAnyKey();
	Reset();
}

void EditContact(){
	system("cls");
	showTitle();
	showContactActionTitle("Edit Contact");
	loadContacts(0);
	EditAnyContact();
}

void findBy(int id, char* key){
	struct Contact result[100];
	int i,k=0;
	for(i=0;i<K;i++){
		if(id==1){
			if(strstr(contacts[i].Name, key)){
				result[k++] = contacts[i];
			}
		}else if(id==2){
			if(strstr(contacts[i].Phone, key)){
				result[k++] = contacts[i];
			}
		}else if(id==3){
			if(strstr(contacts[i].Email, key)){
				result[k++] = contactList[i];
			}
		}else if(id==4){
			if(strstr(contacts[i].Company, key)){
				result[k++] = contacts[i];
			}
		}else if(id==5){
			if(strstr(contacts[i].Address, key)){
				result[k++] = contacts[i];
			}
		}else if(id==6){
			if(strstr(contacts[i].Notes, key)){
				result[k++] = contacts[i];
			}
		}
	}
	if(k==0){
		printf("\n\t\t\tNo contact found for search key : %s\n",key);
		FindContact();
	}else{
		for(i=0;i<k;i++){
			showContacts(i+1, result[i]);
		}
	}
}

void FindAnyContact(){
	FILE *fp;
	int id,i,n;
	char ch;
	char key[100];
	struct Contact contact;

	if(Total==0){
		printf("\n\t\t\tPress any key to show options....");
		getch();
		Reset();
	}
	printf("\n\t\t\tSelect find by(1. Name, 2. PhoneNumber, 3. Email, 4. Company, 5. Address, 6. Notes) (0. Show Options ): ");
	scanf("%d",&id);
	if(id == 0){
		Reset();
	}else{
		fflush(stdin);
		printf("\n\t\t\tEnter search key: ");
		scanf("%s",&key);

		if(id>6 || id<1){
			id = 1;
		}

		findBy(id,key);
	}

	printf("\n\t\t\tDo you want to find another contact?(Y = Yes, N = No): ");
	ch = getch();
	if(ch=='Y' || ch=='y'){
  		FindContact();
	}
	PressAnyKey();
	Reset();
}

void FindContact(){
	system("cls");
	showTitle();
	showContactActionTitle("Find Contact");
	loadContacts(1);
	FindAnyContact();
}
