class Program
{
    static void Main(string[] args)
    {
        int feet;
        int yard;
        string[] line;

        Console.Write("Enter a distance in feet: ");
        feet = int.Parse(Console.ReadLine());

        yard = feet / 3;

        Console.WriteLine("Yards: " + yard);

        int ft1, ft2, ft3;
        int y1, y2, y3;

        Console.Write("Enter 3 distance: ");
        line = Console.ReadLine().Split();

        ft1 = int.Parse(line[0]);
        ft2 = int.Parse(line[1]);
        ft3 = int.Parse(line[2]);

        y1 = ft1 / 3;
        y2 = ft2 / 3;
        y3 = ft3 / 3;

        Console.WriteLine("Distance in yards: " + y1 + ", " + y2 + ", " + y3);
        
        /*
        foreach (string str in line)
            Console.WriteLine(str);

        for(int i = 0; i < line.length; i++)
            Console.WriteLine(line[i]);
        */
    }
}