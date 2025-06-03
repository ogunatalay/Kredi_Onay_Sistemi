#ifndef LINEAR_SVM_H
#define LINEAR_SVM_H

#include <vector>
#include <numeric> // std::iota için
#include <random>  // std::normal_distribution, std::shuffle için
#include <algorithm>
// Global random engine'i HelperFunctions.cpp'de tanımlandığı için burada extern olarak bildiriyoruz.
extern std::mt19937 g;

// LinearSVM sınıfı, doğrusal Destek Vektör Makinesi (SVM) algoritmasını uygular.
class LinearSVM {
private:
    std::vector<double> weights; // Modelin ağırlıkları
    double bias;                 // Modelin bias'ı
    double lr;                   // Öğrenme oranı
    double lambda;               // Düzenlileştirme parametresi

    // Karar fonksiyonu değerini hesaplar.
    double decision_function(const std::vector<double>& x) const;

public:
    // Kurucu metot: Özellik sayısı, öğrenme oranı ve düzenlileştirme parametresi ile başlatır.
    LinearSVM(int n_features, double learning_rate = 0.01, double reg_param = 0.01);

    // Tahmin metodu: Verilen girdi için sınıf tahmini yapar (0 veya 1).
    int predict(const std::vector<double>& x) const;

    // Eğitim metodu: Eğitim verisi üzerinde modeli belirtilen epoch sayısı kadar eğitir.
    void train(const std::vector<std::vector<double>>& X, const std::vector<int>& y, int epochs);
};

#endif // LINEAR_SVM_H