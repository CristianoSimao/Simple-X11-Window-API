#include "SimpleX11API.h"

//This code will change the resolution of screen and create a window in full screen mode.
//Close the window with Alt+F4 if needed.
int main(){
   
    Sx11Init();
   
    //int resposta = Sx11SetScreenResolution(800,600);
    //if(resposta != 0){
    //    printf("Problem trying change resolution.");
    //}
    
    //The color in the Simple X11 API are in RGB hex format
    //Example: 0xff0000 is red
    //         0x00ff00 is green
    //         0x0000ff is blue
    //         0xffff00 is yellow

    Sx11CreateWindow(800,600,"Test Window",0xffffff);
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


        //Check if Mouse button is pressed.
        if(sx11MouseLeftPress == 1){printf("Left Mouse pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11MouseRightPress == 1){printf("Right Mouse pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11MouseMiddlePress == 1){printf("Middle Mouse pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11MouseWheelUpPress == 1){printf("Mouse Wheel Up pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11MouseWheelDownPress == 1){printf("Mouse Wheel Down pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}

        if(sx11MouseLeftReleased == 1){printf("Left Mouse released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11MouseRightReleased == 1){printf("Right Mouse released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11MouseMiddleReleased == 1){printf("Middle Mouse released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11MouseWheelUpReleased == 1){printf("Mouse Wheel Up released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11MouseWheelDownReleased == 1){printf("Mouse Wheel Down released: %d , %d.\n",sx11MouseX,sx11MouseY);}

        if(sx11MouseMove == 1){printf("Mouse moved: %d , %d.\n",sx11MouseX,sx11MouseY);}
        

        //Checa se apertou ou soltou uma tecla do teclado.
        if(sx11Keyboard_A_press == 1){printf("A pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_W_press == 1){printf("W pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_S_press == 1){printf("S pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_D_press == 1){printf("D pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_Q_press == 1){printf("Q pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_E_press == 1){printf("E pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_R_press == 1){printf("R pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_Shift_press == 1){printf("Shift pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_Ctrl_press == 1){printf("Ctrl pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_Space_press == 1){printf("Space pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_1_press == 1){printf("1 pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_2_press == 1){printf("2 pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_3_press == 1){printf("3 pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_4_press == 1){printf("4 pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_Arrow_Left_press == 1){printf("Left Arrow pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_Arrow_Right_press == 1){printf("Right Arrow pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_Arrow_Up_press == 1){printf("Up Arrow pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_Arrow_Down_press == 1){printf("Down Arrow pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_Enter_press == 1){printf("Enter pressed: %d , %d.\n",sx11MouseX,sx11MouseY);}

        if(sx11Keyboard_A_released == 1){printf("A released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_W_released == 1){printf("W released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_S_released == 1){printf("S released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_D_released == 1){printf("D released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_Q_released == 1){printf("Q released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_E_released == 1){printf("E released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_R_released == 1){printf("R released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_Shift_released == 1){printf("Shift released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_Ctrl_released == 1){printf("Ctrl released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_Space_released == 1){printf("Space released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_1_released == 1){printf("1 released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_2_released == 1){printf("2 released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_3_released == 1){printf("3 released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_4_released == 1){printf("4 released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_Arrow_Left_released == 1){printf("Left Arrow released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_Arrow_Right_released == 1){printf("Right Arrow released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_Arrow_Up_released == 1){printf("Up Arrow released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_Arrow_Down_released == 1){printf("Down Arrow released: %d , %d.\n",sx11MouseX,sx11MouseY);}
        if(sx11Keyboard_Enter_released == 1){printf("Enter released: %d , %d.\n",sx11MouseX,sx11MouseY);}

        //refresh screen
        Sx11Flush();

        if (Sx11GetCloseWindowEvent()){ 
            Sx11End();
            run = 0;    
        }

        Sx11ClearButtons();
        sleep(0.2);//sleep 0.2 second
    }

    return 0;
}