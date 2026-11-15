# Mars Kolonisi Yaşam Destek Simülatörü

C diliyle yazılmış, metin tabanlı ve tek harfli komutlarla oynanan bir hayatta kalma oyunu.
Oyuncu, Mars'taki küçük bir araştırma istasyonunda tek başına kalmış bir mühendisi yönetir ve
kurtarma ekibi gelene kadar **15 gün** hayatta kalmaya çalışır.

> Algoritma ve Programlama dersi ödevi olarak hazırlanmıştır.
> Hazırlayan: [Yasin KAYA] - [1260505035]

## İçindekiler

- [Özellikler](#özellikler)
- [Kurulum ve Çalıştırma](#kurulum-ve-çalıştırma)
- [Oyun Mantığı](#oyun-mantığı)
- [Komutlar](#komutlar)
- [Zorluk Seviyeleri](#zorluk-seviyeleri)
- [Kullanılan C Yapıları](#kullanılan-c-yapıları)
- [Örnek Çıktı](#örnek-çıktı)

## Özellikler

- Sağlık, enerji, oksijen, su, yedek parça ve modül hasarı takibi
- 3 zorluk seviyesi (Kolay, Normal, Zor)
- Büyük/küçük harf duyarsız komut sistemi
- Rastgele olaylar: her zar ve eşik değeri ekrana yazdırılır
- Kum fırtınası simülasyonu ve şifreli hava kilidi mini oyunu
- Oyun sonunda puan hesaplayan sonuç raporu

## Kurulum ve Çalıştırma

Projeyi bilgisayarına indir:

```bash
git clone https://github.com/[yasin-ky]/[mars-koloni-projesi].git
cd [mars-koloni-projesi]
```

**GCC ile derleme:**

```bash
gcc mars_kolonisi.c -o mars
./mars
```

Windows'ta çalıştırmak için `mars.exe` yazman yeterlidir.

**Visual Studio ile:** Boş bir C++ projesi oluştur, `mars_kolonisi.c` dosyasını **Source Files**
altına ekle ve `Ctrl + F5` ile çalıştır. Dosya uzantısının `.c` olduğundan emin ol.

## Oyun Mantığı

- Geçerli her komut bir **tur** harcar (`D` ve tanımsız komutlar hariç).
- Her **3 turda** bir yeni gün başlar. Gün başında oksijen 8 azalır, modül hasarı 70'in
  üzerindeyse ek olarak 5 sağlık kaybedilir.
- Sağlık, enerji, oksijen ve modül hasarı her komuttan sonra 0-100 aralığında tutulur.
- Enerjisi veya kaynağı yetmeyen komut iptal edilir ve tur harcamaz.

**Oyun sonu:**

| Durum | Sonuç |
|---|---|
| Sağlık veya oksijen 0'a düşerse | Oyun kaybedilir |
| 15. gün tamamlanırsa | Kurtarma ekibi gelir, oyun kazanılır |
| `Q` komutu girilirse | Oyundan çıkılır |

Her durumda sonuç raporu yazdırılır (hayatta kalınan gün, toplam tur, son değerler ve puan).

**Puan formülü:**

```
Puan = (gun x 100) + saglik + oksijen - modulHasari
```

Burada `gun`, tamamlanan gün sayısıdır.

## Komutlar

| Komut | İşlev |
|---|---|
| `G` | Keşif görevi: enerji -15, oksijen -10. Su bulabilir, yedek parça bulabilir veya eli boş dönebilir. Yaralanma riski vardır. |
| `O` | Oksijen üret: 2 birim su 3 birim oksijene dönüşür, enerji -10. Tek sayı girilirse 1 birim su artık olarak kalır. |
| `T` | Tamir: yedek parça harcayarak modül hasarını azaltır (hafif, orta, ağır kademe), enerji -10. |
| `D` | Durum raporu: tüm değerleri ve kritik uyarıları gösterir. Tur harcamaz. |
| `U` | Uyu / dinlen: enerji ve sağlık artar. Oksijen 20'nin altındaysa sağlık azalır. |
| `K` | Kum fırtınası simülasyonu (for döngüsü), enerji -10. |
| `H` | Hava kilidi şifresi: en fazla 3 denemeyle kilidi mühürle. |
| `Q` | Çıkış. |

Komutlar büyük veya küçük harfle girilebilir (`g` ve `G` aynıdır). Tanımsız bir komut girilirse
uyarı verilir ve tur harcanmaz.

### Tamir kademeleri

| Modül hasarı | Seviye | Harcanan parça | Parça başına onarım |
|---|---|---|---|
| 0 - 30 | Hafif | 1 | 15 |
| 31 - 70 | Orta | 2 | 20 |
| 71 - 100 | Ağır | 3 | 25 |

### Hava kilidi şifresi

Şifre, A harfinden bugünün gün sayısı kadar ilerideki harftir (`'A' + gun % 26`).
Oyuncunun 3 deneme hakkı vardır. Her yanlış denemede enerji 5 azalır ve "ileri git" veya
"geri git" ipucu verilir. Doğru şifre kilidi mühürler ve fırtınalarda oksijen sızıntısını
engeller. 3 deneme de başarısız olursa modül hasarı 20 artar.

## Zorluk Seviyeleri

| | Kolay (K) | Normal (N) | Zor (Z) |
|---|---|---|---|
| Sağlık | 100 | 100 | 90 |
| Enerji | 100 | 90 | 80 |
| Oksijen | 100 | 90 | 80 |
| Su | 30 | 24 | 20 |
| Yedek parça | 3 | 2 | 1 |
| Başlangıç modül hasarı | 0 | 10 | 20 |
| Fırtına süresi (tur) | 3 | 5 | 7 |
| Fırtına hasarı | 5 | 8 | 12 |
| Keşifte su bulma eşiği (iyi / kötü durum) | 70 / 40 | 60 / 30 | 50 / 20 |

## Kullanılan C Yapıları

- **switch-case:** komut sistemi ve zorluk seçimi. Büyük/küçük harf için fall-through kullanıldı
  (`case 'g': case 'G':`), tanımsız girişler `default` bloğunda yakalanır.
- **if - else if - else:** tamir kademeleri, keşif sonuçları, durum raporu uyarıları, sınırlandırma.
- **for döngüsü:** kum fırtınası. `break` ile erken bitirme ve `continue` ile tur atlama içerir.
- **do-while döngüsü:** ana oyun döngüsü, zorluk seçimi ve sınırlı denemeli şifre mekanizması.
- **Aritmetik operatörler:** özellikle mod (`%`): zar (`rand() % 100`), çift/tek kontrolü ve
  gün hesabı (`tur % 3 == 0`).
- **Mantıksal operatörler:** `&&` ve `||` ile birleşik koşullar.
- **Rastgelelik:** `srand(time(NULL))` ve `rand() % 100`.

## Örnek Çıktı

```
=== MARS KOLONISI YASAM DESTEK SIMULATORU ===

Zorluk seviyesi sec (K: Kolay, N: Normal, Z: Zor): k
Kolay seviye secildi.

-------------------------------------------
Gun: 1 | Tur: 0 | Saglik: 100 | Enerji: 100 | Oksijen: 100
Su: 30 | Yedek Parca: 3 | Modul Hasari: 0 | Kilit: 0
G-Kesif O-Oksijen T-Tamir D-Durum U-Uyu K-Firtina H-Hava kilidi Q-Cikis
Komut: g
Kesife ciktin. (-15 enerji, -10 oksijen)
Yaralanma -> Zar: 46 / Esik: 10 (veya modul hasari > 70)
Yaralanmadin.
Kesif sonucu -> Zar: 80 / Esik: 70 -> BASARILI
Yedek parca buldun! (+1 parca)
```
