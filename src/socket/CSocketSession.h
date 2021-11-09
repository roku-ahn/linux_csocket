#pragma once

class CSocketSession {
public :
	CSocketSession();
	~CSocketSession();

protected:
	
	int m_socket;
	//int m_cli_socket;

	struct sockaddr_in m_addr;
	//sockaddr_in m_pcli_Addr;

public:
	int SendData(char* buff);
	int RecvData(char* buff, int size);


	static void  makeThread(void* data);
};

