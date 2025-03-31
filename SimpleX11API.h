//Simple X11 Window API.
//Version: 0.2
//Created by: Cristiano Simao dos Santos
//Date: 20 march 2025 / 31 march 2025
//License: GNU GPL v3.0
//For more details visit: https://github.com/CristianoSimao/Simple-X11-Window-API
//(dec/2022 - mar/2025)

//Update v0.2 include:
//- File header and code separated in files .h and .c
//- New functions to change screen resolution
//- New functions to read keyboard and mouse input
//- Review of architecture

#pragma once
#include <stdio.h>
#include <unistd.h>     //include the function sleep
#include <stdlib.h>     //include the system function
#include <X11/Xlib.h>
#include <X11/Xutil.h>  //to show the window title bar text.
#include <X11/extensions/Xrandr.h>
#include <string.h>     //include strcat function


extern int sx11MouseLeftPress;   
extern int sx11MouseMiddlePress; 
extern int sx11MouseRightPress;  
extern int sx11MouseWheelUpPress;     
extern int sx11MouseWheelDownPress;   
extern int sx11MouseLeftReleased;   
extern int sx11MouseMiddleReleased; 
extern int sx11MouseRightReleased;  
extern int sx11MouseWheelUpReleased;     
extern int sx11MouseWheelDownReleased;
extern int sx11MouseX;           
extern int sx11MouseY;
extern int sx11MouseMove;

extern int sx11Keyboard_A_press;
extern int sx11Keyboard_W_press;
extern int sx11Keyboard_S_press;
extern int sx11Keyboard_D_press;
extern int sx11Keyboard_Q_press;
extern int sx11Keyboard_E_press;
extern int sx11Keyboard_R_press;
extern int sx11Keyboard_Shift_press;
extern int sx11Keyboard_Ctrl_press;
extern int sx11Keyboard_Space_press;
extern int sx11Keyboard_1_press;
extern int sx11Keyboard_2_press;
extern int sx11Keyboard_3_press;
extern int sx11Keyboard_4_press;
extern int sx11Keyboard_Arrow_Left_press;
extern int sx11Keyboard_Arrow_Right_press;
extern int sx11Keyboard_Arrow_Up_press;
extern int sx11Keyboard_Arrow_Down_press;
extern int sx11Keyboard_Enter_press;

extern int sx11Keyboard_A_released;
extern int sx11Keyboard_W_released;
extern int sx11Keyboard_S_released;
extern int sx11Keyboard_D_released;
extern int sx11Keyboard_Q_released;
extern int sx11Keyboard_E_released;
extern int sx11Keyboard_R_released;
extern int sx11Keyboard_Shift_released;
extern int sx11Keyboard_Ctrl_released;
extern int sx11Keyboard_Space_released;
extern int sx11Keyboard_1_released;
extern int sx11Keyboard_2_released;
extern int sx11Keyboard_3_released;
extern int sx11Keyboard_4_released;
extern int sx11Keyboard_Arrow_Left_released;
extern int sx11Keyboard_Arrow_Right_released;
extern int sx11Keyboard_Arrow_Up_released;
extern int sx11Keyboard_Arrow_Down_released;
extern int sx11Keyboard_Enter_released;

//Functions
void Sx11Init();
void Sx11End();
int Sx11GetCloseWindowEvent();
int Sx11SetScreenResolution(int resolutionx, int resolutiony);
int Sx11CreateWindow(int sizeX, int sizeY, char windowtitle[], unsigned long int backgorundColor);
void Sx11SetFullScreen();
int Sx11GetEvents();
void Sx11ClearButtons();
void Sx11DrawString(int x, int y,unsigned long int sx11Color, char sx11text[]);
void Sx11DrawLine(int x, int y, int fx, int fy, unsigned long int sx11Color);
void Sx11DrawPixel(int x, int y, unsigned long int sx11Color);
void Sx11Flush();
