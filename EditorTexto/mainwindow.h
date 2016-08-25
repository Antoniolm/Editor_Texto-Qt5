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
    void on_cursorPositionChanged();

    void on_actionNew_File_triggered();

    void on_actionClose_file_triggered();

    void on_actionExit_triggered();

    void on_actionOpen_File_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_groupQText_currentChanged(int index);

    void on_actionSearch_triggered();

    void on_actionReplace_triggered();

    void on_actionAbout_triggered();

    void on_pushButton_3_clicked();

    void on_underline_clicked();

    void on_italic_clicked();

    void on_actionExport_to_pdf_triggered();

    void on_currentSizeChanged();

    void on_currentFamilyChanged();

    void on_Right_clicked();

    void on_center_clicked();

    void on_left_clicked();

private:
    Ui::MainWindow *ui;
    QLabel *state;
    QTabWidget *groupQText;
    QList<document> docs;
    bool existFile;
    QString family;
    int sizeText;

};

#endif // MAINWINDOW_H
