#include "SimpleX11API.h"

int main(){
    
    Sx11Init();
    //Sx11SetScreenResolution("800x600");
    printf("Width of screen: %i \n",Sx11DefaultMonitor.width);
    printf("Height of screen: %i \n",Sx11DefaultMonitor.height);
    printf("Bitdepth of screen: %i \n",Sx11DefaultMonitor.bitdepth);

    //The color in the Simple X11 API are in RGB hex format
    //Example: 0xff0000 is red
    //         0x00ff00 is green
    //         0x0000ff is blue
    //         0xffff00 is yellow

    Sx11CreateWindow(640,480,"Test Window",0xffffff);
    //Sx11SetFullScreen();

    //Loop to draw and capture screen events
    int run = 1;
    while(run){
        Sx11GetEvents();
        Sx11DrawString(220,160,0x0000ff,"Welcome to the Simple X11 API !!!");
        Sx11DrawLine(197, 195, 292,318, 0x000000);
        Sx11DrawLine(197,318,292,195, 0x000000);
        Sx11DrawLine(337,228,368,192, 0x000000);
        Sx11DrawLine(368,192,368,320, 0x000000);
        Sx11DrawLine(409,228,440,192, 0x000000);
        Sx11DrawLine(440,192,440,320, 0x000000);

        //Drawing a line pixel by pixel
        for(int x = 0; x < 260; x++){
            Sx11DrawPixel(197 + x, 340, 0xff0000);
        }


        if (closeWindowEvent ==1){ 
            Sx11End();
            run = 0;    
        }
        sleep(0.2);//sleep 0.2 second
    }

    return 0;
}