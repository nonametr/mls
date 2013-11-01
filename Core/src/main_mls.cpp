#include <qapplication>
#include <qwidget.h>
#include <qtranslator.h>

#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#include "global.h"
#include "settings.h"
#include "gui_login.h"
#include "gui_main.h"

MlsMain *main_window = NULL;

void redirectIOToConsole( )
{
    int hConHandle;
    long lStdHandle;
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    FILE *fp;

    // Allocate a console for this app
    AllocConsole();

    // Set the screen buffer to be big enough to let us scroll text
    GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &coninfo );
    //coninfo.dwSize.Y = 400; // Number of console lines
    SetConsoleScreenBufferSize( GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize );

    // Redirect unbuffered STDOUT to the console
    lStdHandle = (long)GetStdHandle( STD_OUTPUT_HANDLE );
    hConHandle = _open_osfhandle( lStdHandle, _O_TEXT );
    fp = _fdopen( hConHandle, "w" );
    *stdout = *fp;
    setvbuf( stdout, NULL, _IONBF, 0 );

    // Redirect unbuffered STDIN to the console
    lStdHandle = (long)GetStdHandle( STD_INPUT_HANDLE );
    hConHandle = _open_osfhandle( lStdHandle, _O_TEXT );
    fp = _fdopen( hConHandle, "r" );
    *stdin = *fp;
    setvbuf( stdin, NULL, _IONBF, 0 );

    // Redirect unbuffered STDERR to the console
    lStdHandle = (long)GetStdHandle( STD_ERROR_HANDLE );
    hConHandle = _open_osfhandle( lStdHandle, _O_TEXT );
    fp = _fdopen( hConHandle, "w" );
    *stderr = *fp;
    setvbuf( stderr, NULL, _IONBF, 0 );

    // Make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
    // point to console as well.
    std::ios::sync_with_stdio();
}

int main(int argc, char *argv[])
{	
	redirectIOToConsole();
    traceerr("%s", "Starting MediaLiveSync...");
    traceerr("%s", "Loading configuration...");
    Settings::load();

    QApplication mls_app(argc, argv);

    QSqlRecord current_language = settings->query("SELECT value as name FROM property WHERE name = 'language'").record();
    traceerr("Loading '%s' translation", current_language.value("name").toString().toStdString().c_str());
    QTranslator translator;
    translator.load("./translations/" + current_language.value("name").toString());
    mls_app.installTranslator(&translator);

    main_window = new MlsMain;
    main_window->setWindowFlags(Qt::FramelessWindowHint);
    main_window->show();

    traceerr("%s", "...started successfully");
    return mls_app.exec();
}
