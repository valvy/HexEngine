//#include "prutengine/platform/gnu_linux/GnuXApp.hpp"
#include "prutengine/Application.hpp"
#include "prutengine/platform/OpenGL.hpp"
#include <cstdlib>
#include "GL/glxext.h"
#include "GL/glext.h"
#include <X11/Xlib.h>
#include "prutengine/PrutWindow.hpp"
#include "prutengine/exceptions/InitializationException.hpp"
#include "prutengine/exceptions/NotYetInitializedException.hpp"

using namespace PrutEngine;
using namespace PrutEngine::Math;

namespace{
    Display * dpy;
    Window root;
    GLXContext glc;
    Window win;

    typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
    
}


void Application::clean(){
    //delete GnuXApp::instance;
}


PrutWindow::PrutWindow(){
    
}

void PrutWindow::setWindowTitle(const std::string& title){
    Exceptions::assertNotYetInitialized(dpy == nullptr,"Display is not yet initialized");
    XStoreName(dpy, win, title.c_str());
}

Vector4f PrutWindow::getWindowSize() const{
    XWindowAttributes xwa;
    XGetWindowAttributes(dpy, win, &xwa);
    return Vector4f(xwa.x,xwa.y, xwa.width,xwa.height);
}


bool Application::canUseAppleMetal() const {
    return false;
}


void Application::run(){
    const auto rend = this->setRenderer();
    this->graphicsController = std::shared_ptr<GraphicsController>(new GraphicsController(rend));
    static int visual_attribs[] ={
        GLX_X_RENDERABLE    , True,
        GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
        GLX_RENDER_TYPE     , GLX_RGBA_BIT,
        GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
        GLX_RED_SIZE        , 8,
        GLX_GREEN_SIZE      , 8,
        GLX_BLUE_SIZE       , 8,
        GLX_ALPHA_SIZE      , 8,
        GLX_DEPTH_SIZE      , 24,
        GLX_STENCIL_SIZE    , 8,
        GLX_DOUBLEBUFFER    , True,
        None
    };

    dpy = XOpenDisplay(nullptr);

    if(dpy == nullptr) {    
        throw Exceptions::InitializationException("Could not open display");
    }

    int fbcount;
    GLXFBConfig *fbc = glXChooseFBConfig( dpy, DefaultScreen( dpy ), 
    visual_attribs, &fbcount );

    const GLXFBConfig bestFbc = fbc[0];
    
    XVisualInfo *vi = glXGetVisualFromFBConfig( dpy, bestFbc );
    root = DefaultRootWindow(dpy);

    if(vi == nullptr) {
        glXMakeCurrent(dpy, None, nullptr);
        glXDestroyContext(dpy, glc);
        XDestroyWindow(dpy, win);
        XCloseDisplay(dpy);
        throw Exceptions::InitializationException("No appropiate visual found");
    } 
    Colormap    cmap;
    
    cmap = XCreateColormap(dpy,root, vi->visual, AllocNone);
    XSetWindowAttributes swa;
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask;

    XWindowAttributes xwa;
    XGetWindowAttributes(dpy, DefaultRootWindow(dpy), &xwa);
    
    win = XCreateWindow(dpy, root, xwa.x, xwa.y, xwa.width, xwa.height, 0, vi->depth, InputOutput, vi->visual,CWColormap | CWEventMask, &swa);

    
    XMapRaised(dpy,root);
    XMapWindow(dpy, win);
    XStoreName(dpy, win, "Powered by PrutEngine");
    int attribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 1,
        0
    };

    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
    glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");

    glc = glXCreateContextAttribsARB(dpy, *fbc, 0, true, attribs);
    glXMakeCurrent(dpy, win, glc); 

    GLenum err = glewInit();
    if (GLEW_OK != err){
        glXMakeCurrent(dpy, None, nullptr);
        glXDestroyContext(dpy, glc);
        XDestroyWindow(dpy, win);
        XCloseDisplay(dpy);
        throw Exceptions::InitializationException("glew crashed");
    }

    if (!GLEW_VERSION_4_1){
        glXMakeCurrent(dpy, None, nullptr);
        glXDestroyContext(dpy, glc);
        XDestroyWindow(dpy, win);
        XCloseDisplay(dpy);
        throw Exceptions::InitializationException("Invalid OpenGL");
    }
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    //Make sure when the user press the exit button.. it cleans everything up
    Atom              wm_protocols;
    Atom              wm_delete_window;
    wm_protocols = XInternAtom(dpy, "WM_PROTOCOLS", False);
    wm_delete_window = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(dpy, win, &wm_delete_window, 1);
    XEvent  xev;
    this->awake();
    //Start looping
    for(;;){
        if(this->shouldStop){     
            break; //stop when the app asks for it
        }
        while(XPending(dpy)){//Do not hang the app while waiting for input
            XNextEvent(dpy, &xev);
    
            if(xev.type == KeyPress) {
                this->keyDown(xev.xkey.keycode);
            }else if (xev.xclient.message_type == wm_protocols/* &&
                xev.xclient.data.l[0] == wm_delete_window*/)  {
                //this->shouldStop = true;
                this->quit();
                break;
            }
        
        }
        if(this->shouldStop){     
            break; //stop when the app asks for it
        }
        //Render the program
        Application::getInstance()->loop();
       // this->mainApp->gameLoop();      
        glFlush();
        glXSwapBuffers(dpy, win);
    }
    glXMakeCurrent(dpy, None, nullptr);
    glXDestroyContext(dpy, glc);
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
    std::exit(EXIT_SUCCESS); //To be compliant with MacOS exit :*(
}

