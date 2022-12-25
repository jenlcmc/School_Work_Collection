// Description: Simple program that call functions to calculate the average, variance, and standard deviation of a list of numbers.
// notes: Professor said to experiment with GoRountine that why i have extra code for GoRoutine to test it
// but overall they should give the same result
package main

//some libraries
import (
	"fmt"
	"math"
	"math/rand"
	"os"
)

// constant variables
const MIN = 10
const MAX = 1000000

// quick sort using GoRoutine and sort package
func QuickSortGoRoutine(numbers []int, low int, hight int) {
	//pivot
	if low < hight {
		pivot := partition(numbers, low, hight)
		//recursion left side using GoRoutine
		go QuickSortGoRoutine(numbers, low, pivot-1)
		//recursion right side using GoRoutine
		go QuickSortGoRoutine(numbers, pivot+1, hight)
	}
}

/*
QuickSort – Routine to sort the numbers into ascending order (small to large) using the
Quick Sort.
*/
func QuickSort(numbers []int, low int, hight int) {
	//pivot
	if low < hight {
		pivot := partition(numbers, low, hight)
		//recursion left side
		QuickSort(numbers, low, pivot-1)
		//recursion right side
		QuickSort(numbers, pivot+1, hight)
	}
}

// partition using GoRoutine and sort package
func partition(numbers []int, low int, hight int) int {
	//pivot
	pivot := numbers[hight]
	i := low - 1
	//partition
	for j := low; j < hight; j++ {
		//find number on left that should be on right
		if numbers[j] <= pivot {
			i++
			numbers[i], numbers[j] = numbers[j], numbers[i]
		}
	}
	//swap the numbers
	numbers[i+1], numbers[hight] = numbers[hight], numbers[i+1]
	return i + 1
}

/*DisplayNums – Routine to display the numbers in the array (up to count).*/
func DisplayNums(numbers []int, count int) {
	for i := 0; i < count; i++ {
		fmt.Printf("%d ", numbers[i])
	}
	fmt.Println()
}

/*Stats – Routine to find the average, variance, and standard deviation of the numbers in the array.*/
//formula = (sum of (i - average)^2 from i = 0 to i = count -1 ) / count - 1)
func Stats(numbers []int, count int) {
	var sum int = 0
	var average float64
	var variance float64
	var stdev float64

	//sum
	for i := 0; i < count; i++ {
		sum += numbers[i]
	}
	//average
	average = float64(sum) / float64(count)

	//variance sum
	for i := 0; i < count; i++ {
		variance += math.Pow(float64(numbers[i])-average, 2)
	}
	//variance
	variance = variance / float64(count-1)
	//standard deviation
	stdev = math.Sqrt(variance)

	fmt.Printf("Average: %.2f\n", average)
	fmt.Printf("Variance: %.2f\n", variance)
	fmt.Printf("Standard Deviation: %.2f\n", stdev)
}

/*
GetData – Routine to create a list of random numbers. The routine should obtain the count of numbers to create from the command line.
Then, the routine must place count many numbers in the array.
Create random numbers between 0 and 10,000 (i.e., use: rand.Intn(1000) )
*/
func GetData(count int) []int {
	var numbers []int = make([]int, count)
	for i := 0; i < count; i++ {
		numbers[i] = rand.Intn(1000)
	}
	return numbers
}

// The main should read the count of numbers to generate from the command line and, if valid, call the applicable routines.
func main() {
	var count int
	//make an array
	var numbers []int

	//read command line to get count
	if len(os.Args) != 2 {
		fmt.Println("Usage: proj8 <count>")
		os.Exit(1)
	}
	//put args[1] into count
	fmt.Sscanf(os.Args[1], "%d", &count)

	//check if count is valid
	if count >= MIN && count <= MAX {
		//get random numbers
		numbers = GetData(count)
		//display the data
		fmt.Println("Unsorted Array: ")
		DisplayNums(numbers, count)
		//sort the data
		QuickSort(numbers, 0, count-1)

		//test GoRoutine
		//QuickSortGoRoutine(numbers, 0, count - 1)

		//display the data
		fmt.Println("-------------------------------------")
		fmt.Println("Sorted Array: ")
		DisplayNums(numbers, count)
		//get the stats
		fmt.Println("-------------------------------------")
		Stats(numbers, count)
	} else {
		fmt.Println("Invalid count of numbers to generate.")
		os.Exit(1)
	}

	//end of program
	os.Exit(0)
}
