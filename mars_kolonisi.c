#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Mars Kolonisi Yasam Destek Simulatoru

int main() {
    int saglik, enerji, oksijen, su, yedekParca, modulHasari;
    int kilitMuhurlu = 0;
    int gun = 1, tur = 0;

    char zorluk, komut;
    int zorlukGecerli = 0;

    int firtinaTur, firtinaHasar;
    int esikYuksek, esikDusuk;

    int devam = 1;
    int sonuc = 0;          // 1 kazandi, 2 kaybetti, 3 cikis
    int turHarcandi;
    int temizle;

    int zar, zar2, esik;
    int miktar, uretilen, tuketilen;
    int gerekenParca, harcananParca, birimOnarim, onarilan;
    int i, carpan, olayEsik, kayip;
    int hasarliTur, saglikOnce, oksijenOnce;
    char sifre, girilen;
    int deneme;
    int hayattaKalinanGun, puan;

    srand(time(NULL));

    printf("=== MARS KOLONISI YASAM DESTEK SIMULATORU ===\n");

    // zorluk secimi
    do {
        printf("\nZorluk seviyesi sec (K: Kolay, N: Normal, Z: Zor): ");
        scanf(" %c", &zorluk);
        while ((temizle = getchar()) != '\n' && temizle != EOF);

        switch (zorluk) {
            case 'k':
            case 'K':
                saglik = 100; enerji = 100; oksijen = 100;
                su = 30; yedekParca = 3; modulHasari = 0;
                firtinaTur = 3; firtinaHasar = 5;
                esikYuksek = 70; esikDusuk = 40;
                printf("Kolay seviye secildi.\n");
                zorlukGecerli = 1;
                break;
            case 'n':
            case 'N':
                saglik = 100; enerji = 90; oksijen = 90;
                su = 24; yedekParca = 2; modulHasari = 10;
                firtinaTur = 5; firtinaHasar = 8;
                esikYuksek = 60; esikDusuk = 30;
                printf("Normal seviye secildi.\n");
                zorlukGecerli = 1;
                break;
            case 'z':
            case 'Z':
                saglik = 90; enerji = 80; oksijen = 80;
                su = 20; yedekParca = 1; modulHasari = 20;
                firtinaTur = 7; firtinaHasar = 12;
                esikYuksek = 50; esikDusuk = 20;
                printf("Zor seviye secildi.\n");
                zorlukGecerli = 1;
                break;
            default:
                printf("Gecersiz seviye! K, N veya Z gir.\n");
        }
    } while (zorlukGecerli == 0);

    // ana oyun dongusu
    do {
        turHarcandi = 0;

        printf("\n-------------------------------------------\n");
        printf("Gun: %d | Tur: %d | Saglik: %d | Enerji: %d | Oksijen: %d\n",
               gun, tur, saglik, enerji, oksijen);
        printf("Su: %d | Yedek Parca: %d | Modul Hasari: %d | Kilit: %d\n",
               su, yedekParca, modulHasari, kilitMuhurlu);
        printf("G-Kesif O-Oksijen T-Tamir D-Durum U-Uyu K-Firtina H-Hava kilidi Q-Cikis\n");
        printf("Komut: ");
        scanf(" %c", &komut);
        while ((temizle = getchar()) != '\n' && temizle != EOF);

        switch (komut) {

            case 'g':   // fall-through: g ve G ayni yere duser
            case 'G':
                if (enerji < 15) {
                    printf("Enerjin yetersiz (en az 15 gerekli)! Kesif iptal.\n");
                } else if (oksijen < 10) {
                    printf("Oksijenin yetersiz (en az 10 gerekli)! Kesif iptal.\n");
                } else {
                    enerji = enerji - 15;
                    oksijen = oksijen - 10;
                    turHarcandi = 1;
                    printf("Kesife ciktin. (-15 enerji, -10 oksijen)\n");

                    if (enerji > 40 && oksijen > 30) {
                        esik = esikYuksek;
                    } else {
                        esik = esikDusuk;
                    }

                    zar = rand() % 100;
                    printf("Yaralanma -> Zar: %d / Esik: 10 (veya modul hasari > 70)\n", zar);
                    if (zar < 10 || modulHasari > 70) {
                        saglik = saglik - 10;
                        printf("Yaralandin! (-10 saglik)\n");
                    } else {
                        printf("Yaralanmadin.\n");
                    }

                    zar2 = rand() % 100;
                    printf("Kesif sonucu -> Zar: %d / Esik: %d", zar2, esik);
                    if (zar2 < esik) {
                        printf(" -> BASARILI\n");
                        su = su + 10;
                        printf("Su buldun! (+10 su)\n");
                    } else if (zar2 < esik + 20) {
                        printf(" -> BASARILI\n");
                        yedekParca = yedekParca + 1;
                        printf("Yedek parca buldun! (+1 parca)\n");
                    } else {
                        printf(" -> BASARISIZ\n");
                        printf("Eli bos dondun.\n");
                    }
                }
                break;

            case 'o':
            case 'O':
                if (enerji < 10) {
                    printf("Enerjin yetersiz (en az 10 gerekli)! Iptal.\n");
                } else if (su < 2) {
                    printf("Yeterli su yok (en az 2 gerekli)! Iptal.\n");
                } else {
                    printf("Mevcut su: %d. Kac birim su kullanilsin? ", su);
                    if (scanf("%d", &miktar) != 1) {
                        miktar = 0;
                    }
                    while ((temizle = getchar()) != '\n' && temizle != EOF);

                    if (miktar < 2) {
                        printf("Gecersiz miktar! Iptal.\n");
                    } else if (miktar > su) {
                        printf("Mevcut sudan fazla girilemez! Iptal.\n");
                    } else {
                        // mod ile cift/tek kontrolu
                        if (miktar % 2 == 0) {
                            tuketilen = miktar;
                            printf("Miktar cift, hepsi kullanilacak.\n");
                        } else {
                            tuketilen = miktar - 1;
                            printf("Miktar tek, 1 birim artik kaldi.\n");
                        }
                        uretilen = (tuketilen / 2) * 3;   // 2 su = 3 oksijen

                        su = su - tuketilen;
                        enerji = enerji - 10;
                        oksijen = oksijen + uretilen;
                        turHarcandi = 1;
                        printf("%d su harcandi, %d oksijen uretildi. (-10 enerji)\n", tuketilen, uretilen);
                    }
                }
                break;

            case 't':
            case 'T':
                if (yedekParca <= 0) {
                    printf("Yedek parcan yok, tamir yapilamaz!\n");
                } else if (enerji < 10) {
                    printf("Enerjin yetersiz (en az 10 gerekli)! Iptal.\n");
                } else if (modulHasari == 0) {
                    printf("Modulde hasar yok.\n");
                } else {
                    // hasara gore 3 kademe
                    if (modulHasari <= 30) {
                        printf("Hasar: HAFIF\n");
                        gerekenParca = 1;
                        birimOnarim = 15;
                    } else if (modulHasari <= 70) {
                        printf("Hasar: ORTA\n");
                        gerekenParca = 2;
                        birimOnarim = 20;
                    } else {
                        printf("Hasar: AGIR\n");
                        gerekenParca = 3;
                        birimOnarim = 25;
                    }

                    if (yedekParca < gerekenParca) {
                        harcananParca = yedekParca;
                    } else {
                        harcananParca = gerekenParca;
                    }

                    onarilan = harcananParca * birimOnarim;
                    yedekParca = yedekParca - harcananParca;
                    modulHasari = modulHasari - onarilan;
                    enerji = enerji - 10;
                    turHarcandi = 1;
                    printf("%d parca harcandi, %d hasar onarildi. (-10 enerji)\n", harcananParca, onarilan);
                }
                break;

            case 'd':
            case 'D':
                printf("\n=== DURUM RAPORU ===\n");
                printf("Saglik: %d\nEnerji: %d\nOksijen: %d\nSu: %d\n", saglik, enerji, oksijen, su);
                printf("Yedek Parca: %d\nModul Hasari: %d\n", yedekParca, modulHasari);
                if (kilitMuhurlu == 1) {
                    printf("Hava Kilidi: MUHURLU\n");
                } else {
                    printf("Hava Kilidi: MUHURSUZ\n");
                }
                printf("Gun: %d | Tur: %d\n", gun, tur);

                if (oksijen < 25) {
                    printf("UYARI: Oksijen kritik!\n");
                }
                if (saglik < 30) {
                    printf("UYARI: Saglik kritik!\n");
                }
                if (enerji < 20) {
                    printf("UYARI: Enerji kritik!\n");
                }
                if (modulHasari > 70) {
                    printf("UYARI: Modul hasari kritik!\n");
                }

                if (saglik >= 30 && enerji >= 20 && oksijen >= 25 && modulHasari <= 70) {
                    printf("TUM SISTEMLER NORMAL\n");
                }
                break;

            case 'u':
            case 'U':
                turHarcandi = 1;
                enerji = enerji + 25;
                if (oksijen < 20) {
                    saglik = saglik - 5;
                    printf("Oksijen az, dinlenirken saglik dustu. (-5 saglik, +25 enerji)\n");
                    if (oksijen < 10) {
                        saglik = saglik - 5;
                        printf("Oksijen cok tehlikeli, ekstra -5 saglik!\n");
                    }
                } else {
                    saglik = saglik + 10;
                    printf("Dinlendin. (+10 saglik, +25 enerji)\n");
                }
                oksijen = oksijen - 1;
                printf("Oksijen tuketimi: -1\n");
                break;

            case 'k':
            case 'K':
                if (enerji < 10) {
                    printf("Enerjin yetersiz (en az 10 gerekli)! Iptal.\n");
                } else {
                    enerji = enerji - 10;
                    turHarcandi = 1;
                    saglikOnce = saglik;
                    oksijenOnce = oksijen;
                    hasarliTur = 0;

                    printf("\n*** KUM FIRTINASI (%d tur) *** (-10 enerji)\n", firtinaTur);

                    for (i = 1; i <= firtinaTur; i++) {
                        zar = rand() % 100;

                        carpan = 1;
                        if (i % 2 == 0) {   // cift turda hasar 2 kat
                            carpan = 2;
                            printf("Tur %d: Ruzgar siddetlendi, hasar x2!\n", i);
                        } else {
                            printf("Tur %d:\n", i);
                        }

                        if (enerji < 30) {
                            olayEsik = 40;
                        } else {
                            olayEsik = 25;
                        }
                        printf("  Zar: %d / Esik: %d\n", zar, olayEsik);

                        if (zar < olayEsik) {
                            kayip = 5 * carpan;
                            saglik = saglik - kayip;
                            hasarliTur = hasarliTur + 1;
                            printf("  Savruldun! -%d saglik\n", kayip);
                        } else if (zar < olayEsik + 20) {
                            if (kilitMuhurlu == 1) {
                                printf("  Kilit muhurlu, sizinti olmadi.\n");
                                continue;   // bu turu atla
                            }
                            kayip = 6 * carpan;
                            oksijen = oksijen - kayip;
                            hasarliTur = hasarliTur + 1;
                            printf("  Oksijen sizdi! -%d oksijen\n", kayip);
                        } else if (zar < olayEsik + 40) {
                            kayip = firtinaHasar * carpan;
                            modulHasari = modulHasari + kayip;
                            hasarliTur = hasarliTur + 1;
                            printf("  Modul hasar aldi! +%d hasar\n", kayip);
                        } else {
                            printf("  Zarar gormedin.\n");
                        }

                        if (saglik < 0) {
                            saglik = 0;
                        }
                        if (oksijen < 0) {
                            oksijen = 0;
                        }
                        if (modulHasari > 100) {
                            modulHasari = 100;
                        }

                        if (saglik <= 0 || oksijen <= 0) {
                            printf("  Tehlikeli! Firtina aniden bitti.\n");
                            break;
                        }
                    }

                    printf("\n--- FIRTINA OZETI ---\n");
                    printf("Hasar alinan tur: %d\n", hasarliTur);
                    printf("Kaybedilen saglik: %d\n", saglikOnce - saglik);
                    printf("Kaybedilen oksijen: %d\n", oksijenOnce - oksijen);
                }
                break;

            case 'h':
            case 'H':
                if (kilitMuhurlu == 1) {
                    printf("Hava kilidi zaten muhurlu.\n");
                } else if (enerji < 5) {
                    printf("Enerjin yetersiz (en az 5 gerekli)! Iptal.\n");
                } else {
                    turHarcandi = 1;
                    sifre = 'A' + (gun % 26);
                    deneme = 0;
                    girilen = 0;

                    printf("Sifre A-Z arasi bir buyuk harf.\n");
                    printf("Ipucu: Sifre, A harfinden bugunun gun sayisi kadar ilerideki harf.\n");
                    printf("3 deneme hakkin var.\n");

                    do {
                        printf("Deneme %d - harf gir: ", deneme + 1);
                        scanf(" %c", &girilen);
                        while ((temizle = getchar()) != '\n' && temizle != EOF);

                        if (girilen >= 'a' && girilen <= 'z') {
                            girilen = girilen - 'a' + 'A';
                        }
                        deneme = deneme + 1;

                        if (girilen != sifre) {
                            enerji = enerji - 5;
                            if (girilen < sifre) {
                                printf("Yanlis! ileri git. (-5 enerji)\n");
                            } else {
                                printf("Yanlis! geri git. (-5 enerji)\n");
                            }
                        }
                    } while (girilen != sifre && deneme < 3 && enerji > 0);

                    if (enerji < 0) {
                        enerji = 0;
                    }

                    if (girilen == sifre) {
                        kilitMuhurlu = 1;
                        printf("Sifre dogru! Hava kilidi muhurlendi.\n");
                    } else if (deneme >= 3) {
                        modulHasari = modulHasari + 20;
                        printf("3 deneme de yanlis! Modul hasari +20.\n");
                    } else {
                        printf("Enerjin bitti, yeni deneme yapamazsin! Kilit muhursuz kaldi.\n");
                    }
                }
                break;

            case 'q':
            case 'Q':
                printf("Cikis yapiliyor...\n");
                devam = 0;
                sonuc = 3;
                break;

            default:
                printf("Tanimsiz komut! (tur harcanmadi)\n");
        }

        // degerleri 0-100 arasinda tut
        if (saglik < 0) {
            saglik = 0;
        }
        if (saglik > 100) {
            saglik = 100;
        }
        if (enerji < 0) {
            enerji = 0;
        }
        if (enerji > 100) {
            enerji = 100;
        }
        if (oksijen < 0) {
            oksijen = 0;
        }
        if (oksijen > 100) {
            oksijen = 100;
        }
        if (modulHasari < 0) {
            modulHasari = 0;
        }
        if (modulHasari > 100) {
            modulHasari = 100;
        }

        // zaman akisi
        if (turHarcandi == 1) {
            tur = tur + 1;

            if (tur % 3 == 0) {   // 3 turda bir yeni gun
                gun = gun + 1;
                oksijen = oksijen - 8;
                printf("\n>>> YENI GUN: Gun %d (oksijen -8)\n", gun);
                if (modulHasari > 70) {
                    saglik = saglik - 5;
                    printf(">>> Modul hasari yuksek, -5 saglik!\n");
                }

                if (saglik < 0) {
                    saglik = 0;
                }
                if (oksijen < 0) {
                    oksijen = 0;
                }
            }
        }

        // oyun sonu kontrolu
        if (devam == 1) {
            if (saglik <= 0 || oksijen <= 0) {
                printf("\nOYUN BITTI: Hayatta kalamadin...\n");
                devam = 0;
                sonuc = 2;
            } else if (gun > 15) {
                printf("\nTEBRIKLER! Kurtarma ekibi geldi, 15 gunu tamamladin!\n");
                devam = 0;
                sonuc = 1;
            }
        }

    } while (devam == 1);

    // sonuc raporu
    hayattaKalinanGun = gun - 1;
    puan = (hayattaKalinanGun * 100) + saglik + oksijen - modulHasari;

    printf("\n===========================================\n");
    printf("              SONUC RAPORU\n");
    printf("===========================================\n");
    if (sonuc == 1) {
        printf("Durum: KAZANDIN\n");
    } else if (sonuc == 2) {
        printf("Durum: KAYBETTIN\n");
    } else {
        printf("Durum: OYUNDAN CIKTIN\n");
    }
    printf("Hayatta kalinan gun: %d\n", hayattaKalinanGun);
    printf("Toplam tur: %d\n", tur);
    printf("Saglik: %d | Enerji: %d | Oksijen: %d\n", saglik, enerji, oksijen);
    printf("Su: %d | Yedek Parca: %d | Modul Hasari: %d\n", su, yedekParca, modulHasari);
    printf("PUAN = (gun x 100) + saglik + oksijen - modulHasari = %d\n", puan);
    printf("===========================================\n");

    return 0;
}
