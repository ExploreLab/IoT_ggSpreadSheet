/*	Created by Mr.Jukrapun Chitpong, 2018
	Everyone to sees this
	All Rights Reserved.
	Github: https://github.com/ExploreLab

	Write to Google Sheets using REST API.
	Can be used with ESP32/ESP8266 & other embedded IoT devices.

	Use this file with the ESP32/ESP8266 library WiFiClientSecure
	 
	doGet() and doPost() need the spreadsheet ID. Cannot use "active spreadsheet" here since

	 This Script for connect between ESP32/ESP8266 with Google Apps Script
	   Jukrapun Chitpong - facebook.com/eeeg.ch
   */

var SS = SpreadsheetApp.openById('Your_SheetID');
var sheet = SS.getSheetByName('Sheet1');
var str = "";

function doGet(e){
	var FIELD1 = e.parameter.FIELD1; 
	var FIELD2 = e.parameter.FIELD2; 
  
	if (FIELD1 !== undefined || FIELD2 !== undefined){
		addProduct(FIELD1, FIELD2); 
		str = "Sent: "+ now;
		return ContentService.createTextOutput(str);
	}
}

//https://developers.google.com/apps-script/reference/spreadsheet/sheet
function addProduct(FIELD1, FIELD2) {
  var sheet = SpreadsheetApp.getActiveSheet();
  var Time = new Date(); 
  sheet.appendRow([Time, FIELD1, FIELD2]);
  //sheet.deleteRows(6, 10);
  //Logger.log(values)
}
 
