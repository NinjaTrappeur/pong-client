#ifndef RENDERLABEL_H
#define RENDERLABEL_H

#include "scene.h"
#include <QLabel>
#include <QKeyEvent>
#include <QMouseEvent>

/*!
 * \brief RenderLabel: classe derivant de qlabel dans laquelle la methode paintEvent est redefinie.
 *  Cette classe represente le widget dans lequel le jeu sera dessine a l'aide de qpainter.
 */
class RenderLabel : public QLabel
{
    Q_OBJECT
public:

    /*!
     * \brief Constructeur de la classe. Son utilite principale est de cree la scene associee a ce renderlabel.
     * \param parent Widget parent (widget ayant cree ce widget)
     */
    explicit RenderLabel(QWidget *parent);
    virtual ~RenderLabel();

    /*!
     * \brief Methode appelee chaque fois que le widget sera dessine. Cette methode contiendra toutes les actions
     *  que devra realiser qpainter. La principale action etant de dessiner la scene associee a ce renderlabel.
     *
     * \param event Evenement associe au rafraichissement du widget (non utilise)
     */
    void paintEvent(QPaintEvent *event);

    /*!
     * \brief methode appelee chaque fois qu'une touche du clavier est appuyee. C'est dans cette
     *  methode qu'est associee une routine de traitement a certaines touches.
     *
     * \param ev Evenement cotenant entre autres la combinaison de touches appuyee.
     */
    void keyPressEvent(QKeyEvent *ev);

    /*!
     * \brief Methode appelee chaque fois que la souris est deplacee. Un traitement associe permet de deplacer la raquette.
     * \param ev Evenement contenant les informations necessaires au traitement.
     */
    virtual void mouseMoveEvent(QMouseEvent *ev);

private:

    /*!
     * \brief Pointeur vers la scene associee a ce renderlabel.
     */
    Scene* _scene;


signals:
    
public slots:
    /*!
     * \brief Slot active par le timer. Ce slot est appele 60 fois par secondes. Ceci permet
     *  de rafraichir la position des differents objets du jeu regulierement.
     */
    void animate();

    void startGame();
};

#endif // RENDERLABEL_H
