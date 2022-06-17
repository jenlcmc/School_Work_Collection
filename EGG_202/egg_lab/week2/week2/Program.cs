using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace week2
{
    class Program
    {   
        static double Tax(double total)
        {
            double tax = (86.0 / 100.0) * total / 1.0;
            return tax;
        }

        static double Clothes(double total)
        {
            double clothes = (10.0 / 100.0) * total / 1.0;
            return clothes;
        }

        static double School(double total)
        {
            double school = (1.0 / 100.0) * total / 1.0;
            return school;
        }

        static double Saving(double total)
        {
            double saving = (25.0 / 100.0) * total / 1.0;
            return saving;
        }

        //fix
        static double Parent(double total)
        {
            double parent = total * 1.0 / 2.0;
            return parent;
        }
        static void Main(string[] args)
        {
            const int week = 5;
            double payrate;
            double[] hoursWeek = new double[week];
            double total = 0;
            double afterTax = 0;
            double clothes = 0;
            double supplies = 0;
            double saving = 0;
            double remain = 0;
            double parent = 0;

            Console.Write("Please enter payrate $ ");
            payrate = double.Parse(Console.ReadLine());

            //fix
            for(int i = 0; i < week; ++i)
            {
                Console.Write("Enter hours worked in week " + i  + ": ");
                hoursWeek[i] = double.Parse(Console.ReadLine());
                total += hoursWeek[i];
            }
            total *= payrate;
            afterTax = Math.Round(Tax(total), 2);

            clothes = Math.Round(Clothes(afterTax), 2);
            supplies = Math.Round(School(afterTax), 2);
            remain = afterTax - clothes - supplies;
            saving = Math.Round(Saving(remain), 2);

            // fix
            parent = Math.Round(Parent(saving), 2);

            Console.WriteLine("Summer Budget");
            Console.WriteLine("Income before taxes \t $ \t" + total);
            Console.WriteLine("Income after taxes \t $ \t" + afterTax);
            Console.WriteLine("Cloths \t $ \t" + clothes);
            Console.WriteLine("School supplies \t $ \t" + supplies);
            Console.WriteLine("Saving bonds \t $ \t" + saving);
            Console.WriteLine("Parents savings bonds \t $ \t" + parent);
            
           // Console.WriteLine(parent);
        }
    }
}
