#include<iostream>
#include<limits>
#include<string>
#include<map>
#include<fstream>
#include<windows.h>

using namespace std;
void logo_perusahaan(){
    cout << "=============================" << endl;
    cout << "┌┬┐┬ ┬┌─┐┌─┐┬  ┌─┐  ┌─┐┌─┐┬─┐" << endl;
    cout << "││││ │└─┐│  │  ├┤   │  ├─┤├┬┘" << endl;
    cout << "┴ ┴└─┘└─┘└─┘┴─┘└─┘  └─┘┴ ┴┴└─" << endl;
    cout << "=============================" << endl;
    cout << endl;
    cout << endl;
}

void menu_user(){
    cout << "==========================" << endl;
    cout << "| 1. user                |" << endl;
    cout << "| 2. admin               |" << endl;
    cout << "| 3. exit                |" << endl;
    cout << "| Input Type : " ;
}

int Tipe_mobil(){
    map <int,string> Tipe_mobil;

    Tipe_mobil[1] = "Ford Mustang      ";
    Tipe_mobil[2] = "Dodge Challenger  ";
    Tipe_mobil[3] = "Chevrolet Camaro  ";

    cout << "========================" << endl;
    cout << "| Tipe Mobil :" << endl;
    for(const auto& var : Tipe_mobil){
        cout << "| " << var.first << ". " << var.second << endl;
    }
    cout << "| 0.Kembali" << endl;
    cout << endl;
    return Tipe_mobil.size();

}

void Terimakasihsudahdatang(){
    cout << "Terimakasih sudah datang!" << endl;
}

void clearScreen(){
    cout << "\033[2J\033[H";
}

void error_message(string pesan_error){
    string dummy;
    cout << pesan_error << endl;
    cout << "Enter to continue" << endl;
    getline(cin,dummy);
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

void catatan_pembelian(int id, string nama_pengguna){
    string nama_file = "log_pembelian";
    string final_nama_file = nama_file +to_string(id)+".txt";

    ofstream outputFile(final_nama_file,ios::app);
    if(outputFile.is_open()){
        outputFile << nama_pengguna << "\n";
        outputFile.close();
    }
    return;
}

bool list_pembelian_berdasarkan_id_file(int id){
    int select;
    string nama_file = "log_pembelian";
    string final_nama_file = nama_file +to_string(id)+".txt";
    ifstream openfile(final_nama_file,ifstream::in);
    if(openfile.is_open()){
       cout << "| List nama Pengunjung website mobil " << id << " : " << endl;
       string name;
       while(getline(openfile,name)){
           cout << "| " << name << endl;
       }
       openfile.close();
       return true;
   }else{
       return false;
   }

}

void main_User(){
    int main_select , jumlah_mobil, jumlah_pembelian;
    long long int total_harga, kembalian, pembayaran;
    long long int semua_harga_mobil = 30000000000;
    string nama_pengguna;
    bool status = true;
    while(status){
        try{
           jumlah_mobil = Tipe_mobil ();
            cout << "============================================" << endl;
            cout << "| User Select : " ;
            if(!(cin >> main_select)){
                throw runtime_error("Inputan kurang tepat");
            }
            if(main_select == 0){
                return;
            }
            if( main_select > jumlah_mobil){
                throw runtime_error("Inputan tidak di temukan");
            }
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            clearScreen();

            cout << "============================================" << endl;
            cout << "| Beli berapa mobil? : ";
            if(!(cin >> jumlah_pembelian)){
                throw runtime_error("Inputan kurang tepat");
            }

            if( jumlah_pembelian < 1){
                throw runtime_error("tidak boleh beli 1, minimal 2");
            }
            clearScreen();
            total_harga = semua_harga_mobil * jumlah_pembelian;
            cout << "============================================" << endl;
            cout << "| Total harga yang harus di bayarkan  sebesar : " << total_harga << endl;
            cout << "| Masukan nominal uang yang di berikan user : " ;
            if(!(cin >> pembayaran)){

                throw runtime_error("Inputan tidak sesuai");
            }
            if(pembayaran < total_harga){

                throw runtime_error("Uang anda kurang !");
            }
            kembalian = pembayaran - total_harga;
            cout << "| Total Kembalian anda sebesar : " << kembalian << endl;
            cin.ignore();
            for(int i = 0 ; i < jumlah_pembelian ; i++){
                cout << "Masukan nama pembeli ke " << i + 1 << " : " ;
                if(!(getline(cin, nama_pengguna))){
                    throw runtime_error("input tidak sesuai");
                }
                catatan_pembelian(main_select,nama_pengguna);
            }
            clearScreen();
            cout << "Trimakasi sudah melakukan pembelian di forum ini !" << endl;
            cin.get();
            status = false;

        }catch(const exception& e){
            error_message(e.what());
        }
        clearScreen();
    }
}

void main_Admin(){
    int menu_select , jumlah_mobil;
    bool value_exit;
    string username = "admin";
    string password = "adamaja";
    string input_user, input_password;
    bool status = true;
     while(status){
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        try{
            cout << "Username : " ;
            if(!(getline(cin,input_user))){
                throw runtime_error("inputan tidak sesuai");
            }
            cout << "Password : " ;
            if(!(getline(cin,input_password))){
                throw runtime_error("inputan tidak sesuai");
            }

            if(username == input_user && password == input_password){
                clearScreen();
                jumlah_mobil = Tipe_mobil();
                if(!(cin >> menu_select)){
                    throw runtime_error("Inputan kurang tepat");
                }
                if(menu_select == 0){
                    return;
                }
                if(menu_select > jumlah_mobil){
                    throw runtime_error("inputan tidak di temukan");
                }
               cin.ignore(numeric_limits<streamsize>::max(),'\n');
               value_exit = list_pembelian_berdasarkan_id_file(menu_select);
                if(value_exit == false){
                    cout << "Belum ada pembeli !" << endl;
                }
                cout << "Tekan enter untuk kembali ke menu awal " << endl;
                cin.get();
                status = false;
            }else{
                cout << "User dan password anda salah !" << endl;
                status = true;
            }

        }catch(const exception& e){
            error_message(e.what());
            status = true;
        }
    }
}

int main(){
    int menu_select = 3;
    bool aplikasi_status = true;
    while(aplikasi_status){
        try{
            clearScreen();
            aplikasi_status = false;
            logo_perusahaan();
            menu_user();
            if(!(cin >> menu_select)){
                throw runtime_error("input tidak valid , Harap masukan bilangan bulat");
            }

             switch(menu_select){
                case 1:
                    clearScreen();
                    main_User();

                break;
                case 2:
                    clearScreen();
                    main_Admin();

                break;
                case 3:
                    clearScreen();
                    Terimakasihsudahdatang();
                    return 0;

                break;
                default :
                    error_message("inputan tidak di temukan");
                break;
            }

        }catch(const exception& e){
            error_message(e.what());
        }
        aplikasi_status = true;
    }
    return 0;
}
