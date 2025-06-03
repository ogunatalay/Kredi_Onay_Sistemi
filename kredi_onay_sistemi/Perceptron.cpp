#include "Perceptron.h"

// Perceptron kurucusu
Perceptron::Perceptron(int n_features, double learning_rate) : lr(learning_rate) {
    weights.resize(n_features, 0.0); // Ağırlıkları sıfırlarla başlat
    bias = 0.0;                       // Bias'ı sıfırla başlat
}

// Perceptron tahmin metodu
int Perceptron::predict(const std::vector<double>& x) {
    double total = bias;
    for (size_t i = 0; i < weights.size(); i++) {
        total += weights[i] * x[i];
    }
    return (total >= 0) ? 1 : 0; // Basamak fonksiyonu aktivasyonu
}

// Perceptron eğitim metodu
void Perceptron::train(const std::vector<std::vector<double>>& X, const std::vector<int>& y, int epochs) {
    for (int e = 0; e < epochs; e++) {
        std::vector<size_t> indices(X.size());
        std::iota(indices.begin(), indices.end(), 0); // İndeksleri 0'dan N-1'e kadar doldur
        std::shuffle(indices.begin(), indices.end(), g); // İndeksleri karıştır

        for (size_t idx : indices) {
            int pred = predict(X[idx]);
            int error = y[idx] - pred; // Hata = Gerçek - Tahmin
            if (error != 0) { // Hata varsa ağırlıkları ve bias'ı güncelle
                for (size_t j = 0; j < weights.size(); j++) {
                    weights[j] += lr * error * X[idx][j];
                }
                bias += lr * error;
            }
        }
    }
}