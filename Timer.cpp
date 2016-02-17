/* ****************************************************************
 * Timer.cpp
 *
 * Implementation of the Timer utility classes and methods.
 *
 * Revision History:
 *
 * $Id: Timer.cpp,v 1.2 2011/10/29 16:22:57 robert Exp $
 *
 * $Log: Timer.cpp,v $
 * Revision 1.2  2011/10/29 16:22:57  robert
 * Corrected error in timer when countdown reaches 1 minute.
 * The original version jumps directly to 0:0:0 as soon as the
 * clock reaches 0:1:0.
 *
 * Revision 1.1.1.1  2005/05/20 00:06:03  robert
 * Initial import into CVS.
 *
 *
 *
 * 
 * ******************************************************************/
#include <string.h>
#include <QApplication>
#include "Timer.hpp"

OrasanDialogAgent::OrasanDialogAgent(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    this->setWindowTitle(tr("Task Timer"));

    csecond = chour = cminute = 0;
    timeRemaining = 0;

    // Set up the contents of the minute and hour
    // selector boxes.
    int idx = 0;
    char buf[32];
    for (int v = 0; v < 60; v += 5) {
        sprintf(buf, "%d", v);
	minuteSelectBox->insertItem(idx++, tr(buf));
    }

    idx = 0;
    for (int v = 0; v < 6; ++v) {
        sprintf(buf, "%d", v);
	hourSelectBox->insertItem(idx++, tr(buf));
    }

    connect(hourSelectBox, SIGNAL(activated(int)),
	    this, SLOT(hourChanged(int)));
    connect(minuteSelectBox, SIGNAL(activated(int)),
	    this, SLOT(minuteChanged(int)));
    connect(resetButton, SIGNAL(clicked()),
	    this, SLOT(resetButtonHandler()));
    connect(cmdButton, SIGNAL(clicked()), 
	    this, SLOT(cmdButtonHandler()));

    // Now we prepare the QTimer object which will do the actual
    // timer count.
    tickCount = 0;
    timerMode = TASKTIMER::NOTREADY;
    oneSecTimer = new QTimer();
    connect(oneSecTimer, SIGNAL(timeout()), this, SLOT(update()));
}


// resetButtonHandler() is called each time the reset button
// is pushed.
void OrasanDialogAgent::resetButtonHandler(void)
{

    switch(timerMode) {
	case TASKTIMER::PAUSED:
	    cmdButton->setText(tr("Start"));
	    timerMode = TASKTIMER::READY;
	    // Fall through
	    //
	case TASKTIMER::READY:
	    timeRemaining = 0; 
	    chour = cminute = csecond = 0;
	    lcdHour->display(chour);
	    lcdMinute->display(cminute);
	    lcdSecond->display(csecond);
	    hourSelectBox->setCurrentIndex(chour);
	    minuteSelectBox->setCurrentIndex(cminute);
	    break;
    }
}



// This handler is called whenever the hour
// value changes. 
//
void OrasanDialogAgent::hourChanged(int idx)
{
    chour = idx;
    lcdHour->display(chour);
    if (idx != 0) {
	timerMode = TASKTIMER::READY;
    }
}


void OrasanDialogAgent::minuteChanged(int idx)
{
    cminute = idx*5;
    lcdMinute->display(cminute);
    if (idx != 0) {
	timerMode = TASKTIMER::READY;
    }
}

// Updates the tickcount.
void OrasanDialogAgent::update(void)
{
    int tempValue;

    --timeRemaining;

    if (timeRemaining >= 0) {

	// how many hours are in timeRemaining?
	//
	chour = timeRemaining/3600;

	// How many minutes?
	// tempValue is a scratch variable that will contain
	// the number of minutes off the hour that is in
	// timeRemaining.
	//
	tempValue = timeRemaining - chour*3600;
	cminute = tempValue/60; 

	// And how many seconds?
	//
	csecond = timeRemaining % 60;

	lcdHour->display(chour);
	lcdMinute->display(cminute);
	lcdSecond->display(csecond);
    }
    else {
	oneSecTimer->stop();
	timerMode = TASKTIMER::READY;
	resetButtonHandler();
        cmdButton->setText(tr("Start"));
        return;
    }
}


// This function is called whenever the cmdButton is pressed.
// The action which this handler performs is dependent on the current
// state of the timerMode.
//
void OrasanDialogAgent::cmdButtonHandler(void)
{
    int tempValue;

    timeRemaining = csecond + cminute*60 + chour*3600;

    if (timeRemaining == 0) return;         // Do nothing if no set.

    switch(timerMode) {
	case TASKTIMER::READY:

	    --timeRemaining;    // Decrement by 1 second.

	    // how many hours are in timeRemaining?
	    //
            chour = timeRemaining/3600;

	    // How many minutes?
	    // tempValue is a scratch variable that will contain
	    // the number of minutes off the hour that is in
	    // timeRemaining.
	    //
	    tempValue = timeRemaining - chour*3600;
	    cminute = tempValue/60; 

	    // And how many seconds?
	    //
	    csecond = timeRemaining % 60;

	    timerMode = TASKTIMER::RUNNING;
	    
            lcdHour->display(chour);
            lcdMinute->display(cminute);
	    lcdSecond->display(csecond);
	    cmdButton->setText(tr("Pause"));

            // Now start timer to send timeout() signal 
	    // every 1000 millisecs.
            oneSecTimer->start(1000);
	    break;
	case TASKTIMER::RUNNING:
	    oneSecTimer->stop();
	    cmdButton->setText(tr("Continue"));
	    timerMode = TASKTIMER::PAUSED;
	    break;
	case TASKTIMER::PAUSED:
	    oneSecTimer->start(1000);
	    cmdButton->setText(tr("Pause"));
	    timerMode = TASKTIMER::RUNNING;
	    break;
    }

}

