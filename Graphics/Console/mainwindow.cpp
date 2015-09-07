#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "/home/devin/Documenti/GarageAudioLabs/Console/Input/Archive.h"
#include "/home/devin/Documenti/GarageAudioLabs/Console/Output/Riproduttore.h"
#include "string.h"
#include "iostream"
//Used For Multithetering (-std=c++0x)
#include <thread>						//Libreria per il multithetering
#include <mutex>						//Blocco sezioni critiche
#include <condition_variable>			//Condizioni variabili
#include <queue>						//Code
bool				exited=false;
std::mutex			lockaudio;
bool 				locked;
Archive* 			Musica;
Riproduttore*		Audio;

QString removePath(std::string percorso)
{
    // Remove directory if present.
    // Do this before extension removal incase directory has a period character.
    const size_t last_slash_idx = percorso.find_last_of("\\/");
    if (std::string::npos != last_slash_idx)
    {
        percorso.erase(0, last_slash_idx + 1);
    }

    // Remove extension if present.
    const size_t period_idx = percorso.rfind('.');
    if (std::string::npos != period_idx)
    {
        percorso.erase(period_idx);
    }
    return QString::fromStdString(percorso);
}

void audio_thread()
{
    while(!exited)
    {
        if (!locked)
            {
            if (Audio->endtrack==false)
                {
                    {
                        std::unique_lock<std::mutex> locker(lockaudio);
                        Audio->playPause();
                    }
                }
                else
                {
                    Audio->endtrack=false;
                    Audio->nextSong(); Audio->playPause(0);
                }
            }
    }
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    populateScene();
    Musica = new Archive("/home/devin/Musica/",true);
    Audio = new Riproduttore(*Musica);
    //std::cout<<"File Audio Trovati: "<<Musica->elementi.size()<<std::endl;
    ui->songTitleLabel->setText(removePath( Musica->elementi[0] ));
    Audio->nextSong();
    std::thread thr_audio(audio_thread);
    thr_audio.detach();

    for (int i=0;i<Musica->elementi.size();i++)
    {
        ui->listSong->addItem(removePath( Musica->elementi[i] ));
    }
}
void MainWindow::populateScene()
{
    scene = new QGraphicsScene;

    // Populate scene
    int xx = 0;
    int nitems = 0;
    for (int i = 0; i < 7500; i += 5) {
        ++xx;
        rect = new QGraphicsRectItem(QRect(i, 25,3,100)); //al posto di i va messo xx
        rect->setPos(QPointF(i, 0));
        rect->setPen( QPen( Qt::red) );
        rect->setBrush( Qt::gray );
        rect->setZValue(5);
        rect->setVisible(true);
        rect->update();
        scene->addItem(rect);
        ++nitems;
    }
    ui->waveGraphics->setScene(scene);
    ui->waveGraphics->rect();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_nextButton_clicked()
{
    locked=true;
    {
        std::unique_lock<std::mutex> locker(lockaudio); //Rivedere utilità
        Audio->nextSong();
        Audio->playPause(0);
        ui->songTitleLabel->setText(removePath( Musica->elementi[Musica->puntatore] ));
    }
    locked=false;
}

void MainWindow::on_previusButton_clicked()
{
    locked=true;
    {
        std::unique_lock<std::mutex> locker(lockaudio);
        Audio->prevSong();
        ui->songTitleLabel->setText(removePath( Musica->elementi[Musica->puntatore] ));
        Audio->playPause(0);
    }
    locked=false;
}

void MainWindow::on_playButton_clicked()
{
    Audio->playPause(2);
}


void MainWindow::on_listSong_itemSelectionChanged()
{
    int n=ui->listSong->currentRow();
    Audio->update(Musica->elementi[n]);
    Musica->puntatore=n;
    ui->songTitleLabel->setText(removePath(Musica->elementi[n]));
}
