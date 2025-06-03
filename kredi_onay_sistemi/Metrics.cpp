#include "Metrics.h"

void Metrics::update(int pred, int actual) {
    if (pred == 1 && actual == 1) TP++;
    else if (pred == 0 && actual == 0) TN++;
    else if (pred == 1 && actual == 0) FP++;
    else if (pred == 0 && actual == 1) FN++;
}

double Metrics::accuracy() const {
    int total = TP + TN + FP + FN;
    return (total == 0) ? 0 : (TP + TN) / static_cast<double>(total);
}

double Metrics::precision() const {
    return (TP + FP == 0) ? 0 : TP / static_cast<double>(TP + FP);
}

double Metrics::recall() const {
    return (TP + FN == 0) ? 0 : TP / static_cast<double>(TP + FN);
}

double Metrics::f1_score() const {
    double p = precision();
    double r = recall();
    return (p + r == 0) ? 0 : 2 * (p * r) / (p + r);
}

void Metrics::print(const std::string& modelName) const {
    std::cout << std::fixed << std::setprecision(4);
    std::cout << modelName << " - Doğruluk (Accuracy): " << accuracy() * 100
              << "%, Kesinlik (Precision): " << precision() * 100
              << "%, Hatırlama (Recall): " << recall() * 100
              << "%, F1-Skoru: " << f1_score() * 100 << "%\n";
}