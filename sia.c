/*
   SIA-HS Alarm Monitoring Service
   Copyright (C) Wilco Baan Hofman <wilco@baanhofman.nl> 2012

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "sia.h"

const struct {
	const char *code;
	const char *string;
	const char *description;
} sia_codes[] = {
	{ "AA", "Alarm panel substitution",
	  "An attempt to substitute an alternate alarm panel for a secure panel has been made" },
	{ "AB", "User Abort",
	  "An event message was not sent due to User action" },
	{ "AN", "Analog Restore",
	  "An analog fire sensor has been restored to normal operation" },
	{ "AR", "AC Restore",
	  "AC Power has been restored" },
	{ "AS", "Analog Service",
	  "An analog fire sensor needs to be cleaned or calibrated" },
	{ "AT", "AC Trouble",
	  "AC power has been failed" },
	{ "BA", "Burglary Alarm",
	  "Burglary zone has been violated while armed" },
	{ "BB", "Burglary Bypass",
	  "Burglary zone has been bypassed" },
	{ "BC", "Burglary Cancel",
	  "Alarm has been cancelled by authorized user" },
	{ "BD", "Swinger Trouble",
	  "A non-fire zone has been violated after a Swinger Shutdown on the zone" },
	{ "BE", "Swinger Trouble restore",
	  "A non-fire zone restores to normal from a Swinger Trouble state" },
	{ "BG", "Unverified Event - Burglary",
	  "A point assigned to a Cross Point group has gone into alarm but the Cross Point remained normal" },
	{ "BH", "Burglary Alarm restore",
	  "Burglary Alarm condition eliminated" },
	{ "BJ", "Burglary Trouble restore",
	  "Burglary Trouble condition eliminated" },
	{ "BM", "Burglary Alarm cross point",
	  "Burglary alarm w/cross point also in alarm - alarm verified" },
	{ "BR", "Burglary Restore",
	  "Alarm/trouble condition has been eliminated" },
	{ "BS", "Burglary Supervisory",
	  "Unsafe intrusion detection system condition" },
	{ "BT", "Burglary Trouble",
	  "Burglary zone disabled by fault" },
	{ "BU", "Burglary Unbypass",
	  "Zone bypass has been removed" },
	{ "BV", "Burglary Verified",
	  "A burglary alarm has occurred and been verified within programmed conditions. (zone or point not sent)" },
	{ "BX", "Burglary Test",
	  "Burglary zone activated during testing" },
	{ "BZ", "Missing Supervision",
	  "A non-fire Supervisory point has gone missing" },
	{ "CA", "Automatic Closing",
	  "System armed automatically" },
	{ "CD", "Closing delinquent",
	  "The system has not been armed for a programmed amount of time" },
	{ "CE", "Closing extend",
	  "Extend closing time" },
	{ "CF", "Forced Closing",
	  "System armed, some zones not ready" },
	{ "CG", "Close Area",
	  "System has been partially armed" },
	{ "CI", "Fail to Close",
	  "An area has not been armed at the end of the closing window" },
	{ "CL", "Late Close",
	  "An area was armed after the closing window" },
	{ "CK", "Early Close",
	  "An area was armed before the closing window" },
	{ "CL", "Closing Report",
	  "System armed, normal" },
	{ "CM", "Missing Alarm - Recent Closing",
	  "A point has gone missing within 2 minutes of closing" },
	{ "CO", "Command Sent",
	  "A command has been sent to an expansion/peripheral device" },
	{ "CP", "Automatic Closing",
	  "System armed automatically" },
	{ "CQ", "Remote Closing",
	  "The system was armed from a remote location" },
	{ "CS", "Closing Keyswitch",
	  "Account has been armed by keyswitch" },
	{ "CT", "Late to Open",
	  "System was not disarmed on time" },
	{ "CW", "Was Force Armed",
	  "Header for a force armed session, forced point msgs may follow" },
	{ "CX", "Custom Function Executed",
	  "The panel has executed a preprogrammed set of instructions" },
	{ "CZ", "Point Closing",
	  "A point, as opposed to a whole area or account, has closed" },
	{ "DA", "Card Assigned",
	  "An access ID has been added to the controller" },
	{ "DB", "Card Deleted",
	  "An access ID has been deleted from the controller" },
	{ "DC", "Access Closed",
	  "Access to all users prohibited" },
	{ "DD", "Access Denied",
	  "Access denied, unknown code" },
	{ "DE", "Request to Enter",
	  "An access point was opened via a Request to Enter device" },
	{ "DF", "Door Forced",
	  "Door opened without access request" },
	{ "DG", "Access Granted",
	  "Door access granted" },
	{ "DH", "Door Left Open - Restoral",
	  "An access point in a Door Left Open state has restored" },
	{ "DI", "Access Denied - Passback",
	  "Access denied because credential has not exited area before attempting to re-enter same area" },
	{ "DJ", "Door Forced - Trouble",
	  "An access point has been forced open in an unarmed area" },
	{ "DK", "Access Lockout",
	  "Access denied, known code" },
	{ "DL", "Door Left Open - Alarm",
	  "An open access point when open time expired in an armed area" },
	{ "DM", "Door Left Open - Trouble",
	  "An open access point when open time expired in an unarmed area" },
	{ "DN", "Door Left Open",
	  "An access point was open when the door cycle time expired" },
	{ "DO", "Access Open",
	  "Access to authorized users allowed" },
	{ "DP", "Access Denied - Unauthorized Time",
	  "An access request was denied because the request is occurring outside the user’s authorized time window(s)" },
	{ "DQ", "Access Denied - Unauthorized Arming State",
	  "An access request was denied because the user was not authorized in this area when the area was armed" },
	{ "DR", "Door Restoral",
	  "Access alarm/trouble condition eliminated" },
	{ "DS", "Door Station",
	  "Identifies door for next report" },
	{ "DT", "Access Trouble",
	  "Access system trouble" },
	{ "DU", "Dealer ID",
	  "Dealer ID number" },
	{ "DV", "Access Denied - Unauthorized Entry Level",
	  "An access request was denied because the user is not authorized in this area" },
	{ "DW", "Access Denied - Interlock",
	  "An access request was denied because the doors associated interlock point is open" },
	{ "DX", "Request to Exit",
	  "An access point was opened via a Request to Exit device" },
	{ "DY", "Door Locked",
	  "The door’s lock has been engaged" },
	{ "DZ", "Access Denied - Door Secured",
	  "An access request was denied because the door has been placed in an Access Closed state" },
	{ "EA", "Exit Alarm",
	  "An exit zone remained violated at the end of the exit delay period" },
	{ "EE", "Exit Error",
	  "An exit zone remained violated at the end of the exit delay period ?! Trouble?" },
	{ "EJ", "Expansion Tamper Restore",
	  "Expansion device tamper restoral" },
	{ "EM", "Expansion Device Missing",
	  "Expansion device missing" },
	{ "EN", "Expansion Missing Restore",
	  "Expansion device communications re-established" },
	{ "ER", "Expansion Restoral",
	  "Expansion device trouble eliminated" },
	{ "ES", "Expansion Device Tamper",
	  "Expansion device enclosure tamper" },
	{ "ET", "Expansion Trouble",
	  "Expansion device trouble" },
	{ "EX", "External Device Condition",
	  "A specific reportable condition is detected on an external device" },
	{ "EZ", "Missing Alarm - Exit Error",
	  "A point remained missing at the end of the exit delay period" },
	{ "FA", "Fire Alarm",
	  "Fire condition detected" },
	{ "FB", "Fire Bypass",
	  "Fire zone has been bypassed" },
	{ "FC", "Fire Cancel",
	  "A Fire Alarm has been cancelled by an authorized person" },
	{ "FG", "Unverified Event - Fire",
	  "A point assigned to a Cross Point group has gone into alarm but the Cross Point remained normal" },
	{ "FH", "Fire Alarm Restore",
	  "Fire alarm condition eliminated" },
	{ "FI", "Fire Test Begin",
	  "The transmitter area's fire test has begun" },
	{ "FJ", "Fire Trouble Restore",
	  "Fire trouble condition eliminated" },
	{ "FK", "Fire Test End",
	  "The transmitter area's fire test has ended" },
	{ "FL", "Fire Alarm Silenced",
	  "The fire panel’s sounder was silenced by command" },
	{ "FM", "Fire Alarm - Cross point",
	  "Fire Alarm with Cross Point also in alarm verifying the Fire Alarm" },
	{ "FQ", "Fire Supervisory Trouble Restore",
	  "A fire supervisory zone that was in trouble condition has now restored to normal" },
	{ "FR", "Fire Restoral",
	  "A fire supervisory zone that was in trouble condition has now restored to normal" },
	{ "FS", "Fire Supervisory",
	  "Unsafe fire detection system condition" },
	{ "FT", "Fire Trouble",
	  "Fire Zone disabled by fault" },
	{ "FU", "Fire Unbypass",
	  "Fire Bypass has been removed" },
	{ "FV", "Fire Supervision Restore",
	  "A fire supervision zone that was in alarm has restored to normal" },
	{ "FW", "Fire Supervisory Trouble",
	  "A fire supervisory zone is now in a trouble condition" },
	{ "FX", "Fire Test",
	  "Fire zone activated during test" },
	{ "FY", "Missing Fire Trouble",
	  "A fire point is now logically missing" },
	{ "FZ", "Missing Fire Supervision",
	  "A Fire Supervisory point has gone missing" },
	{ "GA", "Gas Alarm",
	  "Gas alarm condition detected" },
	{ "GB", "Gas Bypass",
	  "Gas zone has been bypassed" },
	{ "GH", "Gas Alarm Restore",
	  "Gas alarm condition eliminated" },
	{ "GJ", "Gas Trouble Restore",
	  "Gas trouble condition eliminated" },
	{ "GR", "Gas Restore",
	  "Gas alarm/trouble condition has been eliminated" },
	{ "GS", "Gas Supervisory",
	  "Unsafe gas detection system condition" },
	{ "GT", "Gas Trouble",
	  "Gas zone disabled by fault" },
	{ "GU", "Gas Unbypass",
	  "Gas bypass has been removed" },
	{ "GX", "Gas Test",
	  "Gas zone activated during test" },
	{ "HA", "Holdup Alarm",
	  "Silent alarm, user under duress" },
	{ "HB", "Holdup Bypass",
	  "Holdup zone has been bypassed" },
	{ "HH", "Holdup Alarm Restore",
	  "Holdup alarm condition eliminated" },
	{ "HJ", "Holdup Trouble Restore",
	  "Holdup trouble condition eliminated" },
	{ "HR", "Holdup Restoral",
	  "Holdup alarm/trouble condition has been eliminated" },
	{ "HS", "Holdup Supervisory",
	  "Unsafe holdup system condition" },
	{ "HT", "Holdup Trouble",
	  "Holdup zone disabled by fault" },
	{ "HU", "Holdup Unbypass",
	  "Holdup bypass has been removed" },
	{ "IA", "Equipment Failure Condition",
	  "A specific, reportable condition is detected on a device" },
	{ "IR", "Equipment Fail - Restoral",
	  "The equipment condition has been restored to normal" },
	{ "JA", "User Code Tamper",
	  "Too many unsuccessful attempts have been made to enter a user ID" },
	{ "JD", "Date Changed",
	  "The date was changed in the transmitter/receiver" },
	{ "JH", "Holiday Changed",
	  "The transmitter's holiday schedule has been changed" },
	{ "JK", "Latchkey Alert",
	  "A designated user passcode has not been entered during a scheduled time window" },
	{ "JL", "Log Treshold",
	  "The transmitter's log memory has reached its threshold level" },
	{ "JO", "Log Overflow",
	  "The transmitter's log memory has overflowed" },
	{ "JP", "User on Premises",
	  "A designated user passcode has been used to gain access to the premises." },
	{ "JR", "Schedule Executed",
	  "An automatic scheduled event was executed" },
	{ "JS", "Schedule Changed",
	  "An automatic schedule was changed" },
	{ "JT", "Time Changed",
	  "The time was changed in the transmitter/receiver" },
	{ "JV", "User Code Changed",
	  "A user's code has been changed" },
	{ "JX", "User Code Deleted",
	  "A user's code has been removed" },
	{ "JY", "User Code Added",
	  "A user’s code has been added" },
	{ "JZ", "User Level Set",
	  "A user's authority level has been set" },
	{ "KA", "Heat Alarm",
	  "High temperature detected on premise" },
	{ "KB", "Heat Bypass",
	  "Heat zone has been bypassed" },
	{ "KH", "Heat Alarm Restore",
	  "Heat alarm condition eliminated" },
	{ "KJ", "Heat Trouble Restore",
	  "Heat trouble condition eliminated" },
	{ "KR", "Heat Restoral",
	  "Heat alarm/trouble condition eliminated" },
	{ "KS", "Heat Supervisory",
	  "Unsafe heat detection system condition" },
	{ "KT", "Heat Trouble",
	  "Heat zone disabled by fault" },
	{ "KU", "Heat Unbypass",
	  "Heat zone bypass has been removed" },
	{ "LB", "Local Program",
	  "Begin local programming" },
	{ "LD", "Local Program Denied",
	  "Local program access code incorrect" },
	{ "LE", "Listen-in Ended",
	  "The listen-in session has been terminated" },
	{ "LF", "Listen-In Begin",
	  "The listen-in session with the RECEIVER has begun" },
	{ "LR", "Phone Line Restoral",
	  "Phone line restored to service" },
	{ "LS", "Local Program Success",
	  "Local programming successful" },
	{ "LT", "Phone Line Trouble",
	  "Phone line trouble report" },
	{ "LU", "Local Program Fail",
	  "Local programming unsuccessful" },
	{ "LX", "Local Program Ended",
	  "A local programming session has been terminated" },
	{ "MA", "Medical Alarm",
	  "Emergency assistance request" },
	{ "MB", "Medical Bypass",
	  "Medical zone has been bypassed" },
	{ "MH", "Medical Alarm Restore",
	  "Medical alarm condition eliminated" },
	{ "MI", "Message",
	  "A canned message is being sent? Say What?" },
	{ "MJ", "Medical Trouble Restore",
	  "Medical Trouble condition eliminated" },
	{ "MR", "Medical Restoral",
	  "Medical alarm/trouble condition has been eliminated" },
	{ "MS", "Medical Supervisory",
	  "Unsafe medical system condition exists" },
	{ "MT", "Medical Trouble",
	  "Medical zone disabled by fault" },
	{ "MU", "Medical Unbypass",
	  "Medical bypass has been removed" },
	{ "NA", "No Activity",
	  "There has been no zone activity for a programmed amount of time" },
	{ "NC", "Network Condition",
	  "A communications network has a specific reportable condition" },
	{ "NF", "Forced Perimeter Alarm",
	  "Some zones/points not ready" },
	{ "NL", "Perimeter Armed",
	  "An area has been perimeter armed" },
	{ "NM", "Perimeter Armed - User Defined",
	  "A user defined area has been perimeter armed" },
	{ "NR", "Network Restoral",
	  "A communications network has returned to normal operation" },
	{ "NS", "Activity Resumed",
	  "A zone has detected activity after an alert" },
	{ "NT", "Network Failure",
	  "A communications network has failed" },
	{ "OA", "Automatic Opening",
	  "System has disarmed automatically" },
	{ "OC", "Cancel Report",
	  "Untyped zone cancel" },
	{ "OG", "Open Area",
	  "System has been partially disarmed" },
	{ "OH", "Early to Open from Alarm",
	  "An area in alarm was disarmed before the opening window" },
	{ "OI", "Fail to Open",
	  "An area has not been armed at the end of the opening window" },
	{ "OJ", "Late Open",
	  "An area was disarmed after the opening window" },
	{ "OK", "Early Open",
	  "An area was disarmed before the opening window" },
	{ "OL", "Late to Open from Alarm",
	  "An area in alarm was disarmed after the opening window" },
	{ "OP", "Opening Report",
	  "Account was disarmed" },
	{ "OQ", "Remote Opening",
	  "The system was disarmed from a remote location" },
	{ "OR", "Disarm From Alarm",
	  "Account in alarm was reset/disarmed" },
	{ "OS", "Opening Keyswitch",
	  "Account has been disarmed by keyswitch" },
	{ "OT", "Late to Close",
	  "System was not armed on time" },
	{ "OU", "Output State - Trouble",
	  "An output on a peripheral device or NAC is not functioning" },
	{ "OV", "Output State - Restore",
	  "An output on a peripheral device or NAC is back to normal operation" },
	{ "OZ", "Point Opening",
	  "A point, rather than a full area or account, disarmed" },
	{ "PA", "Panic Alarm",
	  "Panic emergency assistance request, manually activated" },
	{ "PB", "Panic Bypass",
	  "Panic zone has been bypassed" },
	{ "PH", "Panic Alarm Restore",
	  "Panic alarm condition eliminated" },
	{ "PJ", "Panic Trouble Restore",
	  "Panic trouble condition eliminated" },
	{ "PR", "Panic Restoral",
	  "Panic alarm/trouble condition eliminated" },
	{ "PS", "Panic Supervisory",
	  "Unsafe panic system condition exists" },
	{ "PT", "Panic Trouble",
	  "Panic zone disabled by fault" },
	{ "PU", "Panic Unbypass",
	  "Panic zone bypass has been removed" },
	{ "QA", "Emergency Alarm",
	  "Emergency assistance request" },
	{ "QB", "Emergency Bypass",
	  "Emergency zone has been bypassed" },
	{ "QH", "Emergency Alarm Restore",
	  "Emergency alarm condition eliminated" },
	{ "QJ", "Emergency Trouble Restore",
	  "Emergency trouble condition eliminated" },
	{ "QR", "Emergency Restoral",
	  "Emergency alarm/trouble condition eliminated" },
	{ "QS", "Emergency Supervisory",
	  "Unsafe emergency system condition exists" },
	{ "QT", "Emergency Trouble",
	  "Emergency zone disabled by fault" },
	{ "QU", "Panic Unbypass",
	  "Emergency zone bypass has been removed" },
	{ "RA", "Remote Programmer Call Failed",
	  "Transmitter failed to communicate with the remote programmer" },
	{ "RB", "Remote Program Begin",
	  "Remote programming session initiated " },
	{ "RC", "Relay Close",
	  "A relay has energized" },
	{ "RD", "Remote Program Denied",
	  "Remote Program access passcode incorrect" },
	{ "RN", "Remote Reset",
	  "A TRANSMITTER was reset via a remote programmer" },
	{ "RP", "Automatic Test",
	  "Automatic communication test report" },
	{ "RR", "Power Up",
	  "System lost power, is now restored" },
	{ "RS", "Remote Program Success",
	  "Remote programming successful" },
	{ "RT", "Data Lost",
	  "Dialer data lost, transmission error" },
	{ "RU", "Remote Program Fail",
	  "Remote programming unsuccessful" },
	{ "RX", "Manual Test",
	  "Manual communication test report" },
	{ "RY", "Test Off Normal",
	  "Test signal(s) indicates abnormal condition(s) exist" },
	{ "SA", "Sprinkler Alarm",
	  "Sprinkler flow condition exists" },
	{ "SB", "Sprinkler Bypass",
	  "Sprinkler zone has been bypassed" },
	{ "SC", "Change of State",
	  "An expansion/peripheral device is reporting a new condition or state change" },
	{ "SH", "Sprinkler Alarm Restore",
	  "Sprinkler alarm condition eliminated" },
	{ "SJ", "Sprinkler Trouble Restore",
	  "Sprinkler trouble condition eliminated" },
	{ "SR", "Sprinkler Restoral",
	  "Sprinkler alarm/trouble condition eliminated" },
	{ "SS", "Sprinkler Supervisory",
	  "Unsafe sprinkler system condition exists" },
	{ "ST", "Sprinkler Trouble",
	  "Sprinkler zone disabled by fault" },
	{ "SU", "Sprinkler Unbypass",
	  "Sprinkler zone bypass has been removed" },
	{ "TA", "Tamper Alarm",
	  "Alarm equipment enclosure opened" },
	{ "TB", "Tamper Bypass",
	  "Tamper detection has been bypassed" },
	{ "TC", "All Points Tested",
	  "All points tested" },
	{ "TE", "Test End",
	  "Communicator restored to operation" },
	{ "TH", "Tamper Alarm Restore",
	  "An Expansion Device’s tamper switch restores to normal from an Alarm state" },
	{ "TJ", "Tamper Trouble Restore",
	  "An Expansion Device’s tamper switch restores to normal from a Trouble state" },
	{ "TP", "Walk Test Point",
	  "This point was tested during a Walk Test" },
	{ "TR", "Tamper Restoral",
	  "Alarm equipment enclosure has been closed" },
	{ "TS", "Test Start",
	  "Communicator taken out of operation" },
	{ "TT", "Tamper trouble",
	  "Equipment enclosure opened in disarmed state" },
	{ "TU", "Tamper Unbypass",
	  "Tamper detection bypass has been removed" },
	{ "TW", "Area Watch Start",
	  "Area watch feature has been activated" },
	{ "TX", "Test Report",
	  "An unspecified (manual or automatic) communicator test" },
	{ "TZ", "Area Watch End",
	  "Area watch feature has been deactivated" },
	{ "UA", "Untyped Zone Alarm",
	  "Untyped zone has been violated while armed" },
	{ "UB", "Untyped Zone Bypass",
	  "Untyped zone has been bypassed" },
	{ "UG", "Unverified Event - Untyped",
	  "A point assigned to a Cross Point group has gone into alarm but the Cross Point remained normal" },
	{ "UH", "Untyped Zone Alarm Restore",
	  "Untyped Alarm condition eliminated" },
	{ "UJ", "Untyped Zone Trouble restore",
	  "Untyped Trouble condition eliminated" },
	{ "UM", "Untyped ZoneAlarm cross point",
	  "Untyped alarm w/cross point also in alarm - alarm verified" },
	{ "UR", "Untyped Zone Restore",
	  "Untyped Alarm/trouble condition has been eliminated" },
	{ "US", "Untyped Zone Supervisory",
	  "Unsafe untyped zone system condition" },
	{ "UT", "Untyped Zone Trouble",
	  "Untyped zone disabled by fault" },
	{ "UU", "Untyped Zone Unbypass",
	  "Untyped zone bypass has been removed" },
	{ "UX", "Undefined",
	  "An undefined alarm condition has occurred" },
	{ "UY", "Untyped Missing Trouble",
	  "A point or device which was not armed is now logically missing" },
	{ "UZ", "Untyped Missing Alarm",
	  "A point or device which was armed is now logically missing" },
	{ "VI", "Printer Paper In",
	  "TRANSMITTER or RECEIVER paper in" },
	{ "VO", "Printer Paper Out",
	  "TRANSMITTER or RECEIVER paper out" },
	{ "VR", "Printer Restore",
	  "TRANSMITTER or RECEIVER trouble restored" },
	{ "VT", "Printer Trouble",
	  "TRANSMITTER or RECEIVER trouble" },
	{ "VX", "Printer Test",
	  "TRANSMITTER or RECEIVER test" },
	{ "VY", "Printer Online",
	  "RECEIVER’S printer is now online" },
	{ "VZ", "Printer Offline",
	  "RECEIVER’S printer is now offline" },
	{ "WA", "Water Alarm",
	  "Water detected at protected premises" },
	{ "WB", "Water Bypass",
	  "Water detection has been bypassed" },
	{ "WH", "Water Alarm Restore",
	  "Water alarm condition eliminated" },
	{ "WJ", "Water Trouble Restore",
	  "Water trouble condition eliminated" },
	{ "WR", "Water Restoral",
	  "Water alarm/trouble condition has been eliminated" },
	{ "WS", "Water Supervisory",
	  "Water unsafe water detection system condition" },
	{ "WT", "Water Trouble",
	  "Water zone disabled by fault" },
	{ "WU", "Water Unbypass",
	  "Water detection bypass has been removed" },
	{ "XA", "Extra Account Report",
	  "CS RECEIVER has received an event from a non-existent account" },
	{ "XE", "Extra Point",
	  "Panel has sensed an extra point not specified for this site" },
	{ "XF", "Extra RF Point",
	  "Panel has sensed an extra RF point not specified for this site" },
	{ "XH", "RF Interference Restoral",
	  "A radio device is no longer detecting RF Interference" },
	{ "XI", "Sensor Reset",
	  "A user has reset a sensor" },
	{ "XJ", "RF Receiver Tamper Restoral",
	  "A Tamper condition at a premises RF Receiver has been restored" },
	{ "XL", "Low Received Signal Strength",
	  "The RF signal strength of a reported event is below minimum level" },
	{ "XM", "Missing Alarm - Cross point",
	  "Missing Alarm verified by Cross Point in Alarm (or missing)" },
	{ "XQ", "RF Interference",
	  "A radio device is detecting RF Interference" },
	{ "XR", "Transmitter Battery Restoral",
	  "Low battery has been corrected" },
	{ "XS", "RF Receiver Tamper",
	  "A Tamper condition at a premises receiver is detected" },
	{ "XT", "Transmitter Battery Trouble",
	  "Low battery in wireless transmitter" },
	{ "XW", "Forced Point",
	  "A point was forced out of the system at arm time" },
	{ "XX", "Fail to Test",
	  "A specific test from a panel was not received" },
	{ "YA", "Bell Fault",
	  "A trouble condition has been detected on a Local Bell, Siren, or Annunciator" },
	{ "YB", "Busy Seconds",
	  "Percent of time receiver's line card is on-line" },
	{ "YC", "Communications Fail",
	  "RECEIVER and TRANSMITTER communicatie failure" },
	{ "YD", "Receiver Line Card Trouble",
	  "A line card identified by the passed address is in trouble" },
	{ "YE", "Receiver Line Card Restored",
	  "A line card identified by the passed address is restored" },
	{ "YF", "Parameter Checksum Fail",
	  "System data corrupted" },
	{ "YG", "Parameter Changed",
	  "A TRANSMITTER’S parameters have been changed" },
	{ "YH", "Bell Restored",
	  "A trouble condition has been restored on a Local Bell, Siren, or Annunciator" },
	{ "YI", "Overcurrent Trouble",
	  "An Expansion Device has detected an overcurrent condition" },
	{ "YJ", "Overcurrent Restore",
	  "An Expansion Device has restored from an overcurrent condition" },
	{ "YK", "Communications Restoral",
	  "TRANSMITTER has resumed communication with a RECEIVER" },
	{ "YM", "System Battery Missing",
	  "TRANSMITTER/RECEIVER battery is missing" },
	{ "YN", "Invalid Report",
	  "TRANSMITTER has sent a packet with invalid data" },
	{ "YO", "Unknown Message",
	  "An unknown message was received from automation or the printer" },
	{ "YP", "Power Supply Trouble",
	  "TRANSMITTER/RECEIVER has a problem with the power supply" },
	{ "YQ", "Power Supply Restored",
	  "TRANSMITTER'S/RECEIVERS'S power supply has been restored" },
	{ "YR", "System Battery Restoral",
	  "Low battery has been corrected" },
	{ "YS", "Communications Trouble",
	  "RECEIVER and TRANSMITTER fail to communicate" },
	{ "YT", "System Battery Trouble",
	  "Low battery in control/communicator" },
	{ "YU", "Diagnostic Error",
	  "An expansion/peripheral device is reporting a diagnostic error" },
	{ "YW", "Watchdoc Reset",
	  "The TRANSMITTER created an internal reset" },
	{ "YX", "Service Required",
	  "A TRANSMITTER/RECEIVER needs service" },
	{ "YY", "Status Report",
	  "Account status report transmission" },
	{ "YZ", "Service Completed",
	  "Required TRANSMITTER / RECEIVER service completed" },
	{ "ZA", "Freeze Alarm",
	  "Freeze emergency assistance request, manually activated" },
	{ "ZB", "Freeze Bypass",
	  "Freeze zone has been bypassed" },
	{ "ZH", "Freeze Alarm Restore",
	  "Freeze alarm condition eliminated" },
	{ "ZJ", "Freeze Trouble Restore",
	  "Freeze trouble condition eliminated" },
	{ "ZR", "Freeze Restoral",
	  "Freeze alarm/trouble condition eliminated" },
	{ "ZS", "Freeze Supervisory",
	  "Unsafe freeze system condition exists" },
	{ "ZT", "Freeze Trouble",
	  "Freeze zone disabled by fault" },
	{ "ZU", "Freeze Unbypass",
	  "Freeze zone bypass has been removed" },
	{ NULL, NULL, NULL },
};



const char *sia_code_str(char *code) {
	uint16_t i;

	for (i = 0; sia_codes[i].code != NULL; i++) {
		if (strncmp(code, sia_codes[i].code, 2) != 0) {
			continue;
		}
		return sia_codes[i].string;
	}
	return NULL;
}

const char *sia_code_desc(char *code) {
	uint16_t i;

	for (i = 0; sia_codes[i].code != NULL; i++) {
		if (strncmp(code, sia_codes[i].code, 2) != 0) {
			continue;
		}
		return sia_codes[i].description;
	}
	return NULL;
}
