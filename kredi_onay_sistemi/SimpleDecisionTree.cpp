#include "SimpleDecisionTree.h"

// SimpleDecisionTree eğitim metodu
void SimpleDecisionTree::train(const std::vector<std::vector<double>>& X_train, const std::vector<int>& y_train) {
    // Kredi Skoru (index 2) ve sabit bir eşik üzerinde kural oluşturulur.
    feature_idx = 2; // Özellik: Kredi Skoru (normalleştirilmiş hali)
    threshold = 0.5; // Eşik değeri

    int left_pos = 0, left_neg = 0;   // Eşiğin altındaki pozitif/negatif örnek sayıları
    int right_pos = 0, right_neg = 0; // Eşiğin üstündeki pozitif/negatif örnek sayıları

    // Eğitim verisi üzerinde her örneği kontrol et
    for (size_t i = 0; i < X_train.size(); ++i) {
        if (X_train[i][feature_idx] < threshold) {
            // Eşiğin sol tarafı
            if (y_train[i] == 1) left_pos++;
            else left_neg++;
        } else {
            // Eşiğin sağ tarafı
            if (y_train[i] == 1) right_pos++;
            else right_neg++;
        }
    }

    // Sol ve sağ dallar için çoğunluk sınıfını belirle
    left_class = (left_pos >= left_neg) ? 1 : 0;
    right_class = (right_pos >= right_neg) ? 1 : 0;
}

// SimpleDecisionTree tahmin metodu
int SimpleDecisionTree::predict(const std::vector<double>& x) const {
    // Özellik değerini eşikle karşılaştır ve ilgili sınıfı döndür.
    if (x[feature_idx] < threshold) {
        return left_class;
    } else {
        return right_class;
    }
}