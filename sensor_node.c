//------------ CONTOH PROGRAM TRANSMITTER XBEE ---------------

int nilai=0; // tipe data yang akan dikirim, terserah mau tipe float, int, double dll
float Mnilai=0.0;
String kirim_data; // variabel yang digunakan untuk kirim data, wajib string
int node=1;
void setup() 
{
  Serial.begin(9600); // baudrate
  delay(2000);
}
void loop() 
{
  for (int i=0; i<1000; i++)
  {
    nilai= digitalRead(A0);
    Mnilai+=nilai;
    delay(1);
  }
  Mnilai=Mnilai/250.0;
//  nilai = random(0, 100); // karena contoh, data yang akan dikirim merupakan data random 0-100 (integer)
  kirim_data = "<" + String(node) + "," + String(node) + "," + String(Mnilai) + ">"; // syntax/program untuk kirim data. data yang akan dikirim wajib dijadikan string terlebih dahulu, tambahin aja variabelnya kalau yang dikirim lebih dari satu di syntax itu juga
  Serial.println(kirim_data); //perintah kirim data
  delay(3000);
}
