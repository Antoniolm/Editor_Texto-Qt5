#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>

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

private:
    Ui::MainWindow *ui;
    QTextEdit *mainText;
    QLabel *state;
};

#endif // MAINWINDOW_H
