# Pocuter-Wordwatch
Wordwatch on Pocuter (ESP32-C3) with UART BLE connection 
<p>ESP32-C3 Pocuter Word clock</p>

<p>A small watch that displays the time in words in Dutch, English, French and 
German or digital on a tiny display.<br>The watch is able to receive the time 
via NTP from the internet. Settings can be controled via a webpage on a mobile 
or PC but also with Bluetooth LE.<br>If the watch is used stand-alone without 
connections it can be controlled with buttons.<br><br><br></p>
<p><img alt="Pocuters" src="Pics/img9.jpg" width="890"></p>
<p>The watch is built on a Pocuter One with a ESP32-C3 chip and OLED display 
built by <a href="https://www.pocuter.com/pocuter-one">www.pocuter.com</a><br>
The software is written in the Arduino IDE 1.8.19 and IDE 2.0.0<br><br>The 
software contains coding to use the:<br>1 Pocuter One with 96x64 pixels OLED colour display 
and the use of fonts<br>2 BLE nRF UART connection <br>3 Buttons<br>4 RGB 
LED<br>5 RTC for time<br>6 Storage of the settings on SD-card.<br>8 Menu driven with serial monitor, BLE and WIFI-html page<br>9 
Get time with NTP server via WIFI<br>10 Use of menu's to control the word clock<br>
<br><strong>First Use<br />
</strong>Insert a SD-card.<br> </p>
<p>If the clock is connected to the internet it 
will seek contact with a time server. The time zone is set to UTC+1 Amsterdam. <br />
<br>
To connect to a WIFI network a SSID and password must be entered.<br>
There are a few methods:<br>- Connect the Pocuter with a serial cable to a PC 
and use a serial terminal. I use the Arduino IDE or 
<a href="https://www.compuphase.com/software_termite.htm">Termite</a> as serial terminal.<br />
<br>
If you press I for information you get a menu. </p>
<p><img alt="Termite terminal" src="Pics/Termite.jpg" width="350" /><br />
<br />
-- USE the BLE connection with a UART serial terminal app. For IOS:&nbsp;
<a href="https://apps.apple.com/nl/app/ble-serial-pro/id1632245655?l=en">BLE 
Serial Pro</a> For android: see below<br><br />
In both cases <strong>send the letter I 
of Information and the menu shows up</strong>.<br />
Enter the first letter of the setting you want to changes followed with a code.r />
SoSome entries just toggle On and Off. Like the W to set WIFI Off or On. <br />
<br />
To change the SSID and password:r />
A<span class="auto-style1">my-ssid</span> 
 
and send this command. Eg AFRITZ!Box01<br />
Then&nbsp; B<span class="auto-style1"my password and send that password.<br />
These settings are stored on the SD-card.<br />
If the length of the SSID and/or password is less then 5 characters the WIFI 
will be turned off automatically.  <br />
Use a length of minimal 8 characters for SSID and password.<br />
Check in the menu (third row from the bottom) if WIFI and NTP are on.<br />
</span><br />
Enter @ to reset the Pocuter and connection will be made.<br></p>
<pA last resort:<br />
- In the source code in the subroutine: void 
setup() just above&nbsp;   StartWIFI_NTP();&nbsp; <br>&nbsp;&nbsp;&nbsp; strcpy(Mem.ssid,"<span class="auto-style1">My-SSID-SSID</span>");
<br>&nbsp;&nbsp;&nbsp; strcpy(Mem.password,"<span class="auto-style1">My 
password</span>"); <br>&nbsp;&nbsp;&nbsp; 
StartWIFI_NTP();&nbsp;&nbsp; Tekstprintln("WIFI started");&nbsp;&nbsp;&nbsp; // 
Start WIFI and NTP <br></p>
<p></p>
<p><img alt="Pocuter word clock" src="Pics/IMG_9451.JPG" width="600" /></p>
<p><strong>Control and settings of the clock</strong></If there is no WIFI connection the the time and display mode can be set with 
the buttons. <br />
Check in the menu if WIFI is OFF. The clock will start much quicker because it 
will not try to connect<br />
<br>Top 
Left: + 1 hour 1 hour<br>
Right bottom: + 1 minTop Right: Toggle between word or digital display<br></p>
<p>With the WIFI webpage or BLE UART terminal app the clock can be controlled.<br />
If there is a WIFI connection in the Digital display (Press Top right button) or 
in the menu the ip-address if printed<br />
Enter these numbers and dots in the browser of your mobile or PC where you type 
your internet addresses (URL).<br />
Or<br />
Open the BLE terminal app . Look for the WordClock to connect to and connect.<br />
BLE connection can be made with my app
<a href="https://ednieuw.home.xs4all.nl/BLESerial/BLESerialPRO.html">BLE Serial 
pro</a> on the
<a href="https://apps.apple.com/nl/app/ble-serial-pro/id1632245655?l=en">app 
store</a> for Apple IOS devices. <br />
For Android
<a href="https://play.google.com/store/apps/details?id=com.nordicsemi.nrfUARTv2&amp;hl=en&amp;gl=US"> 
&nbsp;nRF UART terminal program </a>and
<a href="https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal">
Serial Bluetooth terminal from Kai Morich</a><br>Unfortunately these Android 
apps can/do not read strings longer than 20 characters.<br>
<br />
Settings are set by entering the first letter of a command following by 
parameters if necessary.<br><br>For example: To set the colours of the fonts in the display 
to white enter: Q2<br>To shown random all four languages every minute send L4.<br />
<br />
Set the time by entering T130245. (130245 will also work)<br />
<br />
Turn off WIFI by sending a W</p>
<p>Reset the Pocuter with the letter @</p>
<p>Reset to default setting by send R send R<br /In the BLE connection the SSID and password will be shown. <br />
<br>
<br><br><br>
<img alt="Phone" src="Pics/IMG_9449.jpg" width="350" /><img alt="WIFI-BLE" src="Pics/IMG_9448.jpg" width="350"><br>Left the HTML page and 
on the right the BLE menuLE menu<br><br>Because not all 
Pocuter functionalities in the Pocuter library were described or could be found 
by me at the moment of writing this program several standard ESP32-C3 DEV 
functionality was used.<br>In this software version I only used the Pocuter 
Button and OLED 
screen functionality.<br> <br>Settings are stored on the SD-card.<The following libraries are used:</p>
<pre>#include &lt;Pocuter.h&gt;
#include &lt;NimBLEDevice.h&gt;      // For BLE communication  https://github.com/h2zero/NimBLE-Arduino
#include &lt;ESPNtpClient.h&gt;      // https://github.com/gmag11/ESPNtpClient
#include &lt;WiFi.h&gt;              // Used for NTP tme and web page
#include &lt;AsyncTCP.h&gt;          // Used for webpage   https://github.com/me-no-dev/ESPAsyncWebServer
#include &lt;ESPAsyncWebServer.h&gt; // Used for webpage   https://github.com/me-no-dev/ESPAsyncWebServer</pre>
<p>To compile the software some standard setting must be changed. <br>First copy 
the Pocuter libraries in the libraries folder where your sketches are saved. <br>In my 
case copy from here: c:\Program Files (x86)\Arduino\libraries\Pocuter\ to here 
<a href="../libraries/Pocuter/">c:\Users\ednie\Documents\Files\Arduino\libraries\Pocuter\</a><br>
Now we do not change the original Pocuter library and we keep all the 
non-standard Arduino libraries in one place. place.</p>
<p>To be able to compile the esp32 Arduino boards must be installed and the 
ESP32 C3 DEV board selected</p>
<p><img alt="ESP32-c3 DEV board" src="Pics/img6.gif"></p>
<p><brOne change must be made in the file: 
"C:\Users\ednie\Documents\Files\Arduino\libraries\Pocuter\include\PocuterLibConfig.h"<br>
Because we do not use the Pocuter WIFI library we have to disable the WIFI to 
avoid a compilation error of the ESP32 WIFI library.<br>So remove the // before 
#define POCUTER_DISABLE_WIFI to disable the Pocuter WIFI lbrary</p>
<pre>
/* Dont use WIFI functions */
 #define POCUTER_DISABLE_WIFI</pre>
When compiling the program these are the last lines:<pre>Successfully created esp32c3 image. i"C:\\Users\\ednie\\AppData\\Local\\Arduino15\\packages\\esp32\\hardware\\esp32\\2.0.5/tools/gen_esp32part.exe" -q "C:\\Users\\ednie\\AppData\\Local\\Temp\\arduino_build_331013/partitions.csv" "C:\\Users\\ednie\\AppData\\Local\\Temp\\arduino_build_331013/PocuterWordClockV043.ino.partitions.bin"
Multiple libraries were found for "Pocuter.h"
Used: C:\Users\ednie\Documents\Files\Arduino\libraries\Pocuter
Not used: C:\Program Files (x86)\Arduino\libraries\Pocuter
Multiple libraries were found for "WiFi.h"
Used: C:\Users\ednie\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.5\libraries\WiFi
Not used: C:\Users\ednie\Documents\Files\Arduino\libraries\WiFiNINA
Not used: C:\Program Files (x86)\Arduino\libraries\WiFi
Using library Pocuter in folder: C:\Users\ednie\Documents\Files\Arduino\libraries\Pocuter (legacy)
Using library NimBLE-Arduino at version 1.4.1 in folder: C:\Users\ednie\Documents\Files\Arduino\libraries\NimBLE-Arduino 
Using library ESPNTP in folder: C:\Users\ednie\Documents\Files\Arduino\libraries\ESPNTP (legacy)
Using library WiFi at version 2.0.0 in folder: C:\Users\ednie\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.5\libraries\WiFi 
Using library Ticker at version 2.0.0 in folder: C:\Users\ednie\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.5\libraries\Ticker 
Using library AsyncTCP-master at version 1.1.1 in folder: C:\Users\ednie\Documents\Files\Arduino\libraries\AsyncTCP-master 
Using library ESPAsyncWebServer-master at version 1.2.3 in folder: C:\Users\ednie\Documents\Files\Arduino\libraries\ESPAsyncWebServer-master 
Using library FS at version 2.0.0 in folder: C:\Users\ednie\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.5\libraries\FS 
"C:\\Users\\ednie\\AppData\\Local\\Arduino15\\packages\\esp32\\tools\\riscv32-esp-elf-gcc\\gcc8_4_0-esp-2021r2-patch3/bin/riscv32-esp-elf-size" -A "C:\\Users\\ednie\\AppData\\Local\\Temp\\arduino_build_331013/PocuterWordClockV043.ino.elf"
Sketch uses 1258336 bytes (40%) of program storage space. Maximum is 3145728 bytes. bytes.
Global variables use 43908 bytes (13%) of dynamic memory, leaving 283772 bytes for local variables. Maximum is 327680 bytes.
</pre>
<p>&nbsp;</p>
<p><strong>Some lessons learned:</strong></p>
<ul>Use&nbsp;&nbsp; pocuter-&gt;begin(PocuterDisplay::BUFFER_MODE_DOUBLE_BUFFER);&nbsp; 
	for a fast screen display</li>
	<li>Use USBSerial instead of USBSerial.&nbsp; Serial,print is USBSerial.print</li>
	<li>Saving of a file in ESP32 memory with EEPROM, SPIFFS or Preferences 
	libraries in the Pocuter ESP32 memory does not work and it crashes at this 
	moment dd okt2022</li>
</ul>
<p>Ed Nieuwenhuys, October 2022&nbsp;2&nbsp;</p>



