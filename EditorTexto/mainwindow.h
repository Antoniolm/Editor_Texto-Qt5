#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include <QFile>

//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

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

    void on_actionExit_2_triggered();

    void on_actionClose_file_triggered();

    void on_actionExit_triggered();

    void on_MainWindow_iconSizeChanged(const QSize &iconSize);

    void on_actionOpen_File_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    QTextEdit *mainText;
    QLabel *state;
    QFile *file;
    bool existFile;
};

#endif // MAINWINDOW_H
