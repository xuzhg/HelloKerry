using BenchmarkDotNet.Running;
using Microsoft.OData.Edm;
using System;
using System.Collections.Generic;
using System.Linq;

namespace ResolvePropertyBenchmark
{
    internal class Program
    {
        static void Main(string[] args)
        {
            //IDictionary<string, object> data = new Dictionary<string, object>(StringComparer.OrdinalIgnoreCase);
            //data.Add("title", 1);
            //data.Add("Title", 2);
            EdmLibTest.Test(10);
            EdmLibTest.Test(100);

            Console.WriteLine("Press any key to run benchmark...");
            Console.ReadKey();

            var summary = BenchmarkRunner.Run<EdmLibTest>();

            Console.WriteLine("Hello World!");
        }
    }
}
