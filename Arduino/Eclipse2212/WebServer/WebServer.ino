#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

// Adresse MAC
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 99); // Adresse IP
EthernetServer server(80);  // Port du serveur

File webFile;

void setup()
{
    Ethernet.begin(mac, ip);  // Initialise le protocole Ethernet
    server.begin();           // Démarre l'écoute des clients
    Serial.begin(9600);       // Pour débugger(au cas où)
    
    // Initialise la carte SD
    Serial.println("Initialisation de la carte SD...");
    if (!SD.begin(4)) {
        Serial.println("ERREUT - Initialisation échoué!");
        return;    // init failed
    }
    Serial.println("Carte SD initialisée.");
    // check for index.htm file
    if (!SD.exists("Index.html")) {
        Serial.println("ERREUR - Fichier introuvable!");
        return;  // can't find index file
    }
    Serial.println("Fichier trouvé.");
}

void loop()
{
    EthernetClient client = server.available();  // Ecoute les clients

    if (client) {  // On a un client?
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // Si les données sont disponible
                char c = client.read(); // On lis un octet du client (1char)
                // La dernière ligne de la requête client  est vide et se finis par un /n
                // Répon dau client uniquement après que la dernière ligne est reçue
                if (c == '\n' && currentLineIsBlank) {
                    // Envoie un header de réponse HTTP standard
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println();
                    // send web page
                    webFile = SD.open("Index.html");        // Ouvre la page web
                    if (webFile) {
                        while(webFile.available()) {
                            client.write(webFile.read()); // Envoie au lcient la page web
                        }
                        webFile.close();
                    }
                    break;
                }
                // Chaque ligne reçue du client finis par \r\n
                if (c == '\n') {
                    // La ligne vide est lue
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // Un morceau de texte est lu
                    currentLineIsBlank = false;
                }
            } // end if (client.available())
        } // end while (client.connected())
        delay(1);      // Donne le temps au navigateur de récupérer les données
        client.stop(); // ferme la connection
    } // end if (client)
}
