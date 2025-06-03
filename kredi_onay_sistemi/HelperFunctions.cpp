#include "HelperFunctions.h"
#include <numeric> // std::iota için
#include <random> // std::shuffle için

// Rastgele sayı motorunu HelperFunctions.cpp içinde tanımlıyoruz.
// Alternatif olarak, main.cpp'de tanımlayıp burada extern olarak belirtebiliriz.
// Ancak, her cpp dosyasında birer tane olması durumunda global değişken kullanımı biraz karmaşıklaşabilir.
// En iyisi main.cpp'de tanımlayıp diğer dosyalarda extern kullanmaktır.
// Şimdilik burada tanımlıyoruz, ancak birden fazla tanım hatasına dikkat edilmelidir.
// Basitlik adına şu an için extern kullanıldı, tanımı main.cpp'de olacak.

std::vector<Basvuru> veriOku(const std::string& dosyaAdi) {
    std::vector<Basvuru> basvurular;
    std::ifstream dosya(dosyaAdi);
    if (!dosya.is_open()) {
        std::cerr << "Hata: Dosya acilamadi: " << dosyaAdi << ". Lütfen dosyanın mevcut olduğundan emin olun.\n";
        return basvurular;
    }

    std::string satir;
    std::getline(dosya, satir); // Başlık satırını atla
    while (std::getline(dosya, satir)) {
        std::stringstream ss(satir);
        std::string parca;
        Basvuru b;

        try {
            std::getline(ss, parca, ','); b.id = std::stoi(parca);
            std::getline(ss, parca, ','); b.yas = std::stoi(parca);
            std::getline(ss, parca, ','); b.gelir = std::stoi(parca);
            std::getline(ss, parca, ','); b.krediSkoru = std::stoi(parca);
            std::getline(ss, parca, ','); b.evSahibi = parca.empty() ? 'H' : parca[0];
            std::getline(ss, parca, ','); b.calismaSuresi = std::stoi(parca);
            std::getline(ss, parca, ','); b.krediOnayi = std::stoi(parca);

            basvurular.push_back(b);
        } catch (const std::exception& e) {
            std::cerr << "Hata: Hatali satir atlandi: " << satir << " (" << e.what() << ")\n";
        }
    }
    return basvurular;
}

int evSahibiToInt(char c) {
    return (c == 'E' || c == 'e') ? 1 : 0;
}

void normalizeFeatures(std::vector<std::vector<double>>& X,
                                  std::vector<double>& min_vals_out,
                                  std::vector<double>& max_vals_out) {
    if (X.empty()) return;

    size_t num_features = X[0].size();
    min_vals_out.assign(num_features, INFINITY);
    max_vals_out.assign(num_features, -INFINITY);

    // Min ve max değerleri bul
    for (const auto& row : X) {
        for (size_t i = 0; i < num_features; i++) {
            if (row[i] > max_vals_out[i]) max_vals_out[i] = row[i];
            if (row[i] < min_vals_out[i]) min_vals_out[i] = row[i];
        }
    }

    // Normalizasyon uygula
    for (auto& row : X) {
        for (size_t i = 0; i < num_features; i++) {
            if (max_vals_out[i] != min_vals_out[i]) {
                row[i] = (row[i] - min_vals_out[i]) / (max_vals_out[i] - min_vals_out[i]);
            } else {
                row[i] = 0.5; // Tüm değerler aynıysa 0.5'e ayarla
            }
        }
    }
}

void applyNormalization(std::vector<std::vector<double>>& X_target,
                                   const std::vector<double>& min_vals_source,
                                   const std::vector<double>& max_vals_source) {
    if (X_target.empty() || min_vals_source.empty() || max_vals_source.empty()) return;

    size_t num_features = X_target[0].size();
    for (auto& row : X_target) {
        for (size_t i = 0; i < num_features; i++) {
            if (max_vals_source[i] != min_vals_source[i]) {
                row[i] = (row[i] - min_vals_source[i]) / (max_vals_source[i] - min_vals_source[i]);
            } else {
                row[i] = 0.5; // Eğitim kümesinde sabit olan bir özellik için 0.5'e ayarla
            }
        }
    }
}

void analyzeClassDistribution(const std::vector<int>& y) {
    int positive = std::count(y.begin(), y.end(), 1);
    int total = y.size();
    std::cout << "Sınıf Dağılımı: " << positive << " pozitif, "
              << (total - positive) << " negatif ("
              << std::fixed << std::setprecision(1)
              << (static_cast<double>(positive)/total * 100) << "%)\n";
}