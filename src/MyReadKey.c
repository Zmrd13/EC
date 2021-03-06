#include "../include/MyReadKey.h"

int rk_mytermsave(void){

	tcgetattr(0, &tty);
	savetty = tty;
	return 0;
}

int rk_mytermrestore(void){
	tcsetattr(0, TCSAFLUSH, &savetty);
	return 0;
}

int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint){
	if (((regime < 0) || (regime > 1)) && ((vtime < 0) || (vtime > 1)) && ((vmin < 0) || (vmin > 1)) && ((echo < 0) || (echo > 1)) && ((sigint < 0) || (sigint > 1))){
		return -1;
	}
	else {
		tcgetattr(0,&tty);
		
		if (regime == 1) tty.c_lflag  |= ICANON;
		else tty.c_lflag &= ~ICANON;

		if (echo == 1) tty.c_lflag |= ECHO;
		else tty.c_lflag &= ~ECHO;

		if (sigint == 1) tty.c_lflag |= ISIG;
		else tty.c_lflag &= ~ISIG;

		tty.c_cc[VMIN] = vmin;
		tty.c_cc[VTIME] = vtime;
		tcsetattr(0,TCSAFLUSH, &tty);
		mt_gotoXY(25,1);
		return 0;
	}

}

int rk_readkey (enum keys *key, int flag){
	char buf[5];
	int b;
	printf(F_tab);
	fflush(stdout);
	b = read(0, &buf, 4);
	mt_gotoXY(27,1);
	fflush(stdout);
	if(b == -1) 
		return -1;
	else{
		buf[4] = 0;

		if (strncmp(buf, "l", 1) == 0)
			*key = l;
		else if (strncmp(buf, "s", 1) == 0)
	                *key = s;
		else if (strncmp(buf, "r", 1) == 0)
	                *key = r;
		else if (strncmp(buf, "t", 1) == 0)
	                *key = t;
		else if (strncmp(buf, "i", 1) == 0)
	                *key = i;
	 	else if (strncmp(buf, "v", 1) == 0)
                        *key = v;
		else if (strncmp(buf, "p", 1) == 0)
			*key = p;
		else if (strcmp(buf, "\E[15") == 0)
        	        *key = F5;
		else if (strcmp(buf, "\E[17") == 0)
        	        *key = F6;
		else if (strncmp(buf, "q", 1) == 0)
                        *key = q;
		else if (strcmp(buf, "\n") == 0)
        	        *key = ENTER;
		else
        	        *key = NONE;
		if(flag == 1){
			if (strncmp(buf, "\E[D", 3) == 0)
	        	        *key = LEFT;
			else if (strncmp(buf, "\E[C", 3) == 0)
        		        *key = RIGHT;
			else if (strncmp(buf, "\E[A", 3) == 0)
        		        *key = UP;
			else if (strncmp(buf, "\E[B", 3) == 0)
	                	*key = DOWN;
		}
		else{
			if (strncmp(buf, "a", 1) == 0)
				*key = LEFT;
			else if (strncmp(buf, "d", 1) == 0)
        	        	*key = RIGHT;
			else if (strncmp(buf, "w", 1) == 0)
        		        *key = UP;
			else if (strncmp(buf, "s", 1) == 0)
                        	*key = DOWN;		
		}
		return 0;
	}	
}
