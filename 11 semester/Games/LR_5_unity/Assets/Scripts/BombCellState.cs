public class BombCellState : CellState
{
    public override int Click()
    {
        if (IsMark)
        {
            return -2;
        }
        return GetBombCount();
    }

    public override int GetBombCount()
    {
        return -1;
    }

    public override void Update(IObservable subject)
    {
    }
}