void enviaDHT(){
  char MagUmidadeMQTT[10];
  char MagTemperaturaMQTT[10];

  umidade = dht.readHumidity();
  temperatura = dht.readTemperature();

  if(isnan(umidade) || isnan(temperatura)){
    Serial.println("Falha na leitura do sensor DHT11");
  } else{
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" *C ");
    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println(" % ");

    delay(10000);   // mede a cada 10s

    sprintf(MagUmidadeMQTT, "%i",umidade);
    client.publish("casa/umidade", MagUmidadeMQTT);
    sprintf(MagTemperaturaMQTT, "%i", temperatura);
    client.publish("casa/temperatura", MagTemperaturaMQTT);
    
  }
}
