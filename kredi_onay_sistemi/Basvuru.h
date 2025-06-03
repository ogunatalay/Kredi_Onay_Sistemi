#ifndef BASVURU_H
#define BASVURU_H

// Bu struct, kredi başvurularının temel özelliklerini tanımlar.
struct Basvuru {
    int id;
    int yas;
    int gelir;
    int krediSkoru;
    char evSahibi;
    int calismaSuresi;
    int krediOnayi; // Hedef değişken: 1 (Onaylandı), 0 (Onaylanmadı)
};

#endif // BASVURU_H