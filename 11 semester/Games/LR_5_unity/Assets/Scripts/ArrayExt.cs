using System.Linq;

public static class ArrayExt
{
    public static T[] GetRow<T>(this T[,] array, int row)
    {
        return Enumerable.Range(0, array.GetLength(1))
                         .Select(x => array[row, x])
                         .ToArray();
    }
        
    public static T[] GetColumn<T>(this T[,] array, int column)
    {
        return Enumerable.Range(0, array.GetLength(0))
                         .Select(x => array[x, column])
                         .ToArray();
    }
}