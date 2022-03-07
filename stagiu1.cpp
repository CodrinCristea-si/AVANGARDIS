#include <bits/stdc++.h>
#include <graphics.h>
#include <windows.h>
#include <ctime>
#include <stdio.h>
#include <MMSystem.h>
#include "stagiu21.cpp"
using namespace std;
int stagiu1()
{
    ///INITIALIZARE PAGINA GRAFICA FULL SCREEEN
    DWORD lungime_ecran =GetSystemMetrics(SM_CXSCREEN);
    DWORD latime_ecran =GetSystemMetrics(SM_CYSCREEN);
    initwindow(lungime_ecran,latime_ecran,"",-3,-3);

    ///COORDONATELE CENTRULUI PAGINII GRAFICE
    int mijx=lungime_ecran/2;
    int mijy=latime_ecran/2;

    ///LEVEL 1

    ///POZITIA PUNCTULUI DE SUS
    struct PozitiePlayerPunct1
    {
        int x;
        int y;
    } pozplayer1;
    pozplayer1.x=mijx;
    pozplayer1.y=latime_ecran-90;

    ///POZITIA PUNCTULUI DE JOS STANGA
    struct PozitiePlayerPunct2
    {
        int x;
        int y;
    } pozplayer2;
    pozplayer2.x=pozplayer1.x-20;
    pozplayer2.y=pozplayer1.y+30;

    ///POZITIA PUNCTULUI DE JOS DREAPTA
    struct PozitiePlayerPunct3
    {
        int x;
        int y;
    } pozplayer3;
    pozplayer3.x=pozplayer1.x+20;
    pozplayer3.y=pozplayer1.y+30;

    char kill[50];
    /* un text ce memoreaza numarul de inamici distrusi */
    char life[50];
    char shiel[50];
    /* un text care memoreaza intervalul de timp in care se incarca scutul sau tunul*/
    int page=0;
   /* page va memora pagina pecare se va desena */
    int viteza=10;
    /* este viteza cucare se va deplasa avatarul pe ecran*/
    unsigned long long current_time;
    /* aceasta variabila va memora timpul curent din animatie,
    fiind folosita la ghidarea comenzilor jucatorului*/
    unsigned long long raw_time=time(NULL);
    /* aceasta variabila va memora timpul curent de dinainte de animatie,
     cu scopul de a ajuta la organizarea coloanelor de gloante*/
    unsigned long long time_shield=0;
    /* este timpul in care actioneaza scutul*/
    unsigned long long timer_shield=0;
    /* este timpul de incarcare a scutului*/
    unsigned long long timer_gun=0;
    /*este timpul necesar de incarcare a tunului*/
    unsigned long long time_shoot=0;
    /* este timpul de actiune al tunului*/
    unsigned long long auxi,auxi_b=2;
    /*  doua variabile care vor ajuta la crearea fazelor tunului */
    unsigned long long last_wave;
    /* o variabila folosita la initializarea inamicilor si a gloantelor*/
    unsigned long long time_add;
    /* timpul de afisare al unui anunt*/
    unsigned long long time_add1;
    /* timpul de afisare al unui anunt*/
    int shootx,shooty,shootfinx;
    /* coordonatele de inceput ale razeitunului*/
    int raza_enemy=25;
    /* dimensiunea inamicului*/
    int viteza_enemy[21]= {};
    int viteza_enem=10;
    /*viteza de deplasare a inamicilor*/
    int dir_enemy[21]= {};
    /*directia pentru fiecare inimic, toate incep cu 0, 1 spre dreapta, 0 spre stanga*/
    int pozenemyx[21];
    /* pozitia pe orizontala a inamicului*/
    int pozenemyy[21]= {};
    /* pozitia pe verticala a inamicului*/
    int life_enemy[21]= {1};
    /* viata fiecarui inamic, 1- este in viata,  deci poate fi desenat, 0- este mort, deci nu poate fi desenat*/
    int raza_shield=50;
    /*raza scutului jucatorului*/
    long long life_bull[101]= {};
    /* viata fiecarui glont*/
    int nr_enemy=10;
    /* numarul maxim de inamici de pe ecran*/
    int bullet;
    /* o variabila ce reprezinta glontul*/
    int speed_bul=10;
    /* viteza de deplasare a glontului*/
    int fire;
    int bull_st[101]= {};
    /* un vector ce contine un registru al gloantelor, 1 este in desfasurare, 0 a ajuns in partea de jos a ecranului*/
    int bull_stp[101]= {1};
    /*  un vector ce contine informatii cu privire la gloantele care au lovit jucatorul*/
    int contor_p=0;
    /* un contor ce verifica daca un glont a lovit avatarul jucatorului*/
    int total_bull=0;
    /*numarul total de gloante dintr-un val*/
    int contor_bul=0;
    /*variabila prin care se ia fiecare glont in parte*/
    int cnt;
    /* este un contor*/
    int hit=0;
    /* o variabila ce arata daca avataatul este lovit de gloante sau nu*/
    int life_player=3;
    /* vietile jucatorului*/
    int gun_fire=0;
    /* variabila ne arata daca tunul este activ(1) sau nu(0)*/
    int shield=0;
    /* variabila ne arata daca scutul este activ(1) sau nu(0) */
    int nr_kill=0;
    /* reprezinta numarul de inamici pe care jucatorul i-a distrus in acel moment*/
    int limit_kill=60;
   /* numarul maxim de inamici care pot fi distrusi*/
    int contor_kill=0;
    /* numara cati inamici au fost distrusi intr-un val*/
    int enemyr[50]= {};
    /* un vector ce memoreaza numarul de valuri alre inamicilor*/
    int r_limit=0;
    /* numarul de inamici ce trebuie distrusi pentru a declansa un val*/
    int car=0;
   /* aceasta variabila salveaza rezultatul jocului, astfel, daca este 1
   atunci inseamna ca jucatorul a terminat cu succes stadiul, daca este 2
   inseamna ca jucatorul a pierdut stadiul*/
    struct fire_poof
    {
        int x;
        int y;
    } bullets[101];
    /* coordonatele de inceput ale gloantelor*/
    int nr_bul=50;
    /* numarul maxim de gloante dintr-un val*/
    last_wave=raw_time;
/// APARITII BULLET
    total_bull=rand()%60;
    /* numarul total de gloante dintru val va fi generat la intamplare*/
    for(int bullet=1; bullet<=total_bull; bullet++)
    {
        bullets[bullet].x=rand()%lungime_ecran;
        bullets[bullet].y=50;
        life_bull[bullet]=raw_time+rand()%7;
        bull_st[bullet]=1;
        bull_stp[bullet]=1;
        /* se ia fiecare glont in parte si se alege la intamplare
        coordonata de orizontala, apoi se stabileste un interval de timp
         de la inceperea valului la care vor aparea gloantele (life_bull)

         totodata li se atribuieste 2 statuturi,  primul este acela ca pot aparea pe
          ecran si al doilea reprezinta faptul ca nu a lovit pana acm jucatorul
         */
    }
    total_bull=rand()%60;
    /* dupa se genereaza numarul total de gloante pentru urmatorul val*/
///APARITII ENEMY
    for(int enemy=1; enemy<=10; enemy++)
    {
        pozenemyx[enemy]=rand()%lungime_ecran+1;
        pozenemyy[enemy]=50+rand()%100+1;
        viteza_enemy[enemy]=10;
        life_enemy[enemy]=1;
        if(pozenemyx[enemy]>=mijx&&pozenemyx[enemy]<=lungime_ecran)
            dir_enemy[enemy]=1;
        else if(pozenemyx[enemy]<mijx&&pozenemyx[enemy]>=raza_enemy)
            dir_enemy[enemy]=0;
        for(int i=raza_enemy; i>=15; i--)
            circle(pozenemyx[enemy],pozenemyy[enemy],raza_enemy);
            /* se ia fiecare inamic si i se genereaza o coordonata orizontala la intamplare
             si o coordonata verticala intr-un anumit interval, tot la intamplare

             adica se organizeaza gloantele intr-un fel de matrice, in care numarul de linii
             este deta de timpul la cate apar acestea, iar numarul de colone reprezinta fix
             lungimea ecranului

            dupa se verifica pozitia relativa acestora fata de mijlocul ecranului,
             daca se afla in partea stanga a acelui punct, inamicul se va deplasa
              catre stanga si viceversa

            apoi se deseneaza inamicul efectiv, adica un cerc de o anumita grosime
            */
    }
/* cat timp jucatorul are vieti si cat timp inca sunt inamici pe ecran*/
    while(nr_kill<limit_kill&&life_player>0)
    {
        setactivepage(page);
        /* seteaza pagina pe care se va desena */
        setvisualpage(1-page);
         /* seteaza ca pagina pe care o va vizualiza observatorul sa fie cea precedenta */
        cleardevice();
         /* sterge tot ce este pe pagina activa */
        setfillstyle(SOLID_FILL,LIGHTBLUE);
        floodfill(1,1,LIGHTBLUE);
        /* se deseneaza efectiv fundalul, fara citirea unei imagini*/
        int pozplayer[8]= {pozplayer1.x,pozplayer1.y,pozplayer2.x,pozplayer2.y,pozplayer3.x,pozplayer3.y,pozplayer1.x,pozplayer1.y};
        setcolor(YELLOW);
        drawpoly(4,pozplayer);
        setfillstyle(SOLID_FILL,YELLOW);
        fillpoly(4,pozplayer);
        /* se deseneaza un polinom cu 3 varfuri dupa care este colorat, acest polinom reprezentand jucatorul*/
        current_time=time(NULL);
        /* se salveaza timpul din joc*/

        ///COMANDA MERS DREAPTA
        if(GetAsyncKeyState(VK_RIGHT)&&pozplayer3.x+viteza<=lungime_ecran)
        {
            pozplayer1.x+=viteza;
            pozplayer2.x+=viteza;
            pozplayer3.x+=viteza;
        }
        /*daca jucatorul a apasat tasta sageata dreapta si jucatorul nu a ajuns la extremitate
        a din dreapta a ecranului, avatarul se va deplasa catre dreapta*/

        ///COMANDA MERS STANGA
        if(GetAsyncKeyState(VK_LEFT)&&pozplayer2.x+viteza>=1)
        {
            pozplayer1.x-=viteza;
            pozplayer2.x-=viteza;
            pozplayer3.x-=viteza;
        }
        /*daca jucatorul a apasat tasta sageata stanga si jucatorul nu a ajuns la extremitate
        a din stanga a ecranului, avatarul se va deplasa catre stanga*/
        int ok=0;
        ///COMANDA SHIELD
        if(GetAsyncKeyState(VK_DOWN))
        {/* daca esta apasata tasta sageata jos*/
            if(timer_shield<=current_time&&gun_fire==0)
            {
                shield=1;
                for(int i=0; i<=5; i++)
                    arc(pozplayer1.x,pozplayer1.y,0,180,raza_shield+i);
                time_shield=current_time+3;
                /* se verifica daca timpul necesar de incarcare a scutului este mai mic decat timpul curent al jocului

                in caz afirmativ se stabileste valoarea 1 a variabilei shield, care va arata programului
                ca scutul a fost actival, si se va genera scutul

                timpul de actiune al scutului este de 3 secunde */
            }
            else if(timer_shield>current_time)
            {
                setcolor(YELLOW);
                outtextxy(mijx,mijy,"THE SHIELD IS LOADING...");
                /* daca timpul de incarcare este mai mare decat timpul curent, atunci se va afisa un mesaj corespunzator catre jucator*/
            }
            else if(gun_fire==1)
            {
                setcolor(YELLOW);
                outtextxy(mijx,mijy,"CANNOT USE THE SHIELD WHILE THE CANNON IS ACTIVE !");
            /* daca tunul este activ, pe ecran va aparea un mesaj in care i se va
             explica jucatorului ca nu poate folosi doua comenzi in acelasi timp*/
            }
        }

        if(time_shield>=current_time)
        {
            setcolor(WHITE);
            for(int i=0; i<=5; i++)
                arc(pozplayer1.x,pozplayer1.y,0,180,raza_shield+i);
            if(time_shield==current_time)
            {
                timer_shield=current_time+5;
                shield=0;
            }
        /* daca timpul de actiune este mai mare decat timpul curent al jocului, atunci se deseneaza scutul

        daca cele doua variabile sunt egale, atunci scutul se va dezactiva*/
        }
        if(timer_shield>current_time)
        {
            setcolor(WHITE);
            sprintf(shiel,"THE SHIELD IS READY IN : %d",timer_shield-current_time);
            outtextxy(10,mijy+50,shiel);
            /* in cazul in care timpul de incarcare este mai mare decat timpul curent,
             atunci se va afisa pe ecran timpul ramas pana la incarcarea completa */
        }
        else if(time_shield<=current_time&&shield==0)
        {
            setcolor(WHITE);
            outtextxy(10,mijy+50,"THE SHIELD IS READY!");
            /*in cazul in care scutul este incarcat si inca nu s-a activat,
             atunci se va afisa un mesaj in care i se atentioneaza jucatorului ca scutul este gata*/
        }
        ///COMANDA TUN
        if(GetAsyncKeyState(VK_SPACE))
            /*daca s-a apasat tasta space*/
            if(timer_gun<=current_time&&time_shoot<current_time&&shield==0)
            {
                time_shoot=current_time+5;
                auxi=5;
                shootx=pozplayer1.x-3;
                shooty=pozplayer1.y;
                shootfinx=pozplayer1.x+3;
                gun_fire=1;
                /* daca timpul de incarcare este mai mic decat timpul curent si daca tunul
                nu actioneaza si daca scutulnu este activ, atunci se activeaza tunul

                o variabila auxi=5, asta inseamna ca in faza a 5a tunul va crea pagube inamicilor aflati in raza

                raza tunului va incepe din vf de sus al avatarului se se va extinde pe toata circumferinta superioara a acestuia*/

            }
            else if(timer_gun>current_time)
            {
                setcolor(YELLOW);
                outtextxy(mijx,mijy,"THE CANNON IS LOADING...");
                /* daca timpul de incarcare este mai mare decat timpul curent, atunci se va afisa un mesaj corespunzator catre jucator*/
            }
            else if(shield==1)
            {
                setcolor(YELLOW);
                outtextxy(mijx,mijy,"CANNOT USE THE CANNON WHILE THE SHIELD IS ACTIVE !");
                /* daca scutul este activ, pe ecran va aparea un mesaj in care i se va
             explica jucatorului ca nu poate folosi doua comenzi in acelasi timp*/
            }
        if(time_shoot>=current_time)
            if(time_shoot-current_time!=auxi)
            {
                bar(shootx-=10,shooty,shootfinx+=10,1);
                auxi=time_shoot-current_time;
                /*daca tunul este activat si daca s-a terminat una dintre fazele tunului,
                se creeaza raza conform explicatiilor de mai sus

                auxi va memora diferenta intre timpul de actiune si timpul curent, pentru a delimita cele auxi faze */
            }
            else
            {
                setfillstyle(SOLID_FILL,auxi);
                bar(shootx,shooty,shootfinx,1);
                if(time_shoot==current_time)
                {
                    timer_gun=current_time+10;
                    gun_fire=0;
                }
                /* se creeaza faza tunului, daca cele 2 variabile sunt egale, tunul se dezactiveaza */
            }
        if(timer_gun>current_time)
        {
            setcolor(WHITE);
            sprintf(shiel,"THE CANNON IS READY IN : %d",timer_gun-current_time);
            outtextxy(10,mijy+75,shiel);
            /* in cazul in care timpul de incarcare este mai mare decat timpul curent,
             atunci se va afisa pe ecran timpul ramas pana la incarcarea completa */
        }
        else if(timer_gun<=current_time&&gun_fire==0)
        {
            setcolor(WHITE);
            outtextxy(10,mijy+75,"THE CANNON IS READY!");
             /*in cazul in care tunul este incarcat si inca nu s-a activat,
             atunci se va afisa un mesaj in care i se atentioneaza jucatorului ca tunul este gata*/
        }

        /// CONTORALE ENEMY
        for(int enemy=1; enemy<=10; enemy++)
        {
            if(gun_fire==1&&pozenemyx[enemy]>=(shootfinx-70)-raza_enemy&&pozenemyx[enemy]<=shootfinx+raza_enemy&&auxi==1)
                life_enemy[enemy]=0;
            /*daca inamicul se afla in raza tunului si se afla in faza a cincea, atunci inamicul este distrus*/
            if(life_enemy[enemy]==1)
            { /*daca inamicul este in viata*/
                if(pozenemyx[enemy]>=lungime_ecran-raza_enemy-viteza_enem)
                {
                    dir_enemy[enemy]=0;
                    pozenemyx[enemy]-=viteza_enem;
                }
                /* daca inamicul este la capatul din dreapta al ecranului atunci se schimba directia*/
                else if(pozenemyx[enemy]<=raza_enemy+viteza_enem)
                {
                    dir_enemy[enemy]=1;
                    pozenemyx[enemy]+=viteza_enem;
                }
            /* daca inamicul este la capatul din stanga al ecranului atunci se schimba directia*/

                else if(dir_enemy[enemy]==1)
                    pozenemyx[enemy]+=viteza_enem;
                /*inamicul se deplaseaza catre dreapta*/
                else if(dir_enemy[enemy]==0)
                    pozenemyx[enemy]-=viteza_enem;
                     /*inamicul se deplaseaza catre stanga*/
                setcolor(MAGENTA);
                for(int i=raza_enemy; i>=15; i--)
                    circle(pozenemyx[enemy],pozenemyy[enemy],i);
                    /* se deseneaza inamicul*/
            }
        }

        ///ENEMY REINFORCEMENTS
        contor_kill=0;
        for(cnt=1; cnt<=10; cnt++)
            if(life_enemy[cnt]==0)
                contor_kill++;
        /* se verifica daca unul dintre cei 10 inamici estedoborat*/
        if(contor_kill+r_limit>nr_kill)
            nr_kill=r_limit+contor_kill;
        {
            setcolor(GREEN);
            sprintf(kill,"THE NUMBER OF KILLS IS : %d",nr_kill);
        }
        /* daca numarul de inamici doborati adunat cu cel existent este mai mare
        decat numarul afisat de ecran, se modifica numarul de inamici distrusi*/
        outtextxy(25,mijy,kill);
        if(nr_kill%5==0&&enemyr[nr_kill/5]==0)
        {
            time_add=current_time+2;
            enemyr[nr_kill/5]=1;
            r_limit=nr_kill;
            for(cnt=1; cnt<=10; cnt++)
                if(life_enemy[cnt]==0)
                {
                    pozenemyx[cnt]=rand()%lungime_ecran+1;
                    pozenemyy[cnt]=50+rand()%100+1;
                    viteza_enemy[cnt]=10;
                    life_enemy[cnt]=1;
                    if(pozenemyx[cnt]>=mijx&&pozenemyx[cnt]<=lungime_ecran)
                        dir_enemy[cnt]=1;
                    else if(pozenemyx[cnt]<mijx&&pozenemyx[cnt]>=raza_enemy)
                        dir_enemy[cnt]=0;
                    for(int i=raza_enemy; i>=15; i--)
                        circle(pozenemyx[cnt],pozenemyy[cnt],raza_enemy);
                }
        /* daca un anumit numar de inamici au fost distrusi se genereaza alti inamici*/
        }
        if(nr_kill>=10&&time_add>=current_time)
        {
            setcolor(RED);
            outtextxy(mijx,700,"WARNING! THE ENEMY GATHERED MORE REINFORCEMENTS!");
            /* jucatorul este anuntat ca inamicii au primit intariri*/
        }
        else if(time_add>=current_time&&nr_kill<10&&nr_kill>=5)
        {
            setcolor(RED);
            outtextxy(mijx,700,"WARNING! THE ENEMY GATHERED REINFORCEMENTS!");
        /* jucatorul este anuntat ca inamicii au primit intariri*/
        }

        /// FIRE CONTROL
        for(bullet=1; bullet<=total_bull; bullet++)
        {
            if(life_bull[bullet]<=current_time&&bull_st[bullet]==1)
            {
                bullets[bullet].y+=speed_bul;
                setfillstyle(SOLID_FILL,RED);
                bar(bullets[bullet].x,bullets[bullet].y,bullets[bullet].x+10,bullets[bullet].y+25);
            }
            /* se ia fiecare glont si se verifica daca a pornit si daca nu a ajuns la baza ecranului, in caz afirmativ se deseneaza*/
            if(bullets[bullet].y>=latime_ecran)
            {
                bull_st[bullet]=0;
                contor_bul=0;
                for(cnt=1; cnt<=total_bull; cnt++)
                    if(bull_st[cnt]==1)
                        contor_bul++;
                if(contor_bul==0)
                    total_bull=0;
                    /* daca un glont a ajuns la baza ecranului, se sterge de pe ecran */
            }
            if(shield==1&&bullets[bullet].x>=pozplayer1.x-raza_shield&&bullets[bullet].x<=pozplayer1.x+raza_shield&&bullets[bullet].y>=pozplayer1.y-raza_shield)
            {
                bull_st[bullet]=0;
                contor_bul=0;
                for(cnt=1; cnt<=total_bull; cnt++)
                    if(bull_st[cnt]==1)
                        contor_bul++;
                if(contor_bul==0)
                    total_bull=0;
                /*daca scutul este activ si un glont a atins jucatorul, lovitura este anulat si glontul este sters*/
            }
            else if(shield==0&&pozplayer1.x>=bullets[bullet].x&&pozplayer1.x<=bullets[bullet].x+10&&pozplayer1.y>=bullets[bullet].y&&pozplayer1.y<=bullets[bullet].y+25&&bull_st[bullet]==1&&bull_stp[bullet]==1)
            {
                hit=1;
                bull_st[bullet]=0;
                bull_stp[bullet]=0;
                contor_bul=0;
                for(cnt=1; cnt<=total_bull; cnt++)
                    if(bull_st[cnt]==1)
                        contor_bul++;
                if(contor_bul==0)
                    total_bull=0;
                    /* daca glontul loveste varful de sus al avatarului, se salveaza glontul care l-a lovit si se sterge glontul*/

            }
            else if(shield==0&&pozplayer2.x>=bullets[bullet].x&&pozplayer2.x<=bullets[bullet].x+10&&pozplayer2.y>=bullets[bullet].y&&pozplayer2.y<=bullets[bullet].y+25&&bull_st[bullet]==1&&bull_stp[bullet]==1)
            {
                hit=1;
                bull_st[bullet]=0;
                bull_stp[bullet]=0;
                contor_bul=0;
                for(cnt=1; cnt<=total_bull; cnt++)
                    if(bull_st[cnt]==1)
                        contor_bul++;
                if(contor_bul==0)
                    total_bull=0;
 /* daca glontul loveste varful de din drepta al avatarului, se salveaza glontul care l-a lovit si se sterge glontul*/

            }
            else if(shield==0&&pozplayer3.x>=bullets[bullet].x&&pozplayer3.x<=bullets[bullet].x+10&&pozplayer3.y>=bullets[bullet].y&&pozplayer3.y<=bullets[bullet].y+25&&bull_st[bullet]==1&&bull_stp[bullet]==1)
            {
                hit=1;
                bull_st[bullet]=0;
                bull_stp[bullet]=0;
                contor_bul=0;
                for(cnt=1; cnt<=total_bull; cnt++)
                    if(bull_st[cnt]==1)
                        contor_bul++;
                if(contor_bul==0)
                    total_bull=0;
                /* daca glontul loveste varful de stanga al avatarului, se salveaza glontul care l-a lovit si se sterge glontul*/


            }
        }
        ///BULLETS RESET
        if(total_bull==0)
        {
            total_bull=rand()%60;
            for(bullet=1; bullet<=total_bull; bullet++)
            {
                bullets[bullet].x=rand()%lungime_ecran;
                bullets[bullet].y=50;
                life_bull[bullet]=current_time+rand()%7;
                bull_st[bullet]=1;
                bull_stp[bullet]=1;
            }
            /*se genereaza noi gloante, daca toate gloantele au ajuns jos*/
        }
        ///PLAYER'S LIFES
        for(bullet=1; bullet<=total_bull; bullet++)
            if ( bull_stp[bullet]==0)
            {
                contor_p=1;
                bull_stp[bullet]=1;
            }
            /* se verifica daca un glont a lovit jucatorul*/
        if(contor_p==1)
        {
            life_player--;
            contor_p=0;
        }
        /* daca un glont a lovit jucatorul, viata jucatorului scade

        eu numar gloantele care au lovit avatarul, nu numarul de lovituri ale acestora,
         deoarece viata jucatorului s-ar reduce la 0 dupa primul glont*/
        setcolor(YELLOW);
        for(cnt=1; cnt<=life_player; cnt++)
            for(int i=1; i<=20; i++)
                circle(20+cnt*50,latime_ecran-20,i);
            /* se afiseaza viata jucatorului*/
        delay(5);
                  /* aceasta comanda ingheata programul pentru 5 milisecunde*/

        page=1-page;
         /* page va avea doar 2 valori, astfel se vor folosi doar 2 pagini, una anterioada care va fi afisata utilizatorului,
              iar a doua pagina va fi stearga si redesenata

              tranzitia dintre cele 2 pagini va elimita efectul de glich pecare l-ar fi avut animatia */
    }

    if (life_player<=0)
    {/* daca jucatorul a ramas fara vieti atunci se afiseaza un mesaj prin care i se instiinteaza acest lucru, si urmatoarele instructiuni*/
        initwindow(lungime_ecran,latime_ecran,"",-3,-3);
        char textulet[256]="PRESS SPACE TO RESTART THE STAGE";
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(YELLOW);
        outtextxy(mijx-textwidth("GAME OVER!")/2,mijy-textheight("GAME OVER!")/2,"GAME OVER!");
        settextstyle(BOLD_FONT,HORIZ_DIR,2);
        setcolor(WHITE);
        outtextxy(mijx-textwidth(textulet)/2,3*mijy/2-textheight(textulet)/2,textulet);
        delay(2000);
        getch();
        car=2;
    }
    else
    {    /* daca jucatorul a terminat stagiul si mai are vieti atunci se afiseaza un mesaj prin care i se instiinteaza acest lucru,
         si urmatoarele instructiuni*/

        initwindow(lungime_ecran,latime_ecran,"",-3,-3);
        char textulet[256]="PRESS SPACE TO CONTINUE TO THE NEXT STAGE";
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(YELLOW);
        outtextxy(mijx-textwidth("VICTORY!")/2,mijy-textheight("VICTORY!")/2,"VICTORY!");
        settextstyle(BOLD_FONT,HORIZ_DIR,2);
        setcolor(WHITE);
        outtextxy(mijx-textwidth(textulet)/2,3*mijy/2-textheight(textulet)/2,textulet);
        delay(2000);
        getch();
        car=1;
    }
    closegraph();
    /* se inchide toate paginile deschise, astfel sa nu fie deschise
      prea multe pagini, deci ca sa nu scada performanta jocului*/
    if(car==2)
        stagiu1();
    else if(car==1)
        stagiu21();
    /*daca car este egal cu 2, adica daca jucatorul a pierdut se reia stagiul

    daca car este egal cu 1, adica daca jucatorul a castigat se trece la stagiul urmator*/

    return 0;
}
