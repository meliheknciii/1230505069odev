#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEKLIF_VERENLER 100 // En fazla teklif verebilecek kiþi sayýsý
#define URUN_ADI_UZUNLUK 50 // Bu makro, açýk artýrmadaki ürün adýnýn maksimum uzunluðunu belirler. Yani, urun_adi dizisinin en fazla 50 karakter içerebileceðini belirtir.

struct AcikArtirmaOyunu {
    char urun_adi[URUN_ADI_UZUNLUK]; // urun adi olusturduk - tablo
    float mevcut_fiyat; // fiyat belirledik
    char mevcut_teklif_veren[20]; // teklif veren bilgisi
};

void acikArtirmayiBaslat(struct AcikArtirmaOyunu *artirma) {
    printf("%s icin acik artirma baþladi, baþlangic fiyati %.2f.\n", artirma->urun_adi, artirma->mevcut_fiyat);

    while (1) {
        char teklif[20];
        printf("Teklifinizi girin (Acik artirmayi sonlandýrmak icin 'quit' yazin): ");
        scanf("%s", teklif);

        if (strcmp(teklif, "quit") == 0) {
            printf("Acik artirma sona erdi. Baþka teklif yok.\n");
            break;
        }

        if (teklifVer(artirma, teklif)) {
            printf("Mevcut en yuksek teklif: %.2f, veren: %s\n", artirma->mevcut_fiyat, artirma->mevcut_teklif_veren);
        }
    }
}

int teklifVer(struct AcikArtirmaOyunu *artirma, char *teklif) {
    float teklifMiktari; // girilen teklif miktari
    if (sscanf(teklif, "%f", &teklifMiktari) == 1) {
        if (teklifMiktari > artirma->mevcut_fiyat) {
            artirma->mevcut_fiyat = teklifMiktari;
            snprintf(artirma->mevcut_teklif_veren, sizeof(artirma->mevcut_teklif_veren), "TeklifVeren%d", rand() % MAX_TEKLIF_VERENLER + 1); // rastgele sayi atadik teklifveren e 
            return 1;
        } else {
            printf("Teklif, mevcut fiyattan daha yuksek olmalidir.\n");
        }
    } else {
        printf("Gecersiz teklif. Lutfen geçerli bir sayi girin.\n"); // dusuk fiyat verirse 
    }

    return 0;
}

int main() {
    struct AcikArtirmaOyunu artirma;
    strncpy(artirma.urun_adi, "Antika Tablo", sizeof(artirma.urun_adi));
    artirma.mevcut_fiyat = 100.0;

    acikArtirmayiBaslat(&artirma);
}
