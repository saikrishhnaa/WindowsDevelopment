/* 
 * Command to compile : csc.exe /t:library DotNetServerForFileInput.cs 
   Command to create typelibrary regasm.exe DotNetServerForFileInput.dll /tlb
 */

using System;
using System.IO;
using System.Runtime.InteropServices;

public class DotNetServerForInput
{
    public string ReadFromFile(string filePath)
    {
        return File.ReadAllText(filePath);    
    }
}
