import random      #random import edildi
def bahisAl():     #kullanıcıdan bahis alan fonksiyon
    while True:    #sonsuz döngü doğru giriş yapılana kadar döner
        try:
            gecici = input('Bahis miktarini giriniz: ')     #kullanıcıdan bahis miktarı alındı
            miktar = int(gecici)                                 # integer a çevrildi tamsayı girilip girilmediği kontrol edildi
            if miktar < 0: raise ValueError('Gecerli bir bahis miktarı girmediniz. Tekrar giris yapiniz.')     #negatif sayı ise tekrar bahis alınır
            break
        except ValueError:                   #tamsayı girilmediyse tekrar bahis alınır
            print("Gecerli bir bahis miktarı girmediniz. Tekrar giris yapiniz.")
    return miktar           #bahis miktarı döndürüldü
def tahminAl():             #kullanıcıdan tahmin alan fonksiyon
    dizi=['T','Y']          #dizi elemanları Y(yazı) ve T(tura) kullanıcı ikisinden birini girmeli
    while True:
        try:
            gecici2 = input('Tahmininizi giriniz <Yazi icin Y, tura icin T giriniz>: ')       #kullanıcıdan tahmini alındı
            tahmin = gecici2.upper()            #tahmin büyük harfe çevrildi kontrol ederken kolaylık sağlasın diye
            if tahmin not in dizi: raise ValueError('Yanlis karakter girdiniz tekrar giris yapınız.')  #kullanıcının girdiği karakter dizide yoksa tekrar tahmin alınır 
            break                 #doğruysa döngüyü sonlandır
        except ValueError:        #hatalı giriş olursa tekrar tahmin alınır
            print("Yanlis karakter girdiniz tekrar giris yapınız.")
    return tahmin         # tahmin geri döndürüldü
def devamMi():            #kullanıcıdan devam etmek isteyip istemediğini öğrenen fonksiyon
    dizi2=['E','H']       #dizi elemanları E(evet) ve H(hayır) kullanıcı ikisinden birini girmeli
    while True:
        try:
            gecici3 = input('Devam etmek istermisiniz <E/H>: ')       #kullanıcın isteği alındı
            devam = gecici3.upper()                      #kontrol ederken kolaylık sağlasın diye büyük harfe çevrildi
            if devam not in dizi2: raise ValueError('Yanlis karakter girdiniz tekrar giris yapınız. ')     #kullanıcının girdiği karakter dizide yoksa tekrar tahmin alınır
            break       #doğruysa döngüyü sonlandır
        except ValueError:
            print("Yanlis karakter girdiniz tekrar giris yapiniz")
    return devam        # devam geri döndürüldü
sayac_Oyun=1            #oynan oyun sayısını saklar
kaybedilen=0            #kaybedilen miktarı saklar
kazanilan=0             # kazanılan mıktarı saklar
kar=0                   # karı saklar
dizi=['Y','T']           # bilgisayar bu diziden rastgele seçicek tahminini 
while True:
    print('Oyun %d' % sayac_Oyun)      #her seferinde kaçıncı oyun oynandığı ekrana basılır
    pc_tahmin = random.choice(dizi)       #diziden rasgele bir elemanı seçer bilgisayarın tahmini olur          
    bahis_Tutar = bahisAl()            #bahisAL fonksiyonu çağrıldı ve bahis alındı
    tahmin1 = tahminAl()               #tahminAl fonksiyonu çağrıldı ve tahmin alındı
    if tahmin1 == pc_tahmin:          #kullanıcı doğru tahmin yaparsa işletilecek blok
        kazanilan = kazanilan + bahis_Tutar    #kazancı bahis kadar arttır
        kar = abs(kazanilan - kaybedilen)      # kar hesaplama
        print('%d . oyunu kazandiniz' % sayac_Oyun)    #kullanıcıya kazandığı haberi verildi
        print('Su ana kadar kaybettiginiz tutar: %d' % kaybedilen)    #toplam kazanç ve kayıp edilen miktar gösterildi
        print('Su ana kadar kazandiginiz tutar: %d' % kazanilan)
        if kazanilan < kaybedilen:    #bu blokta toplamda kar mı ettiği zarar mı ettiği anlaşılır ona göre kullanıcıya bilgi verilir
            print('%d TL zaradasiniz' % kar)
        else:
            print('%d TL kardasiniz' % kar)
    else:       # kullanıcı kaybederse
        kaybedilen = kaybedilen + bahis_Tutar   #kaybedileni bahis kadar arttır
        kar = abs(kazanilan - kaybedilen)       #kar hesapla mutlak değer al
        print('%d . oyunu kaybettiniz' % sayac_Oyun)       #durumları ekrana bas
        print('Su ana kadar kaybettiginiz tutar: %d' % kaybedilen)
        print('Su ana kadar kazandiginiz tutar: %d' % kazanilan)
        if kazanilan < kaybedilen:
            print('%d TL zaradasiniz' % kar)
        elif kazanilan > kaybedilen:
            print('%d TL kardasiniz' % kar)
        else:
            print('Ne karda ne de zaradasiniz.')
    sayac_Oyun += 1  #oyun sayısını arttır
    devam = devamMi()    #devamMi fonksiyonu çağrıldı
    if devam == 'E':   # evet derse devam et oyuna
        print('\n')
        continue
    else:    # hayır derse sonlandır
        break
            
