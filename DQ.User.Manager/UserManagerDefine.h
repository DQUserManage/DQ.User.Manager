#pragma once

#if defined(BUILD_USER_MANAGER)
#define  EXPORT_USER_MANAGER __declspec(dllexport)
#else
#define  EXPORT_USER_MANAGER __declspec(dllimport) 
#endif



