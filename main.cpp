/* ********************************************************************
 * main.cpp
 *
 * Main application source for the application named Timer.
 *
 * Timer is a tool for battling procrastination. You run the
 * Timer tool, set a minimum time for which you shall be working
 * on a task and then start the timer. The timer shall then
 * couunt down the time. Hopefully, seeing the timer should
 * allow you to discipline yourself to work at a given task for
 * a set amount of time.
 *
 * It works for me.
 *
 * MANTRA: I AM A PROCRASTINATOR. BUT I WANT TO CHANGE.
 *
 * Revision History:
 *
 * $Id: main.cpp,v 1.1.1.1 2005/05/20 00:06:02 robert Exp $
 *
 * $Log: main.cpp,v $
 * Revision 1.1.1.1  2005/05/20 00:06:02  robert
 * Initial import into CVS.
 *
 *
 *
 * *******************************************************************/
#include "Timer.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    OrasanDialogAgent *mainDialog = new OrasanDialogAgent();
    mainDialog->show();
    return app.exec();
}

