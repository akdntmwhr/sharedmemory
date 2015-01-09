int makeTcpSocket();
void removeTimeWaitState(int s);
void connectTcpClientSocket(int s, char * ip, int port);
void bindTcpServerSocket(int s, int port);
void listenTcpServerSocket(int s);
int acceptTcpServerSocket(int s);
int sendMessage(int s, char *message,int length);
int receiveMessage(int s, char *message, int length);
void closeTcpSocket(int s);
