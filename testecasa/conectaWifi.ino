void conectaWifi(){
  //Tenta conectar ao Wifi
  WiFi.begin(NomeDoWiFi, SenhaDoWiFi);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");  
  }
  Serial.println("");
  Serial.println("Connected");
}

