# LedPixelController
ESP8266 unicast E1.31 to WS2811/WS2812 WiFi controller, output up to 1360 pixels* (8 ports/universes, 170 pixels per port, 4080 channels).
*The number is theoritical, depending on refresh times this number can be much lower.

The LedPixelController accepts 1 unicast broadcast universe, and up to 8 unicast universes.  The controller then multiplexes the data from the UART TXD1 port using an asynchrounous pixel driver that allows writing a universe of data while the E1.31 listens for the next data packets.

### Important Settings
  - *ssid* The name of the WiFi SSID network to connect to.  (WiFi Manager is on my todo list) 
  - *password* The password of the WiFi network to connect to.  (WiFi Manager is on my todo list) 
  - *domain* The name of the domain the ESP will be apart of.
  - *LED_ON* The value to set an enabled channel pin to. (LOW or HIGH, default LOW)
  - *LED_OFF* The value to set a disabled channel pin to. (LOW or HIGH, default HIGH)
  - *Web server

### Unicast Universes

The table below shows the outputs from the ESP8266 based on the universe input, as this is unicast only, only the least significant digit of the universe is utilized to set the proper outputs. Note the inverted outputs (LOW for Enable, HIGH for disable), this can be switch via the LED_ON and LED_OFF constants.
<table>
	<tr><th>Universe</th><th>D0</th><th>D1</th><th>D2</th><th>D3</th><th>D4</th><th>D5</th><th>D6</th><th>D7</th><th>D8</th></tr>
	<tr><td>xx0 (Broadcast)</td><td>LOW</td><td>LOW</td><td>LOW</td><td>LOW</td><td><b>DATA</b></td><td>LOW</td><td>LOW</td><td>LOW</td><td>LOW</td></tr>
  <tr><td>xx1</td><td>LOW</td><td>HIGH</td><td>HIGH</td><td>HIGH</td><td><b>DATA</b></td><td>HIGH</td><td>HIGH</td><td>HIGH</td><td>HIGH</td></tr>
	<tr><td>xx2</td><td>HIGH</td><td>LOW</td><td>HIGH</td><td>HIGH</td><td><b>DATA</b></td><td>HIGH</td><td>HIGH</td><td>HIGH</td><td>HIGH</td></tr>
	<tr><td>xx3</td><td>HIGH</td><td>HIGH</td><td>LOW</td><td>HIGH</td><td><b>DATA</b></td><td>HIGH</td><td>HIGH</td><td>HIGH</td><td>HIGH</td></tr>
	<tr><td>xx4</td><td>HIGH</td><td>HIGH</td><td>HIGH</td><td>LOW</td><td><b>DATA</b></td><td>HIGH</td><td>HIGH</td><td>HIGH</td><td>HIGH</td></tr>
	<tr><td>xx5</td><td>HIGH</td><td>HIGH</td><td>HIGH</td><td>HIGH</td><td><b>DATA</b></td><td>LOW</td><td>HIGH</td><td>HIGH</td><td>HIGH</td></tr>
	<tr><td>xx6</td><td>HIGH</td><td>HIGH</td><td>HIGH</td><td>HIGH</td><td><b>DATA</b></td><td>HIGH</td><td>LOW</td><td>HIGH</td><td>HIGH</td></tr>
	<tr><td>xx7</td><td>HIGH</td><td>HIGH</td><td>HIGH</td><td>HIGH</td><td><b>DATA</b></td><td>HIGH</td><td>HIGH</td><td>LOW</td><td>HIGH</td></tr>
	<tr><td>xx8</td><td>HIGH</td><td>HIGH</td><td>HIGH</td><td>HIGH</td><td><b>DATA</b></td><td>HIGH</td><td>HIGH</td><td>HIGH</td><td>LOW</td></tr>
  	<tr><td>xx9 (Ignore)</td><td>HIGH</td><td>HIGH</td><td>HIGH</td><td>HIGH</td><td><b>DATA</b></td><td>HIGH</td><td>HIGH</td><td>HIGH</td><td>HIGH</td></tr>
</table>

Connecting the ESP8266 to a pair of quadruple bus buffer gates like the [SN74HCT125N](https://www.newark.com/texas-instruments/sn74hct125n/non-inverting-buffer-dip-14/dp/68K1116?gclid=CjwKCAiAs8XiBRAGEiwAFyQ-ejVimsQAh_VLQYTXX-evTnmK4LatxY-gy9NNws8_nsnzISHsaOfKQhoCf4AQAvD_BwE&mckv=sYk7cQyMS_dc|pcrid|219870296115|plid||kword|sn74hct125n|matc) allows for enabling and disabling of a high speed data line for up to four channels.  For each channel of the buffer gates connect the D4/TX1 data line to the input A, then for each channel connect a corresponding ESP output (D0, D1, D2, D3, D5, D6, D7, D8) to the inverted enable /OE.  Finally, the output should be connected to both the pixel strand, and to ground through a fairly large resistance.  The resistance is necessary, as when the buffer chip channel is disabled it floats, and must be held at ground so the pixels can latch the proper data.

### Hackster.io
ESP8266 E1.31 Multiplexing Pixel Controller [project write-up](https://www.hackster.io/jasonspiva/esp8266-e1-31-multiplexing-pixel-controller-002072).

### Credits
Thanks to the code of others that made this possible...
 - [forkineye/E1.31](https://github.com/forkineye/E131)
 - [Makuna/NeoPixelBus](https://github.com/Makuna/NeoPixelBus/tree/master/src/internal)
    - [NeoEsp8266UartMethod.h](https://github.com/Makuna/NeoPixelBus/blob/master/src/internal/NeoEsp8266UartMethod.h)
    - [NeoEsp8266UartMethod.cpp](https://github.com/Makuna/NeoPixelBus/blob/master/src/internal/NeoEsp8266UartMethod.cpp)
 - [esp8266/util.h](https://github.com/esp8266/Arduino/blob/master/libraries/Ethernet/src/utility/util.h)
