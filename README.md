# Kredi Başvurusu Onay Sistemi

Bu proje, C++ kullanarak **kredi başvurularının otomatik olarak değerlendirilmesi ve onaylanması** için bir makine öğrenimi sistemi geliştirmektedir. Geçmiş verilere dayanarak, başvuranların kredi onayı için uygun olup olmadığını tahmin etmek amacıyla çeşitli sınıflandırma algoritmalarını inceliyor ve karşılaştırıyor.

---

## İçerik

* [Proje Amacı](#proje-amacı)
* [Kullanılan Modeller](#kullanılan-modeller)
* [Veri Seti](#veri-seti)
* [Kurulum ve Çalıştırma](#kurulum-ve-çalıştırma)
* [Proje Yapısı](#proje-yapısı)
* [Performans Metrikleri](#performans-metrikleri)
* [Katkıda Bulunma](#katkıda-bulunma)
* [Lisans](#lisans)

---

## Proje Amacı

Günümüz finans dünyasında, kredi başvurularının hızlı ve tutarlı bir şekilde değerlendirilmesi büyük önem taşır. Bu proje, manuel değerlendirme süreçlerinin getirdiği yükü hafifletmek ve daha **veri odaklı kararlar** almak için makine öğreniminin nasıl kullanılabileceğini göstermeyi amaçlar.

**Temel hedefler:**

* Geçmiş kredi verilerini kullanarak, potansiyel başvuranlar için kredi onayı veya reddi tahmininde bulunmak.
* Farklı makine öğrenimi algoritmalarının (Perceptron, Lojistik Regresyon, Basit Karar Ağacı, Doğrusal SVM) performanslarını karşılaştırmak.
* C++'ta temel makine öğrenimi algoritmalarının "sıfırdan" nasıl implemente edilebileceğini göstermek.
* Finansal kuruluşlar için daha hızlı ve verimli karar destek sistemleri geliştirmeye yönelik bir prototip sunmak.

---

## Kullanılan Modeller

Projede, kredi başvurularını sınıflandırmak için beş farklı makine öğrenimi modeli implemente edilmiştir:

* **Perceptron:** Temel bir tek katmanlı sinir ağı.
* **Basit Kural Modeli:** Belirli önceden tanımlanmış kurallara dayalı basit bir sınıflandırıcı.
* **Lojistik Regresyon:** Olasılıksal bir model olup, sonuçlarınızda en iyi performansı gösteren algoritmadır.
* **Basit Karar Ağacı:** Tek bir özelliğe ve eşiğe dayalı hızlı bir karar verme mekanizması.
* **Doğrusal SVM (Destek Vektör Makinesi):** Veriler arasındaki en iyi ayırıcı hiperdüzlemi bulmaya çalışan bir model.

---

## Veri Seti

Proje, `kredi_basvurusu_veri_seti.csv` adlı bir CSV dosyasından veri okur. Bu veri seti aşağıdaki özellikleri içerir:

* `id`: Başvuru numarası
* `yas`: Başvuranın yaşı
* `gelir`: Başvuranın geliri
* `krediSkoru`: Başvuranın kredi skoru
* `evSahibi`: Ev sahibi durumu (`'E'` veya `'H'`)
* `calismaSuresi`: Mevcut işindeki çalışma süresi
* `krediOnayi`: Hedef değişken (`1`: Onaylandı, `0`: Onaylanmadı)

Veri seti, modellerin daha iyi performans göstermesi için **Min-Max Normalizasyonu** kullanılarak ön işleme tabi tutulur.

---

## Kurulum ve Çalıştırma

Projeyi yerel ortamınızda veya Replit gibi bir platformda çalıştırmak için aşağıdaki adımları izleyin.

### Önkoşullar

* C++11 veya daha yeni bir standardı destekleyen bir C++ derleyicisi (örn. `g++`).

### Adımlar

1.  **Depoyu Klonlayın:**
    ```bash
    git clone [https://github.com/KULLANICI_ADINIZ/kredi-basvurusu-onay-sistemi.git](https://github.com/KULLANICI_ADINIZ/kredi-basvurusu-onay-sistemi.git)
    cd kredi-basvurusu-onay-sistemi
    ```
    *(Yukarıdaki `KULLANICI_ADINIZ` kısmını kendi GitHub kullanıcı adınızla değiştirmeyi unutmayın.)*

2.  **Veri Setini Yerleştirin:**
    `kredi_basvurusu_veri_seti.csv` dosyasının projenin kök dizininde bulunduğundan emin olun.

3.  **Derleme ve Çalıştırma:**

    **Yerel Ortamda:**
    Aşağıdaki komutu kullanarak tüm `.cpp` dosyalarını derleyin ve programı çalıştırın:
    ```bash
    g++ main.cpp Metrics.cpp HelperFunctions.cpp Perceptron.cpp SimpleRuleModel.cpp LogisticRegression.cpp SimpleDecisionTree.cpp LinearSVM.cpp -o kredi_onay_sistemi -std=c++11 -Wall
    ./kredi_onay_sistemi
    ```

    **Replit Üzerinde:**
    `run` komutunuzu içerecek şekilde `.replit` dosyanızı aşağıdaki gibi güncelleyin/oluşturun:
    ```replit
    run = "g++ main.cpp Metrics.cpp HelperFunctions.cpp Perceptron.cpp SimpleRuleModel.cpp LogisticRegression.cpp SimpleDecisionTree.cpp LinearSVM.cpp -o kredi_onay_sistemi -std=c++11 && ./kredi_onay_sistemi"
    ```
    Ardından Replit arayüzündeki **"Run"** butonuna basın.

---

## Proje Yapısı

Proje, daha iyi modülerlik ve okunabilirlik için ayrı dosyalara bölünmüştür:

.
├───kredi_basvurusu_veri_seti.csv
├───main.cpp                  # Ana program mantığı ve model çalıştırma
├───Basvuru.h                 # Kredi başvurusu veri yapısı
├───Metrics.h                 # Performans metrikleri tanımı
├───Metrics.cpp               # Performans metrikleri implementasyonu
├───HelperFunctions.h         # Veri okuma, normalizasyon vb. yardımcı fonksiyonlar
├───HelperFunctions.cpp       # Yardımcı fonksiyonların implementasyonu
├───Perceptron.h              # Perceptron model tanımı
├───Perceptron.cpp            # Perceptron implementasyonu
├───SimpleRuleModel.h         # Basit Kural Modeli tanımı
├───SimpleRuleModel.cpp       # Basit Kural Modeli implementasyonu
├───LogisticRegression.h      # Lojistik Regresyon model tanımı
├───LogisticRegression.cpp    # Lojistik Regresyon implementasyonu
├───SimpleDecisionTree.h      # Basit Karar Ağacı model tanımı
├───SimpleDecisionTree.cpp    # Basit Karar Ağacı implementasyonu
├───LinearSVM.h               # Doğrusal SVM model tanımı
└───LinearSVM.cpp             # Doğrusal SVM implementasyonu


---

## Performans Metrikleri

Modellerin performansı aşağıdaki metrikler kullanılarak değerlendirilir:

* **Doğruluk (Accuracy):** Tüm tahminlerin ne kadarının doğru olduğu.
* **Kesinlik (Precision):** Pozitif olarak tahmin edilenlerin ne kadarının gerçekten pozitif olduğu.
* **Hatırlama (Recall):** Gerçekten pozitif olanların ne kadarının doğru bir şekilde pozitif olarak tahmin edildiği.
* **F1-Skoru:** Kesinlik ve Hatırlama'nın harmonik ortalaması, dengeli bir performans göstergesi.

---

## Katkıda Bulunma

Geliştirme önerilerine açığız! Projeye katkıda bulunmak isterseniz:

1.  Bu depoyu forklayın.
2.  Yeni bir özellik dalı oluşturun (`git checkout -b ozellik/yeni-ozellik`).
3.  Değişikliklerinizi yapın ve commit'leyin (`git commit -am 'Yeni özellik ekle: ...'`).
4.  Dalınızı push edin (`git push origin ozellik/yeni-ozellik`).
5.  Bir Pull Request (Çekme İsteği) oluşturun.

---

## Lisans

Bu proje, açık kaynaklı bir lisans altında yayınlanmıştır. Daha fazla bilgi için `LICENSE` dosyasına bakınız.

---
