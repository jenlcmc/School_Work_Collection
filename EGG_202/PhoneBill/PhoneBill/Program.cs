using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PhoneBill
{
    class Program
    {
        static void Main(string[] args)
        {

            // VARIABLES
            string planType;
            string StringregMin;
            string stringcost = "";
            int regMinutes;
            int premDayMinutes, premNightMinutes;
            int minoverD;
            int minoverN;
            double cost, dcost, ncost;

            // EXTRA CREDIT VARIABLES
            bool valid;
            bool valid2;
            int number;


        // PLAN SELECTION
        programm:
            Console.Write("Enter  service  plan: ");
            planType = Console.ReadLine().ToUpper();

            // REGULAR PLAN
            if (planType == "REGULAR")
            {
            Regular:
                Console.Write("Enter minutes: ");
                StringregMin = Console.ReadLine();
                valid = int.TryParse(StringregMin, out number);

                if (valid == true)
                {
                    int a = int.Parse(StringregMin);
                    regMinutes = a;

                    if (regMinutes > 50)
                    {
                        minoverD = (regMinutes - 50);
                        cost = 10 + (minoverD * 0.2);

                        Console.WriteLine(" ");
                        Console.WriteLine("Service - REGULAR");
                        Console.WriteLine("Minutes Over                 " + minoverD);
                        stringcost = String.Format("{0:0.00}", cost);
                        Console.WriteLine("Cost                $     " + stringcost);
                    rep1:
                        Console.WriteLine(" ");
                        Console.WriteLine("Restart? (Y/N)");
                        string ans = Console.ReadLine();
                        switch (ans.ToUpper())
                        {
                            case "Y": goto programm;
                            case "N": break;
                            default: goto rep1;
                        }
                    }

                    else if (regMinutes >= 0 && regMinutes <= 50)
                    {
                        cost = 10;
                        Console.WriteLine(" ");
                        Console.WriteLine("Service - REGULAR");
                        Console.WriteLine("Minutes Over                  0");
                        stringcost = String.Format("{0:0.00}", cost);
                        Console.WriteLine("Cost                $     " + stringcost);
                    rep2:
                        Console.WriteLine(" ");
                        Console.WriteLine("Restart? (Y/N)");
                        string ans = Console.ReadLine();
                        switch (ans.ToUpper())
                        {
                            case "Y": goto programm;
                            case "N": break;
                            default: goto rep2;
                        }
                    }
                }
                else
                {
                    Console.WriteLine("Invalid number, please try again");
                    Console.WriteLine(" ");
                    goto Regular;

                }
            }

            //PREMIUM PLAN
            else if (planType == "PREMIUM")
            {
            Premium:
                Console.Write("Enter day and night minutes: ");
                string[] tokens = Console.ReadLine().Split();
                valid = int.TryParse(tokens[0], out number);
                valid2 = int.TryParse(tokens[1], out number);

                if (valid == true && valid2 == true)
                {
                    premDayMinutes = int.Parse(tokens[0]);
                    premNightMinutes = int.Parse(tokens[1]);

                    // (NOTE)This part could be optimized bc there are a lot of ifs lol

                    //DAY AND NIGHT MIN OVER
                    if (premDayMinutes > 75
                        && premNightMinutes > 100)
                    {
                        minoverD = (premDayMinutes - 75);
                        dcost = minoverD * 0.1;

                        minoverN = (premNightMinutes - 100);
                        ncost = minoverN * 0.05;

                        Console.WriteLine(" ");
                        Console.WriteLine("Service - PREMIUM");
                        Console.WriteLine("Day minutes Over             " + minoverD);
                        Console.WriteLine("Night minutes Over           " + minoverN);
                        cost = (25 + dcost + ncost);
                        stringcost = String.Format("{0:0.00}", cost);
                        Console.WriteLine("Cost                $     " + stringcost);
                    rep3:
                        Console.WriteLine(" ");
                        Console.WriteLine("Restart? (Y/N)");
                        string ans = Console.ReadLine();
                        switch (ans.ToUpper())
                        {
                            case "Y": goto programm;
                            case "N": break;
                            default: goto rep3;
                        }
                    }

                    // DAY AND NIGHT MIN BELOW
                    if (premDayMinutes >= 0 && premDayMinutes <= 75
                        && premNightMinutes >= 0 && premNightMinutes <= 100)
                    {
                        minoverD = 0;
                        dcost = 0;
                        minoverN = 0;
                        ncost = 0;

                        Console.WriteLine(" ");
                        Console.WriteLine("Service - PREMIUM");
                        Console.WriteLine("Day minutes Over              " + minoverD);
                        Console.WriteLine("Night minutes Over            " + minoverN);
                        cost = (25 + dcost + ncost);
                        stringcost = String.Format("{0:0.00}", cost);
                        Console.WriteLine("Cost                $     " + stringcost);
                    rep4:
                        Console.WriteLine(" ");
                        Console.WriteLine("Restart? (Y/N)");
                        string ans = Console.ReadLine();
                        switch (ans.ToUpper())
                        {
                            case "Y": goto programm;
                            case "N": break;
                            default: goto rep4;
                        }
                    }

                    // DAY OVER NIGHT BELOW
                    if (premDayMinutes > 75
                        && premNightMinutes >= 0 && premNightMinutes <= 100)
                    {
                        minoverD = (premDayMinutes - 75);
                        dcost = minoverD * 0.1;
                        minoverN = 0;
                        ncost = 0;

                        Console.WriteLine(" ");
                        Console.WriteLine("Service - PREMIUM");
                        Console.WriteLine("Day minutes Over             " + minoverD);
                        Console.WriteLine("Night minutes Over            " + minoverN);
                        cost = (25 + dcost + ncost);
                        stringcost = String.Format("{0:0.00}", cost);
                        Console.WriteLine("Cost                $     " + stringcost);
                    rep5:
                        Console.WriteLine(" ");
                        Console.WriteLine("Restart? (Y/N)");
                        string ans = Console.ReadLine();
                        switch (ans.ToUpper())
                        {
                            case "Y": goto programm;
                            case "N": break;
                            default: goto rep5;
                        }

                    }

                    // DAY BELOW NIGHT OVER
                    if (premNightMinutes > 100
                        && premDayMinutes >= 0 && premDayMinutes <= 75)
                    {
                        minoverN = (premNightMinutes - 100);
                        ncost = minoverN * 0.05;
                        minoverD = 0;
                        dcost = 0;

                        Console.WriteLine(" ");
                        Console.WriteLine("Service - PREMIUM");
                        Console.WriteLine("Day minutes Over              " + minoverD);
                        Console.WriteLine("Night minutes Over           " + minoverN);
                        cost = (25 + dcost + ncost);
                        stringcost = String.Format("{0:0.00}", cost);
                        Console.WriteLine("Cost                $     " + stringcost);
                    rep6:
                        Console.WriteLine(" ");
                        Console.WriteLine("Restart? (Y/N)");
                        string ans = Console.ReadLine();
                        switch (ans.ToUpper())
                        {
                            case "Y": goto programm;
                            case "N": break;
                            default: goto rep6;
                        }


                    }
                }
                else
                {
                    Console.WriteLine("Invalid numbers, please try again");
                    Console.WriteLine(" ");
                    goto Premium;
                }
            }
            else
            {
                Console.WriteLine("Plan not recognized, please try again.");
                Console.WriteLine(" ");
                goto programm;
            }
        }
    }
}
