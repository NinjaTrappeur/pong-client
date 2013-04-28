#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

/*!
 * \brief Classe MainWindow
 *
 *  Il s'agit du widget principal du programme. C'est ce widget qui contient notemment le qlabel dans lequel le jeu
 *  est dessine.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    Ui::MainWindow *ui() const;
    void setUi(Ui::MainWindow *ui);

private:

    /*!
     * \brief Interface dessinee dans qtdesigner. Contient entre autres renderlabel.
     */
    Ui::MainWindow *_ui;

public slots:
    /*!
     * \brief Slot permettant de lancer le jeu.
     */
    void startGame(QString,qint16);
signals:
    /*!
     * \brief Signal lançant le rendu du jeu.
     */
    void startRender(QString,qint16);
};

#endif // MAINWINDOW_H
