/* Command to compile : cl.exe HelloWorld.cs */

using System;
using System.Runtime.InteropServices;

public class PInvoke 
{
	[DllImport("user32.dll")]
	public static extern int MessageBoxA(int handle, String message, String caption, int type);
	public static void Main()
	{
		MessageBoxA(0, "This is ANSI message box", "Message", 0);
	}
}
