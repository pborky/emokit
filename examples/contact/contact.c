/* 

Get real-time contact quality readings

  */

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "emokit/emokit.h"

int quit;
void cleanup(int i){
	fprintf(stdout,"Shutting down\n");
	quit=1; 
}

int main(int argc, char **argv)
{
	struct emokit_device* d;
	signal(SIGINT, cleanup); //trap cntrl c
	

	quit=0;

	d = emokit_create();
	int count=emokit_get_count(d, EMOKIT_VID, EMOKIT_PID);
	printf("Current epoc devices connected: %d\n", count );
	int r = emokit_open(d, EMOKIT_VID, EMOKIT_PID, 1);
	if(r != 0)
	{
		emokit_close(d);
		emokit_delete(d);
		d = emokit_create();
		r = emokit_open(d, EMOKIT_VID, EMOKIT_PID, 0);
		if (r!=0) {
			printf("CANNOT CONNECT: %d\n", r);
			return 1;
		}
	}
	printf("Connected to headset.\n");
	
	if (emokit_read_data(d)<=0) {
		printf("Error reading from headset\n");
		emokit_close(d);
		emokit_delete(d);
		return 1;
	}

	struct emokit_frame c;
	while (!quit) {
		if(emokit_read_data(d) > 0) {						
			c = emokit_get_next_frame(d);			
			fprintf(stdout,"\033[H\033[2JPress CTRL+C to exit\n\nContact quality:\nFp1  %4d\nP4 %4d\nAFz  %4d\nT6  %4d\nF7  %4d\nF8  %4d\nT5  %4d\nCz  %4d\nO2 %4d\nFp2  %4d\nO1 %4d\nPz  %4d\nFz  %4d\nP3 %4d",c.cq.Fp1, c.cq.P4, c.cq.AFz, c.cq.T6,c.cq.F7, c.cq.F8, c.cq.T5, c.cq.Cz, c.cq.O2, c.cq.Fp2, c.cq.O1, c.cq.Pz, c.cq.Fz, c.cq.P3);
			fflush(stdout);
		} 	
	}
	emokit_close(d);
	emokit_delete(d);
	return 0;
}

