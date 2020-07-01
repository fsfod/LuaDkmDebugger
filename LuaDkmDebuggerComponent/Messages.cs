using System;
using System.Collections.ObjectModel;
using System.IO;

namespace LuaDkmDebuggerComponent
{
    public class SupportBreakpointHitMessage
    {
        public Guid breakpointId;
        public Guid threadId;

        public ulong retAddr;
        public ulong frameBase;
        public ulong vframe;

        public byte[] Encode()
        {
            using (var stream = new MemoryStream())
            {
                using (var writer = new BinaryWriter(stream))
                {
                    writer.Write(breakpointId.ToByteArray());
                    writer.Write(threadId.ToByteArray());

                    writer.Write(retAddr);
                    writer.Write(frameBase);
                    writer.Write(vframe);

                    writer.Flush();

                    return stream.ToArray();
                }
            }
        }

        public bool ReadFrom(byte[] data)
        {
            using (var stream = new MemoryStream(data))
            {
                using (var reader = new BinaryReader(stream))
                {
                    breakpointId = new Guid(reader.ReadBytes(16));
                    threadId = new Guid(reader.ReadBytes(16));

                    retAddr = reader.ReadUInt64();
                    frameBase = reader.ReadUInt64();
                    vframe = reader.ReadUInt64();
                }
            }

            return true;
        }
    }

    public class HelperLocationsMessage
    {
        public ulong helperBreakCountAddress = 0;
        public ulong helperBreakDataAddress = 0;
        public ulong helperBreakHitIdAddress = 0;
        public ulong helperBreakHitLuaStateAddress = 0;
        public ulong helperBreakSourcesAddress = 0;

        public ulong helperStepOverAddress = 0;
        public ulong helperStepIntoAddress = 0;
        public ulong helperStepOutAddress = 0;
        public ulong helperSkipDepthAddress = 0;

        public Guid breakpointLuaHelperBreakpointHit;
        public Guid breakpointLuaHelperStepComplete;
        public Guid breakpointLuaHelperStepInto;
        public Guid breakpointLuaHelperStepOut;

        public ulong helperStartAddress = 0;
        public ulong helperEndAddress = 0;

        public ulong executionStartAddress = 0;
        public ulong executionEndAddress = 0;

        public byte[] Encode()
        {
            using (var stream = new MemoryStream())
            {
                using (var writer = new BinaryWriter(stream))
                {
                    writer.Write(helperBreakCountAddress);
                    writer.Write(helperBreakDataAddress);
                    writer.Write(helperBreakHitIdAddress);
                    writer.Write(helperBreakHitLuaStateAddress);
                    writer.Write(helperBreakSourcesAddress);

                    writer.Write(helperStepOverAddress);
                    writer.Write(helperStepIntoAddress);
                    writer.Write(helperStepOutAddress);
                    writer.Write(helperSkipDepthAddress);

                    writer.Write(breakpointLuaHelperBreakpointHit.ToByteArray());
                    writer.Write(breakpointLuaHelperStepComplete.ToByteArray());
                    writer.Write(breakpointLuaHelperStepInto.ToByteArray());
                    writer.Write(breakpointLuaHelperStepOut.ToByteArray());

                    writer.Write(helperStartAddress);
                    writer.Write(helperEndAddress);

                    writer.Write(executionStartAddress);
                    writer.Write(executionEndAddress);

                    writer.Flush();

                    return stream.ToArray();
                }
            }
        }

        public bool ReadFrom(byte[] data)
        {
            using (var stream = new MemoryStream(data))
            {
                using (var reader = new BinaryReader(stream))
                {
                    helperBreakCountAddress = reader.ReadUInt64();
                    helperBreakDataAddress = reader.ReadUInt64();
                    helperBreakHitIdAddress = reader.ReadUInt64();
                    helperBreakHitLuaStateAddress = reader.ReadUInt64();
                    helperBreakSourcesAddress = reader.ReadUInt64();

                    helperStepOverAddress = reader.ReadUInt64();
                    helperStepIntoAddress = reader.ReadUInt64();
                    helperStepOutAddress = reader.ReadUInt64();
                    helperSkipDepthAddress = reader.ReadUInt64();

                    breakpointLuaHelperBreakpointHit = new Guid(reader.ReadBytes(16));
                    breakpointLuaHelperStepComplete = new Guid(reader.ReadBytes(16));
                    breakpointLuaHelperStepInto = new Guid(reader.ReadBytes(16));
                    breakpointLuaHelperStepOut = new Guid(reader.ReadBytes(16));

                    helperStartAddress = reader.ReadUInt64();
                    helperEndAddress = reader.ReadUInt64();

                    executionStartAddress = reader.ReadUInt64();
                    executionEndAddress = reader.ReadUInt64();
                }
            }

            return true;
        }
    }

    public class RegisterStateMessage
    {
        public ulong stateAddress = 0;

        public ulong hookFunctionAddress = 0;
        public ulong hookBaseCountAddress = 0;
        public ulong hookCountAddress = 0;
        public ulong hookMaskAddress = 0;

        // For Lua 5.4 'settraps'
        public ulong setTrapStateCallInfoOffset = 0;
        public ulong setTrapCallInfoPreviousOffset = 0;
        public ulong setTrapCallInfoCallStatusOffset = 0;
        public ulong setTrapCallInfoTrapOffset = 0;

        public ulong helperHookFunctionAddress = 0;

        public byte[] Encode()
        {
            using (var stream = new MemoryStream())
            {
                using (var writer = new BinaryWriter(stream))
                {
                    writer.Write(stateAddress);

                    writer.Write(hookFunctionAddress);
                    writer.Write(hookBaseCountAddress);
                    writer.Write(hookCountAddress);
                    writer.Write(hookMaskAddress);

                    writer.Write(setTrapStateCallInfoOffset);
                    writer.Write(setTrapCallInfoPreviousOffset);
                    writer.Write(setTrapCallInfoCallStatusOffset);
                    writer.Write(setTrapCallInfoTrapOffset);

                    writer.Write(helperHookFunctionAddress);

                    writer.Flush();

                    return stream.ToArray();
                }
            }
        }

        public bool ReadFrom(byte[] data)
        {
            using (var stream = new MemoryStream(data))
            {
                using (var reader = new BinaryReader(stream))
                {
                    stateAddress = reader.ReadUInt64();

                    hookFunctionAddress = reader.ReadUInt64();
                    hookBaseCountAddress = reader.ReadUInt64();
                    hookCountAddress = reader.ReadUInt64();
                    hookMaskAddress = reader.ReadUInt64();

                    setTrapStateCallInfoOffset = reader.ReadUInt64();
                    setTrapCallInfoPreviousOffset = reader.ReadUInt64();
                    setTrapCallInfoCallStatusOffset = reader.ReadUInt64();
                    setTrapCallInfoTrapOffset = reader.ReadUInt64();

                    helperHookFunctionAddress = reader.ReadUInt64();
                }
            }

            return true;
        }
    }

    public class UnregisterStateMessage
    {
        public ulong stateAddress = 0;

        public byte[] Encode()
        {
            using (var stream = new MemoryStream())
            {
                using (var writer = new BinaryWriter(stream))
                {
                    writer.Write(stateAddress);

                    writer.Flush();

                    return stream.ToArray();
                }
            }
        }

        public bool ReadFrom(byte[] data)
        {
            using (var stream = new MemoryStream(data))
            {
                using (var reader = new BinaryReader(stream))
                {
                    stateAddress = reader.ReadUInt64();
                }
            }

            return true;
        }
    }

    public class LuaLocationsMessage
    {
        public ulong luaExecuteAtStart = 0;
        public ulong luaExecuteAtEnd = 0;

        public ulong luaNewStateAtStart = 0;
        public ulong luaNewStateAtEnd = 0;

        public ulong luaClose = 0;
        public ulong closeState = 0;

        public ulong luaLoadFileEx = 0;
        public ulong luaLoadFile = 0;
        public ulong solCompatLoadFileEx = 0;

        public ulong luaLoadBufferEx = 0;
        public ulong luaLoadBuffer = 0;

        public ulong luaLoad = 0;

        public ulong luaError = 0;
        public ulong luaRunError = 0;
        public ulong luaThrow = 0;
        public ulong luaRotate;

        public byte[] Encode()
        {
            using (var stream = new MemoryStream())
            {
                using (var writer = new BinaryWriter(stream))
                {
                    writer.Write(luaExecuteAtStart);
                    writer.Write(luaExecuteAtEnd);
                    writer.Write(luaNewStateAtStart);
                    writer.Write(luaNewStateAtEnd);
                    writer.Write(luaClose);
                    writer.Write(closeState);
                    writer.Write(luaLoadFileEx);
                    writer.Write(luaLoadFile);
                    writer.Write(solCompatLoadFileEx);
                    writer.Write(luaLoadBufferEx);
                    writer.Write(luaLoadBuffer);
                    writer.Write(luaLoad);
                    writer.Write(luaError);
                    writer.Write(luaRunError);
                    writer.Write(luaThrow);
                    writer.Write(luaRotate);

                    writer.Flush();

                    return stream.ToArray();
                }
            }
        }

        public bool ReadFrom(byte[] data)
        {
            using (var stream = new MemoryStream(data))
            {
                using (var reader = new BinaryReader(stream))
                {
                    luaExecuteAtStart = reader.ReadUInt64();
                    luaExecuteAtEnd = reader.ReadUInt64();
                    luaNewStateAtStart = reader.ReadUInt64();
                    luaNewStateAtEnd = reader.ReadUInt64();
                    luaClose = reader.ReadUInt64();
                    closeState = reader.ReadUInt64();
                    luaLoadFileEx = reader.ReadUInt64();
                    luaLoadFile = reader.ReadUInt64();
                    solCompatLoadFileEx = reader.ReadUInt64();
                    luaLoadBufferEx = reader.ReadUInt64();
                    luaLoadBuffer = reader.ReadUInt64();
                    luaLoad = reader.ReadUInt64();
                    luaError = reader.ReadUInt64();
                    luaRunError = reader.ReadUInt64();
                    luaThrow = reader.ReadUInt64();
                    luaRotate = reader.ReadUInt64();
                }
            }

            return true;
        }
    }
}
