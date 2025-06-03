#ifndef SIMPLE_DECISION_TREE_H
#define SIMPLE_DECISION_TREE_H

#include <vector>

// SimpleDecisionTree sınıfı, çok basit bir karar ağacı uygular (tek bölünmeli).
class SimpleDecisionTree {
private:
    int feature_idx;   // Karar için kullanılan özelliğin indeksi
    double threshold;  // Bölünme için kullanılan eşik değeri
    int left_class;    // Eşiğin altındaki örnekler için tahmin edilen sınıf
    int right_class;   // Eşiğin üstündeki örnekler için tahmin edilen sınıf

public:
    // Eğitim metodu: Eğitim verisi üzerinde karar ağacını (basit kuralı) öğrenir.
    void train(const std::vector<std::vector<double>>& X_train, const std::vector<int>& y_train);

    // Tahmin metodu: Verilen girdi için sınıf tahmini yapar (0 veya 1).
    int predict(const std::vector<double>& x) const;
};

#endif // SIMPLE_DECISION_TREE_H