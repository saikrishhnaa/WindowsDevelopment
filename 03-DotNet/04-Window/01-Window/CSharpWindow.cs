/* Command to compile : cl.exe HelloWorld.cs */

using System;
using System.Windows.Forms;

public class CSharpWindow : Form
{
	public static void Main()
	{
		Application.Run(new CSharpWindow());
	}

	public CSharpWindow()
    {
		Text = "My C Sharp Window";
		BackColor = System.Drawing.Color.Black;
		ResizeRedraw = true;
    }
}
