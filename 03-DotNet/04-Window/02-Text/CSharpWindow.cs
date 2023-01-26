/* Command to compile : csc.exe /t:winexe CSharpWindow.cs */

using System;
using System.Drawing;
using System.Windows.Forms;

public class CSharpWindow : Form
{
	public static void Main()
	{
		Application.Run(new CSharpWindow());
	}

	public CSharpWindow()
    {
		Width = 800;
		Height = 600;
		Text = "My C Sharp Window";
		BackColor = Color.Black;
		ResizeRedraw = true;
    }

	protected override void OnPaint(PaintEventArgs pea)
    {
		Graphics grfx = pea.Graphics;

		StringFormat strfmt = new StringFormat();

		//Horizontal center
		strfmt.Alignment = StringAlignment.Center;

		strfmt.LineAlignment = StringAlignment.Center;

		grfx.DrawString("Hello World!!!",
			Font,
			new SolidBrush(Color.Green),
			ClientRectangle,
			strfmt);
    }
}
