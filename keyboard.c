#include <stdint.h>

#include <linux/input.h>

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#ifndef EV_SYN
#define EV_SYN 0
#endif


int main (int argc, char **argv)
{
	int fd, rd, i, j, k;
	struct input_event ev[64];
	int version;
	unsigned short id[4];
	
	char name[256] = "Unknown";
	int abs[5];

	if (argc < 2) {
		printf("Usage: evtest /dev/input/eventX\n");
		printf("Where X = input device number\n");
		return 1;
	}

	if ((fd = open(argv[argc - 1], O_RDONLY)) < 0) {
		perror("evtest");
		return 1;
	}

	


		

	printf("Testing ... (interrupt to exit)\n");

	while (1) {
		rd = read(fd, ev, sizeof(struct input_event) * 64);

		if (rd < (int) sizeof(struct input_event)) {
			printf("yyy\n");
			perror("\nevtest: error reading");
			return 1;
		}

		for (i = 0; i < rd / sizeof(struct input_event); i++){

			if (ev[i].type == EV_SYN) {
				printf("Event: time %ld.%06ld, -------------- %s ------------\n",
					ev[i].time.tv_sec, ev[i].time.tv_usec, ev[i].code ? "Config Sync" : "Report Sync" );
			} else if(EV_KEY == ev[i].type){
			
				printf("Event: time %ld.%06ld, type %d (%s), code %d (%s), value %d type : %d\n",
					ev[i].time.tv_sec, ev[i].time.tv_usec, ev[i].type,
					events[ev[i].type] ? events[ev[i].type] : "?",
					ev[i].code,
					names[ev[i].type] ? (names[ev[i].type][ev[i].code] ? names[ev[i].type][ev[i].code] : "?") : "?",
					ev[i].value,ev[i].type);
				
			}	
		}

	}
}


