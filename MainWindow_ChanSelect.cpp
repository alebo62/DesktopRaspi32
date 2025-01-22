#include "MainWindow.h"
#include "ui_MainWindow.h"

void MainWindow::ch_dwn_slot()
{
	int val = ui->lcdNumber_Chan->intValue();
	
	if (val > 1)
	{
		
		val--;
		udp->select_channel(val, 0);//tx_rcp);
		ui->lcdNumber_Chan->display(val);		
	}
	
}
void MainWindow::ch_up_slot()
{
	int val = ui->lcdNumber_Chan->intValue();
	
	if (val < reader->max_chan[0])
	{
		val++;
		udp->select_channel(val, 0);//tx_rcp);
		ui->lcdNumber_Chan->display(val);			
	}	
}