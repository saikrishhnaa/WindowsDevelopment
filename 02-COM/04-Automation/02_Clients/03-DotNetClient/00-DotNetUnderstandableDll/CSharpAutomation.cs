using System;
using System.Runtime.InteropServices;
using AutomationServerTypeLibForDotNet;

public class CSharpAutomation
{
	public static void Main()
    {
        // Code
        CMyMathClass objCMyMathClass = new CMyMathClass();
        IMyMath objIMyMath = (IMyMath) objCMyMathClass;

        int num1, num2, sum, subtract;

        num1 = 165;
        num2 = 135;

        sum = objIMyMath.SumOfTwoIntegers(num1, num2);
        Console.WriteLine("Sum of " + num1 + " and " + num2 + " is " + sum);

        subtract = objIMyMath.SubtractionOfTwoIntegers(num1, num2);
        Console.WriteLine("Subtraction of " + num1 + " and " + num2 + " is " + subtract);
    }
}
