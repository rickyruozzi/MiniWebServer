#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define buffer_size 1024 //buffer_size for reading request

int main(){
    int server_fd, new_socket; //file descriptors dei socket
    struct sockaddr_in address; //server address structure
    int addrLen = sizeof(address); //lunghezza dell'indirizzo
    char buffer[buffer_size]={0}; //buffer inizializzato a zero per leeggere la richiesta
    const char *response =  //risposta HTTP 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: 46\r\n"
        "\r\n"
        "<html><body><h1>Hello, World!</h1></body></html>";
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0))==0){ //inizializzazione del server socket
        perror("socket initialization failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET; //IPv4
    address.sin_addr.s_addr = INADDR_ANY; //tutti gli indirizzi disponibili
    address.sin_port = htons(PORT); //porta di ascolto 
    //htons converte la porta in formato di rete
    if(bind(server_fd, (struct sockaddr *)&address , sizeof(address))<0){ //associazione del socket ad un indirizzo e ad una porta
        //il bind() associa il socket all'indirizzo e porta specificati
        perror("bind operation failed");
        exit(EXIT_FAILURE);
    }
    if(listen(server_fd, 3)<0) //mette il server in ascolto e se fallisce chiude il programma
    {
        perror("Listening operation failed");
        exit(EXIT_FAILURE);
    }
    printf("Server is listening on port %d \n", PORT);
    while(1){
        if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrLen))<0){ //accetta una connessione
            //accetta la connessione in entrata
            perror("accept operation failed");
            exit(EXIT_FAILURE);
        }
        read(new_socket, buffer, buffer_size); //legge la richiesta dal client e lo memorizza nel buffer
        printf("Received request:\n%s\n", buffer); //stampa la richiesta ricevuta
        send(new_socket, response, strlen(response), 0); //invia la risposta al client con il testo HTML
        close(new_socket); //chiude il socket del client
    }
    return 0;
}
/*
creazione di due variabili intere che conterranno i file descripto del server e del client.
address contiene le informazioni sull'indirizzo del server.
BIND() => Associa il socket all'indirizzo e alla porta selezionati. 
LISTEN() => Mette il server in ascolto per i client in entrata. 
ACCEPT() => Accetta una connessione in entrata. 
READ() => Sfrutta la struttura un buffer per inserire la richiesta del client in un buffer. 
SEND() = > Invia la risposta al client. 
*/