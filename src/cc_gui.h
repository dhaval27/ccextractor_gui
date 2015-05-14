#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<QString>
#include<QChar>
#include<iostream>
#include<QDropEvent>
#include<QDragEnterEvent>
#include<QProcess>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<QTextStream>
#include<QFile>
#include<QDir>
#include<QFileDialog>
#include<QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void getInputFile();
    void getStartAtTime();
    void getEndAtTime();
    void getVidInfo();
    void getCommand();
    void setPreview();
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void updateText();
    void updateError();
    //void progress();
    //void readStdOut();
    /*void onStarted();
    void onFinished(int);*/

    //void on_textEdit_2_textChanged();

    void on_pushButton_3_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_2_clicked(bool checked);

    void on_radioButton_clicked(bool checked);

    void on_radioButton_3_clicked(bool checked);

    void on_radioButton_4_clicked(bool checked);

    void on_radioButton_5_clicked(bool checked);

    void on_textEdit_2_cursorPositionChanged();

    void on_spinBox_valueChanged(const QString &arg1);

    //void on_radioButton_49_clicked(bool checked);

    void on_radioButton_16_clicked(bool checked);

    void on_radioButton_21_clicked(bool checked);

    void on_radioButton_22_clicked(bool checked);

    void on_radioButton_17_clicked(bool checked);

    void on_radioButton_20_clicked(bool checked);

    void on_radioButton_23_clicked(bool checked);

    void on_radioButton_18_clicked(bool checked);

    void on_radioButton_24_clicked(bool checked);

    void on_spinBox_4_valueChanged(const QString &arg1);

    void on_spinBox_5_valueChanged(const QString &arg1);

    void on_spinBox_6_valueChanged(const QString &arg1);

    void on_spinBox_10_valueChanged(const QString &arg1);

    void on_spinBox_11_valueChanged(const QString &arg1);

    void on_spinBox_12_valueChanged(const QString &arg1);

    void on_radioButton_45_clicked(bool checked);

    void on_radioButton_44_clicked(bool checked);

    void on_spinBox_7_valueChanged(const QString &arg1);

    void on_spinBox_2_valueChanged(const QString &arg1);

    void on_spinBox_8_valueChanged(const QString &arg1);

    void on_spinBox_9_valueChanged(const QString &arg1);

    void on_spinBox_13_valueChanged(const QString &arg1);

    void on_spinBox_18_valueChanged(const QString &arg1);

    void on_spinBox_19_valueChanged(const QString &arg1);

    void on_spinBox_20_valueChanged(const QString &arg1);

    void on_spinBox_21_valueChanged(const QString &arg1);

    void on_spinBox_3_valueChanged(const QString &arg1);

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QString inputText;
    //QString in_file;
    QString exe;
    QString command;
    QString extansion;
    //QString out_file;
    QString fileName;
    QStringList myStringList;
    QStringList arguments;
    QString file_extansion;
    QString option_out;
    QString option_in;
    QString option_delay;
    QString option_in_file;
    QString in_file[8];
    QString option_out_file;
    QString out_file[8];
    QString option_startat;
    QString startat_hh;
    QString startat_mm;
    QString startat_ss;
    QString option_endat;
    QString endat_hh;
    QString endat_mm;
    QString endat_ss;
    QString option_inClock;
    QString option_screenfuls;
    QString option_credit_text;
    QString cstart_before_mm;
    QString cstart_before_ss;
    QString cstart_after_mm;
    QString cstart_after_ss;
    QString cstart_least;
    QString cstart_most;
    QString cend_least;
    QString cend_most;
    QString option_encoding;
    QString option_mode_ss;
    bool check;
    int count;
    int size;
    int i,j;
    int Index;
    char file_1[512];
    char file[4][512];
    char vid_size[16];
    char vid_ar[16];
    char vid_fr[16];
    QProcess *process;
};

#endif // MAINWINDOW_H
