#include <windows.h>
#include <stdio.h>


LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

HWND value1,value2,value3,value4,button1,button2,button3,button4,window;


char szClassName[ ] = ("Calculator");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               
    MSG messages;            
    WNDCLASSEX wincl;        

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      
    wincl.style = CS_DBLCLKS;                 
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                
    wincl.cbClsExtra = 0;                     
    wincl.cbWndExtra = 0;                     
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   
           szClassName,        
           ("Calculator"),       
           WS_OVERLAPPEDWINDOW, 
           500,       
           300,      
           380,      
           110,       
           HWND_DESKTOP,       
           NULL,                
           hThisInstance,       
           NULL                
           );

    /* Remove the console window */
    window = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow (window, 0);

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    char num1[100],num2[100], out[100];
    float first, second;
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:

        value1 = CreateWindow("EDIT",
                                 NULL,
                                  WS_VISIBLE | WS_CHILD | WS_BORDER ,
                                  10,10,100,20,
                                  hwnd,NULL,NULL,NULL);

        value2 = CreateWindow("EDIT",
                                 NULL,
                                  WS_VISIBLE | WS_CHILD |WS_BORDER ,
                                  120,10,100,20,
                                  hwnd,NULL,NULL,NULL);

        value3 = CreateWindow("STATIC",
                                 " = ",
                                  WS_VISIBLE | WS_CHILD ,
                                  230,12,15,10,
                                  hwnd,NULL,NULL,NULL);

        value4 = CreateWindow("STATIC",
                                 "",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER ,
                                  255,10,100,20,
                                  hwnd,NULL,NULL,NULL);

        button1 = CreateWindow("BUTTON",
                              "Add",
                              WS_VISIBLE | WS_CHILD | WS_BORDER,
                              67,40,50,20,
                              hwnd,(HMENU) 1,NULL,NULL);

        button2 = CreateWindow("BUTTON",
                              "Sub",
                              WS_VISIBLE | WS_CHILD | WS_BORDER,
                              127,40,50,20,
                              hwnd,(HMENU) 2,NULL,NULL);

        button3 = CreateWindow("BUTTON",
                              "Mul",
                              WS_VISIBLE | WS_CHILD | WS_BORDER,
                              187,40,50,20,
                              hwnd,(HMENU) 3,NULL,NULL);

        button4 = CreateWindow("BUTTON",
                              "Div",
                              WS_VISIBLE | WS_CHILD | WS_BORDER,
                              244,40,50,20,
                              hwnd,(HMENU) 4,NULL,NULL);

        break;
        case WM_COMMAND:


        switch (LOWORD(wParam))
        {
            case 1:
            GetWindowText(value1,num1,100);
            GetWindowText(value2,num2,100);

            sscanf(num1,"%f",&first);
            sscanf(num2,"%f",&second);

            float result = first+second;
            sprintf(out,"%f",result);

            SetWindowText(value4,out);

            break;

            case 2:
            GetWindowText(value1,num1,100);
            GetWindowText(value2,num2,100);

            sscanf(num1,"%f",&first);
            sscanf(num2,"%f",&second);

            result = first-second;
            sprintf(out,"%f",result);

            SetWindowText(value4,out);

            break;

            case 3:
            GetWindowText(value1,num1,100);
            GetWindowText(value2,num2,100);

            sscanf(num1,"%f",&first);
            sscanf(num2,"%f",&second);

            result = first*second;
            sprintf(out,"%f",result);

            SetWindowText(value4,out);

            break;

            case 4:
            GetWindowText(value1,num1,100);
            GetWindowText(value2,num2,100);

            sscanf(num1,"%f",&first);
            sscanf(num2,"%f",&second);

            result = first/second;
            sprintf(out,"%f",result);

            SetWindowText(value4,out);

            break;
        }
        break;

        case WM_DESTROY:
            PostQuitMessage (0);       
            break;
        default:                      
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}