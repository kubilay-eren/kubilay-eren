#include "mpi.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;
#define TAG1 25
#define TAG2 34
#define TAG3 19
#define TAG4 94
int main(int argc,char* argv[])
{
	int myRank,size,altLimit,ustLimit,sayi,tahmin;/*giskenler timlandi*/
        /*sonsuz donguler icin iki kontrol ifadesi timlandi*/
	bool kontrol=false;
	int kontrol2=0;
	char tahminin;
	MPI_Status status;
	/*MPI baslat*/
	MPI_Init(&argc,&argv);
	/*grup boyutu belirlemdi*/
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&myRank);
	if(size != 2)
	{
		cout<<"lutfen iki bilgisayar kullin!\n";
		MPI_Abort(MPI_COMM_WORLD,99);/*hata sonlandir*/
	}	
	if(myRank==0)/*master bilgisayar*/
	{
		 /*altLimit ve ustLimit kullanicidan alindi*/
		 cout<<"alt limiti gir:";
		 cin>>altLimit;
		 cout<<"ust limiti gir:";
       		 cin>>ustLimit;
		 srand(time(NULL));
		 /*random sayi uretildi*/
                 sayi=altLimit+(rand()%ustLimit);
		 cout<<"Master Urettigi sayi="<<sayi<<"\n";
		 /*altLimit ve ustLimit slave bilgisayara iletildi*/
		 MPI_Send(&altLimit,1,MPI_INT,1,TAG1,MPI_COMM_WORLD);
		 cout<<"master altLimiti iletti\n";
		 MPI_Send(&ustLimit,1,MPI_INT,1,TAG2,MPI_COMM_WORLD);
		 cout<<"master ustLimiti iletti\n";
		 while(kontrol==false)/*tahmin dogru olana kadar don*/
		 {
			 /*slave bilgisayin bilgisi alindi*/
			 MPI_Recv(&tahmin,1,MPI_INT,1,TAG3,MPI_COMM_WORLD,&status);
			 cout<<"master slave'in tahminini aldi\n";
			 cout<<"slave'in tahmini="<<tahmin<<"\n";
			 if(tahmin<sayi)
			 {
				tahminin='k';
				/*tahminin kucuk oldugu bilgisi iletildi*/
				MPI_Send(&tahminin,1,MPI_CHAR,1,TAG4,MPI_COMM_WORLD);
				cout<<"master tahminin kucuk oldugunu iletti\n";
				kontrol=false;
			 }
			 else if(tahmin>sayi)
			 {
				 tahminin='b';
				 /*tahminin buyuk oldugu bilgisi iletildi*/
				 MPI_Send(&tahminin,1,MPI_CHAR,1,TAG4,MPI_COMM_WORLD);
				 cout<<"master tahminin buyuk oldugunu iletti\n";
				 kontrol=false;
			 }
			 else
			 {
			 	tahminin='d';
				/*tahminin dogru oldugu bilgisi iletildi*/
				MPI_Send(&tahminin,1,MPI_CHAR,1,TAG4,MPI_COMM_WORLD);
			        cout<<"master tahminin dogru oldugunu iletti\n";
				kontrol=true;
			 }
		 }
	}
	else
	{
		 /*altLimit ve ustLimit master bilgisayardan alindi*/
		 MPI_Recv(&altLimit,1,MPI_INT,0,TAG1,MPI_COMM_WORLD,&status);
		 cout<<"slave altLimiti aldi\n";
		 MPI_Recv(&ustLimit,1,MPI_INT,0,TAG2,MPI_COMM_WORLD,&status);
		 cout<<"slave ustLimiti aldi\n";
		 /*sayi tahmin islemi*/
		 tahmin=(altLimit+ustLimit)/2;
		 /*tahmin master bilgisayara iletildi*/
		 MPI_Send(&tahmin,1,MPI_INT,0,TAG3,MPI_COMM_WORLD);
		 cout<<"slave master'a tahminini iletti\n";
		 while(kontrol2==0)/*dogruyu bulana kadara don*/
		 {
			/*master bilgisayardan cevabin dogru olup olmadigi*/
			/*bilgisi alindi*/
			MPI_Recv(&tahminin,1,MPI_CHAR,0,TAG4,MPI_COMM_WORLD,&status);
			cout<<"tahminin dogru olup olmadigi bilgisini aldi\n";
			if(tahminin=='k')
			{
				tahmin=(tahmin+ustLimit)/2;/*limit degisti*/
				/*yeni tahmin master bilgisayara gonderildi*/
				MPI_Send(&tahmin,1,MPI_INT,0,TAG3,MPI_COMM_WORLD);
				cout<<"yeni tahmin master'a yollandi\n";
				kontrol2=0;
			}
			else if(tahminin=='b')
			{
				tahmin=(tahmin+altLimit)/2;/*limit degisti*/
				/*yeni tahmin master bilgisayara gonderildi*/
				MPI_Send(&tahmin,1,MPI_INT,0,TAG3,MPI_COMM_WORLD);
				kontrol2=0;
			}
			else
			{
				cout<<"tahmin dogru oyun biti\n";
				/*2 degeri 1 yapildi dongu sonlandi*/
				kontrol2=1;
			}
		 }
	}
	/*MPI Bitir*/
	MPI_Finalize();
	return 0;	
}
