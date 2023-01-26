/* Command to compile : csc.exe /t:winexe /res:MyIcon.ico CSharpWindow.cs */

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
		Icon = new Icon(GetType().Assembly.GetManifestResourceStream("MyIcon.ico"));
		Text = "My C Sharp Window";
		BackColor = Color.Black;
		ResizeRedraw = true;
		Width = 800;
		Height = 600;
		this.KeyDown += new KeyEventHandler(MyKeyDown);
		this.MouseDown += new MouseEventHandler(MyMouseDown);
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

	void MyKeyDown(object sender, KeyEventArgs e)
    {
		MessageBox.Show("A key is pressed.");
    }

	void MyMouseDown(object sender, MouseEventArgs e)
    {
		MessageBox.Show("A mouse is clicked.");
    }
}
