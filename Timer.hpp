/* ***********************************************************************
 * Timer.hpp
 *
 * Class definitions required by the Timer application.
 *
 * Revision History:
 *
 * $Id: Timer.hpp,v 1.2 2011/10/29 16:23:41 robert Exp $
 *
 * $Log: Timer.hpp,v $
 * Revision 1.2  2011/10/29 16:23:41  robert
 * Added the private variable timeRemaining. This is done to correct
 * an error in the update() handler during the countdown.
 *
 * Revision 1.1.1.1  2005/05/20 00:06:03  robert
 * Initial import into CVS.
 *
 *
 *
 * ***********************************************************************/
#ifndef TIMER_HPP
#define TIMER_HPP

#include <QtGui>
#include <QDialog>

#include "ui_Orasan.h"

namespace TASKTIMER {
    enum {
	NOTREADY, READY, RUNNING, PAUSED
    };
}


class OrasanDialogAgent : public QDialog, public Ui::OrasanDialog
{
    Q_OBJECT

    public:
	OrasanDialogAgent(QWidget *parent = 0);


    private slots:
        void resetButtonHandler(void);
        void hourChanged(int);
	void minuteChanged(int);
	void cmdButtonHandler(void);
	void update();
	
    private:
	int chour, cminute, csecond;    // Current hour, minute, second.
	int timeRemaining;              // Number of seconds remaining in
	                                // countdown.
	QTimer *oneSecTimer;   // The one second timer.
	int tickCount;
	void doneTask(void);   // Call this after task has been done.
	int timerMode;         // Enumeration from TASKTIMER
};

#endif

