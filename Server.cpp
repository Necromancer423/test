#include <stdio.h>
#include <winsock.h>
#include <string.h>
 
int main(int argc, char *argv[])
{ SOCKET listenSocket;
  SOCKET remoteSocket;
  SOCKADDR_IN Server_addr;
  SOCKADDR_IN Client_addr;
  int sin_size;
  short port;
 
  char buffer[256];
 
  int wsastartup;
  int ls_result;
 
/* Inizializzazione della libreria Socket */
WORD wVersionRequested = MAKEWORD(2,2);
WSADATA wsaData;           // La struttura WSADATA contiene informazioni sull'implementazione delle socket windows
wsastartup = WSAStartup(wVersionRequested, &wsaData);  // Inizializza la versione di socket windows richiesta 
if (wsastartup != NO_ERROR) printf("Errore WSAStartup()\n");
 
/* Creazione della Socket che si porrà in ascolto di richieste del Client*/
listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  // Crea una Socket della Famiglia Internet / TCP (stream) / 
if (listenSocket < 0)
printf("Server: errore nella creazione della socket.\n");
else printf("La Listening Socket e' partita\n");
 
/* Effettua la bind sull'indirizzo e porta ora specificati */
port = 4000;
 
Server_addr.sin_family = AF_INET;
Server_addr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
Server_addr.sin_port = htons(port);
 
if (bind(listenSocket,(LPSOCKADDR)&Server_addr,sizeof(struct sockaddr)) < 0) // Associa un Nome (IndirizzoIP:Porta) alla Socket
printf("Server: errore durante la bind.\n");
 
/* La socket si pone in "ascolto" tramite la listen() */
ls_result = listen(listenSocket, SOMAXCONN);    // Si mette in stato di attesa di richiesta di connessione (8 massimo numero connessioni accett)
if (ls_result < 0) printf("Server: errore durante la listen.\n");
else printf("La Socket e' in Ascolto\n");
 
/* La socket accetta la richiesta di connessione del Client */
sin_size = sizeof(struct sockaddr_in);
remoteSocket = accept(listenSocket, (struct sockaddr *)&Client_addr,&sin_size);  // Accetta una connessione in entrata su questa Socket
printf("Accettata Connessione con Client: %s\n\n",
inet_ntoa(Client_addr.sin_addr));
 
/* Il Server accetta il messaggio dal Client */
recv(remoteSocket, buffer, sizeof(buffer), 0);    // Riceve dati da una Socket connessa
printf("Messaggio Arrivato: %s \n", buffer);
// ---------------------------------------- INIZIO   Conversione della stringa -----------------------
int l= strlen(buffer);
int diff='A'-'a';
for (int i=0; i<l; i++)
{ if (buffer[i]>='a' && buffer[i]<='z')
     buffer[i]=buffer[i]+diff;
 } 
// ---------------------------------------- FINE   Conversione della stringa -----------------------
printf("Messaggio Convertito: %s \n", buffer);
/* Il Server rimanda il messaggio al Client */
send(remoteSocket, buffer, sizeof(buffer), 0);  // Invia dati ad una Socket connessa

printf("Chiudo il Server");
closesocket(remoteSocket);   // Chiude il Socket specificato
WSACleanup();  // Rilascia tutte le risorse utilizzate dal Socket
 
system("pause");
return 0;
}

