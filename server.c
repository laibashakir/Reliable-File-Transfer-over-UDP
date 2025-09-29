#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h> 
#include<stdbool.h>
#include <arpa/inet.h>

void main(int argc, char *argv[])
{

int port = atoi(argv[2]);    
struct sockaddr_in s_ip, c_ip;
int sock = socket(AF_INET, SOCK_DGRAM, 0);

if(sock == -1)    
{
printf("Socket not created\n");
exit(0); 
}
else
printf("Socket created successfully\n");

s_ip.sin_family = AF_INET;   
s_ip.sin_addr.s_addr = htonl(INADDR_ANY);  
s_ip.sin_port = htons(port);    

if(bind(sock, (struct sockaddr*)&s_ip, sizeof(s_ip))!=0)   
printf("Not Binded!\n");
else
printf("Binded!\n");

printf("The server is listening!\n");

FILE *f; 
char Buff[500];    
char send_Buff[1];
char window[5][500];  
int seq_Num = 0;    
bool order[5];

socklen_t ip_len = sizeof(c_ip);
f = fopen(argv[1], "wb");  

while(recvfrom(sock, Buff, sizeof(Buff), 0, (struct sockaddr *)&c_ip, &ip_len) > 0) 
{	
	strcpy(window[seq_Num], Buff);   
	send_Buff[0] = Buff[0];    
	sendto(sock, send_Buff, sizeof(send_Buff), 0, (struct sockaddr *)&c_ip, ip_len);   
	if(seq_Num != (int) Buff[0])   
	{
		order[seq_Num]=false;    
		memset(&Buff, 0, sizeof(Buff));
	}
	else{
		order[seq_Num]=true;   
		fwrite(&Buff[1], sizeof(char), sizeof(Buff) - 1, f); 
		memset(&Buff, 0, sizeof(Buff));
	}
	seq_Num++;  
	if(seq_Num == 5)   
	{
		seq_Num = 0;   
		int n=0;
		for(n=0;n<5;n++){
		if (order[n]==false){   
			fwrite(&window[n], sizeof(char), sizeof(Buff) - 1, f); 
		}
		}
	}
}
fclose(f);   
printf("\nFile is successfully received!");
}
