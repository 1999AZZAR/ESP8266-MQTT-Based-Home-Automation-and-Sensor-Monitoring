# IoT Sensor Data Publisher with Multi-WiFi and MQTT

[![CodeFactor](https://www.codefactor.io/repository/github/1999azzar/esp8266-mqtt-based-home-automation-and-sensor-monitoring/badge)](https://www.codefactor.io/repository/github/1999azzar/esp8266-mqtt-based-home-automation-and-sensor-monitoring)

This Arduino project demonstrates an ESP8266-based IoT sensor data publisher. It reads temperature and humidity data from a DHT11 sensor and light control signals from Adafruit IO MQTT broker. The code supports multi-WiFi configuration with fallback and robust MQTT connection.

## Hardware Requirements

- ESP8266-based board (e.g., NodeMCU, Wemos D1 Mini, etc.)
- DHT11 temperature and humidity sensor
- Two-channel relay module

## Configuration

### config.h

This header file contains the necessary configurations for WiFi and Adafruit IO MQTT. Update the following parameters to match your setup:

- `Relay1`: The GPIO pin connected to the first relay (Light1).
- `Relay2`: The GPIO pin connected to the second relay (Light2).
- `DHTPIN`: The GPIO pin connected to the DHT11 sensor.
- `DHTTYPE`: The DHT sensor type (DHT11 in this case).
- `ssid1`, `password1`: WiFi credentials for the first network.
- `ssid2`, `password2`: WiFi credentials for the second network.
- `ssid3`, `password3`: WiFi credentials for the third network.
- `AIO_SERVER`: The Adafruit IO MQTT broker server.
- `AIO_SERVERPORT`: The MQTT broker port (use 8883 for SSL).
- `AIO_USERNAME`: Your Adafruit IO username.
- `AIO_KEY`: Your Adafruit IO secret key.

### main.ino

The main Arduino sketch sets up the connections, subscribes to Adafruit IO feeds for relay control, and publishes temperature and humidity data to corresponding feeds on Adafruit IO.

## Usage

1. Update the configurations in `config.h`.
2. Connect the relay module and DHT11 sensor to the appropriate GPIO pins on the ESP8266 board.
3. Upload the code to your ESP8266 board using the Arduino IDE or compatible software.
4. The ESP8266 board will attempt to connect to the available WiFi networks in the order defined in `wifi_multi.addAP()`. If one WiFi fails, it will try the next one, ensuring a reliable connection.
5. Once connected to WiFi and Adafruit IO MQTT broker, it will subscribe to the specified feeds for relay control.
6. The board will publish temperature and humidity data to the corresponding feeds on Adafruit IO.
7. Monitor and control the relay outputs remotely through Adafruit IO.

## flowchart

```mermaid
flowchart TD
    start[Start] --> config[Config.h]
    config --> library[Include Libraries]
    library --> define[Define Pin Output]
    define --> dht[Define DHT Module]
    dht --> wifi[Wifi Config]
    wifi --> wifi1[Wifi 1]
    wifi --> wifi2[Wifi 2]
    wifi --> wifi3[Wifi 3]
    wifi1 --> connected1[Connected to Wifi 1]
    wifi2 --> connected2[Connected to Wifi 2]
    wifi3 --> connected3[Connected to Wifi 3]
    connected1 --> server1[Start Server]
    connected2 --> server2[Start Server]
    connected3 --> server3[Start Server]
    server1 --> handleRoot1[Handle Root Request]
    server2 --> handleRoot2[Handle Root Request]
    server3 --> handleRoot3[Handle Root Request]
    handleRoot1 --> html1[WiFi Credentials Form]
    handleRoot2 --> html2[WiFi Credentials Form]
    handleRoot3 --> html3[WiFi Credentials Form]
    html1 --> processCred1[Process WiFi Credentials]
    html2 --> processCred2[Process WiFi Credentials]
    html3 --> processCred3[Process WiFi Credentials]
    processCred1 --> connect1[Connect to WiFi]
    processCred2 --> connect2[Connect to WiFi]
    processCred3 --> connect3[Connect to WiFi]
    connect1 --> mqtt[MQTT Connection]
    connect2 --> mqtt
    connect3 --> mqtt
    mqtt --> subscribe1[Subscribe to Light1]
    mqtt --> subscribe2[Subscribe to Light2]
    subscribe1 --> controlRelay1[Control Relay1 Light1]
    subscribe2 --> controlRelay2[Control Relay2 Light2]
    controlRelay1 --> a[End]
    controlRelay2 --> a
    a --> loop[Loop]

    loop --> dhtRead[Read DHT Sensors]
    dhtRead --> publishTemp[Publish Temperature]
    dhtRead --> publishHumi[Publish Humidity]
    publishTemp --> checkTemp[Check Publish Status]
    publishHumi --> checkHumi[Check Publish Status]
    checkTemp --> checkEnd[End]
    checkHumi --> checkEnd
    checkEnd --> delay[Delay]
    delay --> mqttRead[Read MQTT Messages]
    mqttRead --> checkSub1[Check Subscribe Light1]
    mqttRead --> checkSub2[Check Subscribe Light2]
    checkSub1 --> updateRelay1[Update Relay1]
    checkSub2 --> updateRelay2[Update Relay2]
    updateRelay1 --> loop
    updateRelay2 --> loop

style start fill:#8BC34A,stroke:#4CAF50
style a fill:#FF5722,stroke:#F44336
style wifi1, wifi2, wifi3, connected1, connected2, connected3, server1, server2, server3, handleRoot1, handleRoot2, handleRoot3, html1, html2, html3, processCred1, processCred2, processCred3, connect1, connect2, connect3, mqtt, subscribe1, subscribe2, controlRelay1, controlRelay2, loop, dhtRead, publishTemp, publishHumi, checkTemp, checkHumi, checkEnd, delay, mqttRead, checkSub1, checkSub2, updateRelay1, updateRelay2 stroke:#333,stroke-width:2px
```

## Note

- Ensure you have a stable internet connection and access to the Adafruit IO server for MQTT communication.
- Double-check hardware connections and GPIO pin assignments to avoid any issues.

## Support

You can support me by buy me a coffee if u like to.

<div align="left">
<!--   <h4>And you can also support me by <a href="https://www.buymeacoffee.com/azzar" target="_blank">buying me coffee</a></h4> -->
  <a href="https://www.buymeacoffee.com/azzar" target="_blank">
    <img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 42px !important;width: 151.9px !important; margin-top: 50px !important;">
  </a>
</div>

## Credits

This project uses the following libraries:

- [ESP8266WiFi](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html)
- [ESP8266WiFiMulti](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi/src)
- [Adafruit_MQTT](https://github.com/adafruit/Adafruit_MQTT_Library)
- [Adafruit_MQTT_Client](https://github.com/adafruit/Adafruit_MQTT_Library)
- [DHT](https://github.com/adafruit/DHT-sensor-library)
