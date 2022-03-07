#include <bits/stdc++.h>
#include <windows.h>
#include <graphics.h>
#include "stagiu1.cpp"
#include "stagiu2.cpp"
#include "stagiu3.cpp"
using namespace std;

int playmenu()
{
    ///INITIALIZARE PAGINA GRAFICA FULL SCREEEN
    DWORD lungime_ecran =GetSystemMetrics(SM_CXSCREEN);
    DWORD latime_ecran =GetSystemMetrics(SM_CYSCREEN);
    /*intializez 2 variabile pentru care le voi rezolutia ecranului*/
    initwindow(lungime_ecran,latime_ecran,"",-3,-3);

    ///COORDONATELE CENTRULUI PAGINII GRAFICE
    int mijx=lungime_ecran/2;
    int mijy=latime_ecran/2;
    /* se salveaza coordonatele din centru ecranului*/
    int lbut=lungime_ecran/6;
    /*lbut reprezinta lungimea pe care o are butonul masurata in pixeli */
    int ltbut=latime_ecran/6;
    /*ltbut reprezinta latimea pe care o are butonul masurata in pixeli */
    int disbut=latime_ecran/9.1;
    /* disbut reprezinta distanta dintre butoane masurata in pixeli */
    struct button
    {
        int xi;
        int yi;
        int xf;
        int yf;
    } but;
    but.xi=mijx/3;
    but.yi=3*mijy/6;
    but.xf=but.xi+lbut;
    but.yf=but.yi+ltbut;
    /* folosesc aceasta structura pentru a creea coodonatele primului si ultimului varf,
     aflate pe diagonala principala, al primului buton

     creez doar primul buton in asa fel incat toate celelalte butoane sa depinda depozitia
      si dimensiule primului buton, pentru a fi mai usor de editat
     */

    ///BUTON 1
    setfillstyle(SOLID_FILL,GREEN);
    bar(but.xi,but.yi,but.xf,but.yf);
    /* se stabileste tipul de culoare a polinomului ce va reprezenta butonul

     se constuieste un dreptunghi de la primul varf pana la ultimul varf de pe diagonala principala */
    char lvl1text[256];
    /*sirul "lvl1text" va memora textul corespunzator */
    strcpy(lvl1text,"LEVEL 1");
    /*atribuirea sirului "lvl1text" textul dorit*/
    int text1x=textwidth(lvl1text);
    int text1y=textheight(lvl1text);
    /*cu cele 2 variabile vor salva dimensiunile textului
    (lungimea si latimea acestuia) din sirul de caractere "inceptext"*/
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    /* comanda prin care i se atribuyie textului un anumit stil, font ingrosat,
      desfasurare orizontala, dimensinea caracterelor e de 5 ori mai mare decat ar fi in mod normal */
    setcolor(YELLOW);
    /*cu aceasta comanda voi seta culoarea pe care o va avea textul, in acest caz galben (YELLOW) */
    outtextxy(but.xi+(but.xf-but.xi)/2-5*text1x/3,but.yi+(but.yf-but.yi)/2-4*text1y/3,lvl1text);
    /*cu aceasta comanda voi afisa textul incepand de la un punct fix

      motivul pentru care incep afisarea textului imediat ce l-am initializat,
      este pentru a creea un suport pentru celelate texte

      astfel, daca nu afisam textul imediat ce l-am creat,
      textele de toate butoanele s-ar fi situat in partea dreapta a butoanelor,deci nu ar fi centrate
      */


    ///BUTON 2
    setfillstyle(SOLID_FILL,GREEN);
    setcolor(GREEN);
    bar(but.xi+lbut+disbut,but.yi,but.xf+disbut+lbut,but.yf);
    char lvl2text[256];
    strcpy(lvl2text,"LEVEL 2");
    int text2x=textwidth(lvl2text);
    int text2y=textheight(lvl2text);
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    setcolor(YELLOW);
    outtextxy(but.xi+lbut+disbut+(but.xf-but.xi)/2-5*text1x/3,but.yi+(but.yf-but.yi)/2-4*text1y/3,lvl2text);
    /* se aplica acelasi principiu ca si in cazul BUTON 1, BUTON 2 fiind o derivata a acestuia*/

    ///BUTON 3
    setfillstyle(SOLID_FILL,GREEN);
    setcolor(GREEN);
    bar(but.xi+2*lbut+2*disbut,but.yi,but.xf+2*disbut+2*lbut,but.yf);
    char lvl3text[256];
    strcpy(lvl3text,"LEVEL 3");
    int text3x=textwidth(lvl3text);
    int text3y=textheight(lvl3text);
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    setcolor(YELLOW);
    outtextxy(but.xi+2*lbut+2*disbut+(but.xf-but.xi)/2-5*text1x/3,but.yi+(but.yf-but.yi)/2-4*text1y/3,lvl3text);
    /* se aplica acelasi principiu ca si in cazul BUTON 1, BUTON 3 fiind o derivata a acestuia*/

    ///BUTON QUIT
    setfillstyle(SOLID_FILL,GREEN);
    setcolor(GREEN);
    int lbutb=lungime_ecran/13;
    int ltbutb=latime_ecran/10;
    bar(10,10,2*lbutb,ltbutb);
    char backtext[256];
    strcpy(backtext,"QUIT");
    int textbx=textwidth(backtext);
    int textby=textheight(backtext);
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    setcolor(YELLOW);
    outtextxy(lbutb/2-5*text1x/3+10,ltbutb/2-4*text1y/3,backtext);
    /* se aplica acelasi principiu ca si in cazul BUTON 1, BUTON QUIT fiind o derivata a acestuia*/

    POINT mouse;
    /* mouse va memora pozitia cursorului mouse-ului la un anumit moment */
    int timeless=10;
    /* timeless va memora viteza de redare a desenelor */
    int viteza=3;
    /* viteza va memora viteza de deplasare a butoanelor in decursul animatiei */
    int cabral=0;
    /* variabila cabral va memora obtiunea utilizatorului*/
    int page=0;
    /* page va memora pagina pecare se va desena */


    ///ANIMATIIE
    for(int i=1; i<=but.yi; i=i+viteza)
    {
        /* structura repetitiva for este utilizata pentru a face ca cele trei butoane sa se deplaseze
               de la partea de sus a ecranului, pana in pozitia stabilita in initializare*/
        setactivepage(page);
        /* seteaza pagina pe care se va desena */
        setvisualpage(1-page);
        /* seteaza ca pagina pe care o va vizualiza observatorul sa fie cea precedenta */
        cleardevice();
        /* sterge tot ce este pe pagina activa */
        readimagefile("bk.jpg",0,0,lungime_ecran,latime_ecran);
        /* backgroundul programului va fi o imat=gine cu dimensiunea de 1x1 pixeli
              pentru a face citirea si afisarea mai rapida,
              astfel animatia va derula mai usor si mai eficient */

        ///BUTON 1
        setfillstyle(SOLID_FILL,GREEN);
        setcolor(GREEN);
        bar(but.xi,i,but.xf,i+ltbut);
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setbkcolor(GREEN);
    /*cu aceasta comanda voi seta culoarea backgroundului pe care o va avea textul, in acest caz verde (GREEN)
    pentru a evita spatiul negru din jurul textlui */
        setcolor(YELLOW);
        outtextxy(but.xi+(but.xf-but.xi)/2-5*text1x/3,i+ltbut/2-4*text1y/3,lvl1text);
        ///BUTON 2
        setfillstyle(SOLID_FILL,GREEN);
        setcolor(GREEN);
        bar(but.xi+lbut+disbut,i,but.xf+disbut+lbut,i+ltbut);
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(YELLOW);
         setbkcolor(GREEN);
        outtextxy(but.xi+lbut+disbut+(but.xf-but.xi)/2-5*text1x/3,i+ltbut/2-4*text1y/3,lvl2text);
        ///BUTON 3
        setfillstyle(SOLID_FILL,GREEN);
        setcolor(GREEN);
        bar(but.xi+2*lbut+2*disbut,i,but.xf+2*disbut+2*lbut,i+ltbut);
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(YELLOW);
         setbkcolor(GREEN);
        outtextxy(but.xi+2*lbut+2*disbut+(but.xf-but.xi)/2-5*text1x/3,i+ltbut/2-4*text1y/3,lvl3text);
        /* stilul celor trei butoane este acelasi, difera doar pozitia acestora in functie de distanta
        la care se afla de fiecare buton, astfel doar primul buton va fi mutat, restul se vor situa la
        acelasi nivel cu primu, dar la coordonate orizontale diferite, acestea ramanand aceleasi

        in rest mecanica este aceeasi ca si la intializare */
        page=1-page;
        /* page va avea doar 2 valori, astfel se vor folosi doar 2 pagini, una anterioada care va fi afisata utilizatorului,
              iar a doua pagina va fi stearga si redesenata

              tranzitia dintre cele 2 pagini va elimita efectul de glich pecare l-ar fi avut animatia */
        delay(timeless);
        /* aceasta comanda ingheata programul pentru cateva milisecunde,
             in functie de ce valoare are timeless */
    }

///FREEDOM
    while(cabral==0)
    {

        /* cat timp utilizatorul nu a selectat vreun buton, se genereaza in continuu se deseneaza o pagina */
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();
        /* acelasi principiu ca si la animatie */
        GetCursorPos(&mouse);
        /* aceasta comanda reda pozitia la care se afla cursorul mouse-ului in acel moment */
        readimagefile("bk.jpg",0,0,lungime_ecran,latime_ecran);

        ///BUTON 1
        setfillstyle(SOLID_FILL,GREEN);
        setcolor(GREEN);
        bar(but.xi,but.yi,but.xf,but.yf);
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(YELLOW);
         setbkcolor(GREEN);
        outtextxy(but.xi+(but.xf-but.xi)/2-5*text1x/3,but.yi+(but.yf-but.yi)/2-4*text1y/3,lvl1text);

        ///BUTON 2
        setfillstyle(SOLID_FILL,GREEN);
        setcolor(GREEN);
        bar(but.xi+lbut+disbut,but.yi,but.xf+disbut+lbut,but.yf);
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(YELLOW);
         setbkcolor(GREEN);
        outtextxy(but.xi+lbut+disbut+(but.xf-but.xi)/2-5*text1x/3,but.yi+(but.yf-but.yi)/2-4*text1y/3,lvl2text);


        ///BUTON 3
        setfillstyle(SOLID_FILL,GREEN);
        setcolor(GREEN);
        bar(but.xi+2*lbut+2*disbut,but.yi,but.xf+2*disbut+2*lbut,but.yf);
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(YELLOW);
         setbkcolor(GREEN);
        outtextxy(but.xi+2*lbut+2*disbut+(but.xf-but.xi)/2-5*text1x/3,but.yi+(but.yf-but.yi)/2-4*text1y/3,lvl3text);

        ///BUTON BACK
        setfillstyle(SOLID_FILL,GREEN);
        setcolor(GREEN);
        bar(10,10,2*lbutb,ltbutb);
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(YELLOW);
        outtextxy(2*lbutb/2-textbx/2,ltbutb/2-textby/2,backtext);
        /*acelasi pricipiu ca si la initializare */

        if(GetAsyncKeyState(VK_LBUTTON))
        {
            /* daca s-a apasat cumva click, verifica urmatoarele 4 lucruri */
            if(mouse.x>=but.xi&&mouse.x<=but.xf&&mouse.y>=but.yi&&mouse.y<=but.yf)
            {
                /* daca cursorul se afla in interiorul butonului de LEVEL 1,
                  daca da atunci optiunea utilizatorului (cabral) devine 1 (primul buton) */
                cabral=1;

            }
            if(mouse.x>=but.xi+lbut+disbut&&mouse.x<=but.xf+disbut+lbut&&mouse.y>=but.yi&&mouse.y<=but.yf)
            {
                /* daca cursorul se afla in interiorul butonului de LEVEL 2,
                               daca da atunci optiunea utilizatorului (cabral) devine 2 (al doilea buton) */
                cabral=2;

            }

            if(mouse.x>=but.xi+2*lbut+2*disbut&&mouse.x<=but.xf+2*disbut+2*lbut&&mouse.y>=but.yi&&mouse.y<=but.yf)
            {
                /* daca cursorul se afla in interiorul butonului de LEVEL 3,
                               daca da atunci optiunea utilizatorului (cabral) devine 3 (al treilea buton) */
                cabral=3;

            }
            if(mouse.x>=10&&mouse.x<=2*lbutb&&mouse.y>=10&&mouse.y<=ltbutb)
            {
                /* daca cursorul se afla in interiorul butonului de QUIT,
                            daca da programul se inchide, deci si aplicatia se va inchide  */
                return 0;

            }
        }
        page=1-page;
        delay(timeless);
    }
    /* in rest este aceeasi mecanica ca si la animatie */
    closegraph();
    /* se inchide toate paginile deschise, astfel sa nu fie deschise
      prea multe pagini, deci ca sa nu scada performanta jocului*/
    if(cabral==1)
        stagiu1();
    else if(cabral==2)
        stagiu2();
    else if(cabral==3)
        stagiu3();
    /*daca optiunea utilizatorului este 1 atunci se dechide stagiul 1

    daca optiunea utilizatorului este 2 atunci se dechide stagiul 2

    daca optiunea utilizatorului este 3 atunci se dechide stagiul 3

    */
    return 0;
}

