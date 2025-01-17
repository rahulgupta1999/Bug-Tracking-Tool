// server code for UDP socket programming 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 

#define IP_PROTOCOL 0 
#define PORT_NO 15050 
#define NET_BUF_SIZE 2048
#define cipherKey 'S' 
#define sendrecvflag 0 
#define nofile "File Not Found!" 


// function to clear buffer 
void clearBuf(char* b) 
{ 
	int i; 
	for (i = 0; i < NET_BUF_SIZE; i++) 
		b[i] = '\0'; 
} 
// function to encrypt 
char Cipher(char ch) 
{ 
	return ch ^ cipherKey; 
} 
// function sending file 
int sendFile(FILE* fp, char* buf, int s) 
{ 
	int i, len; 
	if (fp == NULL) { 
		strcpy(buf, nofile); 
		len = strlen(nofile); 
		buf[len] = EOF; 
		for (i = 0; i <= len; i++) 
			buf[i] = Cipher(buf[i]); 
		return 1; 
	} 
	char ch, ch2; 
	for (i = 0; i < s; i++) { 
		ch = fgetc(fp); 
		ch2 = Cipher(ch); 
		buf[i] = ch2; 
		if (ch == EOF) 
			return 1; 
	} 
	return 0; 
} 
// driver code 
int main() 
{ 
	int sockfd, nBytes, idBytes,bugIdBytes; 
	struct sockaddr_in addr_con; 
	int addrlen = sizeof(addr_con); 
	addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(PORT_NO); 
	addr_con.sin_addr.s_addr = INADDR_ANY; 
	char net_buf[NET_BUF_SIZE]; 
	char id[20];
	char bugId[10];
	FILE* fp,*fp1; 
	// socket() 
	sockfd = socket(AF_INET, SOCK_DGRAM, IP_PROTOCOL); 
	if (sockfd < 0) 
		printf("\nConnection issue\n"); 
	// bind() 
	bind(sockfd, (struct sockaddr*)&addr_con, sizeof(addr_con));
		printf("\nWelcome to the bug tracker\n"); 
		while(1){ 
			clearBuf(id);
		idBytes = recvfrom(sockfd, id, 
						sizeof(id), sendrecvflag, 
						(struct sockaddr*)&addr_con, &addrlen);

		printf("%s",id);	
		clearBuf(net_buf); 


		if(id[0]=='T'){

			clearBuf(net_buf); 

			nBytes = recvfrom(sockfd, net_buf, 
							NET_BUF_SIZE, sendrecvflag, 
							(struct sockaddr*)&addr_con, &addrlen);
			if(net_buf[0]=='n' && net_buf[1]=='u' && net_buf[2]=='l' && net_buf[3]=='l'){
				char var[100];
				// process
				fp=fopen("bugs.txt","r"); 
				fp1=fopen("temp.txt","w");
				while(fgets(var, sizeof(var), fp)!=NULL){
						if(strstr(var,id)){
						fprintf(fp1,"%s",var);}
				}
				fclose(fp1);

				fp1=fopen("temp.txt","r");
					if (sendFile(fp1, net_buf, NET_BUF_SIZE)) { 
						sendto(sockfd, net_buf, NET_BUF_SIZE, 
							sendrecvflag,  
							(struct sockaddr*)&addr_con, addrlen); 
					} 
				// send 
					sendto(sockfd, net_buf, NET_BUF_SIZE, 
						sendrecvflag, 
						(struct sockaddr*)&addr_con, addrlen); 
					clearBuf(net_buf);
				fclose(fp);
				fclose(fp1);
			printf("\nBugs details sent\n");	
			clearBuf(id);	
			}
			else{			
				printf("\nBug details Received: %s\n", net_buf);
				fp=fopen("bugs.txt","a");
				fprintf(fp,"%s",net_buf);
				fprintf(fp,"%s","\n");
				fclose(fp);
				printf("\nBug added to the database\n"); 
				clearBuf(id);
			}
		}
		else if(id[0]=='P'){
			clearBuf(net_buf); 

			nBytes = recvfrom(sockfd, net_buf, 
							NET_BUF_SIZE, sendrecvflag, 
							(struct sockaddr*)&addr_con, &addrlen);
			if(net_buf[0]=='n' && net_buf[1]=='u' && net_buf[2]=='l' && net_buf[3]=='l'){
				// process
				fp1=fopen("bugs.txt","r");
					if (sendFile(fp1, net_buf, NET_BUF_SIZE)) { 
						sendto(sockfd, net_buf, NET_BUF_SIZE, 
							sendrecvflag,  
							(struct sockaddr*)&addr_con, addrlen); 
					} 
				// send 
					sendto(sockfd, net_buf, NET_BUF_SIZE, 
						sendrecvflag, 
						(struct sockaddr*)&addr_con, addrlen); 
					clearBuf(net_buf);
				fclose(fp);
				fclose(fp1);
			printf("\nBugs details sent\n");	
			clearBuf(id);	
			}
		}
		else{
			clearBuf(net_buf); 

			nBytes = recvfrom(sockfd, net_buf, 
							NET_BUF_SIZE, sendrecvflag, 
							(struct sockaddr*)&addr_con, &addrlen);
			if(net_buf[0]=='n' && net_buf[1]=='u' && net_buf[2]=='l' && net_buf[3]=='l'){
				char var[100];
				// process
				fp=fopen("bugs.txt","r"); 
				fp1=fopen("temp.txt","w");
				while(fgets(var, sizeof(var), fp)!=NULL){
						if(strstr(var,id)){
						fprintf(fp1,"%s",var);}
				}
				fclose(fp1);

				fp1=fopen("temp.txt","r");
					if (sendFile(fp1, net_buf, NET_BUF_SIZE)) { 
						sendto(sockfd, net_buf, NET_BUF_SIZE, 
							sendrecvflag,  
							(struct sockaddr*)&addr_con, addrlen); 
					} 
				// send 
					sendto(sockfd, net_buf, NET_BUF_SIZE, 
						sendrecvflag, 
						(struct sockaddr*)&addr_con, addrlen); 
					clearBuf(net_buf);
				fclose(fp);
				fclose(fp1);
			printf("\nBugs details sent\n");	
			clearBuf(id);	
			}
			else{
				
			}
		}
 }
        	return 0; 

} 

