#include "LinearSVM.h"

// LinearSVM kurucusu
LinearSVM::LinearSVM(int n_features, double learning_rate, double reg_param)
    : lr(learning_rate), lambda(reg_param) {
    weights.resize(n_features);
    std::normal_distribution<> d(0, 0.01); // Ağırlıkları küçük rastgele değerlerle başlat
    for(int i = 0; i < n_features; ++i) {
        weights[i] = d(g);
    }
    bias = 0.0; // Bias'ı sıfırla başlat
}

// Karar fonksiyonu hesaplama
double LinearSVM::decision_function(const std::vector<double>& x) const {
    double val = bias;
    for (size_t i = 0; i < weights.size(); ++i) {
        val += weights[i] * x[i];
    }
    return val;
}

// LinearSVM tahmin metodu
int LinearSVM::predict(const std::vector<double>& x) const {
    return (decision_function(x) >= 0) ? 1 : 0; // Karar fonksiyonu sonucuna göre sınıf tahmini
}

// LinearSVM eğitim metodu
void LinearSVM::train(const std::vector<std::vector<double>>& X, const std::vector<int>& y, int epochs) {
    for (int e = 0; e < epochs; ++e) {
        std::vector<size_t> indices(X.size());
        std::iota(indices.begin(), indices.end(), 0);
        std::shuffle(indices.begin(), indices.end(), g);

        for (size_t idx : indices) {
            // SVM'de hedef genellikle -1 ve 1 olarak kullanılır
            int target_y = (y[idx] == 1) ? 1 : -1;
            double current_decision_val = decision_function(X[idx]);

            if (target_y * current_decision_val < 1) { // Menteşe kaybı koşulu
                for (size_t j = 0; j < weights.size(); ++j) {
                    // Ağırlık güncelleme (hata ve düzenlileştirme ile)
                    weights[j] += lr * (target_y * X[idx][j] - lambda * weights[j]);
                }
                bias += lr * target_y; // Bias güncelleme
            } else {
                // Sadece düzenlileştirme terimi uygulanır (doğru sınıflandırılmış ve marjın dışında)
                for (size_t j = 0; j < weights.size(); ++j) {
                    weights[j] -= lr * lambda * weights[j];
                }
            }
        }
    }
}