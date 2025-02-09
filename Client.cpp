// Client - Conversione Maiuscolo
#include <stdio.h>
#include <stdio.h>
#include <winsock.h>
#include <string.h>
int main()
{ 	SOCKET clientsocket;  // Creare un elemento di tipo socket chiamato  clientsocket (Client):
	SOCKADDR_IN addr;
	 
	char messaggio[80];
	short port;
	 
	WORD wVersionRequested = MAKEWORD(2,2);
	WSADATA wsaData;                          // La struttura WSADATA contiene informazioni sull'implementazione delle socket windows
	WSAStartup(wVersionRequested, &wsaData);  // Inizializza la versione di socket windows richiesta 
	 
	port = 4000;
	 
	addr.sin_family = AF_INET;                      // Valorizza gli attributi della variabile strutturata server (Famiglia Internet)
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Il Server accetta richieste da LocalHost 
	//addr.sin_addr.s_addr  = htonl(INADDR_ANY)     // Il Server accetta richieste da ogni interfaccia di rete (da usare per il Server)
	addr.sin_port = htons(port);                   	// Porta utilizzata (4000)
	
	clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);   // Crea una Socket della Famiglia Internet / TCP (stream) 
	if (connect(clientsocket, (LPSOCKADDR)&addr, sizeof(addr)) < 0) // Verifica se il Server haa accettato la connessione 
	printf("Errore nella connessione con il Server");
	 
	printf("Messaggio da Inviare: ");
	gets(messaggio);
	send(clientsocket,messaggio,sizeof(messaggio),0);   // Invia dati ad una Socket connessa
	
	recv(clientsocket,messaggio,sizeof(messaggio),0);   // Riceve dati da una Socket connessa
	printf("\nMessaggio ricevuto %s: ",messaggio);
	closesocket(clientsocket);  	// Chiude il Socket specificato
	WSACleanup();                  // Rilascia tutte le risorse utilizzate dal Socket
	system("pause");
	return 0;
}

