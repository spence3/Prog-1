// CS 2690 Program 1
// Simple Windows Sockets Echo Client (IPv6)
// Last update: 2/12/19
// <Your name here> <Your section here> <Date>
// <Your Windows version and Visual Studio version>
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

// #define ALL required constants HERE, not inline
// #define is a macro, don't terminate with ';' For example...
#define RCVBUFSIZ 50 // buffer size for received messages

// declare any functions located in other .c files here
void DisplayFatalErr(char* errMsg); // writes error message before abnormal termination

void main(int argc, char* argv[]) { // argc is # of strings following command, argv[] is array of ptrs to the strings
    // Declare ALL variables and structures for main() HERE, NOT INLINE (including the following...)
    WSADATA wsaData; // contains details about WinSock DLL implementation
    struct sockaddr_in6 serverInfo; // standard IPv6 structure that holds server socket info

    printf("hello world!");

    // Verify correct number of command line arguments, else do the following:
    // fprintf(stderr, "Helpful error message goes here\n");
    // exit(1); // ...and terminate with abnormal termination code (1)

    // Retrieve the command line arguments. (Sanity checks not required, but port and IP addr will need to be converted from char to network standard. See slides 11-15 & 12-3 for details.)

    // Initialize Winsock 2.0 DLL. Returns 0 if ok. If this fails, fprintf error message to stderr as above & exit(1).
    // Create an IPv6 TCP stream socket. Now that Winsock DLL is loaded, we can signal any errors as shown on next line:
    // DisplayFatalErr("socket() function failed.");

    // Display helpful confirmation messages after key socket calls like this:
    // printf("Socket created successfully. Press any key to continue...");
    // getchar(); // needed to hold console screen open

    // If doing extra credit IPv4 address handling option, add the setsockopt() call as follows...
    // if (perrno = setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, (char *)&v6Only, sizeof(v6Only)) != 0)
    // DisplayFatalErr("setsockopt() function failed.");

    // Zero out the sockaddr_in6 structure and load server info into it. See slide 11-15.
    // Don't forget any necessary format conversions.

    // Attempt connection to the server. If it fails, call DisplayFatalErr() with appropriate message,
    // otherwise printf() confirmation message.

    // Send message to server (without '\0' null terminator). Check for null msg (length=0) & verify all bytes were sent...
    // ...else call DisplayFatalErr() with appropriate message as before.

    // Retrieve the message returned by server. Be sure you've read the whole thing (could be multiple segments).
    // Manage receive buffer to prevent overflow with a big message.
    // Call DisplayFatalErr() if this fails. (Lots can go wrong here, see slides.)

    // Display ALL of the received message, in printable C string format.

    // Close the TCP connection (send a FIN) & print appropriate message.

    // Release the Winsock DLL
    exit(0);
}
