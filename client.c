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

int s_port = atoi(argv[3]);
int sock = socket(AF_INET, SOCK_DGRAM, 0);
if(sock == -1)   
{
printf("Socket not created!\n"); 
exit(0); 
}
else
printf("Socket created successfully\n");

struct sockaddr_in s_ip; 
s_ip.sin_family = AF_INET;   
s_ip.sin_port = htons(s_port);   
inet_pton(AF_INET , argv[2], &s_ip.sin_addr);   

FILE *f; 
f = fopen(argv[1], "rb");   
char send_Buff[500];
int seq_Num = 0;    
char Buff[1];   
bool acks[5];   
char window[5][500];   
socklen_t ip_len = sizeof(s_ip);

int u=0;
for (u=0;u<5;u++){  
acks[u]=false;
}

while(!feof(f)) 
{
	send_Buff[0] = seq_Num;   
	fread(&sendBuff[1], sizeof(char), sizeof(sendBuff) - 1, f);   
	sendto(sock, send_Buff,sizeof(send_Buff), 0, (struct sockaddr *)&s_ip, ip_len);   
	strcpy(window[seq_Num], send_Buff);   
	if(recvfrom(sock, Buff, sizeof(Buff), 0, (struct sockaddr *)&s_ip, &ip_len) > 0)
	{
		acks[(int) Buff[0]] = true;     
		memset(&Buff, 0, sizeof(Buff));
	}
	memset(&send_Buff, 0, sizeof(send_Buff));
	seq_Num++;   

	if(seq_Num == 5)  
	{
		int i = 0;
		seq_Num = 0;
		for(i = 0; i < 5; i++)   
		{
			if(acks[i] == false)   
			{
				sleep(2);   
				if(recvfrom(sock, Buff, sizeof(Buff), 0, (struct sockaddr *)&s_ip, &ip_len) > 0)
					{
						acks[(int) Buff[0]] = true;
						memset(&Buff, 0, sizeof(Buff));
					}
				if(acks[i] == false) 
				{
					sendto(sock, window[i], sizeof(window[i]), 0, (struct sockaddr *)&s_ip, ip_len);  
					sleep(2);   
					if(recvfrom(sock, Buff, sizeof(Buff), 0, (struct sockaddr *)&s_ip, &ip_len) > 0)
						{
							acks[(int) Buff[0]] = true;
							memset(&Buff, 0, sizeof(Buff));
						}	
				}
			}
			acks[i] = false;
		}
		for(i = 0; i < 5; i++)
		{
			memset(&window[i], 0, sizeof(window[i]));
		}
	}
}
printf("\nFile is sent successfully!\n");
close(sock);    
}
