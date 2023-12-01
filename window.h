//creates a window
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdio.h>
#include <stdlib.h>


class window
{
private:

public:
    window();
    window(const window&) = delete;
    window& operator =(const window&) = delete;
    ~window();

    bool ProcessMessages();

};

