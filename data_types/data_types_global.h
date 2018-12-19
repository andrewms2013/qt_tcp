#pragma once
#ifndef DATA_TYPES_GLOBAL_H
#define DATA_TYPES_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DATA_TYPES_LIBRARY)
#  define DATA_TYPESSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DATA_TYPESSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DATA_TYPES_GLOBAL_H
