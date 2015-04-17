#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	//inputText= ui->textEdit_2->toPlainText();
	//qDebug()<<"received text"<<inputText;
	//getInputFile(inputText);
	ui->radioButton->setChecked(true);
	ui->radioButton_6->setChecked(true);
	ui->radioButton_15->setChecked(true);
	ui->radioButton_43->setChecked(true);
	ui->radioButton_31->setChecked(true);
	ui->radioButton_35->setChecked(true);
	ui->radioButton_33->setChecked(true);
	ui->radioButton_53->setChecked(true);
	ui->radioButton_63->setChecked(true);
	ui->radioButton_59->setChecked(true);
	ui->radioButton_59->setChecked(true);
	ui->radioButton_38->setChecked(true);
	ui->radioButton_29->setChecked(true);
	ui->radioButton_57->setChecked(true);
	ui->radioButton_55->setChecked(true);

	startat_hh="00";
	startat_mm="00";
	startat_ss="00";
	endat_hh="00";
	endat_mm="00";
	endat_ss="00";
	cstart_after_mm="00";
	cstart_after_ss="00";
	cstart_before_mm="00";
	cstart_before_ss="00";
	cstart_least="02";
	cstart_most="05";
	cend_least="02";
	cend_most="05";
	setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
	qDebug()<<"in dragEnterEvent";
	event->accept();
	/*if (event->mimeData()->hasUrls())
	  {
	  event->acceptProposedAction();
	  }*/
}

void MainWindow::dropEvent(QDropEvent *event)
{
	qDebug()<<"in dropEvent()";
	qDebug()<<"x= "<<event->pos().x()<<"y= "<<event->pos().y();
	/*foreach(const QUrl &url, event->mimeData()->urls())
	  {
	  const QString &fileName = url.toLocalFile();
	  qDebug() << "Dropped file:" << fileName;
	  }*/
}

void MainWindow::getInputFile()
{
	inputText= ui->textEdit_2->toPlainText();
	qDebug()<<"received text"<<inputText;

	int k=0;
	size=inputText.size();
	qDebug()<<"size ="<<size;

	count=inputText.count('\n');
	qDebug()<<"count ="<<count;

	memset(file_1,0,sizeof(file_1));
	memset(file,0,sizeof(file));

	myStringList = inputText.split("\n");

	//for(int index =0;index < myStringList.length();index++)
	for(Index =0;Index < count;Index++)
	{
		qDebug()<<myStringList.at(Index);

		qDebug()<<(check=(myStringList.at(Index).startsWith("file://")));
		if(check==false)
		{
			qDebug()<<"ERROR IN INPUT FILE";
			//return ;
		}

		//in_file[Index]= myStringList.at(Index).mid(7);
		//qDebug()<<"in_file[Index]="<<in_file[Index];
	}

	qDebug()<<"Index="<<Index;
	option_in_file=myStringList.at(0).mid(7);
	qDebug()<<"option_in_file= "<<option_in_file;

	//option_in_file=myStringList.at(0);
	//qDebug()<<"option_in_file= "<<option_in_file;

	//option_out= "-out=srt ";
	extansion= "srt";

	file_extansion=option_in_file;
	file_extansion.replace((file_extansion.indexOf('.'))+1,3,extansion);
	qDebug()<<"file_extansion="<<file_extansion;

	fileName= file_extansion;

	//memset(option_out_file,0,sizeof(option_out_file));
	//option_out_file= "";
	//return check;
}

void MainWindow::getStartAtTime()
{
	option_startat="-startat ";
	option_startat.append(startat_hh);
	option_startat.append(":");
	option_startat.append(startat_mm);
	option_startat.append(":");
	option_startat.append(startat_ss);
	qDebug()<<"option_startat="<<option_startat;
}

void MainWindow::getEndAtTime()
{
	option_endat="-endat ";
	option_endat.append(endat_hh);
	option_endat.append(":");
	option_endat.append(endat_mm);
	option_endat.append(":");
	option_endat.append(endat_ss);
	qDebug()<<"option_endat="<<option_endat;
}

void MainWindow::updateError()
{
	QByteArray data = process->readAllStandardError();
	int index_hash=0;
	ui->textEdit->append(QString(data));
	//qDebug() << data;

	if(data.contains("###VERSION#"))
	{
		QByteArray version=data.mid(data.indexOf("C"));
		version=version.replace("#"," ");
		ui->label_29->setText(QString(version));
	}

	if(data.contains("###VIDEOINFO#"))
	{
		qDebug()<<"data_VIDEOINFO="<<data;
		QByteArray video_info=data.mid((data.indexOf("###VIDEOINFO#"))+13);

		video_info=video_info.remove(video_info.indexOf("\n"),(video_info.size()));
		qDebug()<<"data_1="<<video_info;

		QByteArray frame_rate= video_info.mid(video_info.lastIndexOf("#"));
		frame_rate= frame_rate.mid(1);
		qDebug()<<"frame_rate"<<frame_rate;
		video_info.chop(frame_rate.size()+1);
		qDebug()<<"data_1="<<video_info;
		ui->label_35->setText(QString(frame_rate));

		QByteArray aspect_ratio= video_info.mid(video_info.lastIndexOf("#"));
		aspect_ratio= aspect_ratio.mid(1);
		qDebug()<<"aspect_ratio"<<aspect_ratio;
		video_info.chop(aspect_ratio.size()+1);
		qDebug()<<"data_2="<<video_info;
		ui->label_34->setText(QString(aspect_ratio));

		video_info=video_info.replace("#","*");
		ui->label_33->setText(QString(video_info));

	}

	if(data.contains("###PROGRESS#"))
	{
		QByteArray progress=data.mid(data.indexOf("###PROGRESS#")+12);
		qDebug()<<"progress="<<progress;

		int count= progress.count("###PROGRESS#");
		qDebug()<<"count="<<count;

		for(int i=0;i<=count;i++)
		{
			QByteArray progress_rest= progress.mid((progress.indexOf("###PROGRESS#"))+12);
			qDebug()<<"progress_rest="<<progress_rest;

			QByteArray progress_first= progress.remove((progress.indexOf("\n")),progress.size());
			qDebug()<<"progress_first="<<progress_first;

			index_hash=progress_first.indexOf("#");
			qDebug()<<"index_hash="<<index_hash;

			QByteArray time= progress_first.mid((index_hash+1));
			//QByteArray time= progress_first.mid((progress_first.indexOf("#"))+1);
			int len= time.size();

			qDebug()<<"len="<<len;
			time=time.replace("#",":");
			ui->label_36->setText(QString(time));
			qDebug()<<"time="<<time;

			progress_first= progress_first.remove(index_hash,len+1);

			ui->progressBar->setValue(progress_first.toInt());
			progress_first= progress_first.append("%");
			ui->label_27->setText(QString(progress_first));
			progress= progress_rest;
		}
	}


	/*if(data.contains("###PROGRESS#"))
	  {
	  QByteArray progress=data.mid(data.indexOf("###PROGRESS#")+12);

	  int count= progress.count("###PROGRESS#");
	  qDebug()<<"count="<<count;


	  progress= progress.remove((progress.indexOf("\n")),progress.size());
	  index_hash=progress.indexOf("#");
	  qDebug()<<"index_hash="<<index_hash;

	  QByteArray time= progress.mid((index_hash+1));
	  int len= time.size();

	  qDebug()<<"len="<<len;
	  time=time.replace("#",":");
	  ui->label_36->setText(QString(time));
	  qDebug()<<"time="<<time;

	  progress= progress.remove(index_hash,len+1);

	  ui->progressBar->setValue(progress.toInt());
	//data=data.append("%");
	ui->label_27->setText(QString(progress));

	}*/


}

void MainWindow::updateText()
{
	QByteArray data = process->readAllStandardOutput();

	//ui->progressBar->setValue( pr->readAll().toInt() );
	//ui->progressBar->setValue( data.size() );
	ui->textEdit->append(QString(data));
}

void MainWindow::getCommand()
{
	getStartAtTime();
	getEndAtTime();

	exe="/home/dhaval/pro/ccextractor/linux/ccextractor";
	exe=exe.append(" ");
	exe=exe.append("--gui_mode_reports");
	exe=exe.append(" ");
	exe=exe.append(option_in);
	exe=exe.append(" ");
	exe=exe.append(option_out);
	exe=exe.append(" ");

	/***********************************************
	 **********MODE OPTION****************/

	if(ui->radioButton_30->isChecked())
	{
		exe=exe.append("-s --stream");
		exe=exe.append(" ");
		exe=exe.append(option_mode_ss);
		exe=exe.append(" ");
	}

	/***********************************************
	 **********TIME RELATED OPTION****************/

	if(ui->radioButton_32->isChecked())
	{
		exe=exe.append(option_startat);
		exe=exe.append(" ");
	}
	if(ui->radioButton_36->isChecked())
	{
		exe=exe.append(option_endat);
		exe=exe.append(" ");
	}
	if(ui->radioButton_34->isChecked())
	{
		exe=exe.append(option_screenfuls);
		exe=exe.append(" ");
	}

	exe=exe.append(option_delay);
	exe=exe.append(" ");

	/*******************************************
	 **********ELEMENTRY STREAM****************/

	/*???????????????????????????????????????????????????*/
	if(ui->radioButton_39->isChecked())
	{
		exe=exe.append("-datapid");
		exe=exe.append(" ");
		exe=exe.append(ui->lineEdit_2->text());
		exe=exe.append(" ");
	}
	if(ui->radioButton_37->isChecked())
	{
		exe=exe.append("-datastreamtype");
		exe=exe.append(" ");
		exe=exe.append(ui->lineEdit->text());
		exe=exe.append(" ");

		exe=exe.append("-streamtype");
		exe=exe.append(" ");
		exe=exe.append(ui->lineEdit_3->text());
		exe=exe.append(" ");
	}

	/***********************************************
	 ****************MYTH TV OPTION****************/
	if(ui->radioButton_40->isChecked())
	{
		exe=exe.append("-myth");
		exe=exe.append(" ");
	}
	if(ui->radioButton_41->isChecked())
	{
		exe=exe.append("-nomyth");
		exe=exe.append(" ");
	}

	/***********************************************
	 **********MISCELLANEOUS OPTION****************/

	if(ui->checkBox_2->isChecked())
	{
		exe=exe.append("-90090 ");
		qDebug()<<"1 checked";
	}

	if(ui->checkBox_4->isChecked())
	{
		exe=exe.append("-fp --fixpadding ");
		qDebug()<<"2 checked";
	}
	/*
	   if(ui->checkBox_5->isChecked())
	   {
	   exe=exe.append("-90090 ");
	   qDebug()<<"3 checked";
	   }
	 */
	if(ui->checkBox_7->isChecked())
	{
		exe=exe.append("-wtvconvertfix ");
		qDebug()<<"4 checked";
	}

	if(ui->checkBox_3->isChecked())
	{
		exe=exe.append("-haup --hauppauge ");
		qDebug()<<"5 checked";
	}

	if(ui->checkBox_6->isChecked())
	{
		exe=exe.append("-poc -usepicorder ");
		qDebug()<<"6 checked";
	}

	if(ui->checkBox->isChecked())
	{
		exe=exe.append("-mp4vidtrack ");
		qDebug()<<"7 checked";
	}

	/***********************************************
	 ***********CLOCK OPTION****************/
	if( (ui->radioButton_44->isChecked()) || (ui->radioButton_45->isChecked()) )
	{
		exe=exe.append(option_inClock);
	}

	/***********************************************
	 ********MULTIPROGRAM TRANSPORT STREAM*********/
	if(ui->radioButton_47->isChecked())
	{
		exe=exe.append("-pn");
		exe=exe.append(" ");
		exe=exe.append("-");

		/*????????????????????????????????????????????????*/
		exe=exe.append(ui->lineEdit_4->text());
		exe=exe.append(" ");

	}
	if(ui->radioButton_46->isChecked())
	{
		exe=exe.append("-autoprogram");
		exe=exe.append(" ");
	}

	/***********************************************
	 ****************CREDITS OPTION****************/

	if(ui->checkBox_24->isChecked())
	{
		QString in_credit=ui->textEdit_5->toPlainText();
		/*char a[1024];
		  memset(a,0,sizeof(a));

		  qDebug()<<"hi="<<in_credit.toStdString().c_str();
		  qDebug()<<"a="<<a;
		 */
		exe=exe.append("--startcreditstext");
		exe=exe.append(" ");
		exe=exe.append("\"");
		exe=exe.append(ui->textEdit_5->toPlainText());
		exe=exe.append("\"");
		exe=exe.append(" ");

		if(ui->checkBox_25->isChecked())
		{
			exe=exe.append("--startcreditsnotbefore");
			exe=exe.append(" ");
			exe=exe.append(cstart_before_mm);
			exe=exe.append(":");
			exe=exe.append(cstart_before_ss);
			exe=exe.append(" ");
		}

		if(ui->checkBox_26->isChecked())
		{
			exe=exe.append("--startcreditsnotafter");
			exe=exe.append(" ");
			exe=exe.append(cstart_after_mm);
			exe=exe.append(":");
			exe=exe.append(cstart_after_ss);
			exe=exe.append(" ");
		}

		exe=exe.append("--startcreditsforatleast");
		exe=exe.append(" ");
		exe=exe.append("00");
		exe=exe.append(":");
		exe=exe.append(cstart_least);
		exe=exe.append(" ");

		exe=exe.append("--startcreditsforatmost");
		exe=exe.append(" ");
		exe=exe.append("00");
		exe=exe.append(":");
		exe=exe.append(cstart_most);
		exe=exe.append(" ");
	}

	/******************************/
	if(ui->checkBox_29->isChecked())
	{
		QString out_credit=ui->textEdit_6->toPlainText();
		/*char a[1024];
		  memset(a,0,sizeof(a));

		  qDebug()<<"hi="<<in_credit.toStdString().c_str();
		  qDebug()<<"a="<<a;
		 */
		exe=exe.append("--endcreditstext");
		exe=exe.append(" ");
		exe=exe.append('\"');
		exe=exe.append(ui->textEdit_6->toPlainText());
		exe=exe.append("\"");
		exe=exe.append(" ");

		exe=exe.append("--endcreditsforatleast");
		exe=exe.append(" ");
		exe=exe.append("00");
		exe=exe.append(":");
		exe=exe.append(cend_least);
		exe=exe.append(" ");

		exe=exe.append("--endcreditsforatmost");
		exe=exe.append(" ");
		exe=exe.append("00");
		exe=exe.append(":");
		exe=exe.append(cend_most);
		exe=exe.append(" ");
	}

	/***********************************************
	 ****************ENCODING OPTION****************/
	if(ui->radioButton_49->isChecked())
	{
		exe=exe.append("-latin1");
		exe=exe.append(" ");
	}

	if(ui->radioButton_49->isChecked())
	{
		exe=exe.append("-utf8");
		exe=exe.append(" ");
	}

	if(ui->radioButton_49->isChecked())
	{
		exe=exe.append("-unicode");
		exe=exe.append(" ");
	}

	/***********************************************
	 ****************COLORS OPTION****************/
	if(ui->radioButton_52->isChecked())
	{
		exe=exe.append("-nofc --nofontcolor");
		exe=exe.append(" ");
	}
	//process->setProcessChannelMode(QProcess::MergedChannels);
	if(ui->radioButton_54->isChecked())
	{
		exe=exe.append("-dc");
		exe=exe.append(" ");
		exe=exe.append(ui->lineEdit_12->text());
		exe=exe.append(" ");
	}

	/***************************************************
	 ****************TYPESETTING OPTION****************/
	if(ui->radioButton_64->isChecked())
	{
		exe=exe.append("-nots --notypesetting");
		exe=exe.append(" ");
	}

	/**************************************************
	 **********LINE TERMINATORS OPTION****************/
	if(ui->radioButton_65->isChecked())
	{
		exe=exe.append("-UCLA");
		exe=exe.append(" ");
	}

	if(ui->radioButton_66->isChecked())
	{
		exe=exe.append("-lf");
		exe=exe.append(" ");
	}

	/***********************************************
	 ****************ROLL-UP OPTION****************/
	if(ui->checkBox_32->isChecked())
	{
		exe=exe.append("-dru");
		exe=exe.append(" ");
	}

	if(ui->checkBox_33->isChecked())
	{
		exe=exe.append("-noru --norollup");
		exe=exe.append(" ");
	}

	if(ui->radioButton_60->isChecked())
	{
		exe=exe.append("-ru1");
		exe=exe.append(" ");
	}

	if(ui->radioButton_61->isChecked())
	{
		exe=exe.append("-ru3");
		exe=exe.append(" ");
	}

	if(ui->radioButton_62->isChecked())
	{
		exe=exe.append("-ru2");
		exe=exe.append(" ");
	}

	/***********************************************
	 **********TEXT POSITION OPTION****************/
	/******?????????????????????????????????*******/
	if(ui->checkBox_30->isChecked())
	{
		exe=exe.append("-trim");
		exe=exe.append(" ");

		exe=exe.append("-autodash");
		exe=exe.append(" ");
	}

	/***********************************************
	 **********SENTENCE CAP OPTION****************/
	if(ui->radioButton_58->isChecked())
	{
		exe=exe.append("--sc --sentencecap");
		exe=exe.append(" ");

		if(ui->checkBox_31->isChecked())
		{
			exe=exe.append("---capfile -caf");
			exe=exe.append(" ");
			exe=exe.append(ui->lineEdit_13->text());
			exe=exe.append(" ");
		}
	}

	/***********************************************
	 *************608 DECODER OPTION**************/
	if(ui->radioButton_9->isChecked())
	{
		exe=exe.append("-cc2");
		exe=exe.append(" ");
	}

	if((ui->checkBox_34->isChecked())||(ui->checkBox_35->isChecked()))
	{
		if( (ui->checkBox_34->isChecked()) && (ui->checkBox_35->isChecked()) )
		{
			exe=exe.append("-12");
			exe=exe.append(" ");
		}
		else if(ui->checkBox_34->isChecked())
		{
			exe=exe.append("-1");
			exe=exe.append(" ");
		}
		else if(ui->checkBox_35->isChecked())
		{
			exe=exe.append("-2");
			exe=exe.append(" ");
		}
	}

	/***********************************************
	 *************708 DECODER OPTION****************/
	if(ui->checkBox_23->isChecked())
	{
		exe=exe.append("-svc --service");
		exe=exe.append(" ");
		exe=exe.append(ui->lineEdit_6->text());
		exe=exe.append(" ");
	}

	/*************************************************
	 **********TELETEXT DECODER OPTION****************/
	if(ui->radioButton_48->isChecked())
	{
		exe=exe.append("-codec dvdsub");
		exe=exe.append(" ");
	}

	if(ui->radioButton_13->isChecked())
	{
		exe=exe.append("-noteletext");
		exe=exe.append(" ");
	}

	/******?????????????????????????????????*******/
	if(ui->radioButton_12->isChecked())
	{
		exe=exe.append("-teletext");
		exe=exe.append(" ");
		exe=exe.append("-datapid");
		exe=exe.append(" ");
		exe=exe.append(ui->lineEdit_8->text());
		exe=exe.append(" ");
	}

	if((ui->lineEdit_7->text())!=NULL)
	{
		qDebug()<<"ui->lineEdit_7->text()="<<ui->lineEdit_7->text();
		exe=exe.append("-tpage");
		exe=exe.append(" ");
		exe=exe.append(ui->lineEdit_7->text());
	}

	/***********************************************
	 ****************DEBUG OPTION****************/

	if(ui->checkBox_22->isChecked())
	{
		/*??????????????????????????????????????*/
	}
	if(ui->checkBox_8->isChecked())
	{
		/*??????????????????????????????????????*/
	}
	if(ui->checkBox_10->isChecked())
	{
		exe=exe.append("-608");
		exe=exe.append(" ");
	}
	if(ui->checkBox_11->isChecked())
	{
		exe=exe.append("-708");
		exe=exe.append(" ");
	}
	if(ui->checkBox_12->isChecked())
	{
		exe=exe.append("-goppts");
		exe=exe.append(" ");
	}
	if(ui->checkBox_13->isChecked())
	{
		exe=exe.append("-vides");
		exe=exe.append(" ");
	}
	if(ui->checkBox_14->isChecked())
	{
		exe=exe.append("-cbraw");
		exe=exe.append(" ");
	}
	if(ui->checkBox_15->isChecked())
	{
		exe=exe.append("-parsedebug");
		exe=exe.append(" ");
	}
	if(ui->checkBox_9->isChecked())
	{
		exe=exe.append("-nosync");
		exe=exe.append(" ");
	}
	if(ui->checkBox_16->isChecked())
	{
		exe=exe.append("-fullbin");
		exe=exe.append(" ");
	}
	if(ui->checkBox_17->isChecked())
	{
		exe=exe.append("-xdsdebug");
		exe=exe.append(" ");
	}
	if(ui->checkBox_18->isChecked())
	{
		exe=exe.append("-parsePAT");
		exe=exe.append(" ");
	}
	if(ui->checkBox_19->isChecked())
	{
		exe=exe.append("-parsePMT");
		exe=exe.append(" ");
	}
	if(ui->checkBox_20->isChecked())
	{
		exe=exe.append("-investigate_packets");
		exe=exe.append(" ");
	}
	if(ui->checkBox_21->isChecked())
	{
		/*??????????????????????????????????????*/
	}


	/***********************************************
	 **********************************************/
	exe=exe.append(option_in_file);
	exe=exe.append(" ");
	command=exe.append(option_out_file);
	qDebug()<<"command= "<<command;

	ui->textEdit_3->setText(command);

	/*for(i=0;i<Index;i++)
	  {
	  exe=exe.append(in_file[i]);
	  exe=exe.append(" ");
	  }
	  for(i=0;i<Index;i++)
	  {
	  exe=exe.append("-o");
	  exe=exe.append(" ");
	  exe=exe.append(option_out_file[i]);
	  }
	  qDebug()<<"exe= "<<exe;
	 */
}

/**************************************************
 ***********     START BUTTON     ******************
 *************************************************/

void MainWindow::on_pushButton_2_clicked()
{
	/*
	//getInputFile();
	//qDebug()<<"inputFile="<<inputFile;


	//char *inputFile= getInputFile();
	//char *str,*token,*saveptr,*file_name;
	//int i;

	if(strlen(inputFile)==0)
	qDebug()<<"no input file added";
	else
	qDebug()<<"inputFile is present= "<<inputFile;



	for(str=inputFile; ; str=NULL)
	{
	token= strtok_r(str,"/",&saveptr);
	if(token==NULL)
	{
	break;
	}
	file_name= token;
	qDebug()<<"token= "<<token;
	}

	qDebug()<<"file_name"<<file_name;*/

	//if(check)
	//{
	qDebug()<<"check="<<check;
	getCommand();
	/**************************************************
	 **************STARTING THE PROCESS***************/

	qDebug()<<"before new";
	process= new QProcess(this);
	QCoreApplication::processEvents();
	//process->setProcessChannelMode(QProcess::MergedChannels);
	//connect(process,SIGNAL(readyRead()),this,SLOT(progress()));

	connect(process, SIGNAL(readyReadStandardError()), this, SLOT(updateError()));
	connect(process, SIGNAL(readyRead()), this, SLOT(updateText()));

	process->start(command);
	process->waitForFinished();
	setPreview();

	//}
	/*else
	  {
	  qDebug()<<"check="<<check;
	  QMessageBox* msgBox= new QMessageBox();
	  msgBox->setWindowTitle("QMessageBox Always On Top");
	  msgBox->setText("This is an always-on-top QMessageBox!");
	  msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
	  msgBox->show();

	  msgBox->exec();
	  }*/

}

/**************************************************
 *************     FOR PREVIEW      ****************
 **************************************************/

void MainWindow::setPreview()
{
	QFile* file = new QFile();
	//QDir::setCurrent("/home/dhaval/pro/ccextractor/linux");
	//file->setFileName("/home/dhaval/pro/ccextractor/linux/Closedcaption_atsc_rollup.srt");
	file->setFileName(file_extansion);

	qDebug()<<"file name= "<<file->fileName();
	qDebug()<<"file exists= "<<file->exists(file->fileName());
	qDebug()<<"file open="<<file->open(QFile::ReadOnly);

	QString line(file->readAll());
	qDebug()<<"after file";
	file->close();

	ui->textEdit_4->append(line);
	qDebug()<<"after append";

	/**************************************************
	 *************************************************/

	/*if(file->exists(file->fileName()))
	  {
	  getVidInfo();
	  }*/

	/**************************************************
	 *************************************************/
	//ui->lineEdit_11->clear();
}

void MainWindow::getVidInfo()
{
	QString outputText=ui->textEdit->toPlainText();
	QStringList myStringList1= outputText.split("\n");

	QString first_line=myStringList1.at(0);
	qDebug()<<"first line="<<first_line;
	int n= first_line.indexOf(',');
	ui->label_29->setText(first_line.mid(0,n));
	qDebug()<<"n="<<n;


	int index,c;

	for(index=0;index<200;index++)
	{
		c=QString::compare(myStringList1.at(index),"New video information found");
		if(c==0)
		{
			qDebug()<<"index="<<index;
			break;
		}
	}
	index++;
	QString video_info= myStringList1.at(index);
	qDebug()<<video_info;

	char vid_info[128];
	int count=0;
	memset(vid_info,0,sizeof(vid_info));
	strcpy(vid_info,video_info.toStdString().c_str());
	qDebug()<<"vid_info="<<vid_info;

	//char *p,*q;
	for(i=0;vid_info[i];i++)
	{
		if(vid_info[i]=='[')
		{
			//p= &vid_info[i];
			count++;
			i++;
			for(j=0;vid_info[i]!=']';i++)
			{
				if(count==1)
				{
					vid_size[j++]=vid_info[i];
				}
				if(count==2)
				{
					vid_ar[j++]=vid_info[i];
				}
				if(count==3)
				{
					vid_fr[j++]=vid_info[i];
				}
			}
			//i++;
			if(count==1)
			{
				vid_size[j]='\0';
				qDebug()<<"vid_size="<<vid_size;
			}
			if(count==2)
			{
				vid_ar[j]='\0';
				qDebug()<<"vid_ar="<<vid_ar;
			}
			if(count==3)
			{
				vid_fr[j]='\0';
				qDebug()<<"vid_fr="<<vid_fr;
			}
		}
		qDebug()<<"count="<<count;
		qDebug()<<"i="<<i;
	}
	qDebug()<<"vid_size="<<vid_size;
	qDebug()<<"vid_ar="<<vid_ar;
	qDebug()<<"vid_fr="<<vid_fr;
	ui->label_33->setText(vid_size);
	ui->label_34->setText(vid_ar+4);
	ui->label_35->setText(vid_fr+4);
}

/**************************************************
 ***********     BROWSE BUTTON     ******************
 *************************************************/
void MainWindow::on_pushButton_3_clicked()
{
	if(ui->radioButton_7->isChecked())
	{
		qDebug()<<option_in_file.indexOf('.');
		file_extansion=option_in_file;
		file_extansion.replace((file_extansion.indexOf('.'))+1,3,extansion);
		qDebug()<<"file_extansion="<<file_extansion;

		//QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::currentPath());
		//"/home/dhaval/pro/ccextractor/linux/Closedcaption_atsc_rollup.srt"
		fileName = QFileDialog::getSaveFileName(this, tr("Save File"),file_extansion
				/*tr("Images (*.png *.xpm *.jpg)")*/);

		file_extansion=fileName;
		ui->lineEdit_11->setText(fileName);

		option_out_file= "-o ";
		option_out_file.append(fileName);
		option_out_file.append(" ");
		qDebug()<<"out_file"<<option_out_file;
	}
}

void MainWindow::on_radioButton_clicked()
{
	//option= "-out=srt "; //home/dhaval/pro/ccextractor/linux/hello.srt ";
}

/*******************************************************
 ******************OUTPUT OPTION*************************/
void MainWindow::on_radioButton_2_clicked()
{
	//option= "-out=sami ";
	//extansion= "smi";
}

void MainWindow::on_radioButton_2_clicked(bool checked)
{
	if(checked)
	{
		option_out= "-out=sami ";
		extansion= "smi";

		file_extansion=option_in_file;
		file_extansion.replace((file_extansion.indexOf('.'))+1,3,extansion);
		qDebug()<<"file_extansion="<<file_extansion;
	}
}

void MainWindow::on_radioButton_clicked(bool checked)
{
	if(checked)
	{
		option_out= "-out=srt ";
		extansion= "srt";

		file_extansion=option_in_file;
		file_extansion.replace((file_extansion.indexOf('.'))+1,3,extansion);
		qDebug()<<"file_extansion="<<file_extansion;
	}
}

void MainWindow::on_radioButton_3_clicked(bool checked)
{
	if(checked)
	{
		option_out= "-out=raw ";
		extansion= "raw";

		file_extansion=option_in_file;
		file_extansion.replace((file_extansion.indexOf('.'))+1,3,extansion);
		qDebug()<<"file_extansion="<<file_extansion;
	}
}

void MainWindow::on_radioButton_4_clicked(bool checked)
{
	if(checked)
	{
		option_out= "-out=dvdraw ";
		extansion= "dvdraw";

		file_extansion=option_in_file;
		file_extansion.replace((file_extansion.indexOf('.'))+1,3,extansion);
		qDebug()<<"file_extansion="<<file_extansion;
	}
}

void MainWindow::on_radioButton_5_clicked(bool checked)
{
	if(checked)
	{
		option_out= "-out=txt ";
		extansion= "txt";

		file_extansion=option_in_file;
		file_extansion.replace((file_extansion.indexOf('.'))+1,3,extansion);
		qDebug()<<"file_extansion="<<file_extansion;
	}
}

void MainWindow::on_textEdit_2_cursorPositionChanged()
{
	getInputFile();
}

//void MainWindow::on_radioButton_49_clicked(bool checked)
//{
//    if(checked){}
//}

/*******************************************************
 ******************INPUT OPTION*************************/

void MainWindow::on_radioButton_16_clicked(bool checked)
{
	if(checked)
	{
		option_in="-in=ts ";
	}
}

void MainWindow::on_radioButton_21_clicked(bool checked)
{
	if(checked)
	{
		option_in="-in=ps ";
	}
}

void MainWindow::on_radioButton_22_clicked(bool checked)
{
	if(checked)
	{
		option_in="-in=es ";
	}
}

void MainWindow::on_radioButton_17_clicked(bool checked)
{
	if(checked)
	{
		option_in="-in=wtv ";
	}
}

void MainWindow::on_radioButton_20_clicked(bool checked)
{
	if(checked)
	{
		option_in="-in=asf ";
	}
}

void MainWindow::on_radioButton_23_clicked(bool checked)
{
	if(checked)
	{
		option_in="-in=bin ";
	}
}

void MainWindow::on_radioButton_18_clicked(bool checked)
{
	if(checked)
	{
		option_in="-in=raw ";
	}
}

void MainWindow::on_radioButton_24_clicked(bool checked)
{
	if(checked)
	{
		option_in="-in=mp4 ";
	}
}

void MainWindow::on_pushButton_clicked()
{
	ui->textEdit_2->clear();
}

/*******************START AT *****************************/
void MainWindow::on_spinBox_4_valueChanged(const QString &arg1)
{
	startat_hh= arg1;
	qDebug()<<"startat_hh="<<startat_hh;
}

void MainWindow::on_spinBox_5_valueChanged(const QString &arg1)
{
	startat_mm= arg1;
	qDebug()<<"startat_mm="<<startat_mm;
}

void MainWindow::on_spinBox_6_valueChanged(const QString &arg1)
{
	startat_ss= arg1;
	qDebug()<<"startat_ss="<<startat_ss;
}

/*******************END AT *****************************/
void MainWindow::on_spinBox_10_valueChanged(const QString &arg1)
{
	endat_hh= arg1;
	qDebug()<<"endat_hh="<<endat_hh;
}

void MainWindow::on_spinBox_11_valueChanged(const QString &arg1)
{
	endat_mm= arg1;
	qDebug()<<"endat_mm="<<endat_mm;
}

void MainWindow::on_spinBox_12_valueChanged(const QString &arg1)
{
	endat_ss= arg1;
	qDebug()<<"endat_ss="<<endat_ss;
}

/****************DELAY OPTION**************************/
void MainWindow::on_spinBox_valueChanged(const QString &arg1)
{
	int i=ui->spinBox->value();
	qDebug()<<"i="<<i;
	qDebug()<<"argl="<<arg1;


	option_delay="-delay ";
	option_delay.append(arg1);
	option_delay.append(" ");
}

/******************CLOCK OPTION*********************/
void MainWindow::on_radioButton_45_clicked(bool checked)
{
	if(checked)
	{
		option_inClock="-gt --goptime ";
	}
}

void MainWindow::on_radioButton_44_clicked(bool checked)
{
	if(checked)
	{
		option_inClock="-nogt --nogoptime ";
	}
}

void MainWindow::on_spinBox_7_valueChanged(const QString &arg1)
{
	if(ui->radioButton_34->isChecked())
	{
		option_screenfuls="-scr --screenfuls ";
		option_screenfuls.append(arg1);
	}
}

/******************CREDIT OPTION*********************/

/******************CREDIT START OPTION*********************/
void MainWindow::on_spinBox_2_valueChanged(const QString &arg1)
{
	cstart_before_mm= arg1;
}

void MainWindow::on_spinBox_8_valueChanged(const QString &arg1)
{
	cstart_before_ss= arg1;
}

void MainWindow::on_spinBox_9_valueChanged(const QString &arg1)
{
	cstart_after_mm= arg1;
}

void MainWindow::on_spinBox_13_valueChanged(const QString &arg1)
{
	cstart_after_ss= arg1;
}

void MainWindow::on_spinBox_18_valueChanged(const QString &arg1)
{
	cstart_least= arg1;
}

void MainWindow::on_spinBox_19_valueChanged(const QString &arg1)
{
	cstart_most= arg1;
}

/******************CREDIT END OPTION*********************/
void MainWindow::on_spinBox_20_valueChanged(const QString &arg1)
{
	cend_least= arg1;
}

void MainWindow::on_spinBox_21_valueChanged(const QString &arg1)
{
	cend_most= arg1;
}

/******************MODE SECONDS OPTION*********************/
void MainWindow::on_spinBox_3_valueChanged(const QString &arg1)
{
	option_mode_ss= arg1;
}

/******************BROWSE TO OPEN FILE*********************/
void MainWindow::on_pushButton_4_clicked()
{
	if(ui->checkBox_31->isChecked())
	{
		QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::currentPath());
		qDebug()<<"dir="<<dir;

		ui->lineEdit_13->setText(dir);

	}
}
