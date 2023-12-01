#include <iostream>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdio.h>
#include <stdlib.h>

Display *dis;
int screen;
Window win;
GC gc;
unsigned long black, white, red, blue;

void init();
void close();
void draw();
unsigned long RGB(int r, int g, int b);

XEvent  event;
KeySym key;
char text[255];
struct coord {
    int x, y;
}dot;

int main(){
    init();
    while(1){
        XNextEvent(dis, &event);
        if(event.type == Expose && event.xexpose.count == 0){
            draw();  
        }
        if(event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key,0)==1){
            if(text[0] == 'q'){
                close();
            }
            std::cout<<"You pressed"<<text[0];
        }
        if(event.type == ButtonPress){
            int x = event.xbutton.x, y=event.xbutton.y;
            XSetForeground(dis, gc,red);
            XDrawLine(dis,win,gc,dot.x,dot.y,x,y);
            XSetForeground(dis,gc,blue);
            strcpy(text,"Hello World");
            XDrawString(dis,win,gc,x,y,text,strlen(text));
            dot.x = x;
            dot.y = y;
        }
    }
    std::cout<<"Hello"<<std::endl;
    return 0;
}

void init(){
    dot.x = 100;
    dot.y = 100;
    dis = XOpenDisplay((char *)0);
    screen = DefaultScreen(dis);
    black = BlackPixel(dis,screen);
    white = WhitePixel(dis,screen);
    blue = RGB(0,0,255);
    red = RGB(255,0,0);
    win = XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,300,300,6,white,black);
    XSetStandardProperties(dis, win, "Hey","HI",None,NULL,0,NULL);
    XSelectInput(dis, win, ExposureMask | ButtonPressMask | KeyPressMask);
    gc = XCreateGC(dis,win,0,0);
    XSetBackground(dis,gc,white);
    XSetForeground(dis,gc,black);
    XClearWindow(dis,win);
    XMapRaised(dis, win);
}

void close(){
    XFreeGC(dis,gc);
    XDestroyWindow(dis,win);
    XCloseDisplay(dis);
    exit(0);
}

void draw(){
    XClearWindow(dis,win);
}


unsigned long RGB(int r, int g, int b){
    return b + (g<<8) + int(r<<16);
}