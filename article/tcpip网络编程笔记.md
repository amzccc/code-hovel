[TOC]

# 1 网络编程和套接字  
> 网络编程就是编写程序使两台联网的计算机可以相互交换数据。套接字（socket）是网络数据传输用的软件设备

## 1 套接字(socket)
1. 创建socket:调用socket函数（安装电话机）
``` c++
#include <sys/socket.h>
int socket (int domain, int type, int protocol);    //domain: 套接字中使用的协议族信息  
                                        //type：数据传输类型
                                        //protocol: 计算机间通信中使用的协议信息
//使用socket函数创建一个整型变量
int sv_or_clnt_sock = socket(PF_INET, SOCK_STREAM, 0);  //需要包含<arpa/iniet.h>
```
2. 调用bind函数（分配电话号码）
意思是分配IP地址和端口号
``` c++
#include <sys/socket.h>
int bind (int sockfd, struct sockaddr* myaddr, socklen_t addrlen);
//sockfd是上述socket创建的文件描述符（pid），第二参数是装有地址的结构体，第三参数是该结构体的长度
```
这样等于电话线就装好了，其他人可以打电话请求连接到该机，需要把套接字转换为可接听状态
3. 调用listen函数，转换为接听状态
``` c++
#include <sys/socket.h>
int listen (int sockfd, int backlog);
```
4. 调用accept函数，拿起话筒进行对话
``` c++
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen);
```
客户端的socket，也就是打电话请求连接的过程只有创建socket和连接两个步骤。
``` c++
#include <sys/socket.h>
int socket (int domain, int type, int protocol);
int connect(int sockfd, struct sockaddr* serv_addr, socklen_t addrlen);
```

# 2 socket类型和协议设置
1. 协议族
> PF_INET       IPv4互联网协议族
> PF_INET6      IPv6互联网协议族
> PF_LOCAL      本地通信的Unix协议族
> PF_PACKET     底层套接字的协议族
> PF_IPX        IPX Novell协议族
套接字中实际采用的最终协议信息是通过第三个参数传递的，在指定的协议族范围内通过第一个参数决定第三个参数。  
2. 套接字类型
套接字类型决定创建的套接字的数据传输方式。  
* 1 面向连接的套接字（SOCK_STREAM）
>面向连接的套接字特点：传输过程中数据不会消失；按序传输数据；传输的数据不存在数据边界

* 2 面向消息的套接字（SOCK_DGRAM）
>强调快速传输而非传输顺序；传输的数据可能丢失和损毁；传输的数据有数据边界；限制每次传输的数据大小

3. 协议的最终选择
一般通过前面的协议族信息和套接字数据传输方式决定了采用的协议，第三个参数传递0就足够，但是存在在同一协议族中存在多个数据传输方式相同的协议，这时需要第三个参数指定具体的协议信息。  
>e.g. int tcp_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
创建了IPv4的协议族，采用面向连接的数据传输方式，满足这连个条件的协议只有IPPROTO_TCP，所以第三个参数传递这个协议

# 3 地址族与数据序列
## 1 IP地址和端口号
IP是为收发网络数据而分配给计算机的值。端口号并非赋予计算机的值，而是为了区分程序中创建的套接字而分配给套接字的序号。
**网络地址**
网络地址是为区分网络而设置的一部分IP地址。向目标主机传输数据时，并非直接浏览所有4字节IP地址，找到目标主机，而是仅浏览4字节的IP地址的网络地址，先把数据传到该网络中，然后路由器接收到数据后，浏览传输数据的主机地址并将数据传给目标主机。
A类地址的首字节范围：0~127
B类地址的首字节范围：128~191
C类地址的首字节范围：192~223

**端口号**
仅有IP地址可以找到目标主机，但是无法区分主机上的应用程序，所以需要端口号来区分。*端口号就是在同一个操作系统中区分不同套接字而设置的，因此1个端口号不能分配给不同的套接字*
==端口号由16位构成，可分配的端口号范围是0到65535，但0到1023是知名端口，一般分配给特定应用程序，所以应当分配此范围之外的值==
>另外，虽然端口号不能重复，但TCP和UDP不会共用端口号，所以允许重复。

## 2 地址信息的表示
采用如下结构体来表示地址信息
``` c++
struct sockaddr_in {
    sa_family_t     sin_family;     //地址族
    uint16_t        sin_port;       //16位tcp/udp端口号
    struct in_addr  sin_addr;       //32位IP地址
    char            sin_zero[8];    //不使用，只是为了与sockaddr保持一致，必须填0
}; //该结构体中涉及另一结构体in_addr,用来存放32位IP地址
struct in_addr {
    In_addr_t       s_addr;     //32位IPv4地址
}
```
**sin_family**
变量|含义
--|--
AF_INET |IPv4网络协议中使用的地址族
AF_INET6|IPv6网络协议中使用的地址族
AF_LOCAL|本地通信中采用的Unix协议的地址族

sockaddr_in结构体变量地址通过bind函数传递给sockaddr
``` c++
struct sockaddr_in serc_addr;       //这是存放服务器的socket的变量
······
if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
    error_handling("bind() error");
······
```
bind函数第二个参数期望得到sockaddr的地址族、端口号、IP地址等，但直接向sockaddr填充这些信息会带来麻烦，因为sockaddr结构体是下面这种形式。
``` c++
struct sockaddr {
    sa_family_t sin_family;     //地址族
    char        sa_data[14];    //地址信息
}
```
结构体成员sa_data保存的地址信息包括ip地址和端口号，剩余部分填充0，这也是bind函数要求的，但这对于包含地址信息来讲非常麻烦，所以有了新的结构体sockaddr_in。按照要求填充sockaddr_in结构体内容，然后转换为sockaddr型再传递给bind函数，更加清晰。
## 3 网络字节序和地址变换
CPU保存和处理数据有两种方式，大端序和小端序。大端序从最高位向最低位保存和处理数据；小端序是先保存最低位，再依次向最高位保存  
>e.g.  0x12345678在32位CPU中保存为
>大端序 0x12 0x34 0x56 0x78
>小端序 0x78 0x56 0x34 0x12
主流intel和AMD的cpu以小端序方式保存数据。
在进行网络传输数据时，约定采用统一的方式大端序进行传输，这种约定称为网络字节序。
**字节序转换**
利用htons函数进行转换，理解函数名称含义：h代表主机字节序，n代表网络字节序，s表示short型。因此，htons可理解为“把short型数据从主机字节序转换为网络字节序”。另有ntohs可类似理解。

## 4 网络地址的初始化和分配
**字符串信息转换为网络字节序的整型**
对于IP地址，常用点分十进制表示，在存储时需要转换为32位整型存储，可利用inet_addr函数转换，它会将字符串形式的ip地址转换为32位整型，并同时进行网络字节序转换。
``` c++
#include <arpa/inet.h>
in_addr_t inet_addr(const char* string);
```
inet_aton函数和inet_addr函数功能相同，只不过该函数利用了in_addr结构体，使用频率更高。
``` c++
#include <arpa/inet.h>
int inet_aton(const char* string, struct in_addr* addr);
```
在实际使用中，如果调用inet_addr函数，还需要将转换后的IP地址信息代入sockaddr_in声明的in_addr结构体中，而inet_aton不需要此过程，因为在传递in_addr结构体变量地址时，函数自动将结果写入了。
```c++
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
int main(int argc, char* argv[])
{
    char* addr = "127.232.124.79";
    struct sockaddr_in addr_inet;
    inet_aton(addr, &addr_inet.sin_addr);
    return 0;
}
```

**网络初始化**
```c++
struct sockaddr_in addr;        //声明存储服务器网络信息的变量
char* serv_ip = "211.217.168.13";        //声明IP地址字符串
char* serv_port = "9190";       //声明端口号字符串
memset(&addr, 0, sizeof(addr));     //addr中所有成员初始化为0
addr.sin_family = AF_INET;          //指定地址族
addr.sin_addr.s_addr = inet_addr(serv_ip);      //初始化ip地址
addr.sin_port = htons(atoi(serv_port));     //初始化端口
```
客户端与服务器端初始化不同。服务器端声明addr_in，将其初始化为服务器的ip地址和socket的端口号，然后调用bind函数绑定到socket创建的文件描述符（PID）；而客户端则是将addr_in初始化为要连接的服务器的ip地址和端口号，然后调用connect函数进行连接。

==INADDR_ANY==关键字
每次创建服务器的socket时都要输入ip地址会非常麻烦，可利用INADDR_ANY自动获取服务器端的ip地址。
``` c++
struct sockaddr_in addr;
char* serv_port = "9190";
memset(&addr, 0, sizeof(addr));
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = inet_addr(INADDR_ANY);
addr.sin_port = htons(atoi(serv_port));
```

# 实现基于TCP的服务器端/客户端
### TCP服务器端的默认函数调用顺序
先创建套接字，然后分配套接字地址，然后等待连接请求状态，然后允许连接，进行数据交换，最后断开连接。
==socke() -> bind() -> listen() -> accept() -> read()/write() -> close()==
socket函数和bind函数如上面所述，绑定了地址后，就需要调用listen才能进入等待连接请求的状态，也就是说，只有在服务器listen之后，客户端才能够进行connect。
``` c++
#include <sys/socket.h>
int listen(int sock, int backlog);      //成功返回0，失败返回-1
```
sock是套接字的文件描述符，backlog表示连接请求等待队列的长度，假设为5，表示最后使5个连接请求进入队列。

在调用listen函数后，若有连接请求，服务器端就该按序受理。请求受理后需要创建一个新的套接字与客户端进行数据交换，但好在无需自己创建，accept函数调用时会自动创建一个socket与客户端连接。
``` c++
#include <sys/socket.h>
int accept(int sock, struct sockaddr* addr, socklen_t* addrlen);
//成功时返回创建的套接字文件描述符，失败时返回-1。
```
函数中sock是服务器的套接字文件描述符，
addr保存客户端地址信息，
addrlen表示addr的长度，调用函数后被填入客户端的地址长度

最后，服务器端向客户端读取或写入内容，然后关闭客户端和服务端的套接字
``` c++
write(int clnt_sock, char* message, sizeof(message));
close(clnt_sock);
close(serv_sock);
```

### TCP客户端的默认函数调用
==socket() -> connect() -> read()/write() -> close()==
服务器端在listen之后，客户端就可以进行connect请求连接
``` c++
#include <sys/socket.h>
int connect(int sock, struct sockaddr* servaddr, socklen_t addrlen);
```
connect函数在下面两种情况下才会返回：
1. 服务器接收连接请求
2. 发生断网等异常情况而中断连接请求

客户端在调用connect时，会自动读取和分配客户端的ip地址和端口号，一般无需调用bind函数分配。
**TCP的服务器端和客户端函数调用关系**
![image](./Pictures/tcp.png)

### Windows下的socket函数
win下的函数名和参数名和Linux下相同，但返回值稍有不同
``` c++
#include <winsock2.h>
SOCKET socket(int af, int type, int protocol);
int bind(SOCKET s, const struct sockaddr* name, int namelen);
int listen(SOCKET s, int backlog);
SOCKET accept(SOCKET s, struct sockaddr* addr, int* addrlen);
int connect(SOCKET s, const struct sockaddr* name, int namelen);
int closesocket(SOCKET s);      //win系统下有专门关闭套接字的函数
int send(SOCKET s, const char* buf, int len, int flags);
int recv(SOCKET s, const char* buf, int len, int flags); //win下用recv和send函数执行收发信息的工作
```
#### Winsock的初始化
进行Winsock编程时，必须调用WSAStartup函数，设置程序用的Winsock版本，并初始化相应版本的库。
``` c++
#include <winsock2.h>
int WASStartup(WORD wVersionRequested, LPWSADATA lpWSAData);
//第一个参数是要用到的Winsock版本信息
//第二个参数是WSADATA结构体变量的地址值
//例如
WSADATA wsaData;
WSAStartup(MAKEWORD(2, 2), &wsaData);

int WSACleanup(void);       //socket程序结束后，注销库
```
将Linux平台下示例转换成Windows平台示例需要注意以下4点：
1. 通过WSAStartup、WSACleanup函数初始化和清除套接字相关库
2. 数据类型和变量名切换为Windows风格
3. 数据传输中用recv、send代替read、write
4. 关闭套接字时用closesocket代替close

# TCP原理
## TCP套接字中的I/O缓冲
write函数调用后并非立即传输数据，read函数调用后也并非立即接收数据。write调用瞬间，数据将移至输出缓冲；read函数调用瞬间，从输入缓冲读取数据。
![tcp套接字io缓冲](./Pictures/tcpio缓冲.png)

缓冲特性如下：
* I/O缓冲在每个TCP套接字中独立存在
* I/O缓冲在创建套接字时自动生成
* 即使关闭套接字也会继续传递输出缓冲中遗留的数据
* 关闭套接字将丢失输入缓冲中的数据

## TCP内部工作原理
### 1 与对方套接字的连接
TCP套接字从创建到消失分为3步：
* 与对方套接字建立连接
* 与对方套接字进行数据交换
* 断开与对方套接字的连接

建立连接过程：TCP在实际通信中会经过3次类似对话过程，又称为三次握手。
套接字以全双工方式工作，即可以双向传递数据。收发数据前需要做一些准备：
首先，*请求连接的主机A向主机B传递如下信息*：
==[SYN] SEQ: 1000, ACK: -==
消息中SEQ为1000，含义是“现在传递的数据包序号是1000，如果接收无误，请通知我向您传递1001号数据包”。ACK为空
这是首次请求连接时使用的信息，又称为SYN，表示收发数据前传输的同步消息。
*然后主机B向A传递消息*：
==[SYN+ACK] SEQ: 2000, ACK: 1001==
SEQ的含义是“现在传递的数据包序号为2000，如果接收无误，请通知我向您传递2001号数据包”。ACK1001的含义是“刚才传输的SEQ为1000的数据包接收无误，现在请传递SEQ为1001的数据包”。
对主机A首次传输的数据包的确认信息（ACK 1001）和为主机B传输数据做准备的同步信息（SEQ 2000）捆绑发送，因此这种类型消息又称SYN+ACK。
收发数据前向数据包分配序号，并向对方通报此序号，都是为了防止数据丢失做的准备。通过向数据包分配序号并确认，可以在数据丢失时马上查看并重传丢失的数据包。
*最后主机A向B传输消息*：
==[ACK] SEQ: 1001, ACK: 2001==
含义是“已正确收到传输的SEQ为2000的数据包，现在可以传输SEQ为2001的数据包”。
这样，主机A和主机B就确认了彼此都已准备就绪了。

### 2 与对方主机的数据交换
![数据交换](./Pictures/tcp数据交换.png)

### 3 断开与套接字的连接
套接字A要断开连接时，先向B传递断开连接的消息，然后B发出确认收到的信息，然后向A传递可以断开连接的消息，A再同样发出确认消息。也就是说，双方各发送依次FIN消息后断开连接。
这个过程经历4个阶段，所以又称四次握手。
![断开连接](./Pictures/tcp断开连接.png)

# UDP
udp是一种不可靠的数据传输协议，但在结构上比tcp更加简洁，因为不需要发送类似ACK确认消息和不会像SEQ那样给数据包编号，所以性能有时比tcp高很多。
**为了提供可靠的数据传输服务，TCP和不可靠的IP层进行流控制，而UDP就缺少这种流控制机制**
TCP慢于UDP的两点原因：
> * 收发数据前后进行的连接设置及清除过程
> * 收发数据过程中为保证可靠性而添加的流控制


## 基于UDP的服务器端/客户端
UDP没有无需经过连接过程，就是说不调用listen和accept函数，只有创建套接字的过程和数据交换的过程。
UDP中不管是服务器端还是客户端都只需要1个套接字，而在tco中为了保证一一对应的关系，需要多个套接。例如，tcp要向10个客户端提供服务，除了一开始创建的守门的服务器套接字外，还需要创建10个服务器端套接字。

### I/O函数
由于UDP套接字不会一直保持连接状态，因此每次传输数据都要添加目标地址信息。
``` c++
#include <sys/socket.h>
ssize_t sendto(in sock, void* buff, size_t nbytes, int flags, struct sockaddr* to, socklen_t addrlen);

ssize_t recvfrom(int sock, void* buff, size_t nbytes, int flags, struct sockaddr* from, socklen_t* addrlen);
```
buff保存待收发数据的缓冲地址值，nbytes表示待收发数据的长度，以字节为单位，flags为可选项，没有就设置为0。

### UDP客户端的地址分配
UDP中，调用sendto函数传输数据前应完成对套接字的地址分配，因此调用bind函数。如果调用sendto函数时尚未分配地址信息，则在首次调用sendto函数时给相应的套接字自动分配ip和端口，并一直保留到程序结束为止。
综上，调用sendto函数时会自动分配ip和端口号，因此在UDP客户端中通常无需额外的分配地址过程，这也是普遍的实现方式。

### UDP的数据传输特性和connect函数调用
#### UDP套接字存在数据边界
tcp数据传输不存在边界，意思是“tcp数据传输过程中调用i/o函数的次数不具有任何意义。”
但在UDP协议中，调用i/o函数的次数是非常重要的，因此，输入函数的调用次数应和输出函数的调用次数完全一致，这样才能保证接收所有已发送的数据。

#### 已连接的UDP套接字和未连接的UDP套接字
在TCP套接字中需要注册待传输数据的目标IP和端口号，但在UDP中无需注册，因此，通过sendto函数传输数据的过程可分为3个阶段：**第一阶段，向UDP套接字注册目标IP和端口号；第二阶段，传输数据；第三阶段，删除UDP套接字中注册的目标地址信息。**
> 每次调用sendto函数时都会重复上述过程。每次都变更目标地址，所以可以重复利用同一个套接字向不同目标传输数据。这种未注册目标地址信息的套接字称为未连接套接字，反之称为已连接套接字。UDP套接字默认是属于未连接套接字。
> 若一个主机需要进行长时间通信，将UDP套接字设置为已连接套接字会提高效率。

**创建已连接UDP套接字**
只需要对UDP套接字调用connect函数
``` c++
sock = socket(PF_INET, SOCK_DGRAM, 0);
memset(&adr, 0, sizeof(adr));
adr.sin_family = AF_INET;
adr.sin_addr.s_addr = ...;
adr.sin_port = ...;
connect(sock, (struct sockaddr*) &adr, sizeof(adr));
```

## 如何优雅地断开连接
### TCP的半关闭
Linux下的close函数和Windows下的closesocket函数意味着完全断开连接，完全断开指不仅无法传输数据，也不能接收数据。因此，在某些情况下，通信一方直接断开连接不是太合适（e.g. A向B发送完数据后调用close，之后A无法再接收B所传输的数据，最终，B传输的A必须接收的文件只能销毁了）。
于是，半关闭的方法应运而生。半关闭意思是可以传输数据但无法接收，或者可以接收数据但无法传输。
一旦两台主机建立了套接字连接，每个主机都会拥有单独的输入流和输出流。当然，其中一台主机的输入流和另一台主机的输出流连接，而输出流与另一台的输入流相连。半关闭是只断开一个流，之前使用的close是同时断开两个流，所以不太优雅。
``` c++
#include <sys/socket.h>
int shutdown(in sock, int howto);
```
sock是需要断开的文件描述符；howto传递断开的方式,包括如下：
> SHUT_RD: 断开输入流
> SHUT_WR: 断开输出流
> SHUT_RDWR: 同时断开I/O流
> 在Windows环境下变量名有所不同，分别为SD_RECEIVE, SD_SEND, SD_BOTH

半关闭主要是为了解决以下情况：服务器端只需要连续地传输文件数据即可，但是客户端无法知道要接收数据到什么时候。客户端不能无休止地调用输入函数，因为这可能导致程序阻塞（调用地函数没有返回）；因此，规定服务器端向客户端传递EOF表示文件传输结束，客户端通过函数返回值接收EOF，这样可以避免与文件内容冲突，那么服务器如何传递EOF?
如果调用close关闭流，可以向向对方发送EOF，但是就无法接收到对方的反馈数据，这时就可以调用shutdown，只关闭输出流，这样就既可以发送EOF，又可以保留输入流接收对方的数据。


# 域名和网络地址
DNS是对IP地址和域名进行相互转换的系统，核心是DNS服务器。
> 什么是域名？
> 服务器端通过ip地址提供网络服务，但ip地址形式不是容易记住，因此用一些容易记住的文字符号代替ip地址，这种文字符号就是域名，等于给ip地址取了个容易记住的名字。

例如，在上网的时候一般通过输入www.baidu.com访问百度主页，这就是域名，当然可以也可以通过输入百度的ip地址119.75.217.109访问，但一般不会有人这么干吧。
域名是服务器端的虚拟地址，而非实际地址，因此在访问的这个过程中还需要DNS服务器将域名转换为ip地址。
所有计算机中都记录着默认的DNS服务器地址，通过这个默认的DNS服务器得到相应的域名的ip地址信息。在浏览器中输入域名后，浏览器通过默认DNS服务器获取该域名对应的ip地址信息，之后才真正接入该网站。
> 一般服务器不会轻易改变服务器域名，但会相对频繁地改变服务器ip地址。

默认的DNS服务器不可能知道网络上所有的域名的ip地址信息。若该DNS服务器无法解析，就会询问其他DNS服务器，再提供给用户。
默认DNS服务器收到自己无法解析的请求时，向上级DNS服务器询问，通过这种方式逐级向上传递信息，到达顶级DNS服务器，即根服务器时，它知道该向哪个DNS服务器询问。向下级DNS服务器传递解析请求，得到ip地址后原路返回，最后将解析的ip地址传递给发送请求的主机。DNS就是这种层次化管理的分布式数据库系统。

> 为什么需要使用域名？
> 主要是方便服务器为用户提供服务，因为不可能要求每一个用户在请求网络服务时都知道ip地址和端口号，而且每次都要输入这些。同时，域名相比ip地址不会轻易变更。
> 在确定使用域名后，程序就应该根据域名解析出ip地址，再接入服务器，这样就不用依赖服务器ip地址了。因此，程序中也需要ip地址和域名之间的转换函数。

## IP地址和域名间的转换
### 利用域名获取ip地址
``` c++
#include <netdb.h>
struct hostent* gethostbyname(const char* hostname);
```
hostent结构体定义如下：
``` c++
struct hostent {
    char* h_name;
    char** h_aliases;
    int h_addrtyoe;
    int h_length;
    char** h_addr_list;
};
```
 变量名|含义 
-|-
h_name|这个变量中存着官方域名。
h_aliases|可以通过多个域名访问同一主页，即同一ip绑定多个域名。这些信息通过h_aliases获得。
h_addrtype|gethostbyname支持v4和v6，这个变量保存着地址族信息。如是IPv4就存着AF_INET。
h_length|保存ip地址长度。IPv4是4字节，就保存4；IPv6是16字节，就保存16。
==h_addr_list==|这是最重要的成员。通过这个变量以整数形式保存域名对应的ip地址。此外，用户较多的网站可能分配多个IP给同一域名，利用多服务器进行负载均衡。此时同时通过此变量获取ip地址信息。
域名转ip时只需关注h_addr_list就可以了。

### 利用ip地址获取域名
``` c++
#include <netdb.h>
struct hostent* gethostbyaddr(const char* addr, socklen_t len, int family);
```
> 注意：Windows环境下包含的库是<WinSock2.h>

# 套接字的多种可选

<table>
    <tr>
        <td>协议层</td>
        <td>选项名</td>
        <td>读取</td>
        <td>设置</td>
    </tr>
    <tr>
        <td rowspan="9">SOL_SOCKET</td>
        <td>SO_SNDBUF</td>
        <td>O</td>
        <td>O</td>
    </tr>
    <tr>
        <td>SO_RCVBUF</td>
        <td>O</td>
        <td>O</td>
    </tr>
    <tr>
        <td>SO_REUSEADDR</td>
        <td>O</td>
        <td>O</td>
    </tr><tr>
        <td>SO_KEEPALIVE</td>
        <td>O</td>
        <td>O</td>
    </tr><tr>
        <td>SO_BROADCAST</td>
        <td>O</td>
        <td>O</td>
    </tr><tr>
        <td>SO_DONTROUTE</td>
        <td>O</td>
        <td>O</td>
    </tr><tr>
        <td>SO_OOBINLINE</td>
        <td>O</td>
        <td>O</td>
    </tr><tr>
        <td>SO_ERROR</td>
        <td>O</td>
        <td>X</td>
    </tr><tr>
        <td>SO_TYPE</td>
        <td>O</td>
        <td>X</td>
    </tr>
    <tr>
        <td rowspan="5">IPPROTO_IP</td>
        <td>IP_TOS</td>
        <td>O</td>
        <td>O</td>
    </tr>
    <tr>
        <td>IP_TTL</td>
        <td>O</td>
        <td>O</td>
    </tr>
    <tr>
        <td>IP_MULTICAST_TTL</td>
        <td>O</td>
        <td>O</td>
    </tr><tr>
        <td>IP_MULTICAST_LOOP</td>
        <td>O</td>
        <td>O</td>
    </tr><tr>
        <td>IP_MULTICAST_IF</td>
        <td>O</td>
        <td>O</td>
    </tr>
    <tr>
        <td rowspan="3">IPPRPTO_TCP</td>
        <td>TCP_KEEPALIVE</td>
        <td>O</td>
        <td>O</td>
    </tr>
    <tr>
        <td>TCP_NODELAY</td>
        <td>O</td>
        <td>O</td>
    </tr>
    <tr>
        <td>TCP_MAXSEG</td>
        <td>O</td>
        <td>O</td>
    </tr>
</table>
了解即可

通过getsockopt和setsockopt设置可选项
``` c++
#include <sys/socket.h>
int getsockopt(int sock, int level, int optname, void* optval, socklen_t* optlen);

int setsockopt(int sock, int level, int optname, const void* optval, socklen_t optlen);
```
变量|含义 
-|-
sock|用于查看选项套接字文件描述符
level|要查看的可选项的协议层
optname|要查看的可选项名
optval|保存查看或设置结果的缓冲地址值
optlen|向第四个参数optval传递的缓冲大小。调用函数后，该变量中保存通过第四个参数返回的可选项信息的字节数

## 一些选项名
**SO_TYPE**
> SO_TYPE是典型的只读可选项，用来查看套接字的类型。

**SO_SNDBUF**和**SO_RCVBUF**
> 通过这两个可选项可以读取和设置套接字I/O缓冲的的大小。

**SO_REUSEADDR**
SO_REUSEADDR及其相关的Time-wait状态很重要
TCP断开连接是通过“4次挥手”完成的，如果是服务器端主动发送FIN消息时，套接字不是立即消除的，而是经过一段时间的Time-wait状态，即等待客户端确认断开连接。所以服务器先断开连接是无法立即重新运行的，需要等待个Time-wait状态，此时端口是正在使用的状态。
> 如果是客户端发起的FIN信息，客户端当然也会经历Time-wait状态，但一般客户端的端口都是任意指定的，所以无需过多关注客户端的Time-wait状态。

>为什么需要Time-wait状态？
> 假设A向B传输ACK消息（SEQ 5001、ACK 7502）后立即删除套接字。但这条ACK消息在传输途中丢失了，主机会认为之前自己发送的FIN消息（SEQ 7501、ACK 5001）未能到达A，从而试图重传，此时A是完全终止的状态，导致B永远无法收到A最后传来的ACK消息。相反，若A套接字处于Time-wait状态，就会向B重传最后的ACK消息，B也可以正常终止。

Time-wait状态是重要的，但有时也会引起麻烦。如果系统发生故障而紧急停止，需要尽快重启服务器提供服务，但因为time-wait状态，总是必须要等待几分钟。
在A的四次挥手过程中，如果最后的消息丢失，B会认为A未收到自己的FIN消息，从而重传，这时，收到FIN消息的A将重启Time-wait计时器。如果网络状态不好，Time-wait状态将一直持续。
*解决的办法就是修改SO_REUSEADDR的状态。*
> 调整该参数，可将Time-wait状态的端口号重新分配给新的套接字。SO_REUSEADDR的默认值是0，即无法分配Time-wait状态下的端口号；将这个值置为1，就可以重新分配了。
``` c++
//伪代码
optlen = sizeof(option);
option = TRUE;
setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, (void*)&option, optlen);
```
**TCP_NODELAY**
TCP套接字默认使用Nagle算法交换数据，因此最大限度地进行缓冲，直到收到ACK。
> Nagle算法：简单理解为，只有收到上一条数据的ACK消息，才会发送下一条数据。在未收到ACK消息前，要发送的消息都会放入发送缓冲中，一旦收到ACK消息，会将缓冲中的数据装入一个数据包发送出去。

不使用Nagle算法时，每一个消息都单独发送，造成网络的拥挤，为了提高网络传输效率，必须使用Nagle算法。
~~凡事总有例外~~ Nagel算法有时也不那么优秀，如果网络流量未受太大影响，不使用Nagle算法传输速度更快。最典型的，传输大文件数据。
开启和关闭的方法也很简单
``` c++
int opt_val = 1;
setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (void*) &opt_val, sizeof(opt_val));      //TCO_NODELAY置为1是禁用，默认0是开启

//可通过getsockopt查看Nagle是否开启
int opt_val;
socklen_t opt_len;
opt_len = sizeof(opt_val);
getsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (void*) &opt_val, &opt_len); 
```

# 多进程服务器端
代表性的并发服务器实现模型和方法：
* 多进程服务器：通过创建多个进程提供服务，
* 多路复用服务器：通过捆绑并统一管理I/O对象提供服务。
* 多线程服务器：通过生成和客户端等量的线程提供服务。

> 什么是进程？
> 定义：“占用内存空间的正在运行的程序。”
> 从操作系统的角度来看，进程是程序流的基本单位。若创建多个进程，则操作系统将同时运行。
> 也就是说，进程是系统中同时运行的程序，当然有时一个程序可以产生多个进程，这只是便于理解的片面简单的解释。多进程服务器就是一个程序产生多个进程的代表。
> CPU的核数和可同时运行的进程数相同，若进程数超过了核数，进程将分时使用CPU资源。

## 通过fork函数创建进程
创建进程的方法有很多，这本书中只介绍用于创建多进程服务器端的fork函数。
``` c++
#include <unistd.h>
pid_t fork(void);
```
fork函数将创建调用的进程副本。就是说，不是根据完全不同的程序创建进程，而是复制正在运行的、调用fork函数的进程。两个进程都将执行fork函数调用之后的语句，主要根据fork的返回值来区分。父进程返回的是子进程的PID，子进程返回的是0。
如下示例
``` c++
#include <stdio.h>
#include <unistd.h>

int gval = 10;
int main(int argc, char* argv[])
{
    pid_t pid;
    int lval = 20;
    gval++;
    lval += 5;
    pid = fork();
    if(pid == 0) {    //如果是子进程
        gval += 2;
        lval += 2;
    }
    else {      //不等于0就是父进程
        gval -= 2;
        lval -= 2;
    }
    if(pid == 0)
        printf("Child Proc: [%d, %d]\n", gval, lval);
    else
        printf("Parent Proc: [%d, %d]\n", gval, lval);
    return 0;
}
```
父进程和子进程都会执行fork之后的所有语句，根据fork返回值的不同，设置不同的执行分支。

## 僵尸进程处理
fork函数产生的子进程有两种终止方式：
* 传递参数并调用exit函数
* main函数中执行return语句并返回值

子进程结束后返回的值会传递给操作系统，而操作系统不会销毁子进程，而是等到把这些值传递给父进程后才销毁，这也是僵尸进程产生的原因。~~(死了但没完全死)~~
而且，操作系统不会主动把子进程的返回值传递给父进程，只有父进程主动发起请求时，操作系统才会传递该值。
解决的办法：
1. **利用wait函数**

``` c++
#include <sys/wait.h>
pid_t wiat(int* statloc);
```
调用该函数后，如果已有子进程终止，那么子进程终止时传递的返回值将保存到该函数的参数所指的内存空间。但函数参数指向的单元中还包含其他信息如下：
WIFEXITED子进程正常终止时返回true；
WEXITSTATUS返回子进程的返回值。
也就是说，向wait函数传递变量status的地址时，调用wait函数后要编写如下内容代码：
``` c++
wait(&status);  //调用wait函数
if(WIFEXITED(status))   //是正常终止吗
{
    puts("Normal termination!");    //这句不用写
    printf("Child pass num: %d", WEXITSTATUS(status));  //返回值是多少
}
```
使用wait函数时需要注意，如果没有已终止的子进程，程序将会阻塞，直至有子进程终止。

2. **使用waitpid函数**
``` c++
#include <sys/wait.h>
pid_t waitpid(pid_t pid, int* statloc, int options);
```
wait函数会引起阻塞，waitpid函数则不会。
pid：等待终止的子进程的pid，若为-1表示等待任意子进程终止。
statloc：指向内存空间的指针。
options：传递头文件sys/wait.h中声明的常量WNOHANG，即使没有终止的子进程也不会进入阻塞状态，而是返回0并退出函数。
同样，在调用waitpid函数后也是要在下面加上一段代码的。

## 信号处理
这里的信号是指在特定事件发生时，由操作系统向进程发送的消息。
> 进程：“操作系统，如果我的子进程终止了，帮我调用zombie_handler函数。”
> 操作系统：“好的！你先把该函数要执行的语句编好。”

上述对话相当于“注册信号”的过程，即进程的子进程结束，请求操作系统帮助直接调用特定函数。
``` c++
#include <signal.h>
void (*signal(int signo, void (*func)(int)))(int);  //为了在产生信号时调用，返回之前注册的函数指针
```
函数名：signal
参数：int signo, void (*func)(int)
返回类型：参数为int型，返回void型函数指针
调用信号函数时，第一个参数为特殊情况的信息，第二个参数为特殊情况下要调用的函数的指针。发生第一个参数代表的情况时，调用第二个参数所指的函数。部分特殊情况如下：
SIGALRM：已到通过调用alarm函数注册的时间。
SIGINT：按下CTRL + C。
SIGCHILD：子进程终止。

**sigaction函数进行信号处理**
sigaction函数类似于signal函数，且是可以完全取代后者的，也更稳定。现在仍使用signal函数只是为了对旧程序的兼容。
``` c++
#include <signal.h>
int sigaction(int signo, const struct sigaction* act, struct sigaction* oldact);        //成功返回0，失败返回-1
```
signo:与signal函数相同，传递信号信息
act：对应于第一个参数的信号处理函数信息
oldact：通过此参数获取之前注册的信号处理函数指针，若不需要则传递0

sigaction结构体定义如下：
``` c++
struct sigaction {
    void (*sa_handler)(int);
    sigset_t sa_mask;
    int sa_flags;
}
```
sa_handler成员保存信号处理函数的指针；sa_mask和sa_flags的所有位均初始化为0即可，这两个成员用于指定信号相关的选项和特性。
简单使用如下：
``` c++
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig) {
    if(sig == SIGALRM)
        puts("Time out!");
    alarm(2);       //重新计时
}

int main(int argc, char* argv[]) {
    struct sigaction act;
    act.sa_handler = timeout;
    sigemptyset(&act.sa_mask);      //利用函数将sa_mask初始化为0
    act.sa_flags = 0;
    sigaction(SIGALRM, &act, 0);        //注册信号函数
    alarm(2);
    for(int i = 0; i < 3; i++) {
        puts("wait...");
        sleep(100);
    }
    return 0;
}
```

# 进程间通信
进程间通信意味着两个不同进程间可以交换数据，为了完成这一点，两个进程应该拥有可以同时访问的内存空间。
## 通过管道实现进程间通信
由于进程是具有完全独立的内存结构，甚至fork函数创建的子进程都不与父进程共享内存空间，所以进程间通信需要其他特殊方法完成。
为了完成进程间通信，需要创建管道。管道并非属于进程的资源，而是和套接字一样，属于操作系统（也就不是fork函数的复制对象）。所以，两个进程通过操作系统提供的内存空间进行通信。
``` c++
#include <unistd.h>
int pipe(int filedes[2]);
```
filedes[0]：通过管道接收数据时使用的文件描述符，即管道出口。
filedes[1]：通过管道传输数据时使用的文件描述符，即管道入口。
具体使用如下：
``` c++
#include <unistd.h>
#include <iostream>
using namespace std;

const int BUF_SIZE = 30;
int main(int argc, char* argv[])
{
    int fds[2];      //创建管道；
    char str1[] = "Who are you?";
    char str2[] = "Thank you for your message";
    char buf[BUF_SIZE];
    pipe(fds);      //通过管道传输数据
    pid_t pid = fork();     //通过fork创建子进程
    if(pid == 0) {
        write(fds[1], str1, sizeof(str1));
        sleep(2);           //如果不睡眠将会读取最近的输入，即读取本进程的write，违背了该程序的目的
        read(fds[0], buf, BUF_SIZE);
        cout << "Child proc output: " << buf << endl;
    }
    else {
        read(fds[0], buf, BUF_SIZE);
        cout << "Parent proc output: " << buf << endl;
        write(fds[1], str2, sizeof(str2));
        sleep(3);
    }
    return 0;
}
```
如何不需要睡眠？最简单方法就是再使用一个管道。

# I/O复用
i/o复用是除了采用多进程外，解决多并发服务器的另一种方法。引入复用技术，可以减少所需进程数。在多进程服务器模型中，每一个客户端的请求都对应了一个进程，采用复用技术后，无论连接多少个客户端，只有一个进程提供服务。
具体的实现方法就是使用select函数，更极端的说，select函数就是i/o复用的全部。
> 使用方法：
> 步骤一，设置文件描述符 -> 指定监视范围 -> 设置超时
> 步骤2，调用select函数
> 步骤3，查看调用结果

**设置文件描述符**
利用select函数可以监视多个文件描述符，也就可以视为监视套接字。首先需要将要监视的文件描述符放到一起，还要区分监视项（接收、传输、异常）。
使用fd_set数组变量来执行这个操作。fd_set通过位置来表示文件描述符，每个位上保存0或1，1表示监视该描述符。
``` c++
int main()
{
    fd_set set;     //准备监视文件描述符
    FD_ZERO(&set);      //所有位置为0
    FD_SET(1, &set);        //监视描述符1
    FD_SET(3, &set);
    FD_CLR(1, &set);        //清除文件描述符1的监视状态
    FD_ISSET(3, &set);      //判断文件描述符3是否被监视
}
```
**设置监视范围**
首先介绍select函数
``` c++
#include <sys/select.h>
#include <sys/time.h>

int select(int maxfd, fd_set* readset, fd_set* writeset, fd_set* exceptset, const struct timeval* timeout);
//成功返回0，失败返回-1
```
maxfd：监视对象文件描述符数量。（因为每次新建文件描述符时，都是在已有基础上+1，所以传递时只需要把当前最大文件描述符值+1传递）
readset：将所有关注“是否存在待读取数据”的文件描述符注册到fd_set型变量，并传递其地址值。
writeset：将所有关注“是否可传输无阻塞数据”的文件描述符注册到fd_set型变量，并传递其地址值。
exceptset：将所有关注“是否发生异常”的文件描述符注册到fd_set型变量，并传递其地址值。
timeout：调用select函数后，位防止陷入无限阻塞状态，传递超时信息。
返回值：失败返回-1，超时返回0.因发生关注的事件返回时，返回发生事件的文件描述符。timeval结构体如下：
``` c++
struct timeval {
    long tv_sec;        //秒
    long tv_usec;       //毫秒
}
```
select函数只有在监视的文件描述符发生变化时才返回，否则就进入阻塞状态。如果不想一直处于阻塞状态，同上上述结构体，填入秒和毫秒的参数，超过了这个时间select函数就会返回。如果不想设置超时，就传递NULL。

**调用select查看结果**
在select函数调用返回时，向其传递的fd_set变量将发生变化，原本为1的位置全置为0，但发生变化的文件描述符对应位不发生变化，从而可以确定是哪些文件描述符发生了变化。
``` c++
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <iostream>
#include <string>
using namespace std;

const int BUF_SIZE = 30;

int mian(int argc, char* argv[])
{
    fd_set reads, temp;
    struct timeval timeout;
    FD_ZERO(&reads);        //将fd_set初始化
    FD_SET(0， &reads);     //0是标准输入
    int result;
    char buf[BUF_SIZE];
    int str_len;
    string str;
    while(1) {
        temp = reads;       //调用select后会改变fd_set状态，所以先复制原来的状态再操作，这是使用select的通用做法。
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        result = select(1, &temp, 0, 0, timeout);      //只监视读取文件描述符
        if(result == -1) {
            cout << "select() failed";
            break;
        }
        else if(result == 0) {
            cout << "Time out";
        }
        else {
            if(FD_SET(0, &temp)) {
                str_len = read(0, buf, BUF_SIZE);
                buf[str_len] = 0;
                cout << "message from console: " << buf;
            }
        }
    }
    return 0;
} 
```

# 多种I/O函数
## send和recv函数
``` c++
#include <sys/socket.h>

ssize_t send(int sockfd, const void* buf, size_t nbytes, int flags);
ssize_t recv(int sockfd, const void* buf, size_t nbytes, int flags);
```
最后一个参数是收发数据时的可选项，其他参数基本和之前无差别。
flags可利用位或运算符|同时传递多个信息。
可选项|含义|send|recv
:-:|:-:|:-:|:-:
MSG_OOB|用于传输带外数据|√|√
MSG_PEEK|验证输入缓冲中是否存在接收的数据| |√
MSG_DONTROUTE|数据传输过程中不参照路由表，在本地网络中寻找目的地|√| 
MSG_DONTWAIT|调用I/O函数时不阻塞，用于使用非阻塞I/O|√|√
MEG_WAITALL|防止函数返回，直到接收全部请求的字节数| |√

**MSG_OOB**
在一些情况下，消息需要紧急处理时，如果排队等待就不合适。MSG_OOB类似于创建了一个用于收发紧急消息的特殊通道。
但很遗憾，MEG_OOB不会加快数据传输的速度，而且通过信号处理函数读取数据时只能读一字节，剩下的只能通过未设置MSG_OOB的普通输入函数读取。这是因为TCP不存在真正意义上的“带外数据”，而是利用了TCP的紧急模式进行传输。
MSG_OOB的真正意义是督促数据接收对象尽快处理数据，但TCP的“保持传输顺序”的特性仍然成立。~~（MSG_OOB只负责发出消息说抓紧救人，但能不能及时救还得TCP说了算）~~

**MSG_PEEK** 和 **MSG_DONTWAIT**
同时设置MSG_PEEK和MSG_DONTWAIT选项，以验证输入缓冲中是否存在接收的数据。设置MSG_PEEK并调用recv函数时，即使读取了输入缓冲中的数据也不会删除。因此，该选项通常与MSG_DONTWAIT合作，用于调用以非阻塞方式验证待读数据存在与否。

## readv和writev函数
这两个函数有助于提高数据通信效率。
通过writev函数可以将分散保存在多个缓冲中的数据一并发送，通过readv函数可以由多个缓冲分别接收。因此，适当使用可以减少i/o函数的调用次数。
``` c++
#include <sys/uio.h>

ssize_t writev(int filedes, const struct iovec* iov, int iovcnt);
ssize_t readv(int filedes, const struct iovec* iov, int inocnt);
//成功返回字节数，失败返回-1
```
filedes:数据收发对象的文件描述符。
iov：iovec结构体数组的地址值，结构体中包含收发数据的位置和大小信息。
iovcnt：第二参数iov的数量。
``` c++
struct iovec {
    void* iov_base;     //缓冲地址
    size_t iov_len;     //缓冲大小
};
```
结构体iovec由保存待发送数据的缓冲地址值和实际发送的数据长度信息构成。

# 多播与广播
## 多播
多播方式的数据传输 是基于UDP完成的。采用多播方式，可以同时向多个主机传输数据。
多播组是D类IP地址（224.0.0.0 ~ 239.255.255.255）。

为了传递多播数据包，必须设置TTL。TTL是Time to Live的简写，是决定“数据包传递距离”的主要因素。TTL用整数表示，每经过一个路由器就减1，TTL变为0时，该数据包无法再被传递，只能销毁。
TTL是套接字可选项。与设置TTL相关的协议层为IPPROTO_IP,选项名为IP_MULTICAST_TTL。
``` c++
int send_sock;
int time_live = 64;
...
send_sock = socket(PR_INET, SOCK_DGRAM, 0);
setsockopt(send_sock, IPPROTO_IP, IP_MULTICAST_TTL, (void*) &time_live, sizeof(time_live));     //将TTL设置为64
...
```
另外，加入多播组也通过设置socket选项完成，加入多播组相关的协议层为IPPROTO_IP，选项名为IP_ADD_MEMBERSHIP。
``` c++
int recv_sock;
struct ip_mreq join_adr;
...
recv_sock = socket(PF_INET, SOCK_DGRAM, 0);
...
join_adr.imr_multiaddr.s_addr = "多播组地址信息";
join_adr.imr_interface.s_addr = "加入多播组的主机地址信息";
setsockopt(recv_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void*) &join_adr, sizeof(join_adr));
...

//上述涉及的ip_mreq结构体如下
struct ip_mreq
{
    struct in_addr imr_multiaddr;       //写入加入的组IP地址
    struct in_addr imr_interface;       //加入该组的套接字所属主机的IP地址，也可以使用INADDR_ANY
};
```

## 广播
广播分为两种：直接广播和本地广播。
两者在代码实现上的差别主要在IP地址。直接广播的IP地址中除了网络地址外，其余主机地址全部设置为1。反之，本地广播中使用的IP地址限定为255.255.255.255。

# LINUX环境下网络编程
## 标准I/O函数
使用标准I/O优点：
1. 具有良好的移植性
2. 可以利用缓冲提高性能

存在的缺点：
1. 不容易进行双向通信
2. 有时可能频繁调用fflush函数
3. 需要以FILE结构体指针的形式返回文件描述符

> C的<stdio.h>库中定义了用于文件操作的结构体FILE。通过fopen返回一个文件指针（指向FILE结构体的指针）来进行文件操作。

用fdopen函数可将创建套接字时返回的文件描述符转换为标准I/O函数中使用的FILE结构体指针。
``` c++
#include <stdio.h>
FILE* fdopen(int fildes, const char* mode);
```
fileno是个功能与之相反的函数，将FILE结构体指针转换为文件描述符。
``` c++
#include <stdio.h>
int fileno(FILE* stream);
```

## I/O流分离的一些
目前已经通过两种方法进行了I/O流分离，第一种是调用fork函数复制出一个文件描述符，以区分输入和输出中使用的文件描述符；第二种是通过文件模式区分读取和写入。
优点：
1. 通过分开输入和输出过程，降低实现难度。
2. 提高速度和性能。

**流分离带来的EOF问题**
shutdown函数的选择关闭哪个流可以保证fork的流分离是没有问题的。同样，通过文件模式进行流分离也需要这种半关闭。
明显，在使用标准I/O时，读写两种模式的FILE结构体指针都是由同一个文件描述符转换来的，因此，针对任一个FILE指针调用fclose都会直接关闭文件描述符，也就终止了套接字。有用的办法就是**创建FILE指针前先复制一个文件描述符**，这样有两个文件描述符指向同一个套接字，只有在两个文件描述符都关闭的情况下套接字才会关闭。
**复制文件描述符**
使用dup或者dup2函数来复制文件描述符
``` c++
#include <unistd.h>
int dup(int fildes);
int dup2(int filfes, int fildes2);
```
fildes：需要复制的文件描述符
fildes2：明确指定文件描述符副本的整数值。
然后，同样是采用shutdown函数来进行半关闭操作
> e.g. 
> shutdown(fileno(copy_fp), SHUT_WR);

## 优于select的epoll
实现I/O复用的传统方法有select函数和poll函数。但由于各种原因会导致这些方法不能得到令人满意的性能。
因此有了Linux下的epoll，BSD的kqueue、Solaris的/dev/poll和Windows的IOCP等复用技术。

**select速度慢的原因**
1. 调用select函数后常见的针对所有文件描述符的循环语句
2. 每次调用select函数时需要向该函数传递监视对象信息

select也有优点，即具有更好的兼容性，大部分操作系统都是支持select函数的。
### epoll必要的函数和结构体
epoll函数的优点：
1. 无需编写以监视状态变化为目的的针对所有文件描述符的循环语句
2. 调用对应于select函数的epoll_wait函数时无需每次传递监视对象信息

**epoll服务器端需要的3个函数**：
* epoll_create: 创建保存epoll文件描述符的空间
* epoll_ctl: 向空间注册并销毁文件描述符
* epoll_wait: 与select函数类似，等待文件描述符发生变化

epoll方式中通过如下结构体epoll_event将发生变化的文件描述符单独集中到一起。
``` c++
struct epoll_event
{
    __uint32_t events;
    epoll_data_t data;
};

dypedef union epoll_data
{
    void* ptr;
    int fd;
    __uint32_t u32;
    __uint64_t u64;
} epoll_data_t;
```
声明足够大的epoll_event结构体数组后，传递给epoll_wait函数时，发生变化的文件描述符信息将被填入该数组。因此，无需像select函数那样针对所有文件描述符进行循环。

**epoll_creat**
``` c++
#include <sys/epoll.h>
int epoll_create(); //成功时返回epoll文件描述符，失败时返回-1
```
该函数返回的文件描述符主要用于区分epoll例程。需要终止时，也要调用close函数。

**epoll_ctl**
``` c++
#include <sys/epoll.h>
int epoll_ctl(in epfd, int op, int fd, struct epoll_event* event);  //成功时返回0，失败返回-1
//使用示例
epoll_ctl(A, EPOLL_CTL_ADD, B, C);
epoll_ctl(A, EPOLL_CTL_DEL, B, NULL);
```
**op**：用于指定监视对象的添加删除或更改操作
常量|含义
-|-
EPOLL_CTL_ADD|将文件描述符注册到epoll例程
EPOLL_CTL_DEL|从epoll例程中删除文件描述符
EPOLL_CTL_MOD|更改注册的文件描述符的关注事件发生情况

**fd**：需要注册的监视对象的文件描述符
**event**：用于保存发生事件的文件描述符集合。但也可在epoll例程中注册文件描述符时，用于注册关注的事件。
``` c++
//e.g.
struct epoll_event event;
...
event.events = EPOLLIN;     //发生需要读取数据的事件时
event.data.fd =sockfd;
epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
...
```
events中可以保存的常量和事件类型
常量|事件类型
-|-
EPOLLIN|需要读取数据的情况
EPOLLOUT|输出缓冲为空，可以立即发送数据的情况
EPOLLPRI|收到OOB数据的情况
EPOLLRDHUP|断开连接或半关闭的情况，这在边缘触发方式下非常有用
EPOLLERR|发生错误的情况
EPOLLET|以边缘触发的方式得到事件通知
EPOLLONESHOT|发生一次事件后，相应文件描述符不再收到事件通知。因此需要向epoll_ctl函数的第二个参数传递EPOLL_CTL_MOD再次设置事件
可以通过位或运算符同时传递多个上述参数。

**epoll_wait**
``` c++
#include <sys/epoll.h>
int epoll_wait(int epfd, struct epoll_event* events, int maxevents, int timeout);   //成功时返回发生事件的文件描述符数，失败时返回-1
```
``` c++
int event_cnt;
struct epoll_event *ep_events;
...
ep_events = malloc(sizeof(struct epoll_event)* EPOLL_SIZE);     //EPOLL_SIZE是宏常量
...
event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE - 1);    //返回发生事件的文件描述符数
...
```
### 条件触发和边缘触发
条件触发：只要输入缓存中有数据就会一直通知该事件
边缘触发：输入缓冲收到数据时仅注册1次该事件。即使输入缓冲中还留有数据，也不会再进行注册。

## 多线程服务器
``` c++
#include <pthread.h>

int pthread_create(pthread* restrict thread, const pthread_attr_t* restrict attr, void*(*start_routine)(void*), void* restrict arg);
int pthread_join(pthread_t thread, void** status);
```
**线程同步**
也就是加锁
``` c++
#include <pthread.h>
int pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* attr);
int pthread_mutex_lock(pthread_mutex_t* mutex);
int pthread_mutex_unlock(thread_mutex_t* mutex);
int pthread_mutex_destory(pthread_mutex_t* mutex);
```
另外一种是采用信号量的方式
```c++
#include <semaphore.h>
int sem_init(sem_t* sem, int pshared, unsigned int value);
int sem_post(sem_t* sem);
int sem_wait(sem_t* sem);
int sem_destory(sem_t* sem);
```

**销毁线程**
Linux线程不会在返回时自动销毁，所以一般用pthread_join或者pthread_detach加以明确，确保创建的内存空间会被释放。
``` c++
#include <pthread.h>
int pthread_detach(pthread_t thread);
```


# Windows环境下网络编程