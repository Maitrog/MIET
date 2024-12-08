using System;
using System.Linq;
using UnityEngine;
using UnityEngine.SceneManagement;

public class FieldGenerator : MonoBehaviour
{
    [SerializeField] private int columns = 10;
    [SerializeField] private int rows = 10;
    [SerializeField] private int floors = 10;
    [SerializeField] private double bombDensity = 0.13;
    private GameObject[,] CellsFloor;
    private GameObject[,] CellsRoof;
    private GameObject[,] CellsWall_1;
    private GameObject[,] CellsWall_2;
    private GameObject[,] CellsWall_3;
    private GameObject[,] CellsWall_4;

    [SerializeField] private GameObject cellPrefab;
    [SerializeField] private Material[] materials;
    [SerializeField] private Material bombMaterial;
    [SerializeField] private Material emptyMaterial;

    private int BombCountFloor => (int)(rows * columns * bombDensity);
    private int BombCountWall_14 => (int)(floors * columns * bombDensity);
    private int BombCountWall_23 => (int)(floors * rows * bombDensity);

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        Debug.Log("Start method");
        CellsFloor = new GameObject[rows, columns];
        CreateCells(CellsFloor, rows, columns, (x, z) => new Vector3(x, 0, z));

        CellsRoof = new GameObject[rows, columns];
        CreateCells(CellsRoof, rows, columns, (x, z) => new Vector3(x, floors + 1, z));

        CellsWall_1 = new GameObject[floors, columns];
        CreateCells(CellsWall_1, floors, columns, (x, z) => new Vector3(rows / 2, x + floors / 2 + 1, z));

        CellsWall_2 = new GameObject[floors, rows];
        CreateCells(CellsWall_2, floors, rows, (x, z) => new Vector3(z, x + floors / 2 + 1, columns / 2));

        CellsWall_3 = new GameObject[floors, rows];
        CreateCells(CellsWall_3, floors, rows, (x, z) => new Vector3(z, x + floors / 2 + 1, - columns / 2 - 1));

        CellsWall_4 = new GameObject[floors, columns];
        CreateCells(CellsWall_4, floors, columns, (x, z) => new Vector3(- rows / 2 - 1, x + floors / 2 + 1, z));

        FillBomb(CellsFloor, BombCountFloor, rows, columns);
        FillBomb(CellsRoof, BombCountFloor, rows, columns);
        FillBomb(CellsWall_1, BombCountWall_14, floors, columns);
        FillBomb(CellsWall_2, BombCountWall_23, floors, rows);
        FillBomb(CellsWall_3, BombCountWall_23, floors, rows);
        FillBomb(CellsWall_4, BombCountWall_14, floors, columns);

        for (var i = 0; i < rows; i++)
        {
            for (var j = 0; j < columns; j++)
            {
                SubscribeObservers(CellsFloor, i,j, rows, columns, CellsWall_3.GetRow(0), CellsWall_2.GetRow(0), CellsWall_4.GetRow(0), CellsWall_1.GetRow(0));
                SubscribeObservers(CellsRoof, i,j, rows, columns, CellsWall_3.GetRow(floors - 1), CellsWall_2.GetRow(floors - 1), CellsWall_4.GetRow(floors - 1), CellsWall_1.GetRow(floors - 1));
            }
        }
        
        for (var i = 0; i < floors; i++)
        {
            for (var j = 0; j < rows; j++)
            {
                SubscribeObservers(CellsWall_2, i, j, floors, rows, CellsWall_4.GetColumn(columns - 1), CellsWall_1.GetColumn(columns - 1), CellsFloor.GetColumn(columns - 1), CellsRoof.GetColumn(0));
                SubscribeObservers(CellsWall_3, i, j, floors, rows, CellsWall_4.GetColumn(0), CellsWall_1.GetColumn(0), CellsFloor.GetColumn(0), CellsRoof.GetColumn(0));
            }
            for (var j = 0; j < columns; j++)
            {
                SubscribeObservers(CellsWall_1, i, j, floors, columns, CellsWall_3.GetColumn(rows - 1), CellsWall_2.GetColumn(rows - 1), CellsFloor.GetRow(rows - 1), CellsRoof.GetRow(rows - 1));
                SubscribeObservers(CellsWall_4, i, j, floors, columns, CellsWall_3.GetColumn(0), CellsWall_2.GetColumn(0), CellsFloor.GetRow(0), CellsRoof.GetRow(0));
            }
        }
    }

    private void CreateCells(GameObject[,] cells, int rows, int columns, Func<int, int, Vector3> getOffset)
    {
        var halfRows = rows / 2;
        var halfColumns = columns / 2;
        for (var x = -halfRows; x < rows - halfRows; x++)
        {
            for (var z = -halfColumns; z < columns - halfColumns; z++)
            {
                var offset = getOffset(x, z);
                var block = Instantiate(cellPrefab, offset, Quaternion.identity);
                block.transform.position = transform.position + offset;

                block.GetComponent<Renderer>().material = emptyMaterial;
                cells[halfRows + x, halfColumns + z] = block;
            }
        }
    }

    private static void FillBomb(GameObject[,] cells, int bombCount, int rows, int columns)
    {
        var rnd = new System.Random();
        for (var i = 0; i < bombCount; i++)
        {
            var cellNumber = rnd.Next(0, rows * columns);
            if (cells[cellNumber / columns, cellNumber % columns].GetComponent<CellBehaviour>().Cell.IsBomb)
            {
                i--;
            }
            else
            {
                cells[cellNumber / columns, cellNumber % columns].GetComponent<CellBehaviour>().Cell = new BombCell();
            }
        }
    }
    
    private static void SubscribeObservers(GameObject[,] cells, int i, int j, int iSize, int jSize, GameObject[] left, GameObject[] right, GameObject[] up, GameObject[] down)
    {
        if (i != 0)
        {
            cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(cells[i - 1, j].GetComponent<CellBehaviour>().Cell);
        }
        if (i != iSize - 1)
        {
            cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(cells[i + 1, j].GetComponent<CellBehaviour>().Cell);
        }
        if (j != 0)
        {
            cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(cells[i, j - 1].GetComponent<CellBehaviour>().Cell);
        }
        if (j != jSize - 1)
        {
            cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(cells[i, j + 1].GetComponent<CellBehaviour>().Cell);
        }
        if (i != 0 && j != 0)
        {
            cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(cells[i - 1, j - 1].GetComponent<CellBehaviour>().Cell);
        }
        if (i != iSize - 1 && j != 0)
        {
            cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(cells[i + 1, j - 1].GetComponent<CellBehaviour>().Cell);
        }
        if (i != 0 && j != jSize - 1)
        {
            cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(cells[i - 1, j + 1].GetComponent<CellBehaviour>().Cell);
        }
        if (i != iSize - 1 && j != jSize - 1)
        {
            cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(cells[i + 1, j + 1].GetComponent<CellBehaviour>().Cell);
        }
        
        // соседние стороны
        if (i == 0)
        {
            cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(up[j].GetComponent<CellBehaviour>().Cell);

            if (j != 0)
            {
                cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(up[j - 1].GetComponent<CellBehaviour>().Cell);
            }

            if (j != jSize - 1)
            {
                cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(up[j + 1].GetComponent<CellBehaviour>().Cell);
            }
        }
        
        if (i == iSize - 1)
        {
            cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(down[j].GetComponent<CellBehaviour>().Cell);
            if (j != 0)
            {
                cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(down[j - 1].GetComponent<CellBehaviour>().Cell);
            }
            if (j != jSize - 1)
            {
                cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(down[j + 1].GetComponent<CellBehaviour>().Cell);
            }
        }
        
        if (j == 0)
        {
            cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(left[i].GetComponent<CellBehaviour>().Cell);

            if ( i != 0)
            {
                cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(left[i - 1].GetComponent<CellBehaviour>().Cell);
            }

            if (i != iSize - 1)
            {
                cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(left[i + 1].GetComponent<CellBehaviour>().Cell);
            }
        }
        
        if (j == jSize - 1)
        {
            cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(right[i].GetComponent<CellBehaviour>().Cell);

            if (i != 0)
            {
                cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(right[i - 1].GetComponent<CellBehaviour>().Cell);
            }

            if (i != iSize - 1)
            {
                cells[i, j].GetComponent<CellBehaviour>().Cell.Attach(right[i + 1].GetComponent<CellBehaviour>().Cell);
            }
        }
        
    }

    public void Click(GameObject obj)
    {
        var cellClicked = obj.GetComponent<CellBehaviour>().Cell;
        if (cellClicked == null) return;

        var bombCount = cellClicked.Click();
        if (bombCount == -1)
        {
            ShowAllBombs();
            SceneManager.LoadScene("LoseScene");
            return;
        }

        OpenAllCells();

        if (IsWin())
        {
            SceneManager.LoadScene("WinScene");
        }
    }

    private void OpenAllCells()
    {
        OpenCells(CellsFloor);
        OpenCells(CellsRoof);
        OpenCells(CellsWall_1);
        OpenCells(CellsWall_2);
        OpenCells(CellsWall_3);
        OpenCells(CellsWall_4);
    }

    private void ShowAllBombs()
    {
        ShowBombs(CellsFloor);
        ShowBombs(CellsRoof);
        ShowBombs(CellsWall_1);
        ShowBombs(CellsWall_2);
        ShowBombs(CellsWall_3);
        ShowBombs(CellsWall_4);
    }

    private void ShowBombs(GameObject[,] cells)
    {
        foreach (var cellObj in cells)
        {
            var cell = cellObj.GetComponent<CellBehaviour>()?.Cell;
            var renderer = cellObj.GetComponent<Renderer>();

            if (cell.IsBomb)
            {
                renderer.material = bombMaterial;
            }
        }
    }

    private void OpenCells(GameObject[,] cells)
    {
        foreach (var cellObj in cells)
        {
            var cell = cellObj.GetComponent<CellBehaviour>()?.Cell;
            var renderer = cellObj.GetComponent<Renderer>();

            if (cell is not { IsOpen: true, IsBomb: false }) continue;
            var bombCount = cell.Click();
            if (bombCount == 0)
            {
                var highlightMaterial = new Material(renderer.material)
                {
                    color = Color.gray
                };
                renderer.material = highlightMaterial;
            }
            else
            {
                renderer.material = materials[bombCount - 1];
            }
        }
    }

    private bool IsWin()
    {
        return IsAllMarked(CellsFloor)
               && IsAllMarked(CellsRoof)
               && IsAllMarked(CellsWall_1)
               && IsAllMarked(CellsWall_2) 
               && IsAllMarked(CellsWall_3) 
               && IsAllMarked(CellsWall_4);
        
    }
    private bool IsAllMarked(GameObject[,] cells)
    {
        return (from GameObject cellObj in cells select cellObj.GetComponent<CellBehaviour>().Cell).All(cell => cell.IsOpen || cell.IsBomb);
    }
}
