#include "StdAfx.h"

#include "CServer.h"

bool CServer::start(const char* ip, int port){
    
  	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    int cli_socket;
    pid_t pid;
    char readBuff[MAX_BUFFER];
     char sendBuff[MAX_BUFFER];
    cout<< "make socket" << endl;
	if (m_socket == -1) {
		cout << "socket() err" << endl;        
		return false;
	}
    
    cout<< ip << endl;
    cout<< port << endl;

    m_addr.sin_family = AF_INET;           
    m_addr.sin_addr.s_addr = htonl(INADDR_ANY);    
    m_addr.sin_port=htons(port);
    
    cout<< "bind" << endl;
//bind;
    if(bind(m_socket,(struct sockaddr*) &m_addr , sizeof(m_addr) )== -1){
        cout<< "bind Err" <<endl;
        return false;
    }
    
    //listen
    cout<< "listen" << endl;
    if(listen(m_socket,5) == -1){
        cout<< "listen Err" <<endl;
        return false;
    }
    socklen_t cli_Addr_size = sizeof(sockaddr_in);
    int status;
    cout<< "accept wait" << endl;
    while(1){

        sockaddr_in client_addr, peer_addr;


        socklen_t connectSocketLength = sizeof(sockaddr_in);

         while((cli_socket = accept(m_socket, (struct sockaddr*)&client_addr, (socklen_t *)&connectSocketLength)) >= 0){
            getpeername(cli_socket, (struct sockaddr*)&peer_addr, &connectSocketLength);

            char peerName[sizeof(peer_addr.sin_addr) + 1] = { 0 };
            sprintf(peerName, "%s", inet_ntoa(peer_addr.sin_addr));
            fflush(stdin);
            // 접속이 안되었을 때는 출력 x
            if(strcmp(peerName,"0.0.0.0") != 0)
                printf("Client : %s\n", peerName);
            

 
            if (cli_socket < 0)
            {
                printf("Server: accept failed\n");
                exit(0);
            }
            // 클라이언트가 접속할 때마다 fork를 통해 child process를 생성해 echo를 발생.
            pid = fork();
 
            // 자식 서버일 때
            if(pid == 0)
            {    
                // 리스닝 소켓은 닫아준다.
                close(m_socket);
 
                ssize_t receivedBytes;
 
                // read할 값이 있다면 계속 읽어들인다.
                while((receivedBytes = read(cli_socket, readBuff, MAX_BUFFER)) > 0)
                {                
 
                    printf("%lu bytes read - %s \n", receivedBytes, peerName);
                    readBuff[receivedBytes] = '\0';
                    fputs(readBuff, stdout);
                    //fflush(stdout);
    
                    sprintf(sendBuff,"%s",readBuff);
                    fflush(stdin);
                    //write(cli_socket, sendBuff, strlen(sendBuff));

                }
                
                // 클라이언트가 종료되면 해당 자식 프로세스의 커넥팅 소켓도 종료
                close(cli_socket); 
                return 0; // 혹은 exit(0); 이용
    
            }
 
            // 부모 서버라면 커넥팅 소켓을 닫아준다. 
            else
                close(cli_socket);
         }
        
    }
   
    close(m_socket);

    return true;

}

void *CServer::makeThread(void* data)
{
    int* cs = (int*)data;
    char messageBuffer[MAX_BUFFER];
    int receiveBytes;
    
    while (receiveBytes = recv(*cs, messageBuffer, MAX_BUFFER, 0))
	{
		if (receiveBytes > 0)
		{
			printf("TRACE - Receive message : %s (%d bytes)\n", messageBuffer, receiveBytes);
			// 5-2. 데이터 쓰기
            printf("\n server : ");
            cin >> messageBuffer;
            
			int sendBytes = send(*cs, messageBuffer, strlen(messageBuffer), 0);
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
	close(*cs);
	//return;
}