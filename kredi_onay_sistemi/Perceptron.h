#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <numeric> // std::iota için
#include <random>  // std::shuffle için
#include <algorithm>
// Global random engine'i HelperFunctions.cpp'de tanımlandığı için burada extern olarak bildiriyoruz.
extern std::mt19937 g;

// Perceptron sınıfı, tek katmanlı bir yapay sinir ağı modelidir.
class Perceptron {
private:
    std::vector<double> weights; // Modelin ağırlıkları
    double bias;                 // Modelin bias'ı
    double lr;                   // Öğrenme oranı

public:
    // Kurucu metot: Özellik sayısı ve öğrenme oranı ile Perceptron'ı başlatır.
    Perceptron(int n_features, double learning_rate = 0.01);

    // Tahmin metodu: Verilen girdi için sınıf tahmini yapar (0 veya 1).
    int predict(const std::vector<double>& x);

    // Eğitim metodu: Eğitim verisi üzerinde modeli belirtilen epoch sayısı kadar eğitir.
    void train(const std::vector<std::vector<double>>& X, const std::vector<int>& y, int epochs);
};

#endif // PERCEPTRON_H