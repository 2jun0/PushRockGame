#include "textview.h"
#include <GL / glut.h> 
#include <GL / glu.h> 
#include <windows.h>
TextView::TextView() { 

}
TextView::~TextView(){  

}
void TextView::drawString(char * str) {
	intlen, i; 
	wchar_t* wstring;
	HDC hDC  = wglGetCurrentDC(); 
	GLuint list  = glGenLists(1);
	len  = 0;
	for (i = 0; str[i] != '\0'; ++i) {
		if (IsDBCSLeadByte(str[i]))            
			++i;         
		++len;
	}
	wstring  = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len); 
	wstring[len] = L'\0';
	for (i = 0; i < len; ++i) {
		wglUseFontBitmapsW(hDC, wstring[i], 1, list);
		glCallList(list);
	}
			free(wstring);
		glDeleteLists(list, 1);
	}