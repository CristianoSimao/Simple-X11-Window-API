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
   - <b>Sx11ClearButtons()</b>          Clear all keyboard and mouse global variables.<br>
   - <b>Sx11End()</b>                   Close the window and delete all resources.<br> 
   - <b>Sx11Flush()</b>                 Refresh the screen.
   </pre>

  Here you can see the details for all functions: <a href="https://github.com/CristianoSimao/Simple-X11-Window-API/blob/main/Simple%20X11%20Window%20API.pdf">Simple X11 Window API - PDF</a>

  Read the SimpleX11API.c file to discover how the things work.<br>
  Below is some links used as reference to create this project.<br>
  
  You need the **libx11-dev** and **libxrandr-dev** installed in your system to compile.<br>
  To install the libs execute **sudo apt install libx11-dev libxrandr-dev**<br>
  <br>
  Compile the example.c with the command: **gcc \*c -lX11 -lXrandr -o example**<br>
  Execute the program with **./example** to see the messages of buttons pressed.<br>
  
  Example.c will produce the window below:<br>
  
  ![Simple X11 Window test](example01.jpg?raw=true "Simple X11 Window API test")
  
  <br>
  
  # References:
  If you want learn how X Window System works, you can see this video showing all steps <br>and all little details of each function: https://youtu.be/764fnfEb1_c
    <br>
    The official X Window API here: http://www.x.org/releases/X11R7.7/doc/libX11/libX11/libX11.pdf
    <br>
    Other documentations: https://www.x.org/releases/X11R7.7/doc/index.html
    <br>
