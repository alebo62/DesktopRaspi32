#include "MainWindow.h"
#include "ui_MainWindow.h"

void MainWindow::ch_dwn_slot()
{
	int val = ui->lcdNumber_Chan1->intValue();
	
	if (val > 1)
	{
		
		val--;
		udp->select_channel(val, 0);//tx_rcp);
		ui->lcdNumber_Chan1->display(val);
		chan_change_state = 0;
	}
	
}
void MainWindow::ch_up_slot()
{
	int val = ui->lcdNumber_Chan1->intValue();
	
	if (val < reader->max_chan[0])
	{
		val++;
		udp->select_channel(val, 0);//tx_rcp);
		ui->lcdNumber_Chan1->display(val);
		chan_change_state = 0;
	}	
}