#include "MainWindow.h"
#include <array>
// curent_radio 0..3   channel 1..max_channels
// Заполняем поля контактов групп и абонентов при начальной загрузке и смене канала.
void MainWindow::load_contacts(int current_radio, int channel)
{
	combo_gr[current_radio]->clear();
	for (size_t j = 0; j < reader->radio[current_radio].num_contacts_gr; j++)
	{
		if (reader->radio[current_radio].contact_gr[j].channel == channel)
			combo_gr[current_radio]->addItem(reader->radio[current_radio].contact_gr[j].name);
	}

	combo_ab[current_radio]->clear();
	for (size_t j = 0; j < reader->radio[current_radio].num_contacts_ab; j++)
	{
		if (reader->radio[current_radio].contact_ab[j].channel == channel)
			combo_ab[current_radio]->addItem(reader->radio[current_radio].contact_ab[j].name);
	}
}

// radios,r1_ch_num,r2_ch_num,pb_gr1[0],...,pb_ab1[0],...,pb_gr1[0],...
void MainWindow::load_favorite()
{

	int radios = reader->favorite_list.at(0).toInt();

	std::array<int, 4> arr_chan;

	for (size_t i = 0; i < radios; i++)
	{
		arr_chan.at(i) = reader->favorite_list.at(i + 1).toInt();
	}

	int bias = radios + 1;

	for (size_t i = 0; i < radios; i++)
	{
		for (size_t j = 0; j < arr_chan[j]; j++)
		{
			pb_gr1[j]->setText(reader->favorite_list.at(bias + 0 + 8 * j * i));
			pb_gr2[j]->setText(reader->favorite_list.at(bias + 1 + 8 * j * i));
			pb_gr3[j]->setText(reader->favorite_list.at(bias + 2 + 8 * j * i));
			pb_gr4[j]->setText(reader->favorite_list.at(bias + 3 + 8 * j * i));

			pb_ab1[j]->setText(reader->favorite_list.at(bias + 4 + 8 * j * i));
			pb_ab2[j]->setText(reader->favorite_list.at(bias + 5 + 8 * j * i));
			pb_ab3[j]->setText(reader->favorite_list.at(bias + 6 + 8 * j * i));
			pb_ab4[j]->setText(reader->favorite_list.at(bias + 7 + 8 * j * i));
		}
	}
}

void MainWindow::write_favorite()
{
	QFile file;
	file.setFileName("favorites.dat");
	file.open(QIODevice::WriteOnly | QIODevice::Text);

	QString s = reader->favorite_list.join(",");

	file.write(s.toUtf8());
	
	file.close();
	
}

void MainWindow::update_favorites(int curr_idx, int chan_num, int pb_idx , QString& s)
{
	int bias = 1 + reader->favorite_list.at(0).toInt();

	reader->favorite_list[bias + pb_idx + 8 * chan_num * curr_idx] = s;
	
	write_favorite();
}

