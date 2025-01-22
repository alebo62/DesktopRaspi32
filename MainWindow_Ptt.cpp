#include "MainWindow.h"
#include "ui_MainWindow.h"

void MainWindow::ptt_pressed()
{
	
	emit(sig_ptt(1));
}

void MainWindow::ptt_released()
{
	
	emit(sig_ptt(0));
}


// Принимаем сигнал от hid
void MainWindow::slot_ptt(int i)
{
	
}
