public class EmptyCell : Cell
{
    public EmptyCell() : base() { }
    public override CellState CreateCellState()
    {
        return new EmptyCellState();
    }
}