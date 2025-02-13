#include "MainWindow.h"

// curent_radio 0..3   channel 1..max_channels
void MainWindow::load_contacts(int current_radio, int channel)
{
	for (size_t j = 0; j < reader->radio[current_radio].num_contacts_gr; j++)
	{
		if (reader->radio[current_radio].contact_gr[j].channel == channel)
			combo_gr[current_radio]->addItem(reader->radio[current_radio].contact_gr[j].name);	
	}
	
	for (size_t j = 0; j < reader->radio[current_radio].num_contacts_ab; j++)
	{
		if (reader->radio[current_radio].contact_ab[j].channel == channel)
			combo_ab[current_radio]->addItem(reader->radio[current_radio].contact_ab[j].name); 
	}
}


