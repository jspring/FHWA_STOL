/* parser.h - header file for message parsing of RTMS detector data on the
** VSA server and CAN data on the vehicles
*/


/***********************************************************************
************************************************************************
RTMS DETECTOR MESSAGE PARSING
************************************************************************
***********************************************************************/

typedef struct {
        int msg_no;
        int vol_lane_1;
        int vol_lane_2;
        int vol_lane_3;
        int station_id;
        float occ_lane_1;
        float occ_lane_2;
        float occ_lane_3;
        int sidefrd_spd_1;
        int sidefrd_spd_2;
        int sidefrd_spd_3;
        int speed_85_1;
        int speed_85_2;
        int speed_85_3;
        float gap_lane_1;
        float gap_lane_2;
        float gap_lane_3;
        int day;
        int month;
        int year;
        int hour;
        int minute;
        int second;
} IS_PACKED rtms_msg_t;

#define DB_RTMS_TYPE	5000
#define DB_RTMS_VAR	DB_RTMS_TYPE

/***********************************************************************
***********************************************************************/



/***********************************************************************
************************************************************************
VEHICLE MESSAGE PARSING

The rest of this header file contains parsing for the CAN messages that
were being transmitted on the vehicles.  After talking with Tony Ahmad,
I realized that they had already created a method for grabbing the data
on the vehicle, grabbing the data from the VSA server, and displaying
and setting the suggested speed on the vehicle itself.  The following
work was done before this was known, so it is currently unnecessary.
But I'm keeping it anyway in case we need it later....

************************************************************************
***********************************************************************/

typedef struct {

	unsigned char header[20];
	unsigned int offset;		// Byte 20-23
	unsigned int sec_since_epoch;	// Byte 24-27
	unsigned int microsec;		// Byte 28-31
	unsigned int length;		// Byte 32-35
	unsigned int length2;		// Byte 36-39
	unsigned char dest_addr[6];	// Byte 40-45
	unsigned char other1[8];	// Byte 46-53

} IS_PACKED wireless_80211_frame_msg_t;

typedef struct {

	unsigned short frame_control;	// Byte 54-55
	unsigned short duration_id;	// Byte 56-57
	unsigned char dest_addr[6];	// Byte 58-63
	unsigned char source_addr[6];	// Byte 64-69
	unsigned char bssid[6];		// Byte 70-75
	unsigned char other1[4];	// Byte 76-79

} IS_PACKED mac_header_t;

typedef struct {
	
	unsigned char dsap;		// Dest service addr pt. 0xAA Byte 80	
	unsigned char ssap;		// Source service addr pt. 0xAA Byte 81	
	unsigned short control;		// log link control Byte 82-83
	unsigned short org_code;	// Organization code Byte 84-85
	unsigned short type;		// Byte 86-87; always 0x88DC

} IS_PACKED logical_link_control_t;

// WAVE Short Message Protocol, aka IEEE P1609.3
typedef struct {

	unsigned char version;		// Byte 88; always 0x02
	unsigned char psid;		// Byte 89; Provider Service ID always 0x20
	unsigned char channel_id;	// Byte 90; 15 here
	unsigned char channel_length;	// Byte 91; 1 here
	unsigned char channel;		// Byte 92; 0xAC (172) here
	unsigned char extension_rate_id;// Byte 93; 0x10 (16) here
	unsigned char other[2];		// Byte 94-95
	unsigned char extension_power_id; // Byte 96; always 4
	unsigned char extension_power_length; // Byte 97; always 1
	unsigned char tx_power;		// Byte 98; transmit power in dBm (22 dBm here)
	unsigned char wave_elem_id;	// Byte 99; always 0x81
	unsigned short wsm_length;	// Byte 100-101; either 0x00FE (254) or 0x00B7 (183)
	
} IS_PACKED wsmp_t;

// IEEE 1609.2 standard message, part 1 (before optional certificate)
typedef struct {

	unsigned char version;		// Byte 103; always 0x02
	unsigned char content_typ;	// Byte 104; always 0x01 (signed)
	unsigned char id;		// Byte 105; 2=no cert, 3=certificate

} IS_PACKED ieee16092_part1_t;


// IEEE 1609.2 certificate
typedef struct {

	unsigned char certificate[79];	// Byte 106-184

} IS_PACKED ieee16092_certificate_t;


// IEEE 1609.2 standard message, part 2 (after optional certificate)
typedef struct {

	unsigned char msgflag[2];	// Byte 106-107; 185-186
	unsigned char psid;		// Byte 108; 187; Provider Service ID; always 0x20 
	unsigned char length;		// Byte 109; 188
	unsigned char other[7];		// Byte 110-116; 189-195
} IS_PACKED ieee16092_part2_t;

// BSM
typedef struct {
	unsigned int temporary_id; // Byte 117-120; 196-199
	int	latitude;	// Byte 123-126; 202-205
	int	longitude;	// Byte 127-130; 206-209
	unsigned short elevation; // Byte 131-132; 210-211
} IS_PACKED bsm_t;

// IEEE 1609.2 standard message, part 3 (after optional certificate)
typedef struct {

	unsigned char generation_time[16];  // Byte 203-210; 282-289 ;
} IS_PACKED end_t;

/***********************************************************************
***********************************************************************/
