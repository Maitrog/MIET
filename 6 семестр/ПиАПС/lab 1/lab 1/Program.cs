using lab_1.AbstractFactory;
using lab_1.Singleton;
List<BoardAnyCar> boards = new List<BoardAnyCar>();

for(int i = 0; i < 10; i++)
{
    boards.Add(new TrackBoard());
    boards.Add(new BusBoard());
    boards.Add(new TaxiBoard());
} 

for(int i = 0; i < boards.Count; i++)
{
    if (boards[i].IsReady())
    {
        Console.WriteLine(boards[i].Info() + ": " + boards[i].IsReady());
    }
}