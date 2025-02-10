#include "MainWindow.h"
#include <QCoreApplication>
void MainWindow::interface_init()
{
	tab = new QTabWidget();

	QFont font0;
	font0.setPointSize(20);
	tab->setFont(font0);
	
	QFont fontPb;
	fontPb.setPointSize(12);
	
	for (int i = 0; i < reader->server.directions; i++)
	{
		wdg[i] = new QWidget();
		{
			pb_ptt[i] = new QPushButton(wdg[i]);
			pb_ptt[i]->setObjectName("pt_ptt" + QString::number(i));
			pb_ptt[i]->setGeometry(QRect(900, 0, 121, 520));
			QFont font;
			font.setPointSize(28);
			pb_ptt[i]->setFont(font);
			
			pb_ch_dwn[i] = new QPushButton(wdg[i]);
			pb_ch_dwn[i]->setObjectName("pt_ch_dwn" + QString::number(i));
			pb_ch_dwn[i]->setGeometry(QRect(80, 40, 160, 120));
			QFont font1;
			font1.setPointSize(36);
			pb_ch_dwn[i]->setFont(font1);
			
			pb_ch_up[i] = new QPushButton(wdg[i]);
			pb_ch_up[i]->setObjectName("pb_ch_up" + QString::number(i));
			pb_ch_up[i]->setGeometry(QRect(260, 40, 160, 120));
			pb_ch_up[i]->setFont(font1);
			lcdNumber[i] = new QLCDNumber(wdg[i]);
			lcdNumber[i]->setObjectName("lcdNumber");
			lcdNumber[i]->setGeometry(QRect(440, 40, 431, 120));
			lcdNumber[i]->setProperty("intValue", QVariant(1));
			groupBoxGr[i] = new QGroupBox(wdg[i]);
			groupBoxGr[i]->setObjectName("groupBox");
			groupBoxGr[i]->setGeometry(QRect(80, 175, 400, 361));
			combo_gr[i] = new QComboBox(groupBoxGr[i]);
			combo_gr[i]->setObjectName("combo_gr" + QString::number(i));
			combo_gr[i]->setGeometry(QRect(20, 40, 360, 60));
			pb_gr1[i] = new QPushButton(groupBoxGr[i]);
			pb_gr1[i]->setObjectName("pb_gr1" + QString::number(i));
			pb_gr1[i]->setGeometry(QRect(20, 130, 161, 100));
			pb_gr1[i]->setFont(fontPb);
			pb_gr2[i] = new QPushButton(groupBoxGr[i]);
			pb_gr2[i]->setObjectName("pb_gr2" + QString::number(i));
			pb_gr2[i]->setGeometry(QRect(220, 130, 160, 100));
			pb_gr2[i]->setFont(fontPb);
			pb_gr3[i] = new QPushButton(groupBoxGr[i]);
			pb_gr3[i]->setObjectName("pb_gr3" + QString::number(i));
			pb_gr3[i]->setGeometry(QRect(20, 260, 161, 100));
			pb_gr3[i]->setFont(fontPb);
			pb_gr4[i] = new QPushButton(groupBoxGr[i]);
			pb_gr4[i]->setObjectName("pb_gr4" + QString::number(i));
			pb_gr4[i]->setGeometry(QRect(220, 260, 161, 100));
			pb_gr4[i]->setFont(fontPb);
			groupBoxAb[i] = new QGroupBox(wdg[i]);
			groupBoxAb[i]->setObjectName("groupBoxAb");
			groupBoxAb[i]->setGeometry(QRect(490, 175, 400, 361));
			combo_ab[i] = new QComboBox(groupBoxAb[i]);
			combo_ab[i]->setObjectName("combo_ab");
			combo_ab[i]->setGeometry(QRect(20, 40, 360, 60));
			pb_ab1[i] = new QPushButton(groupBoxAb[i]);
			pb_ab1[i]->setObjectName("pb_ab1" + QString::number(i));
			pb_ab1[i]->setGeometry(QRect(20, 130, 160, 100));
			pb_ab1[i]->setFont(fontPb);
			pb_ab2[i] = new QPushButton(groupBoxAb[i]);
			pb_ab2[i]->setObjectName("pb_ab2" + QString::number(i));
			pb_ab2[i]->setGeometry(QRect(220, 130, 160, 100));
			pb_ab2[i]->setFont(fontPb);
			pb_ab3[i] = new QPushButton(groupBoxAb[i]);
			pb_ab3[i]->setObjectName("pb_ab3" + QString::number(i));
			pb_ab3[i]->setGeometry(QRect(20, 260, 160, 100));
			pb_ab3[i]->setFont(fontPb);
			pb_ab4[i] = new QPushButton(groupBoxAb[i]);
			pb_ab4[i]->setObjectName("pb_ab4"  + QString::number(i));
			pb_ab4[i]->setGeometry(QRect(220, 260, 160, 100));
			pb_ab4[i]->setFont(fontPb);
			pb_add_ch[i] = new QPushButton(wdg[i]);
			pb_add_ch[i]->setObjectName("pb_add_ch" + QString::number(i));
			pb_add_ch[i]->setGeometry(QRect(450, 50, 271, 101));
			pb_add_ch[i]->setFont(fontPb);
			
			pb_ptt[i]->setText(QCoreApplication::translate("MainWindow", "PTT", nullptr));
			pb_ch_dwn[i]->setText(QCoreApplication::translate("MainWindow", "--", nullptr));
			pb_ch_up[i]->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
			groupBoxGr[i]->setTitle(QCoreApplication::translate("MainWindow", "\320\223\321\200\321\203\320\277\320\277\320\276\320\262\321\213\320\265", nullptr));
			pb_gr1[i]->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
			pb_gr2[i]->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
			pb_gr3[i]->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
			pb_gr4[i]->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
			groupBoxAb[i]->setTitle(QCoreApplication::translate("MainWindow", "\320\230\320\275\320\264\320\270\320\262\320\270\320\264\321\203\320\260\320\273\321\214\320\275\321\213\320\265", nullptr));
			pb_ab1[i]->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
			pb_ab2[i]->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
			pb_ab3[i]->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
			pb_ab4[i]->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
			pb_add_ch[i]->setText(QString());
		}
		tab->addTab(wdg[i], "Радио" + QString::number(i));
	}

	setCentralWidget(tab);	
}
