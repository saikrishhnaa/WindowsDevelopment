/* 
 * Command to compile : csc.exe /t:library DotNetServerForFileInput.cs 
   Command to create typelibrary regasm.exe DotNetServerForFileInput.dll /tlb
 */

using System;
using System.IO;
using System.Runtime.InteropServices;

public class DotNetServerForInput
{
    [return: MarshalAs(UnmanagedType.BStr)]
    public String ReadFromFile(string filePath)
    {
        File.WriteAllText("log.txt", File.ReadAllText(filePath));
        return File.ReadAllText(filePath);
    }
}
