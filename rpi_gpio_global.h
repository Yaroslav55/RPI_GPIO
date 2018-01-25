#ifndef RPI_GPIO_GLOBAL_H
#define RPI_GPIO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RPI_GPIO_LIBRARY)
#  define RPI_GPIOSHARED_EXPORT Q_DECL_EXPORT
#else
#  define RPI_GPIOSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // RPI_GPIO_GLOBAL_H
