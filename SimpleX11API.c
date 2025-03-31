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

#include "SimpleX11API.h"

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
   
int mouseEvent = 0;
int keyboardEvent = 0;
int closeWindowEvent = 0;

//New variables
//---------------------- Keyboard and Mouse ------------------------------
//Global variables to store information about the keys.
//Some keys generate a single event and others generate successive events of
//pressing and releasing even if you keep the key pressed.
//Therefore, you must be careful to interpret the keys correctly.
//Another limitation is that normal keyboards only inform 4 keys pressed at the same time.

int sx11MouseLeftPress = 0;   
int sx11MouseMiddlePress = 0; 
int sx11MouseRightPress = 0;  
int sx11MouseWheelUpPress = 0;     
int sx11MouseWheelDownPress = 0;   
int sx11MouseLeftReleased = 0;   
int sx11MouseMiddleReleased = 0; 
int sx11MouseRightReleased = 0;  
int sx11MouseWheelUpReleased = 0;     
int sx11MouseWheelDownReleased = 0;
int sx11MouseX = 0;           //coordinates X
int sx11MouseY = 0;           //coordinates Y
int sx11MouseMove = 0;

int sx11Keyboard_A_press = 0;
int sx11Keyboard_W_press = 0;
int sx11Keyboard_S_press = 0;
int sx11Keyboard_D_press = 0;
int sx11Keyboard_Q_press = 0;
int sx11Keyboard_E_press = 0;
int sx11Keyboard_R_press = 0;
int sx11Keyboard_Shift_press = 0;
int sx11Keyboard_Ctrl_press = 0;
int sx11Keyboard_Space_press = 0;
int sx11Keyboard_1_press = 0;
int sx11Keyboard_2_press = 0;
int sx11Keyboard_3_press = 0;
int sx11Keyboard_4_press = 0;
int sx11Keyboard_Arrow_Left_press = 0;
int sx11Keyboard_Arrow_Right_press = 0;
int sx11Keyboard_Arrow_Up_press = 0;
int sx11Keyboard_Arrow_Down_press = 0;
int sx11Keyboard_Enter_press = 0;

int sx11Keyboard_A_released = 0;
int sx11Keyboard_W_released = 0;
int sx11Keyboard_S_released = 0;
int sx11Keyboard_D_released = 0;
int sx11Keyboard_Q_released = 0;
int sx11Keyboard_E_released = 0;
int sx11Keyboard_R_released = 0;
int sx11Keyboard_Shift_released = 0;
int sx11Keyboard_Ctrl_released = 0;
int sx11Keyboard_Space_released = 0;
int sx11Keyboard_1_released = 0;
int sx11Keyboard_2_released = 0;
int sx11Keyboard_3_released = 0;
int sx11Keyboard_4_released = 0;
int sx11Keyboard_Arrow_Left_released = 0;
int sx11Keyboard_Arrow_Right_released = 0;
int sx11Keyboard_Arrow_Up_released = 0;
int sx11Keyboard_Arrow_Down_released = 0;
int sx11Keyboard_Enter_released = 0;

//----------------------------------------------------------------------

XEvent event;
XRRScreenResources *screen_res;
Status status;
RROutput active_output = 0;
XRROutputInfo *output_info = NULL;
XRRCrtcInfo *crtc_info = NULL;
XRRCrtcInfo *original_crtc_info;
int screen;
Window root;
char buffer[32];  // Buffer to store keyboard character codes
int bufsize = sizeof(buffer);
KeySym keysym;    // X11 standard keysym codes (can be compared with XK_a, XK_b...etc)


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

int Sx11SetScreenResolution(int resolutionx, int resolutiony){
    //Return 0 if the resolution changed or 1 if error.

    //List of common screen resolution modes:
    // 1920x1080
    // 1680x1050
    // 1600x900
    // 1280x1024
    // 1440x900
    // 1280x800
    // 1152x864
    // 1280x720
    // 1024x768
    // 832x624
    // 800x600
    // 720x576
    // 720x480
    // 640x480
    // 720x400

    // Get resources of screen with Xrandr
    screen_res = XRRGetScreenResources(sx11Monitor, root);
    if (!screen_res) {
        fprintf(stderr, "Error on get screen resources.\n");
        XCloseDisplay(sx11Monitor);
        return 1;
    }

    // Find active output
    for (int i = 0; i < screen_res->noutput; i++) {
        output_info = XRRGetOutputInfo(sx11Monitor, screen_res, screen_res->outputs[i]);
        if (output_info->connection == RR_Connected && output_info->crtc != 0) {
            active_output = screen_res->outputs[i];
            crtc_info = XRRGetCrtcInfo(sx11Monitor, screen_res, output_info->crtc);
            if (crtc_info) {
                break;
            }
            XRRFreeCrtcInfo(crtc_info);
            crtc_info = NULL;
        }
        XRRFreeOutputInfo(output_info);
        output_info = NULL;
    }

    // Save original configuration to restore resolution
    original_crtc_info = XRRGetCrtcInfo(sx11Monitor, screen_res, output_info->crtc);
    if (!original_crtc_info) {
        fprintf(stderr, "Error saving original configuration of CRTC\n");
        XRRFreeCrtcInfo(crtc_info);
        XRRFreeOutputInfo(output_info);
        XRRFreeScreenResources(screen_res);
        XCloseDisplay(sx11Monitor);
        return 1;
    }

    // Find the mode informed
    RRMode mode_resolution = 0;
    for (int i = 0; i < screen_res->nmode; i++) {
        XRRModeInfo *mode = &screen_res->modes[i];
        if (mode->width == resolutionx && mode->height == resolutiony) {
            mode_resolution = mode->id;
            break;
        }
    }
    if (mode_resolution == 0) {
        fprintf(stderr, "Resolution mode %dx%d not find.\n",resolutionx,resolutiony);
        XRRFreeCrtcInfo(original_crtc_info);
        XRRFreeCrtcInfo(crtc_info);
        XRRFreeOutputInfo(output_info);
        XRRFreeScreenResources(screen_res);
        XCloseDisplay(sx11Monitor);
        return 1;
    }

    // Change screen resolution to the mode selected
    status = XRRSetCrtcConfig(sx11Monitor, screen_res, output_info->crtc, CurrentTime,
                                     0, 0, mode_resolution, RR_Rotate_0,
                                     &active_output, 1);
    if (status != RRSetConfigSuccess) {
        fprintf(stderr, "Error setting new screen resolution mode.\n");
        XRRFreeCrtcInfo(original_crtc_info);
        XRRFreeCrtcInfo(crtc_info);
        XRRFreeOutputInfo(output_info);
        XRRFreeScreenResources(screen_res);
        XCloseDisplay(sx11Monitor);
        return 1;
    }

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

    //new informations for version 0.2
    screen = DefaultScreen(sx11Monitor);
    root = RootWindow(sx11Monitor, screen);
}

void Sx11End(){
    

    if(sx11ResolutionChanged == '1'){
        // Restore resolution to the default screen resolution
            status = XRRSetCrtcConfig(sx11Monitor, screen_res, output_info->crtc, CurrentTime,
                                      original_crtc_info->x, original_crtc_info->y, original_crtc_info->mode,
                                      original_crtc_info->rotation, original_crtc_info->outputs,
                                      original_crtc_info->noutput);
            if (status != RRSetConfigSuccess) {
                fprintf(stderr, "Error trying restore orininal screen resolution\n");
            }
            XSync(sx11Monitor, False);
    }

    //close the conection to X and return the monitor resolution to the original value if changed
    // Free resources and close
    XRRFreeCrtcInfo(original_crtc_info);
    XRRFreeCrtcInfo(crtc_info);
    XRRFreeOutputInfo(output_info);
    XRRFreeScreenResources(screen_res);
    XCloseDisplay(sx11Monitor);
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
    XSelectInput(sx11Monitor,sx11Win,
        KeyPressMask | KeyReleaseMask |
        ButtonPressMask | ButtonReleaseMask |
        PointerMotionMask);

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
    //Return 0 if no keyboard or mouse generated an event or 1 if some button was pressed.
    
    mouseEvent = 0;       //inform if mouse have a event
    keyboardEvent = 0;    //inform if keyboard have a event
    closeWindowEvent = 0; //inform if X button of the window was pressed or Alt+F4.
    int eventExist = 0;   //inform that keyboard or mouse generated a event


    //Receive and process the list of buttons pressed.
    while(XPending(sx11Monitor) > 0){
        eventExist = 1;
        XEvent evento = {0};
        XNextEvent(sx11Monitor,&evento); //get a event from queue.

        //Discover the type of event and your informations.
        switch (evento.type){
        
            case ButtonPress:
                //Mouse button pressed
                 {
                    switch(evento.xbutton.button){
                        case 1: //XK_Pointer_Button1:
                            sx11MouseLeftPress = 1;
                            break;

                        case 2: //XK_Pointer_Button2:
                            sx11MouseMiddlePress = 1;
                            break;    

                        case 3: //XK_Pointer_Button3:
                            sx11MouseRightPress = 1;
                            break;

                        case 4: //XK_Pointer_Button4:
                            sx11MouseWheelUpPress = 1;
                            break;

                        case 5: //XK_Pointer_Button5:
                             sx11MouseWheelDownPress = 1;
                            break;
                   }
                   sx11MouseX = evento.xbutton.x;
                   sx11MouseY = evento.xbutton.y;
                }
                break;


            case ButtonRelease:
                //Mouse button released
                {
                    switch(evento.xbutton.button){
                        case 1: //XK_Pointer_Button1:
                            sx11MouseLeftReleased = 1;
                            break;

                        case 2: //XK_Pointer_Button2:
                            sx11MouseMiddleReleased = 1;
                            break;  

                        case 3: //XK_Pointer_Button3:
                            sx11MouseRightReleased = 1;
                            break;

                        case 4: //XK_Pointer_Button4:
                            sx11MouseWheelUpReleased = 1;
                            break;

                        case 5: //XK_Pointer_Button5:
                            sx11MouseWheelDownReleased = 1;
                            break;
                   }
                   sx11MouseX = evento.xbutton.x;
                   sx11MouseY = evento.xbutton.y;
                }
                break;

            case MotionNotify:
                //Mouse moved
                {
                    sx11MouseX = evento.xbutton.x;
                    sx11MouseY = evento.xbutton.y;
                    sx11MouseMove = 1;
                }
                break;    

            case KeyPress:
                //Keyboard key pressed
                {
                    int count = XLookupString(&evento.xkey, buffer, bufsize, &keysym, NULL);
                    buffer[count] = '\0';  // Terminate string
            

                   //Check if key letter by letter
                   switch (keysym){
                   
                        case XK_a:
                        case XK_A:
                            sx11Keyboard_A_press = 1;
                            break;

                        case XK_w:
                        case XK_W:
                            sx11Keyboard_W_press = 1;
                            break;

                        case XK_s:
                        case XK_S:
                            sx11Keyboard_S_press = 1;
                            break;

                        case XK_d:
                        case XK_D:
                            sx11Keyboard_D_press = 1;
                            break;

                        case XK_q:
                        case XK_Q:
                            sx11Keyboard_Q_press = 1;
                            break;

                        case XK_e:
                        case XK_E:
                            sx11Keyboard_E_press = 1;
                            break;

                        case XK_r:
                        case XK_R:
                            sx11Keyboard_R_press = 1;
                            break;

                        case XK_Shift_L:
                        case XK_Shift_R:
                            sx11Keyboard_Shift_press = 1;
                            break;

                        case XK_Control_L:
                        case XK_Control_R:
                            sx11Keyboard_Ctrl_press = 1;
                            break;

                        case XK_space:
                            sx11Keyboard_Space_press = 1;
                            break;

                        case XK_1:
                            sx11Keyboard_1_press = 1;
                            break;

                        case XK_2:
                            sx11Keyboard_2_press = 1;
                            break;

                        case XK_3:
                            sx11Keyboard_3_press = 1;
                            break;

                        case XK_4:
                            sx11Keyboard_4_press = 1;
                            break;

                        case XK_Left:
                            sx11Keyboard_Arrow_Left_press = 1;
                            break;

                        case XK_Right:
                            sx11Keyboard_Arrow_Right_press = 1;
                            break;

                        case XK_Up:
                            sx11Keyboard_Arrow_Up_press = 1;
                            break;

                        case XK_Down:
                            sx11Keyboard_Arrow_Down_press = 1;
                            break;

                        case XK_Return:
                            sx11Keyboard_Enter_press = 1;
                            break;
                     
                        default:
                        break;
                   }
                }
                break;

            case KeyRelease:
                //Keyboard key pressed
                {
                    int count = XLookupString(&evento.xkey, buffer, bufsize, &keysym, NULL);
                    buffer[count] = '\0';  // Terminate string

                   //Check if key letter by letter
                    switch (keysym){
                   
                        case XK_a:
                        case XK_A:
                            sx11Keyboard_A_released = 1;
                            break;

                        case XK_w:
                        case XK_W:
                            sx11Keyboard_W_released = 1;
                            break;

                        case XK_s:
                        case XK_S:
                            sx11Keyboard_S_released = 1;
                            break;

                        case XK_d:
                        case XK_D:
                            sx11Keyboard_D_released = 1;
                            break;

                        case XK_q:
                        case XK_Q:
                            sx11Keyboard_Q_released = 1;
                            break;

                        case XK_e:
                        case XK_E:
                            sx11Keyboard_E_released = 1;
                            break;

                        case XK_r:
                        case XK_R:
                            sx11Keyboard_R_released = 1;
                            break;

                        case XK_Shift_L:
                        case XK_Shift_R:
                            sx11Keyboard_Shift_released = 1;
                            break;

                        case XK_Control_L:
                        case XK_Control_R:
                            sx11Keyboard_Ctrl_released = 1;
                            break;

                        case XK_space:
                            sx11Keyboard_Space_released = 1;
                            break;

                        case XK_1:
                            sx11Keyboard_1_released = 1;
                            break;

                        case XK_2:
                            sx11Keyboard_2_released = 1;
                            break;

                        case XK_3:
                            sx11Keyboard_3_released = 1;
                            break;

                        case XK_4:
                            sx11Keyboard_4_released = 1;
                            break;

                        case XK_Left:
                            sx11Keyboard_Arrow_Left_released = 1;
                            break;

                        case XK_Right:
                            sx11Keyboard_Arrow_Right_released = 1;
                            break;

                        case XK_Up:
                            sx11Keyboard_Arrow_Up_released = 1;
                            break;

                        case XK_Down:
                            sx11Keyboard_Arrow_Down_released = 1;
                            break;

                        case XK_Return:
                            sx11Keyboard_Enter_released = 1;
                            break;
                 
                        default:
                        break;
                   }
                }
                break;

            case ClientMessage: 
                if ((Atom) evento.xclient.data.l[0] == sx11DeleteComand) {
                    //send close window message
                    closeWindowEvent = 1;
                }    

            default:
                break;
        }
    }
    return eventExist;
}

void Sx11ClearButtons(){
    //Clear all buttons variables from keyboard and mouse.
    //Mouse
    sx11MouseLeftPress = 0;  
    sx11MouseMiddlePress = 0; 
    sx11MouseRightPress = 0; 
    sx11MouseWheelUpPress = 0; 
    sx11MouseWheelDownPress = 0;   
    sx11MouseLeftReleased = 0;   
    sx11MouseMiddleReleased = 0; 
    sx11MouseRightReleased = 0;  
    sx11MouseWheelUpReleased = 0;     
    sx11MouseWheelDownReleased = 0;
    sx11MouseMove = 0;

    //Keyboard
    sx11Keyboard_A_press = 0;
    sx11Keyboard_W_press = 0;
    sx11Keyboard_S_press = 0;
    sx11Keyboard_D_press = 0;
    sx11Keyboard_Q_press = 0;
    sx11Keyboard_E_press = 0;
    sx11Keyboard_R_press = 0;
    sx11Keyboard_Shift_press = 0;
    sx11Keyboard_Ctrl_press = 0;
    sx11Keyboard_Space_press = 0;
    sx11Keyboard_1_press = 0;
    sx11Keyboard_2_press = 0;
    sx11Keyboard_3_press = 0;
    sx11Keyboard_4_press = 0;
    sx11Keyboard_Arrow_Left_press = 0;
    sx11Keyboard_Arrow_Right_press = 0;
    sx11Keyboard_Arrow_Up_press = 0;
    sx11Keyboard_Arrow_Down_press = 0;
    sx11Keyboard_Enter_press = 0;

    sx11Keyboard_A_released = 0;
    sx11Keyboard_W_released = 0;
    sx11Keyboard_S_released = 0;
    sx11Keyboard_D_released = 0;
    sx11Keyboard_Q_released = 0;
    sx11Keyboard_E_released = 0;
    sx11Keyboard_R_released = 0;
    sx11Keyboard_Shift_released = 0;
    sx11Keyboard_Ctrl_released = 0;
    sx11Keyboard_Space_released = 0;
    sx11Keyboard_1_released = 0;
    sx11Keyboard_2_released = 0;
    sx11Keyboard_3_released = 0;
    sx11Keyboard_4_released = 0;
    sx11Keyboard_Arrow_Left_released = 0;
    sx11Keyboard_Arrow_Right_released = 0;
    sx11Keyboard_Arrow_Up_released = 0;
    sx11Keyboard_Arrow_Down_released = 0;
    sx11Keyboard_Enter_released = 0;
}

int Sx11GetCloseWindowEvent(){
    return closeWindowEvent;
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

void Sx11Flush(){
    //refresh screen to show new drawings.
    XFlush(sx11Monitor);
}