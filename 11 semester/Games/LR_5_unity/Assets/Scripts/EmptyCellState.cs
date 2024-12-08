public class EmptyCellState : CellState
{
    public override int Click()
    {
        if (IsMark)
        {
            return -2;
        }
        Update(this);
        return GetBombCount();
    }

    public override int GetBombCount()
    {
        int count = 0;
        foreach (var cell in Cells)
        {
            if (cell.CellState is BombCellState)
            {
                count++;
            }
        }
        return count;
    }

    public override void Update(IObservable subject)
    {
        {
            if (IsOpen == false)
            {
                IsMark = false;
                Open();
                if (GetBombCount() == 0)
                {
                    Notify();
                }
            }
        }
    }
}