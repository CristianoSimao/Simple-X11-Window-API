# Simple-X11-Window-API
A simple X11 API to create basic windows in Linux.<br>
<pre>    X Window System (X11) is the default API to create windows in Linux. This is a very old API
projected to work trought internet. Because of this old style of programming compared to
today standards, this API can consume some days of study and research until you get a
simple window working in your screen. The X Window System work in a asynchronous way complicating
a little more the things.
    Then I decided create this Simple X11 API to create windows in Linux. This will offer basic
functions to create windows in C programing language and some example codes.</pre>
<br>
   Functions:
<br>
<pre>
   - <b>Sx11Init()</b>                  Configure the initial steps to create windows.<br>
   - <b>Sx11CreateWindow()</b>          Create a basic window.<br>
   - <b>Sx11SetFullScreen()</b>         Make the window fullscreen.<br>
   - <b>Sx11SetScreenResolution()</b>   Change the resolution of the screen monitor to other modes.<br>
   - <b>Sx11DrawString()</b>            Print text to the window.<br>
   - <b>Sx11DrawLine()</b>              Draw a line in the window.<br>
   - <b>Sx11DrawPixel()</b>             Draw a pixel in the window.<br>
   - <b>Sx11GetEvents()</b>             Capture keyboard and mouse events.<br>
   - <b>Sx11End()</b>                   Close the window and delete all resources.<br> 
   </pre>

  Read the SimpleX11API.h file to discover how the things work.<br>
  Below is some links used as reference to create this project.<br>
  
  You need the **libx11-dev** installed in your system to compile.<br>
  Compile the example01.c with the command: **gcc example01.c -lX11 example01**<br>
  
  Example01.c will produce the window below:<br>
  
  ![Simple X11 Window test](example01.jpg?raw=true "Simple X11 Window API test")
  
  <br>
  
  # References:
  If you want learn how X Window System works, you can see this video showing all steps <br>and all little details of each function: https://youtu.be/764fnfEb1_c
    <br>
    The official X Window API here: http://www.x.org/releases/X11R7.7/doc/libX11/libX11/libX11.pdf
    <br>
    Other documentations: https://www.x.org/releases/X11R7.7/doc/index.html
    <br>
