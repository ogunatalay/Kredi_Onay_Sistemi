#ifndef SIMPLE_RULE_MODEL_H
#define SIMPLE_RULE_MODEL_H

#include <vector>

// SimpleRuleModel sınıfı, önceden tanımlanmış basit kurallara göre tahmin yapar.
class SimpleRuleModel {
public:
    // Tahmin metodu: Belirli özellik değerlerine göre sınıf tahmini yapar.
    // X vektöründe özelliklerin belirli indekslerde olduğunu varsayar
    // (örn. x[1] gelir, x[2] krediSkoru).
    int predict(const std::vector<double>& x);
};

#endif // SIMPLE_RULE_MODEL_H