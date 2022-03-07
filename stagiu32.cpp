#include <bits/stdc++.h>
#include <graphics.h>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <MMSystem.h>

using namespace std;
int stagiu32()
{
    int car=0;
    ///INITIALIZARE PAGINA GRAFICA FULL SCREEEN
    DWORD lungime_ecran =GetSystemMetrics(SM_CXSCREEN);
    DWORD latime_ecran =GetSystemMetrics(SM_CYSCREEN);
    initwindow(lungime_ecran,latime_ecran,"",-3,-3);
    ///COORDONATELE CENTRULUI PAGINII GRAFICE
    int mijx=lungime_ecran/2;
    int mijy=latime_ecran/2;

    ///LEVEL 3
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
    char time1[256];
    int page=0;
    unsigned long long current_time;
    unsigned long long raw_time=time(NULL);
    unsigned long long time_left;
    unsigned long long time_shield=0;
    unsigned long long timer_shield=0;
    unsigned long long timer_gun=0;
    unsigned long long time_shoot=0;
    unsigned long long auxi,auxi_b=2;
    unsigned long long last_wave;
    int shootx,shooty,shootfinx;
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
    int bull_ste[101]= {};
    int contor_p=0;
    int raza_bomb=25;
    int raza_exp=60;
    long long life_ex[101]= {};
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
    int r_limit=180;
    unsigned long long time_add=0;
    unsigned long long time_add1;
    struct fire_poof
    {
        int x;
        int y;
    } bullets[101];
    int nr_bul=50;
///BULLETS SPAWN
    total_bull=rand()%60;
    for(int bullet=1; bullet<=total_bull; bullet++)
    {
        bullets[bullet].x=rand()%lungime_ecran;
        bullets[bullet].y=50;
        life_bull[bullet]=raw_time+rand()%7;
        bull_st[bullet]=1;
        bull_stp[bullet]=1;
    }
    total_bull=rand()%60;
    current_time=time(NULL);
    total_bull=rand()%60;
    ///BOSS SPAWN
    struct bossf
    {
        int x;
        int y;
    } boss;
    boss.x=mijx+1;
    boss.y=200;
    int r_boss=125;
    int sh_r=5;
    int boss_shieldr=150;
    int r_eye=30;
    int dis_eye=70;
    int eyex=mijx-30;
    int eyey=150;
    int r_sad=50;
    int sady=250;
    int dir_boss=1;
    int nr_shots=0;
    int dif_shots=0;
    int life_boss=lungime_ecran;
    int damage=100;
    for(int i=0; i<=7; i++)
        circle(boss.x,boss.y,r_boss-i);
    while(life_boss>0&&life_player>=0)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();
        setfillstyle(SOLID_FILL,LIGHTGRAY);
        floodfill(1,1,LIGHTGRAY);
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
        int ok=0;
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
                outtextxy(mijx,mijy,"THE SHIELD IS LOADING...");
            }
            else if(gun_fire==1)
            {
                setcolor(YELLOW);
                outtextxy(mijx,mijy,"CANNOT USE THE SHIELD WHILE THE CANNON IS ACTIVE !");
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
            outtextxy(10,mijy+50,shiel);
        }
        else if(time_shield<=current_time&&shield==0)
        {
            setcolor(WHITE);
            outtextxy(10,mijy+50,"THE SHIELD IS READY!");
        }
        ///COMANDA TUN
        if(GetAsyncKeyState(VK_SPACE))
            if(timer_gun<=current_time&&time_shoot<current_time&&shield==0)
            {
                time_shoot=current_time+5;
                auxi=5;
                shootx=pozplayer1.x-3;
                shooty=pozplayer1.y;
                shootfinx=pozplayer1.x+3;
                gun_fire=1;
                nr_shots++;
            }
            else if(timer_gun>current_time)
            {
                setcolor(YELLOW);
                outtextxy(mijx,mijy,"THE CANNON IS LOADING...");
            }
            else if(shield==1)
            {
                setcolor(YELLOW);
                outtextxy(mijx,mijy,"CANNOT USE THE CANNON WHILE THE SHIELD IS ACTIVE !");
            }
        if(time_shoot>=current_time)
            if(time_shoot-current_time!=auxi)
            {
                bar(shootx-=10,shooty,shootfinx+=10,1);
                auxi=time_shoot-current_time;
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
            }
        if(timer_gun>current_time)
        {
            setcolor(WHITE);
            sprintf(shiel,"THE CANNON IS READY IN : %d",timer_gun-current_time);
            outtextxy(10,mijy+75,shiel);
        }
        else if(timer_gun<=current_time&&gun_fire==0)
        {
            setcolor(WHITE);
            outtextxy(10,mijy+75,"THE CANNON IS READY!");
        }
        ///BOSS CONTROLE
        if(boss.x>=lungime_ecran-r_boss-viteza_enem)
        {
            dir_boss=0;
            boss.x-=viteza_enem;
            eyex-=viteza_enem;
        }
        else if(boss.x<=r_boss+viteza_enem)
        {
            dir_boss=1;
            boss.x+=viteza_enem;
            eyex+=viteza_enem;
        }
        else if(dir_boss==1)
        {
            boss.x+=viteza_enem;
            eyex+=viteza_enem;
        }
        else if(dir_boss==0)
        {
            boss.x-=viteza_enem;
            eyex-=viteza_enem;
        }
        ///BOSS SPAWN
        setcolor(YELLOW);
        for(int i=0; i<=10; i++)
            circle(boss.x,boss.y,r_boss-i);
        setcolor(MAGENTA);
        for(int i=1; i<=7; i++)
            circle(eyex,eyey,r_eye-i);
        for(int i=1; i<=7; i++)
            circle(eyex+dis_eye,eyey,r_eye-i);
        setcolor(BLUE);
        for(int i=1; i<=5; i++)
            arc(boss.x,sady-i,0,180,r_sad);
        ///BOSS SHIELD
        if(sh_r)
        {
            int cont=1;
            setcolor(WHITE);
            for(int i=0; i<sh_r; i++)
                circle(boss.x,boss.y,boss_shieldr-i);
            if(gun_fire==1&&boss.x>=(shootfinx-70)-r_boss&&boss.x<=shootfinx+r_boss&&auxi==1)
                cont=0;
            if(dif_shots!=nr_shots&&cont==0)
            {
                sh_r--;
                dif_shots=nr_shots;
            }
            if(sh_r==0)
                time_add=current_time+3;
        }
        if(time_add>=current_time)
        {
            setcolor(YELLOW);
            outtextxy(300,mijy,"THE BOSS SHIELD IS DOWN !");
        }
        ///LIFE BOSS
        if(gun_fire==1&&boss.x>=(shootfinx-70)-r_boss&&boss.x<=shootfinx+r_boss&&auxi==1&&sh_r<=0)
        {
            if(dif_shots!=nr_shots)
            {
                life_boss-=damage;
                dif_shots=nr_shots;
            }
        }
        if(sh_r<=0)
        {
            setfillstyle(SOLID_FILL,RED);
            bar(0,25,life_boss,35);
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
            if(bullets[bullet].y>=latime_ecran)
            {
                bull_st[bullet]=0;
                contor_bul=0;
                for(cnt=1; cnt<=total_bull; cnt++)
                    if(bull_st[cnt]==1)
                        contor_bul++;
                if(contor_bul==0)
                    total_bull=0;
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

        page=1-page;
        delay(8);
    }
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
        char textulet[256]="PRESS SPACE TO CONTINUE TO EXIT";
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(YELLOW);
        outtextxy(mijx-textwidth("VICTORY!")/2,mijy-textheight("VICTORY!")/2,"VICTORY!");
        settextstyle(BOLD_FONT,HORIZ_DIR,2);
        setcolor(WHITE);
        outtextxy(mijx-textwidth(textulet)/2,3*mijy/2-textheight(textulet)/2,textulet);
        getch();
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(YELLOW);
        strcpy(textulet,"THANK YOU FOR PLAYING THE GAME!");
        outtextxy(mijx-textwidth(textulet)/2,mijy-textheight(textulet)/2,textulet);
        settextstyle(BOLD_FONT,HORIZ_DIR,2);
        strcpy(textulet,"PRESS SPACE TO CONTINUE TO EXIT");
        outtextxy(mijx-textwidth(textulet)/2,3*mijy/2-textheight(textulet)/2,textulet);
        delay(2000);
        getch();
        car=1;
    }
    closegraph();
    if(car==2)
        stagiu32();
    return 0;
}


