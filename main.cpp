//#include <mysql.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zconf.h>


//TODO Test
int main(void) {
    MYSQL *connection;    /* Der MySQL-Handler: Verbindung zum MySQL-Server */
    MYSQL_RES *ergebnis;  /* Ergebnis einer Abfrage */
    char abfrage[1000];  /* beinhaltet die Abfrage */
    MYSQL_ROW zeile;      /* Ergebniszeile */
    int anz;        /* Anzahl der Zeilen */
    int i;

    /* Datenbank Login Details */
    char host[] = "127.0.0.1";      /* Hostname */
    char user[] = "root";           /* Benutzername */
    char password[] = "ubuntu";         /* Passwort */
    char db[] = "weiterbildung";  /* Datenbank */
    int port = 1111;            /* Port */

    /* SSH Connection Details */
    char sshUser[] = "ubuntu";        /* SSH Benutzername */
    char sshHost[] = "192.168.1.134"; /* SSH Hostname */
    char sshLocalPort[] = "1111";           /* SSH local Port */

    /* SSH Verbindungsdetails werden zusammengefügt */
    char sshConnectString[80];
    strcpy(sshConnectString, "ssh ");
    strcat(sshConnectString, sshUser);         /* Benutzername */
    strcat(sshConnectString, "@");
    strcat(sshConnectString, sshHost);         /* Hostname */
    strcat(sshConnectString, " -L ");
    strcat(sshConnectString, sshLocalPort);    /* Local Port */
    strcat(sshConnectString, ":localhost:3306 -f -N");

    /*int sshid = system(sshConnectString);*/

    /*printf("Rückgabewert von system %i\n", sshid);*/

    /*
    int sohnpid;
    ((sohnpid = fork()) == 0);
    {

        printf("Gelesen:\n");
        printf("sohnpid = %i:\n", sohnpid);

        exit(0);

    }*/




    connection = mysql_init(NULL);      /* Datenstruktur initalisieren */

    /* Die einzelnen Typen von mysql_real_connect() werden weiter unten erklärt */
    /* Später werden wir natürlich Variablen für Host, User, Passwort usw benutzen */
    if(mysql_real_connect(          /* Verbindung aufbauen */
            connection,         /* MySQL-Handler */
            "127.0.0.1",            /* Host-Name */
            "root",           /* User-Name */
            "ubuntu",        /* Passwort  */
            "weiterbildung",        /* Datenbank */
            1111,              /* Port, standard = 0 */
            NULL,               /* Socket, standard = NULL */
            0) == NULL) {           /* keine Flags */
        fprintf(stderr, "Verbindung schlug fehl: %u (%s)\n", mysql_errno(connection), mysql_error(connection));
        mysql_close(connection);
        exit(1);
    }

    /* muss hier erst mal genügen */
    sprintf(abfrage, "SELECT * FROM dozent");   /* Ich weiss, ziemlich krude */

    if((mysql_query(connection, abfrage) != 0)) {   /* SQL-Befehl ausführen */
        fprintf(stderr, "Abfrage schlug fehl: %u (%s)\n", mysql_errno(connection), mysql_error(connection));
        mysql_close(connection);
        exit(1);
    }

    ergebnis = mysql_store_result(connection);  /* Ergebnisse speichern */

    anz = mysql_num_fields(ergebnis);       /* Anzahl der Zeilen ermitteln */
    while((zeile = mysql_fetch_row(ergebnis))) {    /* Zeilen aus ergebnis abholen */
        for(i = 0; i < anz; i++)
            printf("%s ", zeile[i]);    /* Zeilen ausgeben */
        printf("\n");
    }

    mysql_free_result(ergebnis);            /* Ergebnisspeicher wieder freigeben */

    mysql_close(connection);            /* verbindung trennen */
    return 0;
}
