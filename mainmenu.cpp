#include <bits/stdc++.h>
#include <graphics.h>
#include <windows.h>
#include <ctime>
#include <stdio.h>
#include <MMSystem.h>
#include "playmenu.cpp"
#include "rules.cpp"
using namespace std;

int mainmenu()
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

    ///INITIALIZARE TEXT DE BUN VENIT;
    char inceptext[256];
    /*sirul "inceptext" va memora textul de bun venit*/
    strcpy(inceptext,"WELCOME TO AVANGARDIS!");
    /*atribuirea sirului "inceptext" textul dorit*/
    int textx=textwidth(inceptext);
    int texty=textheight(inceptext);
    /*cu cele 2 variabile vor salva dimensiunile textului
    (lungimea si latimea acestuia) din sirul de caractere "inceptext"*/
    settextstyle(BOLD_FONT,HORIZ_DIR,7);
    /*cu aceasta comanda voi seta fontul textului, adica va fide tip bold (ingrosat),
    desfasurarea (asezarea) va fi pe orizontala,
    iar dimensiunea (marimea) va fi de 7 ori mai mare decat ar fi normal */
    setcolor(YELLOW);
    /*cu aceasta comanda voi seta culoarea pe care o va avea textul, in acest caz galben (YELLOW) */
    outtextxy(mijx-5/2*textx,mijy-17*texty,inceptext);
    /*cu aceasta comanda voi afisa textul incepand de la un punct fix

    motivul pentru care incep afisarea textului imediat ce l-am initializat,
    este pentru a creea un suport pentru celelate texte

    astfel, daca nu afisam textul imediat ce l-am creat,
    textele de toate butoanele s-ar fi situat in partea dreapta a butoanelor,deci nu ar fi centrate
    */

    int distbut=latime_ecran/9;
    /* disbut reprezinta distanta dintre butoane masurata in pixeli */

    /// BUTONUL PLAY
    int lungbp=lungime_ecran/5;
    /*lungbp reprezinta lungimea pe care o are butonul de play masurata in pixeli */
    int latbp=latime_ecran/6;
    /*latbut reprezinta latimea pe care o are butonul de play masurata in pixeli */
    int bpix=mijx-lungbp/2;
    int bpiy=mijy-latbp/2-distbut;
    int bpfx=mijx+lungbp/2;
    int bpfy=mijy+latbp/2-distbut;
    /* aceste 4 variabile reprezinta coordonatele primului si ultimului varf
    aflate pe diagonala principala a poligolului pe care il vor forma  */
    char playtext[256];
    /* declar sirul pentru care voi atribui textul de "PLAY" */
    strcpy(playtext,"PLAY");
    /* comanda de atribuire a textului */
    int textpx=textwidth(playtext);
    int textpy=textheight(playtext);
    /* 2 variabile prin care memorez dimensiunile textului */
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    /* comanda prin care i se atribuyie textului un anumit stil, font ingrosat,
    desfasurare orizontala, dimensinea caracterelor e de 5 ori mai mare decat ar fi in mod normal */
    setcolor(YELLOW);
    /* comanda de atribuire a unei culori textului */
    outtextxy(bpix+(bpfx-bpix)/2-textpx/2,bpiy+(bpfy-bpiy)/2-textpy/2,playtext);
    /* comanda pentru afisarea textului, in asa maniera incat sa fie centrata in interiorul butonului

    motivul pentru care incep afisarea textului imediat ce l-am initializat,
    este pentru a creea un suport de stabilitate pentru textul aflat in cele 2 animatii

    astfel, daca nu afisam textul imediat ce l-am creat,
    textul butonului s-ar fi situat in partea dreapta a acestuia,deci nu ar fi centrat
    */



    /// BUTONUL RULES
    int lungbr=lungime_ecran/5;
    int latbr=latime_ecran/6;
    int brix=mijx-lungbr/2;
    int briy=mijy-latbr/2+distbut;
    int brfx=mijx+lungbr/2;
    int brfy=mijy+latbr/2+distbut;
    char ruletext[256];
    strcpy(ruletext,"RULES");
    int textrx=textwidth(ruletext);
    int textry=textheight(ruletext);
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    setcolor(YELLOW);
    outtextxy(brix+(brfx-brix)/2-textrx/2,briy+(brfy-briy)/2-textry/2,ruletext);
    /* se aplica aceeasi mecanica de la BUTONUL PLAY */


    /// BUTONUL QUIT
    int lungbc=lungime_ecran/5;
    int latbc=latime_ecran/6;
    int bcix=mijx-lungbr/2;
    int bciy=mijy-latbr/2+3*distbut;
    int bcfx=mijx+lungbr/2;
    int bcfy=mijy+latbr/2+3*distbut;
    char credittext[256];
    strcpy(credittext,"QUIT");
    int textcx=textwidth(ruletext);
    int textcy=textheight(ruletext);
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    setcolor(YELLOW);
    outtextxy(bcix+(bcfx-bcix)/2-textcx/3*2,bciy+(bcfy-bciy)/2-textcy/2,credittext);
    /* se aplica aceeasi mecanica de la BUTONUL PLAY */


    int page=0;
    /* page va memora pagina pecare se va desena */
    int timeless=2;
    /* timeless va memora viteza de redare a desenelor */
    int viteza=5;
    /* viteza va memora viteza de deplasare a butoanelor in decursul animatiei */
    int cabral=0;
    /* variabila cabral va memora optiunea utilizatorului*/

    ///SETARI CURSOR
    POINT cursor_poz;
    /* cursor_poz va memora pozitia cursorului mouse-ului la un anumit moment */

    ///APARITIE TEXT
    for(int i=1; i<=mijy-17*texty; i=i+viteza-2)
    {
        /* structura repetitiva for este utilizata pentru a face textul sa se deplaseze
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
        settextstyle(BOLD_FONT,HORIZ_DIR,7);
        setcolor(YELLOW);
        setbkcolor(RED);
    /*cu aceasta comanda voi seta culoarea backgroundului pe care o va avea textul, in acest caz rosu (RED)
    pentru a evita spatiul negru din jurul textlui */
        outtextxy(mijx-5/2*textx,i,inceptext);
        /* aceeasi mecanica ca si la initializare, doar ca se afiseaza textul la o anumita pozitie i*/
        page=1-page;
        /* page va avea doar 2 valori, astfel se vor folosi doar 2 pagini, una anterioada care va fi afisata utilizatorului,
        iar a doua pagina va fi stearga si redesenata

        tranzitia dintre cele 2 pagini va elimita efectul de glich pecare l-ar fi avut animatia */
        delay(timeless);
        /* aceasta comanda ingheata programul pentru cateva milisecunde,
        in functie de ce valoare are timeless */
    }

    ///APARITIE PLAY
    for(int i=1; i<=bpix; i=i+viteza)
    {
        /* structura repetitiva for este utilizata pentru a face butonul sa se deplaseze
           din partea stanga a ecranului, pana in pozitia stabilita in initializare*/
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();
        readimagefile("bk.jpg",0,0,lungime_ecran,latime_ecran);
        ///AFISARE TEXT
        settextstyle(BOLD_FONT,HORIZ_DIR,7);
        setcolor(YELLOW);
        /* pricipiul este acelasi ca si la TEXT SPAWN */
        setbkcolor(RED);
        outtextxy(mijx-5/2*textx,mijy-17*texty,inceptext);
        /* se afiseaza textul de bun venit in pozitia optima */
        ///PLAY
         setbkcolor(GREEN);
        setfillstyle(SOLID_FILL,GREEN);
        bar(i,bpiy,i+lungbp,bpfy);
        /* se stabileste tipul de culoare a polinomului ce va reprezenta butonul de PLAY

        se constuieste un dreptunghi de la primul varf pana la ultimul varf de pe diagonala principala */
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(YELLOW);
        outtextxy(i+lungbp/2-textpx/3,bpiy+(bpfy-bpiy)/2-textpy/3,playtext);
        /* aceeasi mecanica ca si la initializare, doar ca se afiseaza textul la o anumita pozitie i*/
        page=1-page;
        delay(timeless);
        /* pricipiul este acelasi ca si la APARITIE TEXT  */
    }


    ///APARITIE RULE
    for(int i=lungime_ecran-lungbc; i>=brix; i=i-viteza)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();
        readimagefile("bk.jpg",0,0,lungime_ecran,latime_ecran);
        ///AFISARE TEXT
        settextstyle(BOLD_FONT,HORIZ_DIR,7);
        setcolor(YELLOW);
        setbkcolor(RED);
        outtextxy(mijx-5/2*textx,mijy-17*texty,inceptext);
        ///AFISARE BUTON PLAY
        setfillstyle(SOLID_FILL,GREEN);
        bar(bpix,bpiy,bpfx,bpfy);
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(YELLOW);
        setbkcolor(GREEN);
        outtextxy(bpix+(bpfx-bpix)/2-textpx/3,bpiy+(bpfy-bpiy)/2-textpy/3,playtext);
        /* se afiseaza butonul de PLAY in pozitia initiala*/
        bar(i,briy,i+lungbr,brfy);
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(YELLOW);
        setbkcolor(GREEN);
        outtextxy(i+lungbp/2-textrx/2,briy+(brfy-briy)/2-textry/2,ruletext);
        page=1-page;
        delay(timeless);
    }
    /* in rest principiul este acelasi ca si in cazul APARITIE PLAY  */


    /// APARITIE QUIT
    for(int i=1; i<=bcix; i=i+viteza)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();
        readimagefile("bk.jpg",0,0,lungime_ecran,latime_ecran);
        ///AFISARE TEXT
        settextstyle(BOLD_FONT,HORIZ_DIR,7);
        setcolor(YELLOW);
        setbkcolor(RED);
        outtextxy(mijx-5/2*textx,mijy-17*texty,inceptext);
        /// AFISARE BUTON PLAY SI RULES
        setfillstyle(SOLID_FILL,GREEN);
        bar(bpix,bpiy,bpfx,bpfy);
        bar(brix,briy,brfx,brfy);
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(YELLOW);
        setbkcolor(GREEN);
        outtextxy(bpix+(bpfx-bpix)/2-textpx/3,bpiy+(bpfy-bpiy)/2-textpy/3,playtext);
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(YELLOW);
        outtextxy(brix+(brfx-brix)/2-textrx/2,briy+(brfy-briy)/2-textry/2,ruletext);
        /* se afiseaza butonul de PLAY si butonul de RULES in pozitia initiala*/

        bar(i,bciy,i+lungbc,bcfy);
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(YELLOW);
        outtextxy(i+lungbp/2-textcx/2,bciy+(bcfy-bciy)/2-textcy/2,credittext);
        page=1-page;
        delay(timeless);
    }
    /* in rest principiul este acelasi ca si in cazul  APARITIE PLAY  */
    ///FREEROOM
    while(cabral==0)
    {
        /* cat timp utilizatorul nu a selectat vreun buton, se genereaza in continuu se deseneaza o pagina */
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();
        /* acelasi principiu ca si la animatie */
        GetCursorPos(&cursor_poz);
        /* aceasta comanda reda pozitia la care se afla cursorul mouse-ului in acel moment */
        readimagefile("bk.jpg",0,0,lungime_ecran,latime_ecran);
        ///AFISARE TEXT
        settextstyle(BOLD_FONT,HORIZ_DIR,7);
        setcolor(YELLOW);
        setbkcolor(RED);
        outtextxy(mijx-5/2*textx,mijy-17*texty,inceptext);
        ///AFISAREA BUTONULUI DE PLAY
        setfillstyle(SOLID_FILL,GREEN);
        bar(bpix,bpiy,bpfx,bpfy);
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(YELLOW);
        setbkcolor(GREEN);
        outtextxy(bpix+(bpfx-bpix)/2-textpx/3,bpiy+(bpfy-bpiy)/2-textpy/3,playtext);
        ///AFISAREA BUTONULUI DE RULES
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(YELLOW);
        bar(brix,briy,brfx,brfy);
        outtextxy(brix+(brfx-brix)/2-textrx/2,briy+(brfy-briy)/2-textry/2,ruletext);
        setfillstyle(SOLID_FILL,GREEN);
        ///AFISAREA BUTONULUI DE QUIT
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(YELLOW);
        bar(bcix,bciy,bcfx,bcfy);
        outtextxy(bcix+(bcfx-bcix)/2-textcx/2,bciy+(bcfy-bciy)/2-textcy/2,credittext);
        /*acelasi pricipiu ca si la initializare */
        if(GetAsyncKeyState(VK_LBUTTON))
        {
            /* daca s-a apasat cumva click, verifica urmatoarele 3 lucruri */
            if(cursor_poz.x>=bpix&&cursor_poz.x<=bpfx&&cursor_poz.y>=bpiy&&cursor_poz.y<=bpfy)
            {
                /* daca cursorul se afla in interiorul butonului de PLAY,
                  daca da atunci optiunea utilizatorului (cabral) devine 1 (primul buton) */
                cabral=1;
            }
            if(cursor_poz.x>=brix&&cursor_poz.x<=brfx&&cursor_poz.y>=briy&&cursor_poz.y<=brfy)
            {
                /* daca cursorul se afla in interiorul butonului de RULES,
                   daca da atunci optiunea utilizatorului (cabral) devine 2 (al doilea  buton) */
                cabral=2;

            }
            if(cursor_poz.x>=bcix&&cursor_poz.x<=bcfx&&cursor_poz.y>=bciy&&cursor_poz.y<=bcfy)
            {
                /* daca cursorul se afla in interiorul butonului de QUIT,
                   daca da programul se inchide, deci si aplicatia se va inchide  */
                return 0;
            }
        }
        page=1-page;
        delay(10);
    }
    /* in rest este aceeasi mecanica ca si la animatie */
    closegraph();
    /* se inchide toate paginile deschise, astfel sa nu fie deschise
    prea multe pagini, deci ca sa nu scada performanta jocului*/
    if(cabral==1)
        playmenu();
    else if(cabral==2)
    {
        rules();
        mainmenu();
    }
    /*daca optiunea utilizatorului este 1 atunci se dechide meniul de play

    daca optiunea utilizatorului este 2 atunci se va deschide meniul de rules
    si se va relua programul din meniul principal*/
    return 0;
}

