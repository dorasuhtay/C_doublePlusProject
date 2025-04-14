#ifndef __SQLfunc_common__H
#define __SQLfunc_common__H

#include "class_HostnameMRTonline.h"
#include "class_SQLfunc.h"

using namespace System;
using namespace common_ClassLib;

extern int reload_HOSTNAME_MRT_db(class_HostnameMRTonline *classhost, class_SQLfunc ^%SQLfunc);
extern BOOL sGetRegKeyValue(HKEY hRoot, LPCWSTR lpszRegPath, LPCWSTR lpszValName, String ^%szValue, DWORD *dwType, DWORD *reg_dword);
extern String ^GetSQLVersionInformation(String ^%InstanceName, String ^%SQLRootpath);
extern String ^GetDotNetVersionInformation(String ^%InstanceName, String ^%SQLRootpath);

#endif