# IoT_ggSpreadSheet
This project shows how to Write to Google Sheets using REST API.Can be used with ESP32/ESP8266 &amp; other embedded IoT devices.
![alt text](https://github.com/ExploreLab/IoT_ggSpreadSheet/blob/master/ESP_GG_Script.jpg)

Based on video: coming soon on My channel [https://www.youtube.com/channel/UCquZEdTFMHx1FPNgaFnAMLQ].

## How to create Google Sheets and Google Apps Script
```
1. Create Sheets.
2. Copy Your_SheetID.
   https://docs.google.com/spreadsheets/d/Your_SheetID/edit#gid=0
3. Click on menu Tools > Script editor.
4. Copy and Paste code from ggScript_ggSpreadSheet.gs to Code.gs .
5. Change Your_SheetID* from Google Sheet URL (Line. 17).
6. Click on menu Publish > Deploy as web app ...
7. Change "Who has access to the app:" to "Anyone, even anonymous", then click "OK" 
8. Aollow Google Account Permissions.
9. Copy Current web app URL:
  example https://script.google.com/macros/s/AKfycbzPYa_qeKlwdgJi9ZlkGEX-Fnz2t26hh_S-rlotnULNABCDEFG/exec
  GScriptId = AKfycbzPYa_qeKlwdgJi9ZlkGEX-Fnz2t26hh_S-rlotnULNABCDEFG
```

## How to use IoT_ggSpreadSheet.ino
```
1. Download and open file "IoT_ggSpreadSheet.ino" using Arduino IDE.
2. Change YourSSID, YourPASSWORD (Line 31-32).
3. Change Your GScriptId (Line 79).
4. Verify and Upload.
5. ESP8266 send data to Google Apps Script > Google Sheet
6. Successfully.
```
