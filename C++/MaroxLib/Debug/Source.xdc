<?xml version="1.0"?><doc>
<members>
<member name="M:_wassert(System.Char!System.Runtime.CompilerServices.IsConst*,System.Char!System.Runtime.CompilerServices.IsConst*,System.UInt32)" decl="true" source="f:\git\maroxlib\maroxlib\detail\http\common\include\stringprocess.h" line="1">
Copyright 2008-2009 Cheng Shi.  All rights reserved.
Email: shicheng107@hotmail.com

</member>
<member name="M:Marox.Tools.Convert.wstring_to_string(std.basic_string&lt;System.Char,std.char_traits{System.Char},std.allocator&lt;System.Char&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="f:\git\maroxlib\maroxlib\convert.hpp" line="12">
<summary>
Converts <c>wstring</c> to <c>string</c>
</summary>
<param name="_val">Source <c>wstring</c></param>
<returns>std::string</returns>
</member>
<member name="M:Marox.Tools.Convert.string_to_wstring(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="f:\git\maroxlib\maroxlib\convert.hpp" line="22">
<summary>
Converts <c>string</c> to <c>wstring</c>
</summary>
<param name="_val">Source <c>string</c></param>
<returns>std::wstring</returns>
</member>
<!-- Discarding badly formed XML document comment for member 'T:Marox.Threading.THREAD'. -->
<member name="M:Marox.Threading.THREAD.threadStart(System.Boolean)" decl="false" source="f:\git\maroxlib\maroxlib\threads.hpp" line="129">
<summary>
Starts the thread.
</summary>
<param name="_join">If set to <c>true</c>, the thread will be started with <c>join</c></param>
</member>
<member name="M:Marox.Threading.THREAD.threadStop" decl="false" source="f:\git\maroxlib\maroxlib\threads.hpp" line="152">
<summary>
Gives signal to finish thread loop execution.
</summary>
<remarks>
Disables the <c>isThreadRunning</c> flag, so works only if you have e.g. <c>while (isThreadRunning())</c> loop inside your thread method.
</remarks>
</member>
<member name="M:Marox.Threading.THREAD.getID" decl="false" source="f:\git\maroxlib\maroxlib\threads.hpp" line="162">
<summary>
Returns the thread id.
</summary>
<returns>Thread id as <c>std::thread::id</c></returns>
</member>
<member name="M:Marox.Threading.THREAD.isThreadRunning" decl="false" source="f:\git\maroxlib\maroxlib\threads.hpp" line="170">
<summary>
Checks whether the thread is running.
</summary>
<returns><c>true</c> if the thread is running, <c>false</c>if it is not</returns>
</member>
<member name="M:Marox.Threading.THREAD.isJoinable" decl="false" source="f:\git\maroxlib\maroxlib\threads.hpp" line="178">
<summary>
Checks whether the thread is joinable.
</summary>
<remarks>
(calls <c>std::thread::joinable()</c>)
</remarks>
<returns><c>true</c> if the thread is joinable</returns>
</member>
<member name="M:Marox.Threading.THREAD.join" decl="false" source="f:\git\maroxlib\maroxlib\threads.hpp" line="189">
<summary>
Method returns when the thread execution has completed. (calls <c>std::thread::join()</c>)
</summary>
\throw std::exception if thread is not joinable  
</member>
<member name="M:Marox.Threading.THREAD.Sleep(System.UInt32)" decl="false" source="f:\git\maroxlib\maroxlib\threads.hpp" line="205">
<summary>
Sleeps current thread.
</summary>
<remarks>
Meant to be used from within the desired thread, thus inside <c>run()</c> method or the main thread.
</remarks>
<param name="_ms">duration [ms]</param>
</member>
<member name="M:Marox.Threading.THREAD.run" decl="false" source="f:\git\maroxlib\maroxlib\threads.hpp" line="219">
<summary>
Main method of the thread - needs to be implemented in the derived class!
</summary>
<remarks>
If your thread works as the e.g loop, you should check the state of <c>isThreadRunning</c> flag inside your method implementation. (see <c>THREAD</c> example code)
</remarks>
</member>
<member name="M:Marox.Tools.Autostart.isProgramRegisteredForStartup(System.Char!System.Runtime.CompilerServices.IsConst*)" decl="false" source="f:\git\maroxlib\maroxlib\autostart.hpp" line="11">
<summary>
Checks whether application is registered for autostart
</summary>
<param name="pszAppName">Application name</param>
<returns></returns>
</member>
<member name="M:Marox.Tools.Autostart.registerMyProgramForStartup(System.Char!System.Runtime.CompilerServices.IsConst*)" decl="false" source="f:\git\maroxlib\maroxlib\autostart.hpp" line="48">
<summary>
Registers program for autostart
</summary>
<param name="_appName">Application name</param>
<returns></returns>
</member>
<member name="M:Marox.Tools.Window.hideConsoleWindow" decl="false" source="f:\git\maroxlib\maroxlib\other.hpp" line="15">
<summary>
Hides the console window.
</summary>
</member>
<member name="M:Marox.Tools.Window.showConsoleWindow" decl="false" source="f:\git\maroxlib\maroxlib\other.hpp" line="22">
<summary>
Shows the console window.
</summary>
</member>
<member name="M:Marox.Tools.return_current_time_and_date" decl="false" source="f:\git\maroxlib\maroxlib\other.hpp" line="30">
<summary>
Returns current time and date
</summary>
<returns>Returns <c>string</c> in the following format: <c>YYYY-MM-DD HH:MM:SS</c></returns>
</member>
<member name="T:Marox.Tools.Timer" decl="false" source="f:\git\maroxlib\maroxlib\time.hpp" line="8">
<summary>
Use Timers to indicate 'points' between which you want to measure time
</summary>
<example> Example usage:
<code>
Marox::Tools::Timer t1;
actions_to_be_done();
Marox::Tools::Timer t2;
auto duration = Marox::Tools::Timer::getDuration_milliseconds(t1,t2);
</code>
</example>
</member>
<member name="M:Marox.Tools.Timer.#ctor" decl="false" source="f:\git\maroxlib\maroxlib\time.hpp" line="22">
<summary>
Creates a <c>Timer</c>
</summary>
</member>
<member name="M:Marox.Tools.Timer.getDuration_milliseconds(Marox.Tools.Timer!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Marox.Tools.Timer!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="f:\git\maroxlib\maroxlib\time.hpp" line="30">
<summary>
Get time elapsed between two <c><see cref="T:Marox.Tools.Timer"/>s</c>
</summary>
<param name="timer_begin">Initial <c>Timer</c></param>
<param name="timer_end">Ending <c>Timer</c></param>
<returns>Duration in <c>milliseconds</c></returns>
</member>
<member name="M:Marox.Tools.Timer.getDuration_seconds(Marox.Tools.Timer!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Marox.Tools.Timer!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="f:\git\maroxlib\maroxlib\time.hpp" line="41">
<summary>
Get time elapsed between two <c><see cref="T:Marox.Tools.Timer"/>s</c>
</summary>
<param name="timer_begin">Initial <c>Timer</c></param>
<param name="timer_end">Ending <c>Timer</c></param>
<returns>Duration in <c>seconds</c></returns>
</member>
</members>
</doc>