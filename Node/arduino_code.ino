//this is code that is uploaded to arduino board
#define ag_ismi "CMPE_IOT"
#define ag_sifresi "cmpeiot123"
#define address "smartcleaning.eu-gb.mybluemix.net"
 
float kapi01;
 
void setup()
{
  Serial.begin(115200); //Seriport'u açýyoruz. Güncellediðimiz 
                        //ESP modülünün baudRate deðeri 115200 olduðu için bizde Seriport'u 115200 þeklinde seçiyoruz
  
  Serial.println("AT"); //ESP modülümüz ile baðlantý kurulup kurulmadýðýný kontrol ediyoruz.
  
  delay(3000); //ESP ile iletiþim için 3 saniye bekliyoruz.
 analogReference(INTERNAL);
  if(Serial.find("OK")){         //esp modülü ile baðlantýyý kurabilmiþsek modül "AT" komutuna "OK" komutu ile geri dönüþ yapýyor.
     Serial.println("AT+CWMODE=1"); //esp modülümüzün WiFi modunu STA þekline getiriyoruz. Bu mod ile modülümüz baþka aðlara baðlanabilecek.
     delay(2000);
     String baglantiKomutu=String("AT+CWJAP=\"")+ag_ismi+"\",\""+ag_sifresi+"\"";
    Serial.println(baglantiKomutu);
    
     delay(2000);
 }
}
 
void loop(){
  float kapi01 = digitalRead(4); 
  float kapi02 = digitalRead(5); 
  float kapi03 = digitalRead(6); 
Serial.println(kapi01);
Serial.println(kapi02);
Serial.println(kapi03);
 sicaklik_yolla(kapi01,kapi02,kapi03);
 // dakikada 1 güncellenmesi için 1 dakika bekle
 delay(1000);
}
 
 
void sicaklik_yolla(float kapi01,float kapi02,float kapi03){
 Serial.println(String("AT+CIPSTART=\"TCP\",\"") + address + "\",80");  //thingspeak sunucusuna baðlanmak için bu kodu kullanýyoruz. 
                                                                   //AT+CIPSTART komutu ile sunucuya baðlanmak için sunucudan izin istiyoruz. 
                                                                   //TCP burada yapacaðýmýz baðlantý çeþidini gösteriyor. 80 ise baðlanacaðýmýz portu gösteriyor
            delay(1000);
              if(Serial.find("Error")){     //sunucuya baðlanamazsak ESP modülü bize "Error" komutu ile dönüyor.
              Serial.println("AT+CIPSTART Error");
              return;
            }
  
String yollanacakkomut = "GET /data?&field1=";
yollanacakkomut += (kapi01);
yollanacakkomut += "&field2=";
yollanacakkomut += (kapi02);
yollanacakkomut += "&field3=";
yollanacakkomut += (kapi03);
yollanacakkomut += " HTTP/1.1";
yollanacakkomut += "\r\n";
yollanacakkomut += "Host: smartcleaning.eu-gb.mybluemix.net";
yollanacakkomut += "\r\n";
yollanacakkomut += "Accept: */*";
yollanacakkomut += "\r\n\r\n";
delay(3000);                                                                                // /r/n komutu kullanmamýz gerekiyor.
 
 Serial.print("AT+CIPSEND=");                    //veri yollayacaðýmýz zaman bu komutu kullanýyoruz. Bu komut ile önce kaç tane karakter yollayacaðýmýzý söylememiz gerekiyor.
 Serial.println(yollanacakkomut.length()+2);       //yollanacakkomut deðiþkeninin kaç karakterden oluþtuðunu .length() ile bulup yazýrýyoruz.
 
 delay(1000);
 
 if(Serial.find(">")){                           //eðer sunucu ile iletiþim saðlayýp komut uzunluðunu gönderebilmiþsek ESP modülü bize ">" iþareti ile geri dönüyor.
                                                 // arduino da ">" iþaretini gördüðü anda sýcaklýk verisini esp modülü ile thingspeak sunucusuna yolluyor.
 Serial.print(yollanacakkomut);
 Serial.print("\r\n\r\n");
 }
 else{
 Serial.println("AT+CIPCLOSE");
 }
}
