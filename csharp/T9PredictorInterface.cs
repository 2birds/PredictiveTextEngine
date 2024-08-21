using System; 
using System.Text; 
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Diagnostics;
using UnityEngine;
using System.Linq;

namespace T9Predictor
{
   class T9Predictor
   {
      public static List<string>? Predict(List<string> letterGroups)
      {
         if (letterGroups.Count() == 0 )
         {
            return null;
         }

         StringBuilder lg = new StringBuilder(string.Join(" ", letterGroups));

         int maxResultsSize = 100;
         StringBuilder rs = new StringBuilder(maxResultsSize);

         Predict(lg, rs, out maxResultsSize);
            UnityEngine.Debug.Log("rs.Length: " + rs.Length);
         UnityEngine.Debug.Log("maxResultsSize: " + maxResultsSize);
         if (maxResultsSize > 0)
         {
            UnityEngine.Debug.Log("rs.Length: " + rs.Length);
            List<string> resultsList = new List<string>(rs.ToString().Split(" "));
            UnityEngine.Debug.Log("resultsList.Count():" + resultsList.Count);
            return (resultsList.Count > 0) ? resultsList : null;
         }

         return null;
      }

      public static List<string>? PredictNextWord(string word)
      {
         StringBuilder w = new StringBuilder(word);

         int maxResultsSize = 100;
         StringBuilder rs = new StringBuilder(maxResultsSize);

         PredictNextWord(w, rs, out maxResultsSize);
         UnityEngine.Debug.Log("rs.Length: " + rs.Length);
         UnityEngine.Debug.Log("maxResultsSize: " + maxResultsSize);
         if (maxResultsSize > 0)
         {
            UnityEngine.Debug.Log("rs.Length: " + rs.Length);
            List<string> resultsList = new List<string>(rs.ToString().Split(" "));
            UnityEngine.Debug.Log("resultsList.Count():" + resultsList.Count);
            return (resultsList.Count > 0) ? resultsList : null;
         }

         return null;
      }

      [DllImport(@"T9Predictor_C_LIB.dll", CallingConvention = CallingConvention.Cdecl)]
      public extern static bool ParseFile(string fname);

      [DllImport(@"T9Predictor_C_LIB.dll", CallingConvention = CallingConvention.Cdecl)]
      public extern static bool Predict(StringBuilder groups, StringBuilder results, out int nResults);

      [DllImport(@"T9Predictor_C_LIB.dll", CallingConvention = CallingConvention.Cdecl)]
      public extern static bool PredictNextWord(StringBuilder word, StringBuilder results, out int nResults);
   }
}