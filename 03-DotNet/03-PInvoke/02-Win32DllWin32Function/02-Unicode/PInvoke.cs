/* Command to compile : cl.exe HelloWorld.cs */

using System;
using System.Runtime.InteropServices;

public class PInvoke 
{
	[DllImport("user32.dll", CharSet = CharSet.Unicode)]
	public static extern int MessageBoxW(int handle, String message, String caption, int type);
	public static void Main()
	{
		MessageBoxW(0, "This is Unicode message box", "Message", 0);
	}
}
