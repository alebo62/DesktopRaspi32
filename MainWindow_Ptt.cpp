#include "MainWindow.h"
#include "ui_MainWindow.h"

void MainWindow::ptt_pressed()
{
	udp->make_call(10, eGroupCall, 0);
	emit(sig_ptt(1));
}

void MainWindow::ptt_released()
{
	udp->make_stop_call(0);
	emit(sig_ptt(0));
}


// Принимаем сигнал от hid
void MainWindow::slot_ptt(int i)
{
	
}
