#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define buffer_size 1024 //buffer_size for reading response

int main(){
    int sock=0; //file descriptor del socket
    struct sockaddr_in address; 
    char buffer[buffer_size]={0};
    const char *request = 
        "GET / HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "Connection: close\r\n"
        "\r\n";

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){ //inizializza il socket
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    if(inet_pton(AF_INET, "127.0.0.1", &address.sin_addr)<=0){ //controlla se l'indirizzo è valido
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }
    if(connect(sock, (struct sockaddr *)&address, sizeof(address)) < 0){ //si connette al server
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }
    send(sock, request, strlen(request),0); //invia la richiesta al server 
    read(sock, buffer, buffer_size); //legge la risposta dal server
    printf("Response from server:\n%s\n", buffer); //stampa la risposta ricevuta
    close(sock); //chiude il socket
}