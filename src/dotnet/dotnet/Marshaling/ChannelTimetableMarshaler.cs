/* 
 * FreeSWITCH Modular Media Switching Software Library / Soft-Switch Application
 * Copyright (C) 2006, James Martelletti <james@nerdc0re.com>
 *
 * Version: MPL 1.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is FreeSWITCH Modular Media Switching Software Library / Soft-Switch Application
 *
 * The Initial Developer of the Original Code is
 * James Martelletti <james@nerdc0re.com>
 * Portions created by the Initial Developer are Copyright (C)
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 * 
 * James Martelletti <james@nerdc0re.com>
 *
 *
 * ChannelTimetableMarshaler.cs -- 
 *
 */
using System;
using System.Runtime.InteropServices;
using FreeSwitch.NET.Types;
using FreeSwitch.NET.Marshaling.Types;

namespace FreeSwitch.NET.Marshaling
{
    class ChannelTimetableMarshaler : ICustomMarshaler
    {
        private static ChannelTimetableMarshaler Instance = new ChannelTimetableMarshaler();

        public static ICustomMarshaler GetInstance(string s)
        {
            return Instance;
        }

        public void CleanUpManagedData(object o)
        {
        }

        public void CleanUpNativeData(IntPtr pNativeData)
        {
        }

        public int GetNativeDataSize()
        {
            return IntPtr.Size;
        }

        public IntPtr MarshalManagedToNative(object obj)
        {
            ChannelTimetable channelTimetable = (ChannelTimetable)obj;

            return channelTimetable.marshaledObject.Handle;
        }

        public object MarshalNativeToManaged(IntPtr channelTimetablePtr)
        {
            ChannelTimetableMarshal channelTimetableMarshal = new ChannelTimetableMarshal();
            ChannelTimetable        channelTimetable        = new ChannelTimetable();

            Marshal.PtrToStructure(channelTimetablePtr, channelTimetableMarshal);

            channelTimetable.marshaledObject = new HandleRef(channelTimetableMarshal, channelTimetablePtr);

            return channelTimetable;
        }
    }
}
