// ******************************************************************
// *
// *    .,-:::::    .,::      .::::::::.    .,::      .:
// *  ,;;;'````'    `;;;,  .,;;  ;;;'';;'   `;;;,  .,;; 
// *  [[[             '[[,,[['   [[[__[[\.    '[[,,[['  
// *  $$$              Y$$$P     $$""""Y$$     Y$$$P    
// *  `88bo,__,o,    oP"``"Yo,  _88o,,od8P   oP"``"Yo,  
// *    "YUMMMMMP",m"       "Mm,""YUMMMP" ,m"       "Mm,
// *
// *   Cxbx->Win32->Cxbx->WndAbout.cpp
// *
// *  This file is part of the Cxbx project.
// *
// *  Cxbx and Cxbe are free software; you can redistribute them
// *  and/or modify them under the terms of the GNU General Public
// *  License as published by the Free Software Foundation; either
// *  version 2 of the license, or (at your option) any later version.
// *
// *  This program is distributed in the hope that it will be useful,
// *  but WITHOUT ANY WARRANTY; without even the implied warranty of
// *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// *  GNU General Public License for more details.
// *
// *  You should have recieved a copy of the GNU General Public License
// *  along with this program; see the file COPYING.
// *  If not, write to the Free Software Foundation, Inc.,
// *  59 Temple Place - Suite 330, Bostom, MA 02111-1307, USA.
// *
// *  (c) 2002-2003 Aaron Robinson <caustik@caustik.com>
// *
// *  All rights reserved
// *
// ******************************************************************
#include "Cxbx.h"
#include "WndAbout.h"

#include "resource.h"

// ******************************************************************
// * constructor
// ******************************************************************
WndAbout::WndAbout(HINSTANCE x_hInstance, HWND x_parent) : Wnd(x_hInstance)
{
    m_classname = "WndAbout";
    m_wndname   = "Cxbx - About";

    m_w         = 200;
    m_h         = 120;

	// center to parent
    {
        RECT rect;

        GetWindowRect(x_parent, &rect);

        m_x = rect.left + (rect.right - rect.left)/2 - m_w/2;
        m_y = rect.top + (rect.bottom - rect.top)/2 - m_h/2;
    }

    m_parent    = x_parent;
    m_wndstyle  = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE;

    return;
}

// ******************************************************************
// * deconstructor
// ******************************************************************
WndAbout::~WndAbout()
{
}

// ******************************************************************
// * WndProc
// ******************************************************************
LRESULT CALLBACK WndAbout::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
        case WM_CREATE:
        {
            EnableWindow(m_parent, FALSE);

            HDC hDC = GetDC(hwnd);

            int nHeight = -MulDiv(8, GetDeviceCaps(hDC, LOGPIXELSY), 72);

			m_hFont = CreateFont(nHeight, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_ROMAN, "verdana");

            ReleaseDC(hwnd, hDC);
        }
        break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;

            BeginPaint(hwnd, &ps);

            HDC hDC = GetDC(hwnd);

            // draw text
            {
                HGDIOBJ tmpObj = SelectObject(hDC, m_hFont);

                // draw top version bar and bottom url bar
                {
                    SetBkColor(hDC, GetSysColor(COLOR_HIGHLIGHT));

				    SetTextColor(hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));

                    // top version bar
                    {
				        char buffer[] = " Cxbx Version " CXBX_VERSION;

                        RECT rect = {0, 0, 200, 14};
                        ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rect, buffer, strlen(buffer), 0);
                    }

                    // bottom url bar
                    {
				        char buffer[] = " http://www.caustik.com/xbox/";

                        RECT rect = {0, 74, 200, 88};
                        ExtTextOut(hDC, 0, 74, ETO_OPAQUE, &rect, buffer, strlen(buffer), 0);
                    }
                }

                // draw credits
                {
                    SetBkColor(hDC, RGB(0,0,0));

				    SetTextColor(hDC, RGB(0xFF,0xFF,0xFF));

                    char bufferA[] = " The First XBox Emulator";
                    char bufferB[] = " Designed and Coded by Caustik";
                    char bufferC[] = " (Click Window to Close)";

                    RECT rectA = {0, 22, 200, 37};
                    ExtTextOut(hDC, 0, 22, ETO_OPAQUE, &rectA, bufferA, strlen(bufferA), 0);

                    RECT rectB = {0, 37, 200, 51};
                    ExtTextOut(hDC, 0, 37, ETO_OPAQUE, &rectB, bufferB, strlen(bufferB), 0);

                    RECT rectC = {22, 53, 70, 67};
                    ExtTextOut(hDC, 22, 53, ETO_OPAQUE, &rectC, bufferC, strlen(bufferC), 0);
                }

                SelectObject(hDC, tmpObj);
            }

            if(hDC != NULL)
                ReleaseDC(hwnd, hDC);

            EndPaint(hwnd, &ps);
        }
        break;

        case WM_LBUTTONUP:
        {
            SendMessage(hwnd, WM_CLOSE, 0, 0);
        }
        break;

        case WM_CLOSE:
        {
            EnableWindow(m_parent, TRUE);
            DestroyWindow(hwnd);
        }
        break;

        case WM_DESTROY:
        {
            DeleteObject(m_hFont);
            PostQuitMessage(0);
        }
		break;

        default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

    return 0;
}