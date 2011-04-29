/*
 *   part of this code is origined from
 *   GOGO-no-coda
 *
 *   Copyright(C) 2001,2002,2003 gogo-developer
 */


#include <windows.h>

HINSTANCE	s_hDLLInstance = NULL;
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	s_hDLLInstance = (HINSTANCE)hModule;

#if		defined(GOGO_DLL_EXPORTS) && defined(USE_REGISTRY)
	{
		static	BOOL	bRegistered = FALSE;

		if( !bRegistered ){
		#define ParentKey	HKEY_CURRENT_USER				//�ƥ���
		#define SubKey		"Software\\MarineCat\\GOGO_DLL"	//�����륵�֥���
		#define INSTPATH_C	"INSTPATH"					//�����륵�֥���
		#define INSTPATH_VB	"INSTPATH_VB"					//�����륵�֥���

			HKEY	hKey;
			DWORD	dwPosition, dwType;
			LONG	lResult;
			char	szPathName[ _MAX_PATH ];

			GetModuleFileName(s_hDLLInstance, szPathName, sizeof szPathName);

			// ��Ͽ����Ƥ��뤫Ĵ�٤�
			if( RegCreateKeyEx(
					ParentKey,
					SubKey,
					0,
					"",
					REG_OPTION_NON_VOLATILE,
					KEY_ALL_ACCESS,
					NULL,
					&hKey,
					&dwPosition) == ERROR_SUCCESS 
			){
				char	szTemp[ _MAX_PATH ];

				dwPosition = sizeof( szTemp );
				lResult = RegQueryValueEx( hKey,
						INSTPATH_C,
						0,
						&dwType,
						szTemp,
						&dwPosition );
				if( lResult == ERROR_SUCCESS && strcmp( szTemp, szPathName ) == 0 ){

					dwPosition = sizeof( szTemp );
					lResult = RegQueryValueEx( hKey,
							INSTPATH_VB,
							0,
							&dwType,
							szTemp,
							&dwPosition );

					if( lResult == ERROR_SUCCESS && strcmp( szTemp, szPathName ) == 0 ){
						bRegistered	=	TRUE;
					}
				}
						
				// ��Ͽ����Ƥ��ʤ����⤷���ϰۤʤäƤ�������Ͽ����
				if( !bRegistered )  {
					// for VC/BC/Delphi etc.
					lResult = RegSetValueEx( hKey,
						INSTPATH_C,
						0,
						REG_SZ,
						(CONST BYTE *)szPathName,
						lstrlen(szPathName));

					// for VB
					lResult = RegSetValueEx( hKey,
						INSTPATH_VB,
						0,
						REG_SZ,
						(CONST BYTE *)szPathName,
						lstrlen(szPathName));

					bRegistered = TRUE;
				}
				RegCloseKey(hKey);
			}
		}
	}
#endif

    return TRUE;
}

