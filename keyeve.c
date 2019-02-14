#include <stdint.h>

#include <linux/input.h>

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#ifndef EV_SYN
#define EV_SYN 0
#endif

static int capit_control[24]={0};
static const char protocol[24] = "udlrsxyzabcmwhijktopqdef";

int main (int argc, char **argv)
{
	int fd, rd ,fd2,sync_control=0;
	struct input_event ev[64];
    char *portname = "/dev/ttyFIQ0";
    char data[24]={0};
    fd2 = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd2 < 0) {
        return -1;
    }
	if (argc < 2) {
	
		return 1;
	}

	if ((fd = open(argv[argc - 1], O_RDONLY)) < 0) {
	
		return 1;
	}


	

	while (1) {
		rd = read(fd, ev, sizeof(struct input_event) * 64);

		if (rd < (int) sizeof(struct input_event)) {
            
			return 1;
		}

		for (int i = 0; i < rd / sizeof(struct input_event); i++){

			if (ev[i].type == EV_SYN) {
	
			} else if(EV_KEY == ev[i].type) {
				/*printf("Event: time %ld.%06ld, type %d (%s), code %d (%s), value %d\n",
					ev[i].time.tv_sec, ev[i].time.tv_usec, ev[i].type,
					events[ev[i].type] ? events[ev[i].type] : "?",
					ev[i].code,
					names[ev[i].type] ? (names[ev[i].type][ev[i].code] ? names[ev[i].type][ev[i].code] : "?") : "?",
					ev[i].value);
                */
          
                
                switch(ev[i].code){
                    case KEY_UP :
                        capit_control[0]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_DOWN :
                        capit_control[1]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_LEFT :
                        capit_control[2]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_RIGHT :
                        capit_control[3]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_S :
                        capit_control[4]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_X :
                        capit_control[5]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_Y :
                        capit_control[6]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_Z :
                        capit_control[7]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_A :
                        capit_control[8]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_B :
                        capit_control[9]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_C :
                        capit_control[10]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_M :
                        capit_control[11]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_W :
                        capit_control[12]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_H :
                        capit_control[13]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_I :
                        capit_control[14]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_J :
                        capit_control[15]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_K :
                        capit_control[16]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_T :
                        capit_control[17]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_O :
                        capit_control[18]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_P :
                        capit_control[19]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_Q :
                        capit_control[20]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_D :
                        capit_control[21]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_E :
                        capit_control[22]=ev[i].value;
                        sync_control=1;
                        break;
                    case KEY_F :
                        capit_control[23]=ev[i].value;
                        sync_control=1;
                        break;
                }
            }	
        }
        if(sync_control){
            for(int i=0;i<24;i++){
                data[i]=protocol[i]-capit_control[i]*32;
            }
            write(fd2,&data,24);
            sync_control = 0;
        }
    }
    return 0;
}
