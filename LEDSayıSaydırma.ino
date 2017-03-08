int  a[]={8,9,10,11,12,13}; //pin numaralarını tutan dizi
void ledYak(int[],int[]); // ledleri yakan yardımcı fonksiyon
int rastgeleSayiUret(); // random sayı üreten fonksiyon
int button=A3; // buton pini
int val=0; // buton değeri
int sayi; // random atayacağımız sayı değişkeni
int dizi[6]; // random buluduğumuz 6 bitlik sayının
          // binary sistemdeki karşılığının elemanlarını
          // saklayan dizi
int beklemeSuresi=20;          
int c;
void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<6;i++){
  pinMode(a[i],OUTPUT); // ledlere çıkış verdim
  }
  pinMode(button,INPUT); // butona giriş verdim

}

void loop() {
  // put your main code here, to run repeatedly:
  int sayi;
  sayi=rastgeleSayiUret();
  val=digitalRead(button); // buton pininden dijital okuma tanımladık
  if(val==HIGH){ // butona basıldıysa
    for(int j=0;j<6;j++){ // sayıyı ikilik tabana çevrildiği bölüm
      c=(sayi%2); // 2'ye bölümünden kalan
      dizi[j]=c; // diziye atama
      sayi=sayi/2; // sayıyı azalt
    }
    ledYak(dizi,a);
  
    }
  }

void ledYak(int d[],int f[]){
      if(d[0]==1){ // 1 se ledi yak
      digitalWrite(f[0],HIGH); // ledi yak
      delay(beklemeSuresi);}
      else { // değilse söndür
      digitalWrite(f[0],LOW);} // ledi söndür
      if(d[1]==1){
      digitalWrite(f[1],HIGH);
      delay(beklemeSuresi);}
      else{
      digitalWrite(f[1],LOW);}
      if(d[2]==1){
      digitalWrite(f[2],HIGH);
      delay(beklemeSuresi);}
      else{
      digitalWrite(f[2],LOW);}
      if(d[3]==1){
      digitalWrite(f[3],HIGH);
      delay(beklemeSuresi);}
      else{
      digitalWrite(f[3],LOW);}
      if(d[4]==1){
      digitalWrite(f[4],HIGH);
      delay(beklemeSuresi);}
      else{
      digitalWrite(f[4],LOW);}
      if(d[5]==1){
      digitalWrite(f[5],HIGH);
      delay(beklemeSuresi);}
      else {
      digitalWrite(f[5],LOW);}
}
      

int rastgeleSayiUret(){ // rastgele sayı üreten fonksiyon
    sayi=random(64,128); // rastgele 6 bitlik sayı ürettim
    return sayi;
}

