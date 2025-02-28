#include "MainWindow.h"
#include "ui_MainWindow.h"

void MainWindow::ch_dwn_slot()
{
	int val = lcdNumber[current_index]->intValue();
	
	if (val > 1)
	{
		
		val--;
		//udp->select_channel(val, 0);//tx_rcp); если нет соединения - зависает!!!
		lcdNumber[current_index]->display(val);
		chan_change_state = 0;
		
		load_contacts(current_index, val);
	}
	
}
void MainWindow::ch_up_slot()
{
	int val = lcdNumber[current_index]->intValue();
	
	if (val < reader->radio[current_index].channels)
	{
		val++;
		//udp->select_channel(val, 0);//tx_rcp); если нет соединения - зависает!!!
		lcdNumber[current_index]->display(val);
		chan_change_state = 0;
		
		load_contacts(current_index, val);
	}	
}