# Yığın Kullanarak Labirent Çözme - C++

Bu proje, C++ dilinde bir yığın (stack) veri yapısını kullanarak labirent çözme algoritmasını uygular. Labirent bir `.txt` dosyası ile temsil edilir ve program, labirentte gezinerek çıkışı bulur ve alınan adımları görselleştirir.

## Özellikler

- **Node Sınıfı**: Bağlı liste yapısını uygular, veriyi saklar ve bir sonraki düğüme işaret eder.
- **Stack Sınıfı**: LIFO (Last In, First Out) prensibini izleyen bir yığın veri yapısı, labirentteki konumları izlemek ve geri dönmek için kullanılır.
- **Konum ve Yön Yapıları**:
  - Labirent içerisindeki konumları ve yönleri (YUKARI, AŞAĞI, SOL, SAĞ) temsil eder.
  - Belirli yönlerde hareket etmek ve köşe durumlarını yönetmek için fonksiyonlar içerir.
- **Labirent Sınıfı**: Labirent düzenini yönetir ve çözüm sürecini gerçekleştirir. Şunları içerir:
  - `.txt` dosyasından labirenti yükleme.
  - Yığın işlemlerini kullanarak labirentte gezinme.
  - Labirenti ve yapılan adımları ekranda görselleştirme.

## Kullanım

1. **Proje Yapısı**:
   - `Node`, `Stack`, `Konum` ve `Labirent` sınıflarını içeren kaynak dosyalarını düzenleyin.
   - Proje yapısı ve bağımlılıklarını yönetmek için bir `Makefile` oluşturun.

2. **Labirenti Çözme**:
   - Labirent başlangıç ve bitiş konumlarını belirleyin.
   - Program, başlangıç konumundan çıkışa kadar adımları takip eder ve her adımı ekranda gösterir.

3. **Çalıştırma**:
   - Projeyi derlemek ve çalıştırmak için terminalde `mingw32-make` komutunu kullanın.

## Kaynaklar

- Ders notları
- ChatGPT
- [Gökhan Şengün - Makefile ve Make Nedir? Ne İşe Yarar?](https://gokhansengun.com/makefile-ve-make-nedir-ne-ise-yarar/)
- YouTube:
  - [Video 1](https://www.youtube.com/watch?v=mTdhPXfsU8c)
  - [Video 2](https://youtu.be/SGqmFMm9eEo?si=I7b6WcMXpLCNjTeP)
