#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define DEVRE "devre.txt"
#define BASKA "baska_dosya.txt"
#define DEGER "deger.txt"
#define KOMUT "komut.txt"
#define LOG "log.txt"

//Devrenin t�m bilgileri tutulur.
struct lojik
{
	
	char tum[2]; //Devredeki u�lar�n isimleri tutulur.
	char deger[2]; //deger.txt den okutulan de�erler tutulur.
	int deger2;    //deger.txt den okutulan de�erler int' e �evirilerek burada tutulur.
	char devreUc[2]; //S komutundaki u�/u�lar�n bilgisi tutulur.
	int ilkDeger;	//S komutundaki u�/u�lar�n ilk de�eri tutulur.
	int sonDeger;	//S komutundaki u�/u�lar�n son de�eri tutulur.
	int ns;			//S komutundaki nanosaniye tutulur.
};

void kapiNAND(struct lojik *d,int j,int z,int x,char islemKapi[5][5],int k,int dizi[])
{
	int sonuc=1;	//Kap� i�leminin ��z�m�nde sonucu bulmak i�in kullan�l�r.
	int giris[5]; 	//Kap� i�leminde kullan�lcak de�erler tutulur.
	int i=0;		
	int s=2;		
	int t=0;
	int nanosaniye=dizi[0];		//Ge�en s�re tutulur.
	int w=dizi[1];				//S komutundaki struct �n boyutu tutulur.
	int n=sizeof(islemKapi);	//islemKapi n�n boyutu bulunur.
	etiket1:
	for(i=0;i<k;i++)
	{
		//islemKapi daki girisler bulunur ve de�erler atan�r.
		if(strcmp(islemKapi[s],d[i].tum)==0)
		{
			
			giris[t]=d[i].deger2;
			t++;
		}
	}
	s++;
	if(s!=n)
	{
		goto etiket1;
	}
	else
	{
		goto etiket;
	}
	etiket:
	//Kapi i�lemi yap�l�r.
	for(i=0;i<t;i++)
	{
		sonuc*=giris[i];
	}
	//Nand kap�s�na g�re i�lem yap�ld��� i�in sonucun de�ili al�n�r.	
	if(sonuc==0)
	{
		sonuc=1;
	}
	//Nand kap�s�na g�re i�lem yap�ld��� i�in sonucun de�ili al�n�r.
	else if(sonuc==1)
	{
		sonuc=0;
	}
	for(i=0;i<k;i++)
	{
		//islemKapi daki ��k�� ucu bulunur ve sonuc de�eri atan�r.
		if(strcmp(islemKapi[1],d[i].tum)==0)
		{
			//Devreyi simule etmek i�in de�erler tutulur.
			strcpy(d[w].devreUc,d[i].tum); 
			d[w].ilkDeger=d[i].deger2;
			d[i].deger2=sonuc;
			d[w].sonDeger=d[i].deger2;
		}
	}
	int sure=atoi(islemKapi[n]);	//islemKapi n�n nanosaniye de�eri int'e �evirilir.
	
	if(sure>=nanosaniye)
	{
		while(1)
		{
			if((sure-nanosaniye)==0)
			{
				break;
			}
			nanosaniye++;
		}
	}
	d[w].ns=nanosaniye;
	w++;
	nanosaniye++;
	dizi[0]=nanosaniye;
	dizi[1]=w;
}
void kapiXOR(struct lojik *d,int j,int z,int x,char islemKapi[5][5],int k,int dizi[])
{
	int sonuc;			//Kap� i�leminin ��z�m�nde sonucu bulmak i�in kullan�l�r.
	int giris[5];		//Kap� i�leminde kullan�lcak de�erler tutulur.
	int i=0;
	int s=2;
	int t=0;
	int n=sizeof(islemKapi);	//islemKapi n�n boyutu bulunur.

	int nanosaniye=dizi[0];		//Ge�en s�re tutulur.
	int w=dizi[1];				//S komutundaki struct �n boyutu tutulur.
	etiket1:
	
	for(i=0;i<k;i++)
	{
		//islemKapi daki girisler bulunur ve de�erler atan�r.
		if(strcmp(islemKapi[s],d[i].tum)==0)
		{
			giris[t]=d[i].deger2;
			t++;
		}
	}
	s++;
	if(s!=n)
	{
		goto etiket1;
	}
	else
	{
		goto etiket;
	}
	
	etiket:
	//XOR kap�s�na g�re i�lemler yap�l�r.
	if((giris[0]==1 && giris[1]==1) || (giris[0]==0 && giris[1]==0))
	{
		sonuc=0;	
	}
	//XOR kap�s�na g�re i�lemler yap�l�r.
	else if((giris[0]==0 && giris[1]==1) || (giris[0]==1 && giris[1]==0))
	{
		sonuc=1;	
	} 
	for(i=0;i<k;i++)
	{
		//islemKapi daki ��k�� ucu bulunur ve sonuc de�eri atan�r.
		if(strcmp(islemKapi[1],d[i].tum)==0)
		{
			//Devreyi simule etmek i�in de�erler tutulur.
			strcpy(d[w].devreUc,d[i].tum);
			d[w].ilkDeger=d[i].deger2;
			d[i].deger2=sonuc;
			d[w].sonDeger=d[i].deger2;
		}
	}
	
	int sure=atoi(islemKapi[n]);		//islemKapi n�n nanosaniye de�eri int'e �evirilir.
	if(sure>=nanosaniye)
	{
		while(1)
		{
			if((sure-nanosaniye)==0)
			{
				break;
			}
			nanosaniye++;
		}
	}
	d[w].ns=nanosaniye;
	w++;
	nanosaniye++;
	dizi[0]=nanosaniye;
	dizi[1]=w;
}
void kapiNOR(struct lojik *d,int j,int z,int x,char islemKapi[5][5],int k,int dizi[])
{
	int sonuc=0;		//Kap� i�leminin ��z�m�nde sonucu bulmak i�in kullan�l�r.
	int giris[5];		//Kap� i�leminde kullan�lcak de�erler tutulur.
	int i=0;
	int s=2;
	int t=0;
	int nanosaniye=dizi[0];		//Ge�en s�re tutulur.
	int w=dizi[1];				//S komutundaki struct �n boyutu tutulur.
	int n=sizeof(islemKapi);	//islemKapi n�n boyutu bulunur.

	etiket1:
	for(i=0;i<k;i++)
	{
		//islemKapi daki girisler bulunur ve de�erler atan�r.
		if(strcmp(islemKapi[s],d[i].tum)==0)
		{
			giris[t]=d[i].deger2;
			t++;
		}
	}
	s++;
	if(s!=n)
	{
		goto etiket1;
	}
	else
	{
		goto etiket;
	}
	etiket:
	//Kap� i�lemleri yap�l�r.
	for(i=0;i<t;i++)
	{
		sonuc+=giris[i];
	}	
	//NOR kap�s�na g�re i�lem yap�ld��� i�in sonucun de�ili al�n�r.
	if(sonuc==0)
	{
		sonuc=1;
	}
	//NOR kap�s�na g�re i�lem yap�ld��� i�in sonucun de�ili al�n�r.
	else if(sonuc==1 || sonuc==2)
	{
		sonuc=0;
	}
	for(i=0;i<k;i++)
	{
		//islemKapi daki ��k�� ucu bulunur ve sonuc de�eri atan�r.
		if(strcmp(islemKapi[1],d[i].tum)==0)
		{
			//Devreyi simule etmek i�in de�erler tutulur.
			strcpy(d[w].devreUc,d[i].tum);
			d[w].ilkDeger=d[i].deger2;
			d[i].deger2=sonuc;
			d[w].sonDeger=d[i].deger2;
		}
	}
	int sure=atoi(islemKapi[n]);	//islemKapi n�n nanosaniye de�eri int'e �evirilir.
	if(sure>=nanosaniye)
	{
		while(1)
		{
			if((sure-nanosaniye)==0)
			{
				break;
			}
			nanosaniye++;
		}
	}
	d[w].ns=nanosaniye;
	w++;
	nanosaniye++;
	dizi[0]=nanosaniye;
	dizi[1]=w;
}
void kapiAND(struct lojik *d,int j,int z,int x,char islemKapi[5][5],int k,int dizi[])
{
	int sonuc=1;		//Kap� i�leminin ��z�m�nde sonucu bulmak i�in kullan�l�r.
	int giris[5];		//Kap� i�leminde kullan�lcak de�erler tutulur.
	int i=0;
	int s=2;
	int t=0;
	
	int nanosaniye=dizi[0];		//Ge�en s�re tutulur.
	int w=dizi[1];				//S komutundaki struct �n boyutu tutulur.
	int n=sizeof(islemKapi);	//islemKapi n�n boyutu bulunur.			
	etiket1:
	for(i=0;i<k;i++)
	{
		//islemKapi daki girisler bulunur ve de�erler atan�r.
		if(strcmp(islemKapi[s],d[i].tum)==0)
		{
			giris[t]=d[i].deger2;
			t++;
		}
	}
	s++;
	if(s!=n)
	{
		goto etiket1;
	}
	else
	{
		goto etiket;
	}
	etiket:
	//AND Kap�s�na g�re i�lemler yap�l�r.
	for(i=0;i<t;i++)
	{
		sonuc*=giris[i];
	}	
	if(sonuc==0)
	{
		sonuc=0;
	}
	else if(sonuc==1)
	{
		sonuc=1;
	}
	for(i=0;i<k;i++)
	{
		//islemKapi daki ��k�� ucu bulunur ve sonuc de�eri atan�r.
		if(strcmp(islemKapi[1],d[i].tum)==0)
		{
			//Devreyi simule etmek i�in de�erler tutulur.
			strcpy(d[w].devreUc,d[i].tum);
			d[w].ilkDeger=d[i].deger2;
			d[i].deger2=sonuc;
			d[w].sonDeger=d[i].deger2;
		}
	}
	int sure=atoi(islemKapi[n]);	//islemKapi n�n nanosaniye de�eri int'e �evirilir.	
	if(sure>=nanosaniye)
	{
		while(1)
		{
			if((sure-nanosaniye)==0)
			{
				break;
			}
			nanosaniye++;
		}
	}
	d[w].ns=nanosaniye;
	w++;
	nanosaniye++;
	dizi[0]=nanosaniye;
	dizi[1]=w;
}
void kapiOR(struct lojik *d,int j,int z,int x,char islemKapi[5][5],int k,int dizi[])
{
	int sonuc=0;		//Kap� i�leminin ��z�m�nde sonucu bulmak i�in kullan�l�r.
	int giris[5];		//Kap� i�leminde kullan�lcak de�erler tutulur.
	int i=0;
	int s=2;
	int t=0;
	int nanosaniye=dizi[0];		//Ge�en s�re tutulur.
	int w=dizi[1];				//S komutundaki struct �n boyutu tutulur.
	int n=sizeof(islemKapi);	//islemKapi n�n boyutu bulunur.	
	etiket1:
	for(i=0;i<k;i++)
	{
		//islemKapi daki girisler bulunur ve de�erler atan�r.
		if(strcmp(islemKapi[s],d[i].tum)==0)
		{
			giris[t]=d[i].deger2;
			t++;
		}
	}
	s++;
	if(s!=n)
	{
		goto etiket1;
	}
	else
	{
		goto etiket;
	}
	etiket:
	//OR Kap� i�lemleri yap�l�r.
	for(i=0;i<t;i++)
	{
		sonuc+=giris[i];
	}
	if(sonuc==0)
	{
		sonuc=0;
	}
	else if(sonuc==1 || sonuc==2)
	{
		sonuc=1;
	}
	for(i=0;i<k;i++)
	{
		//islemKapi daki ��k�� ucu bulunur ve sonuc de�eri atan�r.
		if(strcmp(islemKapi[1],d[i].tum)==0)
		{
			//Devreyi simule etmek i�in de�erler tutulur.
			strcpy(d[w].devreUc,d[i].tum);
			d[w].ilkDeger=d[i].deger2;
			d[i].deger2=sonuc;
			d[w].sonDeger=d[i].deger2;
		}
	}
	int sure=atoi(islemKapi[n]);	//islemKapi n�n nanosaniye de�eri int'e �evirilir.
	if(sure>=nanosaniye)
	{
		while(1)
		{
			if((sure-nanosaniye)==0)
			{
				break;
			}
			nanosaniye++;
		}
	}
	d[w].ns=nanosaniye;
	w++;
	nanosaniye++;
	dizi[0]=nanosaniye;
	dizi[1]=w;
}
void kapiNOT(struct lojik *d,int j,int z,int x,char islemKapi[5][5],int k,int dizi[])
{
	int sonuc;			//Kap� i�leminin ��z�m�nde sonucu bulmak i�in kullan�l�r.
	int giris;		//Kap� i�leminde kullan�lcak de�erler tutulur.
	int i=0;
	int s=2;
	int t=0;
	int n=sizeof(islemKapi);	//islemKapi n�n boyutu bulunur.
	int nanosaniye=dizi[0];		//Ge�en s�re tutulur.
	int w=dizi[1];				//S komutundaki struct �n boyutu tutulur.
	etiket1:
	for(i=0;i<k;i++)
	{
		//islemKapi daki girisler bulunur ve de�erler atan�r.
		if(strcmp(islemKapi[s],d[i].tum)==0)
		{
			giris=d[i].deger2;
		}
	}
		s++;
	if(s!=n)
	{
		goto etiket1;
	}
	else
	{
		goto etiket;
	}
	etiket:
	//NOT kap�s�na g�re i�lemler yap�l�r.
	if(giris==0)
	{
		sonuc=1;
	}
	else if(giris==1)
	{
		sonuc=0;
	}
	for(i=0;i<k;i++)
	{
		//islemKapi n�n nanosaniye de�eri int'e �evirilir.
		if(strcmp(islemKapi[1],d[i].tum)==0)
		{
			//Devreyi simule etmek i�in de�erler tutulur.
			strcpy(d[w].devreUc,d[i].tum);
			d[w].ilkDeger=d[i].deger2;
			d[i].deger2=sonuc;
			d[w].sonDeger=d[i].deger2;
		}
	}
	int sure=atoi(islemKapi[n]);	//islemKapi n�n nanosaniye de�eri int'e �evirilir.
	if(sure>=nanosaniye)
	{
		while(1)
		{
			if((sure-nanosaniye)==0)
			{
				break;
			}
			nanosaniye++;
		}
	}
	d[w].ns=nanosaniye;
	w++;
	nanosaniye++;
	dizi[0]=nanosaniye;
	dizi[1]=w;
}
void kapiIslem(struct lojik *d,char uc[],char kapi1[5][5],char kapi2[5][5],char kapi3[5][5],int j,int z,int x,int k,int dizi[])
{
	int i=0,s=0,t=0,var1=0,var2=0,var3=0,p;
	char islemKapi1[5][5];		//��lem yap�lacak ilk kap�n�n de�erleri tutulur.	
	char islemKapi2[5][5];		//��lem yap�lacak ikinci kap�n�n de�erleri tutulur.
	char islemKapi3[5][5];		//��lem yap�lacak ���nc� kap�n�n de�erleri tutulur.
	char islemKapi4[5][5];		//��lem tekrar� yap�lacak kap�n�n de�erleri tutulur.
	int kapiSure1=atoi(kapi1[j]);		//kapi1'in nanosaniye de�eri int'e �evirilir.
	int kapiSure2=atoi(kapi2[x]);		//kapi2'in nanosaniye de�eri int'e �evirilir.
	int kapiSure3=atoi(kapi3[z]);		//kapi3'in nanosaniye de�eri int'e �evirilir.
	for(p=2;p<j;p++)
	{
		//De�i�mesi istenilen ucun de�eri 1 yap�l�r.
		if(strcmp(uc,kapi1[p])==0)
		{
			var1=1;
		}
		
	}
	for(p=2;p<x;p++)
	{
		//De�i�mesi istenilen ucun de�eri 1 yap�l�r.
		if(strcmp(uc,kapi2[p])==0)
		{
			var2=1;
		}
	}
	for(p=2;p<z;p++)
	{
		//De�i�mesi istenilen ucun de�eri 1 yap�l�r.
		if(strcmp(uc,kapi3[p])==0)
		{
			var3=1;
		}
	}
	if(var1==1 && var2==1)
	{

		//kapi1 ve kapi2'nin s�releri kar��la�t�r�l�r.
		if(kapiSure1<kapiSure2)
		{
		//kapi1'in s�resi k���k ise islemKapi1'e de�erleri kopyalan�r.
		while(i<=j)
		{
			strcpy(islemKapi1[i],kapi1[i]);
			i++;
		}
		//kapi2 ve kapi3'�n s�releri kar��la�t�r�l�r.
		if(kapiSure2<kapiSure3)
		{
			while(s<=x && t<=z)
			{
				strcpy(islemKapi2[s],kapi2[s]);		//kapi2'in s�resi k���k ise islemKapi2'ye de�erleri kopyalan�r.
				strcpy(islemKapi3[t],kapi3[t]);		//kapi3'�n de�erleri islemkapi3'e kopyalan�r.
				s++;
				t++;
			}
		}
		//Kap� s�releri �ak���yor mu diye kontrol edilir.
		else if(kapiSure2==(kapiSure3+kapiSure1))
		{
			//2 kap�dan birinin rastgele se�ilmesi i�in i�lem yap�l�r.
			srand(time(NULL)); 
			int rastgele=1+rand()%2;
			//kapi2 �nce i�leme al�n�r.
			if(rastgele==1)
			{
				while(s<=x && t<=z)
				{
					strcpy(islemKapi2[s],kapi2[s]);				//kapi2'nin de�erleri islemKapi2'e  kopyalan�r.
					strcpy(islemKapi3[t],kapi3[t]);				//kapi3'�n de�erleri islemkapi3'e kopyalan�r.
					s++;
					t++;
				}
			}
			//kapi3 �nce i�leme al�n�r.
			else if(rastgele==2)
			{
				while(s<=x && t<=z)
				{
					strcpy(islemKapi2[t],kapi3[t]);				//kapi3'�n de�erleri islemKapi2'e  kopyalan�r.
					strcpy(islemKapi3[s],kapi2[s]);				//kapi2'nin de�erleri islemKapi3'e  kopyalan�r.
					strcpy(islemKapi4[t],kapi3[t]);				//��lem tekrar� olaca�� i�in kapi3'�n de�erleri islemKapi4'e kopyalan�r.
					s++;
					t++;
					
				}
			}
		}
		else
		{
			while(s<=x && t<=z)
			{
				strcpy(islemKapi2[t],kapi3[t]);		//kapi3'�n de�erleri islemKapi2'e  kopyalan�r.
				strcpy(islemKapi3[s],kapi2[s]);		//kapi2'nin de�erleri islemKapi3'e  kopyalan�r.
				s++;
				t++;
			}
		}
	}
	//kapi1 ve kapi2'nin s�releri kar��la�t�r�l�r.
	else if(kapiSure1>kapiSure2)
	{
		//kapi2'nin s�resi k���k ise islemKapi1'e de�erleri kopyalan�r.
		while(i<=x)
		{
			strcpy(islemKapi1[i],kapi2[i]);		
			i++;
		}
		//kapi1 ve kapi3'�n s�releri kar��la�t�r�l�r.
		if(kapiSure1<kapiSure3)
		{
			while(s<=j && t<=z)
			{
				strcpy(islemKapi2[s],kapi1[s]);		//kapi1'in s�resi k���k ise de�erleri islemKapi2'ye kopyalan�r.
				strcpy(islemKapi3[t],kapi3[t]);		//kapi3'�n de�erleri islemKapi3'e kopyalan�r.
				s++;
				t++;
			}
		}
		//Kap� s�releri �ak���yor mu diye kontrol edilir.
		else if(kapiSure1==(kapiSure3+kapiSure2))
		{
			//2 kap�dan birinin rastgele se�ilmesi i�in i�lem yap�l�r.
			srand(time(NULL)); 
			int rastgele=1+rand()%2;
			//kapi1 �nce i�leme al�n�r.
			if(rastgele==1)
			{
				while(s<=j && t<=z)
				{
					strcpy(islemKapi2[s],kapi1[s]);		//kapi1'in de�erleri islemkapi2'ye kopyalan�r.
					strcpy(islemKapi3[t],kapi3[t]);		//kapi3'�n de�erleri islemKapi3'e kopyalan�r.
					s++;
					t++;
				}
			}
			//kapi3 �nce i�leme al�n�r.
			else if(rastgele==2)
			{
				while(s<=j && t<=z)
				{
					strcpy(islemKapi2[t],kapi3[t]);		//kapi3'�n de�erleri islemKapi2'e kopyalan�r.
					strcpy(islemKapi3[s],kapi1[s]);		//kapi1'�n de�erleri islemKapi3'e kopyalan�r.
					strcpy(islemKapi4[t],kapi3[t]);		//��lem tekrar� olaca�� i�in kapi3'�n de�erleri islemKapi4'e kopyalan�r.
					s++;
					t++;
				}
			}
		}
		else
		{
			while(s<=j && t<=z)
				{
					strcpy(islemKapi2[t],kapi3[t]);		//kapi3'�n de�erleri islemKapi2'ye kopyalan�r.
					strcpy(islemKapi3[s],kapi1[s]);		//kapi1'in de�erleri islemKapi3'e kopyalan�r.
					s++;
					t++;
				}
		}		
	}
	}
	else if(var1==1 && var2==0)
	{
		while(i<=j && t<=z)
		{
			strcpy(islemKapi1[i],kapi1[i]);
			strcpy(islemKapi2[t],kapi3[t]);
			i++;
			t++;
		}
	}
	else if(var1==0 && var2==1)
	{
		
		while(s<=x && t<=z)
		{
			strcpy(islemKapi1[s],kapi2[s]);
			strcpy(islemKapi2[t],kapi3[t]);
			s++;
			t++;
		}
	}
	else if(var3==1)
	{
		while(t<=z)
		{
			strcpy(islemKapi1[t],kapi3[t]);
			t++;
		}
	}
	//islemKapi1'in kapi t�r�ne g�re fonksiyon �a�r�l�r.
	if(strcmp(islemKapi1[0],"NAND")==0)
	{
		kapiNAND(d,j,z,x,islemKapi1,k,dizi);
	}
	if(strcmp(islemKapi1[0],"AND")==0)
	{
		kapiAND(d,j,z,x,islemKapi1,k,dizi);
	}
	if(strcmp(islemKapi1[0],"NOR")==0)
	{
		kapiNOR(d,j,z,x,islemKapi1,k,dizi);
	}
	if(strcmp(islemKapi1[0],"OR")==0)
	{
		kapiOR(d,j,z,x,islemKapi1,k,dizi);
	}
	if(strcmp(islemKapi1[0],"XOR")==0)
	{
		kapiXOR(d,j,z,x,islemKapi1,k,dizi);
	}
	if(strcmp(islemKapi1[0],"NOT")==0)
	{
		kapiNOT(d,j,z,x,islemKapi1,k,dizi);
	}
	//islemKapi2'nin kapi t�r�ne g�re fonksiyon �a�r�l�r.
	if(strcmp(islemKapi2[0],"NAND")==0)
	{
		kapiNAND(d,j,z,x,islemKapi2,k,dizi);
	}
	if(strcmp(islemKapi2[0],"AND")==0)
	{
		kapiAND(d,j,z,x,islemKapi2,k,dizi);
	}
	if(strcmp(islemKapi2[0],"NOR")==0)
	{
		kapiNOR(d,j,z,x,islemKapi2,k,dizi);
	}
	if(strcmp(islemKapi2[0],"OR")==0)
	{
		kapiOR(d,j,z,x,islemKapi2,k,dizi);
	}
	if(strcmp(islemKapi2[0],"XOR")==0)
	{
		kapiXOR(d,j,z,x,islemKapi2,k,dizi);
	}
	if(strcmp(islemKapi2[0],"NOT")==0)
	{
		kapiNOT(d,j,z,x,islemKapi2,k,dizi);
	}
	//islemKapi3'�n kapi t�r�ne g�re fonksiyon �a�r�l�r.
	if(strcmp(islemKapi3[0],"NAND")==0)
	{
		kapiNAND(d,j,z,x,islemKapi3,k,dizi);
	}
	if(strcmp(islemKapi3[0],"AND")==0)
	{
		kapiAND(d,j,z,x,islemKapi3,k,dizi);
	}
	if(strcmp(islemKapi3[0],"NOR")==0)
	{
		kapiNOR(d,j,z,x,islemKapi3,k,dizi);
	}
	if(strcmp(islemKapi3[0],"OR")==0)
	{
		kapiOR(d,j,z,x,islemKapi3,k,dizi);
	}
	if(strcmp(islemKapi3[0],"XOR")==0)
	{
		kapiXOR(d,j,z,x,islemKapi3,k,dizi);
	}
	if(strcmp(islemKapi3[0],"NOT")==0)
	{
		kapiNOT(d,j,z,x,islemKapi3,k,dizi);
	}
	//islemKapi4'�n kapi t�r�ne g�re fonksiyon �a�r�l�r.
	if(strcmp(islemKapi4[0],"NAND")==0)
	{
		kapiNAND(d,j,z,x,islemKapi4,k,dizi);
	}
	if(strcmp(islemKapi4[0],"AND")==0)
	{
		kapiAND(d,j,z,x,islemKapi4,k,dizi);
	}
	if(strcmp(islemKapi4[0],"NOR")==0)
	{
		kapiNOR(d,j,z,x,islemKapi4,k,dizi);
	}
	if(strcmp(islemKapi4[0],"OR")==0)
	{
		kapiOR(d,j,z,x,islemKapi4,k,dizi);
	}
	if(strcmp(islemKapi4[0],"XOR")==0)
	{
		kapiXOR(d,j,z,x,islemKapi4,k,dizi);
	}
	if(strcmp(islemKapi4[0],"NOT")==0)
	{
		kapiNOT(d,j,z,x,islemKapi4,k,dizi);
	}
	
}

void komutY(char komut[],char uc[])	
{
	
	FILE *dosya4,*dosya;		//Dosyalar� a�mak i�in tan�mlan�rlar.
	char c; 					//devreyi yazd�rmak i�in kullan�l�r.,
	//LOG isimli dosyan�n a��l�p a��lmad��� kontrol edilir.
	if((dosya4=fopen(LOG,"ab+"))==NULL)
	{
		printf("Dosya acilamadi");
		exit(1);
	}
	//DEVRE isimli dosyan�n a��l�p a��lmad��� kontrol edilir.
	if((dosya=fopen(DEVRE,"r"))==NULL)
	{	
		printf("Dosya acilamadi");
		exit(1);
	}
	if(strcmp(uc,"devre.txt")==0)
	{
		//devre yaz�l�r.
		while ((c = fgetc(dosya)) != EOF) {		
		printf("%c", c);
		}
	}
	//LOG'a yap�lan i�lemler yaz�l�r.
	time_t timer=time(NULL);
	fprintf(dosya4,"%s\t\t\t\t\t%s %s\t%s yuklendi\n",ctime(&timer),komut,DEVRE,DEVRE);
	fprintf(dosya4,"\n");
}
void komutI(char komut[],struct lojik *d,char uc[])
{
	int i,j=0;
	char c;						//De�erleri yazd�rmak i�in kullan�l�r.
	FILE *dosya4,*dosya2;		//Dosyalar� a�mak i�in tan�mlan�rlar.
	//LOG isimli dosyan�n a��l�p a��lmad��� kontrol edilir.
	if((dosya4=fopen(LOG,"a"))==NULL)
	{
		printf("Dosya acilamadi");
		exit(1);
	}
	//DEGER isimli dosyan�n a��l�p a��lmad��� kontrl edilir.
	if((dosya2=fopen(DEGER,"r"))==NULL)
	{
		printf("Dosya acilamadi");
		exit(1);
	}
	if(strcmp(uc,"deger.txt")==0)
	{
		//Devrenin u�lar� ve de�erleri yaz�l�r.
		while ((c = fgetc(dosya2)) != EOF) {		
		printf("%c", c);
		}
	}
	//LOG'a yap�lan i�lemler yaz�l�r.
	time_t timer=time(NULL);
	fprintf(dosya4,"\n%s\t\t\t\t\t%s %s\tdegerler atandi\n",ctime(&timer),komut,DEGER);
	fprintf(dosya4,"\n");
}
void komutH(char komut[],struct lojik *d,char uc[],int k,int dizi[])
{
	int nanosaniye=0,w=0;	
	int i,j;
	FILE *dosya4;	//Dosya a�mak i�in tan�mlan�r.
	//LOG isimli dosyan�n a��l�p a��lmad��� kontrol edilir.
	if((dosya4=fopen(LOG,"a"))==NULL)
	{
		printf("Dosya acilamadi");
		exit(1);
	}
	//LOG a yap�lan i�lemler yaz�l�r.
	time_t timer=time(NULL);
	fprintf(dosya4,"\n%s\t\t\t\t\t\t%s %s\t\t%s girisi birlendi\n",ctime(&timer),komut,uc,uc);
	fprintf(dosya4,"\n");
	for(i=0;i<k;i++)
	{
		//De�i�mesi istenilen ucun de�eri 1 yap�l�r.
		if(strcmp(uc,d[i].tum)==0)
		{
			d[w].ilkDeger=d[i].deger2;
			d[i].deger2=1;
			d[w].sonDeger=d[i].deger2;
		}
	}
	strcpy(d[w].devreUc,uc);
	d[w].ns=nanosaniye;
	w++;
	nanosaniye++;
	dizi[0]=nanosaniye;
	dizi[1]=w;
}

void komutL(char komut[],struct lojik *d,char uc[],int k,int dizi[])
{
	int i,nanosaniye=0,w=0;
	FILE *dosya4; //Dosya a�mak i�in tan�mlan�r.
	//LOG isimli dosyan�n a��l�p a��lmad��� kontrol edilir.
	if((dosya4=fopen(LOG,"ab"))==NULL)
	{
		printf("Dosya acilamadi");
		exit(1);
	}
	//LOG'a yap�lan i�lemler yaz�l�r.
	time_t timer=time(NULL);
	fprintf(dosya4,"\n%s\t\t\t\t\t\t%s %s\t\t%s girisi s�f�rland�\n",ctime(&timer),komut,uc,uc);
	fprintf(dosya4,"\n");
	for(i=0;i<k;i++)
	{
		//De�i�tirilmesi istenen ucun de�eri 0 yap�l�r.
		if(strcmp(uc,d[i].tum)==0)
		{
			d[w].ilkDeger=d[i].deger2;
			d[i].deger2=0;
			d[w].sonDeger=d[i].deger2;
		}
	}
	strcpy(d[w].devreUc,uc);
	d[w].ns=nanosaniye;
	w++;
	nanosaniye++;
	dizi[0]=nanosaniye;
	dizi[1]=w;
}
void komutS(struct lojik *d,int dizi[],char komut[])
{
	int i;
	FILE *dosya4;	//Dosya a�mak i�in tan�mlan�r.
	//LOG isimli dosyan�n a��l�p a��lmad���n� kontrol eder.
	if((dosya4=fopen(LOG,"ab+"))==NULL)
	{
		printf("Dosya acilamadi");
		exit(1);
	}
	//Devredeki de�i�imleri yazd�r�r.
	for(i=0;i<dizi[1];i++)
	{
		printf("%dns : %s %d->%d\n",d[i].ns,d[i].devreUc,d[i].ilkDeger,d[i].sonDeger);
	}
	//LOG'a yap�lan i�lemler yaz�l�r.
	time_t timer=time(NULL);
	fprintf(dosya4,"%s\t\t\t\t\t\t%s \t\t",ctime(&timer),komut);
	for(i=0;i<dizi[1];i++)
	{
		fprintf(dosya4,"%dns:%s %d->%d\t\t\t\t\t\t\t\t\t\t\t",d[i].ns,d[i].devreUc,d[i].ilkDeger,d[i].sonDeger);
	}
}
void komutG(struct lojik *d,char uc[],int k,char komut[])
{
	int i;
	FILE *dosya4;	//Dosya a�mak i�in tan�mlan�r.
	//LOG isimli dosyan�n a��l�p a��lmad��� kontrol edilir.
	if((dosya4=fopen(LOG,"ab+"))==NULL)
	{
		printf("Dosya acilamadi");
		exit(1);
	}
	for(i=0;i<k;i++)
	{
		//Yazd�r�lmas� istenen ucun son de�eri yaz�l�r.
		if(strcmp(uc,d[i].tum)==0)
		{
			printf("%s:%d\n",uc,d[i].deger2);
			//LOG'a yap�lan i�lemler yaz�l�r.
			time_t timer=time(NULL);
			fprintf(dosya4,"%s\t\t\t\t\t\t%s %s\t\t%s:%d",ctime(&timer),komut,uc,uc,d[i].deger2);
		}
	}
}
void komutGyildiz(struct lojik *d,int k,char komut[])
{
	int i;
	FILE *dosya4;	//Dosya a�mak i�in tan�mlan�r.
	//LOG isimli dosyan�n a��l�p a��lmad��� kontrol edilir.
	if((dosya4=fopen(LOG,"ab+"))==NULL)
	{
		printf("Dosya acilamadi");
		exit(1);
	}
	//LOG'a yap�lan i�lemler yaz�l�r.
	time_t timer=time(NULL);
	fprintf(dosya4,"%s\t\t\t\t\t\t%s \t\t",ctime(&timer),komut);
	//T�m u�lar�n son de�erleri yaz�l�r.
	for(i=0;i<k;i++)
	{
		printf("%s:%d\n",d[i].tum,d[i].deger2);
		//LOG'a yap�lan i�lemler yaz�l�r.
		fprintf(dosya4,"%s:%d\t\t\t\t\t\t\t\t\t\t\t\t",d[i].tum,d[i].deger2);
	}


}
void komutK(struct lojik *d,int dizi[],int k,char kapi_1[5][5],char kapi_2[5][5],char kapi_3[5][5],int j,int z,int x)
{
	char uc[10];
	char komut[10]; 		
	FILE *dosya3;	//Dosya a�mak i�in tan�mlan�r.
	//KOMUT isimli dosyan�n a��l�p a��lmad��� kontrol edilir.
	if((dosya3=fopen(KOMUT,"r"))==NULL)
	{
		printf("Dosya acilamadi");
		exit(1);
	}
	//KOMUT dosyas�ndan okunan bilgilere g�re i�lemler yap�l�r.
	while(1)
	{
		fscanf(dosya3,"%s",komut);
		if(strcmp(komut,"y")==0 || strcmp(komut,"Y")==0)
		{
			fscanf(dosya3,"%s",uc);
			komutY(komut,uc);
			
		}
		if(strcmp(komut,"i")==0 || strcmp(komut,"I")==0)
		{	
			fscanf(dosya3,"%s",uc);
			komutI(komut,d,uc);
			
		}
		if(strcmp(komut,"h")==0 || strcmp(komut,"H")==0)
		{
			fscanf(dosya3,"%s",uc);
			komutH(komut,d,uc,k,dizi);
			kapiIslem(d,uc,kapi_1,kapi_2,kapi_3,j,z,x,k,dizi);
			
		}
		if(strcmp(komut,"l")==0 || strcmp(komut,"L")==0)
		{
			fscanf(dosya3,"%s",uc);
			komutL(komut,d,uc,k,dizi);
			kapiIslem(d,uc,kapi_1,kapi_2,kapi_3,j,z,x,k,dizi);
			
		}
		if(strcmp(komut,"s")==0 || strcmp(komut,"S")==0)
		{
			komutS(d,dizi,komut);
		}
		if(strcmp(komut,"g")==0 || strcmp(komut,"G")==0)
		{
			fscanf(dosya3,"%s",uc);
			komutG(d,uc,k,komut);
		}
		if(strcmp(komut,"g*")==0 || strcmp(komut,"G*")==0)
		{

			komutGyildiz(d,k,komut);
		}
		if(strcmp(komut,"c")==0 || strcmp(komut,"C")==0)
		{
			break;
		}
	}
}
int main()
{
	
	struct lojik d[20],devre[10];
	int i,j,dizi[2];
	int nanosaniye=0,w=0;
	char giris[5],komut[5];
	FILE *dosya,*dosya1,*dosya2,*dosya3,*dosya4;	//Dosyalar� a�mak i�in tan�mlan�rlar.
	char uc[10];			//Komuttan sonra istenen bilgileri tutmak i�in kullan�l�r.
	char c;										
	//DEVRE isimli dosyan�n a��l�p a��lmad��� kontrol edilir.
	if((dosya=fopen(DEVRE,"r"))==NULL)
	{	
		printf("Dosya acilamadi");
		exit(1);
	}
	//BASKA isimli dosyan�n a��l�p a��lmad��� kontrol edilir.
	if((dosya1=fopen(BASKA,"r"))==NULL)
	{
		printf("Dosya acilamadi");
		exit(1);
	}
	//DEGER isimli dosyan�n a��l�p a��lmad��� kontrol edilir.
	if((dosya2=fopen(DEGER,"r"))==NULL)
	{
		printf("Dosya acilamadi");
		exit(1);
	}
	//KOMUT isimli dosyan�n a��l�p a��lmad��� kontrol edilir.
	if((dosya3=fopen(KOMUT,"r"))==NULL)
	{
		printf("Dosya acilamadi");
		exit(1);
	}
	//LOG isimli dosyan�n a��l�p a��lmad��� kontrol edilir.
	if((dosya4=fopen(LOG,"w"))==NULL)
	{
		printf("Dosya acilamadi");
		exit(1);
	}
    //lOG'a yazd�rma yap�l�r.         	
	fprintf(dosya4,"zaman\t\t\t\t\t\tkomut\t\t\t\tcikti\n");
	fseek(dosya2,0,SEEK_SET);
	int q=0;
	while ((c = fgetc(dosya2))!= EOF) {		
		q++;
	}

	//DEGER'den u�lar�n de�erleri okutulur.
	fseek(dosya2,2,SEEK_SET);	
	j=0;
	for(i=4;i<=q;i+=4)
	{
		fscanf(dosya2,"%s",d[j].deger);
		j++;
		fseek(dosya2,2+i,SEEK_SET);
	}
	//DEGER'den u�lar�n isimleri okutulur.
	i=0;
	int k=0;
	fseek(dosya2,0,SEEK_SET);
	while(i<q)
	{
		fscanf(dosya2,"%1s",d[k].tum);
		k++;
		i+=4;
		fseek(dosya2,i,SEEK_SET);
	}
	//Okutulan de�erler int'e �evirilir.
	for(i=0;i<j;i++)
	{
		d[i].deger2=atoi(d[i].deger);
	}
	//Okutulan de�erler int'e �evirilir.
	for(i=0;i<j;i++)
	{
		d[i].ilkDeger=atoi(d[i].deger);
	}
	

	char kapi_1[5][5],kapi_2[5][5],kapi_3[5][5]; //Kap� bilgilerini tutmak i�in tan�mlan�rlar.	
	char bos[5],tmp[30];				        //bos[] ve tmp[] okunmas� gereksiz olan bilgiler i�in tan�mland�.
	fseek(dosya,0,SEEK_SET);	
	//kap�_1'in bilgilerinin yazmaya ba�land��� yer bulunur.								
	while(1)
	{
		fscanf(dosya,"%s",tmp);
		if(strcmp(tmp,".kapi")==0)
		{
			break;
		}
	}
	//kapi_1'in bilgileri al�n�r.
	fscanf(dosya,"%s",kapi_1[0]);
	fscanf(dosya,"%s",bos);
	fscanf(dosya,"%s",kapi_1[1]);
	j=2;
	while(1)
	{
		fscanf(dosya,"%s",kapi_1[j]);
		if(isdigit(kapi_1[j][0]))
		{
			break;
		}
		j++;
	}
	int z;
	//kap�_3'�n bilgilerinin yazmaya ba�land��� yer bulunur.
	while(1)
	{
		fscanf(dosya,"%s",tmp);
		if(strcmp(tmp,".kapi")==0)
		{
			break;
		}
	}
	//kapi_3'�n bilgileri al�n�r.
	fscanf(dosya,"%s",kapi_3[0]);
	fscanf(dosya,"%s",bos);
	fscanf(dosya,"%s",kapi_3[1]);
	z=2;
	while(1)
	{
		fscanf(dosya,"%s",kapi_3[z]);
		if(isdigit(kapi_3[z][0]))
		{
	
			break;
		}
		z++;
	}
	fseek(dosya1,0,SEEK_SET);
	//kap�_2'nin bilgilerinin yazmaya ba�land��� yer bulunur.
	while(1)
	{
		fscanf(dosya1,"%s",tmp);
		if(strcmp(tmp,".kapi")==0)
		{
			break;
		}
	}
	//kapi_2'nin bilgileri al�n�r.
	fscanf(dosya1,"%s",kapi_2[0]);
	fscanf(dosya1,"%s",bos);
	fscanf(dosya1,"%s",kapi_2[1]);
	int x=2;
	while(1)
	{
		fscanf(dosya1,"%s",kapi_2[x]);
		if(isdigit(kapi_2[x][0]))
		{
	
			break;
		}
		x++;
	}
	//Komut girilmesi istenir ve istenilen komuta g�re fonksiyon �a��r�l�r.
	while(1)
	{
		
		printf(">");
		scanf("%s",&komut);
		if(strcmp(komut,"y")==0 || strcmp(komut,"Y")==0)
		{
			
			getchar();
			scanf("%[^\n]",uc);
			komutY(komut,uc);
			
		}
		else if(strcmp(komut,"i")==0 || strcmp(komut,"I")==0)
		{
			getchar();
			scanf("%[^\n]",uc);
			komutI(komut,d,uc);
			
		} 
		else if(strcmp(komut,"h")==0 || strcmp(komut,"H")==0)
		{
			getchar();
			scanf("%[^\n]",uc);
			komutH(komut,d,uc,k,dizi);
			kapiIslem(d,uc,kapi_1,kapi_2,kapi_3,j,z,x,k,dizi);
			
		}
		else if(strcmp(komut,"l")==0 || strcmp(komut,"L")==0)
		{
			getchar();
			scanf("%[^\n]",uc);
			komutL(komut,d,uc,k,dizi);
			kapiIslem(d,uc,kapi_1,kapi_2,kapi_3,j,z,x,k,dizi);
			
		}
		else if(strcmp(komut,"s")==0 || strcmp(komut,"S")==0)
		{
			komutS(d,dizi,komut);
		}
		else if(strcmp(komut,"g")==0 || strcmp(komut,"G")==0)
		{
			getchar();
			scanf("%[^\n]",uc);
			komutG(d,uc,k,komut);
		}
		else if(strcmp(komut,"g*")==0 || strcmp(komut,"G*")==0)
		{

			komutGyildiz(d,k,komut);
		}
		else if(strcmp(komut,"k")==0 || strcmp(komut,"K")==0)
		{
			komutK(d,dizi,k,kapi_1,kapi_2,kapi_3,j,z,x);
		}
		else if(strcmp(komut,"c")==0 || strcmp(komut,"C")==0)
		{
			break;
		}
		else
		{
			printf("Hata!!!Yanlis komut tekrar giriniz\n");
		}
		
	}
	
	//Dosyalar kapat�l�r.
	fclose(dosya);	
	fclose(dosya1);
	fclose(dosya2);
	fclose(dosya3);
	fclose(dosya4);
	
}
