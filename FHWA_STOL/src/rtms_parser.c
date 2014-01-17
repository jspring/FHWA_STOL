/* parser.c - reads messages from the Vehicle Assistance Device (VAD),
** parses them into self-data (e.g. GPS position, speed, heading),
** and writes the data to the database
*/ 

#include <db_include.h>
#include "parser.h"

int main( int argc, char *argv[]) {

	char buf[1000];
	int option;
	int verbose = 0;
	int interval = 5000;
	char *filename = NULL;
	FILE *fp;
	int retval = 0;
	char str1[100];
	char str2[100];
	rtms_msg_t rtms;
	char *pchar;
	int ms;
	int matchnum;


        while ((option = getopt(argc, argv, "vd:i:")) != EOF) {
                switch(option) {
                case 'v':
                        verbose = 1;
                        break;
                case 'd':
                        filename = strdup(optarg);
                        break;
                case 'i':
                        interval = atoi(optarg);
                        break;
                default:
                        printf("Usage: %s\n", argv[0]);
                        printf("    -d <data file> \n");
                        printf("    -v (verbose)\n");
                        exit(EXIT_FAILURE);
                }
        }

	if(filename != NULL) {
		if( (fp = fopen(filename,"r")) == NULL) {
			perror("fopen");
			return -1;
		}
	}
	else 
		fp = stdin;

	while( (retval = fgets(buf, sizeof(buf), fp) != NULL)) {
		if( (matchnum = strspn(buf, "0123456789: \t")) >= (retval + 8) ) {
			sscanf(buf, "%d %d %d %d:\t%d:%d:%d",
				&rtms.day,
				&rtms.month,
				&rtms.year,
				&rtms.hour,
				&rtms.minute,
				&rtms.second,
				&ms
			);
			printf("Date %02d/%02d/%d Time: %02d:%02d:%02d\n",
				rtms.month,
				rtms.day,
				rtms.year,
				rtms.hour,
				rtms.minute,
				rtms.second
			);
		}
		if(strstr(buf, "MESSAGE NO.") != NULL) {
			sscanf(buf, "%s %s %d %s %d %d %d", 
				&str1[0],
				&str2[0],
				&rtms.msg_no,
				&str2[0],
				&rtms.vol_lane_1,
				&rtms.vol_lane_2,
				&rtms.vol_lane_3
			);
			printf("Message number %d lane 1 volume %d lane 2 volume %d lane 3 volume %d\n",
				rtms.msg_no,
				rtms.vol_lane_1,
				rtms.vol_lane_2,
				rtms.vol_lane_3
			);
		}
		if(strstr(buf, "STATION ID.") != NULL) {
			sscanf(buf, "%s %s %d %s %f %f %f", 
				&str1[0],
				&str2[0],
				&rtms.station_id,
				&str2[0],
				&rtms.occ_lane_1,
				&rtms.occ_lane_2,
				&rtms.occ_lane_3
			);
			printf("Station ID %d lane 1 occupancy %.1f lane 2 occupancy %.1f lane 3 occupancy %.1f\n",
				rtms.msg_no,
				rtms.occ_lane_1,
				rtms.occ_lane_2,
				rtms.occ_lane_3
			);
		}
		if(strstr(buf, "SIDEFRD") != NULL) {
			// Replace the question marks with ASCII '0'
			while( (pchar = strchr(&buf[0], '?')) != NULL)
				*pchar = '0';
			sscanf(buf, "%s %s %d %s %s %d %d %d %s %s %s %s %s %s", 
				&str1[0],
				&str2[0],
				&rtms.sidefrd_spd_1,
				&str2[0],
				&str2[0],
				&rtms.sidefrd_spd_1,
				&rtms.sidefrd_spd_2,
				&rtms.sidefrd_spd_3,
				&str1[0],
				&str1[0],
				&str1[0],
				&str1[0],
				&str1[0],
				&str1[0]
			);
			printf("lane 1 sidefired_speed %d lane 2 sidefired_speed %d lane 3 sidefired_speed %d\n",
				rtms.sidefrd_spd_1,
				rtms.sidefrd_spd_2,
				rtms.sidefrd_spd_3
			);
		}
		if(strstr(buf, "SPEED 85") != NULL) {
			// Replace the question marks with ASCII '0'
			while( (pchar = strchr(&buf[0], '?')) != NULL)
				*pchar = '0';
			sscanf(buf, "%s %s %d %d %d", 
				&str1[0],
				&str2[0],
				&rtms.speed_85_1,
				&rtms.speed_85_2,
				&rtms.speed_85_3
			);
			printf("lane 1 speed 85%% %d lane 2 speed 85%% %d lane 3 speed 85%% %d\n",
				rtms.speed_85_1,
				rtms.speed_85_2,
				rtms.speed_85_3
			);
		}
		if(strstr(buf, "GAP") != NULL) {
			// Replace the question marks with ASCII '0'
			while( (pchar = strchr(&buf[0], '?')) != NULL)
				*pchar = '0';
			sscanf(buf, "%s %f %f %f", 
				&str1[0],
				&rtms.gap_lane_1,
				&rtms.gap_lane_2,
				&rtms.gap_lane_3
			);
			printf("lane 1 gap %.1f lane 2 gap %.1f lane 3 gap %.1f\n",
				rtms.gap_lane_1,
				rtms.gap_lane_2,
				rtms.gap_lane_3
			);
		}
		memset(buf, 0, sizeof(buf));
	}
	return 0;
}
