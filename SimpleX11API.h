//Simple X11 Window API.
//Version: 0.1
//Created by: Cristiano Simao dos Santos
//Date: 22 december 2022
//License: GNU GPL v3.0
//For more details visit: https://github.com/CristianoSimao/Simple-X11-Window-API

#include <stdio.h>
#include <unistd.h>     //include the function sleep
#include <stdlib.h>     //include the system function
#include <X11/Xlib.h>
#include <X11/Xutil.h>  //to show the window title bar text.
#include <string.h>     //include strcat function

struct Sx11HardwareMonitor{
    int width;
    int height;
    int bitdepth;
}Sx11DefaultMonitor;

Display *sx11Monitor;       //pointer to the X Server
Screen *sx11Defaultscreen;  //pointer to information about screen.
int sx11ScreenNumber;       // Number to the hardware screen if more than 1 screen monitor are used in the desktop.
char sx11ResolutionChanged = '0'; 
Window sx11Win;
GC sx11Pencil;
Atom sx11DeleteComand;
   
int mouseEvent;
int keyboardEvent;
int closeWindowEvent;

void sendFullscreenEvent(Display* display, Window win){
	if (win != None && win != DefaultRootWindow(display))
	{
		Atom atomFullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", True);
		Atom atomState = XInternAtom(display, "_NET_WM_STATE", True);
		XClientMessageEvent event;
		event.type = ClientMessage;
		event.serial = 0;
		event.send_event = True;
		event.window = win;
		event.message_type = atomState;
		event.format = 32;
		event.data.l[0] = 1;
		event.data.l[1] = atomFullscreen;
		event.data.l[2] = 0;
		XSendEvent(display, DefaultRootWindow(display), False,
				   SubstructureRedirectMask | SubstructureNotifyMask,
				   (XEvent*)&event);
		XFlush(display);
	}
}

int Sx11SetScreenResolution(char resolution[9]){
    //This function uses a shell program "xrandr" to change the screen resolution
    //return 0 if is ok or 1 if have error.
    //Typical values "640x480", "800x600", "1280x720","1920x1080"

    char comand[30] = "xrandr --size ";
    strcat(comand,resolution);
    //printf("%s \n",comand); //Debug
    int r = system(comand);
    if (r !=0){
       printf("Error: Sx11SetScreenResolution:resolution %s not supported.\n",resolution);
       return 1;
    }
    //infor the change
    sx11ResolutionChanged = '1';
    return 0;
}

void Sx11Init(){
    //initializing X Server
    sx11Monitor = XOpenDisplay(NULL); 
    sx11Defaultscreen = XDefaultScreenOfDisplay(sx11Monitor);
    sx11ScreenNumber = XDefaultScreen(sx11Monitor); // default number to the screen
    //Get some information about the hardware monitor
    Sx11DefaultMonitor.width = XDisplayWidth(sx11Monitor, sx11ScreenNumber);
    Sx11DefaultMonitor.height = XDisplayHeight(sx11Monitor,sx11ScreenNumber);
    Sx11DefaultMonitor.bitdepth = DefaultDepthOfScreen(sx11Defaultscreen);

}

void Sx11End(){
    //close the conection to X and return the monitor resolution to the original value if changed
    XCloseDisplay(sx11Monitor);

    if(sx11ResolutionChanged == '1'){
        //return the resolution to the original
        char original[12];
        sprintf(original,"%ix%i",Sx11DefaultMonitor.width,Sx11DefaultMonitor.height); //convert int to char to represent the resolution
        //printf("Resolution original: %s\n",original);  //Debug
        Sx11SetScreenResolution(original);
    }

}

int Sx11CreateWindow(int sizeX, int sizeY, char windowtitle[], unsigned long int backgorundColor){
    //Creting the window.
    sx11Win = XCreateSimpleWindow(sx11Monitor,RootWindow(sx11Monitor,sx11ScreenNumber),0,0,sizeX,sizeY,1,0,backgorundColor);

    //Set the window title
    XSetStandardProperties(sx11Monitor, sx11Win, windowtitle, "0", None, NULL, 0, NULL);

    //Get the color configurations to draw
    sx11Pencil = XCreateGC(sx11Monitor,sx11Win,0,0);

    //Configuring the close event (when the user click in the "X" buton to close the window or press Alt+F4)
    sx11DeleteComand = XInternAtom(sx11Monitor, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(sx11Monitor, sx11Win, &sx11DeleteComand, 1);
   
    //Configure the events to get (keyboard and mouse)
    XSelectInput(sx11Monitor,sx11Win,KeyPressMask | ButtonPressMask);

    //Show the window
    XMapWindow(sx11Monitor,sx11Win);

    //Synchronization
    XSync(sx11Monitor,False);

    return 0;
}

void Sx11SetFullScreen(){
    //Sending full screen event
    sendFullscreenEvent(sx11Monitor, sx11Win);
}

int Sx11GetEvents(){
    //Return 0 if no event exists or 1 if some event exists
    mouseEvent =0;
    keyboardEvent =0;
    closeWindowEvent =0;
    while(XPending(sx11Monitor) > 0){
        //Some events exists 
        XEvent evento = {0};
        XNextEvent(sx11Monitor,&evento);

        switch (evento.type) {
            case ButtonPress:{
                //To do: implement a mouse button identification
                mouseEvent = 1;
            }break;

            case KeyPress:{
                //To do: implement a keyboard button identification
                keyboardEvent = 1;
                switch (XLookupKeysym(&evento.xkey, 0)) {
                        case 'q':
                        printf("Keyboar Q key pressed.\n");
                    }
            }break;

            case ClientMessage: {
                if ((Atom) evento.xclient.data.l[0] == sx11DeleteComand) {
                    //send close window message
                    closeWindowEvent = 1;
                }
            }

        }
        return 1;
    }

    return 0;
}

void Sx11DrawString(int x, int y,unsigned long int sx11Color, char sx11text[]){
    //Draw the string in the position x y.
    XSetForeground(sx11Monitor,sx11Pencil,sx11Color);
    XDrawString(sx11Monitor,sx11Win,sx11Pencil,x,y,sx11text,strlen(sx11text));
}

void Sx11DrawLine(int x, int y, int fx, int fy, unsigned long int sx11Color){
    XSetForeground(sx11Monitor,sx11Pencil,sx11Color);
    XDrawLine(sx11Monitor,sx11Win,sx11Pencil,x,y,fx,fy);
}

void Sx11DrawPixel(int x, int y, unsigned long int sx11Color){
    XSetForeground(sx11Monitor,sx11Pencil,sx11Color);
    XDrawPoint(sx11Monitor,sx11Win,sx11Pencil,x,y);
}