#include <fstream>
#include <iomanip>
#include <Windows.h>
#include <iostream>

#define YUKSEKLIK 20 
#define GENISLIK 63

using namespace std;

typedef enum { ASAGI, SOL, YUKARI, SAG } Yon;


template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(const T& data, Node<T>* next = NULL) {
        this->data = data;
        this->next = next;
    }
};

template <typename T>
class Stack {
private:
    Node<T>* stack_top;

public:
    Stack() {
        stack_top = NULL;
    }
    bool isEmpty() const {
        return stack_top == NULL;
    }
    void push(const T& data) {
        stack_top = new Node<T>(data, stack_top);
    }
    void pop() {
        if (isEmpty()) throw "Stack is Empty";
        Node<T>* temp = stack_top;
        stack_top = stack_top->next;
        delete temp;
    }
    const T& top() const {
        if (isEmpty()) throw "Stack is Empty";
        return stack_top->data;
    }
    void makeEmpty() {
        while (!isEmpty()) pop();
    }
    ~Stack() {
        makeEmpty();
    }
};

class Konum {
    public :
        int x, y;
        Yon yon;
        Konum(int x, int y, Yon yon){
            this->x = x ;
            this->y = y;
            this->yon = yon; 
        }
        Konum(int x, int y) {
            this->x = x;
            this->y = y;
            this->yon = ASAGI;
        }    
        Konum() {
            x = 0;
            y = 0;
            yon = ASAGI;
        }
        Konum AyniYon() {
            switch (yon) {
            case YUKARI:
                return Yukari();
            case SAG:
                return Sag();
            case ASAGI:
                return Asagi();
            default:
                return Sol();
        }
        }
        Konum SaatYonu(Yon yn) {
            switch (yn) {
            case YUKARI:
                return Sag();
            case SAG:
                return Asagi();
            case ASAGI:
                return Sol();
            default:
                return Yukari();
            }
        }
        Konum Asagi() {
            return Konum(x + 1, y, ASAGI);
        }
        Konum Yukari() {
            return Konum(x - 1, y, YUKARI);
        }
        Konum Sol() {
            return Konum(x, y - 1, SOL);
        }
        Konum Sag() {
            return Konum(x, y + 1, SAG);
        }
        Yon TersYon() {
            if (yon == ASAGI) return YUKARI;
            if (yon == YUKARI) return ASAGI;
            if (yon == SOL) return SAG;
            if (yon == SAG) return SOL;
            return YUKARI;
        }
};

class Labirent {
public:
    char harita[YUKSEKLIK][GENISLIK];
    int x, y;
    Yon yon;
    Konum bitis;
    Stack<Konum>* stack;

    Labirent(Konum baslangic, Konum bitis) {
    
        FILE* fp = fopen("Harita.txt", "r");
        unsigned char karakter = 0;
        int yukseklik = 0, genislik = 0;
        x = baslangic.x;
        y = baslangic.y;
        this->bitis = bitis;
        yon = ASAGI;
        stack = new Stack<Konum>();
        stack->push(Konum(-1, -1, yon));
        while (!feof(fp)) {
            
            karakter = getc(fp);
            if (feof(fp)) break;
            if (karakter == '\n') {
                yukseklik++;
                genislik = 0;
            }
            else {
                harita[yukseklik][genislik] = karakter;
                genislik++;
            }
        }
    }
    Konum mevcutKonum() {
        return Konum(x, y, yon);
    }
    bool adimAt(Konum mevcut, Konum ileri) {
        if (!EngelVarmi(ileri)) {
            stack->push(mevcut);
            ayarla(ileri, ileri.yon);
            return true;
        }
        return false;
    }
    void ayarla(Konum konum, Yon yon) {
        
        system("cls");
        this->x = konum.x;
        this->y = konum.y;
        this->yon = yon;
        harita[konum.x][konum.y]= char(219) ;
        cout << yaz();

        Sleep(25);
        
    }
    bool CikisaGeldimi() {
        return x == bitis.x && y == bitis.y ;  
    }
    
    bool EngelVarmi(Konum konum) {
        if (konum.x >= YUKSEKLIK || konum.x < 0 || konum.y >= GENISLIK || konum.y < 0) return false;
        return harita[konum.x][konum.y] == '#' || harita[konum.x][konum.y] == char(219);
    }

    string yaz() {

        char YonChr[] = { 94,60,118,62 };
        stringstream ss;
        ss << setw(10) << "Furkan Duran B210109048 \n" << setw(10) << "LABIRENT COZUCUYE HOSGELDINIZ !" << endl ; 
        for (int yukseklik = 0; yukseklik < YUKSEKLIK; yukseklik++) {
            ss << setw(15);
        
            for (int genislik = 0; genislik < GENISLIK; genislik++) {
                if (yukseklik == x && genislik == y) {
                    ss << YonChr[yon];
                }
                else {
                    if (harita[yukseklik][genislik] == '-') ss << char(254);
                    else ss << harita[yukseklik][genislik];
                }
            }
            ss << endl;
        }
        return ss.str();
    }

};


int main() {

        system("color 30") ; // denemeler yaparken derleme işleminin gerçekleştiğini anlamam için bunu kullandım. çünkü \n
                             // uygulama dosyasını bin klasörü içerisine atmam gerekiyor ve derlenmenin olduğunu net görmek için.
    Labirent* labirent = new Labirent(Konum(0, 2), Konum(19,11));

    labirent->stack->push(Konum(labirent->x, labirent->y, ASAGI));
    labirent->ayarla(Konum(labirent->x, labirent->y, ASAGI).Asagi(), ASAGI);
    while (!labirent->CikisaGeldimi()) {
        int denemeYonSayisi = 1;
        Konum oncekiKonum = labirent->stack->top();
        Konum mevcutKonum = labirent->mevcutKonum();

        Konum ileri = mevcutKonum.AyniYon();

        if (!labirent->adimAt(mevcutKonum, ileri)) {
            int i = 0;
            bool sonuc = false;
            Konum yeni = mevcutKonum;
            while (!sonuc && denemeYonSayisi < 5) {
                yeni = mevcutKonum.SaatYonu((Yon)((mevcutKonum.yon + i) % 4));

                i++;
                denemeYonSayisi++;
                if (yeni.yon == mevcutKonum.TersYon()) {
                    sonuc = false;
                }
                else {
                    sonuc = labirent->adimAt(mevcutKonum, yeni);
                }
            }
            if (denemeYonSayisi == 5) {
                labirent->stack->pop();
                labirent->ayarla(oncekiKonum, oncekiKonum.TersYon());
            }
        }

    }

    system("color 30") ;
    cout << "Cikisa Ulasildi." << endl;
    
    
    return 0;
}
