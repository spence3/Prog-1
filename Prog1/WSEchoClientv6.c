// CS 2690 Program 1
// Simple Windows Sockets Echo Client (IPv6)
// Last update: 2/12/19
// Spencer Miller 601 10/11/24
// Windows 11 VS 2019
//
// Usage: WSEchoClientv6 <server IPv6 address> <server port> <"message to echo">
// Companion server is WSEchoServerv6
// Server usage: WSEchoServerv6 <server port>
//
// This program is coded in conventional C programming style, with the
// exception of the C++ style comments.
//
// I declare that the following source code was written by me or provided
// by the instructor. I understand that copying source code from any other
// source or posting solutions to programming assignments (code) on public
// Internet sites constitutes cheating, and that I will receive a zero
// on this project if I violate this policy.
// ----------------------------------------------------------------------------

#include <stdio.h> // for print functions
#include <stdlib.h> // for exit()
#include <winsock2.h> // for Winsock2 functions
#include <ws2tcpip.h> // adds support for getaddrinfo & getnameinfo for v4+6 name resolution
#include <Ws2ipdef.h> // optional - needed for MS IP Helper
#include <stdbool.h> //include bool

// #define ALL required constants HERE, not inline
// #define is a macro, don't terminate with ';' For example...
#define RCVBUFSIZ 50 // buffer size for received messages
char rcvBuffer[RCVBUFSIZ]; // Buffer to store received data

// declare any functions located in other .c files here

void DisplayFatalErr(char* errMsg)
{
    // Returns errorcode from current task or thread
    fprintf(stderr, "%s: %d\n", errMsg, WSAGetLastError()); 
        WSACleanup();
    exit(1);
}

int main(int argc, char* argv[]) { // argc is # of strings following command, argv[] is array of ptrs to the strings
    // Declare ALL variables and structures for main() HERE, NOT INLINE (including the following...)
    WSADATA wsaData; // contains details about WinSock DLL implementation
    //initialize data
    int sock1, sock2;
    int numArgs;
    numArgs = argc;

    if (numArgs != 4) {
        printf("Number of arguments are not corret... Must have 4.");
        exit(1);
    }

    //Declare structure and variables
    struct sockaddr_in6 serverInfo;

    //Server IP address and port number come from the client command line
    //initialize message ("This is a test")
    char* ip;
    int port;
    const char* message;
    int msgLen;

    //get ip and port from command line
    ip = argv[1];
    port = (unsigned short)atoi(argv[2]);
    message = argv[3];
    msgLen = strlen(message);

    //procedural code
    memset(&serverInfo, 0, sizeof(serverInfo));//zero out the structure

    //load server info into sockadd_in6
    serverInfo.sin6_family = AF_INET6;
    serverInfo.sin6_port = htons(port); //convert int port into network order*

    //convert server addr from char to ntwrk form, load into socketaddr_in6
    if (inet_pton(AF_INET6, ip, &serverInfo.sin6_addr) <= 0) {
        int err = WSAGetLastError(); // Get the error code
        fprintf(stderr, "inet_pton() failed to convert IP address: %s. Error: %d\n", ip, err);
        exit(1); // Exit with error code
    }

    //Initialize Winsock 2.0 DLL
    int result = WSAStartup(MAKEWORD(2, 0), &wsaData);
    if (result != 0) {
        fprintf(stderr, "Failed to initialize Winsock");
        exit(1);
    }
    //set up socks
    sock1 = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    sock2 = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);


    //check for success of socks
    if (sock1 == INVALID_SOCKET) {
        DisplayFatalErr("socket() function failed for sock1.");
    }
    else {
        printf("Socket1 created successfully. Press ENTER key to continue...");
        getchar();
    }
    if (sock2 == INVALID_SOCKET) {
        DisplayFatalErr("socket() function failed for sock2.");
    }
    else {
        printf("Socket2 created successfully. Press ENTER key to continue...");
        getchar();
    }

    //connect to server
    if (connect(sock1, (struct sockaddr*)&serverInfo, sizeof(serverInfo)) < 0) {
        DisplayFatalErr("connect() function failed.\n");
    }
    else {
        printf("Connected to server!\n");
    }

    //Check for null msg(length = 0)
    if (msgLen == 0) {
        DisplayFatalErr("We not good with message length\n");
    }
    //send function
    int PASCAL FAR send(SOCKET s, const char FAR * buf, int len, int flags);
    //send message
    if (send(sock1, message, msgLen, 0) != msgLen) {
        DisplayFatalErr("Failed to Send Message\n");
    }
    else {
        printf("Send Successfull!\n");
    }

    //receive function
    int PASCAL FAR recv(SOCKET s, char FAR * buf, int len, int flags);
    int bytesRead;
    int totalBytesReceived = 0;//should equal message len
    int PASCAL FAR closesocket(SOCKET s);// closing socket when finished

    printf("msg len(expected bytes to receive): %d\n", msgLen);//expected bytes to receive
    while ((bytesRead = recv(sock1, rcvBuffer, RCVBUFSIZ - 1, 0)) > 0) {
        //errors
        if (bytesRead <= 0) {
            DisplayFatalErr("Message not received");
        }


        totalBytesReceived += bytesRead;//updating total bytes
        rcvBuffer[bytesRead] = '\0';//C string for printing

        printf("Received chunk: %s\n", rcvBuffer); // Print received chunk
        printf("%d\n", bytesRead);

        //all the message has been received --> exit
        if (totalBytesReceived == msgLen) {
            closesocket(sock1);
        }
    }

    closesocket(sock1);//close socket and send FIN
    printf("Socket Closed Successfully...\n");
    WSACleanup();//cleanup
    printf("Winsock resources cleaned up successfully...\n");


    exit(0);
}


//DONE:
   // Verify correct number of command line arguments, else do the following:
    // fprintf(stderr, "Helpful error message goes here\n");
    // exit(1); // ...and terminate with abnormal termination code (1)]


    //----------------PRETTY SURE IM GOOD ON THIS------------------
    // Retrieve the command line arguments.
    // (Sanity checks not required, but port and
    // IP addr will need to be converted from char to network standard.
    // See slides 11-15 & 12-3 for details.)


   // Initialize Winsock 2.0 DLL. Returns 0 if ok. If this fails, fprintf error message to stderr as above & exit(1).
    // Create an IPv6 TCP stream socket. Now that Winsock DLL is loaded, we can signal any errors as shown on next line:
    // DisplayFatalErr("socket() function failed.");



    // Display helpful confirmation messages after key socket calls like this:
    // printf("Socket created successfully. Press any key to continue...");
    // getchar(); // needed to hold console screen open


    //-----------------------DO LATER IF FEEL LIKE IT---------------------
    // If doing extra credit IPv4 address handling option, add the setsockopt() call as follows...
    // if (perrno = setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, (char *)&v6Only, sizeof(v6Only)) != 0)
    // DisplayFatalErr("setsockopt() function failed.");

    //-----------------------FEEL PRETTY GOOD ON THIS---------------------
    // Zero out the sockaddr_in6 structure and load server info into it. See slide 11-15.
    // Don't forget any necessary format conversions.


    // Attempt connection to the server. If it fails, call DisplayFatalErr() with appropriate message,
    // otherwise printf() confirmation message.



    //------------------------PRETTY SURE WE GOOD HERE---------------------
    // Send message to server (without '\0' null terminator). Check for null msg (length=0) & verify all bytes were sent...
    // ...else call DisplayFatalErr() with appropriate message as before.


    // Retrieve the message returned by server. Be sure you've read the whole thing (could be multiple segments).
    // Manage receive buffer to prevent overflow with a big message.
    // Call DisplayFatalErr() if this fails. (Lots can go wrong here, see slides.)

    // Display ALL of the received message, in printable C string format.

    // Close the TCP connection (send a FIN) & print appropriate message.

    // Release the Winsock DLL