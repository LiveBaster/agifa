#ifndef AGIFALIB_GLOBAL_H
#define AGIFALIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(AGIFALIB_LIBRARY)
#  define AGIFALIB_EXPORT Q_DECL_EXPORT
#else
#  define AGIFALIB_EXPORT Q_DECL_IMPORT
#endif

#endif // AGIFALIB_GLOBAL_H
