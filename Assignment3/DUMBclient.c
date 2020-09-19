#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<pthread.h>
#include<unistd.h>

char*argHolder;


int main(int argc, char** argv){
	argHolder=malloc(4000*sizeof(char));
        int sock;
	int three=0;
	int status=-2;
	int countfuck=0;
	int curOpen=0;

	struct sockaddr_in servAddr; 
	while (three<3){
        sock=socket(AF_INET, SOCK_STREAM, 0);
        servAddr.sin_family = AF_INET;
        servAddr.sin_port = htons(atoi(argv[2]));
        servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	status = connect(sock, (struct sockaddr*) &servAddr, sizeof(servAddr));
	if(status == -1){
                printf("fuck\n");
		countfuck=countfuck+1;
		three=three+1;
		continue;
        }
	three=three+1;
	break;
	}

	if (countfuck==3){
	printf("\nFailed to connect :(, Goodbye!\n");
	return 0;
	}

/*
        char msg[256];
	char msgHi[256]="HELLO";
	send(sock,msgHi,sizeof(msgHi),0);
        recv(sock, &msg, sizeof(msg), 0);
	if (strcmp(msg,"HELLO DUMBv0 ready!")==0){
	printf("\n%s",msg);
	}
*/

int k=0;
int i=0;
char str[4000];
char name[4000];
char command[4000]="command!";
char *arg0=malloc(1000*sizeof(char));
char *arg1=malloc(4000*sizeof(char));
char creat[4000]="CREAT";
char openMsg[4000]="OPNBX";
char deleteMsg[4000]="DELBX";
char closeMsg[4000]="CLSBX";
char putMsg[4000]="PUTMG";
char nextMsg[4000]="NXTMG";

int gay=0;
char strGay[12];


printf("\nHELLO DUMBv0 ready!");

while(1){
k=0;
while (k<4000){
arg0[k]='\0';
arg1[k]='\0';
k=k+1;
}

if (curOpen==1){
printf("\nType 'help' for details:");
printf("\n%s:>",argHolder);
scanf("%s",command);
//can either be close, putmg or nxtmg
//anything else is an error, they must close the box

if (strcmp(command,"next")==0){
send(sock,nextMsg,sizeof(nextMsg),0);
recv(sock,&str,sizeof(str),0);
if (strlen(str)<6){
printf("\nThis message box is empty.");
}
k=3;
while (1){
if (str[k]=='!'){
break;
}
k=k+1;
}
k=k+1;
printf("\nMessage--> ");
while (k<strlen(str)){
printf("%c",str[k]);
k=k+1;
}

continue;
}

if (strcmp(command,"put")==0){
printf("\nPlease enter the message you would like put into the box.");
printf("\nmsg:>");
scanf("%s",arg1);
gay=strlen(arg1);
sprintf(strGay,"%d",gay);
strcat(putMsg,"!");
strcat(putMsg,strGay);
strcat(putMsg,"!");
strcat(putMsg,arg1);
send(sock,putMsg,sizeof(putMsg),0);
recv(sock,&str,sizeof(str),0);
printf("\nstr:%s",str);
strcpy(putMsg,"PUTMG");
continue;
}


if (strcmp(command,"close")==0){
send(sock,closeMsg,sizeof(closeMsg),0);
recv(sock,&command,sizeof(command),0);
curOpen=0;
continue;
}

if (strcmp(command,"help")==0){
printf("\n\nCommands:\nWHILE NOT INSIDE A BOX\n1)'create': Creates a new message box\n2)'open': Opens a message box\n3)'delete': Deletes an empty message box\n4)'quit': Ends connection with the terminal\n\nWHILE INSIDE A BOX:\n5)'put': Puts a new message into the box\n6)'next': Reads the next message in the box\n7)'close': Closes the currently open box");
send(sock,command,sizeof(command),0);
recv(sock,&str,sizeof(str),0);
continue;
}

send(sock,argHolder,sizeof(argHolder),0);
recv(sock,&command,sizeof(command),0);
printf("\nPlease use one of the following commands:\n1)'next'\n2)'put'\n3)'close'");
continue;
}//end if Open



//Can only be create,open,delete,quit

//close-putmg-nxtmg---> we tell user they must open a box

printf("\nType 'help' for details:\n");
printf("DUMBv0:>");
scanf("%s",command);

if (strcmp(command,"create")==0){
printf("\nWhat would you like to name your box?\n");
printf("create:>");
scanf("%s",arg0);
strcat(creat," ");
strcat(creat,arg0);
send(sock,creat,sizeof(creat),0);
recv(sock,&str,sizeof(str),0);
if (strcmp(str,"OK!")==0){
printf("\nBox successfully created: %s",arg0);
}
if (strcmp(str,"ER:EXIST!")==0){
printf("\nThat box already exists.");
}
if (strcmp(str,"ER:WHAT")==0){
printf("\nBox NOT created: You cannot name a box that.");
printf("\nPlease follow these rules below.");
printf("\n1) Box name must be between 5 and 25 characters long.");
printf("\n2) Box name must start with an alphabetic letter.");
}
strcpy(creat,"CREAT");
continue;
}


if (strcmp(command,"open")==0){
printf("\nWhich box do you want to open?");
printf("\nopen:>");
scanf("%s",arg0);
strcat(openMsg," ");
strcat(openMsg,arg0);
send(sock,openMsg,sizeof(openMsg),0);
recv(sock,&str,sizeof(str),0);
if(strcmp(str,"ER:NEXST")==0){
printf("\nThat box does not exist.");
}

if (strcmp(str,"ER:OPEND")==0){
printf("\nThat box was already open, try a different one.\n");
}
if (strcmp(str,"OK!")==0){
curOpen=1;
printf("\nSuccess! You are now in box: %s",arg0);
k=0;
while (k<4000){
argHolder[k]='\0';
k=k+1;
}
k=0;
while (k<strlen(arg0)){
argHolder[k]=arg0[k];
k=k+1;
}
}
strcpy(openMsg,"OPNBX");
continue;
}


if(strcmp(command,"delete")==0){
printf("\nWhich box do you want to delete?");
printf("\ndelete:>");
scanf("%s",arg0);
k=6;
i=0;
deleteMsg[5]=' ';
while (i<4000){
deleteMsg[k]=arg0[i];
k=k+1;
i=i+1;
}

send(sock,deleteMsg,sizeof(deleteMsg),0);
recv(sock,&str,sizeof(str),0);


if (strcmp(str,"ER:OPEND")==0){
printf("\nThat box is currently opened, and cannot be deleted until it is closed.\n");
}
if (strcmp(str,"ER:NEXST")==0){
printf("\nThat box does not exist.\n");
}
if (strcmp(str,"ER:NOTMT")==0){
printf("\nThat box currently has messages in it, and you can only delete an empty box.\n");
}
if (strcmp(str,"OK!")==0){
printf("\nSuccess! Deleted box:%s\n",arg0);
continue;
}
k=0;
strcpy(deleteMsg,"DELBX");
continue;
}


if (strcmp(command,"quit")==0){
send(sock,"GDBYE",sizeof("GDBYE"),0);
printf("\nClosing connection to DUMBv0...\nGoodbye!\n");
return 0;
}

if (strcmp(command,"help")==0){
printf("\n\nCommands:\nWHILE NOT INSIDE A BOX\n1)'create': Creates a new message box\n2)'open': Opens a message box\n3)'delete': Deletes an empty message box\n4)'quit': Ends connection with the terminal\n\nWHILE INSIDE A BOX:\n5)'put': Puts a new message into the box\n6)'next': Reads the next message in the box\n7)'close': Closes the currently open box");
send(sock,command,sizeof(command),0);
recv(sock,&str,sizeof(str),0);
continue;
}


send(sock,command,sizeof(command),0);
recv(sock,&str,sizeof(str),0);
printf("\nPlease use one of the following commands:\n1)'create'\n2)'open'\n3)'delete'\n4)'quit'");
continue;
}//end scanf whileLoop


        return 0;

}

