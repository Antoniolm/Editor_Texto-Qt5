//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include <QFile>
#include <QTableWidget>
#include <QList>
#include <document.h>
#include <QTextCursor>
#include <QString>
#include <QFileDialog>
#include <QTextStream>
#include <QIODevice>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_mainText_cursorPositionChanged();

    void on_actionNew_File_triggered();

    void on_actionClose_file_triggered();

    void on_actionExit_triggered();

    void on_actionOpen_File_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_groupQText_currentChanged(int index);

    void on_actionSearch_triggered();

    void on_actionReplace_triggered();

private:
    Ui::MainWindow *ui;
    QLabel *state;
    QTabWidget *groupQText;
    QList<document> docs;
    bool existFile;

};

#endif // MAINWINDOW_H
