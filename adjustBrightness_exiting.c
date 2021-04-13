#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/input.h>

#define MOUSEFILE "/dev/custommouse"

int main()
{

	//brightness vars
	
	FILE *fp;
  	int currentBrightness = 0;
  	const char *kFileName ="/sys/class/backlight/intel_backlight/brightness";
  	
  	//mouse vars
    int fd;
    struct input_event ie;
    unsigned char *ptr = (unsigned char*)&ie;
    unsigned char button,bLeft,bMiddle,bRight;
    char x,y;
    
                                                              
    if((fd = open(MOUSEFILE, O_RDONLY | O_NONBLOCK )) == -1){
    
        printf("NonBlocking %s open ERROR\n",MOUSEFILE);
        exit(EXIT_FAILURE);
    }
    else{
    
        printf("NonBlocking %s open OK\n",MOUSEFILE);
    }
    
    printf("--------------------------------------------------------\n");
    printf("Right click to increase brightness\n");
    printf("Left click to decrease brightness\n");
    printf("--------------------------------------------------------\n");

    while(1)
    {       
        if(read(fd, &ie, sizeof(struct input_event))!=-1)
        {
                        
            button=ptr[0];
            bLeft = button & 0x1;
            bMiddle = ( button & 0x4 ) > 0;
            bRight = ( button & 0x2 ) > 0;
            x=(char) ptr[1];y=(char) ptr[2];
            
            //check for middleButton press
			if(bMiddle == 1){
				break;
			}
            
            fp = fopen(kFileName, "r");
            fscanf(fp, "%d", &currentBrightness);
            fclose(fp);

            //increase brightness
            if (bRight== 1){
                printf("RIGHT PRESSED!\n");
                fp = fopen(kFileName, "w");
                fprintf(fp, "%d", currentBrightness + 500);
                fclose(fp);
            }
            
            //decrease brightness
            if(bLeft == 1){
                printf("LEFT PRESSED!\n");
                fp = fopen(kFileName, "w");
                fprintf(fp, "%d", currentBrightness - 500);
                fclose(fp);
            }
            fflush(stdout);
        }
    }
    
    //wait for release of middle button
    int a;
    int b;
    while(1){
    
		if(read(fd, &ie, sizeof(struct input_event))!=-1){
		
			a = ptr[0];
			b = ( a & 0x4 ) > 0;
			if(b == 0) break;
		}
    
    }
    close(fd);
    fflush(stdout);
return 0;
}
