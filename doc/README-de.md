# mGaugeESP

Bei dieser Software handelt es sich um den ESP  Anteil von mGauge.

## Was is mGauge

mGauge besteht aus zwei Komponenten die über Bluetooth (BLE) verbunden sind.

### ESP32 Gauge

Auf Basis eines ESP32-S3 realisiertes Messgerät mit 2 Funktionen.

Es wurde ein ESP32-S3 gewählt da er BLE 5.0 unterstützt und damit eine sichere verbindung zum mGaugeGUI gewährleistet.

- INA219 zur Messung von Gleichstrom
  
  - Spannung: 0..26V
  - Strom: 0..3.2A
  - Leistung: 0..83.2W
  - Anzeige 3.5" LCD für Strom und Spannung
- xy-FX35 als elektronischer Widertand
  mit einer Leistung von maximal 35W (1..25V, 0..5A)

### GUI

Qt PC Software zum Anzeigen und Aufzeichnen der Messdaten

- Plot der Messwerte
- Speichern der Messwerte als *.cvs Daten.

code ist im Repositoy   [mGaugeGUI](https://github.com/steand/mGaugeGUI) vorhanden.

