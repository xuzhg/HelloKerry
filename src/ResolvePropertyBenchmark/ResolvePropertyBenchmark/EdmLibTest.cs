using BenchmarkDotNet.Attributes;
using Microsoft.OData.Edm;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ResolvePropertyBenchmark
{
    [MemoryDiagnoser]
    public class EdmLibTest
    {
       // [Params(10, 100, 1,000,000)]
        [Params(10, 100)]
        public int N; // number of property

        private string caseName1;
        private string caseName2;
   //     private string caseName3;
   //     private string unknowcase;

        private IEdmEntityType _entityType;

        public static void Test(int n)
        {
            Console.WriteLine($"\nTest in N = {n}");

            EdmLibTest test = new EdmLibTest
            {
                N = n
            };

            test.GlobalSetup();

            IEdmProperty property = test._entityType.FindProperty(test.caseName1);
            Console.WriteLine($"FindProperty {test.caseName1}:- ' {property?.Name}'");

            property = test._entityType.FindProperty(test.caseName2);
            Console.WriteLine($"FindProperty {test.caseName2}:- ' {property?.Name}'");

            property = test._entityType.FindProperty(test.caseName1, true);
            Console.WriteLine($"FindProperty-CaseInsensitive_LinqWhere {test.caseName1}:- ' {property?.Name}'");

            property = test._entityType.FindProperty(test.caseName2, true);
            Console.WriteLine($"FindProperty-CaseInsensitive_LinqWhere {test.caseName2}:- ' {property?.Name}'");

            property = test._entityType.FindProperty2(test.caseName1, true);
            Console.WriteLine($"FindProperty-CaseInsensitive_DoubleForeach {test.caseName1}:- ' {property?.Name}'");

            property = test._entityType.FindProperty2(test.caseName2, true);
            Console.WriteLine($"FindProperty-CaseInsensitive_DoubleForeach {test.caseName2}:- ' {property?.Name}'");

            property = test._entityType.FindProperty3(test.caseName1, true);
            Console.WriteLine($"FindProperty-CaseInsensitive_Lookup {test.caseName1}:- ' {property?.Name}'");

            property = test._entityType.FindProperty3(test.caseName2, true);
            Console.WriteLine($"FindProperty-CaseInsensitive_Lookup {test.caseName2}:- ' {property?.Name}'");

            EdmEntityType entityType = (EdmEntityType)test._entityType;
            entityType.AddStructuralProperty("title8", EdmPrimitiveTypeKind.Int32);

            try
            {
                entityType.Properties().ToDictionary(p => p.Name, p => p, StringComparer.OrdinalIgnoreCase);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"{ex.Message}");
            }

            var lookup = entityType.Properties().ToLookup(p => p.Name, p => p, StringComparer.OrdinalIgnoreCase);

            if (lookup.Contains("title8"))
            {
                var group = lookup["title8"];
                foreach (var edmProperty in group)
                {
                    Console.WriteLine($"------{edmProperty.Name}");
                }
            }

            var group1 = lookup["unknown"];
            Console.WriteLine($"group1 = {group1.Count()}");
        }

        [GlobalSetup]
        public void GlobalSetup()
        {
            EdmEntityType entityType = new EdmEntityType("NS", "Customer");

            for(int i = 0; i< N; i++)
            {
                entityType.AddStructuralProperty($"Title{i}", EdmPrimitiveTypeKind.Int32);
        //        entityType.AddStructuralProperty($"tiTle{i}", EdmPrimitiveTypeKind.String);
        //        entityType.AddStructuralProperty($"title{i}", EdmPrimitiveTypeKind.Double);
            }

            caseName1 = $"Title{N - 2}";
            caseName2 = $"tiTle{N - 2}";
            _entityType = entityType;

            Console.WriteLine($"EntityType PropertyNumber: {entityType.Properties().Count()}");
            Console.WriteLine($"caseName1: {caseName1}");
            Console.WriteLine($"caseName2: {caseName2}");
        }

        [Benchmark]
        public void FindProperty_Title8_CaseSensitive_Interface()
        {
            IEdmProperty property = _entityType.FindProperty(caseName1);
        }

        [Benchmark]
        public void FindProperty_tiTle8_CaseSensitive_Interface()
        {
            IEdmProperty property = _entityType.FindProperty(caseName2);
        }

        [Benchmark]
        public void FindProperty_Title8_CaseInSensitive_LinqWhere()
        {
            IEdmProperty property = _entityType.FindProperty(caseName1, true);
        }

        [Benchmark]
        public void FindProperty_tiTle8_CaseInSensitive_LinqWhere()
        {
            IEdmProperty property = _entityType.FindProperty(caseName2, true);
        }

        [Benchmark]
        public void FindProperty_Title8_CaseInSensitive_DoubleForeach()
        {
            IEdmProperty property = _entityType.FindProperty2(caseName1, true);
        }

        [Benchmark]
        public void FindProperty_tiTle8_CaseInSensitive_DoubleForeach()
        {
            IEdmProperty property = _entityType.FindProperty2(caseName2, true);
        }

        [Benchmark]
        public void FindProperty_Title8_CaseInSensitive_Lookup()
        {
            IEdmProperty property = _entityType.FindProperty3(caseName1, true);
        }

        [Benchmark]
        public void FindProperty_tiTle8_CaseInSensitive_Lookup()
        {
            IEdmProperty property = _entityType.FindProperty3(caseName2, true);
        }
    }
}
