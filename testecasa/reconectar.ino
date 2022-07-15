void reconectar()
{
  //Repete até conectar
  while(!client.connected())
  {
    bool conectado = strlen(servidor_mqtt_usuario)>0 ?
                     client.connect("fowmjfeg", servidor_mqtt_usuario, servidor_mqtt_senha) :
                     client.connect("k-Z9yumoegOn");
    if (conectado)
    {
      //Subscreve para monitorar os comandos recebidos
      client.subscribe(mqtt_topico_sub, 1); //QoS1
    }
    else
    {
      delay(5000);
    }
  }  
  
}
