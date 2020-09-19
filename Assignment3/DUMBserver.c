#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<string.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
char holdGuy[4000];
char command[4000]="hiya";
char response[10]="yo";
char what[10]="ER:WHAT?";
char conn[20] = "connected";
char hello[20] = "HELLO";
char gdbye[20] = "GDBYE";
char disc[20] = "disconnected";
char opnbx[20] = "OPNBX";
//char nexst[20] = "NEXST";
char clsbx[20] = "CLSBX";
char creat[20] = "CREAT";
char nxtmg[20] = "NXTMG";
char putmg[20] = "PUTMG";
char delbx[20] = "DELBX";
char erexist[10]="ER:EXIST";
char opend[10]="ER:OPEND";
char notmt[10]="ER:NOTMT";
char nexst[10]="ER:NEXST";
char tryAgain[10]="TRYAGAIN";
char ok[4000]="OK!";
char** boxNames;
char*** messages;
int init=0;
int openBool[1000];
int curBox=-1;
int q=0;
int p=0;
int numBoxes=10;
int nameLen=25;
int numMsg=25;
int msgLen=4000;
int msgCount=0;
int gay=0;
char strGay[12];

void serverPrint(int sock, char* str){
	struct sockaddr_in addr;
	socklen_t addr_size = sizeof(struct sockaddr_in);
	getpeername(sock, (struct sockaddr_in *)&addr, &addr_size);
	char* clientip[20];
	strcpy(clientip, inet_ntoa(addr.sin_addr));
	char timebuf[12];
	time_t now = time(NULL);
	struct tm *tm = localtime(&now);
	strftime(timebuf, 12, "%H%M %d %b", tm);
	printf("%s ", timebuf);
	printf("%s ", clientip);
	printf("%s\n", str);


}

void *servThread(void* args) 
{ 
if (init==0){
boxNames=malloc(numBoxes*sizeof(char*));
while(p<numBoxes){
boxNames[p]=malloc(nameLen*sizeof(char));
p=p+1;
}
p=0;
messages=malloc(numBoxes*sizeof(char**));
while (p<numBoxes){
messages[p]=malloc(numMsg*sizeof(char*));
q=0;
while(q<numMsg){
messages[p][q]=malloc(msgLen*sizeof(char));
q=q+1;
}
p=p+1;
}
init=1;
}

int clientSock=*((int*)args);
int i=0;
int k=0;
char *arg=malloc(5*sizeof(char));
char *arg0=malloc(nameLen*sizeof(char));
char *arg1=malloc(msgLen*sizeof(char));
recv(clientSock, &command, sizeof(command), 0);
while (1){
//serverPrint(clientSock, tryAgain);
i=0;
while(i<5){
arg[i]='\0';
i=i+1;
}
i=0;
while(i<nameLen){
arg0[i]='\0';
i=i+1;
}
i=0;
while(i<msgLen){
arg1[i]='\0';
i=i+1;
}
i=0;
k=0;
while (i<5){
arg[i]=command[i];
i=i+1;
}

if (command[5]==' '){
i=i+1;
while (i<(nameLen+5)){
arg0[k]=command[i];
k=k+1;
i=i+1;
}
}//end if space

if (command[5]=='!'){
i=i+1;
while (1){
if (command[i]=='!'){
i=i+1;
break;
}
arg0[k]=command[i];
i=i+1;
k=k+1;
}
k=0;
while (i<strlen(command)){
arg1[k]=command[i];
k=k+1;
i=i+1;
}

}//end if !



k=0;
i=0;
if(strcmp(arg,"CREAT")==0){
if (strlen(command)>31||strlen(command)<11){
serverPrint(clientSock, what);
send(clientSock,what,sizeof(what),0);
recv(clientSock,&command,sizeof(command),0);

continue;
}

if (isalpha(arg0[0])==0){
serverPrint(clientSock, what);
send(clientSock,what,sizeof(what),0);
recv(clientSock,&command,sizeof(command),0);
continue;
}

i=0;
while (i<numBoxes){
if (strcmp(boxNames[i],arg0)==0){
serverPrint(clientSock, erexist);
send(clientSock,erexist,sizeof(erexist),0);
recv(clientSock,&command,sizeof(command),0);
i=1001;
continue;
}
if (strlen(boxNames[i])==0){
k=0;
while (k<nameLen){
boxNames[i][k]=arg0[k];
k=k+1;
}
serverPrint(clientSock, creat);
send(clientSock,ok,sizeof(ok),0);
recv(clientSock,&command,sizeof(command),0);
i=1001;
continue;
}
i=i+1;
}
if (i==1001){
continue;
}
//boxes are full
serverPrint(clientSock, what);
send(clientSock,what,sizeof(what),0);
recv(clientSock,&command,sizeof(command),0);
continue;
}


if(strcmp(arg,"OPNBX")==0){
i=0;


while (i<numBoxes){
if (strcmp(boxNames[i],arg0)==0){
if (openBool[i]==1){
serverPrint(clientSock, opend);
send(clientSock,opend,sizeof(opend),0);
recv(clientSock,&command,sizeof(command),0);
i=1001;
continue;
}
openBool[i]=1;
curBox=i;
k=0;
while (k<numMsg){
if (strcmp(messages[i][k],"")!=0){
msgCount=msgCount+1;
}
k=k+1;
}
serverPrint(clientSock, opnbx);
send(clientSock,ok,sizeof(ok),0);
recv(clientSock,&command,sizeof(command),0);
i=1001;
continue;
}
i=i+1;
}
if (i==1001){
continue;
}
serverPrint(clientSock, nexst);
send(clientSock,nexst,sizeof(nexst),0);
recv(clientSock,&command,sizeof(command),0);
continue;
}



if(strcmp(arg,"DELBX")==0){
i=0;
k=0;
while (i<numBoxes){
if (strcmp(arg0,boxNames[i])==0){
if(openBool[i]==1){
serverPrint(clientSock, opend);
send(clientSock,opend,sizeof(opend),0);
recv(clientSock,&command,sizeof(command),0);
i=1001;
continue;
}
if (strlen(messages[i][0])==0){
k=0;
while (k<nameLen){
boxNames[i][k]='\0';
k=k+1;
}
i=1001;
serverPrint(clientSock, delbx);
send(clientSock,ok,sizeof(ok),0);
recv(clientSock,&command,sizeof(command),0);
continue;
}
serverPrint(clientSock, notmt);
send(clientSock,notmt,sizeof(notmt),0);
recv(clientSock,&command,sizeof(command),0);
i=1001;
continue;
}
i=i+1;
}//end while

if (i==numBoxes){
serverPrint(clientSock, nexst);
send(clientSock,nexst,sizeof(nexst),0);
recv(clientSock,&command,sizeof(command),0);
continue;
}
continue;
}


if(strcmp(arg,"CLSBX")==0){
openBool[curBox]=0;
curBox=-1;
msgCount=0;
serverPrint(clientSock, clsbx);
send(clientSock,ok,sizeof(ok),0);
recv(clientSock,&command,sizeof(command),0);
continue;
}

if(strcmp(arg,"NXTMG")==0){
strcat(holdGuy,messages[curBox][0]);
gay=strlen(holdGuy);
sprintf(strGay,"%d",gay);
strcat(ok,strGay);
strcat(ok,"!");
strcat(ok,holdGuy);

k=0;
while(k<msgCount){
strcpy(messages[curBox][k],"");
strcat(messages[curBox][k],messages[curBox][k+1]);
k=k+1;
}
msgCount=msgCount-1;
k=0;
serverPrint(clientSock, nxtmg);
send(clientSock,ok,sizeof(ok),0);
recv(clientSock,&command,sizeof(command),0);
strcpy(holdGuy,"");
strcpy(ok,"OK!");
continue;
}


if(strcmp(arg,"PUTMG")==0){
strcat(ok,arg0);
if (strlen(arg1)>msgLen){
serverPrint(clientSock, what);
send(clientSock,what,sizeof(what),0);
recv(clientSock,&command,sizeof(command),0);
strcpy(ok,"OK!");
continue;
}
strcat(messages[curBox][msgCount],arg1);
msgCount=msgCount+1;
serverPrint(clientSock, putmg);
send(clientSock,ok,sizeof(ok),0);
recv(clientSock,&command,sizeof(command),0);
strcpy(ok,"OK!");
continue;
}



if (strcmp(arg,"GDBYE")==0){
printf("closing socket:%d",clientSock);
sleep(1);
serverPrint(clientSock, disc);
close(clientSock);
pthread_exit(NULL);
return 0;
}
serverPrint(clientSock, what);
send(clientSock,what,sizeof(what),0);
recv(clientSock, &command, sizeof(command), 0);
}

    return NULL; 
} 






int main(int argc, char** argv){


int servSock;
servSock = (socket(AF_INET, SOCK_STREAM, 0));
struct sockaddr_in servAddr;
struct sockaddr_storage serverStorage;
socklen_t addr_size;
servAddr.sin_family = AF_INET;
servAddr.sin_port = htons(atoi(argv[1]));
servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
bind(servSock, (struct sockaddr*) &servAddr, sizeof(servAddr));

int clientSock;
listen(servSock, 50);
pthread_t tid[60];
int i=0;


while (1){
addr_size=sizeof serverStorage;
clientSock = accept(servSock,(struct sockaddr*) &serverStorage, &addr_size);
serverPrint(clientSock, conn);
pthread_create(&tid[i], NULL, servThread,&clientSock);



}   

}






