#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

char camera[10][10][26],player='o';
char holcursa[10][100], cameracod50[10][21];

typedef unsigned short natural;

int nr_camere=4,camere_parcurse=1;

unsigned short camera_generata, event_random,tip_camera_generata;

bool stillalive=1, este_ascuns=0;

void initializare_hol(int k)
{
    int i,j;
    if(k==8)
    {
        for(i=0; i<=9; i++)
            for(j=0; j<=24; j++)
                if(i==0 || i==9) camera[k][i][j]='_';
                else if(j==0 || j==24) camera[k][i][j]='|';
                else camera[k][i][j]=' ';
    }
    else
    {
        for(i=0; i<=9; i++)
            for(j=0; j<=24; j++)
                if(i==0 || i==9) camera[k][i][j]='_';
                else if(j==0 || j==24) camera[k][i][j]='|';
                else if(i>=3 && i<=6 && j>=4 && j<=20)camera[k][i][j]='#';
                else camera[k][i][j]=' ';
    }
    camera[k][9][0]='|';
    camera[k][9][24]='|';
    camera[k][5][24]=' ';
    for(i=0; i<=9; i++)
        camera[k][9][25]='\0';
}

void generare_camera_50()
{
    int i,j;
    for(i=0; i<=9; i++)
        for(j=0; j<=19; j++)
            if(i==0 || i==9) cameracod50[i][j]='_';
            else if(j==0 || j==19) cameracod50[i][j]='|';
            else cameracod50[i][j]=' ';
    cameracod50[5][0]=cameracod50[5][19]=' ';
    cameracod50[0][9]=cameracod50[9][9]=' ';
    cameracod50[9][0]=cameracod50[9][19]='|';
    for(i=0; i<=9; i++)
        cameracod50[i][20]='\0';
}
void camera_50_100(int camere)
{
    char comanda,charprec=' ';
    natural cod[6],i,nrcodghicit=0,x,y;
    srand(time(0)+1);
    for(i=0; i<=5; i++)
    {
        cod[i]=rand()%5;
        if(!cod[i]) cod[i]++;
    }
    generare_camera_50();
    natural x1=9,y1=0,x2=19,y2=5,y3=9,x4=0,y4=5;
    x=9,y=5;
    bool corect=0,ok=0;
    cameracod50[y][x]=player;
    while(nrcodghicit!=6)
    {
        cout<<"\033[1m\033[33mCamera "<< camere<< "\033[0m"<<'\n';
        if(nrcodghicit!=1)cout<<"Ai ghicit " << nrcodghicit << " usi din secventa de 6 usi."<<'\n';
        else cout<<"Ai ghicit 1 usa din secventa de 6 usi."<<'\n';
        if(corect && ok)cout<<"\x1B[32mCorect!\u001b[0m"<<'\n';
        else if(ok)cout<<"\u001b[31mGresit!\u001b[0m"<<'\n';
        for(i=0; i<=9; i++)
            cout<<cameracod50[i]<<'\n';
        comanda=_getch();
        switch(comanda)
        {
        case 'w':
        {

            if(cameracod50[y-1][x]==' ')
            {
                cameracod50[y][x]=charprec;
                charprec=cameracod50[y-1][x];
                cameracod50[y-1][x]='o';
                --y;
                break;
            }
            else break;
        }
        case 'a':
        {
            if(cameracod50[y][x-1]==' ')
            {
                cameracod50[y][x]=charprec;
                charprec=cameracod50[y][x-1];
                cameracod50[y][x-1]='o';
                --x;
                break;
            }
            else break;
        }
        case 'd':
        {
            if(cameracod50[y][x+1]==' ')
            {
                cameracod50[y][x]=charprec;
                charprec=cameracod50[y][x+1];
                cameracod50[y][x+1]='o';
                ++x;
                break;
            }
            else break;
        }
        case 's':
        {
            if(cameracod50[y+1][x]==' ')
            {
                cameracod50[y][x]=charprec;
                charprec=cameracod50[y+1][x];
                cameracod50[y+1][x]='o';
                ++y;
                break;
            }
            else break;
        }
        }
        if(x==x1)
        {
            if(y==y1)
            {
                if(cod[nrcodghicit]==1)
                    corect=1,ok=1,nrcodghicit++,cameracod50[y][x]=' ',x=9,y=5,cameracod50[y][x]=player;
                else corect=0,ok=1,nrcodghicit=0,cameracod50[y][x]=' ',x=9,y=5,cameracod50[y][x]=player;
            }
            else if(y==y3)
                {
                    if(cod[nrcodghicit]==3)
                    corect=1,ok=1,nrcodghicit++,cameracod50[y][x]=' ',x=9,y=5,cameracod50[y][x]=player;
                else corect=0,ok=1,nrcodghicit=0,cameracod50[y][x]=' ',x=9,y=5,cameracod50[y][x]=player;
                }
        }
        else if(x==x2)
        {
            if(y==y2)
                {
                if(cod[nrcodghicit]==2)
                    corect=1,ok=1,nrcodghicit++,cameracod50[y][x]=' ',x=9,y=5,cameracod50[y][x]=player;
                else corect=0,ok=1,nrcodghicit=0,cameracod50[y][x]=' ',x=9,y=5,cameracod50[y][x]=player;
                }
        }
        else if(x==x4)
        {
            if(y==y4)
                {
                if(cod[nrcodghicit]==4)
                    corect=1,ok=1,nrcodghicit++,cameracod50[y][x]=' ',x=9,y=5,cameracod50[y][x]=player;
                else corect=0,ok=1,nrcodghicit=0,cameracod50[y][x]=' ',x=9,y=5,cameracod50[y][x]=player;
                }
        }
        Sleep(30);
        system("cls");
    }
}

void initializare_camera(int k)
{
    if(k<=5)
    {
        int i,j;
        for(i=0; i<=9; i++)
            for(j=0; j<=15; j++)
                if(i==0 || i==9) camera[k][i][j]='_';
                else if(j==0 || j==15) camera[k][i][j]='|';
                else camera[k][i][j]=' ';
        camera[k][9][0]='|';
        camera[k][9][15]='|';
        camera[k][5][15]=' ';
        for(i=0; i<=9; i++)
            camera[k][9][16]='\0';
    }
    else if(k==6||k==7)
    {
        int i,j;
        for(i=0; i<=9; i++)
            for(j=0; j<=15; j++)
                if(i==0 || i==9) camera[k][i][j]='_';
                else if(j==0 || j==15) camera[k][i][j]='|';
                else if(i>=3 && i<=6 && j>=4 && j<=11)camera[k][i][j]='#';
                else camera[k][i][j]=' ';
        camera[k][9][0]='|';
        camera[k][9][15]='|';
        camera[k][5][15]=' ';
    }
    else initializare_hol(k);
}

void ascuns(bool &indulap, int &event, int k, int iesy, int y, int x)
{
    system("cls");
    int counter=3;
    if(event==1)
    {
        camera[k][y][x]=' ';
        while(counter>=0)
        {
            cout<<(char)7;
            Sleep(30);
            system("cls");
            cout<<"Esti ascuns. Apasa orice tasta pentru a iesi odata ce trece timpul."<<'\n'<<counter<<'\n';
            for(int i=0; i<=9; i++)
            {
                cout<<camera[k][i];
                cout<<'\n';
            }
            Sleep(1000);
            --counter;
        }
        camera[k][y][x]=player;
    }
    if(event!=1)
    {
        camera[k][y][x]=' ';
        cout<<"Esti ascuns. Apasa orice tasta pentru a iesi."<<'\n';
        if(event!=3)
            for(int i=0; i<=9; i++)
            {
                for(int j=0; j<=iesy; j++)
                    cout<<camera[k][i][j];
                cout<<'\n';
            }
        camera[k][y][x]=player;
    }
    if(event==1)
        event=0;
    indulap=1;
    char comanda='\0';
    while(comanda=='\0')comanda=getch();
}

char cameraintunecata[10][26];
void generare_camera_intunecata(int k)
{
    int i,j;
    if(k<=7)
    {
        for(i=0; i<=9; i++)
            for(j=0; j<=15; j++)
                cameraintunecata[i][j]='/';
        for(i=0; i<=9; i++)
            cameraintunecata[i][16]='\0';
    }
    else
    {
        for(i=0; i<=9; i++)
            for(j=0; j<=24; j++)
                cameraintunecata[i][j]='/';
        for(i=0; i<=9; i++)
            cameraintunecata[i][25]='\0';
    }
}

void lanterna(int x,int y, int r,int k)
{
    if(r)
    {
        cameraintunecata[y][x]=camera[k][y][x];
        r--;
        lanterna(x+1,y,r,k);
        lanterna(x-1,y,r,k);
        lanterna(x,y+1,r,k);
        lanterna(x,y-1,r,k);
    }
}

void jocul_principal(int k,int tip_camera_generata, int event,bool &player_alive)
{
    int x,y,iesy,i;
    x=0;
    y=5;
    if(k<=7)iesy=15;
    else iesy=24;
    int ciesy=iesy;
    if(event==2) swap(x,ciesy);
    char comanda;
    bool cheie=1;
    player_alive=1;
    srand(time(0));
    natural locatiecheie;
    locatiecheie=rand()%2;
    switch(tip_camera_generata)
    {
    case 1:
    {
        if(k<=7)
        {
            camera[k][1][4]=camera[k][1][10]='D';
            camera[k][8][4]=camera[k][8][10]='D';
        }
        else
        {
            camera[k][1][4]=camera[k][1][19]='D';
            camera[k][8][4]=camera[k][8][19]='D';
        }
        break;
    }
    case 2:
    {
        if(k<=7)
        {
            camera[k][1][4]=camera[k][1][10]='D';
            camera[k][8][4]=camera[k][8][10]='D';
            if(locatiecheie)camera[k][8][7]='K';
            else camera[k][1][7]='K';
            if(event!=2)camera[k][5][iesy]='|';
            else camera[k][5][ciesy]='|';
            cheie=0;
        }
        else
        {
            camera[k][1][4]=camera[k][1][19]='D';
            camera[k][8][4]=camera[k][8][19]='D';
            if(locatiecheie)camera[k][8][11]='K';
            else camera[k][1][11]='K';
            if(event!=2)camera[k][5][iesy]='|';
            else camera[k][5][ciesy]='|';
            cheie=0;
        }
        break;
    }
    }
    if(event!=2)camera[k][5][0]=player;
    else camera[k][5][x]=player;
    int miscari=10;
    este_ascuns=0;
    char charprec=' ';
    if(event==3)generare_camera_intunecata(k);
    while(camera[k][5][ciesy]!=player && player_alive)
    {
        cout<<"\033[1m\033[33mCamera"<<' '<<camere_parcurse<<"\033[0m"<<'\n';
        if(cheie)
        {
            if(event!=2)camera[k][5][iesy]=' ';
            else camera[k][5][ciesy]=' ';
        }
        else cout<<"Usa este incuiata. Ai nevoie de o cheie."<<'\n';
        switch(event)
        {
        case 1:
        {
            if((tip_camera_generata==1 || tip_camera_generata==2)&&!este_ascuns)
            {
                system("color 4");
                cout<<"\u001b[31m!!! ATENTIE !!! SE APROPRIE O ENTITATE !!!\u001b[0m"<<'\n';
                if(miscari>1)cout<<"\u001b[31m"<<"!!! MAI AI "<< miscari <<" MISCARI !!!\u001b[0m"<<'\n';
                else cout<<"\u001b[31m"<<"!!! MAI AI 1 MISCARE !!!\u001b[0m"<<'\n';
                if(miscari<=0) player_alive=0;
            }
            break;
        }
        case 2:
        {
            cout<<"Camera pare ca s-a inversat."<<'\n';
            break;
        }
        case 3:
        {
            cout<<"S-au stins luminile. Noroc ca ai o lampa."<<'\n';
            int r=3;
            lanterna(x,y,r,k);
            for(i=0; i<=9; i++)
                cout<<cameraintunecata[i]<<'\n';
            generare_camera_intunecata(k);
            break;
        }
        default:
            break;
        }
        if(event!=3)
            for(i=0; i<=9; i++)
                cout<<camera[k][i]<<'\n';
        comanda=_getch();
        if(event==1 && (comanda=='w'||comanda=='d'||comanda=='s'||comanda=='a'))miscari--;
        switch(comanda)
        {
        case 'w':
        {

            if(camera[k][y-1][x]==' '||camera[k][y-1][x]=='#')
            {
                camera[k][y][x]=charprec;
                charprec=camera[k][y-1][x];
                camera[k][y-1][x]='o';
                --y;
                break;
            }
            else if(camera[k][y-1][x]=='K')
            {
                camera[k][y-1][x]='o';
                camera[k][y][x]=' ';
                --y;
                cheie=1;
                break;
            }
            else if(camera[k][y-1][x]=='D')miscari+=2,player_alive=1,ascuns(este_ascuns,event,k,iesy,y,x);
            else break;
        }
        case 'a':
        {
            if(camera[k][y][x-1]==' '||camera[k][y][x-1]=='#')
            {
                camera[k][y][x]=charprec;
                charprec=camera[k][y][x-1];
                camera[k][y][x-1]='o';
                --x;
                break;
            }
            else if(camera[k][y][x-1]=='K')
            {
                camera[k][y][x-1]='o';
                camera[k][y][x]=' ';
                --x;
                cheie=1;
                break;
            }
            else if(camera[k][y][x-1]=='D')miscari+=2,player_alive=1,ascuns(este_ascuns,event,k,iesy,y,x);
            else break;
        }
        case 'd':
        {
            if(camera[k][y][x+1]==' '||camera[k][y][x+1]=='#')
            {
                camera[k][y][x]=charprec;
                charprec=camera[k][y][x+1];
                camera[k][y][x+1]='o';
                ++x;
                break;
            }
            else if(camera[k][y][x+1]=='K')
            {
                camera[k][y][x+1]='o';
                camera[k][y][x]=' ';
                ++x;
                cheie=1;
                break;
            }
            else if(camera[k][y][x+1]=='D')miscari+=2,player_alive=1,ascuns(este_ascuns,event,k,iesy,y,x);
            else break;
        }
        case 's':
        {
            if(camera[k][y+1][x]==' '||camera[k][y+1][x]=='#')
            {
                camera[k][y][x]=charprec;
                charprec=camera[k][y+1][x];
                camera[k][y+1][x]='o';
                ++y;
                break;
            }
            else if(camera[k][y+1][x]=='K')
            {
                camera[k][y+1][x]='o';
                camera[k][y][x]=' ';
                ++y;
                cheie=1;
                break;
            }
            else if(camera[k][y+1][x]=='D')miscari+=2,player_alive=1,ascuns(este_ascuns,event,k,iesy,y,x);
            else break;
        }
        }
        Sleep(30);
        system("cls");
    }
    if(player_alive==0) camera[k][y][x]=charprec;
    if(event!=2)camera[k][5][iesy]=' ';
    else camera[k][5][ciesy]=' ';
    switch(tip_camera_generata)
    {
    case 1:
    {
        if(k<=7)
        {
            camera[k][1][4]=camera[k][1][10]=' ';
            camera[k][8][4]=camera[k][8][10]=' ';
            break;
        }
        else
        {
            camera[k][1][4]=camera[k][1][19]=' ';
            camera[k][8][4]=camera[k][8][19]=' ';
        }
    }
    case 2:
    {
        if(k<=7)
        {
            camera[k][1][4]=camera[k][1][10]=' ';
            camera[k][8][4]=camera[k][8][10]=' ';
            if(locatiecheie)camera[k][8][7]=' ';
            else camera[k][1][7]=' ';
            if(event!=2)camera[k][5][iesy]=' ';
            else camera[k][5][ciesy]=' ';
        }
        else
        {
            camera[k][1][4]=camera[k][1][19]=' ';
            camera[k][8][4]=camera[k][8][19]=' ';
            if(locatiecheie)camera[k][8][11]=' ';
            else camera[k][1][11]=' ';
            if(event!=2)camera[k][5][iesy]=' ';
            else camera[k][5][ciesy]=' ';
            cheie=0;
        }
        break;
    }
}
}



void hol_cursa()
{
    natural i,j;
    for(i=0; i<=9; i++)
        for(j=0; j<=98; j++)
            if(i==0 || i==9) holcursa[i][j]='_';
            else if(j==0 || j==98) holcursa[i][j]='|';
            else holcursa[i][j]=' ';
    for(i=0; i<=9; i++)
        holcursa[i][99]='\0';
    holcursa[9][0]=holcursa[9][98]='|';
    holcursa[5][98]=' ';

    srand(time(0));
    natural perete=75;
    natural nr_pereti[100]={0};
    while(perete)
    {
        i=rand()%9;
        j=rand()%94;
        if(j<=1)j+=2;
        if(j>=97) j-=2;
        if(i==0)i++;
        if(nr_pereti[j]++<=2)holcursa[i][j]='|';
        perete--;
    }
}

void cursahol(bool &player_alive,int camere)
{
    int i;
    hol_cursa();
    holcursa[5][0]=player;
    player_alive=1;
    char charprec=' ',comanda,smiley=1,charprecs=' ';
    int x=0,y=5,xs=0,ys=5,pxs,pys;
    bool spawn=0;
    pxs=xs;
    pys=ys;
    while(holcursa[5][98]!=player && player_alive)
    {
        cout<<"\033[1m\033[33mCamera "<<camere<<"\033[0m"<<'\n';
        for(i=0; i<=9; i++)
        {
            cout<<holcursa[i];
            cout<<'\n';
        }
        comanda=_getch();
        switch(comanda)
        {
        case 'w':
        {

            if(holcursa[y-1][x]==' '||holcursa[y-1][x]=='#')
            {
                holcursa[y][x]=charprec;
                charprec=holcursa[y-1][x];
                holcursa[y-1][x]='o';
                --y;
                break;
            }
            else break;
        }
        case 'a':
        {
            if(holcursa[y][x-1]==' '||holcursa[y][x-1]=='#')
            {
                holcursa[y][x]=charprec;
                charprec=holcursa[y][x-1];
                holcursa[y][x-1]='o';
                --x;
                break;
            }
            else break;
        }
        case 'd':
        {
            if(holcursa[y][x+1]==' '||holcursa[y][x+1]=='#')
            {
                holcursa[y][x]=charprec;
                charprec=holcursa[y][x+1];
                holcursa[y][x+1]='o';
                ++x;
                break;
            }
            else break;
        }
        case 's':
        {
            if(holcursa[y+1][x]==' '||holcursa[y+1][x]=='#')
            {
                holcursa[y][x]=charprec;
                charprec=holcursa[y+1][x];
                holcursa[y+1][x]='o';
                ++y;
                break;
            }
            else break;
        }
        }
        if(x>=4) spawn=1;
        if(spawn)
        {
            if((holcursa[ys][xs-1]=='|'||holcursa[ys][xs+1]=='|'||holcursa[ys-1][xs]=='|'||holcursa[ys+1][xs]=='|' )&& charprec==' ')
            {
                pys=ys;
                pxs=xs;
            }
            if(ys>y && holcursa[ys-1][xs]!='|')
            {
                holcursa[ys][xs]=charprecs;
                charprecs=holcursa[ys-1][xs];
                ys--;
                holcursa[ys][xs]=smiley;
            }
            else if(xs<x && holcursa[ys][xs+1]!='|')
            {
                holcursa[ys][xs]=charprecs;
                charprecs=holcursa[ys][xs+1];
                xs++;
                holcursa[ys][xs]=smiley;
            }
            else if(ys<y &&holcursa[ys+1][xs]!='|' )
            {
                holcursa[ys][xs]=charprecs;
                charprecs=holcursa[ys+1][xs];
                ys++;
                holcursa[ys][xs]=smiley;
            }
            else if(xs>x && holcursa[ys][xs-1]!='|')
            {
                holcursa[ys][xs]=charprecs;
                charprecs=holcursa[ys][xs-1];
                xs--;
                holcursa[ys][xs]=smiley;
            }

            else if(pys==ys && holcursa[ys][xs+1]=='|')
            {
                holcursa[ys][xs]=charprecs;
                charprecs=holcursa[ys][xs+1];
                if(charprecs=='|') charprecs='#';
                xs++;
                holcursa[ys][xs]=smiley;
            }
            else if(pys==ys && holcursa[ys][xs-1]=='|')
            {
                holcursa[ys][xs]=charprecs;
                charprecs=holcursa[ys][xs-1];
                if(charprecs=='|') charprecs='#';
                xs--;
                holcursa[ys][xs]=smiley;
            }
            else if(pxs==xs && holcursa[ys+1][xs]=='|')
            {
                holcursa[ys][xs]=charprecs;
                charprecs=holcursa[ys+1][xs];
                if(charprecs=='|') charprecs='#';
                ys++;
                holcursa[ys][xs]=smiley;
            }
            else if(pxs==xs && holcursa[ys-1][xs]=='|')
            {
                holcursa[ys][xs]=charprecs;
                charprecs=holcursa[ys-1][xs];
                if(charprecs=='|') charprecs='#';
                ys--;
                holcursa[ys][xs]=smiley;
            }

        }
        Sleep(30);
        system("cls");
        if(spawn && (holcursa[ys][xs+1]=='o'||holcursa[ys][xs-1]=='o'||holcursa[ys-1][xs]=='o'||holcursa[ys+1][xs]=='o'||holcursa[ys][xs]=='o'))
        {
            player_alive=0;
            for(i=0; i<=9; i++)
            {
                cout<<holcursa[i];
                cout<<'\n';
            }
        }
    }
    stillalive=player_alive;
}

void Help()
{
    char comanda='\0';
    system("cls");
    cout<<"Scopul acestui joc este parcurgerea a 100 de camere fara a fi prins de anumite 'entitati' care ar putea aparea in drum."<<'\n';
    cout<<"Entitatile, cat si camerele, vor fi generate aleatoriu. Anumite evenimente nu vor fi aleatorii. "<<'\n';
    cout<<"Primele 5 camere vor contine evenimentele ce se pot intampla in timpul jocului, fiind pentru obisnuirea jucatorului cu acestea."<<'\n';
    cout<<"La fiecare 30 de camere, jucatorul trebuie sa scape de o anumita entitate pe un hol mai larg generat aleatoriu."<<'\n';
    cout<<"Camerele 50 si 100 vor contine un puzzle in care trebuie aleasa corect secventa de usi pentru a descifra codul de 6 iesiri."<<'\n';
    cout<<"Tastele pentru miscare sunt urmatoarele:" << '\n' << "'w' -> miscare in sus;" << '\n' << "'a' -> miscare in dreapta;" << '\n' << "'s' -> miscare in jos;" << '\n' << "'d' -> miscare la dreapta."<<'\n';
    cout<<"Jocul se desfasoare sub forma unui tablou bidimensional, in care punctele de interes sunt notate cu litere, si pentru a fi accesate jucatorul trebuie doar sa se deplaseze inspre ele. Acestea sunt:"<<'\n';
    cout<<"D -> dulap, util pentru ascunderea jucatorului; " <<'\n' << "K -> cheie, pentru descuierea usii, unde este cazul;" << '\n' << "# -> reprezinta o bucata de covor sau un obstacol distrus, jucatorul poate merge pe acesta;"<<'\n'<<"/ -> intuneric."<<'\n';
    cout<<"Evenimentele, precum si entitatile, vor ramane o surpriza :)"<<'\n';
    cout<<'\n'<<'\n'<<'\n';
    cout<<"Pentru a parasi aceasta fereastra, apasa 'm'.";
    while(comanda!='m')
        comanda=_getch();

}

void meniu_principal()
{
    char litera;
    cout<<"\033[1m\033[33m-+-Escape Room-+-"<<'\n'<<"Face o selectie folosind una dintre literele de mai jos.\033[0m"<<'\n';
    cout<<"\033[1m\033[32mp -> Joc nou\033[0m"<<'\n';
    cout<<"\033[1m\033[35mh -> Ajutor\033[0m"<<'\n';
    cout<<"\033[1m\033[31mq -> Iesire din joc\033[0m"<<'\n';
    litera=_getch();
    switch(litera)
    {
    case 'p':
    {
        system("cls");
        while(camere_parcurse!=101 && stillalive)
        {
            srand(time(0));
            camera_generata=rand();
            event_random=rand();
            tip_camera_generata=rand();
            if(camere_parcurse<=5)
                event_random=0;
            if(camere_parcurse==3)
                tip_camera_generata=2;
            if(camere_parcurse==4)
                event_random=3;
            if(camere_parcurse%30!=0 && camere_parcurse!=100 && camere_parcurse!=50)jocul_principal(camera_generata%10,tip_camera_generata%3,event_random%4,stillalive);
            else if(camere_parcurse==50 || camere_parcurse==100)camera_50_100(camere_parcurse);
            else cursahol(stillalive,camere_parcurse);
            camere_parcurse++;
        }
        system("cls");
        if(stillalive)cout<<"\033[1m\033[33mFelicitari! Ai castigat!\033[0m"<<'\n';
        else cout<<"\033[1m\033[31mAi pierdut!\033[0m"<<'\n';
        cout<<'\n';
        litera='\0';
        cout<<"Apasa litera 'm' pentru a reveni la meniu."<<'\n'<<"Apasa litera 'q' pentru a inchide jocul.";
        while(litera!='m'&&litera!='q') litera=_getch();
        stillalive=1;
        camere_parcurse=1;
        system("cls");
        if(litera=='m')meniu_principal();
        else if(litera=='q')system("taskkill /f /im cb_console_runner.exe");
        break;
    }
    case 'h':
    {
        Help();
        system("cls");
        meniu_principal();
        break;
    }
    case 'q':
    {
        system("taskkill /f /im cb_console_runner.exe");
        break;
    }
    default:
    {
        system("cls");
        cout<<"\u001b[31mIntroduceti o litera valida!\u001b[0m"<<'\n';
        meniu_principal();
        break;
    }
    }

}
int main()
{
    system("cls");
    for(int i=0; i<=9; i++)
        initializare_camera(i);
    meniu_principal();
    return 0;
}
