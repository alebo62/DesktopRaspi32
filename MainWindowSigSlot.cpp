#include "MainWindow.h"

void MainWindow::sig_slot_init()
{
	for (int i = 0; i < reader->server.directions; i++)
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
		
		connect(pb_add_ch[i], SIGNAL(pressed()), this, SLOT(add_ch_click_slot()));
		connect(pb_add_ch[i], SIGNAL(released()), this, SLOT(add_ch_release_slot()));
		
		connect(combo_ab[i], SIGNAL(textHighlighted(const QString&)), this, SLOT(cb_ab_slot(const QString&)));
		connect(combo_gr[i], SIGNAL(textHighlighted(const QString&)), this, SLOT(cb_gr_slot(const QString&)));
		
	}
	connect(&pb_add_Timer, SIGNAL(timeout()), this, SLOT(pb_add_Timer_slot()));
}


void MainWindow::gr1_slot()
{
	// надо при изменении канала обновлять список избранных
	if (pb_add_ch[current_index]->palette() == palet)
	{
		if (pb_gr1[current_index]->text() != "")
		{
			pb_add_ch[current_index]->setText(pb_gr1[current_index]->text());
			current_call_type = GROUP;
		}
	}
	else
	{
		if (current_call_type == GROUP)
		{
			QString s = pb_add_ch[current_index]->text();
			pb_gr1[current_index]->setText(s);
			update_favorites(current_index, current_channel, 0, s);
		}
		pb_add_ch[current_index]->setPalette(palet);
	}
}


void MainWindow::gr2_slot()
{
	if (pb_add_ch[current_index]->palette() == palet)
	{
		if (pb_gr2[current_index]->text() != "")
		{
			pb_add_ch[current_index]->setText(pb_gr2[current_index]->text());
			current_call_type = GROUP;
		}
	}
	else
	{
		if (current_call_type == GROUP)
		{
			QString s = pb_add_ch[current_index]->text();
			pb_gr2[current_index]->setText(s);
			update_favorites(current_index, current_channel, 1, s);
		}
		pb_add_ch[current_index]->setPalette(palet);
	}
}


void MainWindow::gr3_slot()
{
	if (pb_add_ch[current_index]->palette() == palet)
	{
		if (pb_gr3[current_index]->text() != "")
		{
			pb_add_ch[current_index]->setText(pb_gr3[current_index]->text());
			current_call_type = GROUP;
		}
	}
	else
	{
		if (current_call_type == GROUP)
		{
			QString s = pb_add_ch[current_index]->text();
			pb_gr3[current_index]->setText(s);
			update_favorites(current_index, current_channel, 2, s);
		}
		pb_add_ch[current_index]->setPalette(palet);
	}
}

void MainWindow::gr4_slot()
{
	if (pb_add_ch[current_index]->palette() == palet)
	{
		if (pb_gr4[current_index]->text() != "")
		{
			pb_add_ch[current_index]->setText(pb_gr4[current_index]->text());
			current_call_type = GROUP;
		}
	}
	else
	{
		if (current_call_type == GROUP)
		{
			QString s = pb_add_ch[current_index]->text();
			pb_gr4[current_index]->setText(s);
			update_favorites(current_index, current_channel, 3, s);
		}
		pb_add_ch[current_index]->setPalette(palet);
	}	
}

void MainWindow::ab1_slot()
{
	// надо проверить что это номер абонента , а не группы в каждом слоте и записать в файл favorite.dat

	if (pb_add_ch[current_index]->palette() == palet)
	{
		if (pb_ab1[current_index]->text() != "")
		{
		pb_add_ch[current_index]->setText(pb_ab1[current_index]->text());
		current_call_type = PRIVATE;
		}
	}
	else
	{
		if (current_call_type == PRIVATE)
		{
			QString s = pb_add_ch[current_index]->text();
			pb_ab1[current_index]->setText(s);
			update_favorites(current_index, current_channel, 4, s);
		}
		pb_add_ch[current_index]->setPalette(palet);
	}
}


void MainWindow::ab2_slot()
{
	if (pb_add_ch[current_index]->palette() == palet)
	{
		if (pb_ab2[current_index]->text() != "")
		{
		pb_add_ch[current_index]->setText(pb_ab2[current_index]->text());
		current_call_type = PRIVATE;
		}
	}
	else
	{
		if (current_call_type == PRIVATE)
		{
			QString s = pb_add_ch[current_index]->text();
			pb_ab2[current_index]->setText(s);
			update_favorites(current_index, current_channel, 5, s);
		}
		pb_add_ch[current_index]->setPalette(palet);
	}
}


void MainWindow::ab3_slot()
{
	if (pb_add_ch[current_index]->palette() == palet)
	{
		if (pb_ab3[current_index]->text() != "")
		{
		pb_add_ch[current_index]->setText(pb_ab3[current_index]->text());
		current_call_type = PRIVATE;
		}
	}
	else
	{
		if (current_call_type == PRIVATE)
		{
			QString s = pb_add_ch[current_index]->text();
			pb_ab3[current_index]->setText(s);
			update_favorites(current_index, current_channel, 6, s);
		}
		pb_add_ch[current_index]->setPalette(palet);
	}	
}

void MainWindow::ab4_slot()
{
	if (pb_add_ch[current_index]->palette() == palet)
	{
		if (pb_ab4[current_index]->text() != "")
		{
		pb_add_ch[current_index]->setText(pb_ab4[current_index]->text());
		current_call_type = PRIVATE;
		}
	}
	else
	{
		if (current_call_type == PRIVATE)
		{
			QString s = pb_add_ch[current_index]->text();
			pb_ab4[current_index]->setText(s);
			update_favorites(current_index, current_channel, 7, s);
		}
		pb_add_ch[current_index]->setPalette(palet);
	}	
}

void MainWindow::add_ch_click_slot()
{
	QString str = ((QPushButton *)sender())->text();
	qDebug() << str;
	pb_add_Timer.start(1500);
}

void MainWindow::add_ch_release_slot()
{
	if (pb_add_ch[current_index]->palette() == palet)
	{
		pb_add_Timer.stop();
	}
}

void MainWindow::cb_ab_slot(const QString& s)
{
	pb_add_ch[current_index]->setText(s);
}

void MainWindow::cb_gr_slot(const QString& s)
{
	pb_add_ch[current_index]->setText(s);
	current_call_type = GROUP;
}

void MainWindow::pb_add_Timer_slot()
{
	if (pb_add_ch[current_index]->palette() == new_palet)
	{
		pb_add_ch[current_index]->setPalette(palet);
		pb_add_Timer.stop();
		qDebug() << "second";
		
	}
	else
	{
		pb_add_ch[current_index]->setPalette(new_palet);
		qDebug() << "first";
	}
	
}

