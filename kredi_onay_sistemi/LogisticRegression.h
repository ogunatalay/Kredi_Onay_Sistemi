#ifndef LOGISTIC_REGRESSION_H
#define LOGISTIC_REGRESSION_H

#include <vector>
#include <cmath>   // exp için
#include <numeric> // std::iota için
#include <random>  // std::normal_distribution, std::shuffle için
#include <algorithm>
// Global random engine'i HelperFunctions.cpp'de tanımlandığı için burada extern olarak bildiriyoruz.
extern std::mt19937 g;

// LogisticRegression sınıfı, lojistik regresyon algoritmasını uygular.
class LogisticRegression {
private:
    std::vector<double> weights; // Modelin ağırlıkları
    double bias;                 // Modelin bias'ı
    double lr;                   // Öğrenme oranı
    double lambda;               // L2 düzenlileştirme parametresi

    // Sigmoid aktivasyon fonksiyonu.
    double sigmoid(double z);

public:
    // Kurucu metot: Özellik sayısı, öğrenme oranı ve düzenlileştirme parametresi ile başlatır.
    LogisticRegression(int n_features, double learning_rate = 0.01, double reg_param = 0.001);

    // Tahmin metodu: Verilen girdi için sınıf tahmini yapar (0 veya 1).
    int predict(const std::vector<double>& x);

    // Eğitim metodu: Eğitim verisi üzerinde modeli belirtilen epoch sayısı kadar eğitir.
    void train(const std::vector<std::vector<double>>& X, const std::vector<int>& y, int epochs);
};

#endif // LOGISTIC_REGRESSION_H