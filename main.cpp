#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>

using namespace std;
const int SO_KHOA = 6;
const int SO_LOP_TRONG_KHOA = 3;

class Person {
protected:
    string id;
    string hoTen;
    string boPhan;
    int namSinh;
    string gioiTinh;
    string diaChi;
    string soDienThoai;

public:
    Person(const string& id, const string& ten, const string& bp, int ns, const string& gt, const string& dc, const string& sdt)
        : id(id), hoTen(ten), boPhan(bp), namSinh(ns), gioiTinh(gt), diaChi(dc), soDienThoai(sdt) {}

    virtual bool xetKhenThuong() const = 0;
    virtual void hienThi() const = 0;
    virtual void capNhatThongTin() = 0;

    virtual ~Person() {}

    void xuatFile(ofstream& file) {
    }

    string getId () const {
        return id;
    }
    string getHoTen () const {
        return hoTen;
    }
    string getBoPhan () const {
        return boPhan;
    }


    bool kiemtrasodienthoai(const string& sdt) {
    if (sdt.length() != 10) {
        return false;
    }
    for (char ch : sdt) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}
    bool kiemtragioitinh(const string& gt) {
    if (gt != "Nam" && gt != "Nu") {
        return false;
    }
    return true;
}
    bool kiemtradiachi(const string& dc) {
    if (dc.empty()) {
        return false;
    }
    return true;
}

    bool kiem_tra_ho_ten(const string& hoten) {
    if (hoten.empty()) {
        return false;
    }

    regex pattern("^[a-zA-ZÀÁÂÃÈÉÊÌÍÒÓÔÕÙÚĂĐĨŨƠàáâãèéêìíòóôõùúăđĩũơĂÂÊÔ ]+$");
    if (!regex_match(hoten, pattern)) {
        return false;
    }

    string trimmed_hoten;
    bool space_detected = false;
    for (char ch : hoten) {
        if (ch != ' ') {
            if (space_detected) {
                trimmed_hoten += ' ';
                space_detected = false;
            }
            trimmed_hoten += ch;
        } else if (!trimmed_hoten.empty()) {
            space_detected = true;
        }
    }

    return trimmed_hoten == hoten;
    }

bool kiemTraNamSinh(int namSinh) {
    if (namSinh < 1950) {
        cout << "Nam sinh khong the nho hon 1950!" << endl;
        return false;
    }
    if (namSinh > 2010) {
        cout << "Nam sinh khong the lon hon nam 2010!" << endl;
        return false;
    }
    return true;
}
};

class SinhVien : public Person {
private:
    float diemTBC;
    float diemRenLuyen;
    int soTinChi;
    string chuyenNganh;
    string truong;

public:
    SinhVien(const string& id, const string& ten, const string& bp, int ns, const string& gt, const string& dc, const string& sdt,
             float dtbc, float drl, int stc, const string& cn, const string& trg)
        : Person(id, ten, bp, ns, gt, dc, sdt), diemTBC(dtbc), diemRenLuyen(drl), soTinChi(stc), chuyenNganh(cn), truong(trg) {}

    bool xetKhenThuong() const override {
        return diemTBC >= 8.0 && diemRenLuyen >= 85;
    }

    void hienThi() const override {
        cout << id << setw(15) << hoTen << setw(10)<< boPhan  << setw(10)<< namSinh << setw(10)
             << gioiTinh << setw(10)<< diemTBC << setw(10)<< diemRenLuyen << setw(10)
             << soTinChi << setw(10)<< chuyenNganh <<setw(20)<<truong<< endl;
    }
    float getDiemTBC () const {
        return diemTBC;
    }
    float getDiemRenLuyen () const {
        return diemRenLuyen;
    }
    int getsoTinChi() const{
        return soTinChi;
    }
    string getChuyenNganh () const {
        return chuyenNganh;
    }

    void capNhatThongTin() override {
    int choice2;
    do {
        cout << "\n--- Cap nhat thong tin Sinh vien ---\n";
        cout << "1. Ten\n";
        cout << "2. Chuyen nganh/Lop\n";
        cout << "3. Nam sinh\n";
        cout << "0. Thoát cập nhật\n";
        cout << "Chọn thông tin cần cập nhật (0-4): ";
        cin >> choice2;
        cin.ignore();
        switch (choice2) {
            case 1:
                cout << "Nhap ten moi: ";
                getline(cin, hoTen);
                if (!kiem_tra_ho_ten(hoTen)) {
                    cout << "Ten khong hop le!" << endl;
                    continue;
                }
                break;
            case 2:
                cout << "Nhap chuyen nganh moi: ";
                cout<<"Danh sach chuyen nganh: "<<endl;
                cout<<"1.CNTT"<<endl;
                cout<<"2.CNSH"<<endl;
                cout<<"3.CDT"<<endl;
                cout<<"4.CK"<<endl;
                cout<<"5.TDH"<<endl;
                cout<<"6.D"<<endl;
                cout<<"Nhap chuyen nganh can chon(1-6): ";
                int choice3;
                cin>>choice3;
                cin.ignore();
                switch (choice3)
                {
                case 1:
                    chuyenNganh = "CNTT";
                    cout<<"Danh sach lop thuoc khoa CNTT"<<endl;
                    cout<<"1.IT1"<<endl;
                    cout<<"2.IT2"<<endl;
                    cout<<"3.IT3"<<endl;
                    cout<<"Nhap lop can chon(1-3): ";
                    int choice4;
                    cin>>choice4;
                    cin.ignore();
                    switch (choice4)
                    {
                    case 1:
                        truong = "IT1";
                        break;
                    case 2:
                        truong = "IT2";
                        break;
                    case 3: 
                        truong = "IT3";
                        break;
                    default:
                        cout << "Lua chon khong hop le! Vui long chon lai.\n";
                        break;
                    }
                    break;
                case 2:
                    chuyenNganh = "CNSH";
                    cout<<"Danh sach lop thuoc khoa CNSH"<<endl;
                    cout<<"1.SH1"<<endl;
                    cout<<"2.SH2"<<endl;
                    cout<<"Nhap lop can chon(1-2): ";
                    int choice5;
                    cin>>choice5;
                    cin.ignore();
                    switch (choice5)
                    {
                    case 1:
                        truong = "SH1";
                        break;
                    case 2:
                        truong = "SH2";
                        break;
                    default:
                        cout << "Lua chon khong hop le! Vui long chon lai.\n";
                        break;
                    }
                    break;
                case 3:
                    chuyenNganh = "CDT";
                    cout<<"Danh sach lop thuoc khoa CDT"<<endl;
                    cout<<"1.CDT1"<<endl;
                    cout<<"2.CDT2"<<endl;
                    cout<<"3.CDT3"<<endl;
                    cout<<"Nhap lop can chon(1-3): ";
                    int choice6;
                    cin>>choice6;
                    cin.ignore();
                    switch (choice6)
                    {
                    case 1:
                        truong = "CDT1";
                        break;
                    case 2:
                        truong = "CDT2";
                        break;
                    case 3:
                        truong = "CDT3";
                        break;
                    default:
                        cout << "Lua chon khong hop le! Vui long chon lai.\n";
                        break;
                    }
                    break;
                case 4:
                    chuyenNganh = "CK";
                    cout<<"Danh sach lop thuoc khoa CK"<<endl;
                    cout<<"1.CK1"<<endl;
                    cout<<"2.CK2"<<endl;
                    cout<<"3.CK3"<<endl;
                    cout<<"Nhap lop can chon(1-3): ";
                    int choice7;
                    cin>>choice7;
                    cin.ignore();
                    switch (choice7)
                    {
                    case 1:
                        truong = "CK1";
                        break;
                    case 2:
                        truong = "CK2";
                        break;
                    case 3:
                        truong = "CK3";
                        break;
                    default:
                        cout << "Lua chon khong hop le! Vui long chon lai.\n";
                        break;
                    }
                    break;
                case 5: 
                    chuyenNganh = "TDH";
                    cout<<"Danh sach lop thuoc khoa TDH"<<endl;
                    cout<<"1.TDH1"<<endl;
                    cout<<"2.TDH2"<<endl;
                    cout<<"Nhap lop can chon(1-2): ";
                    int choice8;
                    cin>>choice8;
                    cin.ignore();
                    switch (choice8)
                    {
                    case 1:
                        truong = "TDH1";
                        break;
                    case 2:
                        truong = "TDH2";
                        break;
                    default:
                        cout << "Lua chon khong hop le! Vui long chon lai.\n";
                        break;
                    }
                    break;
                case 6: 
                    chuyenNganh = "Khoa D";
                    cout<<"Danh sach lop thuoc khoa Khoa D"<<endl;
                    cout<<"1.D1"<<endl;
                    cout<<"2.D2"<<endl;
                    cout<<"Nhap lop can chon(1-2): ";
                    int choice9;
                    cin>>choice9;
                    cin.ignore();
                    switch (choice9)
                    {
                    case 1:
                        truong = "D1";
                        break;
                    case 2:
                        truong = "D2";
                        break;
                    default:
                        cout << "Lua chon khong hop le! Vui long chon lai.\n";
                        break;
                    }
                    break;
                default:
                    cout << "Lua chon khong hop le! Vui long chon lai.\n";
                    break;
                }
                break;
            case 3:
                cout << "Nhap nam sinh moi: ";
                cin >> namSinh;
                cin.ignore();
                if (!kiemTraNamSinh(namSinh)) {
                    cout << "Nam sinh khong hop le!" << endl;
                    continue;
                }
                break;
            case 0:
                cout << "Thoat cap nhat thong tin.\n";
                break;
            default:
                cout << "Lua chon khong hop le! Vui long chon lai.\n";
        }
    } while (choice2 != 0);
    }

};


class GiangVien : public Person {
private:
    string khoa;
    string viTri;
    string thanhTuu;
    int soNamGiangDay;
    string hocVi;
    int soLuongCongTrinh;
    string truongBoMon;
    float diemGiangDay;
    float diemNghienCuu;

public:
    GiangVien(const string& id, const string& ten, const string& bp, int ns, const string& gt, const string& dc, const string& sdt,
              const string& k, const string& vt, const string& tt, int sny, const string& hv, int slct, const string& tbm, float dgd, float dnc)
        : Person(id, ten, bp, ns, gt, dc, sdt), khoa(k), viTri(vt), thanhTuu(tt), soNamGiangDay(sny), hocVi(hv), soLuongCongTrinh(slct), truongBoMon(tbm),diemGiangDay(dgd), diemNghienCuu(dnc) {}


    bool xetKhenThuong() const override {
        return soLuongCongTrinh >= 2;
    }

    string getHocVi () const {
        return hocVi;
    }

    void hienThi() const override {
        cout << id << setw(15) << hoTen << setw(10)<< boPhan  << setw(10)<< namSinh << setw(10)
             << gioiTinh << setw(20)<< viTri << setw(15)
             << soNamGiangDay << setw(15)<< hocVi << setw(10)<< soLuongCongTrinh << setw(15)<< truongBoMon <<endl;
    }

    int getSoNamGiangDay () {
        return soNamGiangDay;
    }

    int getSoLuongCongTrinh () {
        return soLuongCongTrinh;
    }
   
    float getDiemGiangDay() const {
        return diemGiangDay;
    }

    float getDiemNghienCuu() const {
        return diemNghienCuu;
    }

    string getKhoa() const {
         return khoa;
    }
   
    void capNhatThongTin() override {
    int choice3;
    do {
        cout << "\n--- Cap nhat thong tin giang vien ---\n";
        cout << "1. Ten\n";
        cout << "2. Nam sinh\n";
        cout << "3. Khoa\n";
        cout << "4. Vi tri\n";
        cout << "5. Thanh tuu\n";
        cout << "0. Thoat cap nhat\n";
        cout << "Chon thong tin can cap nhat (0-5): ";
        cin >> choice3;
        cin.ignore();
        switch (choice3) {
            case 1:
                cout << "Nhap ten moi: ";
                getline(cin, hoTen);
                if (!kiem_tra_ho_ten(hoTen)) {
                    cout << "Ten khong hop le!" << endl;
                    continue;
                }
                break;
            case 2:
                cout << "Nhap nam sinh moi: ";
                cin >> namSinh;
                cin.ignore();
                if (!kiemTraNamSinh(namSinh)) {
                    cout << "Nam sinh khong hop le!" << endl;
                    continue;
                }
                break;
            case 3:
                cout << "Nhap khoa moi:\n";
                cout << "1. Khoa CNTT\n";
                cout << "2. Khoa CNSH\n";
                cout << "3. Khoa CDT\n";
                cout << "4. KHoa CK\n";
                cout << "5. KHoa TDH\n";
                cout<<"Chon khoa can chon(1-5): ";
                int choice4;
                cin >> choice4;
                cin.ignore();
                switch (choice4) {
                    case 1:
                        khoa = "Khoa CNTT";
                        break;
                    case 2:
                        khoa = "Khoa CNSH";
                        break;
                    case 3:
                        khoa = "Khoa CDT";
                        break;
                    case 4:
                        khoa = "Khoa CK";
                        break;
                    case 5:
                        khoa = "Khoa TDH";
                        break;
                    default:
                        cout << "Lua chon khong hop le! Vui long chon lai.\n";
                        break;
                }
                getline(cin, khoa);
                break;
            case 4:
                cout << "Nhap vi tri moi(GVC/GVCC/GVTG/TG): ";
                getline(cin, viTri);
                if (viTri != "GVC" && viTri != "GVCC" && viTri != "GVTG" && viTri != "TG") {
                    cout << "Vi tri khong hop le!" << endl;
                    continue;
                }
                break;
            case 5:
                cout << "Nhap thanh tuu moi: ";
                getline(cin, thanhTuu);
                break;
            case 0:
                cout << "Thoat cap nhat thong tin.\n";
                break;
            default:
                cout << "Lựa chọn không hợp lệ! Vui lòng chọn lại.\n";
        }
    } while (choice3 != 0);
}
};

class QuanLy : public Person {
private:
    string viTri;
    string noLuc;
    int soNamCongTac;
    string phongBan;
    string trinhDo;
    int soLuongDuAn;

public:
    QuanLy(const string& id, const string& ten, const string& bp, int ns, const string& gt, const string& dc, const string& sdt,
           const string& vt, const string& nl, int snct, const string& pb, const string& td, int slda)
        : Person(id, ten, bp, ns, gt, dc, sdt), viTri(vt), noLuc(nl), soNamCongTac(snct), phongBan(pb), trinhDo(td), soLuongDuAn(slda) {}

    bool xetKhenThuong() const override {
        return soLuongDuAn >= 3 && soNamCongTac >= 10;
    }
    string getViTri () const {
        return viTri;
    }
    string getPhongBan () const {
        return phongBan;
    }

    string getNoLuc () const {
        return noLuc;
    }

    int getSoLuongDuAn () const {
        return soLuongDuAn;
    }

    void hienThi() const override {
        cout << id << setw(20) << hoTen << setw(30)<< boPhan  << setw(7)<< namSinh << setw(7)
        << gioiTinh << setw(20)<< viTri << setw(10)<< noLuc << setw(10)
        << soNamCongTac << setw(30)<< phongBan << setw(15)<< trinhDo << setw(5)<< soLuongDuAn << endl;
    }
    void capNhatThongTin() override {
    int choice4;
    do {
        cout << "\n--- Cap nhat thông tin Quan Ly---\n";
        cout << "1. Ten\n";
        cout << "2. Nam sinh\n";
        cout << "3. Phong Ban\n";
        cout << "4. Vi tri\n";
        cout << "5. Trinh Đo\n";
        cout << "0. Thoat cap nhat\n";
        cout << "Chon thong tin can cap nhat (0-5): ";
        cin >> choice4;
        cin.ignore();
        switch (choice4) {
            case 1:
                cout << "Nhap ten moi: ";
                getline(cin, hoTen);
                if (!kiem_tra_ho_ten(hoTen)) {
                    cout << "Ten khong hop le!" << endl;
                    continue;
                }
                break;
            case 2:
                cout << "Nhap nam sinh moi: ";
                cin >> namSinh;
                cin.ignore();
                if (!kiemTraNamSinh(namSinh)) {
                    cout << "Nam sinh khong hop le!" << endl;
                    continue;
                }
                break;
            case 3:
                cout << "Nhap phong ban moi\n";
                cout<<"Danh sach phong ban: "<<endl;
                cout<<"1.Phong cong tac sinh vien"<<endl;
                cout<<"2.Phong dao tao"<<endl;
                cout<<"3.Phong tai chinh"<<endl;
                cout<<"4.Phong to chuc - hanh chinh"<<endl;
                cout<<"Chon phong ban can chon(1-4): ";
                int choice5;
                cin>>choice5;
                cin.ignore();
                switch (choice5)
                {
                case 1:
                    phongBan = "Phong cong tac sinh vien";
                    break;
                case 2:
                    phongBan = "Phong dao tao";
                    break;
                case 3:
                    phongBan = "Phong tai chinh";
                    break;
                case 4: 
                    phongBan = "Phong to chuc - hanh chinh";
                    break;
                default:    
                    cout << "Lua chon khong hop le! Vui long chon lai.\n";
                    break;
                }
                break;
            case 4:
                cout << "Nhap vi tri moi(Truong phong/Pho phong/Chuyen vien): ";
                getline(cin, viTri);
                if (viTri != "Truong phong" && viTri != "Pho phong" && viTri != "Chuyen vien") {
                    cout << "Vi tri khong hop le!" << endl;
                    continue;
                }
                break;
            case 5:
                cout << "Nhap trinh do moi(Tien si/ Thac si/ Cu nhan): ";
                getline(cin, trinhDo);
                if (trinhDo != "Tien si" && trinhDo != "Thac si" && trinhDo != "Cu nhan") {
                    cout << "Trinh do khong hop le!" << endl;
                    continue;
                }
                break;
            case 0:
                cout << "Thoat cap nhat thong tin.\n";
                break;
            default:
                cout << "Lua chon khong hop le! Vui long chon lai.\n";
        }
    } while (choice4 != 0);
}
};


int kiemTraLoaiNguoi(const string& id) {
    regex mauSinhVien("^SV\\d{3}$");
    regex mauGiangVien("^GV\\d{3}$");
    regex mauQuanLy("^QL\\d{3}$");
    if (regex_match(id, mauSinhVien)) {
        return 1;
    } else if (regex_match(id, mauGiangVien)) {
        return 2;
    } else if (regex_match(id, mauQuanLy)) {
        return 3;
    }
    else {
        return 0;
    }
}


void docDuLieuTuFile(const string& tenFile, vector<Person*>& danhSach, int loaiNguoi) {
    ifstream file(tenFile);
    if (!file.is_open()) {
        cout << "Khong the mo file " << tenFile << endl;
        return;
    }
    Person* p;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, hoTen, boPhan, gioiTinh, diaChi, soDienThoai;
        int namSinh;
        getline(ss, id, '|');
        if(kiemTraLoaiNguoi(id) == 0){
            cout << "ID khong hop le!" << endl;
            break;
        }
        getline(ss, hoTen, '|');
        getline(ss, boPhan, '|');
        ss >> namSinh;
        ss.ignore();
        if(!p->kiemTraNamSinh(namSinh)){
            cout << "Nam sinh khong hop le!" << endl;
            break;
        }
        getline(ss, gioiTinh, '|');
        if(!p->kiemtragioitinh(gioiTinh)){
            cout << "Gioi tinh khong hop le!" << endl;
            break;
        }
        getline(ss, diaChi, '|');
        if(!p->kiemtradiachi(diaChi)){
            cout << "Dia chi khong hop le!" << endl;
            break;
        }
        getline(ss, soDienThoai, '|');
        if(!p->kiemtrasodienthoai(soDienThoai)){
            cout << "So dien thoai khong hop le!" << endl;
            break;
        }
        if(kiemTraLoaiNguoi(id) != loaiNguoi) {
            cout << "Loai nguoi khong hop le!" << endl;
            break;
        }
        else{
            if (loaiNguoi == 1) {
                float diemTBC, diemRenLuyen;
                int soTinChi;
                string chuyenNganh, truong;
                ss >> diemTBC;
                ss.ignore();
                ss >> diemRenLuyen;
                ss.ignore();
                ss>> soTinChi;
                ss.ignore();
                if (soTinChi <= 0 || soTinChi > 30) {
                    cout << "So tin chi toi thieu la 1 va toi da la 30!" << endl;
                    break;
                }
                getline(ss, chuyenNganh, '|');
                getline(ss, truong, '|');
                danhSach.push_back(new SinhVien(id, hoTen, boPhan, namSinh, gioiTinh, diaChi, soDienThoai,
                diemTBC, diemRenLuyen, soTinChi, chuyenNganh, truong));
            } else if (loaiNguoi == 2) {
                string khoa, viTri, thanhTuu, hocVi, truongBoMon;
                int soNamGiangDay, soLuongCongTrinh;
                getline(ss, khoa, '|');
                getline(ss, viTri, '|');
                getline(ss, thanhTuu, '|');
                ss >> soNamGiangDay;
                ss.ignore();
                if (soNamGiangDay < 0) {
                    cout << "So nam giang day khong the nho hon 0!" << endl;
                    break;
                }
                getline(ss, hocVi, '|');
                if (hocVi != "TS" && hocVi != "ThS" && hocVi != "DH") {
                    cout << "Hoc vi khong hop le!" << endl;
                    break;
                }
                ss >> soLuongCongTrinh;
                ss.ignore();
                if (soLuongCongTrinh < 0) {
                    cout << "So luong cong trinh khong the nho hon 0!" << endl;
                    break;
                }
                getline(ss, truongBoMon, '|');
                float diemGiangDay, diemNghienCuu;
                ss >> diemGiangDay;
                ss.ignore();
                ss >> diemNghienCuu;
                ss.ignore();
                danhSach.push_back(new GiangVien(id, hoTen, boPhan, namSinh, gioiTinh, diaChi, soDienThoai,
                khoa, viTri, thanhTuu, soNamGiangDay, hocVi, soLuongCongTrinh, truongBoMon,diemGiangDay, diemNghienCuu));
            } else if (loaiNguoi == 3) {
                string viTri, noLuc, phongBan, trinhDo;
                int soNamCongTac, soLuongDuAn;
                getline(ss, viTri, '|');
                getline(ss, noLuc, '|');
                ss >> soNamCongTac;
                ss.ignore();
                if (soNamCongTac < 0 && soNamCongTac > 60) {
                    cout << "So nam cong tac khong the nho hon 0!" << endl;
                    break;
                }
                getline(ss, phongBan, '|');
                getline(ss, trinhDo, '|');
                ss >> soLuongDuAn;
                ss.ignore();
                if (soLuongDuAn < 0) {
                    cout << "So luong du an khong the nho hon 0!" << endl;
                    break;
                }
                danhSach.push_back(new QuanLy(id, hoTen, boPhan, namSinh, gioiTinh, diaChi, soDienThoai,
                viTri, noLuc, soNamCongTac, phongBan, trinhDo, soLuongDuAn));                                   
            }
        }
    }
    file.close();
}


Person* timKiemTheoID(const vector<Person*>& danhSach, const string& id) {
    for (Person* p : danhSach) {
        if (p->getId() == id) {
            return p;
        }
    }
    return nullptr;
}


void xoaTheoID(vector<Person*>& danhSach, const string& id) {
    for (auto it = danhSach.begin(); it != danhSach.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;
            danhSach.erase(it);
            cout << "Đa xoa nguoi voi ID " << id << endl;
            return;
        }
    }
    cout << "Khong tim thay nguoi voi ID " << id << endl;
}

void hienThiDanhSach(const vector<Person*>& danhSach) {
    int choice1,choice5;
    int loai;
    cout << "Nhap doi tuong :"<<endl;
    cout << "1.SinhVien"<<endl;
    cout << "2.GiangVien"<<endl;
    cout << "3.QuanLy"<<endl;
    cin >> loai;
    cin.ignore();
    if (loai == 1) {
        cout << "Chon chuc nang:\n";
        cout << "1. In toan bo danh sach\n";
        cout << "2. In danh sach theo khoa/lop\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> choice1;
        cin.ignore();
        switch (choice1) {
            case 1: {
                for(const Person* p:danhSach){
                    string id = p->getId();
                    if(kiemTraLoaiNguoi(id)!=1){
                        continue;
                    }
                    else{  
                        const SinhVien* sv = dynamic_cast<const SinhVien*>(p);
                        if (sv) {
                        sv->hienThi();
                       }
                    }
                } 
                break;
            }
            case 2: {
                string khoaName;
                string lop;
                cout <<"Chon khoa can tim: ";
                int choice5;
                cout << "Danh sach ten khoa: " << endl;
                cout << "1. Cong nghe thong tin\n";
                cout << "2. Cong nghe sinh hoc\n";
                cout << "3. Co dien tu\n";
                cout << "4. Co khi\n";
                cout << "5. Tu dong hoa\n";
                cout << "6. Dien\n";
                cout << "Nhap khoa can chon (1-6): ";
                cin >> choice5;
                cin.ignore();
                int choice7;
                if(choice5>=1 && choice5<=6){
                    cout <<"Ban muon in theo khoa hay lop"<<endl;
                    cout<<"1.Khoa"<<endl;
                    cout<<"2.Lop"<<endl;
                    cout<<"Nhap lua chon cua ban: ";
                    cin>>choice7;
                    cin.ignore();
                }
                switch (choice5)
                {
                case 1:
                    if(choice7==1){
                        khoaName = "CNTT";
                    }
                    else{
                        int choice6;
                        cout <<"Danh sach lop thuoc khoa CNTT"<<endl;
                        cout<<"1.IT1"<<endl;
                        cout<<"2.IT2"<<endl;
                        cout<<"3.IT3"<<endl;
                        cout<<"Nhap lop can tim(1-3): ";
                        cin>>choice6;
                        cin.ignore();
                        switch (choice6)
                        {
                        case 1:
                        lop = "IT1";
                        break;
                        case 2:
                        lop = "IT2";
                        break;
                        case 3:
                        lop = "IT3";
                        break;
                        default:
                        cout << "Lựa chọn không hợp lệ!\n";
                        break;
                        }
                        }
                   
                    break;
                case 2:
                    if(choice7==1){
                        khoaName = "CNSH";
                    }
                    else{
                        int choice8;
                        cout <<"Danh sach lop thuoc khoa CNSH"<<endl;
                        cout<<"1.SH1"<<endl;
                        cout<<"2.SH2"<<endl;
                        cout<<"Nhap lop can tim(1-2): ";
                        cin>>choice8;
                        cin.ignore();
                        switch (choice8)
                        {
                        case 1:
                            lop = "SH1";
                            break;
                        case 2:
                            lop = "SH2";
                            break;
                        default:
                            cout << "Lựa chọn không hợp lệ!\n";
                            break;
                        }
                    }

                    break;
                case 3:
                    if(choice7==1){
                        khoaName = "CDT";
                    }
                    else{
                        int choice9;
                        cout <<"Danh sach lop thuoc khoa CDT"<<endl;
                        cout<<"1.CDT1"<<endl;
                        cout<<"2.CDT2"<<endl;
                        cout<<"3.CDT3"<<endl;
                        cout<<"Nhap lop can tim(1-3): ";
                        cin>>choice9;
                        cin.ignore();
                        switch (choice9)
                        {
                        case 1:
                            lop = "CDT1";
                            break;
                        case 2:
                            lop = "CDT2";
                            break;
                        case 3:
                            lop = "CDT3";
                            break;
                        default:
                            cout << "Lựa chọn không hợp lệ!\n";
                            break;
                        }
                    }
                   
                    break;
                case 4:
                    if(choice7==1){
                        khoaName = "CK";
                    }
                    else{
                        int choice10;
                        cout <<"Danh sach lop thuoc khoa CK"<<endl;
                        cout<<"1.CK1"<<endl;
                        cout<<"2.CK2"<<endl;
                        cout<<"3.CK3"<<endl;
                        cout<<"Nhap lop can tim(1-3): ";
                        cin>>choice10;
                        cin.ignore();
                        switch (choice10)
                        {
                        case 1:
                            lop = "CK1";
                            break;
                        case 2:
                            lop = "CK2";
                            break;
                        case 3:
                            lop = "CK3";
                            break;
                        default:
                            cout << "Lựa chọn không hợp lệ!\n";
                            break;
                        }
                    }
                    break;
                case 5:
                    if(choice7==1){
                        khoaName = "TDH";
                    }
                    else{
                        int choice11;
                        cout <<"Danh sach lop thuoc khoa TDH"<<endl;
                        cout<<"1.TDH1"<<endl;
                        cout<<"2.TDH2"<<endl;
                        cout<<"Nhap lop can tim(1-2): ";
                        cin>>choice11;
                        cin.ignore();
                        switch (choice11)
                        {
                        case 1:
                            lop = "TDH1";
                            break;
                        case 2:
                            lop = "TDH2";
                            break;
                        default:
                            cout << "Lựa chọn không hợp lệ!\n";
                            break;
                        }
                    }
                   
                    break;
                case 6:
                    if(choice7==1){
                        khoaName = "D";
                    }
                    else{
                        int choice11;
                        cout <<"Danh sach lop thuoc khoa Khoa D"<<endl;
                        cout<<"1.D1"<<endl;
                        cout<<"2.D2"<<endl;
                        cout<<"Nhap lop can tim(1-2): ";
                        cin>>choice11;
                        cin.ignore();
                        switch (choice11)
                        {
                        case 1:
                            lop = "D1";
                            break;
                        case 2:
                            lop = "D2";
                            break;
                        default:
                            cout << "Lua chon khong hop le!\n";
                            break;
                        }
                    }
                    break;
                default:
                    cout << "Lua chon khong hop le!\n";
                    break;
                }
                if(choice7==1){
                    for (const Person* p : danhSach) {
                    const SinhVien* sv = dynamic_cast<const SinhVien*>(p);
                    if (sv && sv->getChuyenNganh() == khoaName) {
                        sv->hienThi();
                    }
                }
                }
                else{
                    for (const Person* p : danhSach) {
                    if (p->getBoPhan().find(lop) != string::npos) {
                        p->hienThi();
                    }
                }
                }
                break;
            }
            default:
                cout << "Lua chon khong hop le!\n";
                break;
        }
    } else if (loai == 2) {
        cout << "Chon chuc nang:\n";
        cout << "1. In toan bo danh sach\n";
        cout << "2. In danh sach theo khoa\n";
        cout << "3. In danh sach theo hoc vi\n";
        cout << "Nhap lua chon cua ban(1-3): ";
        cin >> choice1;
        cin.ignore();
        switch (choice1) {
            case 1: {
                for(const Person* p:danhSach){
                    string id= p->getId();
                    if(kiemTraLoaiNguoi(id)!=2){
                        continue;
                    }
                    else{
                        const GiangVien* gv= dynamic_cast<const GiangVien*>(p);
                        if (gv) {
                        gv->hienThi();  // Hiển thị thông tin giảng viên
                        }
                    }
                 }
                break;
            }
            case 2: {
                string khoa;
                cout << "Nhap ten khoa: ";
                cout << "Danh sách tên khoa: " << endl;
                cout << "1. Cong nghe thong tin\n";
                cout << "2. Cong nghe sinh hoc\n";
                cout << "3. Co dien tu\n";
                cout << "4. Co khi\n";
                cout << "5. Tu dong hoa\n";
                cout << "6.Dien\n";
                cout << "Nhập khoa cần chọn CNTT/CNSH/CDT/TDH/CDT/D: ";
                bool found = false;  
                getline(cin, khoa);
                for (const Person* p : danhSach) {
                    if (p->getBoPhan() == khoa) {
                        p->hienThi();
                        found = true;
                    }
                }
                if (!found) {
                    cout << "Khong tim khoa trong danh sach " << khoa << endl;
                }
                break;
            }
            case 3: {
                string hocVi;
                cout << "Nhap hoc vi(TS/ThS/DH): ";
                bool found = false;
                getline(cin, hocVi);
                for (const Person* p : danhSach) {
                    const GiangVien* gv = dynamic_cast<const GiangVien*>(p);
                    if (gv && gv->getHocVi() == hocVi) {
                        gv->hienThi();
                        found = true;
                    }
                }
                if (!found) {
                    cout << "Khong tim thấy giang vien co hoc vi nay" << hocVi << endl;
                }
                break;
            }
            default:
                cout << "Lua chon khong hop le!\n";
                break;
        }
    } else if (loai == 3) {
        cout << "Chon chuc nang:\n";
        cout << "1. In toan bo danh sach\n";
        cout << "2. In danh sach theo bo phan\n";
        cout << "3. In danh sach theo phong ban\n";
        cout << "Nhập lựa chọn của bạn: ";
        cin >> choice1;
        cin.ignore();
        switch (choice1) {
            case 1: {
                cout<<"Danh sach quan li\n";
                for(const Person* p:danhSach){
                    string id= p->getId();
                    if(kiemTraLoaiNguoi(id)!=3){
                        continue;
                    }
                    else{
                        const QuanLy* ql= dynamic_cast<const QuanLy*>(p);
                        if (ql) {
                        ql->hienThi();
                        }
                    }
                 }
                break;
            }
            case 2: {
                string viTri;
                int choice5;
                cout << "Nhap bo phan: ";
                cout << "Danh sach ten bo phan: " << endl;
                cout << "1. Bo phan thuong truc\n";
                cout << "2.Bo phan khong thuong truc\n";
                cout << "Nhap bo phan can chon (1-2): ";
                cin >> choice5;
                cin.ignore();  // To consume the newline left by cin
                switch (choice5) {
                    case 1:
                        viTri = "Bo phan Thuong truc";
                        break;
                    case 2:
                        viTri = "Bo phan Khong thuong truc";
                        break;
                    default:
                        cout << "Lựa chọn không hợp lệ!\n";
                        return;  // Exit the case if invalid choice
                }
                for (const Person* p : danhSach) {
                    if (p->getBoPhan() == viTri) {
                        p->hienThi();
                    }
                }
                break;
            }
            case 3: {
                string phongBan;
                int choice5;
                cout << "Nhap phong ban: ";
                cout << "Danh sách tên phòng ban: " << endl;
                cout << "1. Phong dao tao\n";
                cout << "2. Phong tai chinh\n";
                cout << "3. Phong cong tac sinh vien\n";
                cout << "4. Phong to chuc hanh chinh\n";
                cout << "5. Phong co so vat chat\n";
                cout << "Nhập phòng ban cần chọn (1-5): ";
                cin >> choice5;
                cin.ignore();  // To consume the newline left by cin
                switch (choice5) {
                    case 1:
                        phongBan = "Dao tao";
                        break;
                    case 2:
                        phongBan = "Tai Chinh";
                        break;
                    case 3:
                        phongBan = "Cong tac sinh vien";
                        break;
                    case 4:
                        phongBan = "To chuc - Hanh chinh";
                        break;
                    case 5:
                        phongBan = "Co so vat chat";
                        break;
                    default:
                        cout << "Lua chon khong hop le!\n";
                        return;  // Exit the case if invalid choice
                }

                for (const Person* p : danhSach) {
                    const QuanLy* ql = dynamic_cast<const QuanLy*>(p);
                    if (ql && ql->getPhongBan() == phongBan) {
                        ql->hienThi();
                    }
                }
                break;
            }
            default:
                cout << "Lua chon khong hop le!\n";
                break;
        }}
     else {
        cout << "Lua chon khong hop le!\n";
    }
}

void capNhatThongTinTheoID(vector<Person*>& danhSach, const string& id) {
    Person* p = timKiemTheoID(danhSach, id);
    if (p) {
        p->capNhatThongTin();
    } else {
        cout << "Khong tim thay nguoi voi ID " << id << endl;
    }
}


bool idHopLe(const vector<Person*>& danhSach, const string& id) {
    return timKiemTheoID(danhSach, id) == nullptr;
}


void themNguoiMoi(vector<Person*>& danhSach) {
    Person* p;
    string id, hoTen, boPhan, gioiTinh, diaChi, soDienThoai;
    int namSinh;
    int loai;
    cout << "Chon doi tuong can them"<<endl;
    cout<<"1.Sinh Vien "<<endl<<"2.Giang Vien"<<endl<<"3.Quan li"<<endl;
    cin>>loai;
    cin.ignore();
    cout << "Nhap ID: ";
    getline(cin, id);


    if (!idHopLe(danhSach, id)) {
        cout << "ID đa ton tai. Vui long nhap lai.\n";
        return;
    }
    if (kiemTraLoaiNguoi(id) == 0) {
        cout << "ID khong hop le. Vui long nhap lai.\n";
        return;
    }
    if(loai==1&&kiemTraLoaiNguoi(id)!=1){
        cout<<"Loai nguoi khong hop le"<<endl;
        return;
    }
    if(loai==2&&kiemTraLoaiNguoi(id)!=2){
        cout<<"Loai nguoi khong hop le"<<endl;
        return;
    }
    if(loai==3&&kiemTraLoaiNguoi(id)!=3){
        cout<<"Loai nguoi khong hop le"<<endl;
        return;
    }
    do{
        cout << "Nhap ten: ";
        getline(cin, hoTen);
    }
    while(!p->kiem_tra_ho_ten(hoTen));
    string chuyenNganh;
    if(loai==1){
        cout<<"Chon chuyen nganh\n";
        cout<<"Danh sach chuyen nganh:\n";
        cout<<"1. Cong nghe thong tin\n";
        cout<<"2. Cong nghe sinh hoc\n";
        cout<<"3. Co dien tu\n";
        cout<<"4. Co khi\n";
        cout<<"5. Tu dong hoa\n";
        cout<<"6. Dien\n";
        int choice;
        cout<<"Nhap chuyen nganh(1-6): ";
        cin>>choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            chuyenNganh = "CNTT";
            cout<<"Danh sach lop:\n";
            cout<<"1.IT1\n";
            cout<<"2.IT2\n";
            cout<<"3.IT3\n";
            cout<<"Nhap lop(1-3): ";
            int choice1;
            cin>>choice1;
            cin.ignore();
            switch (choice1)
            {
            case 1:
                boPhan = "IT1";
                break;
            case 2:
                boPhan = "IT2";
                break;
            case 3:
                boPhan = "IT3";
                break;
            default:
                cout << "Lua chon khong hop le! Vui long chon lai.\n";
                break;
            }
            break;
        case 2:
            chuyenNganh = "CNSH";
            cout<<"Danh sach lop:\n";
            cout<<"1.SH1\n";
            cout<<"2.SH2\n";
            cout<<"Nhap lop(1-2): ";
            int choice2;
            cin>>choice2;
            cin.ignore();
            switch (choice2)
            {
            case 1:
                boPhan = "SH1";
                break;
            case 2:
                boPhan = "SH2";
                break;
            default:
                cout << "Lua chon khong hop le! Vui long chon lai.\n";
                break;
            }
            break;
        case 3:
            chuyenNganh = "CDT";
            cout<<"Danh sach lop:\n";
            cout<<"1.CDT1\n";
            cout<<"2.CDT2\n";
            cout<<"3.CDT3\n";
            cout<<"Nhap lop(1-3): ";
            int choice3;
            cin>>choice3;
            cin.ignore();
            switch (choice3)
            {
            case 1:
                boPhan = "CDT1";
                break;
            case 2:
                boPhan = "CDT2";
                break;
            case 3:
                boPhan = "CDT3";
                break;
            default:
                cout << "Lua chon khong hop le! Vui long chon lai.\n";
                break;
            }
            break;
        case 4:
            chuyenNganh = "CK";
            cout<<"Danh sach lop:\n";
            cout<<"1.CK1\n";
            cout<<"2.CK2\n";
            cout<<"3.CK3\n";
            cout<<"Nhap lop(1-3): ";
            int choice4;
            cin>>choice4;
            cin.ignore();
            switch (choice4)
            {
            case 1:
                boPhan = "CK1";
                break;
            case 2:
                boPhan = "CK2";
                break;
            case 3:
                boPhan = "CK3";
                break;
            default:
                cout << "Lua chon khong hop le! Vui long chon lai.\n";
                break;
            }
            break;
        case 5:
            chuyenNganh = "TDH";
            cout<<"Danh sach lop:\n";
            cout<<"1.TDH1\n";
            cout<<"2.TDH2\n";
            cout<<"Nhap lop(1-2): ";
            int choice5;
            cin>>choice5;
            cin.ignore();
            switch (choice5)
            {
            case 1:
                boPhan = "TDH1";
                break;
            case 2:
                boPhan = "TDH2";
                break;
            default:
                cout << "Lua chon khong hop le! Vui long chon lai.\n";
                break;
            }
            break;
        case 6:
            chuyenNganh = "Khoa D";
            cout<<"Danh sach lop:\n";
            cout<<"1.D1\n";
            cout<<"2.D2\n";
            cout<<"Nhap lop(1-2): ";
            int choice6;
            cin>>choice6;
            cin.ignore();
            switch (choice6)
            {
            case 1:
                boPhan = "D1";
                break;
            case 2:
                boPhan = "D2";
                break;
            default:
                cout << "Lua chon khong hop le! Vui long chon lai.\n";
                break;
            }
            break;
        default:
            cout << "Lua chon khong hop le! Vui long chon lai.\n";
            break;
        }
    }
    if(loai==2){
        cout<<"Danh sach chuyen nganh da tot nghiep:\n";
        cout<<"1.CNTT\n";
        cout<<"2.CNSH\n";
        cout<<"3.CDT\n";
        cout<<"4.CK\n";
        cout<<"5.TDH\n";
        cout<<"Nhap chuyen nganh(1-5): ";
        int choice7;
        cin>>choice7;
        cin.ignore();
        switch (choice7)
        {
        case 1:
            boPhan = "CNTT";
            break;
        case 2:
            boPhan = "CNSH";
            break;
        case 3:
            boPhan = "CDT";
            break;
        case 4:
            boPhan = "CK";
            break;
        case 5:
            boPhan = "TDH";
            break;
        default:
            cout << "Lua chon khong hop le! Vui long chon lai.\n";
            break;
        }
    }

    if(loai==3){
        cout<<"Danh sach bo phan:\n";
        cout<<"1.Bo phan thuong truc\n";
        cout<<"2.Bo phan khong thuong truc\n";
        cout<<"Nhap bo phan(1-2): ";
        int choice8;
        cin>>choice8;
        cin.ignore();
        switch (choice8)
        {
        case 1:
            boPhan = "Bo phan thuong truc";
            break;
        case 2:
            boPhan = "Bo phan khong thuong truc";
            break;
        default:
            cout << "Lua chon khong hop le! Vui long chon lai.\n";
            break;
        }
    }
    int choice2;
    do {
        cout << "\n--- Nhap thong tin ---\n";
        cout << "1. Nam sinh\n";
        cout << "2. Gioi tinh\n";
        cout << "3. Dia chi\n";
        cout << "4. So dien thoai\n";
        cout << "Nhap thong tin can them (1-4): ";
        cin >> choice2;
        cin.ignore();
        switch (choice2) {
            case 1:
                cout << "Nhap nam sinh: ";
                cin >> namSinh;
                cin.ignore();
                if (!p->kiemTraNamSinh(namSinh)) {
                    cout << "Nam sinh khong hop le!" << endl;
                    continue;
                }
                break;
            case 2:
                cout << "Nhap gioi tinh(Nam/Nu): ";
                getline(cin, gioiTinh);
                if (!p->kiemtragioitinh(gioiTinh)) {
                    cout << "Gioi tinh khong hop le!" << endl;
                    continue;
                }
                break;
            case 3:
                cout << "Nhap dia chi: ";
                getline(cin, diaChi);
                if (!p->kiemtradiachi(diaChi)) {
                    cout << "Dia chi khong hop le!" << endl;
                    continue;
                }
                break;
            case 4:
                cout << "Nhap so dien thoai: ";
                getline(cin, soDienThoai);
                if (!p->kiemtrasodienthoai(soDienThoai)) {
                    cout << "So dien thoai khong hop le!" << endl;
                    continue;
                }
                break;
            default:
                cout << "Lua chon khong hop le! Vui long chon lai.\n";
        }
    } while (choice2 != 0);

    if (loai == 1) {
        float diemTBC, diemRenLuyen;
        int soTinChi;
        string truong;
        cout << "Nhap điem TBC: ";
        cin >> diemTBC;
        if(diemTBC<0 || diemTBC>10){
            cout<<"Diem trung binh chung khong hop le\n";
            return;
        }
        cout << "Nhap điem ren luyen: ";
        cin >> diemRenLuyen;
        if(diemRenLuyen<0 || diemRenLuyen>10){
            cout<<"Diem ren luyen khong hop le\n";
            return;
        }
        cout << "Nhap so tin chi: ";
        cin >> soTinChi;
        cin.ignore();
        if(soTinChi<0 || soTinChi>30){
            cout<<"So tin chi khong hop le\n";
            return;
        }
        cout << "Nhap truong: ";
        getline(cin, truong);
        danhSach.push_back(new SinhVien(id, hoTen, boPhan, namSinh, gioiTinh, diaChi, soDienThoai,
        diemTBC, diemRenLuyen, soTinChi, chuyenNganh, truong));
    } else if (loai == 2) {
        string khoa, viTri, thanhTuu, hocVi, truongBoMon;
        int soNamGiangDay, soLuongCongTrinh;
        cout << "Nhap khoa: ";
        cout<<"Danh sach khoa:\n";
        cout<<"1.Khoa CNTT\n";
        cout<<"2.Khoa CNSH\n";
        cout<<"3.Khoa CDT\n";
        cout<<"4.Khoa CK\n";
        cout<<"5.Khoa TDH\n";
        cout<<"Nhap khoa(1-5): ";
        int choice3;
        cin>>choice3;
        cin.ignore();
        switch (choice3)
        {
        case 1:
            khoa = "Khoa CNTT";
            break;
        case 2:
            khoa = "Khoa CNSH";
            break;
        case 3:
            khoa = "Khoa CDT";
            break;
        case 4:
            khoa = "Khoa CK";
            break;
        case 5:
            khoa = "Khoa TDH";
            break;
        default:
            cout << "Lua chon khong hop le! Vui long chon lai.\n";
            break;
        }
        cout << "Nhap vi tri(GVC/GVCC/GVTG/TG):\n";
        cout<<"Chu thich:\n";
        cout<<"GVC: Giang vien chinh\n";
        cout<<"GVCC: Giang vien cao cap\n";
        cout<<"GVTG: Giang vien thinh giang\n";
        cout<<"TG: Tro giang\n";
        getline(cin, viTri);
        if(viTri!="GVC"&&viTri!="GVCC"&&viTri!="GVTG"&&viTri!="TG"){
            cout<<"Vi tri khong hop le\n";
            return;
        }
        cout << "Nhap thanh tuu: ";
        getline(cin, thanhTuu);
        cout << "Nhap so nam giang day: ";
        cin >> soNamGiangDay;
        if(soNamGiangDay<0){
            cout<<"So nam giang day khong hop le\n";
            return;
        }
        cout << "Nhap hoc vi(TS/ThS/DH): ";
        cin.ignore();
        getline(cin, hocVi);
        if(hocVi!="TS"&&hocVi!="ThS"&&hocVi!="DH"){
            cout<<"Hoc vi khong hop le\n";
            return;
        }
        if(hocVi!="TS"&&hocVi!="ThS"&&hocVi!="DH"){
            cout<<"Hoc vi khong hop le\n";
            return;
        }
        cout << "Nhap so cong trinh: ";
        cin >> soLuongCongTrinh;
        cin.ignore();
        if(soLuongCongTrinh<0){
            cout<<"So cong trinh khong hop le\n";
            return;
        }
        cout << "Nhap truong bo mon: ";
        getline(cin, truongBoMon);
        float diemGiangDay, diemNghienCuu;
        danhSach.push_back(new GiangVien(id, hoTen, boPhan, namSinh, gioiTinh, diaChi, soDienThoai,
                                          khoa, viTri, thanhTuu, soNamGiangDay, hocVi, soLuongCongTrinh, truongBoMon,diemGiangDay, diemNghienCuu));
    } else if (loai == 3) {
        string viTri, noLuc, phongBan, trinhDo;
        int soNamCongTac, soLuongDuAn;
        cout << "Nhap vi tri: ";
        cout<<"Danh sach vi tri:\n";
        cout<<"1. Truong phong\n";
        cout<<"2. Pho phong\n";
        cout<<"3. Chuyen vien\n";
        cout<<"Chon vi tri(1-3): ";
        int choice4;
        cin>>choice4;
        cin.ignore();
        switch (choice4)
        {
        case 1:
            viTri = "Truong phong";
            break;
        case 2:
            viTri = "Pho phong";
            break;
        case 3:
            viTri = "Chuyen vien";
            break;
        default:
            cout << "Lua chon khong hop le! Vui long chon lai.\n";
            break;
        }
        cout << "Nhap no luc: ";
        getline(cin, noLuc);
        cout << "Nhap so nam cong tac: ";
        cin >> soNamCongTac;
        if(soNamCongTac<0){
            cout<<"So nam cong tac khong hop le\n";
            return;
        }
        cout << "Nhap phong ban: ";
        cout<<"Danh sach phong ban:\n";
        cout<<"1. Phong dao tao\n";
        cout<<"2. Phong tai chinh\n";
        cout<<"3. Phong cong tac sinh vien\n";
        cout<<"4. Phong to chuc hanh chinh\n";
        cout<<"5. Phong co so vat chat\n";
        cout<<"Nhap phong ban(1-5): ";
        int choice5;
        cin>>choice5;
        cin.ignore();
        switch (choice5)
        {
        case 1:
            phongBan = "Phong dao tao";
            break;
        case 2:
            phongBan = "Phong tai chinh";
            break;
        case 3:
            phongBan = "Phong cong tac sinh vien";
            break;
        case 4:
            phongBan = "Phong to chuc hanh chinh";
            break;
        case 5:
            phongBan = "Phong co so vat chat";
            break;
        default:    
            cout << "Lua chon khong hop le! Vui long chon lai.\n";
            break;
        }
        cout << "Nhap trinh đo(Dai hoc/Thac si/Tien si/Cu nhan): ";
        getline(cin, trinhDo);
        if(trinhDo!="Dai hoc"&&trinhDo!="Thac si"&&trinhDo!="Tien si"&&trinhDo!="Cu nhan"){
            cout<<"Trinh do khong hop le\n";
            return;
        }
        cout << "Nhap so du an: ";
        cin >> soLuongDuAn;
        if(soLuongDuAn<0){
            cout<<"So du an khong hop le\n";
            return;
        }
        danhSach.push_back(new QuanLy(id, hoTen, boPhan, namSinh, gioiTinh, diaChi, soDienThoai,
        viTri, noLuc, soNamCongTac, phongBan, trinhDo, soLuongDuAn));
    } else {
        cout << "Đoi tuong khong hop le.\n";
    }
}
bool SoSanhSinhVien(const SinhVien* a, const SinhVien* b) {
    if (a->getDiemTBC() == b->getDiemTBC()) {
        return a->getDiemRenLuyen() > b->getDiemRenLuyen();
    }
    return a->getDiemTBC() > b->getDiemTBC();
}

int phanChia(vector<SinhVien*>& arr, int low, int high) {
    SinhVien* pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (SoSanhSinhVien(arr[j], pivot)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<SinhVien*>& arr, int low, int high) {
    if (low < high) {
        int pi = phanChia(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

float xetHocBong(vector<SinhVien*>& dsSinhVien, const string& loaiHB, float diemRLMin, int soLuongHocBong, int& soLuongDaXet, float& tongSoTien, int choice) {
    vector<SinhVien*> filteredSinhVien;

    for (SinhVien* sv : dsSinhVien) {
        if (sv->getDiemRenLuyen() >= diemRLMin) {
            filteredSinhVien.push_back(sv);
        }
    }

    quickSort(filteredSinhVien, 0, filteredSinhVien.size() - 1);

    vector<SinhVien*> sinhVienDaXet;
    ofstream file("hocbong.txt", ios::app); 

    if (!filteredSinhVien.empty()) {
        cout << "\nDanh sach " << loaiHB << ":\n";
        for (int i = 0; i < min(static_cast<int>(filteredSinhVien.size()), soLuongHocBong); ++i) {
            SinhVien* sv = filteredSinhVien[i];
            cout << sv->getId() << " - " << sv->getHoTen() << " (" << loaiHB << "): "
                 << "TBC: " << sv->getDiemTBC() << ", DRL: " << sv->getDiemRenLuyen();

            float tienthuong = 0;
            if (loaiHB == "A") {
                tienthuong = sv->getsoTinChi() * 0.78 * 1.5;
            } else if (loaiHB == "B") {
                tienthuong = sv->getsoTinChi() * 0.78 * 1.3;
            } else if (loaiHB == "C") {
                tienthuong = sv->getsoTinChi() * 0.78 * 1.2;
            }

            cout << "  Tien thuong = " << tienthuong << " trieu VND" << endl;
            tongSoTien += tienthuong;

            sinhVienDaXet.push_back(sv);
            soLuongDaXet++;

            if (choice == 1) {
                file << sv->getHoTen() << " | " << sv->getBoPhan() << " | " << tienthuong << " trieu VND" << endl;
            }
        }
    }

    for (SinhVien* sv : sinhVienDaXet) {
        auto it = find(dsSinhVien.begin(), dsSinhVien.end(), sv);
        if (it != dsSinhVien.end()) {
            dsSinhVien.erase(it);
        }
    }

    file.close(); 
    return tongSoTien;
}

void thongKeHocBongTheoChuyenNganh(vector<Person*>& danhSach) {
    map<string, vector<SinhVien*>> sinhVienTheoChuyenNganh;

    for (Person* person : danhSach) {
        SinhVien* sv = dynamic_cast<SinhVien*>(person);
        if (sv) {
            sinhVienTheoChuyenNganh[sv->getChuyenNganh()].push_back(sv);
        }
    }

    cout << "Ban co muon luu ket qua khong? (1/0): ";
    int choice;
    cin >> choice;

    for (auto& entry : sinhVienTheoChuyenNganh) {
        string chuyenNganh = entry.first;
        vector<SinhVien*>& dsSinhVien = entry.second;

        cout << "\nKhoa: " << chuyenNganh << endl;
        int soLuongSinhVien = dsSinhVien.size();
        
        int soLuongHocBongA = max(1, static_cast<int>(soLuongSinhVien * 0.05));  
        int soLuongHocBongB = max(1, static_cast<int>(soLuongSinhVien * 0.05));  
        int soLuongHocBongC = max(1, static_cast<int>(soLuongSinhVien * 0.05));  

        int soLuongDaXet = 0;
        float tongSoTien = 0.0;

        tongSoTien = xetHocBong(dsSinhVien, "A", 9.0, soLuongHocBongA, soLuongDaXet, tongSoTien, choice);
        tongSoTien = xetHocBong(dsSinhVien, "B", 8.5, soLuongHocBongB, soLuongDaXet, tongSoTien, choice);
        tongSoTien = xetHocBong(dsSinhVien, "C", 8.0, soLuongHocBongC, soLuongDaXet, tongSoTien, choice);

        if (tongSoTien != 0) {
            cout << "Tong so tien thuong cua khoa " << chuyenNganh << " la: " << tongSoTien << " trieu VND" << endl;
        } else {
            cout << "Khong co sinh vien nao nhan hoc bong trong khoa " << chuyenNganh << endl;
        }
    }
}

bool SoSanhGiangVien(const GiangVien* a, const GiangVien* b) {
    if (a->getDiemGiangDay() == b->getDiemGiangDay()) {
        return a->getDiemNghienCuu() > b->getDiemNghienCuu();
    }
    return a->getDiemGiangDay() > b->getDiemGiangDay();
}

int phanChia(vector<GiangVien*>& arr, int low, int high) {
    GiangVien* pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (SoSanhGiangVien(arr[j], pivot)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<GiangVien*>& arr, int low, int high) {
    if (low < high) {
        int pi = phanChia(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

float xetKhenThuongGiangVien(vector<GiangVien*>& dsGiangVien, const string& loaiHB, float diemNCMin, int soLuongHocBong, int& soLuongDaXet, float& tongSoTien, int choice) {
    vector<GiangVien*> filteredGiangVien;
    
    for (GiangVien* gv : dsGiangVien) {
        if (gv->getDiemNghienCuu() >= diemNCMin) {
            filteredGiangVien.push_back(gv);
        }
    }

    quickSort(filteredGiangVien, 0, filteredGiangVien.size() - 1);

    ofstream file("thuong.txt", ios::app);

    if (!filteredGiangVien.empty()) {
        cout << "\nDanh sach khen thuong " << loaiHB << ":\n";
        for (int i = 0; i < min(static_cast<int>(filteredGiangVien.size()), soLuongHocBong); ++i) {
            GiangVien* gv = filteredGiangVien[i];
            cout << gv->getId() << " - " << gv->getHoTen() << " (" << loaiHB << "): "
                 << "Diem giang day: " << gv->getDiemGiangDay() << " -- Diem nghien cuu: " << gv->getDiemNghienCuu();
            
            float tienthuong = 0;
            if (loaiHB == "A") {
                tienthuong = gv->getSoLuongCongTrinh() * 1.5;
            } else if (loaiHB == "B") {
                tienthuong = gv->getSoLuongCongTrinh() * 1.3;
            }

            cout << "  Tien thuong = " << tienthuong << " trieu VND" << endl;
            tongSoTien += tienthuong;
            soLuongDaXet++;

            if (choice == 1) {
                file << gv->getHoTen() << " | " << gv->getBoPhan() << " | " << tienthuong << " trieu VND" << endl;
            }
        }
    }

    for (GiangVien* gv : filteredGiangVien) {
        auto it = find(dsGiangVien.begin(), dsGiangVien.end(), gv);
        if (it != dsGiangVien.end()) {
            dsGiangVien.erase(it);
        }
    }

    file.close(); 
    return tongSoTien;
}

void thongKeSoLuongKhenThuongGV(vector<Person*>& danhSach) {
    map<string, vector<GiangVien*>> giangVienTheoKhoa;

    for (Person* person : danhSach) {
        GiangVien* gv = dynamic_cast<GiangVien*>(person);
        if (gv) {
            giangVienTheoKhoa[gv->getKhoa()].push_back(gv);
        }
    }

    int choice;
    cout << "Ban co muon luu ket qua khong? (1/0): ";
    cin >> choice;

    for (auto& entry : giangVienTheoKhoa) {
        string khoa = entry.first;
        vector<GiangVien*>& dsGiangVien = entry.second;

        cout << "\nKhoa: " << khoa << endl;
        int soLuongGiangVien = dsGiangVien.size();
        
        int soLuongLoaiA = max(1, static_cast<int>(soLuongGiangVien * 0.05));  
        int soLuongLoaiB = max(1, static_cast<int>(soLuongGiangVien * 0.10));  
        int soLuongDaXet = 0;
        float tongSoTien = 0.0;

        xetKhenThuongGiangVien(dsGiangVien, "A", 9.0, soLuongLoaiA, soLuongDaXet, tongSoTien, choice);
        xetKhenThuongGiangVien(dsGiangVien, "B", 8.0, soLuongLoaiB, soLuongDaXet, tongSoTien, choice);

        cout << "Tong so tien thuong của khoa " << khoa << " la: " << tongSoTien << " trieu VND" << endl;
    }
}

bool SoSanhQuanLy(const QuanLy* a, const QuanLy* b) {
    return a->getSoLuongDuAn() > b->getSoLuongDuAn();
}

int phanChia(vector<QuanLy*>& arr, int low, int high) {
    QuanLy* pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (SoSanhQuanLy(arr[j], pivot)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<QuanLy*>& arr, int low, int high) {
    if (low < high) {
        int pi = phanChia(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

float xetKhenThuongQuanLy(vector<QuanLy*>& dsQuanLy, const string& loaiHB, int soDuAnMin, int soLuongHocBong, int& soLuongDaXet, float& tongSoTien, int choice) {
    vector<QuanLy*> filteredQuanLy;
    for (QuanLy* ql : dsQuanLy) {
        if (ql->getSoLuongDuAn() >= soDuAnMin) {
            filteredQuanLy.push_back(ql);
        }
    }

    quickSort(filteredQuanLy, 0, filteredQuanLy.size() - 1);

    ofstream file("thuongql.txt", ios::app);

    if (!filteredQuanLy.empty()) {
        cout << "\nDanh sach khen thuong " << loaiHB << ":\n";
        for (int i = 0; i < min(static_cast<int>(filteredQuanLy.size()), soLuongHocBong); ++i) {
            QuanLy* ql = filteredQuanLy[i];
            cout << ql->getId() << " - " << ql->getHoTen() << " (" << loaiHB << "): "
                 << "So du an: " << ql->getSoLuongDuAn();

            float tienThuong = 0.0;
            if (loaiHB == "A") {
                tienThuong = ql->getSoLuongDuAn() * 1.5;
            } else if (loaiHB == "B") {
                tienThuong = ql->getSoLuongDuAn() * 1.2;
            }
            cout << "  Tien thuong = " << tienThuong << " trieu VND" << endl;
            tongSoTien += tienThuong;
            soLuongDaXet++;

            if (choice == 1) {
                file << ql->getHoTen() << " | " << ql->getPhongBan() << " | " << tienThuong << " trieu VND" << endl;
            }
        }
    }

    for (QuanLy* ql : filteredQuanLy) {
        auto it = find(dsQuanLy.begin(), dsQuanLy.end(), ql);
        if (it != dsQuanLy.end()) {
            dsQuanLy.erase(it);
        }
    }
    file.close();
    return tongSoTien;
}

void thongKeSoLuongKhenThuongQL(vector<Person*>& danhSach) {
    map<string, vector<QuanLy*>> quanLyTheoPhongBan;

    for (Person* person : danhSach) {
        QuanLy* ql = dynamic_cast<QuanLy*>(person);
        if (ql) {
            quanLyTheoPhongBan[ql->getPhongBan()].push_back(ql);
        }
    }
    int choice;
    cout << "Ban co muon luu ket qua khong? (1/0): ";
    cin >> choice;

    for (auto& entry : quanLyTheoPhongBan) {
        string phongBan = entry.first;
        vector<QuanLy*>& dsQuanLy = entry.second;
        cout << "\nPhong ban: " << phongBan << endl;
        int soLuongQuanLy = dsQuanLy.size();

        int soLuongLoaiA = max(1, static_cast<int>(soLuongQuanLy * 0.05));  
        int soLuongLoaiB = max(1, static_cast<int>(soLuongQuanLy * 0.10));  
        int soLuongDaXet = 0;    
        float tongSoTien = 0.0; 

        xetKhenThuongQuanLy(dsQuanLy, "A", 5, soLuongLoaiA, soLuongDaXet, tongSoTien, choice);
        xetKhenThuongQuanLy(dsQuanLy, "B", 3, soLuongLoaiB, soLuongDaXet, tongSoTien, choice);

        cout << "Tong tien thuong cua phong ban " << phongBan << " la: " << tongSoTien << " trieu VND" << endl;
    }
}

void menu() {
    cout << "\n════════════════════════════════════════════════════════\n";
    cout << "            🌟 CHUONG TRINH QUAN LY KHEN THUONG 🌟\n";
    cout << "════════════════════════════════════════════════════════\n";
    cout << "|   📂 1. Doc du lieu tu file                           |\n";
    cout << "|   ✏️  2. Chinh sua thong tin                           |\n";
    cout << "|   👥 3. Hien thi danh sach nguoi                      |\n";
    cout << "|   📊 4. Thong ke muc thuong                           |\n";
    cout << "|   📜 5. In ra menu                                    |\n";
    cout << "|   ❌ 6. Thoat chuong trinh                            |\n";
    cout << "════════════════════════════════════════════════════════\n";
}

int main() {
    vector<Person*> danhSach;
    int choice; int choice7;
    string tenFile;
    menu();

    while (true) {
        cout << "👉 Chon chuc nang :";
        cin >> choice;
        cin.ignore();
        int loaiNguoi1;
        switch (choice) {
            case 1:    
                int loaiNguoi;
                cout << "1.Sinh Vien"<<endl;
                cout << "2.Giang Vien" <<endl;
                cout << "3.Quan Ly" <<endl;
                cout << "Chon doi tuong :";
                cin >> loaiNguoi;
                cin.ignore ();
                cout << "Nhap ten file dau vao: ";
                getline(cin, tenFile);
                cin.ignore ();
                docDuLieuTuFile(tenFile, danhSach, loaiNguoi);
                break;
            case 2:
                cout << "Chon chuc nang can chinh sua:\n";
                cout << "1.Tim nguoi theo ID\n";
                cout << "2.Xoa nguoi theo ID\n";
                cout << "3.Cap nhat thong tin nguoi theo ID\n";
                cout << "4.Them nguoi moi\n";
                cout << "5.Thoat\n";
                cout << "Nhap lua chon cua ban(1-5): ";
                cin >> choice7;
                cin.ignore();
                switch (choice7)
                {
                case 1:
                    cout << "Nhap ID để tim: ";
                    getline(cin, tenFile);
                    {
                    Person* p = timKiemTheoID(danhSach, tenFile);
                    if (p) {
                        p->hienThi();
                    } else {
                        cout << "Khong tim thay nguoi voi ID " << tenFile << endl;
                    }
                }
                break;
                case 2:
                    cout << "Nhap ID de xoa: ";
                    getline(cin, tenFile);
                    xoaTheoID(danhSach, tenFile);
                    break;
                case 3:
                    cout << "Nhap ID de cap nhat: ";
                    getline(cin, tenFile);
                    capNhatThongTinTheoID(danhSach, tenFile);
                    break;
                case 4:
                    themNguoiMoi(danhSach);
                    break;
                case 5:
                    break;
                default:
                    cout << "Lua chon khong hop le! Vui long nhap lai.\n";
                    break;
                }
                break;
            case 3:
                hienThiDanhSach(danhSach);
                break;
            case 4 :
                cout << "1.Sinh Vien"<<endl;
                cout << "2.Giang Vien" <<endl;
                cout << "3.Quan Ly" <<endl;
                cout << "Chon doi tuong :";
                cin >> loaiNguoi1;
                cin.ignore ();
                switch (loaiNguoi1)
                {
                case 1:
                    thongKeHocBongTheoChuyenNganh(danhSach);
                    break;
                case 2:
                    thongKeSoLuongKhenThuongGV(danhSach);
                    break;
                case 3:
                    thongKeSoLuongKhenThuongQL(danhSach);
                    break;
                default:
                    break;
                }
                break;
            case 5:
                menu();
                break;
            case 6:
                for (Person* p : danhSach) {
                    delete p;
                }
                danhSach.clear();
                cout << "Da thoat chuong trinh.\n";
                return 0;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai.\n";
                break;
        }
    }
}






