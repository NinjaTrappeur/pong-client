#include "jobcannotbedone.h"

JobCannotBeDone::JobCannotBeDone(const QString &problem): _problem(problem)
{
}

JobCannotBeDone::JobCannotBeDone(): _problem("Laziness... Problem not specified!")
{
}
