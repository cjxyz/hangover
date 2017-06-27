/*
 * Copyright 2017 André Hentschel
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "user32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_ActivateKeyboardLayout,
    qemu_AddClipboardFormatListener,
    qemu_AdjustWindowRect,
    qemu_AdjustWindowRectEx,
    qemu_AlignRects,
    qemu_AppendMenuA,
    qemu_AppendMenuW,
    qemu_AttachThreadInput,
    qemu_BeginPaint,
    qemu_BlockInput,
    qemu_BroadcastSystemMessageA,
    qemu_BroadcastSystemMessageExA,
    qemu_BroadcastSystemMessageExW,
    qemu_BroadcastSystemMessageW,
    qemu_CalcChildScroll,
    qemu_CallMsgFilterA,
    qemu_CallMsgFilterW,
    qemu_CallNextHookEx,
    qemu_CascadeChildWindows,
    qemu_CascadeWindows,
    qemu_ChangeClipboardChain,
    qemu_ChangeMenuA,
    qemu_ChangeMenuW,
    qemu_ChangeWindowMessageFilter,
    qemu_CheckDlgButton,
    qemu_CheckMenuItem,
    qemu_CheckMenuRadioItem,
    qemu_CheckRadioButton,
    qemu_ClipCursor,
    qemu_CloseClipboard,
    qemu_CopyIcon,
    qemu_CopyImage,
    qemu_CountClipboardFormats,
    qemu_CreateCaret,
    qemu_CreateCursor,
    qemu_CreateDialogIndirectParamA,
    qemu_CreateDialogIndirectParamAorW,
    qemu_CreateDialogIndirectParamW,
    qemu_CreateDialogParamA,
    qemu_CreateDialogParamW,
    qemu_CreateIconIndirect,
    qemu_CreateMDIWindowA,
    qemu_CreateMDIWindowW,
    qemu_CreateMenu,
    qemu_CreatePopupMenu,
    qemu_DefDlgProcA,
    qemu_DefDlgProcW,
    qemu_DefFrameProcA,
    qemu_DefFrameProcW,
    qemu_DefMDIChildProcA,
    qemu_DefMDIChildProcW,
    qemu_DefRawInputProc,
    qemu_DefWindowProcA,
    qemu_DefWindowProcW,
    qemu_DeleteMenu,
    qemu_DeregisterShellHookWindow,
    qemu_DestroyCaret,
    qemu_DestroyCursor,
    qemu_DestroyIcon,
    qemu_DestroyMenu,
    qemu_DialogBoxIndirectParamA,
    qemu_DialogBoxIndirectParamAorW,
    qemu_DialogBoxIndirectParamW,
    qemu_DialogBoxParamA,
    qemu_DialogBoxParamW,
    qemu_DisableProcessWindowsGhosting,
    qemu_DispatchMessageA,
    qemu_DispatchMessageW,
    qemu_DlgDirListA,
    qemu_DlgDirListComboBoxA,
    qemu_DlgDirListComboBoxW,
    qemu_DlgDirListW,
    qemu_DlgDirSelectComboBoxExA,
    qemu_DlgDirSelectComboBoxExW,
    qemu_DlgDirSelectExA,
    qemu_DlgDirSelectExW,
    qemu_DrawCaption,
    qemu_DrawCaptionTempA,
    qemu_DrawCaptionTempW,
    qemu_DrawIcon,
    qemu_DrawIconEx,
    qemu_DrawMenuBar,
    qemu_DrawMenuBarTemp,
    qemu_EmptyClipboard,
    qemu_EnableMenuItem,
    qemu_EndDialog,
    qemu_EndMenu,
    qemu_EndPaint,
    qemu_EnumClipboardFormats,
    qemu_EnumDisplayDevicesA,
    qemu_EnumDisplayDevicesW,
    qemu_EnumDisplayMonitors,
    qemu_EnumPropsA,
    qemu_EnumPropsExA,
    qemu_EnumPropsExW,
    qemu_EnumPropsW,
    qemu_ExcludeUpdateRgn,
    qemu_GetActiveWindow,
    qemu_GetAltTabInfoA,
    qemu_GetAltTabInfoW,
    qemu_GetAppCompatFlags,
    qemu_GetAppCompatFlags2,
    qemu_GetAsyncKeyState,
    qemu_GetCapture,
    qemu_GetCaretBlinkTime,
    qemu_GetCaretPos,
    qemu_GetClassInfoA,
    qemu_GetClassInfoExA,
    qemu_GetClassInfoExW,
    qemu_GetClassInfoW,
    qemu_GetClassLongA,
    qemu_GetClassLongPtrA,
    qemu_GetClassLongPtrW,
    qemu_GetClassLongW,
    qemu_GetClassNameA,
    qemu_GetClassNameW,
    qemu_GetClassWord,
    qemu_GetClipboardData,
    qemu_GetClipboardFormatNameA,
    qemu_GetClipboardFormatNameW,
    qemu_GetClipboardOwner,
    qemu_GetClipboardSequenceNumber,
    qemu_GetClipboardViewer,
    qemu_GetClipCursor,
    qemu_GetComboBoxInfo,
    qemu_GetCursor,
    qemu_GetCursorFrameInfo,
    qemu_GetCursorInfo,
    qemu_GetCursorPos,
    qemu_GetDC,
    qemu_GetDCEx,
    qemu_GetDisplayConfigBufferSizes,
    qemu_GetDlgCtrlID,
    qemu_GetDlgItem,
    qemu_GetDlgItemInt,
    qemu_GetDlgItemTextA,
    qemu_GetDlgItemTextW,
    qemu_GetFocus,
    qemu_GetForegroundWindow,
    qemu_GetGUIThreadInfo,
    qemu_GetIconInfo,
    qemu_GetInputState,
    qemu_GetKBCodePage,
    qemu_GetKeyboardLayout,
    qemu_GetKeyboardLayoutNameA,
    qemu_GetKeyboardLayoutNameW,
    qemu_GetKeyboardState,
    qemu_GetKeyboardType,
    qemu_GetKeyNameTextA,
    qemu_GetKeyNameTextW,
    qemu_GetKeyState,
    qemu_GetLastInputInfo,
    qemu_GetListBoxInfo,
    qemu_GetMenu,
    qemu_GetMenuBarInfo,
    qemu_GetMenuContextHelpId,
    qemu_GetMenuDefaultItem,
    qemu_GetMenuInfo,
    qemu_GetMenuItemCount,
    qemu_GetMenuItemID,
    qemu_GetMenuItemInfoA,
    qemu_GetMenuItemInfoW,
    qemu_GetMenuItemRect,
    qemu_GetMenuState,
    qemu_GetMenuStringA,
    qemu_GetMenuStringW,
    qemu_GetMessageA,
    qemu_GetMessageExtraInfo,
    qemu_GetMessagePos,
    qemu_GetMessageTime,
    qemu_GetMessageW,
    qemu_GetMonitorInfoA,
    qemu_GetMonitorInfoW,
    qemu_GetNextDlgGroupItem,
    qemu_GetNextDlgTabItem,
    qemu_GetOpenClipboardWindow,
    qemu_GetPhysicalCursorPos,
    qemu_GetPriorityClipboardFormat,
    qemu_GetProgmanWindow,
    qemu_GetPropA,
    qemu_GetPropW,
    qemu_GetQueueStatus,
    qemu_GetRawInputBuffer,
    qemu_GetRawInputData,
    qemu_GetRawInputDeviceInfoA,
    qemu_GetRawInputDeviceInfoW,
    qemu_GetRawInputDeviceList,
    qemu_GetRegisteredRawInputDevices,
    qemu_GetShellWindow,
    qemu_GetSubMenu,
    qemu_GetSystemMenu,
    qemu_GetTaskmanWindow,
    qemu_GetTitleBarInfo,
    qemu_GetUpdatedClipboardFormats,
    qemu_GetUpdateRect,
    qemu_GetUpdateRgn,
    qemu_GetWindowDC,
    qemu_HideCaret,
    qemu_HiliteMenuItem,
    qemu_InSendMessage,
    qemu_InSendMessageEx,
    qemu_InsertMenuA,
    qemu_InsertMenuItemA,
    qemu_InsertMenuItemW,
    qemu_InsertMenuW,
    qemu_InvalidateRect,
    qemu_InvalidateRgn,
    qemu_IsClipboardFormatAvailable,
    qemu_IsDialogMessageA,
    qemu_IsDialogMessageW,
    qemu_IsDlgButtonChecked,
    qemu_IsGUIThread,
    qemu_IsHungAppWindow,
    qemu_IsMenu,
    qemu_IsTouchWindow,
    qemu_IsWindowRedirectedForPrint,
    qemu_IsWinEventHookInstalled,
    qemu_keybd_event,
    qemu_KillSystemTimer,
    qemu_KillTimer,
    qemu_LoadBitmapA,
    qemu_LoadBitmapW,
    qemu_LoadCursorA,
    qemu_LoadCursorFromFileA,
    qemu_LoadCursorFromFileW,
    qemu_LoadCursorW,
    qemu_LoadIconA,
    qemu_LoadIconW,
    qemu_LoadImageA,
    qemu_LoadImageW,
    qemu_LoadKeyboardLayoutA,
    qemu_LoadKeyboardLayoutW,
    qemu_LoadLocalFonts,
    qemu_LoadMenuA,
    qemu_LoadMenuIndirectA,
    qemu_LoadMenuIndirectW,
    qemu_LoadMenuW,
    qemu_LockWindowUpdate,
    qemu_LookupIconIdFromDirectory,
    qemu_LookupIconIdFromDirectoryEx,
    qemu_MapDialogRect,
    qemu_MapVirtualKeyA,
    qemu_MapVirtualKeyExA,
    qemu_MapVirtualKeyExW,
    qemu_MapVirtualKeyW,
    qemu_MessageBeep,
    qemu_MessageBoxA,
    qemu_MessageBoxExA,
    qemu_MessageBoxExW,
    qemu_MessageBoxIndirectA,
    qemu_MessageBoxIndirectW,
    qemu_MessageBoxTimeoutA,
    qemu_MessageBoxTimeoutW,
    qemu_MessageBoxW,
    qemu_ModifyMenuA,
    qemu_ModifyMenuW,
    qemu_MonitorFromRect,
    qemu_MonitorFromWindow,
    qemu_mouse_event,
    qemu_MsgWaitForMultipleObjects,
    qemu_MsgWaitForMultipleObjectsEx,
    qemu_NotifyWinEvent,
    qemu_OemKeyScan,
    qemu_OemToCharA,
    qemu_OpenClipboard,
    qemu_PaintDesktop,
    qemu_PeekMessageA,
    qemu_PeekMessageW,
    qemu_PostMessageA,
    qemu_PostMessageW,
    qemu_PostQuitMessage,
    qemu_PostThreadMessageA,
    qemu_PostThreadMessageW,
    qemu_PrintWindow,
    qemu_PrivateExtractIconExA,
    qemu_PrivateExtractIconExW,
    qemu_PrivateExtractIconsA,
    qemu_PrivateExtractIconsW,
    qemu_RealGetWindowClassA,
    qemu_RealGetWindowClassW,
    qemu_RedrawWindow,
    qemu_RegisterClassA,
    qemu_RegisterClassExA,
    qemu_RegisterClassExW,
    qemu_RegisterClassW,
    qemu_RegisterClipboardFormatA,
    qemu_RegisterClipboardFormatW,
    qemu_RegisterDeviceNotificationA,
    qemu_RegisterDeviceNotificationW,
    qemu_RegisterHotKey,
    qemu_RegisterLogonProcess,
    qemu_RegisterPowerSettingNotification,
    qemu_RegisterShellHookWindow,
    qemu_RegisterSystemThread,
    qemu_RegisterTasklist,
    qemu_RegisterWindowMessageA,
    qemu_RegisterWindowMessageW,
    qemu_ReleaseCapture,
    qemu_ReleaseDC,
    qemu_RemoveClipboardFormatListener,
    qemu_RemoveMenu,
    qemu_RemovePropA,
    qemu_RemovePropW,
    qemu_ReplyMessage,
    qemu_ScrollChildren,
    qemu_ScrollDC,
    qemu_ScrollWindow,
    qemu_ScrollWindowEx,
    qemu_SendDlgItemMessageA,
    qemu_SendDlgItemMessageW,
    qemu_SendIMEMessageExA,
    qemu_SendIMEMessageExW,
    qemu_SendInput,
    qemu_SendMessageA,
    qemu_SendMessageCallbackA,
    qemu_SendMessageCallbackW,
    qemu_SendMessageTimeoutA,
    qemu_SendMessageTimeoutW,
    qemu_SendMessageW,
    qemu_SendNotifyMessageA,
    qemu_SendNotifyMessageW,
    qemu_SetActiveWindow,
    qemu_SetCapture,
    qemu_SetCaretBlinkTime,
    qemu_SetCaretPos,
    qemu_SetClassLongA,
    qemu_SetClassLongPtrA,
    qemu_SetClassLongPtrW,
    qemu_SetClassLongW,
    qemu_SetClassWord,
    qemu_SetClipboardData,
    qemu_SetClipboardViewer,
    qemu_SetCoalescableTimer,
    qemu_SetCursor,
    qemu_SetCursorPos,
    qemu_SetDebugErrorLevel,
    qemu_SetDeskWallPaper,
    qemu_SetDlgItemInt,
    qemu_SetDlgItemTextA,
    qemu_SetDlgItemTextW,
    qemu_SetFocus,
    qemu_SetForegroundWindow,
    qemu_SetKeyboardState,
    qemu_SetLastErrorEx,
    qemu_SetLogonNotifyWindow,
    qemu_SetMenu,
    qemu_SetMenuContextHelpId,
    qemu_SetMenuDefaultItem,
    qemu_SetMenuInfo,
    qemu_SetMenuItemBitmaps,
    qemu_SetMenuItemInfoA,
    qemu_SetMenuItemInfoW,
    qemu_SetMessageExtraInfo,
    qemu_SetMessageQueue,
    qemu_SetPhysicalCursorPos,
    qemu_SetProgmanWindow,
    qemu_SetPropA,
    qemu_SetPropW,
    qemu_SetShellWindow,
    qemu_SetShellWindowEx,
    qemu_SetSystemCursor,
    qemu_SetSystemMenu,
    qemu_SetSystemTimer,
    qemu_SetTaskmanWindow,
    qemu_SetTimer,
    qemu_SetWindowsHookA,
    qemu_SetWindowsHookExA,
    qemu_SetWindowsHookExW,
    qemu_SetWindowsHookW,
    qemu_SetWindowStationUser,
    qemu_SetWinEventHook,
    qemu_ShowCaret,
    qemu_ShowCursor,
    qemu_TileChildWindows,
    qemu_TileWindows,
    qemu_ToAscii,
    qemu_ToAsciiEx,
    qemu_ToUnicode,
    qemu_ToUnicodeEx,
    qemu_TrackMouseEvent,
    qemu_TrackPopupMenu,
    qemu_TrackPopupMenuEx,
    qemu_TranslateAcceleratorA,
    qemu_TranslateAcceleratorW,
    qemu_TranslateMDISysAccel,
    qemu_TranslateMessage,
    qemu_UnhookWindowsHook,
    qemu_UnhookWindowsHookEx,
    qemu_UnhookWinEvent,
    qemu_UnloadKeyboardLayout,
    qemu_UnregisterClassA,
    qemu_UnregisterClassW,
    qemu_UnregisterDeviceNotification,
    qemu_UnregisterHotKey,
    qemu_UnregisterPowerSettingNotification,
    qemu_UpdateWindow,
    qemu_User32InitializeImmEntryTable,
    qemu_UserHandleGrantAccess,
    qemu_ValidateRect,
    qemu_ValidateRgn,
    qemu_VkKeyScanA,
    qemu_VkKeyScanW,
    qemu_WaitForInputIdle,
    qemu_WaitMessage,
    qemu_WindowFromDC,
    qemu_WINNLSEnableIME,
    qemu_WINNLSGetEnableStatus,
    qemu_WINNLSGetIMEHotkey,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side user32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
