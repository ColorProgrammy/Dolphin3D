/*
File: log.cs
Developer: ColorProgrammy

Description:
Makes a log to help if someone has problems with the code.
*/

using System;
using System.IO;
using System.Collections.Generic;
using System.Diagnostics;

class Program
{
    static void Main()
    {
        LogKeywordsInFile("log.txt");
    }

    static void LogKeywordsInFile(string filePath)
    {
        var keywordsMessages = new Dictionary<string, string>
        {
            { "RotateX", "RotateX command begins." },
            { "RotateY", "RotateY command begins." },
            { "RotateZ", "RotateZ command begins." },
            { "Vector2.h", "Vector2.h library loaded" },
            { "Vector3.h", "Vector3.h library loaded" },
            { "int Width", "The Width variable is set" },
            { "Vector3.h", "Vector3.h library loaded" },
            { "Vector3.h", "Vector3.h library loaded" },
            { "Vector3.h", "Vector3.h library loaded" },
            { "Vector3.h", "Vector3.h library loaded" },
            { "Vector3.h", "Vector3.h library loaded" },
            { "Vector3.h", "Vector3.h library loaded" },
            { "Vector3.h", "Vector3.h library loaded" },
            { "Vector3.h", "Vector3.h library loaded" },
            { "Vector3.h", "Vector3.h library loaded" },
            { "Vector3.h", "Vector3.h library loaded" },
            { "Vector3.h", "Vector3.h library loaded" },
            { "Vector3.h", "Vector3.h library loaded" },
            { "Vector3.h", "Vector3.h library loaded" },
            { "Vector3.h", "Vector3.h library loaded" }
        };

        string content = File.ReadAllText(filePath);
        var logMessages = new List<string>();

        foreach (var kvp in keywordsMessages)
        {
            if (content.Contains(kvp.Key))
            {
                logMessages.Add(kvp.Value);
            }
        }

        Stopwatch stopwatch = Stopwatch.StartNew();

        using (StreamWriter logFile = new StreamWriter("debug.log", true))
        {
            foreach (var msg in logMessages)
            {
                logFile.WriteLine(msg);
            }

            stopwatch.Stop();
            double elapsedTimeMs = stopwatch.Elapsed.TotalMilliseconds;
            logFile.WriteLine($"Elapsed time: {elapsedTimeMs:F2} ms");
            logFile.WriteLine($"Date and Time: {DateTime.Now:yyyy-MM-dd HH:mm:ss}");
        }
    }
}
