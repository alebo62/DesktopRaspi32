#include "MainWindow.h"
#include "ui_MainWindow.h"

void MainWindow::ptt_pressed()
{
	//int i = sender()->objectName().last(1).toInt();
	udp->make_call(10, eGroupCall, tab->currentIndex());
	emit(sig_ptt(1));
}

void MainWindow::ptt_released()
{
	udp->make_stop_call(tab->currentIndex());
	emit(sig_ptt(0));
}


// Принимаем сигнал от hid
void MainWindow::slot_ptt(int i)
{
	
}
