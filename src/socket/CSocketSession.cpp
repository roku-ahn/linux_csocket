#include "StdAfx.h"
#include "CSocketSession.h"



CSocketSession::CSocketSession() {

	m_socket = -1;
    //m_cli_socket = -1;
    
  
	memset(&m_addr, 0,sizeof(m_addr));
    //memset(&m_pcli_Addr, 0,sizeof(m_pcli_Addr));
}

CSocketSession::~CSocketSession() {

if(m_socket != -1)
  close(m_socket);
  //close(m_cli_socket);
  
}

int CSocketSession::SendData(char* buff) {
	return send(m_socket, buff, strlen(buff), 0);
}
int CSocketSession::RecvData(char* buff, int size) {
	int len = recv(m_socket, buff, size, 0);
	buff[len] = NULL;
	return len;
}

void CSocketSession::makeThread(void* data)
{
    
	int socket = (*(int*)data);
	// 5-1. 데이터 읽기
	char messageBuffer[MAX_BUFFER];
	int receiveBytes;
	while (receiveBytes = recv(socket, messageBuffer, MAX_BUFFER, 0))
	{
		if (receiveBytes > 0)
		{
			printf("TRACE - Receive message : %s (%d bytes)\n", messageBuffer, receiveBytes);
			// 5-2. 데이터 쓰기
			int sendBytes = send(socket, messageBuffer, strlen(messageBuffer), 0);
			if (sendBytes > 0)
			{
				printf("TRACE - Send message : %s (%d bytes)\n", messageBuffer, sendBytes);
			}
		}
		else
		{
			break;
		}
	}
	
    close(socket);

	return;
    
}