#include <iostream>
#include <stdexcept>
#include <cstring>
#include <memory>
#include <cerrno>
extern "C"
{
  #include <arpa/inet.h>
  #include <netinet/in.h>
  #include <netinet/ip.h>
  #include <sys/types.h>         
  #include <sys/socket.h>
  #include <unistd.h>
  #include <signal.h>
  #include <sys/wait.h>
}

using namespace std;

void sigHandler(int );

int main(int argc, char* argv[]) {
  if(argc != 3) {
    throw runtime_error("argc error");
  }
  struct sigaction act;
  act.sa_flags = 0;
  act.sa_handler = sigHandler;
  sigemptyset(&act.sa_mask);
  if(sigaction(SIGCHLD, &act, nullptr) == -1) {
    cout << strerror(errno) << endl;
    exit(1);
  }

  int sock = 0;
  if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    cout << strerror(errno) << endl;
    throw runtime_error("socket error");
  }

  int option;
  socklen_t optionlen = sizeof(option);
  option = true;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void*)&option, optionlen);

  unique_ptr<struct sockaddr_in> sockAddr(make_unique<struct sockaddr_in>()), 
    clientAddr;
  sockAddr->sin_family = AF_INET;
  if(!inet_aton(argv[1], &(sockAddr->sin_addr))) {
    cout << strerror(errno) << endl;
    throw runtime_error("inet_aton error");
  }
  sockAddr->sin_port = static_cast<in_port_t>(htons(atoi(argv[2])));
  socklen_t sockLen = sizeof(*sockAddr);

  if(bind(sock, reinterpret_cast<sockaddr *>(sockAddr.get()), sockLen)) {
    cout << strerror(errno) << endl;
    throw runtime_error("bind error");
  }

  if(listen(sock, 5)) {
    cout << strerror(errno) << endl;
    throw runtime_error("listen error");
  }

  unique_ptr<socklen_t> clientAddrlen(make_unique<socklen_t>(sizeof(clientAddr.get())));
  while(1) {
    int clientSock = accept(sock, reinterpret_cast<sockaddr *>(clientAddr.get()), clientAddrlen.get());
    if(clientSock == -1) {
      continue;
    }
    pid_t child = fork();
    if(child == 0) {
      close(sock);
      cout << "enter child process" << endl;
      char buf[80];
      memset(buf, 0, 80);
      size_t num = 0;
      num = read(clientSock, buf, 79);
      if (num == -1) {
        cout << strerror(errno) << "Read " << endl;
        close(clientSock);
        return 0;
      }
      buf[num] = '\0';
      cout << buf << endl;
      write(clientSock, buf, strlen(buf));
      close(clientSock);
      return 0;
    } else {
      close(clientSock);
    }

  }

  close(sock);
  return 0;
}

void sigHandler(int signum ){
  cout << signum << endl;
  int statu;
  auto pid = waitpid(-1, &statu, 0);
  if(WIFEXITED(statu)) {
    cout <<  WEXITSTATUS(statu) << " " << pid << endl;
  }
}