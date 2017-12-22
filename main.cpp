/* Standard C++ includes */
#include <iostream> // untu3k mendeklarasikan bahasa c++
#include <conio.h> //untuk pemanggilan getch
#include <ctime> //
#include <cstdlib> //untuk menerapkan CLS (clear screen)
#include <fstream> //untuk menerapkan varfile (akses file)
#include <windows.h> //untuk memanggil sistem

//sqlite3 library
#include "sqlite3.h"

using namespace std;

   sqlite3 *db;
   char *zErrMsg = 0;
   int rc,rc2;
   char *sql;
   const char* data = "";
   sqlite3_stmt *stmt;

//manggil sql
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("\t%s", argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

void cetakgaris(int n) //untuk menampilkan garis
 {  int i;
  for(i=0;i<=n;i++)
       cout<<"=";cout<<"\n";
 }

void loadfirst(){ //untuk menampilkan loading
  cout<<"\nMembuka data ";
  for(int l=0;l<20;l++){
  Sleep(50);cout<<"±";
}
}

void header(){
cetakgaris(79);
	cout<<"\t\t\t         Selamat Datang"<<endl;
	cout<<"\t\t\t     PT. Kereta Api SEMARANG    \n"<<endl;
	cout<<"\t\t\t        Created Kelompok 2   "<<endl;
cetakgaris(79);
}

int hargatiket(int z){
	int harga;
	if (z==1){
		harga=140000;
	}
	else if (z==2){
		harga=250000;
	}
	else if (z==3){
		harga=120000;
	}
	else if (z==4){
		harga=150000;
	}
	else if (z==5){
		harga=180000;
	}
	else if (z==6){
		harga=250000;
	}
	else if (z==7){
		harga=140000;
	}
	else if (z==8){
		harga=150000;
	}
	else if (z==9||z==10){
		harga=275000;
	}
	else if (z==11){
		harga=310000;
	}
	else if (z==12){
		harga=95000;
	}
	else if (z==13){
		harga=225000;
	}
	else if (z==14){
		harga=300000;
	}
	else if (z==15){
		harga=310000;
	}
	else if (z==16){
		harga=330000;
	}
	return (harga);
}

int total(int x, int z) {
	int dewasa, total;
		dewasa=x*hargatiket(z);
		total=dewasa;
		return (total);
}

void biopenumpang(int z, int booking){
    char sqlStr[256];
	std::string id;
   	char nama[20];
	std::string umur;
	char kodeker[4];
	sprintf(kodeker, "%d", z);
	cout<<"\n\t+=========================================================+";
	cout<<"\n\t|                   BIODATA PENUMPANG                     |";
	cout<<"\n\t+=========================================================+";
	cout<<"\n\t  => Kode Booking : ";
	cout<<booking;
    char BOOKING[4];
	sprintf(BOOKING, "%d", booking);
	cout<<endl;
	cout<<"\n\t  => No Identitas : ";
	cin>>id;
	const char * IDPEMBELI = id.c_str();
	cout<<"\n\t  => Nama         : ";
	cin>>nama;
	cout<<"\n\t  => Umur         : ";
	cin>>umur;
	const char * UMUR = umur.c_str();
	cout<<endl;
	/* Create SQL statement */
	sprintf( sqlStr, "INSERT INTO penumpang (ID,NAMA,UMUR,kodekereta,booking) VALUES (%s, '%s', %s, '%s','%s'); ", IDPEMBELI, nama, UMUR,kodeker,BOOKING );
	
	/* Execute SQL statement */
   rc = sqlite3_exec(db, sqlStr, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "\t\t **Data Tersimpan\n");
   }
}	

int jmlpenumpang(int z){
	int x;
	char sqlStr[256];
	string y;
	srand(time(0));
	int booking = 1001 + rand();	
	cout<<"\n\t+=========================================================+";
	cout<<"\n\t|                  Jumlah Penumpang                       |";
	cout<<"\n\t+=========================================================+";
	cout<<"\n\t  => Jumlah Penumpang: "; cin>>x;
    char jmlpenumpang[5];
	sprintf(jmlpenumpang, "%d", x);
	char kodeker[4];
	sprintf(kodeker, "%d", z);	
    char BOOKING[4];
	sprintf(BOOKING, "%d", booking);
			
		cout<<"\n\t  => Total = Rp."<< total(x,z);
    	char TOTAL[10];
		sprintf(TOTAL, "%d", total);
		/* Create SQL statement */
		sprintf( sqlStr, "INSERT INTO book_king (booking,jmlpenumpang,kodekereta,kodeharga,total) VALUES ('%s', %s, %s, %s ,%s); ", BOOKING, jmlpenumpang, kodeker, kodeker, TOTAL );
	
		/* Execute SQL statement */
   		rc = sqlite3_exec(db, sqlStr, callback, 0, &zErrMsg);

		cout<<"\n\t+---------------------------------------------------------+";
		cout<<"\n\t  => Apakah Setuju ? [Y/N] : "; cin>>y;
		cout<<"\n\t+---------------------------------------------------------+"<<endl;
		if (y=="y"||y=="Y"){
	  		for (int i=1; i<=x; i++){
				cout<<"\n\t+---------------------------------------------------------+";
				cout<<"\n\t|                  PENUMPANG ke-"<<i<<"                         |";
				cout<<"\n\t+---------------------------------------------------------+";
				biopenumpang(z,booking);		
			}
    		char BOOKING[4];
			sprintf(BOOKING, "%d", booking);
			cout<<"\n  +------------------------------------------------------------------------+";
			cout<<"\n  |                             DATA PENUMPANG                             |";
			cout<<"\n  +------------------------------------------------------------------------+";
			cout<<"\n      id       nama     nama kereta     tujuan      berangkat   tiba";
			cout<<"\n      -------  ------  -------------    ---------   ---------   -------"<<endl;
	   		/* Create SQL statement */
	   		sprintf( sqlStr, "SELECT ID,NAMA,namakereta,ke,jamberangkat,jamtiba FROM penumpang NATURAL JOIN kereta WHERE booking= '%s'ORDER BY NAMA ASC", BOOKING);
	   		/* Execute SQL statement */
	   		rc = sqlite3_exec(db, sqlStr, callback, (void*)data, &zErrMsg);

			cout<<"\n\t+---------------------------------------------------------+";
			cout<<"\n\t  => Apakah Setuju ? [Y/N] : "; cin>>y;
			cout<<"\n\t+---------------------------------------------------------+"<<endl;
			if (y=="y"||y=="Y"){
				char kursi[4];
				sprintf(kursi, "%d", x);
				char kodeker[4];
				sprintf(kodeker, "%d", z);
				/* Create SQL statement */
				sprintf( sqlStr, "UPDATE kereta SET kursi = kursi -%s WHERE kodekereta='%s';", kursi, kodeker);
	
				/* Execute SQL statement */
				rc = sqlite3_exec(db, sqlStr, callback, 0, &zErrMsg);
   
 			 	if( rc != SQLITE_OK ){
      				fprintf(stderr, "SQL error: %s\n", zErrMsg);
      				sqlite3_free(zErrMsg);
   				} else {
      				fprintf(stdout, "\n\t+---------------------------------------------------------+\n\t\t    >>  Pesanan BERHASIL DISIMPAN  <<  \n\t+---------------------------------------------------------+\n");
   				}
			}
			else if (y=="n"||y=="N"){
				/* Create SQL statement */
				sprintf( sqlStr, "DELETE FROM penumpang WHERE booking=%s;", BOOKING);
	
				/* Execute SQL statement */
    			rc = sqlite3_exec(db, sqlStr, callback, 0, &zErrMsg);
    			
				/* Create SQL statement */
				sprintf( sqlStr, "DELETE FROM book_king WHERE booking=%s;", BOOKING);
	
				/* Execute SQL statement */
    			rc = sqlite3_exec(db, sqlStr, callback, 0, &zErrMsg);   
   
 		    	if( rc != SQLITE_OK ){
      				fprintf(stderr, "SQL error: %s\n", zErrMsg);
      				sqlite3_free(zErrMsg);
   				} else {
      				fprintf(stdout, "\n\t+---------------------------------------------------------+\n\t\t    >>  Pesanan BERHASIL DIBATALKAN  <<  \n\t+---------------------------------------------------------+\n");
   				}	
			}	
			else{
				cout<<"\n\t+---------------------------------------------------------+";
				cout<<"\n\t|              TIDAK ADA DALAM PILIHAN                    |";
				cout<<"\n\t+---------------------------------------------------------+"<<endl;
			}
	}
	else if (y=="n"||y=="N"){
		cout<<"\n\t+---------------------------------------------------------+";
		cout<<"\n\t|                        KELUAR                           |";
		cout<<"\n\t+---------------------------------------------------------+"<<endl;
	}
	else{
		cout<<"\n\t+---------------------------------------------------------+";
		cout<<"\n\t|              TIDAK ADA DALAM PILIHAN                    |";
		cout<<"\n\t+---------------------------------------------------------+"<<endl;
	}
	return 0;
} 

int main(int argc, char* argv[]) {
	char sqlStr[256];
	header();
	loadfirst();
	awal:
	system ("CLS");
	header();
   rc = sqlite3_open("tiketkereta.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Gagal membuka database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Sukses membuka database\n");
   }
	int tujuan;
	cout<<endl;
	cout<<"\n\t\t+-----------------------------------------+";
	cout<<"\n\t\t|                 TUJUAN                  |";
	cout<<"\n\t\t+-----------------------------------------+";
	cout<<"\n\t\t|             1. BANDUNG                  |";	
	cout<<"\n\t\t|             2. JAKARTA                  |";
	cout<<"\n\t\t|             3. SURABAYA                 |";
	cout<<"\n\t\t|             0. KELUAR                   |";		
	cout<<"\n\t\t+-----------------------------------------+";
	cout<<"\n\t\t   KODE TUJUAN : "; cin>>tujuan;
	switch (tujuan){
		int z;
	case 1:{
		system ("CLS");
		header();
		cout<<endl;
	cout<<"\n  +------------------------------------------------------------------------+";
	cout<<"\n  |                              PILIH KERETA                              |";
	cout<<"\n  +------------------------------------------------------------------------+";
	cout<<"\n      kode     nama kereta      tujuan      berangkat   kursi   harga ";
	cout<<"\n      ----     -------------    ---------   ---------   ------  -------"<<endl;
   /* Create SQL statement */
   sql = "SELECT kodekereta,namakereta,ke,jamberangkat,kursi,harga FROM kereta NATURAL JOIN harga WHERE ke='BANDUNG  ' ORDER BY kodekereta ASC";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	cout<<"\n\t\t => Kode KA : ";
	cin>>z;
	char kodeker[4];
	sprintf(kodeker, "%d", z);	
	sprintf( sqlStr, "SELECT kursi from kereta WHERE kodekereta=%s", kodeker);
	if (sqlite3_prepare_v2(db, sqlStr, -1, &stmt, NULL) != SQLITE_OK)
    			cout<<"database gagal";
	else {
    	for (;;) {
    		int rc = sqlite3_step(stmt);
    		if (rc == SQLITE_DONE)
    	    break;
    		if (rc != SQLITE_ROW) {
    			cout<<"database gagal";
       			break;
    		}
    		if ((sqlite3_column_int(stmt, 0))==0) {
    			cout<<"\n\t\t------------------------------------------------"<<endl;
		  		cout<<"\t\t             >>  Kursi Habis  <<  "<<endl;
		  		cout<<"\t\t------------------------------------------------"<<endl;
			} else {
				jmlpenumpang(z);
			}
    	}
    	sqlite3_finalize(stmt);
	}	
        system ("PAUSE");	
		goto awal;
		break;
	}
	case 2:{
		system ("CLS");
		header(); 
	cout<<endl;
	cout<<"\n  +------------------------------------------------------------------------+";
	cout<<"\n  |                              PILIH KERETA                              |";
	cout<<"\n  +------------------------------------------------------------------------+";
	cout<<"\n      kode     nama kereta      tujuan      berangkat   kursi   harga ";
	cout<<"\n      ----     -------------    ---------   ---------   ------  -------"<<endl;
   /* Create SQL statement */
   sql = "SELECT kodekereta,namakereta,ke,jamberangkat,kursi,harga FROM kereta NATURAL JOIN harga WHERE ke='JAKARTA   ' ORDER BY kodekereta ASC";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	cout<<"\n\t => Kode KA : ";
	cin>>z;
	char kodeker[4];
	sprintf(kodeker, "%d", z);	
	sprintf( sqlStr, "SELECT kursi from kereta WHERE kodekereta=%s", kodeker);
	if (sqlite3_prepare_v2(db, sqlStr, -1, &stmt, NULL) != SQLITE_OK)
    			cout<<"database gagal";
	else {
    	for (;;) {
    		int rc = sqlite3_step(stmt);
    		if (rc == SQLITE_DONE)
    	    break;
    		if (rc != SQLITE_ROW) {
    			cout<<"database gagal";
       			break;
    		}
    		if ((sqlite3_column_int(stmt, 0))==0) {
    			cout<<"\n\t\t------------------------------------------------"<<endl;
		  		cout<<"\t\t             >>  Kursi Habis  <<  "<<endl;
		  		cout<<"\t\t------------------------------------------------"<<endl;
			} else {
				jmlpenumpang(z);
			}
    	}
    	sqlite3_finalize(stmt);
	}	
	    system ("PAUSE");
		goto awal;
		break;
	}	
	case 3:{
		system ("CLS");
		header(); 
	cout<<endl;
	cout<<"\n  +------------------------------------------------------------------------+";
	cout<<"\n  |                              PILIH KERETA                              |";
	cout<<"\n  +------------------------------------------------------------------------+";
	cout<<"\n      kode     nama kereta      tujuan      berangkat   kursi   harga ";
	cout<<"\n      ----     -------------    ---------   ---------   ------  -------"<<endl;
   /* Create SQL statement */
   sql = "SELECT kodekereta,namakereta,ke,jamberangkat,kursi,harga from kereta NATURAL JOIN harga WHERE ke='SURABAYA' ORDER BY kodekereta ASC";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	cout<<"\n\t => Kode KA : ";
	cin>>z;
	char kodeker[4];
	sprintf(kodeker, "%d", z);	
	sprintf( sqlStr, "SELECT kursi from kereta WHERE kodekereta=%s", kodeker);
	if (sqlite3_prepare_v2(db, sqlStr, -1, &stmt, NULL) != SQLITE_OK){
    			cout<<"database gagal";
	}
	else {
    	for (;;) {
    		int rc = sqlite3_step(stmt);
    		if (rc == SQLITE_DONE)
    	    break;
    		if (rc != SQLITE_ROW) {
    			cout<<"database gagal";
       			break;
    		}
    		if ((sqlite3_column_int(stmt, 0))==0) {
    			cout<<"\n\t\t------------------------------------------------"<<endl;
		  		cout<<"\t\t             >>  Kursi Habis  <<  "<<endl;
		  		cout<<"\t\t------------------------------------------------"<<endl;
			} else {
				jmlpenumpang(z);
			}
    	}
    	sqlite3_finalize(stmt);
	}
		
        	system ("PAUSE");
			goto awal; 
			break;
	}
	case 0 :{
		system ("CLS");
		header();
		  cout<<"\n\t\t------------------------------------------------"<<endl;
		  cout<<"\t\t    >>  Anda telah keluar dari program  <<  "<<endl;
		  cout<<"\t\t------------------------------------------------"<<endl;
        system ("PAUSE");
		break;
	} 
	default :{
		system ("CLS");
		header();
		  cout<<"\n\t\t------------------------------------------------"<<endl;
		  cout<<"\t\t        >>  Tidak Ada Dalam Pilihan  <<  "<<endl;
		  cout<<"\t\t------------------------------------------------"<<endl;
        system ("PAUSE");
		goto awal;
		break;
	} 
}
}
