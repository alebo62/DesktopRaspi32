#include "MainWindow.h"

void MainWindow::sig_slot_init()
{
	for (int i = 0; i < reader->udp_num; i++)
	{
		connect(pb_ptt[i], SIGNAL(pressed()), this, SLOT(ptt_pressed()));
		connect(pb_ptt[i], SIGNAL(released()), this, SLOT(ptt_released()));
	
		connect(pb_ch_up[i], SIGNAL(clicked()), this, SLOT(ch_up_slot()));
		connect(pb_ch_dwn[i], SIGNAL(clicked()), this, SLOT(ch_dwn_slot()));
		
		connect(pb_gr1[i], SIGNAL(clicked()), this, SLOT(gr1_slot()));
		connect(pb_gr2[i], SIGNAL(clicked()), this, SLOT(gr2_slot()));
		connect(pb_gr3[i], SIGNAL(clicked()), this, SLOT(gr3_slot()));
		connect(pb_gr4[i], SIGNAL(clicked()), this, SLOT(gr4_slot()));
		
		connect(pb_ab1[i], SIGNAL(clicked()), this, SLOT(ab1_slot()));
		connect(pb_ab2[i], SIGNAL(clicked()), this, SLOT(ab2_slot()));
		connect(pb_ab3[i], SIGNAL(clicked()), this, SLOT(ab3_slot()));
		connect(pb_ab4[i], SIGNAL(clicked()), this, SLOT(ab4_slot()));
		
	}
}