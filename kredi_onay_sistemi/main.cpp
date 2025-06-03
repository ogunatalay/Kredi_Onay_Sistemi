#include <iostream>
#include <vector>
#include <string>
#include <numeric> // std::iota için
#include <random>  // std::shuffle için

// Yardımcı fonksiyonlar, veri yapıları ve model sınıflarının başlık dosyalarını dahil et
#include "Basvuru.h"
#include "Metrics.h"
#include "HelperFunctions.h" // veriOku, evSahibiToInt, normalizeFeatures, applyNormalization, analyzeClassDistribution içerir
#include "Perceptron.h"
#include "SimpleRuleModel.h"
#include "LogisticRegression.h"
#include "SimpleDecisionTree.h"
#include "LinearSVM.h"

// Rastgele sayı üretimi için global bir motoru burada tanımlıyoruz.
// Diğer .cpp dosyalarında 'extern std::mt19937 g;' olarak bildiriliyor.
std::mt19937 g(42); // Sabit seed (42) ile tekrar üretilebilir sonuçlar

int main() {
    std::string dosyaAdi = "kredi_basvurusu_veri_seti.csv";
    std::vector<Basvuru> veriler = veriOku(dosyaAdi); // Veriyi oku

    if (veriler.empty()) {
        std::cerr << "Hata: Veri okunamadi veya dosya bos. Lütfen 'kredi_basvurusu_veri_seti.csv' dosyasının mevcut olduğundan emin olun.\n";
        return 1;
    }

    // Özellik ve hedef vektörlerini hazırla
    std::vector<std::vector<double>> X; // Özellikler
    std::vector<int> y;                 // Hedef değişken (Kredi Onayı)
    for (const auto& b : veriler) {
        X.push_back({
            static_cast<double>(b.yas),
            static_cast<double>(b.gelir),
            static_cast<double>(b.krediSkoru),
            static_cast<double>(evSahibiToInt(b.evSahibi)), // Kategorik özelliği sayısal değere dönüştür
            static_cast<double>(b.calismaSuresi)
        });
        y.push_back(b.krediOnayi);
    }

    // Sınıf dağılımını analiz et
    analyzeClassDistribution(y);

    // Veriyi Eğitim ve Test Kümelerine Ayırma
    std::vector<size_t> indices(X.size());
    std::iota(indices.begin(), indices.end(), 0); // 0'dan N-1'e kadar indeksleri oluştur
    std::shuffle(indices.begin(), indices.end(), g); // İndeksleri karıştır

    double train_ratio = 0.8; // Eğitim kümesi oranı
    size_t train_size = static_cast<size_t>(X.size() * train_ratio); // Eğitim kümesi boyutu

    std::vector<std::vector<double>> X_train, X_test;
    std::vector<int> y_train, y_test;

    // Veriyi eğitim ve test kümelerine ayır
    for (size_t i = 0; i < X.size(); ++i) {
        if (i < train_size) {
            X_train.push_back(X[indices[i]]);
            y_train.push_back(y[indices[i]]);
        } else {
            X_test.push_back(X[indices[i]]);
            y_test.push_back(y[indices[i]]);
        }
    }

    std::cout << "\nVeri Bölümü Boyutları: Eğitim " << X_train.size()
              << " örnek, Test " << X_test.size() << " örnek.\n";

    // Normalizasyon (Eğitim kümesinden öğrenip Test kümesine uygula)
    std::vector<double> train_min_vals, train_max_vals;
    normalizeFeatures(X_train, train_min_vals, train_max_vals); // Eğitim kümesini normalleştir
    applyNormalization(X_test, train_min_vals, train_max_vals); // Test kümesine aynı normalizasyonu uygula

    // --- Model Oluşturma ve Eğitim ---
    // Her bir model için nesneleri oluştur ve eğit

    // Lojistik Regresyon (En iyi bulunan parametrelerle)
    const double BEST_LR = 0.01;
    const int BEST_EPOCHS = 500;
    const double BEST_LAMBDA = 0.01;
    LogisticRegression logreg(X_train[0].size(), BEST_LR, BEST_LAMBDA);
    logreg.train(X_train, y_train, BEST_EPOCHS);

    // Perceptron
    Perceptron perceptron(X_train[0].size(), 0.1);
    perceptron.train(X_train, y_train, 1000);

    // Basit Kural Modeli
    SimpleRuleModel simpleRule; // Bu modelin train metodu yok, direkt kurallarla çalışır

    // Basit Karar Ağacı
    SimpleDecisionTree decisionTree;
    decisionTree.train(X_train, y_train);

    // Doğrusal SVM
    LinearSVM svm(X_train[0].size(), 0.01, 0.001);
    svm.train(X_train, y_train, 1000);

    // --- Model Performansını Değerlendirme ---
    // Her model için performans metriklerini hesapla
    Metrics m_perceptron, m_rule, m_logreg, m_decisionTree, m_svm;

    for (size_t i = 0; i < X_test.size(); i++) {
        // Her modelden tahmin al
        int p_pred = perceptron.predict(X_test[i]);
        int r_pred = simpleRule.predict(X_test[i]);
        int l_pred = logreg.predict(X_test[i]);
        int dt_pred = decisionTree.predict(X_test[i]);
        int svm_pred = svm.predict(X_test[i]);

        // Metrikleri güncelle
        m_perceptron.update(p_pred, y_test[i]);
        m_rule.update(r_pred, y_test[i]);
        m_logreg.update(l_pred, y_test[i]);
        m_decisionTree.update(dt_pred, y_test[i]);
        m_svm.update(svm_pred, y_test[i]);
    }

    std::cout << "\n--- Model Performans Sonuçları (Test Kümesi Üzerinden) ---\n";
    m_perceptron.print("Perceptron");
    m_rule.print("Basit Kural Modeli");
    m_logreg.print("Lojistik Regresyon");
    m_decisionTree.print("Basit Karar Ağacı");
    m_svm.print("Doğrusal SVM");

    return 0;
}