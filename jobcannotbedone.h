#ifndef JOBCANNOTBEDONE_H
#define JOBCANNOTBEDONE_H

/*!
 *\file jobcannotbedone.h
 *\brief Fichier contenant l'exception JobCannotBeDone
 */

#include <exception>
#include <QString>

/*!
 * \brief The JobCannotBeDone class
 *
 *  Classe derivant de std::exception. Cette exception peut etre levee quand un travail demande ne peut
 *  etre effectue.
 */

class JobCannotBeDone : public std::exception
{
public:

    /*!
     * \brief Constructeur usuellement utilise
     *
     * \param problem Chaine de caracteres decrivant le probleme rencontre.
     */
    JobCannotBeDone(const QString &problem);

    /*!
     * \brief Constructeur sans parametres.
     *
     * \deprecated
     */
    JobCannotBeDone();
    virtual ~JobCannotBeDone() throw(){};
private:

    /*!
     * \brief Chaine de caractere decrivant le probleme rencontre qui a conduit a l'abandon du travail en cours.
     */
    QString _problem;
};

#endif // JOBCANNOTBEDONE_H
