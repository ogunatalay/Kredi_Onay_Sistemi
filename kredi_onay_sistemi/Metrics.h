#ifndef METRICS_H
#define METRICS_H

#include <string>
#include <iostream>
#include <iomanip> // std::fixed, std::setprecision için

// Metrics struct'ı, sınıflandırma modellerinin performans metriklerini hesaplar ve saklar.
struct Metrics {
    int TP = 0, TN = 0, FP = 0, FN = 0;

    // Tahmin ve gerçek değere göre sayaçları günceller.
    void update(int pred, int actual);

    // Doğruluk (Accuracy) oranını hesaplar.
    double accuracy() const;

    // Kesinlik (Precision) oranını hesaplar.
    double precision() const;

    // Hatırlama (Recall) oranını hesaplar.
    double recall() const;

    // F1-Skoru'nu hesaplar.
    double f1_score() const;

    // Metrikleri konsola yazdırır.
    void print(const std::string& modelName) const;
};

#endif // METRICS_H