#include <bits/stdc++.h>
#include <graphics.h>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <MMSystem.h>
#include "stagiu31.cpp"
using namespace std;
int stagiu2()
{
    ///INITIALIZARE PAGINA GRAFICA FULL SCREEEN
    DWORD lungime_ecran =GetSystemMetrics(SM_CXSCREEN);
    DWORD latime_ecran =GetSystemMetrics(SM_CYSCREEN);
    initwindow(lungime_ecran,latime_ecran,"",-3,-3);
    ///COORDONATELE CENTRULUI PAGINII GRAFICE
    int mijx=lungime_ecran/2;
    int mijy=latime_ecran/2;

    ///LEVEL 2
    initwindow(lungime_ecran,latime_ecran,"",-3,-3);
    int viteza=10;
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
    char life[50];
    char shiel[50];
    int page=0;
    unsigned long long current_time;
    unsigned long long raw_time=time(NULL);
    unsigned long long time_shield=0;
    unsigned long long timer_shield=0;
    unsigned long long timer_gun=0;
    unsigned long long time_shoot=0;
    unsigned long long auxi,auxi_b=2;
    unsigned long long last_wave;
    int shootx,shooty,shootfinx;
    int raza_enemy=25;
    int viteza_enemy[21]= {};
    int viteza_enem=10;
    int dir_enemy[21]= {};
    int pozenemyx[21];
    int pozenemyy[21]= {};
    int life_enemy[21]= {1};
    int raza_shield=50;
    long long life_bull[101]= {};
    int nr_enemy=10;
    int bullet;
    int speed_bul=10;
    int fire;
    int bull_st[101]= {};
    int bull_stp[101]= {1};
    int contor_p=0;
    int total_bull=0;
    int contor_bul=0;
    int cnt;
    int hit=0;
    int life_player=5;
    int gun_fire=0;
    int shield=0;
    int nr_kill=0;
    int limit_kill=60;
    int contor_kill=0;
    int enemyr[50]= {};
    unsigned long long time_add;
    unsigned long long time_add1;
    struct fire_poof
    {
        int x;
        int y;
    } bullets[101];
    int car=0;
    int nr_bul=50;
    /* toate aceste variabile au fost explicate in stagiul 1*/
    int r_limit=180;
    /* timpul total de joc*/
    int raza_bomb=25;
    /* dimensiunea bombelor*/
    int bull_ste[101]= {};
    /* un vector care salveaza un numar care arata daca avatarul a fost sau nu prin in explozie*/
    int raza_exp=60;
    /* dimensiunea exploziei*/
    unsigned long long time_left;
    /* timpul de joc*/
    long long life_ex[101]= {};
    /* un vector care salveaza statusul exploziilor, 1 dacaeste in cur de detonare, 0 daca a fost detonata deja */
    char time1[256];
    /* un text care afiseaza timpul ramas*/
///BOMB SPAWN
    total_bull=rand()%30;
    for(int bullet=1; bullet<=total_bull; bullet++)
    {
        bullets[bullet].x=rand()%lungime_ecran;
        bullets[bullet].y=50;
        life_bull[bullet]=raw_time+rand()%7;
        bull_st[bullet]=1;
        bull_stp[bullet]=1;
        bull_ste[bullet]=0;
    }
    /* este acelasi principiu ca si la aparitia gloantelor*/
    current_time=time(NULL);
    total_bull=rand()%30;
    time_left=raw_time+r_limit;
    /* cat timp timpul nu s-a scurs si cat timp jucatorul are vieti*/
    while(time_left>=current_time&&life_player>0)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();
        setfillstyle(SOLID_FILL,LIGHTGREEN);
        floodfill(1,1,LIGHTGREEN);
        int pozplayer[8]= {pozplayer1.x,pozplayer1.y,pozplayer2.x,pozplayer2.y,pozplayer3.x,pozplayer3.y,pozplayer1.x,pozplayer1.y};
        setcolor(YELLOW);
        drawpoly(4,pozplayer);
        setfillstyle(SOLID_FILL,YELLOW);
        fillpoly(4,pozplayer);
        current_time=time(NULL);
        ///COMANDA MERS DREAPTA
        if(GetAsyncKeyState(VK_RIGHT)&&pozplayer3.x+viteza<=lungime_ecran)
        {
            pozplayer1.x+=viteza;
            pozplayer2.x+=viteza;
            pozplayer3.x+=viteza;
        }
        ///COMANDA MERS STANGA
        if(GetAsyncKeyState(VK_LEFT)&&pozplayer2.x+viteza>=1)
        {
            pozplayer1.x-=viteza;
            pozplayer2.x-=viteza;
            pozplayer3.x-=viteza;
        }
        ///COMANDA SHIELD
        if(GetAsyncKeyState(VK_DOWN))
        {
            if(timer_shield<=current_time&&gun_fire==0)
            {
                shield=1;
                for(int i=0; i<=5; i++)
                    arc(pozplayer1.x,pozplayer1.y,0,180,raza_shield+i);
                time_shield=current_time+3;
            }
            else if(timer_shield>current_time)
            {
                setcolor(YELLOW);
                //PlaySound(TEXT("DENIED"),NULL,SND_SYNC);
                settextstyle(8,HORIZ_DIR,1);
                outtextxy(mijx,mijy,"THE SHIELD IS LOADING...");
            }
            else if(gun_fire==1)
            {
                setcolor(YELLOW);
                // PlaySound(TEXT("DENIED"),NULL,SND_SYNC);
                outtextxy(mijx,mijy,"CANNOT USE THE SHIELD WHILE THE CANNON IS ACTIVE !");
                settextstyle(8,HORIZ_DIR,1);
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
        }
        if(timer_shield>current_time)
        {
            setcolor(WHITE);
            sprintf(shiel,"THE SHIELD IS READY IN : %d",timer_shield-current_time);
            settextstyle(8,HORIZ_DIR,1);
            outtextxy(10,mijy+50,shiel);
        }
        else if(time_shield<=current_time&&shield==0)
        {
            setcolor(WHITE);
            {
                outtextxy(10,mijy+50,"THE SHIELD IS READY!");
                settextstyle(8,HORIZ_DIR,1);
            }
        }
        /* este esact acelasi principiu ca si la stagiul 1*/
        /// FIRE CONTROL
        for(bullet=1; bullet<=total_bull; bullet++)
        {
            if(life_bull[bullet]<=current_time&&bull_st[bullet]==1)
            {
                bullets[bullet].y+=speed_bul;
                setfillstyle(SOLID_FILL,RED);
                setcolor(WHITE);
                for(int i=0; i<=3; i++)
                    circle(bullets[bullet].x,bullets[bullet].y,raza_bomb-i);
            }
            if(bullets[bullet].y+raza_bomb>=latime_ecran&&bull_ste[bullet]==0)
            {
                bull_st[bullet]=0;
                bull_ste[bullet]=1;
                life_ex[bullet]=current_time+1;
                contor_bul=0;
                for(cnt=1; cnt<=total_bull; cnt++)
                    if(bull_st[cnt]==1)
                        contor_bul++;
                if(contor_bul==0)
                    total_bull=0;
            }
            /* este acelasi principiu ca si la stagiul 1 doar ca dupa ce bombele au fost generate, li se atribuie un stadiu de explozie*/

            ///EXPLOSION STATE
            if(life_ex[bullet]>=current_time&&bull_ste[bullet]==1)
            {
/* da bombele au explodat*/

                if(bullets[bullet].x-raza_exp<=pozplayer1.x&&bullets[bullet].x+raza_exp>=pozplayer1.x&&bullets[bullet].y-raza_exp<=pozplayer1.y&&bullets[bullet].y+raza_exp>=pozplayer1.y)
                {
                    bull_stp[bullet]=0;
                    contor_bul=0;
                    for(cnt=1; cnt<=total_bull; cnt++)
                        if(bull_ste[cnt]==1&&life_ex[cnt]<current_time)
                            contor_bul++;
                    if(contor_bul==total_bull)
                        total_bull=0;
                    life_ex[bullet]=current_time-1;
                }
                else if(bullets[bullet].x-raza_exp<=pozplayer2.x&&bullets[bullet].x+raza_exp>=pozplayer2.x&&bullets[bullet].y-raza_exp<=pozplayer2.y&&bullets[bullet].y+raza_exp>=pozplayer2.y)
                {
                    bull_stp[bullet]=0;
                    contor_bul=0;
                    for(cnt=1; cnt<=total_bull; cnt++)
                        if(bull_ste[cnt]==1&&life_ex[cnt]<current_time)
                            contor_bul++;
                    if(contor_bul==total_bull)
                        total_bull=0;
                    life_ex[bullet]=current_time-1;
                }
                else if(bullets[bullet].x-raza_exp<=pozplayer3.x&&bullets[bullet].x+raza_exp>=pozplayer3.x&&bullets[bullet].y-raza_exp<=pozplayer3.y&&bullets[bullet].y+raza_exp>=pozplayer3.y)
                {
                    bull_stp[bullet]=0;
                    contor_bul=0;
                    for(cnt=1; cnt<=total_bull; cnt++)
                        if(bull_ste[cnt]==1&&life_ex[cnt]<current_time)
                            contor_bul++;
                    if(contor_bul==total_bull)
                        total_bull=0;
                    life_ex[bullet]=current_time-1;
                }
                /* in aceasta secventa de cod se verifica daca in raza
                 explozitiei se afla unul dintre punctele avatarului, in caz
                 afirmativ se salveaza boba care a provocat acea explozie */
                if(bull_stp[bullet]==1)
                {
                    setcolor(RED);
                    for(cnt=raza_exp; cnt>=raza_exp-5; cnt--)
                        circle(bullets[bullet].x,bullets[bullet].y,cnt);
                    contor_bul=0;
                    for(cnt=1; cnt<=total_bull; cnt++)
                        if(bull_ste[cnt]==1&&life_ex[cnt]<current_time)
                            contor_bul++;
                    if(contor_bul==total_bull)
                        total_bull=0;
                }
                /* daca timup de desfasurare a exploziei nu s-a sfarsit, se deseneaza explozia*/
            }
            if(shield==1&&bullets[bullet].x-raza_bomb>=pozplayer1.x-raza_shield&&bullets[bullet].x-raza_bomb<=pozplayer1.x+raza_shield&&bullets[bullet].y-raza_bomb>=pozplayer1.y-raza_shield)
            {
                bull_st[bullet]=0;
                contor_bul=0;
                for(cnt=1; cnt<=total_bull; cnt++)
                    if(bull_ste[cnt]==1&&life_ex[cnt]<current_time)
                        contor_bul++;
                if(contor_bul==total_bull)
                    total_bull=0;
            }
            else if(shield==0&&pozplayer1.x>=bullets[bullet].x-raza_bomb&&pozplayer1.x<=bullets[bullet].x+raza_bomb&&pozplayer1.y>=bullets[bullet].y-raza_bomb&&pozplayer1.y<=bullets[bullet].y+raza_bomb&&bull_st[bullet]==1&&bull_stp[bullet]==1)
            {
                hit=1;
                bull_st[bullet]=0;
                bull_stp[bullet]=0;
                contor_bul=0;
                for(cnt=1; cnt<=total_bull; cnt++)
                    if(bull_ste[cnt]==1&&life_ex[cnt]<current_time)
                        contor_bul++;
                if(contor_bul==total_bull)
                    total_bull=0;
            }
            else if(shield==0&&pozplayer2.x>=bullets[bullet].x-raza_bomb&&pozplayer2.x<=bullets[bullet].x+raza_bomb&&pozplayer2.y>=bullets[bullet].y-raza_bomb&&pozplayer2.y<=bullets[bullet].y+raza_bomb&&bull_st[bullet]==1&&bull_stp[bullet]==1)
            {
                hit=1;
                bull_st[bullet]=0;
                bull_stp[bullet]=0;
                contor_bul=0;
                for(cnt=1; cnt<=total_bull; cnt++)
                    if(bull_ste[cnt]==1&&life_ex[cnt]<current_time)
                        contor_bul++;
                if(contor_bul==total_bull)
                    total_bull=0;
            }
            else if(shield==0&&pozplayer3.x>=bullets[bullet].x-raza_bomb&&pozplayer3.x<=bullets[bullet].x+raza_bomb&&pozplayer3.y>=bullets[bullet].y-raza_bomb&&pozplayer3.y<=bullets[bullet].y+raza_bomb&&bull_st[bullet]==1&&bull_stp[bullet]==1)
            {
                hit=1;
                bull_st[bullet]=0;
                bull_stp[bullet]=0;
                contor_bul=0;
                for(cnt=1; cnt<=total_bull; cnt++)
                    if(bull_ste[cnt]==1&&life_ex[cnt]<current_time)
                        contor_bul++;
                if(contor_bul==total_bull)
                    total_bull=0;
            }
            /* este acelasi principiu ca si in cazul gloantelor de la stagiul 1, in cazul in care avatarul este lovit de o bomba */
        }
        ///PLAYER'S LIFES
        for(bullet=1; bullet<=total_bull; bullet++)
            if ( bull_stp[bullet]==0)
            {
                contor_p=1;
                bull_stp[bullet]=1;
            }
        if(contor_p==1)
        {
            life_player--;
            contor_p=0;
        }
        setcolor(YELLOW);
        for(cnt=1; cnt<=life_player; cnt++)
            for(int i=1; i<=20; i++)
                circle(20+cnt*50,latime_ecran-20,i);
        ///BULLETS RESET
        if(total_bull==0)
        {
            total_bull=rand()%30;
            for(bullet=1; bullet<=total_bull; bullet++)
            {
                bullets[bullet].x=rand()%lungime_ecran;
                bullets[bullet].y=50;
                life_bull[bullet]=current_time+rand()%7;
                bull_st[bullet]=1;
                bull_stp[bullet]=1;
                bull_ste[bullet]=0;
            }
        }
        /* este acelasi principiu ca si in stagiul 1*/
        setcolor(YELLOW);
        sprintf(time1,"TIME LEFT : %d SECONDS ",time_left-current_time);
        settextstyle(8,HORIZ_DIR,2);
        outtextxy(30,400,time1);
        /* se afiseaza timpul ramas*/
        page=1-page;
        delay(10);
    }
    int ok=0;
    if (life_player<=0)
    {
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
    {
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
    /* este aceeasi mecanica ca si in stagiul 1*/
    closegraph();
    if(car==2)
        stagiu2();
    else if(car==1)
        stagiu31();
        /*daca car este egal cu 2, adica daca jucatorul a pierdut se reia stagiul

    daca car este egal cu 1, adica daca jucatorul a castigat se trece la stagiul urmator*/
    return 0;
}

