/* 
 * Command to compile : csc.exe /t:library DotNetServerForFileInput.cs 
   Command to create typelibrary regasm.exe DotNetServerForFileInput.dll /tlb
 */

using System;

public class DotNetServer
{
    public int SumOfTwoIntegers(int num1, int num2)
    {
        return num1 + num2;
    }

    public int SubtractionOfTwoIntegers(int num1, int num2)
    {
        return num1 - num2;
    }
}
