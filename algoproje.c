#include <stdio.h> 
#include <math.h> 
#include <time.h> 
#include <stdlib.h> 
#include <string.h>

double ortalama1 = 0;
double std1 = 0; 

void cevap_anahtari_uret(char cevap_anahtari[], int S) 
{ 
 
     srand(time(0)); 
     char cevap_siklari[5]={'A','B','C','D','E'}; 
     printf("Cevap Anahtari: \n"); 
     for(int i=0; i<S; i++){ 
            int random_index = rand()%5; 
            cevap_anahtari[i]=cevap_siklari[random_index]; 
     } 
 
 
} 

void cevap_anahtari_yazdir(char cevap_anahtari[], int S) 
{ 
    for(int i=0; i<S; i++){ 
        printf("Soru %d: %c | ",i+1,cevap_anahtari[i]); 
    } 
 
} 

void sinavi_uygula(char ogrenci_cevaplari[][100], char cevap_anahtari[], int N, int S, double B, 
double D) 
{ 
    char yanlis_cevap1[4] = {'B','C','D','E'}; 
    char yanlis_cevap2[4] = {'A','C','D','E'}; 
    char yanlis_cevap3[4] = {'A','B','D','E'}; 
    char yanlis_cevap4[4] = {'A','B','C','E'}; 
    char yanlis_cevap5[4] = {'A','B','C','D'}; 
 
    for(int i=0; i<N; i++){ 
        for(int j=0; j<S; j++){ 
            int kontrol = rand()%10+1; 
            if(kontrol<=D*10) //doğru cevaplar 
            ogrenci_cevaplari[i][j] = cevap_anahtari[j]; 
            else if(kontrol>D*10 && kontrol<=(1-B)*10){//yanlış cevaplar 
                switch(cevap_anahtari[j]) 
                { 
                    case 'A': 
                    ogrenci_cevaplari[i][j]= yanlis_cevap1[rand()%4]; 
                    break; 
                    case 'B': 
                    ogrenci_cevaplari[i][j]= yanlis_cevap2[rand()%4]; 
                    break; 
                    case 'C': 
                    ogrenci_cevaplari[i][j]= yanlis_cevap3[rand()%4]; 
                    break; 
                    case 'D': 
                    ogrenci_cevaplari[i][j ]= yanlis_cevap4[rand()%4]; 
                    break; 
                    case 'E': 
                    ogrenci_cevaplari[i][j] = yanlis_cevap5[rand()%4]; 
                    break; 
                    default: 
                        printf("HATALI!\n"); 
                } 
            } 
            else if(kontrol>(1-B)*10 && kontrol<=10) //boş cevaplar 
            ogrenci_cevaplari[i][j] = 'X'; 
        } 
    } 
} 

void ogrenci_cevabini_yazdir(char ogrenci_cevaplari[][100], int ogrenci_ID, int S) 
{ 
    for(int i=0; i<ogrenci_ID; i++){ 
        printf("\n%d.ogrencinin cevaplari: \n",i+1); 
        for(int j=0; j<S; j++){ 
            printf("Soru %d: %c | ",j+1,ogrenci_cevaplari[i][j]);
        } 
    } 
} 

void ogrencileri_puanla(char ogrenci_cevaplari[][100], char cevap_anahtari[], double HBN[], int N, int S)
{
    float dogru_sayisi=0;
    float yanlis_sayisi=0;
    for(int i=0; i<N; i++){
        dogru_sayisi=0;
        yanlis_sayisi=0;
        for(int j=0; j<S; j++){
            if(ogrenci_cevaplari[i][j]==cevap_anahtari[j])
                dogru_sayisi++;
            else if(ogrenci_cevaplari[i][j]=='X')
                ;
            else if(ogrenci_cevaplari[i][j]!=cevap_anahtari[j])
                yanlis_sayisi++;
        }
        HBN[i] = (dogru_sayisi-(yanlis_sayisi)/4)*(100/S);
        if(HBN[i]<0)
        HBN[i]=0;    
    }

}

double sinif_ortalamasi_hesapla(double HBN[], int N)
{
    double toplam=0;
    for(int i=0; i<N; i++){
        toplam = toplam + HBN[i];
    }
    ortalama1=toplam/N;
    printf("Sınıf Ortalamasi: %.2lf\n",ortalama1);
    if(ortalama1>80.0 && ortalama1<=100)
    printf("Sınıf Duzeyi: Ustun Basari!\n");
    else if(ortalama1>70.0 && ortalama1<=80)
    printf("Sınıf Duzeyi: Mukemmel\n");
    else if(ortalama1>62.5 && ortalama1<=70)
    printf("Sınıf Duzeyi: Cok iyi\n");
    else if(ortalama1>57.5 && ortalama1<=62.5)
    printf("Sınıf Duzeyi: iyi\n");
    else if(ortalama1>52.5 && ortalama1<=57.5)
    printf("Sınıf Duzeyi: Ortanın Ustu\n");
    else if(ortalama1>47.5 && ortalama1<=52.5)
    printf("Sınıf Duzeyi: Orta\n");
    else if(ortalama1>42.5 && ortalama1<=47.5)
    printf("Sınıf Duzeyi: Zayıf\n");
    else if(ortalama1<=42.5)
    printf("Sınıf Duzeyi: Kotu\n");
    return ortalama1;

}

double standart_sapma_hesapla(double ortalama, double HBN[], int N)
{
    double hesap=0;
    for(int i=0; i<N; i++){
        hesap = hesap + pow((HBN[i]-ortalama),2);
    }
    std1 = sqrt(hesap/N);
    printf("Standart Sapma: %.2lf\n",std1);
    return std1;

}

void T_skoru_hesapla(double ortalama, double HBN[], int N, double std, double T_skoru[])
{
        for(int i=0; i<N; i++){
            if(std<=0){
                if(ortalama==100)
                T_skoru[i]=100;}
            else
            T_skoru[i]=60+10*((HBN[i]-ortalama)/std);
        }
 }

void ogrenci_notlari_yazdir(double HBN[],double T_skoru[],int N)
{
    
    int harf_notu[100];
    if(ortalama1>80.0 && ortalama1<=100)
        for(int i=0; i<N; i++){
            harf_notu[i] = (T_skoru[i] < 32) ? 70 : (T_skoru[i] >= 32 && T_skoru[i] <= 36.99) ? 79 : (T_skoru[i] >= 37 && T_skoru[i] <= 41.99) ? 68 : (T_skoru[i] >= 42 && T_skoru[i] <= 46.99) ? 89 : (T_skoru[i] >= 47 && T_skoru[i] <= 51.99) ? 67 : (T_skoru[i] >= 52 && T_skoru[i] <=56.99) ? 99 : (T_skoru[i] >= 57 && T_skoru[i] <= 61.99) ? 66 : (T_skoru[i] >= 62 && T_skoru[i] <= 66.99) ? 109 : 65;      
    }
    if(ortalama1>70.0 && ortalama1<=80)
        for(int i=0; i<N; i++){
            harf_notu[i] = (T_skoru[i] < 34) ? 70 : (T_skoru[i] >= 34 && T_skoru[i] <= 38.99) ? 79 : (T_skoru[i] >= 39 && T_skoru[i] <= 43.99) ? 68 : (T_skoru[i] >= 44 && T_skoru[i] <= 48.99) ? 89 : (T_skoru[i] >= 49 && T_skoru[i] <= 53.99) ? 67 : (T_skoru[i] >= 54 && T_skoru[i] <=58.99) ? 99 : (T_skoru[i] >= 59 && T_skoru[i] <= 63.99) ? 66 : (T_skoru[i] >= 64 && T_skoru[i] <= 68.99) ? 109 : 65;      
    }
    if(ortalama1>62.5 && ortalama1<=70)
        for(int i=0; i<N; i++){
            harf_notu[i] = (T_skoru[i] < 36) ? 70 : (T_skoru[i] >= 36 && T_skoru[i] <= 40.99) ? 79 : (T_skoru[i] >= 41 && T_skoru[i] <= 45.99) ? 68 : (T_skoru[i] >= 46 && T_skoru[i] <= 50.99) ? 89 : (T_skoru[i] >= 51 && T_skoru[i] <= 55.99) ? 67 : (T_skoru[i] >= 56 && T_skoru[i] <=60.99) ? 99 : (T_skoru[i] >= 61 && T_skoru[i] <= 65.99) ? 66 : (T_skoru[i] >= 66 && T_skoru[i] <= 70.99) ? 109 : 65;      
    }
    if(ortalama1>57.5 && ortalama1<=62.5)
        for(int i=0; i<N; i++){
            harf_notu[i] = (T_skoru[i] < 38) ? 70 : (T_skoru[i] >= 38 && T_skoru[i] <= 42.99) ? 79 : (T_skoru[i] >= 43 && T_skoru[i] <= 47.99) ? 68 : (T_skoru[i] >= 48 && T_skoru[i] <= 52.99) ? 89 : (T_skoru[i] >= 53 && T_skoru[i] <= 57.99) ? 67 : (T_skoru[i] >= 58 && T_skoru[i] <=62.99) ? 99 : (T_skoru[i] >= 63 && T_skoru[i] <= 67.99) ? 66 : (T_skoru[i] >= 68 && T_skoru[i] <= 72.99) ? 109 : 65;      
    }
    if(ortalama1>52.5 && ortalama1<=57.5)
        for(int i=0; i<N; i++){
            harf_notu[i] = (T_skoru[i] < 40) ? 70 : (T_skoru[i] >= 40 && T_skoru[i] <= 44.99) ? 79 : (T_skoru[i] >= 45 && T_skoru[i] <= 49.99) ? 68 : (T_skoru[i] >= 50 && T_skoru[i] <= 54.99) ? 89 : (T_skoru[i] >= 55 && T_skoru[i] <= 59.99) ? 67 : (T_skoru[i] >= 60 && T_skoru[i] <=64.99) ? 99 : (T_skoru[i] >= 65 && T_skoru[i] <= 69.99) ? 66 : (T_skoru[i] >= 70 && T_skoru[i] <= 74.99) ? 109 : 65;      
    }
    if(ortalama1>47.5 && ortalama1<=52.5)
        for(int i=0; i<N; i++){
            harf_notu[i] = (T_skoru[i] < 42) ? 70 : (T_skoru[i] >= 42 && T_skoru[i] <= 46.99) ? 79 : (T_skoru[i] >= 47 && T_skoru[i] <= 51.99) ? 68 : (T_skoru[i] >= 52 && T_skoru[i] <= 56.99) ? 89 : (T_skoru[i] >= 57 && T_skoru[i] <= 61.99) ? 67 : (T_skoru[i] >= 62 && T_skoru[i] <=66.99) ? 99 : (T_skoru[i] >= 67 && T_skoru[i] <= 71.99) ? 66 : (T_skoru[i] >= 72 && T_skoru[i] <= 76.99) ? 109 : 65;      
    }
    if(ortalama1>42.5 && ortalama1<=47.5)
        for(int i=0; i<N; i++){
            harf_notu[i] = (T_skoru[i] <44) ? 70 : (T_skoru[i] >= 44 && T_skoru[i] <= 48.99) ? 79 : (T_skoru[i] >= 49 && T_skoru[i] <= 53.99) ? 68 : (T_skoru[i] >= 54 && T_skoru[i] <= 58.99) ? 89 : (T_skoru[i] >= 59 && T_skoru[i] <= 63.99) ? 67 : (T_skoru[i] >= 64 && T_skoru[i] <=68.99) ? 99 : (T_skoru[i] >= 69 && T_skoru[i] <= 73.99) ? 66 : (T_skoru[i] >= 74 && T_skoru[i] <= 78.99) ? 109 : 65;      
    }
    if(ortalama1<=42.5)
        for(int i=0; i<N; i++){
            harf_notu[i] = (T_skoru[i] <46) ? 70 : (T_skoru[i] >= 46 && T_skoru[i] <= 50.99) ? 79 : (T_skoru[i] >= 51 && T_skoru[i] <=55.99) ? 68 : (T_skoru[i] >= 56 && T_skoru[i] <= 60.99) ? 89 : (T_skoru[i] >= 61 && T_skoru[i] <= 65.99) ? 67 : (T_skoru[i] >= 66 && T_skoru[i] <=70.99) ? 99 : (T_skoru[i] >= 71 && T_skoru[i] <= 75.99) ? 66 : (T_skoru[i] >= 76 && T_skoru[i] <= 80.99) ? 109 : 65;      
    }

    printf("Ogrenci Skorları: \n");
    for(int i=0; i<N; i++){
        if( T_skoru[i]!=100){
        if(harf_notu[i]==70 || harf_notu[i]==68 || harf_notu[i]==67 || harf_notu[i]==66 || harf_notu[i]==65) 
        printf("\n%d. ogrencinin HBN'si: %.2lf , T_skoru: %.2lf , harf notu: %c%c\n",i+1,HBN[i],T_skoru[i],harf_notu[i],harf_notu[i]);
        else if(harf_notu[i]==79)
        printf("\n%d. ogrencinin HBN'si: %.2lf , T_skoru: %.2lf , harf notu: FD\n",i+1,HBN[i],T_skoru[i]);
        else if(harf_notu[i]==89)
        printf("\n%d. ogrencinin HBN'si: %.2lf , T_skoru: %.2lf , harf notu: DC\n",i+1,HBN[i],T_skoru[i]);
        else if(harf_notu[i]==99)
        printf("\n%d. ogrencinin HBN'si: %.2lf , T_skoru: %.2lf , harf notu: CB\n",i+1,HBN[i],T_skoru[i]);
        else if(harf_notu[i]==109)
        printf("\n%d. ogrencinin HBN'si: %.2lf , T_skoru: %.2lf , harf notu: BA\n",i+1,HBN[i],T_skoru[i]);
    }
    else if(T_skoru[i]==100)
         printf("\n%d. ogrencinin HBN'si: %.2lf , T_skoru: Yazdirilamaz , harf notu: AA\n",i+1,HBN[i]);
    }
    
}

 
int main() 
{ 
    int N,S; double B,D;
     
    printf("Ogrenci sayisini giriniz (max 100): "); 
    scanf("%d",&N); 
 
    printf("Soru sayisini giriniz (max 100): "); 
    scanf("%d",&S); 
 
    printf("Bos birakma ihtimalini giriniz (0.0-1.0): "); 
    scanf("%lf",&B); 
 
    printf("Dogru cevap verme ihtimalini giriniz (0.0-1.0): "); 
    scanf("%lf",&D); 
    printf("\n"); 
 
    char ogrenci_cevaplari[100][100]; char cevap_anahtari[100]; 
    int ogrenci_ID = N; 
    double HBN[100]={0}; double T_skoru[100]={0};

    cevap_anahtari_uret(cevap_anahtari,S); 
    cevap_anahtari_yazdir(cevap_anahtari,S); 
    printf("\n"); 
    sinavi_uygula(ogrenci_cevaplari,cevap_anahtari,N,S,B,D); 
    ogrenci_cevabini_yazdir(ogrenci_cevaplari,ogrenci_ID,S); 
    printf("\n");
    ogrencileri_puanla(ogrenci_cevaplari,cevap_anahtari,HBN,N,S);
    printf("\n"); 
    sinif_ortalamasi_hesapla(HBN,N);
    standart_sapma_hesapla(ortalama1,HBN,N);
    printf("\n");
    T_skoru_hesapla(ortalama1,HBN,N,std1,T_skoru);
    ogrenci_notlari_yazdir(HBN,T_skoru,N);
  return 0;  
}







