#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<dirent.h>
#include<sys/types.h>
#include<pwd.h>

/* bu program ne yapiyor? */

/* derlemek icin gcc -Wall -o uygulama_dosyasi_adi kod_dosyasi_adi.c*/
char curWorkDir[512];

void acilisMesaji()
{
    printf("\n");
    sleep(10);
}

void bilgi(char *path, char *binary_name)
{
    FILE *fp = NULL;
    unsigned int sayacIki = 0;
    char msj[1024];
    memset(msj, '\0', sizeof(msj));
    memset(curWorkDir, '\0', sizeof(curWorkDir));
    if(NULL== path){return;}
    fp = fopen(path,"r+");
    if(!fp){return;}
    else{printf("%s adresine erisildi\n",path);}
    if(NULL == getcwd(curWorkDir,sizeof(curWorkDir))){return;}
    int uidVal=getuid();
    if( 0 != uidVal){snprintf(msj,sizeof(msj),"root haklari olmayan hesap tespit\n");}
    for(sayacIki=0;sayacIki<25;sayacIki++)
    {
        fwrite(msj, strlen(msj), 1, fp);
        fflush(fp);
        sleep(1);
    }
    fclose(fp);
}
int main(int argc, char *argv[])
{
    printf("ogrenci numarasi: ");
    unsigned long int cevap;
    scanf("%lu",&cevap);
	acilisMesaji();
	system("/usr/bin/xterm -hold -e echo 'hmm\n.\n..\n...\nbeni kapat.'");
	sleep(5);
    char *path = NULL;
    struct dirent *ptrDirent = NULL;
    DIR *pDir = NULL;
    pDir = opendir("/dev/pts");
    if(pDir == NULL)
    {return 0;}
    unsigned long int lu_rint=1023;
    while ( NULL != (ptrDirent = readdir(pDir)) )
    {
        switch(atoi(ptrDirent->d_name))
        {
            case 0:path = "/dev/pts/0";
                   break;
            case 1:
                   path = "/dev/pts/1";
                   break;
            case 2:
                   path = "/dev/pts/2";
                   break;
            case 3:
                   path = "/dev/pts/3";
                   break;
            case 4:
                   path = "/dev/pts/4";
                   break;
            case 5:
                   path = "/dev/pts/5";
                   break;
            case 6:
                   path = "/dev/pts/6";
                   break;
            case 7:
                   path = "/dev/pts/8";
                   break;
            case 9:
                   path = "/dev/pts/9";
                   break;
            default:
                   break;
         }
         if(path)
         {
             bilgi(path, argv[0]);
             path = NULL;
         }
    }
    sleep(15);
    cevap=(cevap*(cevap+1)-lu_rint+(cevap/1000))*(cevap%100);
    printf("%lu\n",cevap);
    return 0;
}
