public class BombCell : Cell
{
    public BombCell() : base() { }
    public override CellState CreateCellState()
    {
        return new BombCellState();
    }
}