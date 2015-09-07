#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsRectItem>

class QGraphicsScene;
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
    void on_nextButton_clicked();

    void on_previusButton_clicked();

    void on_playButton_clicked();

    void on_listSong_itemSelectionChanged();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *rect;
    void populateScene();
};

#endif // MAINWINDOW_H
