#include "SimpleRuleModel.h"

// SimpleRuleModel tahmin metodu
int SimpleRuleModel::predict(const std::vector<double>& x) {
    // x[1] = gelir, x[2] = krediSkoru (normalize edilmiş varsayılır)
    // Kural: Kredi skoru 0.7 veya üzeri VE Gelir 0.6 veya üzeri ise onay (1), aksi takdirde red (0).
    return (x[2] >= 0.7 && x[1] >= 0.6) ? 1 : 0;
}