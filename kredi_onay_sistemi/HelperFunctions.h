#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream> // std::stringstream için
#include <fstream> // std::ifstream için
#include <cmath>   // INFINITY için
#include <algorithm> // std::count için
#include <iomanip> // std::fixed, std::setprecision için
#include <random>

#include "Basvuru.h" // Basvuru struct'ını kullanabilmek için

// Rastgele sayı üretimi için global bir motor.
// main.cpp'de tanımlanacak veya burada extern olarak belirtilebilir.
extern std::mt19937 g;

// CSV dosyasından kredi başvurularını okur.
std::vector<Basvuru> veriOku(const std::string& dosyaAdi);

// 'E'/'e' (Ev Sahibi) -> 1, 'H'/'h' (Değil) -> 0 dönüşümü yapar.
int evSahibiToInt(char c);

// Min-Max Normalizasyonu uygular.
void normalizeFeatures(std::vector<std::vector<double>>& X,
                       std::vector<double>& min_vals_out,
                       std::vector<double>& max_vals_out);

// Test/doğrulama kümesine normalizasyon uygular.
void applyNormalization(std::vector<std::vector<double>>& X_target,
                        const std::vector<double>& min_vals_source,
                        const std::vector<double>& max_vals_source);

// Sınıf dağılımını analiz eder ve konsola yazdırır.
void analyzeClassDistribution(const std::vector<int>& y);

#endif // HELPER_FUNCTIONS_H