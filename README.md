🐇 WhiteRabbit — Bluetooth Jammer

ESP32-C6 + Dual NRF24L01 RF Disruption Tool
Built by x0jacob0x | Based on RF-Clown by CiferTech


⚠️ Disclaimer
This project is intended for educational and research purposes only. Jamming wireless signals may be illegal in your country or region. The author takes no responsibility for misuse. Always operate within the bounds of your local laws.

📖 About
WhiteRabbit is a Bluetooth jammer built on the ESP32-C6-WROOM-1 using two NRF24L01 radio modules running simultaneously to maximize 2.4 GHz channel disruption. This project is heavily inspired by and based upon the excellent RF-Clown project by CiferTech — huge thanks to them for the original work.

🛠️ Hardware

MCU: ESP32-C6-WROOM-1
Radios: 2× NRF24L01 (or NRF24L01+PA+LNA for extended range)


🔌 Wiring / Pin Map
Both NRF24L01 modules share the same SPI bus (SCK, MOSI, MISO) but have individual CE and CSN pins for independent control.
SignalRadio 1Radio 2VCC3V3 shared3V3 sharedGNDGND sharedGND sharedCEGPIO10GPIO11CSNGPIO17GPIO16SCKGPIO6 sharedGPIO6 sharedMOSIGPIO7 sharedGPIO7 sharedMISOGPIO2 sharedGPIO2 shared

Note: NRF24L01 modules run on 3.3V — do not connect to 5V or you will damage them. Adding a 10µF decoupling capacitor across VCC/GND on each module is strongly recommended for stability.


🚀 Getting Started
Prerequisites

Arduino IDE or PlatformIO
ESP32 board support package installed
RF24 Library by TMRh20

Installation

Clone this repository:

bash   git clone https://github.com/x0jacob0x/WhiteRabbit.git
   cd WhiteRabbit

Install the RF24 library via Arduino Library Manager or PlatformIO.
Open the project, select ESP32C6 Dev Module as your board, and flash.


📡 How It Works
WhiteRabbit uses both NRF24L01 modules to rapidly hop across Bluetooth channels (2402–2480 MHz) and transmit noise, disrupting Bluetooth pairing and communication in the vicinity. The dual-radio configuration allows for wider simultaneous channel coverage compared to a single-module setup.

🙏 Credits & Acknowledgements
This project would not exist without the foundational work of:
► CiferTech — Original RF-Clown Project
🐙 GitHubgithub.com/cifertech/RF-Clown💬 Twitter@CiferTech☕ Patreonpatreon.com/cifertech📧 EmailCiferTech@gmail.com

👤 Author
x0jacob0x

📄 License
This project follows the same open spirit as RF-Clown. Please credit both x0jacob0x and CiferTech if you build upon this work.
