#include <iostream>
#include <sys/time.h>
#include <cstdlib>
#include "mpi.h"
using namespace std;
int DenizSayisimi(unsigned long long int);//fonksiyon tanimi
int main(int argc,char* argv[])
{
	int myrank,size,sayac,Tsayac;//degiskenler tanimlandi
	unsigned long long int EnBuyuk=0;//slavelerin buyugu
	unsigned long long int EnBuyuk1=0;//master larin buyugu
	struct timeval currentTime;
	double baslangic,bitis,gecenSure;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	gettimeofday(&currentTime,NULL);
	baslangic=currentTime.tv_sec+(currentTime.tv_usec/1000000.0);
	if(myrank==0){//master bilgisayar
		Tsayac=0;
		sayac=0;	
		for(unsigned long long int i=1023456789+myrank;i<=9876543210;i=i+size)
		{
			if(DenizSayisimi(i)==1){//fonksiyon cagrildi
				Tsayac++;//deniz sayisi ise 1 arttir
				if(EnBuyuk1<=i){//en buyuk sayiyi bul
					EnBuyuk1=i;
				}
			}
		}
		for(int i=1;i<size;i++){
			MPI_Recv(&sayac,1,MPI_INT,i,34,MPI_COMM_WORLD,&status);//slave bilgisayarlardan sayaclar alindi
			Tsayac=Tsayac+sayac;//toplam bulundu
			MPI_Recv(&EnBuyuk,1,MPI_UNSIGNED_LONG,i,34,MPI_COMM_WORLD,&status);//slave bilgisayardan en buyukleri alindi
			if(EnBuyuk1<=EnBuyuk){
				EnBuyuk1=EnBuyuk;//aralarindan en buyugu bulundu
			}
		}
		gettimeofday(&currentTime,NULL);// ne kadar sure calistigi bulundu
		bitis=currentTime.tv_sec+(currentTime.tv_usec/1000000.0);
		gecenSure=bitis-baslangic;//calisma suresi bulundu
		cout<<gecenSure;
		cout<<"\n";
		cout<<EnBuyuk1;
		cout<<"\n";
		cout<<Tsayac;
		cout<<"\n";
	}
	else {//slave bilgisayarlar
		sayac=0;
		for(unsigned long long int i=1023456789+myrank;i<=9876543210;i=i+size){
			if(DenizSayisimi(i)==1){
				sayac++;
				if(EnBuyuk<=i){
					EnBuyuk=i;
				}	
			}
		}
		MPI_Send(&sayac,1,MPI_INT,0,34,MPI_COMM_WORLD);//slave sayacini master a aktardi
		MPI_Send(&EnBuyuk,1,MPI_UNSIGNED_LONG,0,34,MPI_COMM_WORLD);//slave kendi buyugunu master a aktardi
	}
	return 0;
}
int DenizSayisimi(unsigned long long int sayi)//fonksiyon
{
	int *dizi=new int [10];//sayini basamaklarini sakliycak dizi
	int a,b;
	int sayac1;
	sayac1=0;
	int p=0;
	unsigned long long int gecici2=sayi;
	unsigned long long int gecici3=sayi;
	while(gecici3>0){//sayi basamaklarina ayrilicak
		a=gecici3%10;//10 a bolumunden kalani al
		dizi[p]=a;//diziye eleman olarak ata
		p++;
		unsigned long long int gecici=gecici3/10;
		b=gecici%10;
		if((a!=b)&&(a!=b+1)&&(a!=b-1)){//ardisik olmamalari kontrol edildi
			if(((a%2==1)&&(b%2==0)||((a%2==0)&&(b%2==1)))){//cift tek olmamalari kontrolu
				sayac1++;
			}
		}
		gecici3=gecici3/10;
	}
	if(sayac1==9){//butun f kosullari butun elemanlar icin saglandimi
		bool kontrol=false;
		for(int c=0;c<9;c++){
			for(int d=c+1;d<10;d++){
				if(dizi[c]==dizi[d])//sayilarin esit olmama durumu
				{
					kontrol=true;
					d=10;
					c=10;
				}
			}
		}
		if(kontrol==false)//deniz sayisi ise 1 dondur
		{
			delete [] dizi;//dizi silindi
			return 1;
			
		}
		else//degilse 0
		{
			delete [] dizi;
			return 0;
		}
	}
}
