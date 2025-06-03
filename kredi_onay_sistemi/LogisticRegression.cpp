#include "LogisticRegression.h"

// Sigmoid aktivasyon fonksiyonu
double LogisticRegression::sigmoid(double z) {
    if (z > 30.0) return 1.0;  // Büyük pozitif değerler için taşmayı önle
    if (z < -30.0) return 0.0; // Büyük negatif değerler için taşmayı önle
    return 1.0 / (1.0 + exp(-z));
}

// LogisticRegression kurucusu
LogisticRegression::LogisticRegression(int n_features, double learning_rate, double reg_param)
    : lr(learning_rate), lambda(reg_param) {
    weights.resize(n_features);
    std::normal_distribution<> d(0, 0.01); // Ağırlıkları küçük rastgele değerlerle başlat
    for(int i = 0; i < n_features; ++i) {
        weights[i] = d(g);
    }
    bias = 0.0; // Bias'ı sıfırla başlat
}

// LogisticRegression tahmin metodu
int LogisticRegression::predict(const std::vector<double>& x) {
    double z = bias;
    for (size_t i = 0; i < weights.size(); i++) {
        z += weights[i] * x[i];
    }
    double prob = sigmoid(z);
    return (prob >= 0.5) ? 1 : 0; // Olasılığa göre sınıf tahmini
}

// LogisticRegression eğitim metodu
void LogisticRegression::train(const std::vector<std::vector<double>>& X, const std::vector<int>& y, int epochs) {
    for (int e = 0; e < epochs; e++) {
        std::vector<size_t> indices(X.size());
        std::iota(indices.begin(), indices.end(), 0);
        std::shuffle(indices.begin(), indices.end(), g);

        for (size_t idx : indices) {
            double z = bias;
            for (size_t j = 0; j < weights.size(); j++) {
                z += weights[j] * X[idx][j];
            }
            double pred_prob = sigmoid(z);
            double error = y[idx] - pred_prob; // Hata = Gerçek - Tahmin Edilen Olasılık

            for (size_t j = 0; j < weights.size(); j++) {
                // Ağırlık güncelleme (L2 düzenlileştirme ile)
                weights[j] += lr * (error * X[idx][j] - lambda * weights[j]);
            }
            bias += lr * error; // Bias güncelleme
        }
    }
}