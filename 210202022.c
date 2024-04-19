#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

void menu()
{
    printf("\n1-Kelime veya Etiket Arama\n2-İçerik Güncelleme\n3-Konsolu Temizleme\n4-Çıkış Yapma\n");
    printf("Lutfen yapmak istediginiz islemi seciniz:");
}

int ft_strstr(char *s1, char *s2) // string karşılaştırma fonksiyonu
{
    int i = 0;
    while (s1[i] && s1[i] == s2[i])
    {
        i++;
    }
    if (s1[i] == '\0' && s2[i] == '\0')
    {
        return (1); //stringler aynıysa 1 döner.
    }
    return (0); //stringler farklıysa 0 döner.
}

int ctrl_str(char **str, char *s, int i) // etiket daha önce geçti mi kontrol ediyor.
{
    int j = 0;
    while (j < i)
    {
        if (ft_strstr(str[j], s))
        {
            return (0); // geçtiyse 0 dönüyor.
        }
        j++;
    }
    return (1); // geçmediyse 1 dönüyor.
}

void klasorgezme(char *dosyayolu[250], int *txtsayisi)
{
    system("cd Üniversite & dir */ad/b/d/o:n>dosyalist.txt");
    FILE *dosyaisimleri = fopen(".\\Üniversite\\dosyalist.txt", "r");
    char satir[1500],dosyalar[150], dizi[100], dizi2[100],derssatir[1500];
    *txtsayisi = 0;
    while (fgets(satir, 1500, dosyaisimleri) != NULL)
    {
        satir[strlen(satir) - 1] = '\0';
        strcpy(dizi, "cd .\\Üniversite\\");
        strcpy(dizi2, "& DIR *.TXT/b/o:n>../derslist2.txt");// klasör isimlerini derslist2.txt ye yaz.
        strcat(dizi, satir);
        strcat(dizi, dizi2);
        system(dizi);
        FILE *dersisimleri = fopen("C:\\Users\\FAHRETTIN\\Desktop\\Üniversite\\derslist2.txt", "r");
        while (fgets(derssatir, 1500, dersisimleri) != NULL)
        {
            derssatir[strlen(derssatir) - 1] = '\0';
            sprintf(dosyalar, "C:\\Users\\FAHRETTIN\\Desktop\\Üniversite\\%s\\%s", satir, derssatir);
            dosyayolu[(*txtsayisi)++] = strdup(dosyalar);// tüm dosya yolları
        }
    }
}

void tumetiketler(char *dosyayolu[100],int txtsayisi,char *etiketler[100],int *etiketsayisi) // tüm etiketleri bulma fonksiyonu
{
    char *aranan = "[[";
    char *aranan2 = "]]";
    for (int i = 0; i < txtsayisi; i++)
    {
        char cumle[1000];
        FILE *fp = fopen(dosyayolu[i], "r");
        while (fgets(cumle, 1000, fp))
        {
            char *ret = strstr(cumle, aranan);
            char *ret2 = strstr(cumle, aranan2);
            while (ret != NULL && ret2 != NULL)
            {
                int cont = 0,cont1=0;
                char *etiket_ismi;
                int len = 0;
                while (ret[len + 2] != ']') 
                {
                    len++;
                }
                etiket_ismi = malloc(len + 1); 
                len = 0;                      
                while (ret[len + 2] != ']')  
                {
                    etiket_ismi[len] = ret[len + 2];
                    len++;
                }
                etiket_ismi[len] = '\0';
                for (int i = 0; i < strlen(etiket_ismi); i++)
                {
                    if (etiket_ismi[i] == ' ')
                    {
                        cont++;
                    }
                     if(ispunct(etiket_ismi[i]) && etiket_ismi[i]!='_'){
                        cont1++;
                     }
                }
                if (cont < 2 && cont1==0)
                {
                    etiketler[(*etiketsayisi)++] = strdup(etiket_ismi); 
                }
                ret = strstr((ret) + 1, aranan);
                ret2 = strstr((ret2) + 1, aranan2);
            }
        }
        fclose(fp);
    }
}

void etikettekrarkontrolu(char *etiketler[100],char *uniq_etiketler[100],int *uniq_index,int uniq_sayisi[100],int etiketsayisi){
    for (int i = 0; i < etiketsayisi; i++) 
    {
        int gecissayisi = 0;
        int ui=*uniq_index;
        for (int j = i; j < etiketsayisi && ctrl_str(etiketler, etiketler[i], i); j++) 
                                                                           
        {
            if (ft_strstr(etiketler[i], etiketler[j]))
                gecissayisi++;
        }
        if (gecissayisi != 0)
        {
            uniq_etiketler[ui] = strdup(etiketler[i]);
            uniq_sayisi[ui] = gecissayisi;
            ui++;
        }
        *uniq_index=ui;
    }
}

void yebulma(char *uniq_etiketler[100], int uniq_index, char *aramadosyasi[150], char *yetimetiket[100], int *l, int *k, int *donus) // yetim etiket bulma fonksiyonu
{
    char satir[1500], derssatir[1500], dizi[150], dizi2[150];
    FILE *yetimEtiketYolu = fopen(".\\Üniversite\\dosyalist.txt", "r");
    int y = 0;
    int a=*l,b=*k;
    while (fgets(satir, 1500, yetimEtiketYolu) != NULL)
    {
        satir[strlen(satir) - 1] = '\0';
        strcpy(dizi, "cd .\\Üniversite\\");
        strcpy(dizi2, "& DIR *.TXT/b/o:n>../derslist2.txt");
        strcat(dizi, satir);
        strcat(dizi, dizi2);
        system(dizi);
        FILE *yetimDosyaisimleri = fopen("C:\\Users\\FAHRETTIN\\Desktop\\Üniversite\\derslist2.txt", "r");
        while (fgets(derssatir, 1500, yetimDosyaisimleri) != NULL)
        {
            aramadosyasi[b] = strdup(derssatir);//txt dosya isimleri
            (b)++;
            *k=b;
        }
        fclose(yetimDosyaisimleri);
    }
    fclose(yetimEtiketYolu);
    for (int i = 0; i < uniq_index; i++)
    {
        *donus = 0;
        for (int j = 0; j < b; j++)
            if (strstr(aramadosyasi[j], uniq_etiketler[i]))
                *donus = 1;
        if (*donus == 0)
        {
            yetimetiket[a] = uniq_etiketler[i];
            a++;
            *l=a;
        }
    }
}

void output(char *uniq_etiketler[100],char *yetimetiket[100],int uniq_sayisi[100],int uniq_index,int l,int sayac){

    FILE *openfilepath = fopen("C:\\Users\\FAHRETTIN\\Desktop\\Üniversite\\output.txt", "w");
    fprintf(openfilepath, "Etiket isimleri\t\t\t\t\tTekrar Sayısı\n");
    while (++sayac < uniq_index)
    {
        fprintf(openfilepath, "%-40s\t\t%d\n", uniq_etiketler[sayac], uniq_sayisi[sayac]);
    }
    fclose(openfilepath);
    openfilepath = fopen("C:\\Users\\FAHRETTIN\\Desktop\\Üniversite\\output.txt", "a");
    fprintf(openfilepath, "\nYetim Etiketler\n");
    sayac = -1;
    while (++sayac < l)
    {
        fprintf(openfilepath, "%-40s\n", yetimetiket[sayac]);
    }
    fclose(openfilepath);
}
void outputguncel(char *uniq_etiketler[100],char *yetimetiket[100],int uniq_sayisi[100],int uniq_index,int l,int sayac){

    FILE *openfilepath = fopen("C:\\Users\\FAHRETTIN\\Desktop\\Üniversite\\output.txt", "a");
    fprintf(openfilepath,"\nGüncel Liste\n");
    fprintf(openfilepath, "Etiket isimleri\t\t\t\t\tTekrarSayısı\n");
    while (++sayac < uniq_index)
    {
        fprintf(openfilepath, "%-40s\t\t%d\n", uniq_etiketler[sayac], uniq_sayisi[sayac]);
    }
    fclose(openfilepath);
    openfilepath = fopen("C:\\Users\\FAHRETTIN\\Desktop\\Üniversite\\output.txt", "a");
    fprintf(openfilepath, "\nYetim Etiketler\n");
    sayac = -1;
    while (++sayac < l)
    {
        fprintf(openfilepath, "%-40s\n", yetimetiket[sayac]);
    }
    fclose(openfilepath);
}
void istenenetiketfonk(char *aramadosyasi[100],char *istenenetiket[100],char *uniq_etiketler[100],int uniq_index,int k,int *p){
    int donus = 0;
    int pp =*p;
    for (int i = 0; i < k; i++)
        aramadosyasi[i][strlen(aramadosyasi[i]) - 5] = '\0';
    for (int i = 0; i < k; i++)
    {
        donus = 0;
        for (int j = 0; j < uniq_index; j++){
            if (strstr(uniq_etiketler[j], aramadosyasi[i]))
            {    
                donus = 1;
            }
        }
        if (donus == 0)
        {
            istenenetiket[pp] = aramadosyasi[i];
            (pp)++;
        }
        *p=pp;
    }
}

void dosyadidegisme(char *yenidosyaismi,char *eskidosya,char *yenidosyayolu,char *dosyayolu[100],int txtsayisi){
    for (int i = 0; i < strlen(yenidosyaismi); i++)
                if (yenidosyaismi[i] == ' ')
                        yenidosyaismi[i] = '_';
            strcat(yenidosyaismi, ".txt");
            int a = 0;
            char *ret,*dosyayy,dost[250];
            yenidosyayolu=malloc(250);
            for (int i = 0; i < txtsayisi; i++)
            {
                if((dosyayy = strrchr(dosyayolu[i],'\\'))){
                    strcpy(dost,dosyayy+1);
                    dost[strlen(dost)-4]='\0';
                }
                if((ret = strstr(dosyayolu[i],eskidosya))){
                if ((ft_strstr(dost,eskidosya))==1)
                {
                    int b = ret - dosyayolu[i];
                    memset(yenidosyayolu,0,strlen(yenidosyayolu));
                    strncpy(yenidosyayolu, dosyayolu[i], b);
                    strcat(yenidosyayolu, yenidosyaismi);
                    rename(dosyayolu[i], yenidosyayolu);
                    strcpy(dosyayolu[i],yenidosyayolu);//yeni dosya yolu eski dosya yolu ile değiştiriliyor
                    printf("Dosya ismi başarıyla değiştirildi...");
                    a++;
                }
                }
            }
            if (a == 0)
                printf("Dosya ismi değiştirilemedi");
}
char* etiketdegistirme(char* kopyala,char* degisecek_etiket,char* yeni_etiket,int *con)
{
    char* change_file;
    int i, cnt = 0;
    strcat(degisecek_etiket,"]]");
    int yeniboyut = strlen(yeni_etiket);
    int eskiboyut = strlen(degisecek_etiket)-2;
    for (i = 0; kopyala[i] != '\0'; i++) {
        if (strstr(&kopyala[i], degisecek_etiket) == &kopyala[i]) {
            cnt++;
            *con=1;
            i += eskiboyut ;
        }
    }
    change_file = (char*)malloc(i + cnt * (yeniboyut - eskiboyut) + 1);
    i = 0;
    while (*kopyala) {
        if (strstr(kopyala, degisecek_etiket) == kopyala) {
            strcpy(&change_file[i], yeni_etiket);
            i += yeniboyut;
            kopyala += eskiboyut ;
        }
        else
            change_file[i++] = *kopyala++;
    }
    change_file[i] = '\0';
    return change_file;
}

int main()
{
    setlocale(LC_ALL,"tr_tr.UTF-8");
    char *dosyayolu[250],*yetimetiket[100],*aramadosyasi[150],*etiketler[100],*uniq_etiketler[100],*istenenetiket[100];
    int txtsayisi,p = 0,etiketsayisi = 0,kod = 200,uniq_index=0,uniq_sayisi[100],l = 0, k = 0, donus = 0,sayac = -1,secim,opguncelleme=0;
    char karakter, karakter1, karakter2;
    klasorgezme(dosyayolu, &txtsayisi);
    tumetiketler(dosyayolu,txtsayisi,etiketler,&etiketsayisi);
    etikettekrarkontrolu(etiketler,uniq_etiketler,&uniq_index,uniq_sayisi,etiketsayisi);
    yebulma(uniq_etiketler, uniq_index, aramadosyasi, yetimetiket, &l, &k, &donus);
    output(uniq_etiketler,yetimetiket,uniq_sayisi,uniq_index,l,sayac);
    istenenetiketfonk(aramadosyasi,istenenetiket,uniq_etiketler,uniq_index,k,&p);
    dongu:
    menu();
    scanf("%d", &secim);
    fgetc(stdin);

    if (secim == 1)//kelime veya etiket arama
    {
        printf("\nEtiketler\n");
            for (int i = 0; i < uniq_index; i++)
            {
                printf("%s\n",uniq_etiketler[i]);
            }
        printf("\nLütfen aramak istediğiniz kelime veya etiketi giriniz:");
        char aranan[50];
        fgets(aranan, 50, stdin);
        aranan[strlen(aranan) - 1] = '\0';
        int control = 0;
            for (int i = 0; i < txtsayisi; i++)
            {
                char *derssatir = strrchr(dosyayolu[i],'\\');
                char cumle[1000];
                FILE *fp = fopen(dosyayolu[i], "r");
                int satirsayisi = 1;
                while (fgets(cumle, 1000, fp))
                {
                    char *ret = strstr(cumle, aranan);
                    while (ret != NULL)
                    {
                        int cont = 0,cont1=0;
                        int basindex = ret - cumle;
                        int sonindex = basindex + strlen(aranan);
                        if (cumle[basindex - 1] == '[' && cumle[basindex - 2] == '[' && cumle[sonindex] == ']' && cumle[sonindex + 1] == ']')
                        {
                            for (int i = 0; i < strlen(aranan); i++){
                                if (aranan[i] == ' ')
                                {    cont++;
                                }
                                if(ispunct(aranan[i]) && aranan[i]!='_'){
                                    cont1++;
                                }
                            }
                            if (cont < 2 && cont1==0)
                            {
                                printf("%s etikettir ve %s dosyasında %d.satırdadır.\n", aranan, derssatir+1, satirsayisi);
                                control++;
                            }
                            else
                            {
                                printf("%s etiket değildir ve %s dosyasında %d.satırdadır.\n", aranan, derssatir+1, satirsayisi);
                                control++;
                            }
                        }
                        else{
                            if(isalpha(cumle[sonindex])==0){
                                printf("%s etiket değildir ve %s dosyasında %d.satırdadır.\n", aranan, derssatir+1, satirsayisi);
                                control++;
                            }
                        }
                        ret = strstr(ret + 1, aranan);
                    }
                    satirsayisi++;
                }
                fclose(fp);
            }
        if (control == 0)
            printf("%s herhangi bir yerde kelime olarak geçmemektedir.", aranan);
        printf("\n\nİstenen Etiketler\n");
        for (int i = 0; i < p; i++)
            printf("%s\n", istenenetiket[i]);
    }

    if (secim == 2)//güncelleme
    {
        int secenek;
        printf("1-Etiket ve Dosya Adı Güncelleme\n2-Yetim Etiket Dosyası Açma\n3-Dosya Adı Değiştirme\n");
        printf("Yapmak istediğiniz işlemi seçiniz:");
        scanf("%d", &secenek);
        fgetc(stdin);
        if (secenek == 1)//dosya ve etiket ismi güncelleme
        {
            printf("\nEtiketler\n");
            for (int i = 0; i < uniq_index; i++)
            {
                printf("%s\n",uniq_etiketler[i]);
            }
            char *kopyala, *kopyala2;
            char yenidosyayolu[250],degisecek_etiket[100],yeni_etiket[100],eyeni_etiket[100];
            printf("Lütfen değiştirmek istediğiniz etiketi giriniz:");
            fgets(degisecek_etiket, 100, stdin);
            degisecek_etiket[strlen(degisecek_etiket) - 1] = '\0';
            printf("Lütfen yeni etiketi giriniz:");
            fgets(yeni_etiket, 100, stdin);
            yeni_etiket[strlen(yeni_etiket) - 1] = '\0';
            strcpy(eyeni_etiket,yeni_etiket);
            dosyadidegisme(yeni_etiket,degisecek_etiket,yenidosyayolu,dosyayolu,txtsayisi);
            for (int i = 0; i < txtsayisi; i++)
            {
                char c;
                int a = 0,con = 0;
                kopyala = (char *)malloc(1500);
                FILE *fpp = fopen(dosyayolu[i], "r");
                while ((c = fgetc(fpp)) != EOF)
                    kopyala[a++] = c;
                kopyala[a] = '\0';
                char *change_file;
                change_file = (char *)malloc(1500);
                change_file = etiketdegistirme(kopyala,degisecek_etiket,eyeni_etiket,&con);
                fclose(fpp);
                if (con==1)
                {
                    FILE *dopp = fopen(dosyayolu[i], "w");
                    fprintf(dopp, "%s", change_file);
                    fclose(dopp);
                }
            }
            memset(dosyayolu,0,txtsayisi);
            memset(yetimetiket,0,l*100);
            memset(etiketler,0,etiketsayisi);
            memset(uniq_etiketler,0,uniq_index);
            l = 0,k=0,donus=0,sayac = -1;
            uniq_index=0,etiketsayisi=0;
            klasorgezme(dosyayolu, &txtsayisi);
            tumetiketler(dosyayolu,txtsayisi,etiketler,&etiketsayisi);
            etikettekrarkontrolu(etiketler,uniq_etiketler,&uniq_index,uniq_sayisi,etiketsayisi);
            yebulma(uniq_etiketler,uniq_index,aramadosyasi,yetimetiket,&l,&k,&donus);
            opguncelleme=1;
        }

        if (secenek == 2)//yetim etiket dosyası oluşturma
        {
            sayac = -1;
            memset(yetimetiket,0,l*100);
            l = 0,k=0,donus=0;
            int b = 0;
            yebulma(uniq_etiketler,uniq_index,aramadosyasi,yetimetiket,&l,&k,&donus);
            printf("\nYetim Etiketler\n");
            while (++sayac < l)
                printf("%s\n", yetimetiket[sayac]);
            printf("\nLütfen dosyasını oluşturmak istediğiniz yetim etiketi giriniz:");
            char olusacak[100],filess[250];
            fgets(olusacak, 100, stdin);
            olusacak[strlen(olusacak) - 1] = '\0';
            for (int i = 0; i < l; i++)
            {
                int r = ft_strstr(yetimetiket[i], olusacak);
                if (r != 0)
                {
                    sprintf(filess, "C:\\Users\\FAHRETTIN\\Desktop\\Üniversite\\Dersler\\%s.txt", olusacak);
                    FILE *yedosyaolusturma = fopen(filess, "w");
                    fprintf(yedosyaolusturma, "Dersin Adı: [[%s]]\nDersin Kodu:BLM%d\nDersin içeriği:", yetimetiket[i], kod);
                    b++;
                    kod++;
                    printf("Yetim etiket dosyası oluşturuldu");
                    fclose(yedosyaolusturma);
                }
            }
            opguncelleme=1;
        }
        if (secenek == 3)//dosya adı değiştirme
        {
            memset(dosyayolu,0,txtsayisi);
            memset(yetimetiket,0,l*100);
            memset(etiketler,0,etiketsayisi);
            memset(uniq_etiketler,0,uniq_index);
            l = 0,k=0,donus=0,sayac = -1;
            uniq_index=0,etiketsayisi=0;
            klasorgezme(dosyayolu, &txtsayisi);
            tumetiketler(dosyayolu,txtsayisi,etiketler,&etiketsayisi);
            etikettekrarkontrolu(etiketler,uniq_etiketler,&uniq_index,uniq_sayisi,etiketsayisi);
            yebulma(uniq_etiketler,uniq_index,aramadosyasi,yetimetiket,&l,&k,&donus);
            char bastir[50],eskidosya[50],yenidosyaismi[50],yenidosyayolu[250];
            printf("\nDosya İsimleri\n");
            for (int i = 0; i < k; i++)
            {
                aramadosyasi[i][strlen(aramadosyasi[i])-5]='\0';
                printf("%s\n",aramadosyasi[i]);
            }
            printf("\nLütfen değiştirmek istediğiniz dosya adını giriniz:");
            fgets(eskidosya, 50, stdin);
            eskidosya[strlen(eskidosya) - 1] = '\0';
            printf("Lütfen yeni dosya adını giriniz:");
            fgets(yenidosyaismi, 50, stdin);
            yenidosyaismi[strlen(yenidosyaismi) - 1] = '\0';
            dosyadidegisme(yenidosyaismi,eskidosya,yenidosyayolu,dosyayolu,txtsayisi);
        }
        printf("\n\nİstenen Etiketler\n");
        for (int i = 0; i < p; i++)
            printf("%s\n", istenenetiket[i]);
    }
    if(secim==3)//konsol temizleme
        system("cls");
    if (secim == 4)//çıkış ve güncel output yazdırma
    {
        if(opguncelleme==1){
        memset(dosyayolu,0,txtsayisi);
        memset(yetimetiket,0,l*100);
        memset(etiketler,0,etiketsayisi);
        memset(uniq_etiketler,0,uniq_index);
        l = 0,k=0,donus=0,sayac = -1;
        uniq_index=0,etiketsayisi=0;
        klasorgezme(dosyayolu, &txtsayisi);
        tumetiketler(dosyayolu,txtsayisi,etiketler,&etiketsayisi);
        etikettekrarkontrolu(etiketler,uniq_etiketler,&uniq_index,uniq_sayisi,etiketsayisi);
        yebulma(uniq_etiketler,uniq_index,aramadosyasi,yetimetiket,&l,&k,&donus);
        outputguncel(uniq_etiketler,yetimetiket,uniq_sayisi,uniq_index,l,sayac);
        }
        exit(0);
    }
    goto dongu;//arayüz döngüsü
    return 0;
}