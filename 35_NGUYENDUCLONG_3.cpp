//Nguyen Duc Long 35
#include <bits/stdc++.h>

using namespace std;

class SINHVIEN {
    protected:
        int msv;
        string ho_ten;
        float diemKH;
    public:
        static int soSV;
        static float tongDiem;
        SINHVIEN() {
            ++soSV;
        }
        void nhap() {
            cout << "\nNhap ma sinh vien: "; cin >> msv;
            cout << "\nNhap ho va ten sinh vien: ";
            cin.ignore(); getline(cin, ho_ten);
        }

        friend bool operator < (SINHVIEN a, SINHVIEN b) {
            if(a.diemKH < b.diemKH) return true;
            else return false;
        }

        void In(){
            cout << "|" << setw(13) << msv << "|" << setw(20) << ho_ten << "|" << setw(12) << diemKH << "|";
        }

        ~SINHVIEN() {
            --soSV;
            cout << "Da xoa sinh vien!";
        }
};
int SINHVIEN::soSV = 0;
float SINHVIEN::tongDiem = 0;


class SV_viet_bao: virtual public SINHVIEN {
    int so_bai_bao;
    float gio_bai_bao;
    public:
        void nhap_bao(){
            cout << "\nNhap so bai bao: "; cin >> so_bai_bao;
            cout <<"\nNhap gio bai bao: "; cin >> gio_bai_bao;
            diemKH = so_bai_bao * gio_bai_bao;
            tongDiem += diemKH;
        }
};

class SV_viet_detai: virtual public SINHVIEN {
    int so_detai;
    float so_gio, muc_gio;
    public:
        void nhap_detai(){
            cout << "\nNhap so de tai: "; cin >> so_detai;
            cout << "\nNhap so gio: "; cin >> so_gio;
            cout << "\nNhap muc gio: "; cin >> muc_gio;
            diemKH = so_detai * so_gio * muc_gio;
            tongDiem += diemKH;
        }
};

class LOPHOC: public SV_viet_bao, public SV_viet_detai {
    public:
        LOPHOC *next;
        void nhapDL(){
            nhap();
            int tmp;
            cout << "Sinh vien thuc hien (1: viet bao, 2: de tai): "; cin >> tmp;
            if(tmp == 1)
                nhap_bao();
            else if(tmp == 2) 
                nhap_detai();
        }

        void in(LOPHOC *list){
            int cnt = 1;
            cout << endl << "=========================================================";
            cout << endl << "|  STT  |     MSV     |       Ten SV       |   Diem KH  |";
            cout << endl << "=========================================================";
            for(list; list != NULL; list = list ->next) {
                cout << endl << "|" << setw(7) << cnt; ++cnt;
                list->In();
            }
            cout << endl << "=========================================================";
        }

        void sapxep(LOPHOC *list) {
            for(list; list->next != NULL; list = list->next) {
                for(LOPHOC *tmp = list->next; tmp != NULL; tmp = tmp->next) {
                    if(list->diemKH > tmp->diemKH) 
                        continue;
                    else {
                        swap(list->diemKH, tmp->diemKH);
                        swap(list->ho_ten, tmp->ho_ten);
                        swap(list->msv, tmp->msv);
                    }
                }
            }
        }
        float diemTB() {
            float res = tongDiem / soSV;
            return res;
        }
};
//Sao ngay xua minh cham vay
int main() {
    LOPHOC *list = NULL, *last = NULL, *node = NULL;
    int tiep = 1;
    while(tiep == 1) {
        node = new LOPHOC;
        node->nhapDL();
        node->next = NULL;
        if(list == NULL) {
            list = node;
            last = node;
        }
        else {
            last->next = node;
            last = node;
        }
        cout << "\nCo nhap tiep hay khong (1: co, 2: khong): "; 
        cin >> tiep;
    }
    node->sapxep(list);
    node->in(list);
    cout << "\nDiem trung binh cua sinh vien la: " << fixed << setprecision(2) <<node->diemTB();
}
