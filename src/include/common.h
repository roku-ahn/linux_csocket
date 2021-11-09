#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


using namespace std;

#define MAX_BUFFER        1024
#define SERVER_PORT        3500
enum TYPE { ServerMode, ClientMode, Quit };


