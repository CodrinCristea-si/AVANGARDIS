#include <bits/stdc++.h>
#include <graphics.h>
#include <windows.h>
using namespace std;

int rules()
{
    int cabral=0;
    ///INITIALIZARE ECRAN
    DWORD lungime_ecran=GetSystemMetrics(SM_CXSCREEN);
    DWORD latime_ecran=GetSystemMetrics(SM_CYSCREEN);
    /*intializez 2 variabile pentru care le voi rezolutia ecranului*/
    initwindow(lungime_ecran,latime_ecran,"",-3,-3);

    ///COORDONATELE CENTRULUI PAGINII GRAFICE
    int mijx=lungime_ecran/2;
    int mijy=latime_ecran/2;
     /* se salveaza coordonatele din centru ecranului*/

    int lungime=lungime_ecran/6;
    /*lungime reprezinta lungimea pe care o are butonul masurata in pixeli */
    int latime=latime_ecran/7;
    /*latime reprezinta lungimea pe care o are butonul masurata in pixeli */
    struct buton
    {
        int xi;
        int yi;
    } br;
    br.xi=mijx/2;
    br.yi=mijy/2;
    /* folosesc aceasta structura pentru a creea coodonatele primului varf,
     aflat pe diagonala principala, al primului buton, al doilea varf fiind
     in functie de lungimea si latimea butonului

     creez doar primul buton in asa fel incat toate celelalte butoane sa depinda depozitia
      si dimensiule primului buton, pentru a fi mai usor de editat
     */
    /// BUTON ROMANA
    char textr[256]= {"ROMANA"};
    /*sirul "textr" va memora textul "ROMANA" */
    setfillstyle(SOLID_FILL,YELLOW);
    bar(br.xi,br.yi,br.xi+lungime,br.yi+latime);
     /* se stabileste tipul de culoare a polinomului ce va reprezenta butonul

     se constuieste un dreptunghi de la primul varf pana la ultimul varf de pe diagonala principala */
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    /* comanda prin care i se atribuyie textului un anumit stil, font ingrosat,
      desfasurare orizontala, dimensinea caracterelor e de 5 ori mai mare decat ar fi in mod normal */
    setcolor(BLUE);
    /*cu aceasta comanda voi seta culoarea pe care o va avea textul, in acest caz albastru (BLUE) */
    setbkcolor(YELLOW);
    /*cu aceasta comanda voi seta culoarea backgroundului pe care o va avea textul, in acest caz galben (YELLOW)
    pentru a evita spatiul negru din jurul textlui */

    outtextxy(br.xi+lungime/2-textwidth(textr)/2, br.yi+latime/2-textheight(textr)/2,textr);
    /*cu aceasta comanda voi afisa textul incepand de la un punct fix

      motivul pentru care incep afisarea textului imediat ce l-am initializat,
      este pentru a creea un suport pentru celelate texte

      astfel, daca nu afisam textul imediat ce l-am creat,
      textele de toate butoanele s-ar fi situat in partea dreapta a butoanelor,deci nu ar fi centrate
      */


    /// BUTON ENGLEZA
    char texte[256]= {"ENGLEZA"};
    setfillstyle(SOLID_FILL,YELLOW);
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    setcolor(BLUE);
    bar(br.xi,br.yi+3*latime,br.xi+lungime,br.yi+4*latime);
    setbkcolor(YELLOW);
    outtextxy(br.xi+lungime/2-textwidth(texte)/2, br.yi+7*latime/2-textheight(texte)/2,texte);
/* se aplica acelasi principiu ca si in cazul BUTTON 1, QUIT BUTTON fiind o derivata a acestuia*/

    POINT mouse;
     /* mouse va memora pozitia cursorului mouse-ului la un anumit moment */
    int page=0;
    /* page va memora pagina pecare se va desena */
    int aparitii[5]= {0};
/* vectorul aparitii va fi folosit drept un contor care va asigura faptul ca imaginile nu se vor afisa de mai multe ori */

    while(cabral==0)
    {/* cat timp utilizatorul nu a selectat vreun buton, se genereaza in continuu se deseneaza o pagina */
        setactivepage(page);
         /* seteaza pagina pe care se va desena */
        setvisualpage(1-page);
        /* seteaza ca pagina pe care o va vizualiza observatorul sa fie cea precedenta */
        cleardevice();
        /* sterge tot ce este pe pagina activa */
        GetCursorPos(&mouse);
/* aceasta comanda reda pozitia la care se afla cursorul mouse-ului in acel moment */
        readimagefile("bk.jpg",0,0,lungime_ecran,latime_ecran);
        /* backgroundul programului va fi o imat=gine cu dimensiunea de 1x1 pixeli
              pentru a face citirea si afisarea mai rapida,
              astfel animatia va derula mai usor si mai eficient */
        ///ROMANA
        setfillstyle(SOLID_FILL,YELLOW);
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(BLUE);
        bar(br.xi,br.yi,br.xi+lungime,br.yi+latime);
        setbkcolor(YELLOW);
        outtextxy(br.xi+lungime/2-textwidth(textr)/2, br.yi+latime/2-textheight(textr)/2,textr);
        ///ENGLEZA
        setfillstyle(SOLID_FILL,YELLOW);
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(BLUE);
        bar(br.xi,br.yi+3*latime,br.xi+lungime,br.yi+4*latime);
        setbkcolor(YELLOW);
        outtextxy(br.xi+lungime/2-textwidth(texte)/2, br.yi+7*latime/2-textheight(texte)/2,texte);
 /*acelasi pricipiu ca si la initializare */
        if(GetAsyncKeyState(VK_LBUTTON))
        {/* daca s-a apasat cumva click, verifica urmatoarele 2 lucruri */
            if(mouse.x>=br.xi&&mouse.x<=br.xi+lungime&&mouse.y>=br.yi&&mouse.y<=br.yi+latime)
            {                /* daca cursorul se afla in interiorul butonului de ROMANA,
                  daca da atunci optiunea utilizatorului (cabral) devine 1 (primul buton) */
                cabral=1;
            }
            if(mouse.x>=br.xi&&mouse.x<=br.xi+lungime&&mouse.y>=br.yi+3*latime&&mouse.y<=br.yi+4*latime)
            {/* daca cursorul se afla in interiorul butonului de ENGLEZA,
                               daca da atunci optiunea utilizatorului (cabral) devine 2 (al doilea buton) */
                cabral=2;
            }
        }

        page=1-page;
                /* page va avea doar 2 valori, astfel se vor folosi doar 2 pagini, una anterioada care va fi afisata utilizatorului,
              iar a doua pagina va fi stearga si redesenata

              tranzitia dintre cele 2 pagini va elimita efectul de glich pecare l-ar fi avut animatia */
        delay(10);
          /* aceasta comanda ingheata programul pentru 10 milisecunde*/
    }
    closegraph();
    /* se inchide toate paginile deschise, astfel sa nu fie deschise
      prea multe pagini, deci ca sa nu scada performanta jocului*/
    if(cabral==1)
    {/* daca utilizatorul a ales limba romana*/
        int gata=0;
        /* este un contor care va verifica daca utilizatorul a terminat de citit toate instructiunile*/
        char textc[256]= {"APASA SAGEATA DREAPTA PENTRU A TRECE LA PAGINA URMATOARE"};
        /*sirul de caractere va memora un text care va fi afisat pe tot parcursul animatiei,
         cu scopul de a indruma si ajuta utilizatorul */
        initwindow(lungime_ecran,latime_ecran,"",-3,-3);
        while(gata==0)
        {/* cat timp utilizatorulnu a terminat de citit*/
            settextstyle(1,HORIZ_DIR,2);
            setcolor(WHITE);
            outtextxy(mijx-textwidth(textc)/2,latime_ecran-50-textheight(textc)/2,textc);
            /* se afiseaza textul ajutator*/
            if(aparitii[0]==0)
                readimagefile("regula 1 ro-gigapixel.jpg",0,0,lungime_ecran,latime_ecran);
                /*daca utilizatorul nu a apasat tasta sageata "dreapta", se va afisa prima imagine cu instructiuni*/
            if(GetAsyncKeyState(VK_RIGHT))
            {/* daca a fost apasata tasta sageata "dreapta", inseamna ca se doreste trecerea la alta pagina*/
                if(aparitii[0]==0)
                {
                    aparitii[0]=1;
                    getch();
                }
                /* prin acest if se asigura faptul ca prima imagine nu va fi asfisata incontinuu*/
                if(aparitii[1]==0)
                {/*daca nu a fost afisata prima poza, se afiseaza*/
                    getch();
                    cleardevice();
                    /* se curata pagina precendenta pentru a fi redata o noua imagine*/
                    readimagefile("regula 2 ro-gigapixel.jpg",0,0,lungime_ecran,latime_ecran);
                    /* se afiseaza imaginea pe tot ecranul*/
                    outtextxy(mijx-textwidth(textc)/2,latime_ecran-50-textheight(textc)/2,textc);
                    /* se afiseaza textul ajutator*/
                    aparitii[1]=1;
                    /* aparitii de poza respectiva se face 1 pentru a nu semaiafisa o data*/
                     getch();
                     /* se foloseste aceasta comanda pentru a da posibilitatea utilizatorului
                     de a citi cat timp are nevoie*/
                }
                else if(aparitii[2]==0)
                {
                    getch();
                    cleardevice();
                    readimagefile("regula 3 ro-gigapixel.jpg",0,0,lungime_ecran,latime_ecran);
                    outtextxy(mijx-textwidth(textc)/2,latime_ecran-50-textheight(textc)/2,textc);

                    aparitii[2]=1;
                    getch();
                }
                else if(aparitii[3]==0)
                {
                    getch();
                    cleardevice();
                    readimagefile("regula 4 ro-gigapixel.jpg",0,0,lungime_ecran,latime_ecran);
                    outtextxy(mijx-textwidth(textc)/2,latime_ecran-50-textheight(textc)/2,textc);

                    aparitii[3]=1;
                    getch();
                }
                else if(aparitii[4]==0)
                {
                    getch();
                    cleardevice();
                    readimagefile("regula 5 ro-gigapixel.jpg",0,0,lungime_ecran,latime_ecran);
                    outtextxy(mijx-textwidth(textc)/2,latime_ecran-50-textheight(textc)/2,textc);

                    aparitii[4]=1;
                    gata=1;
                    getch();
                }
                /* acelasi principiu este la toate if-urile*/
            }
        }
    }
    else if (cabral==2)
    {/*daca utilizatorul a selectat ENGLEZA

        se aplica acelasi mecanism ca in cazul sectiunii de ROMANA*/

        int gata=0;
        char textc[256]= {"PRESS THE RIGHT ARROW TO GO TO THE NEXT PAGE"};
        initwindow(lungime_ecran,latime_ecran,"",-3,-3);
        while(gata==0)
        {
            settextstyle(1,HORIZ_DIR,2);

            setcolor(WHITE);
            outtextxy(mijx-textwidth(textc)/2,latime_ecran-25-textheight(textc)/2,textc);
            if(aparitii[0]==0)
                readimagefile("regula 1 eng-gigapixel.jpg",0,0,lungime_ecran,latime_ecran);
            if(GetAsyncKeyState(VK_RIGHT))
            {
                if(aparitii[0]==0)
                {
                    aparitii[0]=1;
                    getch();
                }
                if(aparitii[1]==0)
                {
                    getch();
                    cleardevice();
                    readimagefile("regula 2 eng-gigapixel.jpg",0,0,lungime_ecran,latime_ecran);
                    outtextxy(mijx-textwidth(textc)/2,latime_ecran-25-textheight(textc)/2,textc);
                    aparitii[1]=1;
                    getch();
                }
                else if(aparitii[2]==0)
                {
                    getch();
                    cleardevice();
                    readimagefile("regula 3 eng-gigapixel.jpg",0,0,lungime_ecran,latime_ecran);
                    outtextxy(mijx-textwidth(textc)/2,latime_ecran-25-textheight(textc)/2,textc);

                    aparitii[2]=1;
                    getch();
                }
                else if(aparitii[3]==0)
                {
                    getch();
                    cleardevice();
                    readimagefile("regula 4 eng-gigapixel.jpg",0,0,lungime_ecran,latime_ecran);
                    outtextxy(mijx-textwidth(textc)/2,latime_ecran-25-textheight(textc)/2,textc);

                    aparitii[3]=1;
                    getch();
                }
                else if(aparitii[4]==0)
                {
                    getch();
                    cleardevice();
                    readimagefile("regula 5 eng-gigapixel.jpg",0,0,lungime_ecran,latime_ecran);
                    outtextxy(mijx-textwidth(textc)/2,latime_ecran-25-textheight(textc)/2,textc);

                    aparitii[4]=1;
                    gata=1;
                    getch();
                }
            }
        }


    }
   /*motivul pentru care am ales sa afisez  poze in loc de a scrie regulile efectiv
   a fost acela de a evita aparitia altor erori si bug-uri,
   sau de a scadea performanta si stilul programului*/
    closegraph();
    return 0;
}
