#include "StdAfx.h"
#include "CClient.h"

void CClient::Connect(const char* ip, int port) {

	m_addr.sin_family = AF_INET;
	inet_aton(ip,(struct in_addr*)m_addr.sin_addr.s_addr);
	m_addr.sin_port = htons(port);
	

	m_socket = socket(AF_INET,SOCK_STREAM,0);

	if (connect(m_socket, (struct sockaddr*)&m_addr, sizeof(m_socket)) == -1) {
		cerr << "connect Err" << endl;		
		exit(1);
	}
	else{
		  
		int readBytes, writtenBytes;
        char sendBuffer[MAX_BUFFER];
        char receiveBuffer[MAX_BUFFER];
		
		while (1) 
        {
            //서버에 문자열을 보낸 뒤 서버가 보낸 echo를 받아 출력.
            printf("서버에 보낼 말을 입력하세요 :: ");
 
            fgets(sendBuffer,MAX_BUFFER,stdin);
 
            write(m_socket, sendBuffer, strlen(sendBuffer));
            
            readBytes = read(m_socket, receiveBuffer, MAX_BUFFER);
            printf("%d bytes read\n", readBytes);
            receiveBuffer[readBytes] = '\0';
            fputs(receiveBuffer, stdout);
            fflush(stdout);
 
        }
		close(m_socket);
	}
}