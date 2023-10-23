// a14.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"fa15.h"


int main()
{
    double U, R1, R2, L, tges, tsch;
    int NAnzT;
    double* tFld; 
    double* IFld;
    char szDatNam[13];
    FILE* af;


    puts("Einschalten eines RC-Netzwerks");
    puts("++++++++++++++++++++++++++++++");
    printf("\nSpannung U in V:\t\t\t");
    scanf("%lf", &U);
    FLUSH_STDIN;
    printf("\n Widerstand R1 in Ohm :\t\t\t");
    scanf("%lf", &R1);
    FLUSH_STDIN;
    printf("\n Widerstand R2 in kOhm :\t\t");
    scanf("%lf", &R2);
    FLUSH_STDIN;
    printf("\n Induktivitaet in mH :\t\t\t");
    scanf("%lf", &L);
    FLUSH_STDIN;
    printf("\n Gesamtzeit der Berechnung in ms :\t");
    scanf("%lf", &tges);
    FLUSH_STDIN;
    printf("\n Abstand der Rechnungen in ms :\t\t");
    scanf("%lf", &tsch);
    FLUSH_STDIN;

    NAnzT = (int)(1+ tges/tsch);
  
    tFld = (double*)malloc(NAnzT * sizeof(double));
    IFld = (double*)malloc(NAnzT * sizeof(double));
  
    printf("\n%d Zeiten t, fuer die Strom berechnet wird, in ms:\n", NAnzT);
    puts("-------------------------------------------------------");
 

    for (int x = 0; x < NAnzT; x++) {
        tFld[x] = 0.000 + x * tsch;
        if (x % 6 != 0)printf("%9.2lf", tFld[x]);
        else printf("\n%9.2lf", tFld[x]);
    }
    puts("\n\nBerechneter Strom I in mA zu diesen Zeiten:");
    puts("-------------------------------------------------------");
    
    for (int i = 0; i < NAnzT; i++)
    {
       

        IFld[i] = Strom(U, R1, R2*1e3, L*1e-3, tFld[i]*1e-3) *1e3;
        if (i % 6 != 0)printf("%9.2lf", IFld[i]);
        else printf("\n%9.2lf", IFld[i]);
    }
    printf("\n");
    puts("Speichern der Rechnung in eine Textdatei");
    puts("-------------------------------------------------------");
    printf("Name der Textdatei: ");
    scanf("%12s",&szDatNam);
    FLUSH_STDIN;
    szDatNam[strlen(szDatNam) ] = '\0';
    af = fopen(szDatNam, "wt");
  
    if (!af)
    {
        puts("\nDatei konnte nicht geöffnet werden,\n"
            "Programm wird mit ENTER beendet.!!!");
        getchar(); return 2;
    }
    fputs("Stromberechnungen zum Einschalten einer RL-Schaltung\n",af);
    fputs("ausgefuehrt durch: Evan Reynard Sukarman\n", af);
    fputs("****************************************************\n",af);
    fputs("\nSchaltungswerte",af);
    fputs("\n-------------------------------------------------------\n", af);
    fprintf(af,"U=%.2lf V, R1 =%.2lf Ohm, R2=%.2lf kOhm, L= %.2lf mH\n ", U, R1, R2, L);

    fprintf(af,"\n%d Zeiten t, fuer die Strom berechnet wird, in ms:\n", NAnzT);
    fputs("-------------------------------------------------------",af);


    for (int x = 0; x < NAnzT; x++) {
        tFld[x] = 0.000 + x * tsch;
        if (x % 6 != 0)fprintf(af,"%9.2lf", tFld[x]);
        else fprintf(af,"\n%9.2lf", tFld[x]);
    }
    fputs("\n\nBerechneter Strom I in mA zu diesen Zeiten:",af);
    fputs("\n-------------------------------------------------------",af);

    for (int i = 0; i < NAnzT; i++)
    {


        IFld[i] = Strom(U, R1, R2 * 1e3, L * 1e-3, tFld[i] * 1e-3) * 1e3;
        if (i % 6 != 0)fprintf(af,"%9.2lf", IFld[i]);
        else fprintf(af,"\n%9.2lf", IFld[i]);
    }
  
    free(tFld);
    free(IFld);
    fclose(af);
    printf("Daten erfolgreich in der Datei %s gespeichert",szDatNam);
   
}

